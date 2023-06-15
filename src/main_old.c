#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rand.h>
#include "player.c"
#include "font.c"
#include "background.c"


// Generic Sprite Structure to hold sprite data
struct SPRITE {
	UBYTE startspriteid; // the first sprite id in the collection
	UINT8 x; // x: horizontal coordinate of the top-left corner of the rectangular area in VRAM. (0-255)
	UINT8 y; // y: vertical coordinate of the top-left corner of the rectangular area in VRAM. (0-255)
	UINT8 width; // width: width of the the rectangular area in VRAM. 
	UINT8 height; // height: height of the the rectangular area in VRAM. 
	UBYTE graphic; // graphic: pointer to the tile numbers. The size of the tile numbers should be w*h. 
	UBYTE initialized;
    UBYTE length; // length of the sprite map
    UBYTE spritemapids[64]; // array of sprite ids
};


struct MENUITEMS {
    struct SPRITE menuItems[5];
};

void checkInput();
void drawMenuItems(UBYTE menuItems[][], UINT8 rows);
void drawComplexMenu();
void moveSprites(struct SPRITE* sprite, UINT8 width, UINT8 spacing);
void renderText(struct SPRITE* sprite, UINT8 spacing, UINT8 rows);
void setupSprites(struct SPRITE* sprites);

UINT8 x, y, lastspriteid, h, i, j, c;

void main() {
    x = 55;
    y = 75;

    SPRITES_8x8;
    fadeout();
    fadein();
    drawComplexMenu();
    SHOW_SPRITES;

    // // set_sprite_data(0, 0, player);
    // // set_sprite_tile(0, 0);
    // // move_sprite(0, x, y);

	// // main game loop
    // while(1) {
    //     checkInput();
    //     delay(10);
    // }
}

void drawComplexMenu(){
    UBYTE menuOptionOne[11]  = {35, 32, 39, 39, 42, 0, 50, 42, 45, 39, 31};
    //                          H   E   L   L   O   _    W   O   R   L   D
    UBYTE menuOptionTwo[11]  = {35, 32, 39, 39, 42, 0, 50, 42, 45, 39, 31};
    //                          H   E   L   L   O   _    W   O   R   L   D
    UBYTE menuOptionThree[11]  = {35, 32, 39, 39, 42, 0, 50, 42, 45, 39, 31};
    //                          H   E   L   L   O   _    W   O   R   L   D
    
    UBYTE menuItems[3][11];

    memcpy(menuItems[0], menuOptionOne, sizeof(menuOptionOne));
    memcpy(menuItems[1], menuOptionTwo, sizeof(menuOptionTwo));
    memcpy(menuItems[2], menuOptionThree, sizeof(menuOptionThree));

	drawMenuItems(menuItems, 3);
}

void drawMenuItems(UBYTE menuItems[5][64], UINT8 rows) {
    struct MENUITEMS inturnalMenuItems;
    set_sprite_data(17, 35, FontOG); // load font data
    for(i = 0; i < rows; i++) {
        struct SPRITE newMenuItem;
        inturnalMenuItems.menuItems[i] = newMenuItem;
        memcpy(inturnalMenuItems.menuItems[i].spritemapids, menuItems[i], 11); // copy sprite map to sprite struct
        inturnalMenuItems.menuItems[i].x = 8;
        inturnalMenuItems.menuItems[i].y = 110;
        inturnalMenuItems.menuItems[i].width = 24;
        inturnalMenuItems.menuItems[i].height = 16;
        inturnalMenuItems.menuItems[i].startspriteid = 18;
        inturnalMenuItems.menuItems[i].initialized = 1;
        inturnalMenuItems.menuItems[i].length = 11;
        setupSprites(&inturnalMenuItems.menuItems[i]); // setup sprites
        renderText(&inturnalMenuItems.menuItems[i], 1, i);
    }
}

void moveSprites(struct SPRITE* sprite, UINT8 width, UINT8 spacing) {
    UINT8 spacingaccumulatorx = 0;
	UINT8 spacingaccumulatory = 0;
    UINT8 row = 0;
    UINT8 col = 0;
    h = 0; // h needed to track of sprite maps that are not empty

    // if its not initialized, don't do anything
    if(sprite->initialized == 1) {
        for(j = 0; j <= width; j++){
            if(sprite->spritemapids[(row * 3 + j)] == 255 ) {
                spacingaccumulatory += spacing;
                row++;
                spacingaccumulatorx = 0; // reset for each line
                col = 0;
            }
            if(sprite->spritemapids[(row * 3 + j)] != 255){
                spacingaccumulatorx += spacing;
                move_sprite(sprite->startspriteid + h, sprite->x + (col*8) + spacingaccumulatorx, sprite->y + (row*8) + spacingaccumulatory);
                h++;
                col++;
            }
        }
    }
}

/**
 * renderText - moves sprites in a sprite map
 * sprite - pointer to sprite struct
 * spacing - spacing between sprites
**/
void renderText(struct SPRITE* sprite, UINT8 spacing, UINT8 rows) {
    UINT8 spacingaccumulatorx = 0;
	UINT8 spacingaccumulatory = 0;
    UINT8 row = rows;
    UINT8 col = 0;
    UINT8 currentX = 0;
    UINT8 currentY = 0;
    h = 0; // h needed to track of sprite maps that are not empty

    // if its not initialized, don't do anything
    if(sprite->initialized == 1) {
        for(j = 0; j <= sprite->length; j++) {
            if(sprite->spritemapids[(row * 3 + j)] == 255 ) {
                spacingaccumulatory += spacing;
                row++;
                spacingaccumulatorx = 0; // reset for each line
                col = 0;
                currentX = 0;
                currentY = 0;
            }
            if(sprite->spritemapids[(row * 3 + j)] != 255){
                spacingaccumulatorx += spacing;
                currentX = sprite->x + (col*8) + spacingaccumulatorx;
                currentY = sprite->y + (row*8) + spacingaccumulatory;
                move_sprite(sprite->startspriteid + h, currentX, currentY);
                h++;
                col++;
            }
        }
    }
}

void setupSprites(struct SPRITE* sprite) {
    // -> says "get a property from a pointer"
    UBYTE currentspriteid = sprite->startspriteid;
    for(i = 0; i != sprite->length; i++) {
        if(sprite->spritemapids[i]!=255){ // check if sprite map is empty (255) or not
            set_sprite_tile(currentspriteid,sprite->spritemapids[i]);
        }
        currentspriteid++;
    }
}

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


