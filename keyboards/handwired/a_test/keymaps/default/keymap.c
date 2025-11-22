// Copyright 2025 Geoff (@geoffmiller)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
  // debug_enable=true;
  // debug_matrix=true;
}

// Required for #define POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
    // set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

// Caps Word: Both Shifts
void caps_word_set(bool active) {
    if (active) {
        // Do something when Caps Word activates
    } else {
        // Do something when Caps Word deactivates
    }
}

// Custom keycodes
#define LT1_ENT    LT(1,KC_ENT)          // held -> Layer 1,     tap -> Enter
#define LT2_ENT    LT(2,KC_ENT)          // held -> Layer 2,     tap -> Enter
#define LCTL_Z     MT(MOD_LCTL, KC_Z)    // held -> Left Control,tap -> Z
#define QUOT_SHFT  MT(MOD_RSFT, KC_QUOT) // held -> Right Shift, tap -> Quotes
// #define CAPS_SHFT  MT(MOD_LSFT, KC_CAPS) // held -> Left Shift,  tap -> Caps Lock

// or: lint_off 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,    KC_GRV,  KC_1,      KC_2,    KC_3,    KC_4,   KC_5,              KC_6,   KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_TAB,    KC_Q,    KC_W,      KC_E,    KC_R,    KC_T,    MS_BTN1,        MS_BTN1,  KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LSFT,   KC_A,    KC_S,      KC_D,    KC_F,    KC_G,     MS_BTN2,      KC_VOLU,   KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, QUOT_SHFT,
        KC_LSFT,   LCTL_Z,  KC_X,      KC_C,    KC_V,    KC_B,      KC_MUTE,    KC_VOLD,    KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        XXXXXXX,   XXXXXXX, KC_LALT,   KC_LGUI, KC_SPC,  LT1_ENT,  XXXXXXX,        XXXXXXX, LT2_ENT,  KC_BSPC, KC_LGUI, KC_RALT, XXXXXXX, XXXXXXX
    ),
    [1] = LAYOUT(
        TO(0),   _______, _______, _______, _______, _______, _______,      _______, _______, _______, KC_LPRN, KC_RPRN, _______,   TO(1), 
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______,
        KC_CAPS, _______, _______, _______, _______, _______,  _______,   _______,  _______, _______, KC_LCBR, KC_RCBR, _______, _______,
        KC_CAPS, _______, _______, _______, _______, _______,   QK_BOOT,  _______,   KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______,
        XXXXXXX, XXXXXXX, _______, _______, _______, _______, XXXXXXX,      XXXXXXX, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX,  XXXXXXX
    ),
    [2] = LAYOUT(
        TO(0),   _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  TO(2),
        _______, _______, _______, MS_UP,   _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
        KC_CAPS, MS_LEFT, MS_LEFT, MS_DOWN, MS_RGHT, MS_RGHT,  _______,    _______,  MS_WHLD, MS_WHLU, _______, _______, _______, _______,
        KC_CAPS, _______, _______, _______, _______, _______,   _______,  QK_BOOT,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
        XXXXXXX, XXXXXXX, _______, _______, _______, _______, XXXXXXX,      XXXXXXX, MS_BTN1, MS_BTN2, _______, _______, XXXXXXX, XXXXXXX
    ),
    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, MS_BTN1, MS_BTN1, MS_BTN1,      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, MS_BTN2,      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
        XXXXXXX, XXXXXXX, _______, _______, _______, _______, XXXXXXX,      XXXXXXX, _______, _______, _______, _______, XXXXXXX, XXXXXXX
    )
// or: lint_off 
};
