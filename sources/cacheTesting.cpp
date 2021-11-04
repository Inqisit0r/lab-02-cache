// Copyright 2021 Your Name <your_email>

#include "cacheTesting.hpp"

/* cache_sizes['1'] = 256 KB
 * cache_sizes['2'] = 1024 KB
 * cache_sizes['3'] = 6144 KB
 * 128 KB < 256 KB < 1024 KB < 6114 KB < 9171 KB
 */

static unsigned int seed = 54321;

auto example() -> void
{
  throw std::runtime_error("not implemented");
}

void frontResearch(const uint8_t* in, size_t inSize, researchTimes* times)
{
  for (size_t i = 0; i < inSize; i += STEP)
  {
    times->tempValue = in[i];
  }

  auto startPoint = Time::now();

  for (size_t i = 0; i < 1000; i++)
  {
    for (size_t j = 0; j < inSize; j += STEP)
    {
      times->tempValue = in[j];
    }
  }

  auto stopPoint = Time::now();
  diffFloat diff = startPoint - stopPoint;
  times->time = std::chrono::duration_cast<ns>(abs(diff / 1000));
}

void reverseResearch(const uint8_t* in, size_t inSize, researchTimes* times)
{
  for (size_t i = 0; i < inSize; i += STEP)
  {
    times->tempValue = in[i];
  }

  auto startPoint = Time::now();

  for (size_t i = 0; i < 1000; i++)
  {
    for (size_t j = 0; j < inSize; j += STEP)
    {
      times->tempValue = in[inSize - j];
    }
  }

  auto stopPoint = Time::now();
  diffFloat diff = startPoint - stopPoint;
  times->time = std::chrono::duration_cast<ns>(abs(diff / 1000));
}

void randomResearch(const uint8_t* in, size_t inSize, researchTimes* times)
{
  for (size_t i = 0; i < inSize; i += STEP)
  {
    times->tempValue = in[i];
  }

  size_t counter = inSize / STEP;

  std::vector<int> index(inSize);
  for (size_t i = 0; i < counter; i++)
  {
    index[i] = static_cast<int>(i * STEP);
  }

  diffFloat diff;
  for (size_t i = 0; i < 1000; i++)
  {
    random_shuffle(index.begin(), index.end());

    auto startPoint = Time::now();
    for (size_t j = 0; j < counter; j++)
    {
      times->tempValue = in[index[j]];
    }
    auto stopPoint = Time::now();
    diff += startPoint - stopPoint;
  }

  times->time = std::chrono::duration_cast<ns>(abs(diff / 1000));
}

void experiment(size_t bufferSize, size_t number, researchTimes* times)
{
  std::cout << "\t- experiment:\n" << "\t\tnumber: " << number << std::endl
       << "\t\tinput_data:\n" << "\t\t\tbuffer_size: " << bufferSize << " byte"
       << std::endl << "\t\tresults:\n" <<  "\t\t\tduration: "
       << times->time.count() << " ns" << std::endl;
}

void formatPrint()
{
  size_t bufferSizes[] = { 131072, 262144, 1048576, 6291456, 9437184 };
  researchTimes times = { 0, ZERO };

  std::cout << "investigation:\n" << "\ttravel_variant: front\n"
       << "\texperiments:" << std::endl;

  for (size_t i = 0; i < 5; i++)
  {
    auto* array = static_cast<uint8_t*>(malloc(bufferSizes[i]));
    for (size_t j = 0; j < bufferSizes[i]; j++)
    {
      array[j] = rand_r(&seed) % 128;
    }
    frontResearch(array, bufferSizes[i], &times);
    experiment(bufferSizes[i], i + 1, &times);
    if (array)
    {
      free(array);
    }
  }

  std::cout << "\ttravel_variant: reverse\n"
       << "\texperiments:" << std::endl;

  for (size_t i = 0; i < 5; i++)
  {
    auto* array = static_cast<uint8_t*>(malloc(bufferSizes[i]));
    for (size_t j = 0; j < bufferSizes[i]; j++)
    {
      array[j] = rand_r(&seed) % 128;
    }
    reverseResearch(array, bufferSizes[i], &times);
    experiment(bufferSizes[i], i + 1, &times);
    if (array)
    {
      free(array);
    }
  }

  std::cout << "\ttravel_variant: random\n"
       << "\texperiments:" << std::endl;

  for (size_t i = 0; i < 5; i++)
  {
    auto* array = static_cast<uint8_t*>(malloc(bufferSizes[i]));
    for (size_t j = 0; j < bufferSizes[i]; j++)
    {
      array[j] = rand_r(&seed) % 128;
    }
    randomResearch(array, bufferSizes[i], &times);
    experiment(bufferSizes[i], i + 1, &times);
    if (array)
    {
      free(array);
    }
  }
}
