#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rand.h>
#include "player.c"
#include "font.c"
#include "background.c"
#include "splash.c"
#include "gbt_player.h"

extern const unsigned char * song_Data[];


// GameState enum
enum GameState {
  START,
  MENU,
  MAP,
  BATTLE,
  GAMEOVER
};

UINT8 x, y, lastspriteid, h, i, j, c;


void checkInput() {
  switch (joypad()) {
    case J_RIGHT:
      x++;
      move_sprite(0, x, y);
      break;
    case J_LEFT:
      x--;
      move_sprite(0, x, y);
      break;
    case J_UP:
      y--;
      move_sprite(0, x, y);
      break;
    case J_DOWN:
      y++;
      move_sprite(0, x, y);
      break;
    case J_A:
      // interact 1
      break;
    case J_B:
      // interact 2
      break;
    case J_START:
      // bring up game menu
      break;
    case J_SELECT:
      // mute?
      break;
    default:
      break;
  }
}

void SplashScene() {
  // Load splash Scene
  set_bkg_data(0, 126, RabbitSprites);
  set_bkg_tiles(0, 0, 20, 18, RabbitMap);

  SHOW_BKG;
  DISPLAY_ON;
  // fade in
  fadein();
  // wait for input from start button
  delay(1000);
  // fade out
  fadeout();
  // Load splash Scene
  set_bkg_data(0, 141, GardenSprites);
  set_bkg_tiles(0, 0, 20, 18, GardenMap);
  fadein();
    disable_interrupts();
    gbt_play(song_Data, 2, 7);
    gbt_loop(1);

    set_interrupts(VBL_IFLAG);
    enable_interrupts();

    while (1)
    {
        wait_vbl_done();

        // your game code here
        waitpad(J_START);
        fadeout();
        MenuScene();

        gbt_update(); // This will change to ROM bank 1.
    }
  // wait for input from start button
}

void MenuScene() {
  fadein();
  printf("MenuScene");
  // display menu
}

void MapScene() {
  // fade out
  printf("MapScene");
  
  // Load map Scene
  // set_bkg_data(0, 4, MazeSprites);
  // set_bkg_tiles(0, 0, 20, 18, MazeMap);
  // SHOW_BKG;
  // DISPLAY_ON;
  // fade in
  

  // map loop
  while(1) {
    checkInput();
    delay(10);
  }
}

void BattleScene() {
  // Load battle Scene

}

void GameOverScene() {
  // Load gameover Scene

}

// accepts gamestate enum
void RunGame(UINT8 gameState) {
  // Load game Scene
  switch(gameState) {
    case 0: // 0
      // Load splash Scene
      SplashScene();
      break;
    case 1: // 0
      // Load splash Scene
      SplashScene();
      break;
    case 2: // 1
      // Load splash Scene
      MapScene();
      break;
    case 3: // 2
      // Load game Scene
      BattleScene();
      break;
    case 4: // 3
      // Load gameover Scene
      GameOverScene();
      break;
  }
}

void StartGame() {
  // load game, gamestate 0 (start)
  RunGame(0);
}

void main() {
  SPRITES_8x8;
  fadeout();
  StartGame();
}