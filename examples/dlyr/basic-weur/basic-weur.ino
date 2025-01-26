// -*- mode: c++ -*-
// Copyright 2016-2022 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 100's firmware
 */

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-FirmwareVersion.h"
//#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
//#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-LED-Palette-Theme.h"
//#include "Kaleidoscope-Colormap.h"
#include "Kaleidoscope-IdleLEDs.h"
#include "Kaleidoscope-DefaultLEDModeConfig.h"
#include "Kaleidoscope-LEDBrightnessConfig.h"
#include "Kaleidoscope-HardwareTestMode.h"
#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-MagicCombo.h"
#include "Kaleidoscope-USB-Quirks.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-DynamicMacros.h"
//#include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-LayerNames.h"
#include "Kaleidoscope-Steno.h"

#include <Kaleidoscope-HostOS.h>
#include <Kaleidoscope-Unicode.h>
#include <Kaleidoscope-LED-ActiveLayerColor.h>
#include <Kaleidoscope-LED-ActiveModColor.h>

#define Key_Ampersand LSHIFT(Key_7)
#define Key_Asterisk LSHIFT(Key_8)
#define Key_At LSHIFT(Key_2)
#define Key_Carat LSHIFT(Key_6)
#define Key_Clear LSHIFT(Key_KeypadNumLock)
#define Key_Colon LSHIFT(Key_Semicolon)
#define Key_Dollar LSHIFT(Key_4)
#define Key_DoubleQuote LSHIFT(Key_Quote)
#define Key_ExclamationPoint LSHIFT(Key_1)
#define Key_GreaterThan LSHIFT(Key_Period)
#define Key_LeftParen LSHIFT(Key_9)
#define Key_LessThan LSHIFT(Key_Comma)
#define Key_Percent LSHIFT(Key_5)
#define Key_Plus LSHIFT(Key_Equals)
#define Key_Pound LSHIFT(Key_3)
#define Key_QuestionMark LSHIFT(Key_Slash)
#define Key_RithtParen LSHIFT(Key_0)
#define Key_Tilde LSHIFT(Key_Backtick)
//#define Key_Tilde LSHIFT(Key_NonUsPound)
#define Key_Underscore LSHIFT(Key_Minus)

#define Key_Compose Key_CapsLock

enum {
  PRIMARY,
  COLEMAK,
  WEUR,
  SYMBOLS,
  NUMNAV,
  SPACE_QUKEYS
};  // layers

// layers colors, same ordering
static const cRGB layerColormap[] PROGMEM = {
  CRGB(128, 0, 0),
  CRGB(0, 128, 128),
  CRGB(128, 0, 255),
  CRGB(255, 128, 0),
  CRGB(0, 255, 0),
  CRGB(10, 138, 138),  // slightly lighter than colemak
};

enum { MA_ACUTE,
       MA_GRAV,
       MA_CIRC,
       MA_UML,
       MA_CEDIL,
       MA_A_CIRC,
       MA_A_ACUTE,
       MA_A_GRAV,
       MA_A_UML,
       MA_E_CIRC,
       MA_E_ACUTE,
       MA_E_GRAV,
       MA_E_UML,
       MA_I_CIRC,
       MA_I_ACUTE,
       MA_I_GRAV,
       MA_I_UML,
       MA_O_CIRC,
       MA_O_ACUTE,
       MA_O_GRAV,
       MA_O_UML,
       MA_U_CIRC,
       MA_U_ACUTE,
       MA_U_GRAV,
       MA_U_UML,
       MA_C_CEDIL,
       MA_Y_UML,
       MA_A_ELIG,
       MA_O_ELIG
};


/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// clang-format off

