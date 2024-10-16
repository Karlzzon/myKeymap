#pragma once
#include QMK_KEYBOARD_H

// Layers
enum layers {
    _BASE,
    _FIRST,
    _SECOND,
    _THIRD
};

// Specials
#define _non    XXXXXXX // no actions
#define _trn    KC_TRNS // transparent key
