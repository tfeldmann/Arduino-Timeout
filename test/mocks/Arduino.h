#pragma once
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"

#define HIGH 0x1
#define LOW 0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL 0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define LED_BUILTIN 13

#undef abs  // undefine stdlib's functions if encountered
#undef max  // dont use math.h versions
#undef min  // dont use math.h versions

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(x) ((x) > 0 ? (x) : -(x))
#define constrain(amt, low, high) \
    ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
#define round(x) ((x) >= 0 ? (long)((x) + 0.5) : (long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x) * (x))

#define lowByte(w) ((uint8_t)((w)&0xff))
#define highByte(w) ((uint8_t)((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) \
    (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define bit(b) (1UL << (b))

typedef bool boolean;
typedef uint8_t byte;

uint16_t makeWord(unsigned int w) { return w; }
uint16_t makeWord(unsigned char h, unsigned char l) { return (h << 8) | l; }
#define word(...) makeWord(__VA_ARGS__)

uint32_t current_time = 0;

void pinMode(uint8_t pin, uint8_t mode)
{
    printf(BLUE "pinMode: %d is now %d\n" RESET, pin, mode);
}

int analogRead(int pin)
{
    printf(BLUE "Reading pin %d\n" RESET, pin);
    return 0;
}

void digitalWrite(int pin, int val)
{
    printf(BLUE "Setting pin %d to %s\n" RESET, pin, val ? "HIGH" : "LOW");
}

bool digitalRead(int pin)
{
    printf(BLUE "Reading pin %d\n" RESET, pin);
    return true;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void _advance_ms(uint32_t dt) { current_time += dt; }

unsigned long millis() { return current_time; }

void delay(unsigned long ms)
{
    printf("delay(%lu)\n", ms);
    _advance_ms(ms);
}