KEYMAPS(


[PRIMARY] = KEYMAP_STACKED
(
   ___,                 Key_1, Key_2, Key_3, Key_4, Key_5, Key_OneShotCancel,
   Key_Backtick,        Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_Tab,             Key_A, Key_S, Key_D, Key_F, Key_G,
LockLayer(COLEMAK),     Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   OSL(SYMBOLS),        Key_Backspace, OSM(LeftControl), OSM(LeftShift),
   ShiftToLayer(NUMNAV),

   Key_RightAlt,  Key_6, Key_7, Key_8,     Key_9,         Key_0,         Key_LEDEffectNext,
   Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                  Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_Compose,   Key_N, Key_M, Key_Comma, Key_Period,   Key_Slash,     Key_Minus,
   Key_LeftGui,   OSM(LeftAlt), LT(SPACE_QUKEYS, Spacebar), OSM(RightShift),
   ShiftToLayer(WEUR)
 ),

[COLEMAK] = KEYMAP_STACKED
(
   ___            , ___     , ___     , ___     , ___     , ___  , ___,
   ___            , Key_Q   , Key_W   , Key_F   , Key_P   , Key_B, ___,
   ___            , GUI_T(A), ALT_T(R), SFT_T(S), CTL_T(T), Key_G,
LockLayer(PRIMARY), Key_Z   , Key_X   , Key_C   , Key_D   , Key_V, ___,
   ___, ___, ___, ___,
   ___,

   ___,   ___  , ___     , ___      , ___       , ___          , ___       ,
   ___,   Key_J, Key_L   , Key_U    , Key_Y     , Key_Semicolon, Key_Equals,
          Key_M, CTL_T(N), SFT_T(E) , ALT_T(I)  , GUI_T(O)     , Key_Quote ,
   ___,   Key_K, Key_H   , Key_Comma, Key_Period, Key_Slash    , Key_Minus ,
   ___, ___, ___, ___,
   ___
),

[WEUR]= KEYMAP_STACKED
(
   ___, ___           , ___          , ___           , ___ , ___ , ___,
   ___, ___           , ___          , ___           , ___ , ___ , ___,
   ___, M(MA_A_ACUTE) , M(MA_A_CIRC) , M(MA_A_UML)   , ___ , ___ ,
   ___, M(MA_A_ELIG)  , M(MA_O_ELIG) , M(MA_C_CEDIL) , ___ , ___ , ___,
   ___, ___           , ___          , ___           ,
   ___,

   ___, ___ , ___          , ___          , ___          , ___         , ___,
   ___, ___ , M(MA_U_CIRC) , M(MA_U_UML)  , M(MA_U_GRAV) , M(MA_Y_UML) , ___,
        ___ , M(MA_E_ACUTE), M(MA_E_GRAV) , M(MA_E_CIRC) , M(MA_E_UML) , ___,
   ___, ___ , M(MA_I_CIRC) , M(MA_I_UML)  , M(MA_O_CIRC) , M(MA_O_UML) , ___,
   ___, ___ , Key_Enter    , ___          ,
   ___
),

[SYMBOLS] =  KEYMAP_STACKED
(
   ___, ___, ___, ___, ___, ___, ___,
   ___, Key_ExclamationPoint, Key_LessThan,  Key_Equals, Key_GreaterThan, Key_Minus, ___,
   ___, Key_Backslash,        Key_LeftParen, Key_Dollar, Key_RightParen,  Key_Plus,
   ___, Key_Asterisk,         Key_At,        Key_Colon,  Key_Slash,       Key_Pound, ___,
   ___, ___, ___, ___,
   ___,

   ___, ___, ___, ___, ___, ___, ___,
   ___, Key_Carat,    Key_LeftBracket,      Key_Underscore, Key_RightBracket,      Key_DoubleQuote, ___,
        Key_Percent,  Key_LeftCurlyBracket, Key_Semicolon,  Key_RightCurlyBracket, Key_Quote, ___,
   ___, Key_Backtick, Key_Pipe,             Key_Tilde,      Key_Ampersand,         Key_QuestionMark, ___,
   ___, ___, ___, ___,
   ___
    ),

[NUMNAV] = KEYMAP_STACKED
(
 ___             , Key_F1 , Key_F2     , Key_F3       , Key_F4  , Key_F5 , Key_Compose ,
 Key_Tab         , Key_1  , Key_2      , Key_3        , Key_4   , Key_5  ,  ___        ,
 ___             , ___    , Key_Home   , Key_PageUp   , Key_End , ___    ,
 Key_PrintScreen , ___    , Key_Insert , Key_PageDown , ___     , ___    ,  ___        ,

 ___ , Key_Delete , ___,      ___,
 ___,

 Consumer_ScanPreviousTrack , Key_F6 , Key_F7, Key_F8, Key_F9, Key_F10, Key_F11,
 Consumer_ScanNextTrack     , Key_6  , Key_7 , Key_8 , Key_9 , Key_0  , Key_F12,
                               ___          , Key_LeftArrow           , Key_UpArrow   , Key_RightArrow          , Key_Period             , Key_Comma,
 Key_Menu                   , Consumer_Mute , Consumer_VolumeDecrement, Key_DownArrow , Consumer_VolumeIncrement, Consumer_PlaySlashPause, Consumer_Stop,

 ___, ___, Key_Space, ___,
 ___
),

[SPACE_QUKEYS] =  KEYMAP_STACKED
(
   ___        , ___        , ___        , ___        , ___        , ___        , ___        ,
   ___        , ___        , ___        , ___        , ___        , ___        , ___        ,
   ___        , M(MA_GRAV) , M(MA_ACUTE), M(MA_CIRC) , M(MA_UML)  , ___        ,
   ___        , ___        , ___        , M(MA_CEDIL), ___        , ___        , ___        ,
   Key_Compose, Key_Enter  , ___        , ___        ,
   ___        ,

   ___        , ___        , ___        , ___        , ___        , ___        , ___        ,
   ___        , ___        , ___        , ___        , ___        , ___        , ___        ,
                ___        , ___        , ___        , ___        , ___        , ___        ,
   ___        , ___        , ___        , ___        , ___        , ___        , ___        ,
   ___        , ___        , ___        , ___        ,
   ___
),


) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// clang-format on

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

