#include "cacheTesting.hpp"

using namespace std;

uint8_t a[9437184];

int main() {
  for(size_t i = 0; i < 9437184; i++)
  {
    a[i] = rand();
  }
  researchTimer timer = { 0, ZERO, ZERO, ZERO };
  frontResearch(a, 9437184, &timer);
  cout << "FrontResearch: " << timer.frontTimer.count() << " ns" << endl;
  reverseResearch(a, 9437184, &timer);
  cout << "ReverseResearch: " << timer.reversTimer.count() << " ns" << endl;
  randomResearch(a, 9437184, &timer);
  cout << "RandomResearch: " << timer.randomTimer.count() << " ns" << endl;
}