# garden-quest
Garden Quest - A Game Boy game made with [GBDK](https://github.com/gbdk-2020/gbdk-2020/) and [ZGB](https://github.com/Zal0/ZGB). 



### Build Instructions

Create `SDCCDIR` environment variable, that points into the folder where you installed SDCC, `SDCCDIR=/usr` in most cases. 

Compile [GBDK](https://github.com/gbdk-2020/gbdk-2020/) 

Compile [ZGB](https://github.com/Zal0/ZGB) and set `ZGB_PATH`



### Running

To run the game rom you will need to use a Game Boy Advance emulator ([mGBA](https://mgba.io/) for example)

```bash
 cd your_game_build_directory
 mgba game/game.gba
```

