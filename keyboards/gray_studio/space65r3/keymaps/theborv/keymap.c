// Copyright 2022 Yizhen Liu (@edwardslau)
// SPDX-License-Identifier: GPL-2.0

// include
#include QMK_KEYBOARD_H
#include "vial.h"
#include "keymap_eurkey.h"
// macros
enum custom_keycodes {
    KIPAS = QK_KB_0,
	POFF,
	RBOOT,
};

enum layers {
    _L0,
    _L1,
};

// disable swap keycodes
#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}
#endif

// disable swap modifiers
#ifndef MAGIC_ENABLE
uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif

#define TAP_TAPPING_TERM 230
void install_tap_dance_entries(void) {
    vial_tap_dance_entry_t td0 = { KC_SCLN, 
								   EU_AE, 		// hold: æ
								   S(EU_AE), 	// hold: Æ
								   KC_TRNS,
                                   TAP_TAPPING_TERM };
    vial_tap_dance_entry_t td1 = { KC_QUOT, 
                                   EU_OSTR, 	// hold: ø
								   S(EU_OSTR), 	// hold: Æ
								   KC_TRNS,
                                   TAP_TAPPING_TERM };
    vial_tap_dance_entry_t td2 = { KC_LBRC,
                                   EU_ARNG, 	// hold: å
								   S(EU_ARNG), 	// hold: Å
								   KC_TRNS,
                                   TAP_TAPPING_TERM };
    dynamic_keymap_set_tap_dance(0, &td0);
    dynamic_keymap_set_tap_dance(1, &td1);
	dynamic_keymap_set_tap_dance(2, &td2);
}

// send string to run batch files
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KIPAS: // run keepass
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(100) "keepasseirik" SS_DELAY(100) SS_TAP(X_ENT));
        } else {
        }
        break;
	case POFF: // shut down computer
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(100) "PowerShell-Poweroff" SS_DELAY(100) SS_TAP(X_ENT));
        } else {
        }
        break;
	case RBOOT: // reboot computer
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(100) "PowerShell-Reboot" SS_DELAY(100) SS_TAP(X_ENT));
        } else {
        }
        break;
    }
    return true;
};

  /* Qwerty
   * ,------------------------------------------------------------------------------------------------.
   * | ESC |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   BSPC    | HME  |
   * |------------------------------------------------------------------------------------------------+
   * |  TAB  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \    | PGUP |
   * |------------------------------------------------------------------------------------------------+
   * |   CAPS  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    | PGDN |
   * |------------------------------------------------------------------------------------------------+
   * |   Shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | ?/ |   Shift   |  Up  | DEL  |
   * |------------------------------------------------------------------------------------------------+
   * | Ctrl |  Win  |  Alt |                 Space            |Altgr |  Fn  |    | Left | Down |Right |
   * `----------------------------------------------------------------------'    '--------------------'
   */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT(
		QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_HOME,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    TD(2),   KC_RBRC, KC_BSLS, KC_PGUP,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    TD(0),   TD(1),   KC_ENT,           KC_PGDN,
		KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_DEL,
		KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(_L1),                     KC_LEFT, KC_DOWN, KC_RGHT
	),
    [_L1] = LAYOUT(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  QK_BOOT, QK_BOOT, KC_END,
		_______,          UG_TOGG, UG_NEXT, UG_HUEU, UG_SATU, UG_VALU, UG_SPDU, _______, _______, _______, KIPAS,   _______, QK_RBT,  EE_CLR,  KC_PSCR,
		_______,          _______, _______, UG_HUED, UG_SATD, UG_VALD, UG_SPDD, _______, _______, _______, _______, _______, _______,          KC_SCRL,
		_______, _______, _______, _______, _______, _______, NK_OFF,  NK_ON,   _______, _______, _______, _______, _______,          KC_VOLU, KC_PAUS,
		POFF,    _______, RBOOT,                              _______,                            _______, _______,          _______, KC_VOLD, KC_INS
	)
};

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,2, HSV_WHITE}
);  

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer
);

void keyboard_post_init_user(void) {
	// Call the post init code.
    rgblight_layers = my_rgb_layers;
	// Call the post init code.
	#ifdef TAP_DANCE_ENABLE
	install_tap_dance_entries();
	#endif
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}