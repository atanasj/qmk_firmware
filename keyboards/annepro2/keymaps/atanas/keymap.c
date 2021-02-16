#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"


enum anne_pro_layers {
  _BL = 0,        /* base layer */
  _VI = 1,        /* vi navigation layer */
  _NL = 2,        /* numpad layer */
  _MS = 3,        /* mouse layer */
  _FN = 4,        /* function and media layer */
  _FN2_LAYER = 5, /* defualt FN2 layer */
};

/* fix space cadet shift */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_RSFT:
        /* only right because LT() on left alphas */
        perform_space_cadet(record, KC_RSFT, KC_RSFT, KC_0);
        return false;
    default:
        return true; // Process all other keycodes normally
    }
}

/* tapping term per key */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_T(KC_SPC):
            return TAPPING_TERM + 175;
        case LT(_MS,KC_E):
            return 275;
        case LT(_VI,KC_D):
            return 275;
        case RCTL_T(KC_ENT):
            return 350;
        default:
            return TAPPING_TERM;
    }
}

/* move alt to space */
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

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

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

// Tap dance enums
enum {
    X_CTL,
    META_SPC,
    SUPER_SPC,
    R_CTL,
    L_CTL,
    R_CMD,
    L_CMD
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);
void meta_finished(qk_tap_dance_state_t *state, void *user_data);
void meta_reset(qk_tap_dance_state_t *state, void *user_data);
void r_ctl_finished(qk_tap_dance_state_t *state, void *user_data);
void r_ctl_reset(qk_tap_dance_state_t *state, void *user_data);
void l_ctl_finished(qk_tap_dance_state_t *state, void *user_data);
void l_ctl_reset(qk_tap_dance_state_t *state, void *user_data);

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
    LT(_FN,KC_GRV), KC_1,                         KC_2,                         KC_3,          KC_4,            KC_5,           KC_6,                        KC_7,           KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,        LT(_FN2_LAYER,KC_BSPC),
    LCMD_T(KC_TAB), KC_Q,                         KC_W,                         LT(_MS,KC_E),  KC_R,            KC_T,           KC_Y,                        KC_U,           KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC,       RCMD_T(KC_BSLS),
    LCTL_T(KC_ESC), KC_A,                         KC_S,                         LT(_VI,KC_D),  KC_F,            KC_G,           KC_H,                        KC_J,           KC_K,    KC_L,   KC_SCLN, KC_QUOT, RCTL_T(KC_ENT),
    KC_LSPO,        KC_Z,                         KC_X,                         KC_C,          KC_V,            KC_B,           KC_N,                        KC_M,           KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
    HYPR_T(KC_F20), MT(MOD_LGUI|MOD_LCTL,KC_ESC), MT(MOD_LGUI|MOD_LALT,KC_SPC), ALT_T(KC_SPC), LCAG_T(KC_LEFT), MEH_T(KC_DOWN), MT(MOD_LGUI|MOD_LCTL,KC_UP), SGUI_T(KC_RIGHT)
),

  /* VI layer */

 [_VI] = KEYMAP( /* Base */
    _______, _______, _______, _______, _______,      _______, _______,    _______,  _______, _______,   _______, _______,       _______,       KC_LEAD,
    _______, XXXXXXX, XXXXXXX, _______, _______,      XXXXXXX, KC_HOME,    KC_PGDN,  KC_PGUP, KC_END,    XXXXXXX, SCMD(KC_LBRC), SCMD(KC_RBRC), XXXXXXX,
    _______, KC_LALT, KC_LSFT, _______, KC_LCMD,      XXXXXXX, KC_LEFT,    KC_DOWN,  KC_UP,   KC_RIGHT,  KC_F19,  KC_CAPS,       _______,
    XXXXXXX, MO(_NL), _______, _______, _______,      M_DBW,   A(KC_BSPC), KC_BSPC,  KC_DEL,  A(KC_DEL), M_DFW,   XXXXXXX,
    _______, _______, _______, _______, LCA(KC_LCMD), MOD_MEH, _______,    _______
),

 /* NL layer */

 [_NL] = KEYMAP( /* Base */
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_EQL,  XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PDOT, KC_4,    KC_5,    KC_6,    KC_MINS, XXXXXXX, XXXXXXX,
    KC_LSFT, _______, KC_LALT, XXXXXXX, KC_LSFT, XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    KC_SLSH, XXXXXXX,
    XXXXXXX, XXXXXXX, _______, KC_0,    KC_PDOT, XXXXXXX, XXXXXXX, XXXXXXX
 ),

 /* MS layer */

 [_MS] = KEYMAP( /* Base */
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_ACL0, KC_ACL2, KC_ACL1, _______, KC_R,    XXXXXXX, KC_WH_L, KC_WH_U,    KC_WH_D, KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_A,    KC_S,    XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D,    KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_V,    XXXXXXX, XXXXXXX, C(G(KC_D)), XXXXXXX, KC_BTN2, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
 ),

 /* FN layer */

 [_FN] = KEYMAP( /* Base */
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, _______, _______
),

 /* FN2 layer */

 [_FN2_LAYER] = KEYMAP( /* Base */
    KC_AP2_USB, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, XXXXXXX, XXXXXXX, XXXXXXX, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, XXXXXXX, _______,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,      XXXXXXX,                  KC_HOME,         KC_END,  KC_AP2_BT_UNPAIR,
    KC_CAPS,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,      KC_PGUP,                  KC_PGDN,         XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_INS,       KC_DEL,                   XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, _______, _______
),

};
const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {

}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Create an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};

