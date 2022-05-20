
# [Flipper Zero Firmware](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/ReadMe.md) <= READ THIS READ ME
- FLASH STOCK FIRST BEFORE UPDATING TO CUSTOM FIRMWARE
# with some [MuddleBox](https://github.com/MuddledBox/flipperzero-firmware)/[Unleashed](https://github.com/Eng1n33r/flipperzero-firmware/tree/v0.58.1-CodeGrabber) changes + plugins.

****This software is for experimental purposes only and is not meant for any illegal activity/purposes. We do not condone illegal activity and strongly encourage keeping transmissions to legal/valid uses allowed by law.**

Latest Updates:
- Pulled latest DEV changes from 8a81b79
- Rebuild assets on DFU in order to fix tv.ir issues
- Fixed it so renamed flippers will show correctly over Bluetooth
- No longer a dirty build.
- Added some compiled builds with a rename for those that need it.
- Removed BTE Fix and Mifare Classic changes breaking Nice Flor protocol. Thanks Eng1n33r.
- Pulled Latest RTC changes from DEV e8de94c Release
- Pulled Latest UI/UX changes from DEV 9c3f465 Release
- AutoLock with PIN now works correctly! FYI, it will break connection to qFlipper/CLI on lock.
- Reverted dev changes that break Frequency Analyzer on FreqAnalyzer file and Megacode. Hopefully this gets fixed.
- Added Touchtunes/Universal RF updates and optimizations thanks to jimilinuxguy.

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
