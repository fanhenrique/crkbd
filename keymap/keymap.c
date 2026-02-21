/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H


// ### Layers ###
enum {
    TEXT,
    OS,
    NAVIGATE,
    NUMBERS_SYMBOLS,
    FUNCTIONS_NUMPAD,
    SPECIAL,
};

// ### Combos ### 
enum combo_events {
    COMBO_SEMICOLON,
};

// // ### Custom keys ###
enum custom_keycodes {
    KC_CCED = SAFE_RANGE,
    KC_ACUTE,
};

// ### Tap dance (double click) ###
enum tap_dance_events {
    TD_DQUO_QUOT,
    TD_SLSH_QUES,
    TD_LSFT_CAPS,
};

const uint16_t PROGMEM semicolon_combo[] = { KC_COMM, KC_DOT, COMBO_END };
combo_t key_combos[] = {
    [COMBO_SEMICOLON] = COMBO(semicolon_combo, KC_SCLN),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!record->event.pressed) return true;

    switch (keycode) {
        case KC_CCED:
            tap_code16(RALT(KC_COMM));
            tap_code(KC_C);
            return false;
            
        case KC_ACUTE:
            tap_code16(RALT(KC_QUOT));
            return false;
    }

    return true;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_DQUO_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_DQUO, KC_QUOT),
    [TD_SLSH_QUES] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

// ----------------------------------------------------------------    ----------------------------------------------------------------
//   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// ----------------------------------------------------------------    ----------------------------------------------------------------
//   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// ----------------------------------------------------------------    ----------------------------------------------------------------
//   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// ----------------------------------------------------------------    ----------------------------------------------------------------
//                                       XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX,

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [TEXT] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_GRV,       KC_CIRC,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_TILD,     KC_ACUTE,  KC_H,  KC_J,  KC_K,  KC_L,TD(TD_DQUO_QUOT), KC_DEL,
    //----------------------------------------------------------------    ----------------------------------------------------------------
    TD(TD_LSFT_CAPS),LT(FUNCTIONS_NUMPAD,KC_Z),KC_X,KC_C,KC_V,KC_B,              KC_N,  KC_M, KC_COMM, KC_DOT,TD(TD_SLSH_QUES),MO(SPECIAL),
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                    KC_LCTL, LM(OS, MOD_LGUI), KC_SPC,      KC_ENT, MO(NAVIGATE), MO(NUMBERS_SYMBOLS)
    ),

    [OS] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
        XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_VOLU,      XXXXXXX,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_VOLD,      KC_MUTE,    KC_H, KC_LALT, KC_LSFT, KC_LCTL, KC_DQUO, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                           KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                        XXXXXXX, XXXXXXX, KC_SPC,           KC_ENT, MO(NAVIGATE), XXXXXXX
    ),

    [NAVIGATE] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, KC_HOME,   KC_UP, KC_END, XXXXXXX,  KC_BSPC,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        XXXXXXX, XXXXXXX, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX, XXXXXXX,      XXXXXXX,  KC_APP, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX,  KC_DEL, 
    //----------------------------------------------------------------    ----------------------------------------------------------------
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                           XXXXXXX, KC_LGUI,  KC_SPC,      KC_ENT, XXXXXXX, XXXXXXX
    ),

    [NUMBERS_SYMBOLS] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
         KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_DLR,      XXXXXXX,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_PIPE,   KC_AT, KC_COMM,  KC_DOT, KC_ASTR, KC_PLUS, KC_AMPR,      XXXXXXX, KC_HASH, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,  KC_DEL,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_COLN, KC_PERC, KC_EXLM, KC_CCED, KC_SLSH, KC_MINS,                        KC_UNDS, KC_LPRN, KC_RPRN,   KC_LT,   KC_GT, KC_NUBS,
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                            KC_EQL, XXXXXXX,  KC_SPC,      KC_ENT, XXXXXXX, XXXXXXX
    ),

    [FUNCTIONS_NUMPAD] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, XXXXXXX,      XXXXXXX, KC_PLUS,   KC_7,     KC_8,   KC_9,  KC_ASTR, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
          KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,      XXXXXXX, KC_MINS,   KC_4,     KC_5,   KC_6,  KC_SLSH, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_DOT,   KC_1,     KC_2,   KC_3,   KC_EQL, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                            XXXXXXX, XXXXXXX, KC_SPC,       KC_ENT, KC_COMM,  KC_0
    ),
   
    [SPECIAL] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
       QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_REBOOT,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                            XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [TEXT] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [OS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [NAVIGATE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [NUMBERS_SYMBOLS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [FUNCTIONS_NUMPAD] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [SPECIAL] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
