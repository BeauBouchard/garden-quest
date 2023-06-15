#define playerDataBank 0

extern const unsigned char player[];

//generical character structure: id, position, graphics
struct GameCharacter {
	UBYTE spritids[4]; // all characters use 4 sprites
	UINT8 x;
	UINT8 y;
	UINT8 width;
	UINT8 height;
};