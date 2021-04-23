#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"
#include "config.h"
/* #include "g/config_engine.h" */

enum anne_pro_layers {
  _BL = 0,        /* base layer */
  _VI = 1,        /* vi navigation layer */
  _NL = 2,        /* numpad layer */
  _MS = 3,        /* mouse layer */
  _FN = 4,        /* function and media layer */
  _FN2 = 5, /* defualt FN2 layer */
};

#include "g/keymap_combo.h"

enum macros {
    SUSPEND = AP2_SAFE_RANGE
};

// Track led status
bool is_led_on = true;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_RSFT:
        /* fix space cadet shift */
        /* only right because LT() on left alphas */
        perform_space_cadet(record, KC_RSPC, KC_RSFT, KC_RSFT, KC_0);
        return false;
    case SUSPEND:
        if (record->event.pressed) {
            if(is_led_on) {
                is_led_on = false;
                annepro2LedDisable();
                SEND_STRING(SS_LCTL(SS_LGUI("q")) SS_DELAY(500) SS_TAP(X_ESC));
            }
        }
        return true;
    default:
        if (record->event.pressed) {
            if(!is_led_on) {
                is_led_on = true;
                annepro2LedEnable();
            }
        }
    }
    return true;
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
// NOTE many are not used as the mod-tap functionality does not allow permissive
// hold and is laggy to use
enum {
    META_DOWN,
    SUPER_UP,
    X_CTL,
    SL_HLP,
    O_SAVE,
    Z_UNDO,
    I_SLCT,
    X_CCUT,
    C_COPY,
    V_PSTE,
    W_WIND,
    F_FIND,
    Q_QAPP,
    N_NNEW,
    SEMI_,
    PIPE_,
    DEVI_
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void cut_finished(qk_tap_dance_state_t *state, void *user_data);
void cut_reset(qk_tap_dance_state_t *state, void *user_data);
void x_finished(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);
void meta_finished(qk_tap_dance_state_t *state, void *user_data);
void meta_reset(qk_tap_dance_state_t *state, void *user_data);

/* tapping term per key */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LT(_MS,KC_E):
        return 275;
    case LT(_VI,KC_D):
        return 275;
    case RCTL_T(KC_ENT):
        return 350;
    case SL_HLP:
        return 150;
    case SEMI_:
        return 165;
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

/* #define CAPS_LOCATION (MATRIX_COLS * 2 + 11) /\* _VI layer *\/ */

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
    LT(_FN,KC_GRV), KC_1,                         KC_2,                         KC_3,          KC_4,            KC_5,          KC_6,         KC_7,           KC_8,    KC_9,   KC_0,       KC_MINS, KC_EQL,        KC_BSPC,
    LCMD_T(KC_TAB), KC_Q,                         KC_W,                         LT(_MS,KC_E),  KC_R,            KC_T,          KC_Y,         KC_U,           KC_I,    KC_O,   KC_P,       KC_LBRC, KC_RBRC,       RCMD_T(KC_BSLS),
    LCTL_T(KC_ESC), KC_A,                         KC_S,                         LT(_VI,KC_D),  KC_F,            KC_G,          KC_H,         KC_J,           KC_K,    KC_L,   TD(SEMI_),  KC_QUOT, RCTL_T(KC_ENT),
    KC_LSPO,        KC_Z,                         KC_X,                         KC_C,          KC_V,            KC_B,          KC_N,         KC_M,           KC_COMM, KC_DOT, TD(SL_HLP), KC_RSFT,
    HYPR_T(KC_F20), MT(MOD_LGUI|MOD_LCTL,KC_ESC), MT(MOD_LGUI|MOD_LALT,KC_SPC), ALT_T(KC_SPC), LCAG_T(KC_LEFT), TD(META_DOWN), TD(SUPER_UP), SGUI_T(KC_RIGHT)
),

  /* VI layer */
 [_VI] = KEYMAP( /* Base */
    KC_V,    KC_L,    _______, _______, _______, _______, _______,    _______,  _______, _______,   _______, _______,       _______,       _______,
    _______, _______, _______,    _______, KC_N,    KC_L,    KC_HOME,    KC_PGDN,  KC_PGUP, KC_END,    XXXXXXX, SCMD(KC_LBRC), SCMD(KC_RBRC), KC_LEAD,
    _______, KC_LCMD, KC_LALT, _______, KC_LSFT, XXXXXXX, KC_LEFT,    KC_DOWN,  KC_UP,   KC_RIGHT,  KC_F19,  KC_CAPS,       _______,
    XXXXXXX, MO(_NL), _______, _______, _______, M_DBW,   A(KC_BSPC), KC_BSPC,  KC_DEL,  A(KC_DEL), M_DFW,   _______,
    _______, _______, _______, _______, _______, _______, _______,    _______
),
 /* NL layer */
 [_NL] = KEYMAP( /* Base */
    KC_N,    KC_L,    XXXXXXX, XXXXXXX,         XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, _______,         XXXXXXX,         XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_EQL,  XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_LGUI, KC_LALT, _______,         LSFT_T(KC_PDOT), XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_MINS, XXXXXXX, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, LGUI_T(KC_ENT),  XXXXXXX,         XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    KC_PSLS, KC_TAB,
    XXXXXXX, XXXXXXX, _______, KC_0,            _______,         XXXXXXX, XXXXXXX, XXXXXXX
 ),
 /* MS layer */
 [_MS] = KEYMAP( /* Base */
    KC_M,    KC_L,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_ACL0, KC_ACL2, KC_ACL1, _______, KC_R,    XXXXXXX, KC_WH_L, KC_WH_U,    KC_WH_D, KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_A,    KC_S,    XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D,    KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, C(G(KC_D)), XXXXXXX, KC_BTN2, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
 ),
 /* FN layer */
 [_FN] = KEYMAP( /* Base */
    _______, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    XXXXXXX, KC_ASDN, KC_ASUP,  KC_ASRP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, CMB_ON,  CMB_OFF, CMB_TOG,
    XXXXXXX, KC_ASON, KC_ASOFF, KC_ASTG, XXXXXXX, XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_BRID,  KC_BRIU, XXXXXXX, XXXXXXX, _______, _______
),
 /* FN2 layer */
 [_FN2] = KEYMAP( /* Base */
    KC_AP2_USB, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, KC_AP2_BT_UNPAIR, XXXXXXX, XXXXXXX, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, XXXXXXX, XXXXXXX,
    SUSPEND,    S(KC_GRV),  KC_GRV,     KC_BSLS,    S(KC_BSLS), XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,      XXXXXXX,                  XXXXXXX,         XXXXXXX, XXXXXXX,
    XXXXXXX,    S(KC_LBRC), KC_LBRC,    KC_RBRC,    S(KC_RBRC), XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,      _______,                  XXXXXXX,         XXXXXXX,
    XXXXXXX,    S(KC_MINS), XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,      XXXXXXX,                  XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_LGUI,    XXXXXXX,    XXXXXXX,          XXXXXXX, XXXXXXX
),

};
const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {

}

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    } if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8;
}

