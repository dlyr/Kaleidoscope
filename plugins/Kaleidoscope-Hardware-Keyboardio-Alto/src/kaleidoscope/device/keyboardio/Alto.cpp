/* -*- mode: c++ -*-
 * Kaleidoscope-Hardware-Alto -- Keyboardio Alto hardware support for Kaleidoscope
 * Copyright (C) 2021  Keyboard.io, Inc
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef ARDUINO_keyboardio_alto

#include "kaleidoscope/driver/keyscanner/Base_Impl.h"  // For Base<>

#include "kaleidoscope/device/keyboardio/Alto.h"
#include "kaleidoscope/Runtime.h"

#include <Arduino.h>  // for PROGMEM

namespace kaleidoscope {
namespace device {
namespace keyboardio {



#ifndef KALEIDOSCOPE_VIRTUAL_BUILD

/********* Hardware plugin *********/

void Alto::rebootBootloader() {
  USBCore().disconnect();
  NVIC_SystemReset();
}

#endif

}  // namespace keyboardio
}  // namespace device
}  // namespace kaleidoscope

#endif
