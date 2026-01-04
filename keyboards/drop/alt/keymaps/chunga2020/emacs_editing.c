// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

bool process_motion(uint16_t keycode, keyrecord_t *record,
                    layer_state_t accepted_layer_state, uint8_t required_mods,
                    uint16_t to_send)
{
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
