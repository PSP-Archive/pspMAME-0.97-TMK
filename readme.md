The source code in this repository is for version r5 of the TMK fork.

# Guide

The emulator comes in several different builds - one of each arcade system being emulated: one for the CPS2, one for Taito, Konami, and so on. The list of compatible ROMs shown within the emulator reflects only the individual build. Not everything on the list actually works.

For the games that do work, emulation is largely accurate and free from glitches, but this accuracy comes at the cost of limited performance. Setting the clock speed to 333Mhz, increasing frame skip and turning off the audio may help to make games playable.

## Controls

### Menu controls

- L: settings.
- 〇: accept.
- ×: cancel.
- △: filter the list of ROMs.
- Home: End menu

### In-game controls

- L: settings.
	- 〇: accept. 
	- ×: cancel.
- R: pause.
- SELECT: insert coin.
- START: start.
- △ 〇 × □: buttons 1 to 4.
- L + R + START: exit to menu.

## ROMs path

ROMs are to be compressed in the zip format, and placed in a folder in one of these paths:

- Current ./roms
- ms0: / mame / roms
- ms0:/psp/game/mamepsp/roms
	
By default, the emulator will display a list of all ROMs compatible with the current build.

The list can be filtered to only show compatible ROMs available within the folder by pressing △, or by setting 'ROM display mode' to 'available list'.
