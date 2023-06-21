#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rand.h>
#include "./Graphics/Font.h"
#include "./Graphics/Background.h"

// // GameState enum
// enum GameState {
//   START,
//   MENU,
//   MAP,
//   BATTLE,
//   GAMEOVER
// };

// // Scene struct
// struct Scene {
//   UBYTE spriteData[128];
//   UBYTE spriteMap[128];
//   UBYTE backgroundData[128];
//   UBYTE backgroundMap[128];
// };

// // GameState struct
// struct GameState {
//   enum GameState state;
//   struct Scene scenes[];
// };

UINT8 x, y, lastspriteid, h, i, j, c, menuOpen, mainMenuPosition, mapOpen;

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
  set_bkg_data(0, 181, RabbitSprites);
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
  set_bkg_data(0, 255, GardenSprites);
  set_bkg_tiles(0, 0, 20, 18, GardenMap);
  fadein();

  // wait for input from start button
  waitpad(J_START);
  fadeout();
  MenuScene();
}

void MainMenuRenderCursor() {
  // render cursor
  set_sprite_data(17, 35, FontOG); // load font data
  set_sprite_tile(0, 42); // set tile to cursor
  SHOW_SPRITES;
  DISPLAY_ON;
  if(mainMenuPosition < 1) {
    mainMenuPosition = 4;
  }
  if(mainMenuPosition > 4) {
    mainMenuPosition = 1;
  }
  switch (mainMenuPosition) {
    case 1:
      // start new game
      move_sprite(0, 26, 80);
      break;
    case 2:
      // help / controls
      move_sprite(0, 26, 100);
      break;
    case 3:
      // credits
      move_sprite(0, 26, 120);
      break;
    case 4:
      // exit
      move_sprite(0, 26, 140);
      break;
    default:
      // do nothing
      break;
  }
}

void MainMenuCheckMenuInput() {
  MainMenuRenderCursor();
  switch (joypad()) {
    case J_UP:
      // move cursor up
      mainMenuPosition--;
      break;
    case J_DOWN:
      // move cursor down
      mainMenuPosition++;
      break;
    case J_A:
      // select
      menuOpen = 0;
      MainMenuSelectMenuItem();
      break;
    default:
      // do nothing
      break;
  }
}

void MainMenuSelectMenuItem() {
  switch (mainMenuPosition) {
    case 1:
      // start new game
      printf("MenuScene - start new game");
      break;
    case 2:
      // help / controls
      printf("MenuScene - help / controls");
      break;
    case 3:
      // credits
      printf("MenuScene - credits");
      break;
    case 4:
      printf("MenuScene - exit");
      fadeout();
      exit(0);
      // exit
      break;
    default:
      // do nothing
      break;
  }
}




void MenuScene() {
  set_bkg_data(0, 83, MainMenuSprites);
  set_bkg_tiles(0, 0, 20, 18, MainMenuMap);
  fadein();

  UINT8 currentMenuPosition = 0;

  // build menu from sprites
  menuOpen = 1;

  // menu loop
  while(menuOpen) {
    MainMenuCheckMenuInput();
    delay(100);
  }
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
  while(mapOpen) {
    checkInput();
    delay(10);
    // Done processing, yield CPU and wait for start of next frame
    wait_vbl_done();
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
  menuOpen = 0;
  mapOpen = 0;
  mainMenuPosition = 1;
  SPRITES_8x8;
  fadeout();
  StartGame();
}