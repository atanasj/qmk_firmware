#pragma once

#undef TAPPING_TERM
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
#define RETRO_TAPPING

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 350

#define COMBO_VARIABLE_LEN
/* #define COMBO_COUNT 13 */
#define COMBO_TERM 50

/* #define AUTO_SHIFT_TIMEOUT 150 */
/* #define AUTO_SHIFT_MODIFIERS */
/* #define NO_AUTO_SHIFT_ALPHA */
/* #define NO_AUTO_SHIFT_SPECIAL */
/* #define NO_AUTO_SHIFT_NUMERIC */

#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL

/* #define IS_COMMAND() (matrix_is_on(3, 0) && matrix_is_on(3, 11)) */
/* #define IS_COMMAND() (matrix_is_on(0, 1) && matrix_is_on(0, 3) && matrix_is_on(0, 4) && matrix_is_on(0, 5)) */
/* #define IS_COMMAND() (get_mods() == (MOD_BIT(KC_Q) | MOD_BIT(KC_W) | MOD_BIT(KC_E) | MOD_BIT(KC_R))) */

/* #define CAPS_LOCATION (MATRIX_COLS * 2 + 11) */
#define CAPS_LOCATION (MATRIX_COLS * 2 + 11)

#define IDLE_PROFILE_INDEX 0
