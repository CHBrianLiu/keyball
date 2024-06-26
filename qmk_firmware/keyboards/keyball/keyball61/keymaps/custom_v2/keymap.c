/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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
#include "g/keymap_combo.h"

#include "quantum.h"

#define xxx KC_NO
#define ___ KC_TRNS

enum Layers {
    base = 0,
    nav,
    mouse,
    media
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [base] = LAYOUT_universal(
    KC_GRV        , KC_1         , KC_2           , KC_3          , KC_4          , KC_5    ,                           KC_6           , KC_7 , KC_8     , KC_9     , KC_0      , KC_MINS  ,
    KC_TAB        , KC_Q         , KC_W           , KC_E          , KC_R          , KC_T    ,                           KC_Y           , KC_U , KC_I     , KC_O     , KC_P      , KC_EQL   ,
    CW_TOGG       , KC_A         , KC_S           , KC_D          , KC_F          , KC_G    ,                           KC_H           , KC_J , KC_K     , KC_L     , KC_SCLN   , KC_QUOT  ,
    OSM(MOD_LSFT) , KC_Z         , KC_X           , KC_C          , KC_V          , KC_B    , KC_LBRC ,       KC_RBRC , KC_N           , KC_M , KC_COMM  , KC_DOT   , KC_SLSH   , KC_BSLS  ,
    G(KC_TAB)     , OSM(MOD_MEH) , OSM(MOD_LALT)  , OSM(MOD_LGUI) , OSM(MOD_LCTL) , KC_SPC  , TO(nav) ,       KC_BSPC , LT(nav,KC_ENT) , xxx  , KC_NO    , KC_NO    , TO(base)  , TO(media)
  ),

  [nav] = LAYOUT_universal(
    xxx    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,                                 KC_NO      , KC_NO      , KC_NO       , KC_NO       , KC_NO    , KC_NO    ,
    ___    , xxx      , xxx      , KC_NO    , KC_NO    , KC_NO    ,                                 G(KC_LEFT) , A(KC_LEFT) , A(KC_RIGHT) , G(KC_RIGHT) , KC_NO    , KC_NO    ,
    xxx    , MOD_LGUI , MOD_LALT , MOD_LCTL , MOD_LSFT , KC_NO    ,                                 KC_LEFT    , KC_DOWN    , KC_UP       , KC_RIGHT    , KC_NO    , KC_NO    ,
    ___    , xxx      , xxx      , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,           KC_NO    , KC_HOME    , KC_PGDN    , KC_PGUP     , KC_END      , KC_NO    , KC_NO    ,
    ___    , KC_NO    , ___      , ___      , ___      , ___      , TO(base) ,           KC_NO    , KC_NO      , _______    , KC_NO       , KC_NO       , ___    , KC_NO
  ),

  [mouse] = LAYOUT_universal(
    xxx  , xxx     , LSG(KC_2) , xxx     , xxx     , xxx  ,                             KBC_RST  , KBC_SAVE   , xxx        , xxx       , xxx        , xxx     ,
    ___  , xxx     , xxx       , xxx     , G(KC_R) , xxx  ,                             AML_TO   , CPI_D100   , CPI_I100   , SCRL_DVI  , SCRL_DVD   , xxx     ,
    xxx  , G(KC_A) , xxx       , xxx     , xxx     , xxx  ,                             TO(base) , G(KC_LBRC) , G(KC_RBRC) , G(KC_EQL) , G(KC_MINS) , xxx     ,
    ___  , xxx     , G(KC_X)   , G(KC_C) , G(KC_V) , xxx  , xxx      ,           xxx  , G(KC_W)  , KC_BTN1    , KC_BTN2    , KC_BTN3   , xxx        , xxx     ,
    ___  , xxx     , ___       , ___     , ___     , xxx  , TO(base) ,           xxx  , SCRL_TO  , xxx        , xxx        , xxx       , ___        , ___
  ),

  [media] = LAYOUT_universal(
    KC_F11 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                            KC_F6    , KC_F7   , KC_F8      , KC_F9             , KC_F10          , KC_F12 ,
    xxx    , KC_F14 , KC_F15 , xxx    , xxx    , xxx    ,                            xxx      , xxx     , KC_KB_MUTE , KC_KB_VOLUME_DOWN , KC_KB_VOLUME_UP , xxx    ,
    xxx    , xxx    , xxx    , xxx    , xxx    , xxx    ,                            TO(base) , xxx     , xxx        , xxx               , xxx             , xxx    ,
    xxx    , xxx    , xxx    , xxx    , xxx    , xxx    , xxx   ,            xxx   , xxx      , xxx     , xxx        , xxx               , xxx             , xxx    ,
    ___    , xxx    , xxx    , xxx    , xxx    , xxx    , xxx   ,            ___   , xxx      , xxx     , xxx        , xxx               , ___             , xxx
  ),
};
// clang-format on

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    // always change back to normal trackball mode when leave mouse layer.
    keyball_set_scroll_mode(false);
    // when not in the mouse layer, make trackball too slow to use.
    // change back to default once back to the mouse layer.
    if (IS_LAYER_ON_STATE(state, mouse)) {
        // based on the code, set the cpi to 0 will be the default value.
        keyball_set_cpi(0);
    } else {
        keyball_set_cpi(1);
    }
    return state;
}

void keyboard_post_init_user(void) {
    // initialize with the minimum trackball cpi to indicate it's not in the mouse layer
    keyball_set_cpi(1);
}
