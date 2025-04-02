// HID_Descriptors.h
// Defines USB HID report descriptor macros (keyboard, joystick, gamepad, etc.)
// This file is used to define the HID capabilities sent to the host (e.g. "this device has 32 buttons").
// These do NOT include runtime button/key values — those go in HID_Keycodes.h.

#ifndef HID_DESCRIPTORS_H
#define HID_DESCRIPTORS_H

#include "tusb.h"

//--------------------------------------------------------------------------
// Keyboard Report Descriptor
//--------------------------------------------------------------------------
#define HID_REPORT_DESC_KEYBOARD(...) \
  TUD_HID_REPORT_DESC_KEYBOARD(__VA_ARGS__)

//--------------------------------------------------------------------------
// Gamepad / Joystick Report Descriptor Stub
// Replace or extend with actual descriptor macros when needed
//--------------------------------------------------------------------------
#define HID_REPORT_DESC_GAMEPAD(...) \
  HID_USAGE_PAGE(HID_USAGE_PAGE_DESKTOP), \
  HID_USAGE(HID_USAGE_GAMEPAD), \
  HID_COLLECTION(HID_COLLECTION_APPLICATION), \
    /* Add buttons, axes, etc. here */ \
  HID_COLLECTION_END

//--------------------------------------------------------------------------
// (Planned) Joystick with 6 axes, throttle, POV hat, 32 buttons
//--------------------------------------------------------------------------
#define HID_REPORT_DESC_JOYSTICK_FULL(...) \
  HID_USAGE_PAGE(HID_USAGE_PAGE_DESKTOP), \
  HID_USAGE(HID_USAGE_JOYSTICK), \
  HID_COLLECTION(HID_COLLECTION_APPLICATION), \
    HID_USAGE(HID_USAGE_POINTER), \
    HID_COLLECTION(HID_COLLECTION_PHYSICAL), \
      HID_USAGE(HID_USAGE_X), \
      HID_USAGE(HID_USAGE_Y), \
      HID_USAGE(HID_USAGE_Z), \
      HID_USAGE(HID_USAGE_RX), \
      HID_USAGE(HID_USAGE_RY), \
      HID_USAGE(HID_USAGE_RZ), \
      HID_USAGE(HID_USAGE_SLIDER), \
      HID_LOGICAL_MIN16(0), \
      HID_LOGICAL_MAX16(1023), \
      HID_REPORT_SIZE(16), \
      HID_REPORT_COUNT(7), \
      HID_INPUT(HID_DATA | HID_VARIABLE | HID_ABSOLUTE), \
    HID_COLLECTION_END, \
    HID_USAGE_PAGE(HID_USAGE_PAGE_BUTTON), \
      HID_USAGE_MIN(1), \
      HID_USAGE_MAX(32), \
      HID_LOGICAL_MIN(0), \
      HID_LOGICAL_MAX(1), \
      HID_REPORT_SIZE(1), \
      HID_REPORT_COUNT(32), \
      HID_INPUT(HID_DATA | HID_VARIABLE | HID_ABSOLUTE), \
    HID_USAGE_PAGE(HID_USAGE_PAGE_DESKTOP), \
      HID_USAGE(HID_USAGE_HAT_SWITCH), \
      HID_LOGICAL_MIN(0), \
      HID_LOGICAL_MAX(7), \
      HID_PHYSICAL_MIN(0), \
      HID_PHYSICAL_MAX(315), \
      HID_UNIT(HID_UNIT_ENG_ROTATION), \
      HID_REPORT_SIZE(4), \
      HID_REPORT_COUNT(1), \
      HID_INPUT(HID_DATA | HID_VARIABLE | HID_ABSOLUTE), \
      HID_REPORT_SIZE(4), \
      HID_REPORT_COUNT(1), \
      HID_INPUT(HID_CONSTANT), \
  HID_COLLECTION_END

#endif // HID_DESCRIPTORS_H
