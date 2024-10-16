#pragma once
#include QMK_KEYBOARD_H

// Layers
enum layers {
    _BASE,
    _FIRST,
    _SECOND,
    _THIRD
};

// Alias for Keycodes
#define non    XXXXXXX // no actions
#define trnsp  KC_TRNS // transparent key
#define _A     KC_A
#define _B     KC_B
#define _C     KC_C
#define _D     KC_D
#define _E     KC_E
#define _F     KC_F
#define _G     KC_G
#define _H     KC_H
#define _I     KC_I
#define _J     KC_J
#define _K     KC_K
#define _L     KC_L
#define _M     KC_M
#define _N     KC_N
#define _O     KC_O
#define _P     KC_P
#define _Q     KC_Q
#define _R     KC_R
#define _S     KC_S
#define _T     KC_T
#define _U     KC_U
#define _V     KC_V
#define _W     KC_W
#define _X     KC_X
#define _Y     KC_Y
#define _Z     KC_Z
#define _ENTER KC_ENT
#define _SPACE KC_SPC
// You can add other keycodes similarly...
