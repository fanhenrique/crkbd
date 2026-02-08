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
#define COMBO_MUST_TAP_PER_COMBO

// ### Layers ###
enum {
    TEXT,
    OS,
    NAVIGATE,
    SHORTCUT,
    NUMBERS_AND_MATH,
    SYMBOLS,
    FUNCTIONS_AND_NUMPAD,
    SPECIAL,
};

// ### Combos ### 
enum combo_events {
    COMBO_SEMICOLON,
};

// ### Custom keys ###
enum custom_keycodes {
    KC_CCED = SAFE_RANGE,
};

// ### Tap dance (double click) ###
enum tap_dance_events {
    TD_QUOT_DQUO,
    TD_DOT_COLON,
    TD_SLSH_QUES,
    TD_CCED,
};

const uint16_t PROGMEM semicolon_combo[] = { KC_COMM, KC_DOT, COMBO_END };
combo_t key_combos[] = {
    [COMBO_SEMICOLON] = COMBO(semicolon_combo, KC_SCLN),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    
    if (!record->event.pressed) return true;

    switch (keycode) {
        case KC_CCED:
            tap_code(KC_QUOT); // '
            tap_code(KC_C);    // c
            return false;
    }
    return true;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_QUOT_DQUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
    [TD_DOT_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COLN),
    [TD_SLSH_QUES] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
    [TD_CCED] = ACTION_TAP_DANCE_DOUBLE(KC_C, KC_CCED),
};

// //,--------------------------------------------------------------,    ,--------------------------------------------------------------,
//     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// //|--------+--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------+--------|
//     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// //|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
//     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// //'--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------'
//                                         XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX,
//                                     //'--------------------------'    '--------------------------'


// XXXX    XXXX    XXXX    XXXX    XXXX    XXXX    XXXX                   XXXX    XXXX    XXXX    XXXX    XXXX    XXXX    XXXX
// XXXX    XXXX    XXXX    XXXX    XXXX    XXXX    XXXX                   XXXX    XXXX    XXXX    XXXX    XXXX    XXXX    XXXX
// XXXX    XXXX    XXXX    XXXX    XXXX    XXXX                                   XXXX    XXXX    XXXX    XXXX    XXXX    XXXX
//                                 XXXX    XXXX    XXXX                   XXXX    XXXX    XXXX


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [TEXT] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------,    ,--------------------------------------------------------------,
        KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_CAPS,      KC_DEL,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------+--------|
        KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_LCTL,      KC_LALT,  KC_H,  KC_J,  KC_K,  KC_L, TD(TD_QUOT_DQUO), KC_DEL,
    //|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
        KC_LSFT,    KC_Z,    KC_X,TD(TD_CCED),  KC_V,    KC_B,              KC_N,KC_M,KC_COMM, TD(TD_DOT_COLON),TD(TD_SLSH_QUES),MO(SPECIAL),
    //'--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------'
                MO(SYMBOLS), LM(OS, MOD_LGUI), LT(SHORTCUT,KC_SPC),              KC_ENT, MO(NAVIGATE), MO(NUMBERS_AND_MATH)
    ),

    [OS] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------,    ,--------------------------------------------------------------,
        XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_VOLU,      XXXXXXX,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_VOLD,      XXXXXXX,    KC_H,  KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                           KC_N,    KC_M, KC_COMM,  KC_DOT, XXXXXXX, XXXXXXX,
    //'--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------'
                                        XXXXXXX, XXXXXXX, XXXXXXX,           KC_ENT, MO(NAVIGATE), XXXXXXX
    ),

    [NAVIGATE] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------,    ,--------------------------------------------------------------,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, KC_HOME,   KC_UP, KC_END, XXXXXXX,C(KC_BSPC),
    //|--------+--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT,XXXXXXX,C(KC_DEL), 
    //|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //'--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------'
                                            XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [SHORTCUT] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------,    ,--------------------------------------------------------------,
        XXXXXXX, C(KC_Q), C(KC_W), C(KC_E), C(KC_R), C(KC_T), XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, C(KC_A), C(KC_S), C(KC_D), C(KC_F), C(KC_G),C(KC_TAB),      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, C(KC_L), XXXXXXX, XXXXXXX, 
    //|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_B),                        XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //'--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------'
                                            XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [NUMBERS_AND_MATH] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------,    ,--------------------------------------------------------------,
        XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, XXXXXXX,      XXXXXXX,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,  KC_EQL, KC_PLUS, KC_ASTR,  KC_DOT, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_PERC, KC_MINS, KC_SLSH, KC_COMM, XXXXXXX,TO(TEXT),
    //'--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------'
                                        XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [SYMBOLS] = LAYOUT_split_3x6_3_ex2 (
    //,--------------------------------------------------------------,    ,--------------------------------------------------------------,
        XXXXXXX, XXXXXXX,   KC_AT, KC_CIRC, KC_TILD, KC_QUES, XXXXXXX,      XXXXXXX, KC_HASH, KC_LPRN, KC_RPRN,   KC_LT,   KC_GT,XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX,  KC_DLR, KC_COLN, KC_QUOT,  KC_GRV, XXXXXXX,      XXXXXXX, KC_UNDS, KC_LBRC, KC_RBRC, KC_DQUO, KC_QUOT, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, KC_AMPR, KC_PIPE, KC_EXLM,                        XXXXXXX,  KC_LCBR, KC_RCBR, KC_SLSH, KC_NUBS,TO(TEXT),
    //'--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------'
                                            XXXXXXX, XXXXXXX,  XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [FUNCTIONS_AND_NUMPAD] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------,    ,--------------------------------------------------------------,
        XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX, XXXXXXX,      XXXXXXX, KC_PPLS,   KC_P7,   KC_P8,   KC_P9, KC_PAST,XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX, XXXXXXX,      XXXXXXX, KC_PMNS,   KC_P4,   KC_P5,   KC_P6, KC_PSLS, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
        XXXXXXX,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,                        KC_PDOT,   KC_P1,   KC_P2,   KC_P3, KC_PEQL,TO(TEXT),
    //'--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------'
                                            XXXXXXX, XXXXXXX, KC_SPC,      KC_ENT, XXXXXXX,   KC_P0
    ),
   

    [SPECIAL] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------,    ,--------------------------------------------------------------,
       QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_REBOOT,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------+--------|
        RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
        RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,TO(TEXT),
    //'--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------'
                                            XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
        
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [TEXT] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [OS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [SHORTCUT] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [NAVIGATE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [NUMBERS_AND_MATH] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [SYMBOLS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [FUNCTIONS_AND_NUMPAD] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [SPECIAL] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
