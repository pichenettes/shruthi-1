// Copyright 2009 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// In-memory text page with on-demand copy to LCD display.
//
// Instead of queuing text drawing instruction in the LCD buffer (BAD), this
// uses 2 text buffers, one containing the current status of the LCD, and one
// containing the requested text page. The 2 buffer are compared in a background
// process and differences are sent to the LCD display. This also manages a
// software blinking cursor.

#ifndef HARDWARE_HAL_DEVICES_BUFFERED_DISPLAY_H_
#define HARDWARE_HAL_DEVICES_BUFFERED_DISPLAY_H_

#include "hardware/base/base.h"
#include "hardware/hal/log2.h"
#include "hardware/hal/time.h"

namespace hardware_hal {

static const uint8_t kLcdNoCursor = 0xff;
static const uint8_t kLcdCursorBlinkRate = 0x0fff;
static const uint8_t kLcdCursor = 0xff;

template<typename Lcd>
class BufferedDisplay {
 public:
  enum {
    width = Lcd::lcd_width,
    height = Lcd::lcd_height,
    lcd_buffer_size = width * height,
    lcd_buffer_size_wrap = width * height - 1
  };

  BufferedDisplay() { }
  
  static void Init() {
    for (uint8_t i = 0; i < lcd_buffer_size; ++i) {
      local_[i] = ' ';
      remote_[i] = '?';
    }
    scan_position_last_write_ = 255;
    blink_ = 0;
    cursor_position_ = 255;
  }
  
  static void Print(uint8_t line, const char* text) {
    uint8_t row = width;
    uint8_t* destination = local_ + (line << Log2<width>::value);
    while (*text && row) {
      uint8_t character = *text;
      // Skip control characters.
      if (character == 124 || character == 254 ||
          (character >= 8 && character < 32)) {
        *destination++ = ' ';
      } else {
        *destination++ = character;
      }
      ++text;
      --row;
    }
  }
  
  // Use kLcdNoCursor (255) or any other value outside of the screen to hide.
  static inline void set_cursor_position(uint8_t cursor) {
    cursor_position_ = cursor;
  }

  static inline void set_cursor_character(uint8_t character) {
    cursor_character_ = character;
  }

  static inline void set_status(uint8_t status) __attribute__((noinline)) {
    // TODO(pichenettes): we're using the same clock for blinking the cursor
    // and clearing the status indicator. ewwww...
    blink_clock_ = 0;
    status_ = status + 1;
  }

  static void Tick() {
    // The following code is likely to write 4 bytes at most. If there are less
    // than 4 bytes available for write in the output buffer, there's no reason
    // to take the risk to continue.
    if (Lcd::writable() < 4) {
      return;
    }
    // It is now safe to assume that all writes of 4 bytes to the display buffer
    // will not block.
    
    // Blink the cursor and clears the status character.
    blink_clock_ = (blink_clock_ + 1) & kLcdCursorBlinkRate;
    if (blink_clock_ == 0) {
      blink_ = ~blink_;
      status_ = 0;
    }

    uint8_t character = 0;
    // Determine which character to show at the current position.
    // If the scan position is the cursor and it is shown (blinking), draw the
    // cursor.
    if (scan_position_ == cursor_position_ && blink_) {
      character = cursor_character_;
    } else {
      // Otherwise, check if there's a status indicator to display. It is
      // displayed either on the left or right of the first line, depending on
      // the available space.
      if (status_ && (scan_position_ == 0 || scan_position_ == (width - 1)) &&
          local_[scan_position_] == ' ') {
        character = status_ - 1;
      } else {
        character = local_[scan_position_];
      }
    }
    // Check whether the screen really has to be updated to show the character.
    if (character != remote_[scan_position_] ||
        scan_position_ == cursor_position_) {
      // There is a character to transmit!
      // If the new character to transmit is just after the previous one, and on
      // the same line, we're good, we don't need to reposition the cursor.
      if ((scan_position_ == scan_position_last_write_ + 1) &&
          (scan_position_ & (width - 1))) {
        // We use overwrite because we have checked before that there is
        // enough room in the buffer.
        Lcd::WriteData(character);
      } else {
        // The character to transmit is at a different position, we need to move
        // the cursor, and determine the cursor move command argument.
        Lcd::MoveCursor(
            scan_position_ >> Log2<width>::value,
            scan_position_ & (width - 1));
        Lcd::WriteData(character);
      }
      // We can now assume that remote display will be updated.
      remote_[scan_position_] = character;
      scan_position_last_write_ = scan_position_;
    }
    scan_position_ = (scan_position_ + 1) & lcd_buffer_size_wrap;
  }

 private:
  // Character pages storing what the display currently shows (remote), and
  // what it ought to show (local).
  static uint8_t local_[width * height];
  static uint8_t remote_[width * height];

  // Position of the last character being transmitted.
  static uint8_t scan_position_;
  static uint8_t scan_position_last_write_;
  static uint8_t blink_;
  static uint16_t blink_clock_;
  static uint8_t cursor_position_;
  static uint8_t cursor_character_;
  static uint8_t status_;

  DISALLOW_COPY_AND_ASSIGN(BufferedDisplay);
};

/* static */
template<typename Lcd>
uint8_t BufferedDisplay<Lcd>::local_[width * height];

/* static */
template<typename Lcd>
uint8_t BufferedDisplay<Lcd>::remote_[width * height];

/* static */
template<typename Lcd>
uint8_t BufferedDisplay<Lcd>::scan_position_;

/* static */
template<typename Lcd>
uint8_t BufferedDisplay<Lcd>::scan_position_last_write_;

/* static */
template<typename Lcd>
uint8_t BufferedDisplay<Lcd>::blink_;

/* static */
template<typename Lcd>
uint16_t BufferedDisplay<Lcd>::blink_clock_;

/* static */
template<typename Lcd>
uint8_t BufferedDisplay<Lcd>::cursor_position_;

/* static */
template<typename Lcd>
uint8_t BufferedDisplay<Lcd>::cursor_character_ = kLcdCursor;

/* static */
template<typename Lcd>
uint8_t BufferedDisplay<Lcd>::status_;

}  // namespace hardware_hal

#endif   // HARDWARE_HAL_DEVICES_BUFFERED_DISPLAY_H_