#define D_ACUTE T(CapsLock), T(Quote)
#define D_GRAV T(CapsLock), T(Backtick)
#define D_CIRC T(CapsLock), T(Carat)
#define D_UML T(CapsLock), T(DoubleQuote)

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    switch (macro_id) {
      // generics
    case MA_ACUTE:
      return MACRO(D_ACUTE);
      break;
    case MA_GRAV:
      return MACRO(D_GRAV);
      break;
    case MA_CIRC:
      return MACRO(D_CIRC);
      break;
    case MA_UML:
      return MACRO(D_UML);
      break;
    case MA_CEDIL:
      return MACRO(T(CapsLock), T(Comma));
      //A
    case MA_A_CIRC:
      return MACRO(D_CIRC, T(A));
      break;
    case MA_A_ACUTE:
      return MACRO(D_ACUTE, T(A));
      break;
    case MA_A_GRAV:
      return MACRO(D_GRAV, T(A));
      break;
    case MA_A_UML:
      return MACRO(D_UML, T(A));
      break;
      //E
    case MA_E_CIRC:
      return MACRO(D_CIRC, T(E));
      break;
    case MA_E_ACUTE:
      return MACRO(D_ACUTE, T(E));
      break;
    case MA_E_GRAV:
      return MACRO(D_GRAV, T(E));
      break;
    case MA_E_UML:
      return MACRO(D_UML, T(E));
      break;
      //I
    case MA_I_CIRC:
      return MACRO(D_CIRC, T(I));
      break;
    case MA_I_ACUTE:
      return MACRO(D_ACUTE, T(I));
      break;
    case MA_I_GRAV:
      return MACRO(D_GRAV, T(I));
      break;
    case MA_I_UML:
      return MACRO(D_UML, T(I));
      break;
      //O
    case MA_O_CIRC:
      return MACRO(D_CIRC, T(O));
      break;
    case MA_O_ACUTE:
      return MACRO(D_ACUTE, T(O));
      break;
    case MA_O_GRAV:
      return MACRO(D_GRAV, T(O));
      break;
    case MA_O_UML:
      return MACRO(D_UML, T(O));
      break;
      //U
    case MA_U_CIRC:
      return MACRO(D_CIRC, T(U));
      break;
    case MA_U_ACUTE:
      return MACRO(D_ACUTE, T(U));
      break;
    case MA_U_GRAV:
      return MACRO(D_GRAV, T(U));
      break;
    case MA_U_UML:
      return MACRO(D_UML, T(U));
      break;
      //others
    case MA_C_CEDIL:
      return MACRO(T(CapsLock), T(Comma), T(C));
      break;
    case MA_Y_UML:
      return MACRO(D_UML, T(Y));
      break;
    case MA_A_ELIG:
      return MACRO(T(CapsLock), T(A), T(E));
      break;
    case MA_O_ELIG:
      return MACRO(T(CapsLock), T(O), T(E));
      break;
    }
  }
  return MACRO_NONE;
}

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 100's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE,
  // Enter test mode
  COMBO_ENTER_TEST_MODE
};

