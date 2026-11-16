// Internal imports
#include "custom.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case KC_CCED:
            if (!record->event.pressed){
                tap_code16(RALT(KC_COMM));
            }
            return false;
            
        case KC_ACUTE:
            if (!record->event.pressed){
                tap_code16(RALT(KC_QUOT));
            }
            return false;
        
        case KC_MICM: // Mute the microphone volume
            if (!record->event.pressed){
                tap_code16(KC_F20);
            }
            return false;

        case KC_MICU: // Up the microphone volume
            if (!record->event.pressed){
                tap_code16(KC_F14);
            }
            return false;

        case KC_MICD: // Down the microphone volume
            if (!record->event.pressed){
                tap_code16(KC_F15);
            }
            return false;
    }

    return true;
}