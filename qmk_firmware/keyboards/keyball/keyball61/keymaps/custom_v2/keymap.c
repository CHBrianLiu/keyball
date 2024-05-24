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

#include "quantum.h"

enum Layers {
    base = 0,
    nav,
    mouse,
    media
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [base] = LAYOUT_universal(
    KC_GRV        , KC_1      , KC_2           , KC_3          , KC_4          , KC_5           ,                                              KC_6   , KC_7     , KC_8     , KC_9     , KC_0        , KC_MINS  ,
    KC_TAB        , KC_Q      , KC_W           , KC_E          , KC_R          , KC_T           ,                                              KC_Y   , KC_U     , KC_I     , KC_O     , KC_P        , KC_EQL   ,
    CW_TOGG       , KC_A      , KC_S           , KC_D          , KC_F          , KC_G           ,                                              KC_H   , KC_J     , KC_K     , KC_L     , KC_SCLN     , KC_QUOT  ,
    OSM(MOD_LSFT) , KC_Z      , KC_X           , KC_C          , KC_V          , KC_B           , KC_LBRC          ,       KC_RBRC           , KC_N   , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH     , KC_BSLS  ,
    G(KC_TAB)     , C(KC_SPC) , OSM(MOD_LALT)  , OSM(MOD_LGUI) , OSM(MOD_LCTL) , LT(nav,KC_SPC) , LT(mouse,KC_ESC) ,       LT(media,KC_BSPC) , KC_ENT , KC_NO    , KC_NO    , KC_NO    , OSM(KC_MEH) , SCRL_MO
  ),

  [nav] = LAYOUT_universal(
    KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,                                 KC_NO      , KC_NO      , KC_NO       , KC_NO       , KC_NO    , KC_NO    ,
    DM_RSTP  , DM_REC1  , DM_REC2  , KC_NO    , KC_NO    , KC_NO    ,                                 G(KC_LEFT) , A(KC_LEFT) , A(KC_RIGHT) , G(KC_RIGHT) , KC_NO    , KC_NO    ,
    KC_NO    , MOD_LGUI , MOD_LALT , MOD_LCTL , MOD_LSFT , KC_NO    ,                                 KC_LEFT    , KC_DOWN    , KC_UP       , KC_RIGHT    , KC_NO    , KC_NO    ,
    KC_NO    , DM_PLY1  , DM_PLY2  , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,           KC_NO    , KC_HOME    , KC_PGDN    , KC_PGUP     , KC_END      , KC_NO    , KC_NO    ,
    KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , _______  , KC_NO    ,           KC_NO    , KC_NO      , _______    , KC_NO       , KC_NO       , KC_NO    , KC_NO
  ),

  [mouse] = LAYOUT_universal(
    KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,                                 KBC_RST  , KBC_SAVE   , KC_NO      , KC_NO     , KC_NO      , KC_NO    ,
    KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,                                 KC_NO    , G(KC_LBRC) , G(KC_RBRC) , G(KC_EQL) , G(KC_MINS) , KC_NO    ,
    KC_NO    , MOD_LGUI , MOD_LALT , MOD_LCTL , MOD_LSFT , AML_TO   ,                                 KC_BTN2  , KC_BTN1    , KC_BTN3    , KC_NO     , KC_NO      , KC_NO    ,
    KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,           KC_NO    , KC_NO    , CPI_D100   , CPI_I100   , SCRL_DVI  , SCRL_DVD   , KC_NO    ,
    KC_NO    , KC_NO    , KC_NO    , KC_NO    , _______  , KC_NO    , _______  ,           G(KC_W)  , KC_NO    , _______    , KC_NO      , KC_NO     , KC_NO      , _______
  ),

  [media] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EE_CLR   ,            EE_CLR   , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    QK_BOOT  , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  , _______  , _______  , _______  , _______  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
