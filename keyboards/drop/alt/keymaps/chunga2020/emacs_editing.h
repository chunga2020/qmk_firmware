// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef EMACS_EDITING_H
#define EMACS_EDITING_H

#include QMK_KEYBOARD_H

/*
 * Process an Emacs-style motion.
 *
 * Parameters:
 * keycode: the keycode, as for process_record_*
 * record: the key event record, as for process_record_*
 * accepted_layer_state: the layer state that must be active for this action to
 * trigger
 * required_mods: the modifier(s) that must be active to trigger this action
 * to_send: the keycode to send
 */
bool process_motion(uint16_t keycode, keyrecord_t *record,
                    layer_state_t accepted_layer_state, uint8_t required_mods,
                    uint16_t to_send);

#endif
