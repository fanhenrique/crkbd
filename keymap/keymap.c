#include QMK_KEYBOARD_H

#include "raw_hid.h"

// Internal imports
#include "layers.h"
#include "tap_dance/tap_dance.h"
#include "features/combos.h"
#include "features/custom.h"

// ----------------------------------------------------------------    ----------------------------------------------------------------
//   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// ----------------------------------------------------------------    ----------------------------------------------------------------
//   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// ----------------------------------------------------------------    ----------------------------------------------------------------
//   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// ----------------------------------------------------------------    ----------------------------------------------------------------
//                                       XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX,


layer_state_t layer_state_set_user(layer_state_t state)
{
    uint8_t layer = get_highest_layer(state);

    uint8_t data[32] = {0};

    data[24] = 0x90;
    data[25] = layer;

    raw_hid_send(data, 32);

    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_CIRC,       KC_GRV, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_TILD,     KC_ACUTE, KC_H,   KC_J,   KC_K,   KC_L, TD(TDK_DQUO_QUOT), KC_DEL,
    //----------------------------------------------------------------    ----------------------------------------------------------------
    TD(TDK_LSFT_CAPS), KC_Z, KC_X,   KC_C,    KC_V,    KC_B,                   KC_N, KC_M, KC_COMM, KC_DOT,  TD(TDK_SLSH_QUES), KC_LALT,
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                    KC_LCTL, LM(OS, MOD_LGUI), KC_SPC,      KC_ENT, TD(TDL_NAVIGATE), TD(TDL_NUMBERS_SYMBOLS)
    ),

    [OS] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_VOLU,       KC_MICU,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_TAB, XXXXXXX, XXXXXXX,    KC_D,    KC_F, KC_MUTE, KC_VOLD,       KC_MICD, KC_MICM, KC_LCTL, KC_LSFT, KC_LALT, XXXXXXX, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
       KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_B, XXXXXXX, XXXXXXX,XXXXXXX,TD(TDL_MOUSE),TD(TDL_FUNCTIONS_NUMPAD),TD(TDL_SPECIAL),
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                             KC_LCTL, XXXXXXX, KC_SPC,      KC_ENT, TD(TDL_NAVIGATE), MO(OPERATIONS)
    ),

    [OPERATIONS] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, XXXXXXX,      XXXXXXX,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, XXXXXXX,      XXXXXXX,    KC_H,    KC_J,    KC_K,    KC_L, KC_DQUO,  KC_DEL,
    //----------------------------------------------------------------    ----------------------------------------------------------------
       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                           KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                            KC_LCTL, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [NAVIGATE] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      TD(TDL_BASE), XXXXXXX, KC_HOME,   KC_UP, KC_END, XXXXXXX,  KC_BSPC,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_TAB, XXXXXXX, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX, XXXXXXX,      XXXXXXX, KC_PGUP, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX,  KC_DEL, 
    //----------------------------------------------------------------    ----------------------------------------------------------------
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_PGDN,  KC_APP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                           XXXXXXX, KC_LGUI,  KC_SPC,      KC_ENT, TD(TDL_NAVIGATE), XXXXXXX
    ),

    [NUMBERS_SYMBOLS] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
         KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,   KC_5,  KC_EXLM,    TD(TDL_BASE),  KC_6,   KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
    //----------------------------------------------------------------    ----------------------------------------------------------------
         KC_TAB,   KC_AT, KC_ASTR, KC_MINS, KC_PLUS, KC_COLN, KC_AMPR,      KC_COMM,  KC_DLR, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,  KC_DEL,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        KC_PERC, KC_HASH, KC_SLSH, KC_CCED, KC_UNDS,  KC_DOT,                        KC_PIPE, KC_LPRN, KC_RPRN,   KC_LT,   KC_GT, KC_NUBS,
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                            KC_EQL, XXXXXXX,  KC_SPC,      KC_ENT, XXXXXXX, TD(TDL_NUMBERS_SYMBOLS)
    ),

    [FUNCTIONS_NUMPAD] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, XXXXXXX,   TD(TDL_BASE), KC_PLUS,  KC_7,   KC_8,   KC_9,  KC_ASTR, KC_BSPC,
    //----------------------------------------------------------------    ----------------------------------------------------------------
          KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,      XXXXXXX,   KC_MINS,  KC_4,   KC_5,   KC_6,  KC_SLSH,  KC_DEL,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          KC_COMM,  KC_1,   KC_2,   KC_3,   KC_EQL, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                            XXXXXXX, XXXXXXX, KC_SPC,       KC_ENT, KC_DOT,  KC_0
    ),

     [MOUSE] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
         KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    TD(TDL_BASE), MS_BTN3, MS_BTN1, MS_UP, MS_BTN2, XXXXXXX,XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
         KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, MS_WHLU, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        MS_WHLD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                        XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
    ),
   
    [SPECIAL] = LAYOUT_split_3x6_3_ex2(
    //----------------------------------------------------------------    ----------------------------------------------------------------
       QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_REBOOT,   TD(TDL_BASE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //----------------------------------------------------------------    ----------------------------------------------------------------
        RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,TD(TDL_SPECIAL),
    //----------------------------------------------------------------    ----------------------------------------------------------------
                                            XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [OS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [OPERATIONS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [NAVIGATE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [NUMBERS_SYMBOLS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [FUNCTIONS_NUMPAD] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [SPECIAL] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
