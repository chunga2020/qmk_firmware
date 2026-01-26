// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

bool process_motion(keyrecord_t *record, layer_state_t accepted_layer_state,
                    uint8_t required_mods, uint16_t to_send) {
    uint8_t mod_state = get_mods();

    if (layer_state_is(accepted_layer_state)) {
        if (record->event.pressed) {
            if (mod_state & required_mods) {
                del_mods(required_mods);
                tap_code16(to_send);

                set_mods(mod_state);
                return false;
            }
        }
    }
    return true;
}

bool send_sequence(keyrecord_t *record, layer_state_t accepted_layer_state,
                   uint8_t required_mods, uint16_t *sequence, uint8_t num_keys)
{
    uint8_t mod_state = get_mods();

    if (layer_state_is(accepted_layer_state)) {
        if (record->event.pressed) {
            if (mod_state & required_mods) {
                del_mods(required_mods);


                /* Tapping the first item of the sequence before the loop allows
                 * the loop to be written with the inter-key delay first.  This
                 * allows the loop to not have any ending lag. */
                tap_code16(sequence[0]);
                for (int i = 1; i < num_keys; i++) {
                    wait_ms(50); /* might need to adjust this interval */
                    tap_code16(sequence[i]);
                }

                set_mods(mod_state);
                return false;
            }
        }
    }
    return true;
}
