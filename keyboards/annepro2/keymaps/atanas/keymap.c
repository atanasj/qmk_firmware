#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"


enum anne_pro_layers {
  _BL,        /* base layer */
  _VI,        /* vi navigation layer */
  _NL,        /* numpad layer */
  _MS,        /* mouse layer */
  _FN2_LAYER, /* media and defualt FN2 layer */
  _FN,        /* function layer */
};

/* /\* tappining term per key *\/ */
/* uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) { */
/*     switch (keycode) { */
/*         case KC_RSPC: */
/*             return 500; */
/*         case KC_LSPO: */
/*             return 500; */
/*         case LT(_VI, KC_D): */
/*             return 500; */
/*         case LT(_MS, KC_E): */
/*             return 500; */
/*         default: */
/*             return TAPPING_TERM; */
/*     } */
/* } */
/* /\* permissive hold per key *\/ */
/* bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) { */
/*     switch (keycode) { */
/*         case LT(_VI, KC_D): */
/*             return true; */
/*         case LT(_MS, KC_E): */
/*             return true; */
/*         /\* case KC_RSPC: *\/ */
/*         /\*     return true; *\/ */
/*         default: */
/*             return false; */
/*     } */
/* } */
/* /\* ingore mod tap interupt per key *\/ */
/* bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) { */
/*     switch (keycode) { */
/*         case KC_RSPC: */
/*             return true; */
/*         default: */
/*             return false; */
/*     } */
/* } */

/* macros */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO( D(LCMD), D(LSFT), T(LEFT), U(LCMD), U(LSFT), T(BSPC), END  );
            case 1:
                return MACRO( D(LCMD), D(LSFT), T(RIGHT), U(LCMD), U(LSFT), T(BSPC), END  );
        }
    }
    return MACRO_NONE;
};

/* custom keys */
#define M_DBW M(0)
#define M_DFW M(1)

