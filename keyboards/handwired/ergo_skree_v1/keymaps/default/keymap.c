// Copyright 2025 Geoff (@geoffmiller)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <math.h>

/* Layer definitions */
enum layers {
    _BASE = 0,
    _LAYER2,
    _LAYER3,
    _MOUSE
};

/* Custom keycodes */
enum custom_keycodes {
    DRG_SCRL = SAFE_RANGE,
};

/* Drag scroll state */
static bool drag_scroll_enabled = false;
static int16_t scroll_buffer_x = 0;
static int16_t scroll_buffer_y = 0;
static int16_t left_scroll_buffer_x = 0;
static int16_t left_scroll_buffer_y = 0;

#define DRAGSCROLL_BUFFER_SIZE 130

/* Process drag scroll keypress */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DRG_SCRL:
            drag_scroll_enabled = record->event.pressed;
            if (!drag_scroll_enabled) {
                scroll_buffer_x = 0;
                scroll_buffer_y = 0;
            }
            return false;
    }
    return true;
}

/* Rotate point by angle (in degrees) */
static void rotate_point(int16_t* x, int16_t* y, int16_t angle) {
    float rad = angle * 3.14159265f / 180.0f;
    float cos_a = cosf(rad);
    float sin_a = sinf(rad);
    int16_t new_x = (int16_t)((*x) * cos_a - (*y) * sin_a);
    int16_t new_y = (int16_t)((*x) * sin_a + (*y) * cos_a);
    *x = new_x;
    *y = new_y;
}

/* Combined pointing device handler for dual trackballs */
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    // Apply rotation for left side (-80 degrees)
    rotate_point(&left_report.x, &left_report.y, -80);
    // Invert Y axis for left (different orientation than right)
    left_report.y = -left_report.y;
    
    // Left trackball is always scroll-only
    left_scroll_buffer_x += left_report.x;
    left_scroll_buffer_y -= left_report.y;
    
    // Clear left movement (it only scrolls)
    left_report.x = 0;
    left_report.y = 0;
    
    if (abs(left_scroll_buffer_x) > DRAGSCROLL_BUFFER_SIZE) {
        left_report.h = left_scroll_buffer_x > 0 ? 1 : -1;
        left_scroll_buffer_x = 0;
    }
    
    if (abs(left_scroll_buffer_y) > DRAGSCROLL_BUFFER_SIZE) {
        left_report.v = left_scroll_buffer_y > 0 ? 1 : -1;
        left_scroll_buffer_y = 0;
    }
    
    // Apply rotation for right side (-100 degrees)
    rotate_point(&right_report.x, &right_report.y, -100);
    // Invert X axis for right
    right_report.x = -right_report.x;
    
    // Combine the reports using QMK's function
    report_mouse_t combined = pointing_device_combine_reports(left_report, right_report);
    
    // Apply drag scroll to right trackball if enabled (via DRG_SCRL key)
    if (drag_scroll_enabled) {
        scroll_buffer_x += combined.x;
        scroll_buffer_y -= combined.y;
        
        combined.x = 0;
        combined.y = 0;
        
        if (abs(scroll_buffer_x) > DRAGSCROLL_BUFFER_SIZE) {
            combined.h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        
        if (abs(scroll_buffer_y) > DRAGSCROLL_BUFFER_SIZE) {
            combined.v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }
    
    return combined;
}

/* Keyboard initialization */
void keyboard_post_init_user(void) {
    // Enable debug output if needed
    // debug_enable = true;
    // debug_matrix = true;
}

/* Auto mouse layer setup */
void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
    set_auto_mouse_enable(true);
}

/* Mod-tap and layer-tap shortcuts */
#define LT_2_ESC  LT(_LAYER2, KC_ESC)    // Hold: Lower layer, Tap: Escape
#define LT_3_ENT  LT(_LAYER3, KC_ENT)    // Hold: Raise layer, Tap: Enter
#define MT_CTL_Z    MT(MOD_LCTL, KC_Z)    // Hold: Left Ctrl, Tap: Z

/* Keymaps - Updated to match new wiring layout */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * Base Layer (QWERTY)
     *
     * Left side:
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │  `  │  1  │  2  │  3  │  4  │  5  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │Caps │  Q  │  W  │  E  │  R  │  T  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │ Tab │  A  │  S  │  D  │  F  │  G  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │Shift│  Z  │  X  │  C  │  V  │  B  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │MO(2)│  ←  │  →  │ XXX │ XXX │Space│
     * ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │ End │Home │LWin │  ←  │  ↑  │  [  │  (thumb row)
     * └─────┴─────┴─────┴─────┴─────┴─────┘
     *
     * Right side:
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │  6  │  7  │  8  │  9  │  0  │  -  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │  Y  │  U  │  I  │  O  │  P  │  \  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │  H  │  J  │  K  │  L  │  ;  │  '  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │  N  │  M  │  ,  │  .  │  /  │RSft │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │Bksp │ XXX │ XXX │  ↓  │  ↑  │MO(3)│
     * ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │PgDn │PgUp │RAlt │  →  │  ↑  │  ]  │  (thumb row)
     * └─────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_BASE] = LAYOUT(
        KC_EQL,   KC_1,     KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_MINS,
        KC_CAPS,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,    KC_BSLS,
        KC_TAB,   KC_A,     KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN, KC_QUOT,
        KC_LSFT,  MT_CTL_Z, KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT,
        MO(2),    KC_LEFT,  KC_RGHT, _______, _______, KC_SPC,       KC_BSPC, _______, _______, KC_DOWN,  KC_UP,   MO(3),
        KC_LALT,  LT_2_ESC, KC_LGUI, KC_LEFT, KC_UP,   KC_LBRC,      KC_RALT, LT_3_ENT, KC_RGUI, KC_RGHT, KC_DOWN, KC_RBRC
    ),

    /*
     * Layer 2 (QK_BOOT on 1, EE_CLR on 2)
     */
    [_LAYER2] = LAYOUT(
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, EE_CLR,  QK_BOOT,      _______, _______, _______, _______, _______, _______
    ),

    /*
     * Layer 3 (QK_BOOT on 7, EE_CLR on 8 for right side)
     */
    [_LAYER3] = LAYOUT(
        _______, _______, _______, _______, _______, _______,      _______, _______, _______,  _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, EE_CLR,  QK_BOOT
    ),

    /*
     * Mouse Layer (Auto-activated when trackball moves)
     */
    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, DRG_SCRL,     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, MS_BTN1, MS_BTN2, S(MS_BTN3),   _______, _______, _______, _______, _______, _______
    )
};