#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "LUFA/Drivers/Peripheral/TWI.h"
#ifdef SSD1306OLED
    #include "ssd1306.h"
#endif

#define BASE 0 // default layer
#define GAME 1 // symbols

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  SHRUG,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ~    |   1  |   2  |   3  |   4  |   5  |  L0  |           |  L0  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  LU  |           |  LU  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CpLk   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '"   |
 * |--------+------+------+------+------+------|  LD  |           |  LD  |------+------+------+------+------+--------|
 * | LShift |  Z   |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | CTRL | ALT  |  `   | Left | Right|                                       |  Up  | Down |   {  |   }  | SHRUG|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | Esc  |       | Esc  |   |  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space| Enter|------|       |------|  Enter |BSpace|
 *                                 |      |      | LGui |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_TILDE,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   TO(BASE),
        KC_TAB,           KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TO(GAME),
        KC_CAPS,          KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,          KC_Z,         KC_X,   KC_C,   KC_V,   KC_B,   TO(GAME),
        KC_LCTRL,         KC_LALT,      KC_GRAVE,  KC_LEFT,KC_RGHT,
                                              KC_APP,  KC_ESCAPE,
                                                              KC_HOME,
                                               KC_BSPC,KC_ENTER,KC_LGUI,
        // right hand
             TO(BASE),     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_MINS,
             TO(GAME),    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
                          KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN,          KC_QUOT,
            TO(GAME),   KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,
                                  KC_UP, KC_DOWN,KC_LCBR,KC_RCBR,          SHRUG,
             KC_ESCAPE,        KC_PIPE,
             KC_PGUP,
             KC_PGDN,KC_ENT, KC_SPC
    ),
/* Keymap 1: Games
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ~    |   1  |   2  |   3  |   4  |   5  |  L0  |           |  L0  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  LU  |           |  LU  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CpLk   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '"   |
 * |--------+------+------+------+------+------|  LD  |           |  LD  |------+------+------+------+------+--------|
 * | LShift |  Z   |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | CTRL | ALT  |  `   | Left | Right|                                       |  Up  | Down |   {  |   }  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | Esc  |       | Esc  |   |  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space| Enter|------|       |------|  Enter |BSpace|
 *                                 |      |      | LGui |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[GAME] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_TILDE,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   TO(BASE),
        KC_TAB,           KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TO(BASE),
        KC_CAPS,          KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,          KC_Z,         KC_X,   KC_C,   KC_V,   KC_B,   TO(BASE),
        KC_LCTRL,         KC_LALT,      KC_GRAVE,  KC_LEFT,KC_RGHT,
                                              KC_APP,  KC_ESCAPE,
                                                              KC_HOME,
                                               KC_SPC,KC_ENTER,KC_LGUI,
        // right hand
             TO(BASE),     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_MINS,
             TO(BASE),    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
                          KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN,          KC_QUOT,
            TO(BASE),   KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,
                                  KC_UP, KC_DOWN,KC_LCBR,KC_RCBR,          SHRUG,
             KC_ESCAPE,        KC_PIPE,
             KC_PGUP,
             KC_PGDN,KC_ENT, KC_BSPC
)
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(GAME)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case SHRUG:
      if (record->event.pressed) {
        set_unicode_input_mode(UC_LNX);
        send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

#ifdef SSD1306OLED
void matrix_master_OLED_init(void) {
    TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
    iota_gfx_init();

}
#endif

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}
// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

#ifdef SSD1306OLED
    iota_gfx_task();
    struct CharacterMatrix matrix;

    matrix_clear(&matrix);
    matrix_write_P(&matrix, PSTR("camDox"));
    matrix_write_P(&matrix, PSTR("\n"));
    char buf[40];
    snprintf(buf, sizeof(buf), "undef-%ld", layer_state);
    switch(layer_state) {
        case 0:
        case 1:
            matrix_write_P(&matrix, PSTR("main"));
            break;
        case 2:
            matrix_write_P(&matrix, PSTR("games"));
            break;
        default:
            matrix_write(&matrix, buf);

    }
    matrix_update(&display, &matrix);
#endif
};

/*
void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;

    matrix_clear(&matrix);
    matrix_write_P(&matrix, PSTR("USB: "));

    matrix_update(&display, &matrix);

}
*/

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
