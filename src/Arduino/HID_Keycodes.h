// HID_Keycodes.h
// Standard HID keycodes and aliases
// Use canonical TinyUSB HID enums where available

#ifndef HID_KEYCODES_H
#define HID_KEYCODES_H

//------------------------------------------------------------------
// Keyboard Keycodes (USB HID Usage ID: 0x04 - 0xA4)
//------------------------------------------------------------------
#define HID_KEY_A               0x04
#define HID_KEY_B               0x05
#define HID_KEY_C               0x06
#define HID_KEY_D               0x07
#define HID_KEY_E               0x08
#define HID_KEY_F               0x09
#define HID_KEY_G               0x0A
#define HID_KEY_H               0x0B
#define HID_KEY_I               0x0C
#define HID_KEY_J               0x0D
#define HID_KEY_K               0x0E
#define HID_KEY_L               0x0F
#define HID_KEY_M               0x10
#define HID_KEY_N               0x11
#define HID_KEY_O               0x12
#define HID_KEY_P               0x13
#define HID_KEY_Q               0x14
#define HID_KEY_R               0x15
#define HID_KEY_S               0x16
#define HID_KEY_T               0x17
#define HID_KEY_U               0x18
#define HID_KEY_V               0x19
#define HID_KEY_W               0x1A
#define HID_KEY_X               0x1B
#define HID_KEY_Y               0x1C
#define HID_KEY_Z               0x1D

#define HID_KEY_1               0x1E
#define HID_KEY_2               0x1F
#define HID_KEY_3               0x20
#define HID_KEY_4               0x21
#define HID_KEY_5               0x22
#define HID_KEY_6               0x23
#define HID_KEY_7               0x24
#define HID_KEY_8               0x25
#define HID_KEY_9               0x26
#define HID_KEY_0               0x27

//------------------------------------------------------------------
// HID Modifiers
//------------------------------------------------------------------
#define HID_MODIFIER_LEFT_CTRL    0x01
#define HID_MODIFIER_LEFT_SHIFT   0x02
#define HID_MODIFIER_LEFT_ALT     0x04
#define HID_MODIFIER_LEFT_GUI     0x08
#define HID_MODIFIER_RIGHT_CTRL   0x10
#define HID_MODIFIER_RIGHT_SHIFT  0x20
#define HID_MODIFIER_RIGHT_ALT    0x40
#define HID_MODIFIER_RIGHT_GUI    0x80

//------------------------------------------------------------------
// Media Key aliases (defined using enums in TinyUSB <tusb.h>)
// These enums are defined in class/hid/hid.h, already included via tusb.h in your main sketch.
//------------------------------------------------------------------
#define HID_CC_PLAY_PAUSE        HID_USAGE_CONSUMER_PLAY_PAUSE
#define HID_CC_SCAN_NEXT         HID_USAGE_CONSUMER_SCAN_NEXT_TRACK
#define HID_CC_SCAN_PREV         HID_USAGE_CONSUMER_SCAN_PREVIOUS_TRACK
#define HID_CC_STOP              HID_USAGE_CONSUMER_STOP
#define HID_CC_VOLUME_INC        HID_USAGE_CONSUMER_VOLUME_INCREMENT
#define HID_CC_VOLUME_DEC        HID_USAGE_CONSUMER_VOLUME_DECREMENT
#define HID_CC_MUTE              HID_USAGE_CONSUMER_MUTE

#endif // HID_KEYCODES_H