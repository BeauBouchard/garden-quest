#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rand.h>
#include "player.c"
#include "font.c"
#include "background.c"
#include "splash.c"

// GameState enum
enum GameState {
  START,
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
    default:
      break;
  }
}

void SplashScene() {
  // Load splash Scene
  set_bkg_data(0, 114, SplashSprites);
  set_bkg_tiles(0, 0, 20, 18, SplashMap);
  SHOW_BKG;
  DISPLAY_ON;
  // fade in
  fadein();
  // wait for input from start button
  waitpad(J_DOWN);
}

void MapScene() {
  // fade out
  
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
    case 1: // 1
      // Load splash Scene
      MapScene();
      break;
    case 2: // 2
      // Load game Scene
      BattleScene();
      break;
    case 3: // 3
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