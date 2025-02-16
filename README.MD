# PRBOOM-PLUS For PlayStation 2

![DOOM Screenshot taken on pcsx2](https://raw.githubusercontent.com/Wolf3s/prboom-plus/ps2/img/Doom-Screen.png "Raw level geometry")

This is a homebrew port of the game doom, targeting to PS2, Using PrBoom-Plus
as base.

This port uses the unofficial [PS2DEV SDK](https://github.com/ps2dev/ps2dev) and [SDL2](https://github.com/libsdl-org/SDL) to provide rendering,
input, audio and system functionalities for the id Tech 1 engine(Aka: DOOM1/2).

This project is mostly done however due to PS2SDK not being stable, there will be not a stable release.

My goal is try to make a definitive doom playstation 2 port replacing the [prboom libretro port](https://www.youtube.com/watch?v=tFaTfBz_iUw&pp=ygUVcHJib29tIHBzMiB2cyBwczJkb29t) and [ps2doom port](https://www.youtube.com/watch?v=y6BXCzrufCk&t=601s) using only PS2SDK libraries.

## How to run
Pick the prboom-plus executable that can be found on releases section,
unzip it then go to pcsx2 and execute the elf file or in real hardware transfer the folder unzipped to your pen-drive,
run wLaunchELF and find the game on `mass0:` or `mc0:` if you transfer it, then hit the .ELF file and done.

Note: 
hdd and mc support is not tested(mc support should be work fine by the way, but don´t hesitate to contact me). 

Mods:
You can put doom mods by putting them on `prboom-plus/autoload`
choose the folder for that mod(Example: `doom.wad/`) is based on and execute the .ELF file as usual.

# Supported games:
``` 
DOOM 1, DOOM 2, PLUTONIA, TNT, FREEDOOM, BFG-DOOM, BFG-DOOM 2, HACX, Chex Quest and REKKR

```

## Controls:
R1/L1: Change weapon
Triangle: Automap
Circle: Space/Open Doors
Square: CTRL/Shoot
DPad: Move
Left Stick: Move

## TODO
- Fix bad scaled screen
- Fix right stick which he´s being used by changing weapons

## License

DOOM was re-released as GPL, and it remains as such. New code written
for the PS2 port or any changes made to the original source code are also released under the
GNU General Public License version 2. See the accompanying [COPYING](prboom2/COPYING) file for details.

## Credits

* id Software for releasing and re-releasing the source code under GPL along with Boom team.
* Prboom and PrBoom-Plus teams for making big upgrades to original re-released source code
* [lukaszdk](https://github.com/lukaszdk) for the first ps2 doom port
* [Cosmito](https://github.com/cosmito) for updating the original ps2doom port with music
* [Dirsors](https://github.com/dirsors) for adding hdd support and more.
* [7z123dog](https://github.com/7dog123) for the idea for the port plus firstly making the prboom port using SDL1.2
* [fgsfdsfgs](https://github.com/fgsfdsfgs) for the inspiration for the SDL_GameController implementation.
