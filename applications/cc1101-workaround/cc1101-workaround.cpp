#include "flipper.h"

#include "cc1101-workaround/cc1101.h"

#define MIN_DBM -120
#define STEP_DBM 10
#define RSSI_DELAY 600 //rssi delay in micro second

#define RSSI_THRESHOLD -60

#define START_SUB_BAND 3
#define STOP_SUB_BAND 3
#define NUM_OF_SUB_BANDS 7
#define CAL_INT 20 // cal every 10 channels(every 1MHz)

// variables used to calculate rssi
uint8_t rssi_dec;
int16_t rssi_dBm;
uint8_t rssi_offset[NUM_OF_SUB_BANDS] = {74, 74, 74, 74, 74, 74, 74};

#define CHAN_SPA 0.05 // channel spacing

// no change in TEST0 WHERE (>430.5MHz) one should change from TEST0=0x0B to 0x09
uint16_t limitTest0Reg[NUM_OF_SUB_BANDS] = {256, 256, 256, 103, 0, 0, 0};

/* setting to use 50khz channel spacing whole band*****************************************/

int16_t rssiTable[256];
uint16_t channelNumber[256];

// counter used to keep track on how many CS has been asserted
uint8_t carrierSenseCounter = 0;


int16_t calRSSI(uint8_t rssi_dec, uint8_t rssiOffset) {
    int16_t rssi;

    if(rssi_dec >= 128) {
        rssi = (int16_t)((int16_t)(rssi_dec - 256) / 2) - rssiOffset;
    } else {
        rssi = (rssi_dec / 2) - rssiOffset;
    }

    return rssi;
}

/*
void scanFreq(CC1101* cc1101) {
    uint8_t calCounter; // to determine when to calibrate
    uint8_t subBand;
    uint16_t channel;
    uint16_t i;

    float freq;

    cc1101->SpiWriteReg(CC1101_MCSM0, 0x08); // disalbe FS_AUTOCAL
    cc1101->SpiWriteReg(CC1101_AGCCTRL2, 0x43 | 0x0C); // MAX_DVGA_GAIN to 11 for fast rssi
    cc1101->SpiWriteReg(CC1101_AGCCTRL0, 0xB0); // max AGC WAIT_TIME; 0 filter_length
    cc1101->SetMod(GFSK); // set to GFSK for fast rssi measurement | +8 is dcfilter off

    // 1) loop through all sub bands
    for(subBand = START_SUB_BAND; subBand < STOP_SUB_BAND + 1; subBand++) {
        // 1.1) set subBands freq by FREQ2, FREQ1, FREQ0
        cc1101->SetFreq(
            freqSettings[subBand][0], freqSettings[subBand][1], freqSettings[subBand][2]);
        // 1.2) set TEST0--maybe!
        // 1.3) reset calibration counter
        calCounter = 0;
        // 1.4) loop throuhg all channels
        for(channel = firstChannel[subBand]; channel <= lastChannel[subBand]; channel++) {
            uint8_t pktStatus;
            // 1.4.1) set channel register
            cc1101->SetChannel(channel);

            // 1.4.2)  set TEST0
            if(channel == limitTest0Reg[subBand]) {
                //set test0 to 0x09
                cc1101->SpiWriteReg(CC1101_TEST0, 0x09);
                //set FSCAL2 to 0x2A to force VCO HIGH
                cc1101->SpiWriteReg(CC1101_FSCAL2, 0x2A);
                //clear calCounter to invoke mannual calibration
                calCounter = 0;
            }
            // 1.4.3) calibrate every 1MHz
            if(calCounter++ == 0) {
                // perform a manual calibration by issuing SCAL command
                cc1101->SpiStrobe(CC1101_SCAL);
            }
            // 1.4.4) reset calCounter when 1MHz reached
            if(calCounter == CAL_INT) {
                calCounter = 0;
            }
            // 1.4.5-6 enter rx mode
            cc1101->SetReceive();
            // 1.4.7 wait for RSSI to be valid: less than 1.5ms
            delayMicroseconds(RSSI_DELAY);
            // 1.4.8) read PKTSTATUS register while the radio is in RX state
            pktStatus = cc1101->SpiReadStatus(CC1101_PKTSTATUS);
            // 1.4.9) enter IDLE state by issuing a SIDLE command
            cc1101->SpiStrobe(CC1101_SIDLE);
            // 1.4.10) check if CS is assearted
            // //read rssi value and converto to dBm form
            rssi_dec = (uint8_t)cc1101->SpiReadStatus(CC1101_RSSI);
            rssi_dBm = calRSSI(rssi_dec, rssi_offset[subBand]);

            // rssiData[subBand][channel]=rssi_dBm;
            if(pktStatus & 0x40) { //CS assearted
                // store rssi value and corresponding channel number
                rssiTable[carrierSenseCounter] = rssi_dBm;
                channelNumber[carrierSenseCounter] = channel;
                carrierSenseCounter++;
            }

#ifdef CC1101_DEBUG
            printf("rssi_dBm: %d\n", rssi_dBm);
#endif
        } // end channel lop

        // 1.5)before moving to next sub band,
        // scan through rssiTable to find highest rssi value
        for(i = 0; i < carrierSenseCounter; i++) {
            if(rssiTable[i] > highRSSI[subBand]) {
                highRSSI[subBand] = rssiTable[i];
                selectedChannel[subBand] = channelNumber[i];
            }
        }

        // printf("subBand:------------------>");
        // Serial.println(subBand);
        // Serial.print("selectedChannel:");
        // Serial.println(selectedChannel[subBand]);
        // Serial.print("highRSSI:");
        // Serial.println(highRSSI[subBand]);

        // 1.6) reset carrierSenseCounter
        carrierSenseCounter = 0;
    } // end band loop

    // 2) when all sub bands has been scanned , find best subband and channel
    int16_t tempRssi = MIN_DBM;
    for(subBand = 0; subBand < NUM_OF_SUB_BANDS; subBand++) {
        if(highRSSI[subBand] > tempRssi) {
            tempRssi = highRSSI[subBand];
            activeChannel = selectedChannel[subBand];
            activeBand = subBand;
        }
    }

    // printf("activeBand:**********> %d, activeChannel %d,\n", activeBand, activeChannel);

    cc1101->SpiWriteReg(CC1101_MCSM0, 0x18); //enable FS_AUTOCAL
    cc1101->SpiWriteReg(CC1101_AGCCTRL2, 0x43); //back to recommended config
    cc1101->SpiWriteReg(CC1101_AGCCTRL0, 0x91); //back to recommended config
}

void tx(CC1101* cc1101, uint8_t band, uint16_t channel, uint16_t miniSec) {
    cc1101->SetFreq(freqSettings[band][0], freqSettings[band][1], freqSettings[band][2]);
    cc1101->SetChannel(channel);
    // digitalWrite(19,0);
    cc1101->SetTransmit();
    delay(miniSec);

    cc1101->SpiStrobe(CC1101_SIDLE);
}
*/

