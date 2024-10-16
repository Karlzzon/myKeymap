#include "aliases.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                       KC_LGUI,   MO(_FIRST),  KC_SPC,     KC_ENT,   MO(_SECOND), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

    [_FIRST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  _non,     _non,   _non,    _non,    _non,                        KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, _non,     _non,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, _non,     _non,    _non,    _non,    _non,                        _non,     _non,    _non,    _non,   _non,     _non,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _trn,  KC_SPC,     KC_ENT,   MO(_THIRD), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_SECOND] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   _non,   _non,    _non,    _non,    _non,                        KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   _non,   _non,    _non,    _non,    _non,                        KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(_THIRD),  KC_SPC,     KC_ENT, _trn, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, _non,   _non,    _non,    _non,    _non,                         _non,    _non,    _non,    _non,    _non,   _non,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,  _non,    _non,                         _non,    _non,    _non,    _non,    _non,   _non,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,  _non,    _non,                         _non,    _non,    _non,    _non,    _non,   _non,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _trn,  KC_SPC,     KC_ENT, _trn, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
#include "images.h"
// Rotate OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}
#define FRAME_DURATION 333
uint32_t timer = 0;
uint8_t current_frame = 0;
static void render_animation(void){
    // Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1584)
    const char* epd_bitmap_allArray[3] = {
        epd_bitmap_ghost1,
        epd_bitmap_ghost2,
        epd_bitmap_ghost3
    };
    uint16_t frame_sizes[3] = {
        sizeof(epd_bitmap_ghost1),
        sizeof(epd_bitmap_ghost2),
        sizeof(epd_bitmap_ghost3)
    };
    // Run animation
    if (timer_elapsed(timer) > FRAME_DURATION) {
        // Set timer to updated time
        timer = timer_read();
        // Increment frame
        current_frame = (current_frame + 1) % (sizeof(epd_bitmap_allArray) / sizeof(epd_bitmap_allArray[0]));
        // Draw frame to OLED
        oled_write_raw_P(epd_bitmap_allArray[current_frame], frame_sizes[current_frame]); 
    }
}

// Draw to OLED 
bool oled_task_user() {
    if(is_keyboard_master()){
        switch (get_highest_layer(layer_state)){
        case _BASE:
            oled_write_raw_P(im0, sizeof(im0));
            break;
        case _FIRST:
            oled_write_raw_P(im1, sizeof(im1));
            break;
        case _SECOND:
            oled_write_raw_P(im2, sizeof(im2));
            break;
        case _THIRD:
            oled_write_raw_P(im3, sizeof(im3));
            break;
        }
    return false;
    }
    render_animation();
    return false;
}
#endif