// Create an instance of 'tap' for the 'meta' tap dance.
static tap devi_tap_state = {
    .is_press_action = true,
    .state = 0
};

void devi_finished(qk_tap_dance_state_t *state, void *user_data) {
    devi_tap_state.state = cur_dance(state);
    switch (devi_tap_state.state) {
    case SINGLE_TAP:
        tap_code(KC_D);
        break;
    case SINGLE_HOLD:
        layer_on(_VI);
        break;
    case DOUBLE_TAP:
        if (layer_state_is(_MS) || layer_state_is(_NL)) {
            layer_off(_MS);
            layer_off(_NL);
        } else {
            tap_code(KC_D);
            tap_code(KC_D);
        }
        break;
    case DOUBLE_HOLD:
        layer_on(_NL);
        break;
    case TRIPLE_TAP:
        if (layer_state_is(_NL)) {
            layer_off(_NL);
        } else {
            layer_on(_NL);
        }
        break;
    case TRIPLE_HOLD:
        layer_on(_MS);
        break;
    }
}

void devi_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (devi_tap_state.state == SINGLE_HOLD) {
        layer_off(_VI);
    }
    if (devi_tap_state.state == DOUBLE_HOLD) {
        layer_off(_NL);
    }
    if (devi_tap_state.state == TRIPLE_HOLD) {
        layer_off(_MS);
    }
    devi_tap_state.state = 0;
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
        register_code(KC_DOWN);
        break;
    case SINGLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_LALT);
        break;
    /* case DOUBLE_TAP: */
    /*     tap_code(KC_DOWN); */
    /*     register_code(KC_DOWN); */
    /*     break; */
    case DOUBLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_LALT);
        register_code(KC_LGUI);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_DOWN);
        register_code(KC_DOWN);
    }
}

