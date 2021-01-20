#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"


enum anne_pro_layers {
  _BASE_LAYER,
  _VI_LAYER,
  _NUMPAD_LAYER,
  _MOUSE_LAYER,
  _MEDIA_LAYER,
  _FN1_LAYER,
  _FN2_LAYER,
};

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
* Layer _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* | ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp     |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | Ctrl    |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Ctrl     |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | F20  |  L1   |  Alt  |               space             |    R1  |  Alt  |  FN1  |  FN2  |
* \-----------------------------------------------------------------------------------------/
* Layer TAP in _BASE_LAYER
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
 [_BASE_LAYER] = KEYMAP( /* Base */
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    LT(_MOUSE_LAYER,KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, RCMD_T(KC_BSLS),
    LCTL_T(KC_ESC), KC_A, KC_S, LT(_VI_LAYER,KC_D), KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, RCTL_T(KC_ENT),
    KC_LSPO, LT(_NUMPAD_LAYER,KC_Z), KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
    HYPR_T(KC_F20), KC_LCMD, KC_LALT, KC_SPC, RCAG_T(KC_LEFT), MEH_T(KC_DOWN), LT(_FN1_LAYER,KC_UP), LT(_FN2_LAYER,KC_RIGHT)
),
  /*
  * Layer _VI_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     |     |     |    |    |    |              |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |    |  HOME  | PGDN |  PGUP  |  END  |    |    |    |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |KC_LALT |KC_LSFT |    |  KC_LCMD  |    |  LEFT  |  DOWN  |  UP  |  RIGHT  | | |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * |            |    |   |   |    |    |    |  BSPC  |  DEL  |   |    |           |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_VI_LAYER] = KEYMAP( /* Base */
    KC_GRV,  KC_1,              KC_2,    KC_3,                KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TRNS, KC_NO,             KC_NO,   KC_NO,               KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, SCMD(KC_LBRC), SCMD(KC_RBRC), KC_NO,
    KC_TRNS, KC_LALT, KC_LSFT,  KC_TRNS, KC_LCMD, KC_NO,      KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_F19, KC_NO, KC_TRNS,
    KC_NO,   MO(_NUMPAD_LAYER), KC_NO,   KC_NO, KC_NO, M_DBW, LALT(KC_BSPC), KC_BSPC, KC_DEL, LALT(KC_DEL), M_DFW, KC_NO,
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, RCTL(RALT(KC_RCMD)), MOD_MEH, MO(_FN1_LAYER), MO(_FN2_LAYER)
),
  /*
  * Layer _NUMPAD_LAYER
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
 [_NUMPAD_LAYER] = KEYMAP( /* Base */
    KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, KC_7,  KC_8,  KC_9,  KC_EQL,  KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, KC_4,  KC_5,  KC_6,  KC_MINS, KC_NO, KC_NO,
    KC_NO, KC_TRNS, KC_LALT, KC_NO, KC_LSFT, KC_NO, KC_NO, KC_1,  KC_2,  KC_3,  KC_NO,   KC_NO,
    KC_NO, KC_NO,   KC_NO,   KC_0,  KC_PDOT, KC_NO, KC_NO, KC_NO
 ),
  /*
  * Layer _MOUSE_LAYER - Mouse Layer
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
 [_MOUSE_LAYER] = KEYMAP( /* Base */
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_TRNS, KC_ACL2, KC_ACL0, KC_ACL1, MO(_MEDIA_LAYER), KC_NO, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCTL(LCMD(KC_D)), KC_NO, KC_BTN2, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_BTN1, KC_NO, KC_NO, KC_NO, KC_NO
 ),
  /*
  * Layer _MEDIA_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PLAY | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  V-DOWN  |  V_UP  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |V-UP |V-DWN|MUTE |  v  |  b  |  n  |  MUTE  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_MEDIA_LAYER] = KEYMAP( /* Base */
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPLY, KC_HOME, KC_END, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_PGUP, KC_PGDN, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_NO, KC_INS, KC_DEL, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MO(_FN1_LAYER), MO(_FN2_LAYER)
),
 /*
  * Layer _FN1_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |V-UP |V-DWN|MUTE |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN1_LAYER] = KEYMAP( /* Base */
    KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSCR, KC_HOME, KC_END, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_PGDN, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_INS, KC_DEL, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, MO(_FN2_LAYER)
),
  /*
  * Layer _FN2_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  ~  | BT1 | BT2 | BT3 | BT4 |  F5 |  F6 |  F7 |LEDOF|LEDON| F10 | F11 | F12 |    Bksp   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN2_LAYER] = KEYMAP( /* Base */
    KC_AP2_BT_UNPAIR, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, KC_NO, KC_NO, KC_NO, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, KC_NO, KC_NO,
    RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSCR, KC_HOME, KC_END, KC_NO,
    KC_CAPS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_PGDN, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_INS, KC_DEL, KC_NO,
    KC_NO, KC_NO, KC_BRID, KC_BRIU, KC_NO, KC_NO, MO(_FN1_LAYER), KC_TRNS
 ),
};
const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    return layer;
}
