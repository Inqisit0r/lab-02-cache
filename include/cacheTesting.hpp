// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_CACHETESTING_HPP_
#define INCLUDE_CACHETESTING_HPP_

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

#define STEP 16
#define ZERO std::chrono::nanoseconds::zero()

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::nanoseconds ns;
typedef std::chrono::duration<float> diffFloat;

struct researchTimes {
  uint8_t tempValue;
  ns time;
};

/* cache_sizes['1'] = 256 KB
 * cache_sizes['2'] = 1024 KB
 * cache_sizes['3'] = 6144 KB
 * 128 KB < 256 KB < 1024 KB < 6144 KB < 9216 KB
 */

auto example() -> void;

void frontResearch(const uint8_t* in, size_t inSize, researchTimes* times);

void reverseResearch(const uint8_t* in, size_t inSize, researchTimes* times);

void randomResearch(const uint8_t* in, size_t inSize, researchTimes* times);

void experiment(size_t bufferSize, size_t number, researchTimes* times);

void formatPrint();

#endif // INCLUDE_CACHETESTING_HPP_