void meta_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (meta_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_DOWN);
        break;
    case SINGLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        break;
    /* case DOUBLE_TAP: */
    /*     unregister_code(KC_DOWN); */
    /*     break; */
    case DOUBLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_DOWN);
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
        register_code(KC_UP);
        break;
    case SINGLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        break;
    /* case DOUBLE_TAP: */
    /*     tap_code(KC_UP); */
    /*     register_code(KC_UP); */
    /*     break; */
    case DOUBLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        register_code(KC_LGUI);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_UP);
        register_code(KC_UP);
    }
}

void super_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (super_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_UP); break;
    case SINGLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        break;
    /* case DOUBLE_TAP: */
    /*     unregister_code(KC_DOWN); */
    /*     break; */
    case DOUBLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LGUI);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_UP);
    }
    super_tap_state.state = 0;
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

// Create an instance of 'tap' for the 'x' tap dance.
static tap help_tap_state = {
    .is_press_action = true,
    .state = 0
};

void help_finished(qk_tap_dance_state_t *state, void *user_data) {
    help_tap_state.state = cur_dance(state);
    switch (help_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_SLSH);
        break;
        /* case SINGLE_HOLD: register_code(KC_LCTRL); break; */
    case DOUBLE_TAP:
        register_code(KC_LCMD);
        register_code(KC_LSFT);
        register_code(KC_SLSH);
    }
}

void help_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (help_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_SLSH);
        break;
        /* case SINGLE_HOLD: unregister_code(KC_LCTRL); break; */
    case DOUBLE_TAP:
        unregister_code(KC_LCMD);
        unregister_code(KC_LSFT);
        unregister_code(KC_SLSH);
    }
    help_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'x' tap dance.
static tap semi_tap_state = {
    .is_press_action = true,
    .state = 0
};

void semi_finished(qk_tap_dance_state_t *state, void *user_data) {
    semi_tap_state.state = cur_dance(state);
    switch (semi_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_SCLN);
        break;
    case SINGLE_HOLD:
        layer_on(_FN2);
        break;
    case DOUBLE_TAP:
        register_code(KC_LSFT);
        register_code(KC_MINS);
    }
}

void semi_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (semi_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_SCLN);
        break;
    case SINGLE_HOLD:
        layer_off(_FN2);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_LSFT);
        unregister_code(KC_MINS);
    }
    semi_tap_state.state = 0;
}

// Create an instance of 'tap' for the 'x' tap dance.
static tap pipe_tap_state = {
    .is_press_action = true,
    .state = 0
};

void pipe_finished(qk_tap_dance_state_t *state, void *user_data) {
    pipe_tap_state.state = cur_dance(state);
    switch (pipe_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_LBRC);
        break;
        /* case SINGLE_HOLD: register_code(KC_LCTRL); break; */
    case DOUBLE_TAP:
        register_code(KC_BSLS);
    }
}

void pipe_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (pipe_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_LBRC);
        break;
        /* case SINGLE_HOLD: unregister_code(KC_LCTRL); break; */
    case DOUBLE_TAP:
        unregister_code(KC_BSLS);
    }
    pipe_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'x' tap dance.
static tap save_tap_state = {
    .is_press_action = true,
    .state = 0
};

void save_finished(qk_tap_dance_state_t *state, void *user_data) {
    save_tap_state.state = cur_dance(state);
    switch (save_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_0);
        break;
    case DOUBLE_TAP:
        register_code(KC_LCMD);
        register_code(KC_S);
        break;
        /* below important for words like session, which I use a lot */
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_0);
        register_code(KC_0);
    }
}

void save_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (save_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_0);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_LCMD);
        unregister_code(KC_S);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_0);
    }
    save_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'x' tap dance.
static tap undo_tap_state = {
    .is_press_action = true,
    .state = 0
};

void undo_finished(qk_tap_dance_state_t *state, void *user_data) {
    undo_tap_state.state = cur_dance(state);
    switch (undo_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_Z);
        break;
    case DOUBLE_TAP:
        register_code(KC_LCMD);
        register_code(KC_Z);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_Z);
        register_code(KC_Z);
    }
}

void undo_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (undo_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_Z);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_LCMD);
        unregister_code(KC_Z);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_Z);
    }
    undo_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'x' tap dance.
static tap select_tap_state = {
    .is_press_action = true,
    .state = 0
};

