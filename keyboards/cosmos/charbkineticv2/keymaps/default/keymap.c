#include QMK_KEYBOARD_H

#include "rgblight.h"
#include <math.h>

#define RELAY_PIN 11
#define RELAY_ON 0
#define RELAY_OFF 1

/* Layer definitions */
enum layers {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _MOUSE,
};

/* Custom keycodes */
enum custom_keycodes {
    DRG_SCRL = SAFE_RANGE,
};

#define _______ KC_TRNS

/* Drag scroll state */
static bool drag_scroll_enabled = false;
static int16_t scroll_buffer_x = 0;
static int16_t scroll_buffer_y = 0;

#define DRAGSCROLL_BUFFER_SIZE 130

/* Empty passthrough layer template */
#define LAYER_EMPTY LAYOUT( \
    _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, \
    _______ \
)

bool last_led_state;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer
     * Matches your visual layout including thumb cluster labels.
     */
    [_BASE] = LAYOUT(
        KC_ESCAPE, KC_1,    KC_2,    KC_3,    KC_4,        KC_5,
        KC_6,      KC_7,    KC_8,    KC_9,    KC_0,        KC_MINUS,

        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,        KC_T,
        KC_Y,      KC_U,    KC_I,    KC_O,    KC_P,        KC_CAPS,

        KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,        KC_G,
        KC_H,      KC_J,    KC_K,    KC_L,    KC_SEMICOLON, KC_RSFT,

        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,        KC_B,
        KC_N,      KC_M,    KC_COMMA, KC_DOT, KC_SLASH,    KC_RSFT,

        KC_SPACE,  KC_RCTL, KC_ESCAPE,
        KC_ENTER,  KC_LCTL, KC_BACKSPACE,
        KC_LGUI
    ),

    [_LOWER] = LAYER_EMPTY,
    [_RAISE] = LAYER_EMPTY,
    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,

        DRG_SCRL, _______, _______,
        _______, _______, _______,
        _______
    ),
};


void keyboard_post_init_user(void) {
  last_led_state = rgblight_get_val() > 0 ? RELAY_ON : RELAY_OFF;
  gpio_set_pin_output(RELAY_PIN);
  gpio_write_pin(RELAY_PIN, last_led_state);
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
    set_auto_mouse_enable(true);
}

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

/* Drag scroll handler for right trackball */
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (drag_scroll_enabled) {
        scroll_buffer_x += mouse_report.x;
        scroll_buffer_y -= mouse_report.y;
        
        mouse_report.x = 0;
        mouse_report.y = 0;
        
        if (abs(scroll_buffer_x) > DRAGSCROLL_BUFFER_SIZE) {
            mouse_report.h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        
        if (abs(scroll_buffer_y) > DRAGSCROLL_BUFFER_SIZE) {
            mouse_report.v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }
    
    return mouse_report;
}

void housekeeping_task_user(void) {
  bool leds_on = rgblight_get_val() > 0 ? RELAY_ON : RELAY_OFF;
  if (leds_on != last_led_state) {
    last_led_state = leds_on;
    gpio_write_pin(RELAY_PIN, leds_on);
  }
}
