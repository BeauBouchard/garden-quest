;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler 
; Version 4.2.2 #13350 (Linux)
;--------------------------------------------------------
	.module background
	.optsdcc -msm83
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _BackgroundData
	.globl _fadeout
	.globl _fadein
	.globl _wait_vbl_done
	.globl _delay
	.globl _i
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_i::
	.ds 1
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;background.c:6: void fadein(){
;	---------------------------------
; Function fadein
; ---------------------------------
_fadein::
;background.c:7: wait_vbl_done();
	call	_wait_vbl_done
;background.c:10: for(i=1; i != 4; i++){
	ld	hl, #_i
	ld	(hl), #0x01
00106$:
;background.c:11: switch(i){
	ld	a, (#_i)
	dec	a
	jr	Z, 00101$
	ld	a, (#_i)
	sub	a, #0x02
	jr	Z, 00102$
	ld	a, (#_i)
	sub	a, #0x03
	jr	Z, 00103$
	jr	00104$
;background.c:12: case 1:
00101$:
;background.c:13: BGP_REG = 0xFE;
	ld	a, #0xfe
	ldh	(_BGP_REG + 0), a
;background.c:14: break;
	jr	00104$
;background.c:15: case 2:
00102$:
;background.c:16: BGP_REG = 0xF9;
	ld	a, #0xf9
	ldh	(_BGP_REG + 0), a
;background.c:17: break;
	jr	00104$
;background.c:18: case 3:
00103$:
;background.c:19: BGP_REG = 0xE4;
	ld	a, #0xe4
	ldh	(_BGP_REG + 0), a
;background.c:21: }
00104$:
;background.c:22: delay(100);
	ld	de, #0x0064
	call	_delay
;background.c:10: for(i=1; i != 4; i++){
	ld	hl, #_i
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x04
	jr	NZ, 00106$
;background.c:24: }
	ret
;background.c:26: void fadeout(){
;	---------------------------------
; Function fadeout
; ---------------------------------
_fadeout::
;background.c:27: wait_vbl_done();	
	call	_wait_vbl_done
;background.c:28: for(i = 0; i != 4; i++){
	ld	hl, #_i
	ld	(hl), #0x00
00107$:
;background.c:29: switch(i){
	ld	a, (#_i)
	or	a, a
	jr	Z, 00101$
	ld	a, (#_i)
	dec	a
	jr	Z, 00102$
	ld	a, (#_i)
	sub	a, #0x02
	jr	Z, 00103$
	ld	a, (#_i)
	sub	a, #0x03
	jr	Z, 00104$
	jr	00105$
;background.c:30: case 0:
00101$:
;background.c:31: BGP_REG = 0xE4;
	ld	a, #0xe4
	ldh	(_BGP_REG + 0), a
;background.c:32: break;
	jr	00105$
;background.c:33: case 1:
00102$:
;background.c:34: BGP_REG = 0xF9;
	ld	a, #0xf9
	ldh	(_BGP_REG + 0), a
;background.c:35: break;
	jr	00105$
;background.c:36: case 2:
00103$:
;background.c:37: BGP_REG = 0xFE;
	ld	a, #0xfe
	ldh	(_BGP_REG + 0), a
;background.c:38: break;
	jr	00105$
;background.c:39: case 3:
00104$:
;background.c:40: BGP_REG = 0xFF;
	ld	a, #0xff
	ldh	(_BGP_REG + 0), a
;background.c:42: }
00105$:
;background.c:43: delay(100);
	ld	de, #0x0064
	call	_delay
;background.c:28: for(i = 0; i != 4; i++){
	ld	hl, #_i
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x04
	jr	NZ, 00107$
;background.c:45: }
	ret
	.area _CODE
_BackgroundData:
	.db #0x00	; 0
	.area _INITIALIZER
	.area _CABS (ABS)
