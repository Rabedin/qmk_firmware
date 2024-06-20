#include QMK_KEYBOARD_H


enum custom_keycodes {
    DRAG_SCROLL = SAFE_RANGE,
};

// DRAG_SCROLL config
bool set_scrolling = false;

// Values for scroll speed
#define SCROLL_DIVISOR_H 8.0
#define SCROLL_DIVISOR_V 8.0

// Accumulated scroll value variables
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y /SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the x and y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

// Function to handle key events and enable/disable drag scrolling
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DRAG_SCROLL:
            // Toggle set_scrolling when DRAG_SCROLL key is pressed or released
            set_scrolling = record->event.pressed;
            break;
        default:
            break;
    }
    return true;
}



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G, KC_H, RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN),
        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        LT(3,KC_ESC), LT(1,KC_SPC), LT(4,KC_TAB), KC_BSPC, LT(2,KC_ENT)
    ),
	[1] = LAYOUT(
        KC_TRNS, KC_PGUP, KC_UP, KC_PGDN, KC_TRNS, KC_SLSH, KC_7, KC_8, KC_9, KC_MINS,
        KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_EQL, KC_4, KC_5, KC_6, KC_PLUS,
        KC_PSCR, KC_TRNS, KC_INS, KC_TRNS, KC_TRNS, KC_0, KC_1, KC_2, KC_3, KC_ASTR,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
	[2] = LAYOUT(
        KC_PERC, KC_AT, KC_LBRC, KC_RBRC, KC_BSLS, KC_TRNS, KC_TRNS, KC_CIRC, KC_TRNS, KC_TRNS,
        KC_HASH, KC_EXLM, KC_LPRN, KC_RPRN, KC_PIPE, KC_UNDS, KC_QUOT, KC_DQUO, KC_TILD, KC_GRV,
        KC_DLR, KC_TRNS, KC_LCBR, KC_RCBR, KC_AMPR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
	[3] = LAYOUT(
        RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, RGB_SPI, KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F11,
        RGB_M_K, RGB_M_B, RGB_M_P, RGB_TOG, QK_BOOT, KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F12,
        RGB_VAD, RGB_SAD, RGB_HUD, RGB_RMOD, RGB_SPD, KC_F10, KC_F1, KC_F2, KC_F3, KC_F13,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
	[4] = LAYOUT(
        KC_NO, KC_ACL0, KC_ACL1, KC_ACL2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, DB_TOGG, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_BTN3, DRAG_SCROLL,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_BTN3, DRAG_SCROLL,
        KC_NO, KC_NO, KC_NO, KC_BTN4, KC_BTN5
    )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)