/*
* Layer _BL
* ,-----------------------------------------------------------------------------------------.
* | ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp     |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | Ctrl    |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Ctrl     |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | F20  |  L1   |  Alt  |               space             |    R1  |  Alt  |  FN  |  FN2  |
* \-----------------------------------------------------------------------------------------/
* Layer TAP in _BL
* ,-----------------------------------------------------------------------------------------.
* |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
* |-----------------------------------------------------------------------------------------+
* |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
* |-----------------------------------------------------------------------------------------+
* | esc     |     |     |     |     |     |     |     |     |     |     |     |  Enter      |
* |-----------------------------------------------------------------------------------------+
* |     (      |     |     |     |     |     |     |     |     |     |     |       |   )    |
* |-----------------------------------------------------------------------------------------+
* |       |       |       |                                 |       |       |       |       |
* \-----------------------------------------------------------------------------------------/
*/
 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_BL] = KEYMAP( /* Base */
    LT(_FN,KC_GRV), KC_1,    KC_2,    KC_3,            KC_4,            KC_5,           KC_6,          KC_7,           KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,        KC_BSPC,
    LCMD_T(KC_TAB), KC_Q,    KC_W,    LT(_MS,KC_E),    KC_R,            KC_T,           KC_Y,          KC_U,           KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC,       RCMD_T(KC_BSLS),
    LCTL_T(KC_ESC), KC_A,    KC_S,    LT(_VI,KC_D),    KC_F,            KC_G,           KC_H,          KC_J,           KC_K,    KC_L,   KC_SCLN, KC_QUOT, RCTL_T(KC_ENT),
    KC_LSPO,        KC_Z,    KC_X,    KC_C,            KC_V,            KC_B,           KC_N,          KC_M,           KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
    HYPR_T(KC_F20), KC_LCMD, KC_LALT, KC_SPC,          LCAG_T(KC_LEFT), MEH_T(KC_DOWN), LT(_FN,KC_UP), LT(_FN2_LAYER,KC_RIGHT)
),
  /*
  * Layer _VI
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |    |    |    |              |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     | _FN2_LAYER m|    |  HOME  | PGDN |  PGUP  |  END  |    |    |    |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc  |ALT |SFT |   | CMD |   | LEFT | DOWN | UP | RIGHT |    |     |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * |            |    |   |   |    |    |    |  BSPC  |  DEL  |   |    |           |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_VI] = KEYMAP( /* Base */
    _______, KC_1,    KC_2,    KC_3,    KC_4,         KC_5,    KC_6,       KC_7,     KC_8,    KC_9,      KC_0,    KC_MINS,       KC_EQL,        KC_BSPC,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      MO(_FN), KC_HOME,    KC_PGDN,  KC_PGUP, KC_END,    XXXXXXX, SCMD(KC_LBRC), SCMD(KC_RBRC), XXXXXXX,
    _______, KC_LALT, KC_LSFT, _______, KC_LCMD,      XXXXXXX, KC_LEFT,    KC_DOWN,  KC_UP,   KC_RIGHT,  KC_F19,  XXXXXXX,       _______,
    XXXXXXX, MO(_NL), XXXXXXX, XXXXXXX, XXXXXXX,      M_DBW,   A(KC_BSPC), KC_BSPC,  KC_DEL,  A(KC_DEL), M_DFW,   XXXXXXX,
    _______, _______, _______, _______, LCA(KC_LCMD), MOD_MEH, MO(_FN),    MO(_FN2_LAYER)
),
  /*
  * Layer _NL
  * ,-----------------------------------------------------------------------------------------.
* |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
* |-----------------------------------------------------------------------------------------+
* |        |     |  7  |  8  |  9  |     |  +  |  7  |  8  |  9  |     |     |     |        |
* |-----------------------------------------------------------------------------------------+
* |         |  0  |  4  |  5  |  6  |     |  0  |  4  |  5  |  6  |  /  |     |             |
* |-----------------------------------------------------------------------------------------+
* |            |     |  1  |  2  |  3  |  ,  |  *  |  1  |  2  |  3  |  -  |                |
* |-----------------------------------------------------------------------------------------+
* |       |       |       |               0                 |  .     |       |       |       |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_NL] = KEYMAP( /* Base */
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_EQL,  XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PDOT, KC_4,    KC_5,    KC_6,    KC_MINS, XXXXXXX, XXXXXXX,
    XXXXXXX, _______, KC_LALT, XXXXXXX, KC_LSFT, XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    KC_SLSH, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_0,    KC_PDOT, XXXXXXX, XXXXXXX, XXXXXXX
 ),
  /*
  * Layer _MS - Mouse Layer
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     |ACL2 |WL-U |MS-U |WL-D |ACL1 |ACL0 |     |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |     | ACL0 | ACL1 | ACL2 |     |BTN3 |MS-L |MS-D |MS-R |BTN2 |     |             |
  * |-----------------------------------------------------------------------------------------+
  * |            |     |     |     |     |     |BTN4 |BTN5 |WL-L |WL-R |     |                |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |              BTN1               |       |       |       |       |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_MS] = KEYMAP( /* Base */
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_ACL0, KC_ACL2, KC_ACL1, _______, MO(_FN2_LAYER), XXXXXXX, KC_WH_L, KC_WH_U,    KC_WH_D, KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, KC_MS_L, KC_MS_D,    KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, C(G(KC_D)), XXXXXXX, KC_BTN2, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX
 ),
  /*
  * Layer _FN2_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PLAY | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  V-DOWN  |  V_UP  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |V-UP |V-DWN|MUTE |  v  |  b  |  n  |  MUTE  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN2_LAYER] = KEYMAP( /* Base */
    KC_AP2_USB, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, XXXXXXX, XXXXXXX, XXXXXXX, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, XXXXXXX, KC_AP2_BT_UNPAIR,
    RESET,      XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,      KC_MPLY,                  KC_HOME,         KC_END,  XXXXXXX,
    KC_CAPS,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU,       KC_MNXT,      KC_PGUP,                  KC_PGDN,         XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX,       KC_INS,       KC_DEL,                   XXXXXXX,
    XXXXXXX,    XXXXXXX,    KC_BRID,    KC_BRIU,    XXXXXXX,    XXXXXXX, MO(_FN), _______
),
 /*
  * Layer _FN
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |V-UP |V-DWN|MUTE |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN] = KEYMAP( /* Base */
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,          KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_DEL,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(_FN2_LAYER), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_HOME, KC_END, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  KC_DEL,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, _______, MO(_FN2_LAYER)
),
};
const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

void keyboard_post_init_user(void) {
// if you haven't already and/or you want to enable LEDs by default at startup
annepro2LedEnable();

// i is the index of what profile you want to start with
// annepro2LedSetProfile(i);
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    return layer;
}
