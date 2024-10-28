#include QMK_KEYBOARD_H
//Swedish letters for US Eng os layout
#define KC_Å KC_LALT(KC_P)  // å
#define KC_Ä KC_LALT(KC_Q)  // ä
#define KC_Ö KC_LALT(KC_O)  // ö

enum custom_keycodes {          
  ALT_TAB = SAFE_RANGE,
};

// GACS is for those who reply to GASC’s bullet point 1 
// by saying that enabling a greater range of one-handed Ctrl+Letter 
// keyboard shortcuts is more important than a greater range 
// of one-handed capital letters you can type.

//GACS
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

// Shift should still be bound somewhere to type a series of capitalized letters
#define SFT_TAB LSFT_T(KC_TAB)
#define RALT_ENTER RALT_T(KC_ENT) // For RALT leader key in glaze etc. 

// To use in the Super Alt Tab
bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_Å,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,     KC_U,    KC_I,    KC_O,   KC_P,   KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_Ä,    GUI_A,   ALT_S,   CTL_D,   SFT_F,    KC_G,                         KC_H,   SFT_J,  CTL_K,  ALT_L,  GUI_SCLN,  KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_Ö,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, ALT_TAB,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SFT_TAB,   MO(1),  KC_SPC,   KC_BSPC , MO(2), RALT_ENTER
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_DEL,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______,
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
// Rotate OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}
#define FRAME_DURATION 333
uint32_t timer = 0;
uint8_t current_frame = 0;
static void render_animation(void){
    // Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1584)
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
//The code below implements the following behavior:
//Keys	                      |  Sends
//Backspace	                  | Backspace as usual
//Shift + Backspace	          |  Delete
//Both shift keys + Backspace | Shift + Delete
  switch (keycode) {
    case KC_BSPC: {
      static uint16_t registered_key = KC_NO;
      if (record->event.pressed) {  // On key press.
        const uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
        uint8_t shift_mods = (mods | get_oneshot_mods()) & MOD_MASK_SHIFT;
#else
        uint8_t shift_mods = mods & MOD_MASK_SHIFT;
#endif  // NO_ACTION_ONESHOT
        if (shift_mods) {  // At least one shift key is held.
          registered_key = KC_DEL;
          // If one shift is held, clear it from the mods. But if both
          // shifts are held, leave as is to send Shift + Del.
          if (shift_mods != MOD_MASK_SHIFT) {
#ifndef NO_ACTION_ONESHOT
            del_oneshot_mods(MOD_MASK_SHIFT);
#endif  // NO_ACTION_ONESHOT
            unregister_mods(MOD_MASK_SHIFT);
          }
        } else {
          registered_key = KC_BSPC;
        }

        register_code(registered_key);
        set_mods(mods);
      } else {  // On key release.
        unregister_code(registered_key);
      }
    } return false;


//This macro will register KC_LALT and tap KC_TAB, then wait for 1000ms. 
//If the key is tapped again, it will send another KC_TAB; 
//if there is no tap, KC_LALT will be unregistered, thus allowing you to cycle through windows.
  
  switch (keycode) { // This will do most of the grunt work with the keycodes.
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
      break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }


    // Other macros...
  }

  return true;
}