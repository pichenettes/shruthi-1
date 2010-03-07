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
// A set of basic operands, especially useful for fixed-point arithmetic, with
// fast ASM implementations.

#ifndef HARDWARE_UTILS_OP_H_
#define HARDWARE_UTILS_OP_H_

#include "hardware/base/base.h"

namespace hardware_utils_op {
  
static inline int16_t Clip(int16_t value, int16_t min, int16_t max) {
  return value < min ? min : (value > max ? max : value);
}

static inline uint8_t AddClip(uint8_t value, uint8_t increment, uint8_t max) {
  value += increment;
  if (value > max) {
    value = max;
  }
  return value;
}

#ifdef USE_OPTIMIZED_OP

static inline uint8_t Clip8(int16_t value) {
  uint8_t result;
  asm(
    "mov %0, %A1"   "\n\t"  // by default, copy the value.
    "or %B1, %B1"   "\n\t"  // load H to set flags.
    "brpl .+4"      "\n\t"  // if positive, skip
    "ldi %0, 0"     "\n\t"  // set to 0.
    "rjmp .+4"      "\n\t"  // and jump.
    "breq .+2"      "\n\t"  // if null, skip
    "ldi %0, 255"   "\n\t"  // set to 255
    : "=r" (result)
    : "a" (value)
  );
  return result;  
}

static inline int8_t SignedClip8(int16_t value) {
  return Clip8(value + 128) + 128;  
}

static inline uint8_t Mix(uint8_t a, uint8_t b, uint8_t balance) {
  Word sum;
  asm(
    "mul %3, %2"      "\n\t"  // b * balance
    "movw %A0, r0"    "\n\t"  // to sum
    "com %2"          "\n\t"  // 255 - balance
    "mul %1, %2"      "\n\t"  // a * (255 - balance)
    "com %2"          "\n\t"  // reset balance to its previous value
    "add %A0, r0"     "\n\t"  // add to sum L
    "adc %B0, r1"     "\n\t"  // add to sum H
    "eor r1, r1"      "\n\t"  // reset r1 after multiplication
    : "&=r" (sum)
    : "a" (a), "a" (balance), "a" (b)
    );
  return sum.bytes[1];
}


static inline uint8_t Mix4(uint8_t a, uint8_t b, uint8_t balance) {
  uint16_t sum;
  asm(
    "mul %2, %1"      "\n\t"  // b * balance
    "movw %A3, r0"    "\n\t"  // to sum
    "com %1"          "\n\t"  // 255 - balance
    "subi %1, 240"    "\n\t"  // 15 - balance
    "mul %0, %1"      "\n\t"  // a * (15 - balance)
    "subi %1, 16"     "\n\t"
    "com %1"          "\n\t"  // reset balance to its previous value
    "add %A3, r0"     "\n\t"  // add to sum L
    "adc %B3, r1"     "\n\t"  // add to sum H
    "eor r1, r1"      "\n\t"  // reset r1 after multiplication
    "andi %B3, 15"    "\n\t"  // keep 4 lowest bits of H
    "andi %A3, 240"   "\n\t"  // keep 4 highest bits of L 
    "or %B3, %A3"     "\n\t"  // copy 4 high bits of L to H -> LLLLHHHH
    "swap %B3"        "\n\t"  // swap to get HHHHLLLL
    "mov %0, %B3"     "\n\t"  // move to output
    : "=r" (a)
    : "a" (balance), "a" (b), "a" (sum)
    );
  return a;
}

static inline uint16_t UnscaledMix4(uint8_t a, uint8_t b, uint8_t balance) {
  uint16_t sum;
  asm(
    "mul %3, %2"      "\n\t"  // b * balance
    "movw %A0, r0"    "\n\t"  // to sum
    "com %2"          "\n\t"  // 255 - balance
    "subi %2, 240"    "\n\t"  // 15 - balance
    "mul %1, %2"      "\n\t"  // a * (15 - balance)
    "subi %2, 16"     "\n\t"
    "com %2"          "\n\t"  // reset balance to its previous value
    "add %A0, r0"     "\n\t"  // add to sum L
    "adc %B0, r1"     "\n\t"  // add to sum H
    "eor r1, r1"      "\n\t"  // reset r1 after multiplication
    : "&=r" (sum)
    : "a" (a), "a" (balance), "a" (b)
    );
  return sum;
}

static inline uint8_t ShiftLeft4(uint8_t a) {
  uint8_t result;
  asm(
    "mov %0, %1"      "\n\t"
    "swap %0"         "\n\t"
    "andi %0, 240"     "\n\t"
    : "=r" (result)
    : "a" (a)
    );
  return result;
}

static inline uint8_t Swap4(uint8_t a) {
  uint8_t result;
  asm(
    "mov %0, %1"      "\n\t"
    "swap %0"         "\n\t"
    : "=r" (result)
    : "a" (a)
    );
  return result;
}

static inline uint8_t ShiftRight4(uint8_t a) {
  uint8_t result;
  asm(
    "mov %0, %1"      "\n\t"
    "swap %0"         "\n\t"
    "andi %0, 15"     "\n\t"
    : "=r" (result)
    : "a" (a)
    );
  return result;
}

static inline uint8_t MulScale8(uint8_t a, uint8_t b) {
  uint8_t result;
  asm(
    "mul %1, %2"      "\n\t"
    "mov %0, r1"      "\n\t"
    "eor r1, r1"      "\n\t"
    : "=r" (result)
    : "a" (a), "a" (b)
  );
  return result;
}

static inline int8_t SignedMulScale8(int8_t a, uint8_t b) {
  uint8_t result;
  asm(
    "mulsu %1, %2"    "\n\t"
    "mov %0, r1"      "\n\t"
    "eor r1, r1"      "\n\t"
    : "=r" (result)
    : "a" (a), "a" (b)
  );
  return result;
}

static inline int16_t SignedUnsignedMul(int8_t a, uint8_t b) {
  int16_t result;
  asm(
    "mulsu %1, %2"    "\n\t"
    "movw %0, r0"      "\n\t"
    "eor r1, r1"      "\n\t"
    : "=r" (result)
    : "a" (a), "a" (b)
  );
  return result;
}

static inline uint16_t UnsignedUnsignedMul(uint8_t a, uint8_t b) {
  uint16_t result;
  asm(
    "mul %1, %2"    "\n\t"
    "movw %0, r0"      "\n\t"
    "eor r1, r1"      "\n\t"
    : "=r" (result)
    : "a" (a), "a" (b)
  );
  return result;
}

static inline int8_t SignedSignedMulScale8(int8_t a, int8_t b) {
  uint8_t result;
  asm(
    "muls %1, %2"    "\n\t"
    "mov %0, r1"      "\n\t"
    "eor r1, r1"      "\n\t"
    : "=r" (result)
    : "a" (a), "a" (b)
  );
  return result;
}

static inline uint16_t Mul16Scale8(uint16_t a, uint16_t b) {
  uint16_t result;
  uint32_t product;
  asm(
    "mul %A2, %A3"    "\n\t"
    "movw %A1, r0"    "\n\t"
    "mul %B2, %B3"    "\n\t"
    "movw %C1, r0"    "\n\t"
    "mul %B3, %A2"    "\n\t"
    "add %B1, r0"     "\n\t"
    "adc %C1, r1"     "\n\t"
    "eor r1, r1"      "\n\t"
    "adc %D1, r1"     "\n\t"
    "mul %B2, %A3"    "\n\t"
    "add %B1, r0"     "\n\t"
    "adc %C1, r1"     "\n\t"
    "eor r1, r1"      "\n\t"
    "adc %D1, r1"     "\n\t"
    "mov %A0, %B1"    "\n\t"
    "mov %B0, %C1"    "\n\t"
    : "=r" (result), "=&r" (product)
    : "a" (a), "a" (b)
  );
  return result;
}

// The code generated by gcc for >> 6 is short but uses a loop. This saves
// a couple of cycles.
static inline uint8_t ShiftRight6(int16_t value) {
  uint8_t result;
  asm(
    "asr %B1"       "\n\t"
    "ror %A1"       "\n\t"
    "asr %B1"       "\n\t"
    "ror %A1"       "\n\t"
    "andi %B1, 0x0f""\n\t"
    "andi %A1, 0xf0""\n\t"
    "or %B1, %A1"   "\n\t"
    "swap %B1"      "\n\t"
    "mov %0, %B1"   "\n\t"
    : "=r" (result)
    : "a" (value)
  );
  return result;  
}

#else

static inline uint8_t Clip8(int16_t value) {
  return value < 0 ? 0 : (value > 255 ? 255 : value);
}

static inline int8_t SignedClip8(int16_t value) {
  return value < -128 ? -128 : (value > 127 ? 127 : value);
}

static inline uint8_t Mix(uint8_t a, uint8_t b, uint8_t balance) {
  return a * (255 - balance) + b * balance >> 8;
}

static inline uint8_t Mix4(uint8_t a, uint8_t b, uint8_t balance) {
  return a * (15 - balance) + b * balance >> 4;
}

static inline uint8_t UnscaledMix4(uint8_t a, uint8_t b, uint8_t balance) {
  return a * (15 - balance) + b * balance;
}

static inline uint8_t ShiftRight4(uint8_t a) {
  return a >> 4;
}

static inline uint8_t ShiftLeft4(uint8_t a) {
  return a << 4;
}

static inline uint8_t Swap4(uint8_t a) {
  return (a << 4) | (a >> 4);
}

static inline uint8_t MulScale8(uint8_t a, uint8_t b) {
  return a * b >> 8;
}

static inline int8_t SignedMulScale8(int8_t a, uint8_t b) {
  return a * b >> 8;
}

static inline int16_t SignedUnsignedMul(int8_t a, uint8_t b) {
  return a * b;
}

static inline uint16_t UnsignedUnsignedMul(uint8_t a, uint8_t b) {
  return a * b;
}

static inline int8_t SignedSignedMulScale8(int8_t a, int8_t b) {
  return a * b >> 8;
}

static inline uint16_t Mul16Scale8(uint16_t a, uint16_t b) {
  return static_cast<uint32_t>(a) * b >> 8;
}

static inline uint8_t ShiftRight6(uint16_t value) {
  return value >> 6;
}
  
#endif  // USE_OPTIMIZED_OP

}  // namespace hardware_utils_op

#endif  // HARDWARE_UTILS_OP_H_