void select_finished(qk_tap_dance_state_t *state, void *user_data) {
    select_tap_state.state = cur_dance(state);
    switch (select_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_1);
        break;
    case DOUBLE_TAP:
        register_code(KC_LCMD);
        register_code(KC_A);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_1);
        register_code(KC_1);
    }
}

void select_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (select_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_1);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_LCMD);
        unregister_code(KC_A);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_1);
    }
    select_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'x' tap dance.
static tap cut_tap_state = {
    .is_press_action = true,
    .state = 0
};

void cut_finished(qk_tap_dance_state_t *state, void *user_data) {
    cut_tap_state.state = cur_dance(state);
    switch (cut_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_X);
        break;
    case DOUBLE_TAP:
        register_code(KC_LCMD);
        register_code(KC_X);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_X);
        register_code(KC_X);
    }
}

void cut_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (cut_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_X);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_LCMD);
        unregister_code(KC_X);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_X);
    }
    cut_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'x' tap dance.
static tap copy_tap_state = {
    .is_press_action = true,
    .state = 0
};

void copy_finished(qk_tap_dance_state_t *state, void *user_data) {
    copy_tap_state.state = cur_dance(state);
    switch (copy_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_C);
        break;
    case DOUBLE_TAP:
        register_code(KC_LCMD);
        register_code(KC_C);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_C);
        register_code(KC_C);
    }
}

void copy_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (copy_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_C);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_LCMD);
        unregister_code(KC_C);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_C);
    }
    copy_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'x' tap dance.
static tap pst_tap_state = {
    .is_press_action = true,
    .state = 0
};

void pst_finished(qk_tap_dance_state_t *state, void *user_data) {
    pst_tap_state.state = cur_dance(state);
    switch (pst_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_V);
        break;
    case DOUBLE_TAP:
        register_code(KC_LCMD);
        register_code(KC_V);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_V);
        register_code(KC_V);
    }
}

void pst_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (pst_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_V);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_LCMD);
        unregister_code(KC_V);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_V);
    }
    pst_tap_state.state = 0;
}

// Create an instance of 'tap' for the 'x' tap dance.
static tap wind_tap_state = {
    .is_press_action = true,
    .state = 0
};

void wind_finished(qk_tap_dance_state_t *state, void *user_data) {
    wind_tap_state.state = cur_dance(state);
    switch (wind_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_W);
        break;
    case DOUBLE_TAP:
        register_code(KC_LCMD);
        register_code(KC_W);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_W);
        register_code(KC_W);
    }
}

void wind_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (wind_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_W);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_LCMD);
        unregister_code(KC_W);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_W);
    }
    wind_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'x' tap dance.
static tap find_tap_state = {
    .is_press_action = true,
    .state = 0
};

void find_finished(qk_tap_dance_state_t *state, void *user_data) {
    find_tap_state.state = cur_dance(state);
    switch (find_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_F);
        break;
    case DOUBLE_TAP:
        register_code(KC_LCMD);
        register_code(KC_F);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_F);
        register_code(KC_F);
    }
}

void find_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (find_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_F);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_LCMD);
        unregister_code(KC_F);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_F);
    }
    find_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'x' tap dance.
static tap qapp_tap_state = {
    .is_press_action = true,
    .state = 0
};

void qapp_finished(qk_tap_dance_state_t *state, void *user_data) {
    qapp_tap_state.state = cur_dance(state);
    switch (qapp_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_Q);
        break;
    case DOUBLE_TAP:
        register_code(KC_LCMD);
        register_code(KC_Q);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_Q);
        register_code(KC_Q);
    }
}

void qapp_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (qapp_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_Q);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_LCMD);
        unregister_code(KC_Q);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_Q);
    }
    qapp_tap_state.state = 0;
}


// Create an instance of 'tap' for the 'x' tap dance.
static tap nnew_tap_state = {
    .is_press_action = true,
    .state = 0
};

void nnew_finished(qk_tap_dance_state_t *state, void *user_data) {
    nnew_tap_state.state = cur_dance(state);
    switch (nnew_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_N);
        break;
    case DOUBLE_TAP:
        register_code(KC_LCMD);
        register_code(KC_N);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code(KC_N);
        register_code(KC_N);
    }
}

