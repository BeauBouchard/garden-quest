#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rand.h>
#include "player.c"
#include "font.c"


// Generic Sprite Structure to hold sprite data
struct SPRITE {
	UBYTE spritemapids[9]; // array of sprite ids
	UBYTE startspriteid; // the first sprite id in the collection
	UINT8 x; // x: horizontal coordinate of the top-left corner of the rectangular area in VRAM. (0-255)
	UINT8 y; // y: vertical coordinate of the top-left corner of the rectangular area in VRAM. (0-255)
	UINT8 width; // width: width of the the rectangular area in VRAM. 
	UINT8 height; // height: height of the the rectangular area in VRAM. 
	UBYTE graphic; // graphic: pointer to the tile numbers. The size of the tile numbers should be w*h. 
	UBYTE initialized;
};

void checkInput();
void drawMenu(UBYTE menuItems[]);
void drawhelloworld();
void drawHelloWorldNewFont();
void moveSprites(struct SPRITE* sprite, UINT8 width, UINT8 spacing);
void setupSprites(struct SPRITE* sprites);

UINT8 x, y, lastspriteid, h, i, j, c;
struct SPRITE helloworldsprite;

// hello world sprite
const UBYTE helloworldspritemap[11]     = {35, 32, 39, 39, 42, 50, 42, 45, 39, 31, 255};
const UBYTE font8x8_basicspritemap[10]  = {73, 70, 77, 77, 80, 88, 80, 83, 77, 69}; // above -38

// blank sprite
const unsigned char blankSprite[1] =
{
	0x00
};

void main() {
    x = 55;
    y = 75;

    SPRITES_8x8;
    drawhelloworld();
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

// UBYTE * stringToFont(char string[]) {
//     // using font8x8_basic
//     int length = sizeof(string);
//     UBYTE response[];

//     for (int i = 0; i < length; i++) {
//         // get the character
//         char c = string[i];

//         // get the index of the character in the font
//         int index = response;

//         // get the sprite data for the character
//         UBYTE spriteData[] = font8x8_basic[index];

//         // add spriteData to response array
//         // using font8x8_basicSpriteMap
//         // get the index of the character in the font
        

       

//         // copy the sprite data to the sprite map
//         //memcpy(spritemapids, spriteData, sizeof(spriteData));
//     }
// }



void drawhelloworld(){
    UBYTE testsprite[11]     = {35, 32, 39, 39, 42, 255, 50, 42, 45, 39, 31};
	drawMenu(testsprite);
}

void drawMenu(UBYTE menuItems[]) {
    struct SPRITE menusprite;
    int length = sizeof(menuItems);
    set_sprite_data(17, 35, FontOG); // load font data
    memcpy(menusprite.spritemapids, menuItems, 11); // copy sprite map to sprite struct

    // we want to render the menu to have a max of 4 rows, at 8 pixels each
    // there is a 32 char limit per a row using this font with 1 px space
    menusprite.x = 8; // set x position
    menusprite.y = 100; // set y position
    menusprite.width = 24; // set width
    menusprite.height = 16; // set height
    menusprite.startspriteid = 18; // 1-18 UI items, 19-51 numbers/letters
    menusprite.initialized = 1; // set initialized to true
    lastspriteid = 11;
    setupSprites(&menusprite); // setup sprites
    moveSprites(&menusprite,11,1);
}

void drawHelloWorldNewFont() {
    set_sprite_data(0, 127, font8x8_basic);
    memcpy(helloworldsprite.spritemapids, font8x8_basicspritemap, sizeof(font8x8_basicspritemap));
    helloworldsprite.x = 68; // set x position
    helloworldsprite.y = 40; // set y position
    helloworldsprite.width = 24; // set width
    helloworldsprite.height = 16; // set height
    helloworldsprite.startspriteid = 65;
    helloworldsprite.initialized = 1; // set initialized to true
    lastspriteid = 10;
    setupSprites(&helloworldsprite); // setup sprites
	moveSprites(&helloworldsprite,5,0);
}

/**
 * moveSprites - moves sprites in a sprite map
 * sprite - pointer to sprite struct
 * width - width of sprite map
 * spacing - spacing between sprites
**/
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

void setupSprites(struct SPRITE* sprite) {
    // -> says "get a property from a pointer"
    UBYTE currentspriteid = sprite->startspriteid;
    for(i = 0; i != sizeof(sprite->spritemapids); i++) {
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