/** Wrappers, to be used by MagicCombo. **/

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/**
 * Toggles between using the built-in keymap, and the EEPROM-stored one.
 */
static void toggleKeymapSource(uint8_t combo_index) {
  if (Layer.getKey == Layer.getKeyFromPROGMEM) {
    Layer.getKey = EEPROMKeymap.getKey;
  } else {
    Layer.getKey = Layer.getKeyFromPROGMEM;
  }
}

/**
 *  This enters the hardware test mode
 */
static void enterHardwareTestMode(uint8_t combo_index) {
  HardwareTestMode.runTests();
}

/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
enum { PROTOCOLE,
       TEST_MODE,
       KEYMAP_SOURCE,
       //       A_CIRC,
       E_ACUTE
};


void typeSpecialChar(uint8_t combo_index) {
  switch (combo_index) {
  case E_ACUTE:
    Macros.tap(Key_CapsLock);
    Macros.tap(Key_Quote);
    Macros.tap(Key_E);
    break;
  default:
    Macros.type(PSTR("It's a kind of magic!"));
    break;
  }
}

USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = {R3C6, R2C6, R3C7}},
                 {.action = enterHardwareTestMode,
                  // Left Fn + Prog + LED
                  .keys = {R3C6, R0C0, R0C6}},
                 {.action = toggleKeymapSource,
                  // Left Fn + Prog + Shift
                  .keys = {R3C6, R0C0, R3C7}},
                 //N + E
                 //   {.action = typeSpecialChar,
                 //                  .keys = {R2C11, R2C12}}
);


// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // ----------------------------------------------------------------------
  // Chrysalis plugins

  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,
  HostOS,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion,

  // The LayerNames plugin allows Chrysalis to display - and edit - custom layer
  // names, to be shown instead of the default indexes.
  LayerNames,

  // Enables setting, saving (via Chrysalis), and restoring (on boot) the
  // default LED mode.
  DefaultLEDModeConfig,

  // Enables controlling (and saving) the brightness of the LEDs via Focus.
  // LEDBrightnessConfig,

  // ----------------------------------------------------------------------
  // Keystroke-handling plugins

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  Qukeys,

  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  //SpaceCadet,
  //SpaceCadetConfig,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  OneShot,
  //OneShotConfig,
  EscapeOneShot,
  //EscapeOneShotConfig,

  // The macros plugin adds support for macros
  Macros,
  Unicode,
  // Enables dynamic, Chrysalis-editable macros.
  //  DynamicMacros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  //  MouseKeys,
  // MouseKeysConfig,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // Enables the GeminiPR Stenography protocol. Unused by default, but with the
  // plugin enabled, it becomes configurable - and then usable - via Chrysalis.
  //  GeminiPR,

  // ----------------------------------------------------------------------
  // LED mode plugins

  // The boot greeting effect pulses the LED button for 10 seconds after the
  // keyboard is first connected
  //  BootGreetingEffect,

  // LEDControl provides support for other LED modes
  LEDControl,
  LEDActiveLayerColorEffect,
  ActiveModColorEffect,
  LEDOff,

  // The LED Palette Theme plugin provides a shared palette for other plugins,
  // like Colormap below
  // LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  //  ColormapEffect,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // Turns LEDs off after a configurable amount of idle time.
  IdleLEDs,
  PersistentIdleLEDs,

  // ----------------------------------------------------------------------
  // Miscellaneous plugins

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  HardwareTestMode  //,
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */


