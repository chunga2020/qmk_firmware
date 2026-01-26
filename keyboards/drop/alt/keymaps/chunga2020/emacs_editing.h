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
bool process_motion(keyrecord_t *record, layer_state_t accepted_layer_state,
                    uint8_t required_mods, uint16_t to_send);

/*
 * Send a sequence of keypresses from a single physical keypress.
 *
 * Parameters:
 * keycode: the keycode, as for process_record_*
 * record: the key event record, as for process_record_*
 * accepted_layer_state: the layer state that must be active for this sequence
 * to trigger
 * required_mods: the modifier(s) that must be active to trigger this sequence
 * sequence: the key sequence to send.  This is a list of keycodes that will be
 * sent one after another.
 * num_keys: the number of keys in the sequence, for loop termination
 */
bool send_sequence(keyrecord_t *record, layer_state_t accepted_layer_state,
                   uint8_t required_mods, uint16_t *sequence, uint8_t num_keys);
#endif
