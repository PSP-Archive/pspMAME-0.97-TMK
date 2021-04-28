The source code in this repository is for version r5 of the TMK fork, found on [TMK's blog](http://tmk2000.blog41.fc2.com/).

# Guide

## Builds

The emulator comes in several different builds - one of each arcade system being emulated: one for the CPS2, one for Taito, Konami, and so on. The list of compatible ROMs shown within the emulator reflects only the individual build.

| Name                                                             | Games | Dat                                                                                |
|------------------------------------------------------------------|-------|------------------------------------------------------------------------------------|
| [Bandai](https://archive.org/details/mame097_psp_r06.7z) | 29    |                                                                                    |
| [Capcom](https://archive.org/details/capcom.7z)          | 78    |                                                                                    |
| [Deco](https://archive.org/details/deco.7z)              | 228   |                                                                                    |
| [Irem](https://archive.org/details/irem.7z)              | 108   |                                                                                    |
| [Jaleco](https://archive.org/details/jaleco.7z)          | 86    |                                                                                    |
| [Konami](https://archive.org/details/konami.7z)          | 125   |                                                                                    |
| [Namco](https://archive.org/details/namco.7z)            | 93    |                                                                                    |
| [Nichibutsu](https://archive.org/details/nichibutsu.7z)  | 138   |                                                                                    |
| [Sega](https://archive.org/details/sega.7z_202104)       | 136   |                                                                                    |
| [SNK](https://archive.org/details/snk.7z_202104)         | 77    |                                                                                    |
| [Sunsoft](https://archive.org/details/sunsoft.7z)        | 8     | [link](https://github.com/PSP-Archive/pspMAME-0.97-TMK/blob/main/dats/Sunsoft.dat) |
| [Taito](https://archive.org/details/taito.7z)            | 175   |                                                                                    |
| [Taito 2](https://archive.org/details/taito2.7z)         | 246   |                                                                                    |
| [Technos](https://archive.org/details/technos.7z)        | 46    |                                                                                    |
| [Tecmo](https://archive.org/details/tecmo.7z)            | 36    |                                                                                    |
| [Universal](https://archive.org/details/universal.7z)    | 42    |                                                                                    |
| [Upl](https://archive.org/details/upl.7z)                | 33    |                                                                                    |

## Supported games

- [Full list of supported ROMs](supported.md)

Not everything on the list actually works.

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

Dat files are text files with information about games emulated with a specific version of MAME. There is no .dat file specific to the PSP port of MAME 0.97; the closest match would be the .dat for the mainstream 0.97 release ( [link](https://github.com/PSP-Archive/pspMAME-0.97-TMK/blob/main/dats/MAME%200.97.dat) ).

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
