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
// Driver for Sparkfun's serial-enabled LCD displays, with double buffering, and
// a "low-granularity" approach to writes.
//
// All updates to the content of the screen are done in an in-memory "local"
// text page. A "remote" buffer mirrors the current state of the LCD display.
// A task should periodically call the Update() method, which scans the local
// and remote pages for differences, transmits serially the modified character
// in the local page to the LCD, and updates the remote buffer to reflect that
// the character was transmitted. This guarantees that large, contiguous chunks
// of CPU time are not spent in the display code - and makes this class deal
// more nicely with other tasks when cooperative multitasking is used.
//
// Note also that it minimizes the amount of data to transmit. In particular,
// if only small sections of the display are updated (for example a digit in
// the bottom right corner), this only retransmits the updated characters -
// without the programmer having to manually deal with cursor positioning.
//
// TODO(pichenettes): this class assumes that software serial will be used.
// Rework this a bit to have the driver and serial i/o more loosely coupled.

#ifndef HARDWARE_HAL_DEVICES_SPARKFUN_SER_LCD_H_
#define HARDWARE_HAL_DEVICES_SPARKFUN_SER_LCD_H_

#include "hardware/base/base.h"
#include "hardware/hal/log2.h"
#include "hardware/hal/software_serial.h"
#include "hardware/hal/time.h"
#include "hardware/resources/resources_manager.h"
#include "hardware/utils/logging.h"

using hardware_resources::SimpleResourcesManager;

namespace hardware_hal {

static const uint8_t kLcdNoCursor = 0xff;
static const uint8_t kLcdCursorBlinkRate = 0x7f;
static const uint8_t kLcdCursor = 0xff;
// Dear Serial LCD, why do I have to tell you all the time that I don't want
// to use your stupid default 9600 bps baud rate? Are you listening to me?
// Serial LCD? Serial LCD? Serial LCD?
static const uint8_t kSerialLcdIsMyProblemChild = 5;

template<typename TxPin,
         uint16_t main_timer_rate,
         uint16_t baud_rate,
         uint8_t width = 16,
         uint8_t height = 2>
class Display {
 public:
  enum {
    lcd_buffer_size = width * height,
    lcd_buffer_size_wrap = width * height - 1
  };
  typedef BufferedSoftwareSerialOutput<
      TxPin,
      main_timer_rate,
      baud_rate,
      8> DisplaySerialOutput;

  typedef SoftwareSerialOutput<
      TxPin,
      9600> DisplayPanicSerialOutput;

  Display() { }
  static void Init() {
    for (uint8_t i = 0; i < lcd_buffer_size; ++i) {
      local_[i] = ' ';
      remote_[i] = '?';
    }
    scan_position_last_write_ = 255;
    blink_ = 0;
    cursor_position_ = 255;
    // It is assumed, at initialization, that the display is wrongly in 9600
    // bauds mode. Send this message to switch to the target baud rate.
    // At worst, if the baud rate is already set, this will display glitchy
    // characters for a short amount of time (if the display is configured at
    // 2400 bps, they look like the infinity symbol).
    for (uint8_t i = 0; i < kSerialLcdIsMyProblemChild; ++i) {
      DisplayPanicSerialOutput::Write(124);
      if (baud_rate == 2400) {
        DisplayPanicSerialOutput::Write(11);
      } else if (baud_rate == 4800) {
        DisplayPanicSerialOutput::Write(12);
      } else if (baud_rate == 9600) {
        DisplayPanicSerialOutput::Write(13);
      } else if (baud_rate == 14400) {
        DisplayPanicSerialOutput::Write(14);
      } else if (baud_rate == 19200) {
        DisplayPanicSerialOutput::Write(15);
      } else if (baud_rate == 19200) {
        DisplayPanicSerialOutput::Write(16);
      }
      Delay(200);
    }
    DisplaySerialOutput::Init();
  }
  
