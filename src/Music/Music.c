#include <stdarg.h>
#include "Music.h"

const UINT8 FX_REG_SIZES[] = {5, 4, 5, 4, 3};
const UINT16 FX_ADDRESS[] = {0xFF10, 0xFF16, 0xFF1A, 0xFF20, 0xFF24};

extern UINT8 music_mute_frames;

#ifdef MUSIC_DRIVER_HUGE
BYTE hUGE_paused = TRUE;
const hUGESong_t * hUGE_current_track;
UBYTE hUGE_current_track_bank;

void MusicCallback() __nonbanked {
    if (hUGE_paused) 
			return;

    UBYTE __save = _current_bank;
    SWITCH_ROM_MBC1(hUGE_current_track_bank);
    hUGE_dosound();
    SWITCH_ROM_MBC1(__save);
}

void hUGE_mute(UBYTE mute) {
    hUGE_mute_channel(HT_CH1, mute);
    hUGE_mute_channel(HT_CH2, mute);
    hUGE_mute_channel(HT_CH3, mute);
    hUGE_mute_channel(HT_CH4, mute);
}
#endif

#ifdef MUSIC_DRIVER_GBT
#include "BankManager.h"

void MusicCallback() __nonbanked {
	if(last_music)
	{
		gbt_update();
		REFRESH_BANK;
	}
}
#endif

void* last_music = 0;
UINT8 stop_music_on_new_state = 1;
void __PlayMusic(void* music, unsigned char bank, unsigned char loop) {
loop;
	if(music != last_music) {
		last_music = music;
#ifdef MUSIC_DRIVER_GBT
		gbt_play(music, bank, 7);
		gbt_loop(loop);
		REFRESH_BANK;
#endif
#ifdef MUSIC_DRIVER_HUGE
		NR52_REG = 0x80;
		NR51_REG = 0xFF;
		NR50_REG = 0x77;

		hUGE_paused = 1;
    hUGE_current_track = music; hUGE_current_track_bank = bank;
    UBYTE __save = _current_bank;
    SWITCH_ROM_MBC1(hUGE_current_track_bank);
    hUGE_init(hUGE_current_track);
    SWITCH_ROM_MBC1(__save);
		hUGE_paused = 0;
#endif
	}
}

void PlayFx(SOUND_CHANNEL channel, UINT8 mute_frames, ...) {
	UINT8 i;
	UINT8* reg = (UINT8*)FX_ADDRESS[channel];
	va_list list;

	if(channel != CHANNEL_5) {
		MUTE_CHANNEL(channel);
	}
	music_mute_frames = mute_frames;

	va_start(list, mute_frames);
	for(i = 0; i < FX_REG_SIZES[channel]; ++i, ++reg) {
		*reg = va_arg(list, INT16);
	}
	va_end(list);
}