void x_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_X); break;
        case SINGLE_HOLD: register_code(KC_LCTRL); break;
        case DOUBLE_TAP: register_code(KC_ESC); break;
        case DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
    }
}

void x_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_X); break;
        case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
        case DOUBLE_TAP: unregister_code(KC_ESC); break;
        case DOUBLE_HOLD: unregister_code(KC_LALT);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
    }
    xtap_state.state = 0;
}

// Create an instance of 'tap' for the 'meta' tap dance.
static tap meta_tap_state = {
    .is_press_action = true,
    .state = 0
};

void meta_finished(qk_tap_dance_state_t *state, void *user_data) {
    meta_tap_state.state = cur_dance(state);
    switch (meta_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_SPC);
        break;
    case SINGLE_HOLD:
        register_code(KC_LGUI);
        register_code(KC_LALT);
        break;
    case DOUBLE_TAP:
        register_code(KC_ESC);
        break;
    case DOUBLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        register_code(KC_LALT);
        break;
    case DOUBLE_SINGLE_TAP: tap_code(KC_SPC); register_code(KC_SPC);
    }
}

void meta_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (meta_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_SPC);
        break;
    case SINGLE_HOLD:
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_ESC);
        break;
    case DOUBLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_SPC);
    }
    meta_tap_state.state = 0;
}

// Create an instance of 'tap' for the 'meta' tap dance.
static tap super_tap_state = {
    .is_press_action = true,
    .state = 0
};

void super_finished(qk_tap_dance_state_t *state, void *user_data) {
    super_tap_state.state = cur_dance(state);
    switch (super_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_SPC);
        break;
    case SINGLE_HOLD:
        register_code(KC_LGUI);
        register_code(KC_LCTL);
        break;
    case DOUBLE_TAP:
        register_code(KC_ESC);
        break;
    case DOUBLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_LGUI);
        register_code(KC_LCTL);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_SPC);
        register_code(KC_SPC);
    }
}

void super_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (super_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_SPC); break;
    case SINGLE_HOLD:
        unregister_code(KC_LGUI);
        unregister_code(KC_LCTL);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_ESC);
        break;
    case DOUBLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_LCTL);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_SPC);
    }
    super_tap_state.state = 0;
}

// Create an instance of 'tap' for the 'meta' tap dance.
static tap r_ctl_tap_state = {
    .is_press_action = true,
    .state = 0
};

void r_ctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    r_ctl_tap_state.state = cur_dance(state);
    switch (r_ctl_tap_state.state) {
    case SINGLE_TAP: register_code(KC_ENT); break;
    case SINGLE_HOLD:
        register_code(KC_RCTL);
        break;
    case DOUBLE_TAP:
        tap_code(KC_ENT);
        register_code(KC_ENT);
        break;
    case DOUBLE_HOLD:
        register_code(KC_RSFT);
        register_code(KC_RCTL);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_ENT);
        register_code(KC_ENT);
    }
}

void r_ctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (r_ctl_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_ENT);
        break;
    case SINGLE_HOLD:
        unregister_code(KC_RCTL);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_ENT);
        break;
    case DOUBLE_HOLD:
        unregister_code(KC_RSFT);
        unregister_code(KC_RCTL);
        /* break; */
    case DOUBLE_SINGLE_TAP: unregister_code(KC_ENT);
    }
    r_ctl_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'meta' tap dance.
static tap l_ctl_tap_state = {
    .is_press_action = true,
    .state = 0
};

void l_ctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    l_ctl_tap_state.state = cur_dance(state);
    switch (l_ctl_tap_state.state) {
    case SINGLE_TAP: register_code(KC_ESC); break;
    case SINGLE_HOLD:
        register_code(KC_LCTL);
        break;
    case DOUBLE_TAP:
        tap_code(KC_ESC);
        register_code(KC_ESC);
        break;
    case DOUBLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_ESC);
        register_code(KC_ESC);
    }
}