void nnew_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (nnew_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_N);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_LCMD);
        unregister_code(KC_N);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code(KC_N);
    }
    nnew_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [META_DOWN] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, meta_finished, meta_reset, 175),
    [SUPER_UP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, super_finished, super_reset, 175),
    [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
    /* NOTE in newer qmk firmware `_TIME` suffix function is depracted, use TAPPING_TERM_PER_KEY instead */
    [SL_HLP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, help_finished, help_reset),
    [SEMI_]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, semi_finished, semi_reset),
    [PIPE_]  = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, pipe_finished, pipe_reset, 150),
    [Z_UNDO] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, undo_finished, undo_reset, 175),
    [O_SAVE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, save_finished, save_reset, 175),
    [I_SLCT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, select_finished, select_reset, 175),
    [X_CCUT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, cut_finished, cut_reset, 175),
    [C_COPY] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, copy_finished, copy_reset, 120),
    [V_PSTE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, pst_finished, pst_reset, 175),
    [W_WIND] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, wind_finished, wind_reset, 130),
    [F_FIND] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, find_finished, find_reset, 120),
    [Q_QAPP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, qapp_finished, qapp_reset, 150),
    [DEVI_] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, devi_finished, devi_reset, 250),
    [N_NNEW] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, nnew_finished, nnew_reset, 120)
};

/* leader key */
LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();
        SEQ_ONE_KEY(KC_A) {
            SEND_STRING(SS_LGUI("a"));
        }
        SEQ_ONE_KEY(KC_C) {
            SEND_STRING(SS_LGUI("c"));
        }
        SEQ_ONE_KEY(KC_O) {
            SEND_STRING(SS_LGUI("o"));
        }
        SEQ_ONE_KEY(KC_V) {
            SEND_STRING(SS_LGUI("v"));
        }
        SEQ_ONE_KEY(KC_X) {
            SEND_STRING(SS_LGUI("x"));
        }
        SEQ_ONE_KEY(KC_S) {
            SEND_STRING(SS_LGUI("s"));
        }
        SEQ_TWO_KEYS(KC_S, KC_S) {
            SEND_STRING(SS_LSFT(SS_LGUI("s")));
        }
        SEQ_ONE_KEY(KC_H) {
            SEND_STRING(SS_LSFT(SS_LGUI("/")));
        }
        SEQ_ONE_KEY(KC_F) {
            SEND_STRING(SS_LGUI("f"));
        }
        SEQ_TWO_KEYS(KC_F, KC_F) {
            SEND_STRING(SS_LSFT(SS_LGUI("f")));
        }
        SEQ_TWO_KEYS(KC_W, KC_W) {
            SEND_STRING(SS_LGUI("w"));
        }
        SEQ_TWO_KEYS(KC_Q, KC_Q) {
            SEND_STRING(SS_LGUI("q"));
        }
        SEQ_ONE_KEY(KC_Z) {
            SEND_STRING(SS_LGUI("z"));
        }
        SEQ_TWO_KEYS(KC_Z, KC_Z) {
            SEND_STRING(SS_LSFT(SS_LGUI("z")));
        }
    }
}

/* NOTE colour section */
/* =============================================================================== */

void keyboard_post_init_user(void) {
annepro2LedEnable();
// white
/* annepro2LedSetProfile(0); */
/* rainbow */
annepro2LedSetProfile(7);
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    switch(get_highest_layer(layer)) {
    case _VI:
        // Set the leds to white
        annepro2LedSetProfile(0);
        break;
    case _NL:
        // Set the leds to orange
        annepro2LedSetProfile(1);
        break;
    case _MS:
        // Set the leds to red
        annepro2LedSetProfile(2);
        break;
    case _FN:
        // Set the leds to blue
        annepro2LedSetProfile(3);
        break;
    case _FN2:
        // Set the leds to yellow
        annepro2LedSetProfile(4);
        break;
    default:
        // Reset back to the current profile
        annepro2LedSetProfile(7);
        break;
    }
    return layer;
}

// The function to handle the caps lock logic
// We use a state to avoid clearing the background if capslock was not set
// somehow it leads to flickering with fn1 and fn1 in tap mode.
bool is_caps_on = false;
bool led_update_user(led_t leds) {
    if (leds.caps_lock) {
        // Set the leds to red
        is_caps_on = true;
        annepro2LedSetProfile(2);
        /* annepro2LedSetForegroundColor(0xFF, 0x00, 0x00); */
    } else if (is_caps_on){
        // Reset back to the current profile if there is no layer active
        if(!layer_state_is(_VI) && !layer_state_is(_NL) && !layer_state_is(_MS) && !layer_state_is(_FN) && !layer_state_is(_FN2)) {
            annepro2LedSetProfile(11);
            /* annepro2LedResetForegroundColor(); */
            is_caps_on = false;
        }
    }
    return true;
}