typedef struct {
    float base_freq;
    uint8_t settings[3]; // FREQ2, FREQ1, FREQ0
    uint8_t first_channel;
    uint8_t last_channel;
} Band;

typedef struct {
    Band* band;
    uint16_t channel;
} FreqConfig;

Band bands[NUM_OF_SUB_BANDS] = {
    {387, {0x0E, 0xE2, 0x76}, 0, 255},
    {399.8, {0x0F, 0x60, 0x76}, 0, 255},
    {412.6, {0x0F, 0xDE, 0x76}, 0, 255},
    {425.4, {0x10, 0x5C, 0x76}, 160, 180},
    {438.2, {0x10, 0xDA, 0x76}, 0, 255},
    {451, {0x11, 0x58, 0x8F}, 0, 255},
    {463.8, {0x11, 0xD6, 0x8F}, 0, 4},
};

FreqConfig FREQ_LIST[] = {
    {&bands[0], 0},
    {&bands[0], 50},
    {&bands[0], 100},
    {&bands[0], 150},
    {&bands[0], 200},
    {&bands[1], 0},
    {&bands[1], 50},
    {&bands[1], 100},
    {&bands[1], 150},
    {&bands[1], 200},
    {&bands[2], 0},
    {&bands[2], 50},
    {&bands[2], 100},
    {&bands[2], 150},
    {&bands[2], 200},
    {&bands[3], 160},
    {&bands[3], 170},
    {&bands[4], 0},
    {&bands[4], 50},
    {&bands[4], 100},
    {&bands[4], 150},
    {&bands[4], 200},
    {&bands[5], 0},
    {&bands[5], 50},
    {&bands[5], 100},
    {&bands[5], 150},
    {&bands[5], 200},
    {&bands[6], 0},
};

typedef enum {
    EventTypeTick,
    EventTypeKey,
} EventType;

typedef struct {
    union {
        InputEvent input;
    } value;
    EventType type;
} Event;

typedef enum {
    ModeRx,
    ModeTx
} Mode;

typedef struct {
    Mode mode;
    size_t active_freq;
} State;

static void render_callback(CanvasApi* canvas, void* ctx) {
    State* state = (State*)acquire_mutex((ValueMutex*)ctx, 25);

    canvas->clear(canvas);
    canvas->set_color(canvas, ColorBlack);
    canvas->set_font(canvas, FontPrimary);
    canvas->draw_str(canvas, 2, 12, "cc1101 workaround");

    {
        char buf[24];
        FreqConfig conf = FREQ_LIST[state->active_freq];
        float freq =  conf.band->base_freq + CHAN_SPA * conf.channel;
        sprintf(buf, "freq: %ld.%02ld MHz", (uint32_t)freq, (uint32_t)(freq * 100.) % 100);

        canvas->set_font(canvas, FontSecondary);
        canvas->draw_str(canvas, 2, 25, buf);
    }

    release_mutex((ValueMutex*)ctx, state);
}

