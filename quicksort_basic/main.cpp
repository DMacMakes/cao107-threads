#include <iostream>
#include <string>
#include <array>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;

bool quicksort(int* numbers, int left, int right)
{
  // Choose right as starting pivot
  int pivot = right;
  // Is left bigger than pivot?
  cout << "\t *sort sort wow a million sqrts eh?*\n";
  float wango=22020303.0f;
  for (int i=0; i<150000; i++)
  {
    wango = sqrt(wango);
  }
  cout << "\t Bye wango: " << wango << endl;
  // Call yerself
  // if(left != right)
  // quicksort(numbers,left,pivot-1);
  // quicksort(numbers,pivot+1,right);
  return true;
}

int main()
{
  high_resolution_clock::time_point start = high_resolution_clock::now();
  // Make an array of ints
  int sortMe[13]{20, 4, 1, 15, 9, 2, 24, 22, 8, 14, 5, 5, 7};

  // Display them
  quicksort(sortMe, 0,12);
  // display them
  high_resolution_clock::time_point end = high_resolution_clock::now();
  auto timeTaken = end - start;
  auto millis = duration_cast<milliseconds>(timeTaken);
  cout << "quicksort ran in " << millis.count() << " ms";
	//cout << "Hi bro, nice qs" << endl;
}
