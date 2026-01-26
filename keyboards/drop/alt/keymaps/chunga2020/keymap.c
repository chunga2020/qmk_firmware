// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "emacs_editing.h"

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

uint16_t fwd_del_word[] = {C(S(KC_RIGHT)), C(KC_BSPC)};
uint16_t del_to_eol[] = {S(KC_END), KC_BSPC};
uint16_t insert_newline_before[] = {KC_ENT, KC_LEFT};

/* binary representation of the active modifier keys */
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    mod_state = get_mods();

    switch (keycode) {
    case KC_F:
        if (mod_state & MOD_MASK_CTRL) {
            return process_motion(record, 2, MOD_MASK_CTRL, KC_RIGHT);
        }
        if (mod_state & MOD_MASK_ALT) {
            return process_motion(record, 2, MOD_MASK_ALT, C(KC_RGHT));
        }
        break;
    case KC_B:
        if (mod_state & MOD_MASK_CTRL) {
            return process_motion(record, 2, MOD_MASK_CTRL, KC_LEFT);
        }
        if (mod_state & MOD_MASK_ALT) {
            return process_motion(record, 2, MOD_MASK_ALT, C(KC_LEFT));
        }
        break;
    case KC_N:
        return process_motion(record, 2, MOD_MASK_CTRL, KC_DOWN);
    case KC_P:
        return process_motion(record, 2, MOD_MASK_CTRL, KC_UP);

    case KC_A:
        return process_motion(record, 2, MOD_MASK_CTRL, KC_HOME);
    case KC_E:
        return process_motion(record, 2, MOD_MASK_CTRL, KC_END);

    case KC_D:
        if (mod_state & MOD_MASK_CTRL) {
            return process_motion(record, 2, MOD_MASK_CTRL, KC_DEL);
        }
        if (mod_state & MOD_MASK_ALT) {
            return send_sequence(record, 2, MOD_MASK_ALT, fwd_del_word, 2);
        }
        break;
    case KC_K:
        return send_sequence(record, 2, MOD_MASK_CTRL, del_to_eol, 2);
    case KC_O:
        return send_sequence(record, 2, MOD_MASK_CTRL, insert_newline_before, 2);
    case KC_COMMA:
        return process_motion(record, 2, MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT),
                              C(KC_HOME));
    case KC_DOT:
        return process_motion(record, 2, MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT),
                              C(KC_END));
    }
    return true;
}
