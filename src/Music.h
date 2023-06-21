#ifndef MUSIC_H
#define MUSIC_H

#include <gb/gb.h>

extern void* last_music;
extern UINT8 stop_music_on_new_state;

void __PlayMusic(void* music, unsigned char bank, unsigned char loop);
void MusicCallback() __nonbanked;


	#include "gbt_player.h"
	#include "BankManager.h"

	#define INIT_MUSIC gbt_stop()
	#define DECLARE_MUSIC(SONG) extern const void __bank_ ## SONG ## _mod_Data; extern const unsigned char * SONG ## _mod_Data[]
	#define PlayMusic(SONG, LOOP) __PlayMusic(SONG ## _mod_Data, (uint8_t)&__bank_ ## SONG ## _mod_Data, LOOP)
	#define StopMusic gbt_stop(); last_music = 0

	#define MUTE_CHANNEL(CHANNEL) gbt_enable_channels(~(0xF & (1 << CHANNEL)))
	#define UNMUTE_ALL_CHANNELS gbt_enable_channels(0xF)


#endif

#ifndef SOUND_H
#define SOUND_H

typedef enum {
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4,
	CHANNEL_5
} SOUND_CHANNEL;

void PlayFx(SOUND_CHANNEL channel, UINT8 mute_frames, ...);

#endif