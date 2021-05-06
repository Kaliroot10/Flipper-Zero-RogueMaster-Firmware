#pragma once
#include <api-hal.h>
#include "key-info.h"
#include "encoder-generic.h"
#include "encoder-emmarine.h"
#include "encoder-hid-h10301.h"
#include "encoder-indala-40134.h"
#include "pulse-joiner.h"
#include <map>

class RfidTimerEmulator {
public:
    enum class Type : uint8_t {
        EM,
        HID_H10301,
        Indala_40134,
    };

    RfidTimerEmulator();
    ~RfidTimerEmulator();
    void start(Type type);
    void stop();
    void emulate();

private:
    EncoderGeneric* current_encoder = nullptr;

    std::map<Type, EncoderGeneric*> encoders = {
        {Type::EM, new EncoderEM()},
        {Type::HID_H10301, new EncoderHID_H10301()},
        {Type::Indala_40134, new EncoderIndala_40134()},
    };

    PulseJoiner pulse_joiner;
    static void timer_update_callback(void* _hw, void* ctx);
};