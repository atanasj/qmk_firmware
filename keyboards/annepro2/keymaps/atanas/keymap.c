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

/* enum custom_keycodes { */
/*     killb = SAFE_RANGE, */
/*     /\* killfwd *\/ */
/* }; */

/*                  /\* [:slash [:!CSleft_arrow :delete_or_backspace]] *\/ */
/*                  /\* [:!Sslash [:!CSright_arrow :delete_or_backspace]] *\/ */
/* const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) { */
/*     switch(id) { */
/*         case killb: { */
/*             if (record->event.pressed) { */
/*                 return MACRO( D(LCMD), D(LSFT), T(BSPC), U(LCTL), U(LCMD), END  ); */
/*             } else { */
/*                 /\* return MACRO( D(LCTL), T(V), U(LCTL), END  ); *\/ */
/*             } */
/*             break; */
/*         } */
/*     } */
/*     return MACRO_NONE; */
/* }; */
/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
/*     switch (keycode) { */
/*     case killback: */
/*         if (record->event.pressed) { */
/*             // when keycode is pressed */
/*             register_code(LCMD(LSFT(KC_RIGHT))); */
/*             tap_code(KC_BSPC); */
/*             /\* SEND_STRING("cell"); *\/ */
/*         } else { */
/*             // when keycode is released */
/*             clear_keyboard(); */
/*         } */
/*         break; */

/*     case killfwd: */
/*         if (record->event.pressed) { */
/*             // when keycode is pressed */
/*             register_code(LCMD(LSFT(KC_LEFT))); */
/*             tap_code(KC_BSPC); */
/*         } else { */
/*             // when keycode is released */
/*             clear_keyboard(); */
/*         } */
/*         break; */
/*     } */
/*     return true; */
/* }; */



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
    LT(_MOUSE_LAYER,KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    LCTL_T(KC_ESC), KC_A, KC_S, LT(_VI_LAYER,KC_D), KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, RCTL_T(KC_ENT),
    KC_LSPO, LT(_NUMPAD_LAYER,KC_Z), KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
    KC_F20, KC_LCMD, KC_LALT, KC_SPC, RCMD_T(KC_LEFT), RALT_T(KC_DOWN), LT(_FN1_LAYER,KC_UP), LT(_FN2_LAYER,KC_RIGHT)
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

                 /* [:##y :home] */
                 /* [:u :page_down] */
                 /* [:i :page_up] */
                 /* [:##o :end :!finder] */
 [_VI_LAYER] = KEYMAP( /* Base */
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    LCTL_T(KC_ESC), KC_LALT, KC_LSFT, KC_TRNS, KC_LCMD, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_TRNS, KC_TRNS, RCTL_T(KC_ENT),
    KC_LSPO, MO(_NUMPAD_LAYER), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LALT(KC_BSPC), KC_BSPC, KC_DEL, LALT(KC_DEL), KC_TRNS, KC_RSPC,
    KC_F20, KC_LCMD, KC_LALT, KC_SPC, KC_RCMD, KC_RALT, MO(_FN1_LAYER), MO(_FN2_LAYER)
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

                 /* [:##semicolon :hyphen] */
                 /* [:##v :left_shift] */
                 /* [:##x :left_option] */
                 /* [:##p :equal_sign] */
 [_NUMPAD_LAYER] = KEYMAP( /* Base */
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_7,   KC_8,   KC_9,  KC_EQL, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, MO(_VI_LAYER), KC_TRNS, KC_TRNS, KC_TRNS,   KC_4,   KC_5,   KC_6, KC_MINS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_LALT, KC_TRNS, KC_LSFT, KC_TRNS, KC_TRNS,   KC_1,   KC_2,   KC_3, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,   KC_0, KC_PDOT, KC_TRNS, KC_TRNS, KC_TRNS
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
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_ACL2, KC_ACL0, KC_ACL1, MO(_MEDIA_LAYER), KC_TRNS, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(LCMD(KC_D)), KC_TRNS, KC_BTN2, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
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
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_HOME, KC_END, KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_FN1_LAYER), MO(_FN2_LAYER)
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
    KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_FN2_LAYER)
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
    KC_AP2_BT_UNPAIR, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, KC_TRNS, KC_TRNS, KC_TRNS, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_FN1_LAYER), MO(_FN2_LAYER)
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
