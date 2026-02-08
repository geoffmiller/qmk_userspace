// Copyright 2025 Geoff (@geoffmiller)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// TEMPORARY: Clear EEPROM on boot - remove after flashing once!
// #define CLEAR_EEPROM_ON_BOOT

/* Layer definitions */
enum layers {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _MOUSE
};

/* Custom keycodes */
enum custom_keycodes {
    DRG_SCRL = SAFE_RANGE,
};

/* Drag scroll state - using official Charybdis pattern */
static bool drag_scroll_enabled = false;
static int16_t scroll_buffer_x = 0;
static int16_t scroll_buffer_y = 0;

/* Zoom mode state - activated by Ctrl+Space */
static bool zoom_mode_active = false;
static bool ctrl_held = false;
static bool space_held = false;

/*
 * Drag scroll buffer threshold: emit scroll when movement exceeds this value.
 * Tuning: If scrolling feels too slow/fast, adjust this value:
 *   3-4  = more sensitive (faster scrolling)
 *   6    = default (matches official Charybdis with low DPI)
 *   32+  = less sensitive (needed for higher DPI sensors)
 */
#define CHARYBDIS_DRAGSCROLL_BUFFER_SIZE 130

/* Process drag scroll keypress */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Track Ctrl and Space for zoom mode
    if (keycode == KC_LCTL || keycode == KC_RCTL) {
        ctrl_held = record->event.pressed;
        zoom_mode_active = ctrl_held && space_held;
    }
    if (keycode == KC_SPC) {
        space_held = record->event.pressed;
        zoom_mode_active = ctrl_held && space_held;
    }
    
    // When zoom mode is active (Ctrl+Space held), remap 0 and -
    if (zoom_mode_active) {
        if (keycode == KC_0 && record->event.pressed) {
            // 0 = Zoom out (Ctrl+Minus)
            tap_code16(LCTL(KC_MINS));
            return false;
        }
        if (keycode == KC_MINS && record->event.pressed) {
            // - = Zoom in (Ctrl+Plus/Equal)
            tap_code16(LCTL(KC_EQL));
            return false;
        }
    }
    
    switch (keycode) {
        case DRG_SCRL:
            drag_scroll_enabled = record->event.pressed;
            // Reset buffers when starting/stopping drag scroll
            if (!drag_scroll_enabled) {
                scroll_buffer_x = 0;
                scroll_buffer_y = 0;
            }
            return false;
    }
    return true;
}

