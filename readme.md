The source code in this repository is for version r5 of the TMK fork, found on [TMK's blog](http://tmk2000.blog41.fc2.com/).

- [Full list of supported ROMs](supported.md)

# Guide

The emulator comes in several different builds - one of each arcade system being emulated: one for the CPS2, one for Taito, Konami, and so on. The list of compatible ROMs shown within the emulator reflects only the individual build. Not everything on the list actually works.

For the games that do work, emulation is largely accurate and free from glitches, but this accuracy comes at the cost of limited performance. Setting the clock speed to 333Mhz, increasing frame skip and turning off the audio may help to make games playable.


## ROMs path

ROMs are to be compressed in the zip format, and placed in this folder:

- ms0:/mame/roms

Reportedly accepted paths, but seemingly non-working in r6:

- Current ./roms
- ms0:/psp/game/mamepsp/roms
	
By default, the emulator will display a list of all ROMs compatible with the current build.

The list can be filtered to only show compatible ROMs available within the folder by pressing △, or by setting 'ROM display mode' to 'available list'.

## Dat file for ClrmamePro

Dat files are text files with information about games emulated with a specific version of MAME. There is no .dat file specific to the PSP port of MAME 0.97; the closest match would be the .dat for the mainstream 0.97 release ( [link](MAME 0.97.dat) ).

## Controls

### Menu controls

- L: settings.
- 〇: accept.
- ×: cancel.
- △: filter the list of ROMs.
- Home: Exit to XMB.

### In-game controls

- L: settings.
	- 〇: accept. 
	- ×: cancel.
- R: pause.
- SELECT: insert coin.
- START: start.
- △ 〇 × □: buttons 1 to 4.
- L + R + START: exit to menu; will often cause a hard freeze unless the game is first paused (by pressing R).
