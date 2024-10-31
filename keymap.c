#include QMK_KEYBOARD_H

enum custom_keycodes {          
  ALT_TAB = SAFE_RANGE,
};

//GACS - for improved one-handed shortcuts
// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define CTL_D LCTL_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define CTL_K RCTL_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

#define SFT_TAB LSFT_T(KC_TAB)
#define RALT_ENTER RALT_T(KC_ENT)

bool is_alt_tab_active = false; 
uint16_t alt_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ALT_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,     KC_U,    KC_I,    KC_O,   KC_P,   KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  GUI_A,   ALT_S,   CTL_D,   SFT_F,    KC_G,                         KC_H,   SFT_J,  CTL_K,  ALT_L,  GUI_SCLN,  KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_LBRC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SFT_TAB,   MO(1),  KC_SPC,   KC_BSPC , MO(2), RALT_ENTER
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_DEL,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT, KC_PSCR, _______, KC_MPRV, KC_MPLY, KC_MNXT,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SFT_TAB, _______,  KC_SPC,     KC_BSPC,   MO(3), RALT_ENTER
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM,  KC_AT, KC_HASH,  KC_DLR, KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_TILD, KC_HASH, KC_PSLS, KC_LCBR, KC_LBRC,                      KC_RBRC, KC_RCBR, KC_BSLS, KC_MINS, KC_PPLS, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, KC_UNDS, KC_PEQL, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SFT_TAB,   MO(3),  KC_SPC,     KC_BSPC, _______, RALT_ENTER
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     QK_BOOT,  _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SFT_TAB, _______,  KC_SPC,     KC_BSPC, _______, RALT_ENTER
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
#include "images.h"
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}
#define FRAME_DURATION 250
uint32_t timer = 0;
uint8_t current_frame = 0;
static void render_animation(void){
    const char* epd_bitmap_allArray[5] = {
        sam1,
        sam2,
        sam3,
        sam4,
        sam5,
    };
    uint16_t frame_sizes[5] = {
        sizeof(sam1),
        sizeof(sam2),
        sizeof(sam3),
        sizeof(sam4),
        sizeof(sam5),
    };
    if (timer_elapsed(timer) > FRAME_DURATION) {
        timer = timer_read();
        current_frame = (current_frame + 1) % (sizeof(epd_bitmap_allArray) / sizeof(epd_bitmap_allArray[0]));
        oled_write_raw_P(epd_bitmap_allArray[current_frame], frame_sizes[current_frame]); 
    }
}

bool oled_task_user() {
    if(is_keyboard_master()){
        switch (get_highest_layer(layer_state)){
        case 0:
            oled_write_raw_P(im0, sizeof(im0));
            break;
        case 1:
            oled_write_raw_P(im1, sizeof(im1));
            break;
        case 2:
            oled_write_raw_P(im2, sizeof(im2));
            break;
        case 3:
            oled_write_raw_P(im3, sizeof(im3));
            break;
        }
    return false;
    }
    render_animation();
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case KC_BSPC: {
      if (record->event.pressed) {  
        const uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
        uint8_t shift_mods = (mods | get_oneshot_mods()) & MOD_MASK_SHIFT;
#else
        uint8_t shift_mods = mods & MOD_MASK_SHIFT;
#endif
        if (shift_mods == MOD_MASK_SHIFT) {
          tap_code(KC_DEL);
        }
        else {
          tap_code(KC_BSPC);
        }
      }
      return false;
    }

    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      return false;
  }
  return true;
}

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 600) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}
