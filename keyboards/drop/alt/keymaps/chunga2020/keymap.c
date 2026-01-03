// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

/*
 * Layer explanation:
 * 0: base QWERTY layer
 * 1: F keys, RGB, volume, misc
 * 2: empty for Emacs-style editing anywhere
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_NO,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  TG(2),
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_NO,
        MO(1),   KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE,
        _______, RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______,
        _______, _______, RM_HUED, RM_SATD, RM_VALD, _______, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU,
        _______, _______, _______, _______, _______, QK_BOOT, NK_TOGG, _______, _______, _______, _______, _______,          KC_PGUP, KC_VOLD,
        _______, _______, _______,                            EE_CLR,                             KC_APP,  _______, KC_HOME, KC_PGDN, KC_END
    ),
    [2] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    )
};

/* From Linux: pressing both Shift keys together to get Caps Lock behavior;
 * might not need to use Caps Lock very often, hence the decision to get rid of
 * its dedicated key, but it *is* useful sometimes and better than having to do
 * hand dances with the Shift keys */
const uint16_t PROGMEM both_shifts_combo[] = {KC_LSFT, KC_RSFT, COMBO_END};
combo_t key_combos[] = {
    COMBO(both_shifts_combo, KC_CAPS)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
    case TG(2):
        if (IS_LAYER_OFF(2)) {
            rgb_matrix_set_color_all(0xff, 0x00, 0x00);
        } else {
            rgb_matrix_set_color_all(0xff, 0xff, 0xff);
        }
        return true;
    case RCTL(KC_B):
        if (record->event.pressed && IS_LAYER_ON(2)) {
            tap_code16(KC_LEFT);
        }
        return true;
    case RCTL(KC_F):
        tap_code16(KC_RIGHT);
        return true;
    default:
        return true;            /* process all other keycodes normally */
    }
}