void setup() {

  //  for magic combo accent
  //    QUKEYS(
  //  kaleidoscope::plugin::Qukey(1, KeyAddr(2, 11), Key_NoKey), kaleidoscope::plugin::Qukey(1,
  //    KeyAddr(2, 12), Key_NoKey))

  //  QUKEYS(
  // left-side modifiers
  //  kaleidoscope::plugin::Qukey(COLEMAK, KeyAddr(2, 1), Key_LeftGui),      // A
  //    kaleidoscope::plugin::Qukey(COLEMAK, KeyAddr(2, 2), Key_LeftAlt),      // R
  //    kaleidoscope::plugin::Qukey(COLEMAK, KeyAddr(2, 3), Key_LeftControl),  // S
  //    kaleidoscope::plugin::Qukey(COLEMAK, KeyAddr(2, 4), Key_LeftShift),    // T
  //  )
  Qukeys.setHoldTimeout(250);
  Qukeys.setOverlapThreshold(80);
  //  Qukeys.setMinimumHoldTime(100);
  Qukeys.setMinimumPriorInterval(10);
  //  Qukeys.setMaxIntervalForTapRepeat(150);
  //
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  OneShot.setTimeout(500);
  OneShot.setDoubleTapTimeout(2500);

  LEDActiveLayerColorEffect.setColormap(layerColormap);
  ActiveModColorEffect.setHighlightColor(CRGB(128, 128, 128));
  ActiveModColorEffect.setOneShotColor(CRGB(255, 255, 255));
  ActiveModColorEffect.setStickyColor(CRGB(255, 150, 255));
  ActiveModColorEffect.highlightNormalModifiers(true);

  // Set the hue of the boot greeting effect to something that will result in a
  // nice green color.
  //  BootGreetingEffect.hue = 85;

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for eight layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command, or by using the
  // `keymap.onlyCustom` command to use EEPROM layers only.
  EEPROMKeymap.setup(8);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to eight layers, which is how
  // many editable layers we have (see above).
  //  ColormapEffect.max_layers(8);

  // For Dynamic Macros, we need to reserve storage space for the editable
  // macros. A kilobyte is a reasonable default.
  DynamicMacros.reserve_storage(1024);

  // If there's a default layer set in EEPROM, we should set that as the default
  // here.
  Layer.move(EEPROMSettings.default_layer());

  // use PROGMEM when boot for now
  Layer.getKey = Layer.getKeyFromPROGMEM;

  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  //  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();

  // Editable layer names are stored in EEPROM too, and we reserve 16 bytes per
  // layer for them. We need one extra byte per layer for bookkeeping, so we
  // reserve 17 / layer in total.
  LayerNames.reserve_storage(17 * 8);

  // Unless configured otherwise with Chrysalis, we want to make sure that the
  // firmware starts with LED effects off. This avoids over-taxing devices that
  // don't have a lot of power to share with USB devices
  DefaultLEDModeConfig.activateLEDModeIfUnconfigured(&LEDOff);
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
