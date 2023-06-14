#include <gb/gb.h>
#include "player.c"
#include "font.c"


// Sprite Structure to hold sprite data
struct SPRITE {
	UBYTE spritemapids[9]; // array of sprite ids
	UBYTE startspriteid; // the first sprite id in the collection
	UINT8 x;
	UINT8 y;
	UINT8 width;
	UINT8 height;
	UBYTE graphic;
	UBYTE initialized;
};

void checkInput();
void drawhelloworld();
void setupSprites(struct SPRITE* sprites);

UINT8 x, y, lastspriteid;
struct SPRITE helloworldsprite;


void main() {
    x = 55;
    y = 75;

    SPRITES_8x8;
    set_sprite_data(0, 0, player);
    set_sprite_tile(0, 0);
    move_sprite(0, x, y);

    drawhelloworld();

    SHOW_SPRITES;



	// // main game loop
    // while(1) {
    //     checkInput();
    //     delay(10);
    // }
}

void drawhelloworld(){
	set_sprite_data(17, 35, FontOG); // load font data
    memcpy(helloworldsprite.spritemapids, helloworldspritemap, sizeof(helloworldspritemap)); // copy sprite map to sprite struct
    helloworldsprite.x = 50; // set x position
    helloworldsprite.y = 50; // set y position
    helloworldsprite.width = 28; // set width
    helloworldsprite.height = 16; // set height
    helloworldsprite.startspriteid = 18; // set start sprite id
    helloworldsprite.initialized = 1; // set initialized to true
    lastspriteid = 8;
}

void setupSprites(struct SPRITE* sprite) {
    UBYTE currentspriteid = sprite->startspriteid;
    for(UBYTE i = 0; i != sizeof(sprite->spritemapids); i++) {
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
