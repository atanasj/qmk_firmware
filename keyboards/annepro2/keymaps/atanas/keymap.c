#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"
#include "config.h"
/* #include "g/config_engine.h" */

enum anne_pro_layers {
  _BL = 0,        // base layer
  _VI = 1,        // vi navigation layer
  _NL = 2,        // numpad layer
  _MS = 3,        // mouse layer
  _FN = 4,        // function and media layer
  _FN2 = 5,       // defualt FN2 layer
};

#include "g/keymap_combo.h"

// Track led status
bool is_led_on = true;

// =============================================================================
// MACRO SECTION
// =============================================================================

enum macros {
    SUSPEND = AP2_SAFE_RANGE,
    M_DBW,
    M_DFW
};

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
    case M_DBW:
        if (record->event.pressed) {
            register_code(KC_LCMD);
            register_code(KC_LSFT);
            tap_code(KC_LEFT);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            tap_code(KC_BSPC);
        }
        return true;
    case M_DFW:
        if (record->event.pressed) {
            register_code(KC_LCMD);
            register_code(KC_LSFT);
            tap_code(KC_RIGHT);
            unregister_code(KC_LCMD);
            unregister_code(KC_LSFT);
            tap_code(KC_BSPC);
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
    META_DOWN,
    SUPER_UP,
    SL_HLP,
    SEMI_
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

// =============================================================================
// TAPPING TERM PER KEY SECTION
// =============================================================================

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LT(_MS,KC_E):
        return 225;
    case LT(_VI,KC_D):
        return 225;
    case RCTL_T(KC_ENT):
        return 350;
    case META_DOWN:
        return 165;
    case SUPER_UP:
        return 165;
    case SL_HLP:
        return 150;
    case KC_LSPO:
        return 120;
    case KC_RSPC:
        return 120;
    case SEMI_:
        return 155;
    default:
        return TAPPING_TERM;
    }
}

// =============================================================================
// MOD TAP INTERRUP PER KEY SECTION
// =============================================================================

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_T(KC_SPC):
            return true;
        case KC_LSPO:
            return true;
        case KC_RSFT:
            return true;
        default:
            return false;
    }
}

// =============================================================================
// KEYMAP SECTION
// =============================================================================

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
    KC_V,    KC_L,    _______, _______, _______, _______, _______,    _______,  _______, _______,   _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_HOME,    KC_PGDN,  KC_PGUP, KC_END,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_LCMD, KC_LALT, _______, KC_LSFT, KC_LEAD, KC_LEFT,    KC_DOWN,  KC_UP,   KC_RIGHT,  KC_F19,  KC_CAPS, _______,
    XXXXXXX, MO(_NL), _______, _______, _______, M_DBW,   A(KC_BSPC), KC_BSPC,  KC_DEL,  A(KC_DEL), M_DFW,   _______,
    _______, _______, _______, _______, _______, _______, _______,    _______
),
 /* NL layer */
 [_NL] = KEYMAP( /* Base */
    KC_N,    KC_L,    XXXXXXX, XXXXXXX,  XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, _______,  XXXXXXX,         XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_EQL,  XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_LGUI, KC_LALT, _______,  LSFT_T(KC_PDOT), XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_MINS, XXXXXXX, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  LGUI_T(KC_ENT),         XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    KC_PSLS, KC_TAB,
    XXXXXXX, XXXXXXX, _______, KC_0,     _______,         XXXXXXX, XXXXXXX, XXXXXXX
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

// =============================================================================
// TAP DANCE SECTION
// =============================================================================

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

qk_tap_dance_action_t tap_dance_actions[] = {
    [META_DOWN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, meta_finished, meta_reset),
    [SUPER_UP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, super_finished, super_reset),
    [SL_HLP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, help_finished, help_reset),
    [SEMI_]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, semi_finished, semi_reset)
};

// =============================================================================
// LEADER KEY SECTION
// =============================================================================

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();
        // NOTE in built R operators
        SEQ_ONE_KEY(KC_A) {
            /* needs to a as semi colon is a tap dance key */
            SEND_STRING(" <-");
        }
        SEQ_ONE_KEY(KC_P) {
            SEND_STRING(" %>%");
        }
        SEQ_ONE_KEY(KC_I) {
            SEND_STRING(" %in% ");
        }
        SEQ_ONE_KEY(KC_N) {
            SEND_STRING(" %!in% ");
        }
    }
}

// =============================================================================
// LED SECTION
// =============================================================================

void keyboard_post_init_user(void) {
annepro2LedEnable();
annepro2LedSetProfile(7);
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    switch(get_highest_layer(layer)) {
    case _VI:
        annepro2LedSetProfile(0);
        break;
    case _NL:
        annepro2LedSetProfile(1);
        break;
    case _MS:
        annepro2LedSetProfile(2);
        break;
    case _FN:
        annepro2LedSetProfile(3);
        break;
    case _FN2:
        annepro2LedSetProfile(4);
        break;
    default:
        annepro2LedSetProfile(7);
        break;
    }
    return layer;
}

void enableProfileColor(uint8_t * profile);
void resetProfileColor(void);
bool is_caps_set = false;
bool is_caps_on = false;
uint8_t caps_profile[] = {0xFF,0x00,0x00};
bool led_update_user(led_t leds) {
  if (leds.caps_lock) {
    is_caps_set = true;
    enableProfileColor(caps_profile);
    return true;
  } else if(is_caps_set) {
    is_caps_set = false;
    resetProfileColor();
  }

  return true;
}
