# PRBOOM-PLUS For PlayStation 2

This is a homebrew port of the game doom, targeting the PS2 Console, Using PrBoom-Plus
as base.

This port uses the unofficial [PS2DEV SDK](https://github.com/ps2dev) and SDL2 to provide rendering,
input, audio and system services for the id Tech 1 engine(Aka: DOOM1/2).

This project is still in W.I.P, However Joysticks and Little changes on SDL2 is working
on pcsx2.

My goal is to make a definitive doom playstation 2 port replacing the [prboom libretro port](https://www.youtube.com/watch?v=tFaTfBz_iUw&pp=ygUVcHJib29tIHBzMiB2cyBwczJkb29t) and [ps2doom port](https://www.youtube.com/watch?v=y6BXCzrufCk&t=601s) using only PS2SDK libraries.

## TODO

- Optimize to ensure smooth gameplay
- Fix SDL_GameController on Real Hardware
- Add L3 and R3 for movements

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
