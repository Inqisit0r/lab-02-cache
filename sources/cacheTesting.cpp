// Copyright 2021 Your Name <your_email>

#include "cacheTesting.hpp"

/* cache_sizes['1'] = 256 KB
 * cache_sizes['2'] = 1024 KB
 * cache_sizes['3'] = 6144 KB
 * 128 KB < 256 KB < 1024 KB < 6114 KB < 9171 KB
 */

using namespace std;

auto example() -> void
{
  throw std::runtime_error("not implemented");
}

void frontResearch(const uint8_t* in, size_t inSize, researchTimer* timer)
{
  for (size_t i = 0; i < inSize; i += STEP)
  {
    timer->tempValue = in[i];
  }

  auto startPoint = Time::now();

  for (size_t i = 0; i < 1000; i++)
  {
    for (size_t j = 0; j < inSize; j += STEP)
    {
      timer->tempValue = in[j];
    }
  }

  auto stopPoint = Time::now();
  diffFloat diff = startPoint - stopPoint;
  timer->frontTimer = chrono::duration_cast<ms>(abs(diff / 1000));
}

void reverseResearch(const uint8_t* in, size_t inSize, researchTimer* timer)
{
  for (size_t i = 0; i < inSize; i += STEP)
  {
    timer->tempValue = in[i];
  }

  auto startPoint = Time::now();

  for (size_t i = 0; i < 1000; i++)
  {
    for (size_t j = 0; j < inSize; j += STEP)
    {
      timer->tempValue = in[inSize - j];
    }
  }

  auto stopPoint = Time::now();
  diffFloat diff = startPoint - stopPoint;
  timer->reversTimer = chrono::duration_cast<ms>(abs(diff / 1000));
}

void randomResearch(const uint8_t* in, size_t inSize, researchTimer* timer)
{
  for (size_t i = 0; i < inSize; i += STEP)
  {
    timer->tempValue = in[i];
  }

  size_t counter = inSize / STEP;

  vector<int> index(inSize);
  for (size_t i = 0; i < counter; i++)
  {
    index[i] = static_cast<int>(i * STEP);
  }

  diffFloat diff;
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(1,6);

  for (size_t i = 0; i < 1000; i++)
  {
    random_shuffle(index.begin(), index.end());

    auto startPoint = Time::now();
    for (size_t j = 0; j < counter; j++)
    {
      timer->tempValue = in[index[j]];
    }
    auto stopPoint = Time::now();
    diff += startPoint - stopPoint;
//    cout << i << endl;
  }

  timer->randomTimer = chrono::duration_cast<ms>(abs(diff / 1000));
}