#pragma once

#define _B0 11
#define _B1 15
#define _B2 16
#define _B3 14
#define _B4  8
#define _B5  9
#define _B6 10
#define _B7 12

#define _C6  5
#define _C7 13

#define _D0  3
#define _D1  2
#define _D2  0
#define _D3  1
#define _D4  4
#define _D5 17
#define _D6 22
#define _D7  6

#define _E2 23
#define _E6  7

#define _F0 24
#define _F1 25
#define _F4 21
#define _F5 20
#define _F6 19
#define _F7 18


#define bit_get(p, m) ((p) & (m))
#define bit_on(p, m) ((p) |= (m))
#define bit_off(p, m) ((p) &= ~(m))

#define UNUSED(x) x __attribute__ ((unused))

#define KEY_STATE_NONE 0
#define KEY_STATE_PRESSED 1
#define KEY_STATE_HELD 2
#define KEY_STATE_RELEASED 3

#define KBD_HALT false
#define KBD_CONTINUE true

#define FN_NONE       0
#define FN_KEYPRESS   1
#define FN_MEDIA      2
#define FN_STICKY     3
#define FN_LOCK       4
#define FN_MACRO      5
#define FN_GOTO_LAYER 6
#define FN_TAP_HOLD   7
#define FN_MOUSE_KEY  8
#define FN_AUTO_SHIFT 9
#define FN_NOTES      10
#define FN_USER_0    128

#define MCHY_NONE     0
#define MCHY_TRANS    1

/* modifier masks that are used by Mechy */
#define MOD_LSFT       0b0000000000000011
#define MOD_BITL_LSFT                   0
#define MOD_RSFT       0b0000000000001100
#define MOD_BITL_RSFT                 2
#define MOD_SHIFT      0b0000000000001111

#define MOD_LCTL       0b0000000000110000
#define MOD_BITL_LCTL               4
#define MOD_RCTL       0b0000000011000000
#define MOD_BITL_RCTL             6
#define MOD_CTRL       0b0000000011110000

#define MOD_LALT       0b0000001100000000
#define MOD_BITL_LALT           8
#define MOD_RALT       0b0000110000000000
#define MOD_BITL_RALT        10
#define MOD_ALT        0b0000111100000000

#define MOD_LGUI       0b0011000000000000
#define MOD_BITL_LGUI      12
#define MOD_RGUI       0b1100000000000000
#define MOD_BITL_RGUI    14
#define MOD_GUI        0b1111000000000000
