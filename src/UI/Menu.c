#include <gb/gb.h>
#include <stdio.h>

#include "Menu.h"
#include "../Graphics/Font.h"

UINT8 menuLength;
UINT8 cursorPosition;
bool menuOpen;
UBYTE menuItems[10][16];
UINT8 menuID;



bool isMenuOpen() {
  return menuOpen;
}

void MainMenuOpen() {
  menuLength = 4;
  cursorPosition = 1;
  menuOpen = true;
  menuItems[0] = "Start New Game";
  menuItems[1] = "Help / Controls";
  menuItems[2] = "Credits";
  menuItems[3] = "Exit";
}

void MainMenuSelectMenuItem() {

}

void PauseMenuOpen() {
  menuLength = 3;
  cursorPosition = 1;
  menuOpen = true;
  menuItems[0] = "Resume";
  menuItems[1] = "Help / Controls";
  menuItems[2] = "Exit";
}

void ExitMenu() {
  menuOpen = false;
}

void selectMenuItem() {
  switch(menuID) {
    case 1:
      // main menu
      MainMenuSelectMenuItem();
      break;
    default:
      // do nothing
      break;
  }

}





// Given the screen is 160x144 pixels, and the tile size is 8x8 pixels
// Then the screen is 20 tiles wide and 18 tiles tall
// Given we want to accomidate N menuitems and the menu items with each their own row
// and a blank space between each menu item, we can accomidate 10 menu items max, 2 min
void renderCursor() {

}

/**
 * @brief      On Loop checks for up or down movement and adjusts cursor position accordingly
 *            On A press, calls MainMenuSelectMenuItem()
 * 
*/
void checkMenuInput() {
  renderCursor();
  switch (joypad()) {
    case J_UP:
      // move cursor up
      cursorPosition--;
      break;
    case J_DOWN:
      // move cursor down
      cursorPosition++;
      break;
    case J_A:
      // select
      menuOpen = 0;
      selectMenuItem();
      break;
    default:
      // do nothing
      break;
  }
}

bool openMenu(UINT8 newMenuID) {
  menuID = newMenuID;
  switch(menuID) {
    case 1:
      // main menu
      MainMenuOpen();
      break;
    case 2:
      // pause menu
      PauseMenuOpen();
      break;
    default:
      // do nothing
      break;
  }
  return true;

}



void main() {
  menuID = 1;
}

