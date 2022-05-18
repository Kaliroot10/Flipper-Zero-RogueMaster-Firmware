
# [Flipper Zero Firmware](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/ReadMe.md) <= READ THIS READ ME
- FLASH STOCK FIRST BEFORE UPDATING TO CUSTOM FIRMWARE
# with some [MuddleBox](https://github.com/MuddledBox/flipperzero-firmware) changes + plugins.

Latest Updates:
- Fixed stopwatch sound options
- Fixed random name generated for RAW and NFC/RFID reads to have date and time.
- Merged new updates from main and for Spectrum Analyzer.

**Special Instructions:**
- Download these files into the subghz/assets folder on your SD card. Edit the two `_map` files to contain your specific subghz (.SUB) files.
- - Note 1: If you don't have a subghz/assets folder, you should ensure you have made at least one clean flash with stock firmware and your SD card installed in order to ensure the database structure is built, otherwise it will not exist for alternative forks.
- - Note 2: /any is a special keyword signifying either /int (internal storage) or /ext (external storage).
- - Note 3: the changes you are making to the `_map` files is to point to the location of the specific assets of the touchtunes folder as well as the universal RF map apps which you will have to develop or compile seperately and are not a part of this repo. 
- - Note 4: /any is effectively root, so the folder structure should start "/any/subghz/assets" and not what is based on the repo below do not blindly copy the repo it will not work.
- - [assets/resources/subghz/assets/universal_rf_map](https://github.com/RogueMaster/flipperzero-firmware-wPlugins/blob/dev/assets/resources/subghz/assets/universal_rf_map)
- - [assets/resources/subghz/assets/touchtunes_map](https://github.com/RogueMaster/flipperzero-firmware-wPlugins/blob/dev/assets/resources/subghz/assets/touchtunes_map)
- - [assets/resources/subghz/assets/setting_user](https://github.com/RogueMaster/flipperzero-firmware-wPlugins/blob/dev/assets/resources/subghz/assets/setting_user)
- - [assets/resources/subghz/assets/setting_frequency_analyzer_user](https://github.com/RogueMaster/flipperzero-firmware-wPlugins/blob/dev/assets/resources/subghz/assets/setting_frequency_analyzer_user)
- Download this file into the nfc/assets folder on your SD card. 
- - [assets/resources/nfc/assets/mf_classic_dict.nfc](https://github.com/RogueMaster/flipperzero-firmware-wPlugins/blob/dev/assets/resources/nfc/assets/mf_classic_dict.nfc)
- Add a folder to SD card named `wav_player` (for 8bit 2ch unsigned wav files) 
- Add a folder to SD card named `music_player` (FMF and RTTTL/TXT files)

Special shout out to these libraries for giving us more fun:
- https://github.com/Gioman101/FlipperAmiibo
- https://github.com/jimilinuxguy/flipperzero-touchtunes
- https://github.com/Lucaslhm/AmiiboFlipperConverter
- https://github.com/MuddledBox/FlipperZeroCases
- https://github.com/MuddledBox/FlipperZeroSub-GHz
- https://github.com/neverfa11ing/FlipperMusicRTTTL
- https://github.com/UberGuidoZ/Flipper
- https://github.com/UberGuidoZ/Flipper-IRDB

Plugins:
- [Clock/Stopwatch (By CompaqDisc, Stopwatch & sound alert by me)](https://gist.github.com/CompaqDisc/4e329c501bd03c1e801849b81f48ea61)
- [Flappy Bird (By DroomOne)](https://github.com/DroomOne/flipperzero-firmware/tree/dev/applications/flappy_bird)
- [Tetris (By jeffplang)](https://github.com/jeffplang/flipperzero-firmware/tree/tetris_game/applications/tetris_game)
- [WAV Player (By Zlo)](https://github.com/flipperdevices/flipperzero-firmware/tree/zlo/wav-player)
- [RF Remote (By jimilinuxguy)](https://github.com/jimilinuxguy/flipperzero-universal-rf-remote/tree/main/applications/universal_rf)
- [Touch Tunes Remote (By jimilinuxguy)](https://github.com/jimilinuxguy/flipperzero-universal-rf-remote/tree/028d615c83f059bb2c905530ddb3d4efbd3cbcae/applications/jukebox)
- [Spectrum Analyzer (By jolcese)](https://github.com/jolcese/flipperzero-firmware/tree/spectrum/applications/spectrum_analyzer)

Changes from main: 
 - applications/applications.c
 - applications/applications.mk
 - applications/clock_app/clock_app.c
 - applications/flappy_bird/bird.h
 - applications/flappy_bird/flappy_bird.c
 - applications/jukebox/jukebox.c
 - applications/notification/notification_settings_app.c
 - applications/snake_game/snake_game.c
 - applications/spectrum_analyzer/spectrum_analyzer.c
 - applications/spectrum_analyzer/spectrum_analyzer.h
 - applications/spectrum_analyzer/spectrum_analyzer_worker.c
 - applications/spectrum_analyzer/spectrum_analyzer_worker.h
 - applications/subghz/scenes/subghz_scene_read_raw.c
 - applications/subghz/subghz_setting.c
 - applications/tetris_game/tetris_game.c
 - applications/universal_rf/universal_rf.c
 - applications/wav_player/wav_parser.c
 - applications/wav_player/wav_parser.h
 - applications/wav_player/wav_player.c
 - applications/wav_player/wav_player_hal.c
 - applications/wav_player/wav_player_hal.h
 - applications/wav_player/wav_player_view.c
 - applications/wav_player/wav_player_view.h
 - assets/compiled/assets_icons.c
 - assets/compiled/assets_icons.h
 - assets/icons/MainMenu/Clock_14/frame_01.png
 - assets/icons/MainMenu/Clock_14/frame_02.png
 - assets/icons/MainMenu/Clock_14/frame_03.png
 - assets/icons/MainMenu/Clock_14/frame_04.png
 - assets/icons/MainMenu/Clock_14/frame_05.png
 - assets/icons/MainMenu/Clock_14/frame_06.png
 - assets/icons/MainMenu/Clock_14/frame_07.png
 - assets/icons/MainMenu/Clock_14/frame_08.png
 - assets/icons/MainMenu/Clock_14/frame_rate
 - assets/icons/MainMenu/MusicPlayer_14/frame_0.png
 - assets/icons/MainMenu/MusicPlayer_14/frame_1.png
 - assets/icons/MainMenu/MusicPlayer_14/frame_2.png
 - assets/icons/MainMenu/MusicPlayer_14/frame_3.png
 - assets/icons/MainMenu/MusicPlayer_14/frame_4.png
 - assets/icons/MainMenu/MusicPlayer_14/frame_rate
 - assets/icons/MainMenu/UniversalRemote_14/frame_00_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_01_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_02_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_03_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_04_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_05_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_06_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_07_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_08_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_09_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_10_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_11_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_12_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_13_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_14_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_15_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_16_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_17_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_18_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_19_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_20_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_21_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_22_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_23_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_24_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_25_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_26_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_27_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_28_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_29_delay-0.04s.png
 - assets/icons/MainMenu/UniversalRemote_14/frame_rate
 - assets/resources/nfc/assets/mf_classic_dict.nfc
 - assets/resources/subghz/assets/setting_frequency_analyzer_user
 - assets/resources/subghz/assets/setting_user
 - assets/resources/subghz/assets/touchtunes_map
 - assets/resources/subghz/assets/universal_rf_map
 - firmware/targets/f7/furi_hal/furi_hal_subghz.c
 - firmware/targets/f7/target.mk
 - lib/toolbox/random_name.c