/* Convert mouse movement to scroll when drag scroll is active
 * Using the official Charybdis buffer-based approach:
 * - Accumulate movement in buffer
 * - When buffer exceeds threshold, emit ±1 scroll and reset buffer
 * - This provides consistent scroll increments regardless of speed
 */
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (drag_scroll_enabled) {
        // Accumulate movement into buffers
        scroll_buffer_x += mouse_report.x;
        scroll_buffer_y -= mouse_report.y;  // Invert for natural scrolling
        
        // Clear mouse movement (we're scrolling, not moving cursor)
        mouse_report.x = 0;
        mouse_report.y = 0;
        
        // Emit horizontal scroll when buffer exceeds threshold
        if (abs(scroll_buffer_x) > CHARYBDIS_DRAGSCROLL_BUFFER_SIZE) {
            mouse_report.h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        
        // Emit vertical scroll when buffer exceeds threshold
        if (abs(scroll_buffer_y) > CHARYBDIS_DRAGSCROLL_BUFFER_SIZE) {
            mouse_report.v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }
    return mouse_report;
}

/* Keyboard initialization */
void keyboard_post_init_user(void) {
// #ifdef CLEAR_EEPROM_ON_BOOT
//     eeconfig_init();  // Clear and reinitialize EEPROM
// #endif
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
#define LT_LOW_ESC  LT(_LOWER, KC_ESC)    // Hold: Lower layer, Tap: Escape
#define LT_RSE_ENT  LT(_RAISE, KC_ENT)    // Hold: Raise layer, Tap: Enter
#define MT_CTL_Z    MT(MOD_LCTL, KC_Z)    // Hold: Left Ctrl, Tap: Z
#define MT_SFT_QUOT MT(MOD_RSFT, KC_QUOT) // Hold: Right Shift, Tap: Quote


/* Keymaps */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer (QWERTY)
     * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │       │ 6 │ 7 │ 8 │ 9 │ 0 │ - │
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │Tab│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │ \ │
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │Sft│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │'Sf│
     * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
     * │Sft│CtZ│ X │ C │ V │ B │       │ N │ M │ , │ . │ / │Sft│
     * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
     *             ┌───┬───┬───┐       ┌───┬───┐
     *             │Gui│Spc│LwE│       │RsE│Bsp│
     *             └───┼───┼───┤       ├───┼───┘
     *                 │Clt│Atl│       │Alt│
     *                 └───┴───┘       └───┘
     */
    [_BASE] = LAYOUT(
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,   KC_5,           KC_6,       KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,           KC_Y,       KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,           KC_H,       KC_J,    KC_K,    KC_L,    KC_SCLN, MT_SFT_QUOT,
        KC_LSFT,  MT_CTL_Z,KC_X,    KC_C,    KC_V,   KC_B,           KC_N,       KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        XXXXXXX,  KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, LT_LOW_ESC,     LT_RSE_ENT, KC_BSPC, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /*
     * Lower Layer (Symbols, Navigation)
     * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
     * │ ~ │   │   │   │EEC│Rst│       │   │   │ ( │ ) │ = │ - │
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │CWT│   │   │   │   │   │       │   │   │ [ │ ] │ + │ _ │
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │Cap│   │   │   │   │   │       │   │   │ { │ } │   │   │
     * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │       │ ← │ ↓ │ ↑ │ → │   │   │
     * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
     *             ┌───┬───┬───┐       ┌───┬───┐
     *             │   │   │   │       │A-H│A-L│
     *             └───┼───┼───┤       ├───┼───┘
     *                 │   │   │       │A-K│
     *                 └───┴───┘       └───┘
     */
    [_LOWER] = LAYOUT(
        S(KC_GRV), _______, _______, _______, EE_CLR, QK_BOOT,       _______,   _______,    KC_LPRN,    KC_RPRN,  KC_EQL, KC_MINS,
        CW_TOGG,   _______, _______, _______, _______, _______,      _______,   _______,    KC_LBRC,    KC_RBRC,  KC_PLUS,  KC_UNDS,
        KC_CAPS,   _______, _______, _______, _______, _______,      _______,   _______,    KC_LCBR,    KC_RCBR,  _______,  _______,
        _______,   _______, _______, _______, _______, _______,      KC_LEFT,   KC_DOWN,    KC_UP,      KC_RGHT,  _______,  _______,
        XXXXXXX,   _______, _______, _______, _______,  _______,    LALT(KC_H), LALT(KC_L), LALT(KC_K), XXXXXXX,  XXXXXXX,  XXXXXXX
    ),

    /*
     * Raise Layer (F-Keys, Media)
     * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
     * │ ~ │   │   │   │   │   │       │Rst│EEC│   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │Cap│   │   │   │   │   │       │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │CWT│   │   │   │   │   │       │Wh↓│Wh↑│   │   │   │   │
     * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │       │ ← │ ↓ │ ↑ │ → │   │   │
     * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
     *             ┌───┬───┬───┐       ┌───┬───┐
     *             │Mut│   │   │       │   │   │
     *             └───┼───┼───┤       ├───┼───┘
     *                 │Vl+│Vl-│       │   │
     *                 └───┴───┘       └───┘
     */
    [_RAISE] = LAYOUT(
        S(KC_GRV), _______, _______, _______, _______, _______,      QK_BOOT, EE_CLR,  _______, _______, _______, _______,
        KC_CAPS,   _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        CW_TOGG,   _______, _______, _______, _______, _______,      MS_WHLD, MS_WHLU, _______, _______, _______, _______,
        _______,   _______, _______, _______, _______, _______,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        XXXXXXX,   KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,      _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /*
     * Mouse Layer (Auto-activated when trackball moves)
     * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │       │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │   │       │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │   │       │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │   │       │   │   │   │   │   │   │
     * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
     *             ┌───┬───┬───┐       ┌───┬───┐
     *             │Drg│Mb1│   │       │   │   │
     *             └───┼───┼───┤       ├───┼───┘
     *                 │Mb2│Mb3│       │   │       
     *                 └───┴───┘       └───┘     
     */
    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
        XXXXXXX, MS_BTN2, MS_BTN3, DRG_SCRL, MS_BTN1, _______,     _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX
    )
};