  static void Print(uint8_t line, const char* text) {
    if (line == 0) {
      LOG(INFO) << "display\ttext\t+----------------+";
    }
    LOG(INFO) << "display\ttext\t|" << text << "|";
    if (line == height - 1) {
      LOG(INFO) << "display\ttext\t+----------------+";
    }
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
  
  static void SetBrightness(uint8_t brightness) {  // 0 to 29.
    DisplaySerialOutput::Write(0x7c);
    DisplaySerialOutput::Write(128 + brightness);
  }

  static void SetCustomCharMap(const uint8_t* characters,
                               uint8_t num_characters) {
    DisplaySerialOutput::Write(0xfe);
    DisplaySerialOutput::Write(0x01);
    for (uint8_t i = 0; i < num_characters; ++i) {
      DisplaySerialOutput::Write(0xfe);
      DisplaySerialOutput::Write(0x40 + i * 8);
      for (uint8_t j = 0; j < 8; ++j) {
        // The 6th bit is not used, so it is set to prevent character definition
        // data to be misunderstood with special commands.
        DisplaySerialOutput::Write(0x20 |
            SimpleResourcesManager::Lookup<uint8_t, uint8_t>(
                characters, i * 8 + j));
     }
     DisplaySerialOutput::Write(0xfe);
     DisplaySerialOutput::Write(0x01);
    }
  }

  // Use kLcdNoCursor (255) or any other value outside of the screen to hide.
  static inline void set_cursor_position(uint8_t cursor) {
    cursor_position_ = cursor;
  }

  static inline void set_status(uint8_t status) __attribute__((noinline)) {
    // TODO(pichenettes): we're using the same clock for blinking the cursor
    // and clearing the status indicator. ewwww...
    blink_clock_ = 0;
    status_ = status + 1;
  }

  static inline void Tick() { DisplaySerialOutput::Tick(); }
  
  static void Update() {
    // The following code is likely to write 3 bytes at most. If there are less
    // than 3 bytes available for write in the output buffer, there's no reason
    // to take the risk to continue.
    if (DisplaySerialOutput::writable() < 3) {
      return;
    }
    // It is now safe to assume that all writes of 3 bytes to the display buffer
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
      character = kLcdCursor;
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
        DisplaySerialOutput::Overwrite(character);
      } else {
        // The character to transmit is at a different position, we need to move
        // the cursor, and determine the cursor move command argument.
        uint8_t cursor_position = 0x80;
        cursor_position |= (scan_position_ & ~(width - 1)) <<
            Log2<64 / width>::value;
        cursor_position |= (scan_position_ & (width - 1));
        DisplaySerialOutput::Overwrite(0xfe);
        DisplaySerialOutput::Overwrite(cursor_position);
        DisplaySerialOutput::Overwrite(character);
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
  static uint8_t blink_clock_;
  static uint8_t cursor_position_;
  static uint8_t status_;

  DISALLOW_COPY_AND_ASSIGN(Display);
};

template<typename TxPin, uint16_t main_timer_rate, uint16_t baud_rate,
         uint8_t width, uint8_t height>
uint8_t Display<TxPin, main_timer_rate, baud_rate, width,
                height>::local_[width * height];

template<typename TxPin, uint16_t main_timer_rate, uint16_t baud_rate,
         uint8_t width, uint8_t height>
uint8_t Display<TxPin, main_timer_rate, baud_rate, width,
                height>::remote_[width * height];

template<typename TxPin, uint16_t main_timer_rate, uint16_t baud_rate,
         uint8_t width, uint8_t height>
uint8_t Display<TxPin, main_timer_rate, baud_rate, width,
                height>::scan_position_;

template<typename TxPin, uint16_t main_timer_rate, uint16_t baud_rate,
         uint8_t width, uint8_t height>
uint8_t Display<TxPin, main_timer_rate, baud_rate, width,
                height>::scan_position_last_write_;

template<typename TxPin, uint16_t main_timer_rate, uint16_t baud_rate,
         uint8_t width, uint8_t height>
uint8_t Display<TxPin, main_timer_rate, baud_rate, width, height>::blink_;

template<typename TxPin, uint16_t main_timer_rate, uint16_t baud_rate,
         uint8_t width, uint8_t height>
uint8_t Display<TxPin, main_timer_rate, baud_rate, width, height>::blink_clock_;

template<typename TxPin, uint16_t main_timer_rate, uint16_t baud_rate,
         uint8_t width, uint8_t height>
uint8_t Display<TxPin, main_timer_rate, baud_rate, width,
                height>::cursor_position_;

template<typename TxPin, uint16_t main_timer_rate, uint16_t baud_rate,
         uint8_t width, uint8_t height>
uint8_t Display<TxPin, main_timer_rate, baud_rate, width, height>::status_;

}  // namespace hardware_hal

#endif   // HARDWARE_HAL_DEVICES_SPARKFUN_SER_LCD_H_
