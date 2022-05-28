/* -*- mode: c++ -*-
 * Kaleidoscope-Escape-OneShot -- Turn ESC into a key that cancels OneShots, if active.
 * Copyright (C) 2016-2021  Keyboard.io, Inc
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

#include "kaleidoscope/plugin/Escape-OneShot.h"

#include <Kaleidoscope-OneShot.h>  // for OneShot

#include "kaleidoscope/KeyEvent.h"              // for KeyEvent
#include "kaleidoscope/event_handler_result.h"  // for EventHandlerResult, EventHandlerResult::E...
#include "kaleidoscope/key_defs.h"              // for Key, Key_Escape, Key_NoKey
#include "kaleidoscope/keyswitch_state.h"       // for keyIsInjected, keyToggledOn

namespace kaleidoscope {
namespace plugin {

EventHandlerResult EscapeOneShot::onKeyEvent(KeyEvent &event) {
  // We only act on an escape key (or `cancel_oneshot_key_`, if that has been
  // set) that has just been pressed, and not generated by some other
  // plugin. Also, only if at least one OneShot key is active and/or
  // sticky. Last, only if there are no OneShot keys currently being held.
  //
  // `Key_OneShotCancel` will always count as an escape key, even if not
  // explicitly set so.
  if ((event.key == settings_.cancel_oneshot_key ||
       event.key == Key_OneShotCancel) &&
      keyToggledOn(event.state) &&
      !keyIsInjected(event.state) &&
      ::OneShot.isActive()) {
    // Cancel all OneShot keys
    ::OneShot.cancel(true);
    // Change the cancellation key to a blank key, and signal that event
    // processing is complete.
    event.key = Key_NoKey;
    return EventHandlerResult::EVENT_CONSUMED;
  }

  // Otherwise, do nothing
  return EventHandlerResult::OK;
}

}  // namespace plugin
}  // namespace kaleidoscope

kaleidoscope::plugin::EscapeOneShot EscapeOneShot;
