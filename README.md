# gameboy_emulator

A Game Boy Emulator in C++ using only an Assembly Language Commands, Timings and Opcodes manual titled _Game Boy™ CPU Manual_ by: Pan of Anthrox, GABY, Marat Fayzullin, Pascal Felber, Paul Robson, Martin Korth, kOOPa, Bowser.

## Aim

* Find out how emulators work
* Further knowledge about low-level computing
* To play one my favourite Game Boy games [Donkey Kong 1994](https://en.wikipedia.org/wiki/Donkey_Kong_(1994_video_game))

## Visual Studio

Please use at least MicroSoft Visual Studio 2019 version 16.11. To get started, open this file as project/solution: [./GameBoyEmulator/GameBoyEmulator.sln](./GameBoyEmulator/GameBoyEmulator.sln)

## Tests

See [./GameBoyEmulatorTests](./GameBoyEmulatorTests) for unit tests. This was implemented after getting stuck with buggy opcodes implementation.

### Rom Tests

I found a number of different test gameboy roms. Thank you Blargg!
[Test Roms](https://gbdev.gg8.se/files/roms/blargg-gb-tests/)

## References

* [Motivation 1](https://medium.com/@raphaelstaebler/building-a-gameboy-from-scratch-part-2-the-cpu-d6986a5c6c74)
* [Motivation 2](https://blog.rekawek.eu/2017/02/09/coffee-gb/)
* [Gameboy Architecture, MMU, PPU aid](https://www.youtube.com/watch?v=HyzD8pNlpwI)
* [MMU struct aid](https://www.linkedin.com/pulse/creating-gameboy-emulator-part-1-bruno-croci)
* [DAA instruction aid](http://z80-heaven.wikidot.com/instructions-set:daa)