static void input_callback(InputEvent* input_event, void* ctx) {
    osMessageQueueId_t event_queue = (QueueHandle_t)ctx;

    Event event;
    event.type = EventTypeKey;
    event.value.input = *input_event;
    osMessageQueuePut(event_queue, &event, 0, 0);
}

extern "C" void cc1101_workaround(void* p) {
    osMessageQueueId_t event_queue = 
        osMessageQueueNew(1, sizeof(Event), NULL);
    assert(event_queue);

    State _state;
    _state.mode = ModeRx;
    _state.active_freq = 0;

    ValueMutex state_mutex;
    if(!init_mutex(&state_mutex, &_state, sizeof(State))) {
        printf("[cc1101] cannot create mutex\n");
        furiac_exit(NULL);
    }

    Widget* widget = widget_alloc();

    widget_draw_callback_set(widget, render_callback, &state_mutex);
    widget_input_callback_set(widget, input_callback, event_queue);

    // Open GUI and register widget
    GuiApi* gui = (GuiApi*)furi_open("gui");
    if(gui == NULL) {
        printf("[cc1101] gui is not available\n");
        furiac_exit(NULL);
    }
    gui->add_widget(gui, widget, WidgetLayerFullscreen);

    printf("[cc1101] creating device\n");
    CC1101 cc1101(GpioPin{CC1101_CS_GPIO_Port, CC1101_CS_Pin});
    printf("[cc1101] init device\n");

    uint8_t address = cc1101.Init();
    if(address > 0) {
        printf("[cc1101] init done: %d\n", address);
    } else {
        printf("[cc1101] init fail\n");
        furiac_exit(NULL);
    }

    // RX filter bandwidth 58.035714(0xFD) 100k(0xCD) 200k(0x8D)
    cc1101.SpiWriteReg(CC1101_MDMCFG4, 0xCD);
    // datarate config 250kBaud  for the purpose of fast rssi measurement
    cc1101.SpiWriteReg(CC1101_MDMCFG3, 0x3B);
    // FEC preamble etc. last 2 bits for channel spacing
    cc1101.SpiWriteReg(CC1101_MDMCFG1, 0x20);
    // 50khz channel spacing
    cc1101.SpiWriteReg(CC1101_MDMCFG0, 0xF8);

    Event event;
    while(1) {
        if(osMessageQueueGet(event_queue, &event, NULL, osWaitForever) == osOK) {
            State* state = (State*)acquire_mutex_block(&state_mutex);

            if(event.type == EventTypeKey) {
                if(event.value.input.state && event.value.input.input == InputBack) {
                    printf("[cc1101] bye!\n");
                    // TODO remove all widgets create by app
                    widget_enabled_set(widget, false);
                    furiac_exit(NULL);
                }

                if(event.value.input.state && event.value.input.input == InputUp) {
                    if(state->active_freq > 0) {
                        state->active_freq--;
                    }
                }

                if(event.value.input.state && event.value.input.input == InputDown) {
                    if(state->active_freq < (sizeof(FREQ_LIST)/sizeof(FREQ_LIST[0]) - 1)) {
                        state->active_freq++;
                    }
                }
            }

            release_mutex(&state_mutex, state);
            widget_update(widget);
        }
    }

    /*
    while(1) {
        for(uint8_t i = 0; i <= NUM_OF_SUB_BANDS; i++) {
            highRSSI[i] = MIN_DBM;
        }

        activeChannel = 300;

        tx(&cc1101, activeBand, activeChannel, 500);

        scanFreq(&cc1101);

        if(activeChannel < 256 && highRSSI[activeBand] > RSSI_THRESHOLD) {
            float freq = base_freq[activeBand] + CHAN_SPA * activeChannel;

            printf(
                "channel: %d, freq: %d, RSSI: %d\n",
                activeChannel,
                (uint32_t)(freq * 1000),
                highRSSI[activeBand]
            );

            *
            if(tx_on) {
                tx(&cc1101, activeBand, activeChannel, 500);
            } else {
                osDelay(1000);
            }
            *
        } else {
            // printf("0 carrier sensed\n");
        }
        *

        uint8_t band = 4; // 438.2 MHz

        *
        cc1101.SetFreq(freqSettings[band][0], freqSettings[band][1], freqSettings[band][2]);
        cc1101.SetChannel(0);
        cc1101.SetTransmit();

        delay(5000);

        cc1101.SpiStrobe(CC1101_SIDLE);
        *

        delay(1000);
    }
    */
}