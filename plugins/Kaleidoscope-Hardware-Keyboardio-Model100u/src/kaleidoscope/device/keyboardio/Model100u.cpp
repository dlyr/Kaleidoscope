/* -*- mode: c++ -*-
 * Kaleidoscope-Hardware-Model100u -- Keyboardio Model 100 hardware support for Kaleidoscope
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

#ifdef ARDUINO_keyboardio_model_100u

#include "kaleidoscope/device/keyboardio/Model100u.h"

#include <Arduino.h>  // for PROGMEM
#include <Wire.h>     // for Wire

#include "kaleidoscope/driver/keyscanner/Base_Impl.h"  // For Base<>

namespace kaleidoscope {
namespace device {
namespace keyboardio {


#ifndef KALEIDOSCOPE_VIRTUAL_BUILD


/********* Key scanner *********/

driver::keyboardio::keydata_t Model100uKeyScanner::leftHandState;
driver::keyboardio::keydata_t Model100uKeyScanner::rightHandState;
driver::keyboardio::keydata_t Model100uKeyScanner::previousLeftHandState;
driver::keyboardio::keydata_t Model100uKeyScanner::previousRightHandState;

void Model100uKeyScanner::enableScannerPower() {
  pinMode(PB14, INPUT);
  digitalWrite(PB14, LOW);
  pinMode(PB15, INPUT);
  digitalWrite(PB15, LOW);
}


void Model100uKeyScanner::setup() {
}

void Model100uKeyScanner::readMatrix() {
  //scan the Keyboard matrix looking for connections
  previousLeftHandState  = leftHandState;
  previousRightHandState = rightHandState;

  if (Model100uHands::leftHand.readKeys()) {
    leftHandState = Model100uHands::leftHand.getKeyData();
  }

  if (Model100uHands::rightHand.readKeys()) {
    rightHandState = Model100uHands::rightHand.getKeyData();
  }
}

void Model100uKeyScanner::actOnHalfRow(uint8_t row, uint8_t colState, uint8_t colPrevState, uint8_t startPos) {
  if ((colState != colPrevState) || (colState != 0)) {
    for (uint8_t col = 0; col < 8; col++) {
      // Build up the key state for row, col
      uint8_t keyState = ((bitRead(colPrevState, 0) << 0) |
                          (bitRead(colState, 0) << 1));
      if (keyState)
        ThisType::handleKeyswitchEvent(Key_NoKey, KeyAddr(row, startPos - col), keyState);

      // Throw away the data we've just used, so we can read the next column
      colState     = colState >> 1;
      colPrevState = colPrevState >> 1;
    }
  }
}

void Model100uKeyScanner::actOnMatrixScan() {
  for (uint8_t row = 0; row < 4; row++) {
    actOnHalfRow(row, leftHandState.rows[row], previousLeftHandState.rows[row], 7);
    actOnHalfRow(row, rightHandState.rows[row], previousRightHandState.rows[row], 15);
  }
}


void Model100uKeyScanner::scanMatrix() {
  readMatrix();
  actOnMatrixScan();
}

void Model100uKeyScanner::setKeyscanInterval(uint8_t interval) {
  Model100uHands::leftHand.setKeyscanInterval(interval);
  Model100uHands::rightHand.setKeyscanInterval(interval);
}

bool Model100uKeyScanner::isKeyswitchPressed(KeyAddr key_addr) {
  auto row = key_addr.row();
  auto col = key_addr.col();
  if (col <= 7) {
    return (bitRead(leftHandState.rows[row], 7 - col) != 0);
  } else {
    return (bitRead(rightHandState.rows[row], 7 - (col - 8)) != 0);
  }
}

bool Model100uKeyScanner::wasKeyswitchPressed(KeyAddr key_addr) {
  auto row = key_addr.row();
  auto col = key_addr.col();
  if (col <= 7) {
    return (bitRead(previousLeftHandState.rows[row], 7 - col) != 0);
  } else {
    return (bitRead(previousRightHandState.rows[row], 7 - (col - 8)) != 0);
  }
}

uint8_t Model100uKeyScanner::pressedKeyswitchCount() {
  return __builtin_popcountl(leftHandState.all) + __builtin_popcountl(rightHandState.all);
}

uint8_t Model100uKeyScanner::previousPressedKeyswitchCount() {
  return __builtin_popcountl(previousLeftHandState.all) + __builtin_popcountl(previousRightHandState.all);
}

/********* Hardware plugin *********/

void Model100u::setup() {
  Model100uKeyScanner::setup();
  kaleidoscope::device::Base<Model100uProps>::setup();
}

void Model100u::enableHardwareTestMode() {
  // Toggle the programming LEDS on
  // TODO(anyone): PORTD |= (1 << 5);
  // TOOD(anyone): PORTB |= (1 << 0);

  // Disable the debouncer on the ATTinys
  KeyScanner::setKeyscanInterval(2);
}

void Model100u::rebootBootloader() {
  USBCore().disconnect();
  NVIC_SystemReset();
}

#endif

}  // namespace keyboardio
}  // namespace device
}  // namespace kaleidoscope

#endif