void l_ctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (l_ctl_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_ESC);
        break;
    case SINGLE_HOLD:
        unregister_code(KC_LCTL);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_ESC);
        break;
    case DOUBLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        /* break; */
    case DOUBLE_SINGLE_TAP: unregister_code(KC_ESC);
    }
    l_ctl_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'meta' tap dance.
static tap r_cmd_tap_state = {
    .is_press_action = true,
    .state = 0
};

void r_cmd_finished(qk_tap_dance_state_t *state, void *user_data) {
    r_cmd_tap_state.state = cur_dance(state);
    switch (r_cmd_tap_state.state) {
    case SINGLE_TAP: register_code(KC_BSLS); break;
    case SINGLE_HOLD:
        register_code(KC_RCMD);
        break;
    case DOUBLE_TAP:
        tap_code(KC_BSLS);
        register_code(KC_BSLS);
        break;
    case DOUBLE_HOLD:
        register_code(KC_RSFT);
        register_code(KC_RCMD);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_BSLS);
        register_code(KC_BSLS);
    }
}

void r_cmd_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (r_cmd_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_BSLS); break;
    case SINGLE_HOLD:
        unregister_code(KC_RCMD);
        break;
    case DOUBLE_TAP:
        /* unregister_code(KC_RSFT); */
        unregister_code(KC_BSLS);
        break;
    case DOUBLE_HOLD:
        unregister_code(KC_RSFT);
        unregister_code(KC_RCMD);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_BSLS);
    }
    r_cmd_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'meta' tap dance.
static tap l_cmd_tap_state = {
    .is_press_action = true,
    .state = 0
};

void l_cmd_finished(qk_tap_dance_state_t *state, void *user_data) {
    l_cmd_tap_state.state = cur_dance(state);
    switch (l_cmd_tap_state.state) {
    case SINGLE_TAP: register_code(KC_TAB); break;
    case SINGLE_HOLD:
        register_code(KC_LCMD);
        break;
    case DOUBLE_TAP:
        tap_code(KC_TAB);
        register_code(KC_TAB);
        break;
    case DOUBLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_LCMD);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_TAB);
        register_code(KC_TAB);
    }
}

void l_cmd_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (l_cmd_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_TAB); break;
    case SINGLE_HOLD:
        unregister_code(KC_LCMD);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_TAB);
        break;
    case DOUBLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_LCMD);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_TAB);
    }
    l_cmd_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
    [META_SPC] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, meta_finished, meta_reset, 200),
    [SUPER_SPC] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, super_finished, super_reset, 200),
    [R_CTL] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, r_ctl_finished, r_ctl_reset, 275),
    [L_CTL] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, l_ctl_finished, l_ctl_reset, 175),
    [R_CMD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, r_cmd_finished, r_cmd_reset, 175),
    [L_CMD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, l_cmd_finished, l_cmd_reset, 225)
};

/* leader key */
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // Replace the sequences below with your own sequences.
    SEQ_ONE_KEY(KC_T) {
      // When I press KC_LEAD and then T, this sends CTRL + SHIFT + T
      /* SEND_STRING(SS_LCTRL(SS_LSFT("t"))); */
      SEND_STRING("FM Susan");
    }
    SEQ_ONE_KEY(KC_H) {
      // When I press KC_LEAD and then T, this sends CTRL + SHIFT + T
      /* SEND_STRNG(SS_LCTRL(SS_LSFT("t"))); */
      SEND_STRING(SS_LSFT(SS_LGUI("/")));
    }
    // Note: This is not an array, you don't need to put any commas
    // or semicolons between sequences.
    // kill window
    SEQ_TWO_KEYS(KC_K, KC_W) {
      SEND_STRING(SS_LGUI("w"));
    }
    // kill app
    SEQ_TWO_KEYS(KC_K, KC_A) {
      SEND_STRING(SS_LGUI("q"));
    }
    // sleep screen
    SEQ_TWO_KEYS(KC_K, KC_S) {
      SEND_STRING(SS_LGUI(SS_LCTL("q")));
    }
    SEQ_TWO_KEYS(KC_N, KC_T) {
      // When I press KC_LEAD and then N followed by T, this sends CTRL + T
      SEND_STRING("I don't mind if I do, my dear. Just singing in the rain.");
      /* SEND_STRING(SS_LCTRL("t")); */
    }
  }
}

void keyboard_post_init_user(void) {
// if you haven't already and/or you want to enable LEDs by default at startup
annepro2LedEnable();

// i is the index of what profile you want to start with
annepro2LedSetProfile(10);
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    return layer;
}
