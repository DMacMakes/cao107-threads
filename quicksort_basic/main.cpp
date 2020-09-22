#include <iostream>
#include <string>
#include <array>
#include <chrono>
#include <cmath>
#include "Timer.h"
using namespace std;

bool quicksort(int* numbers, int left, int right)
{
  // Choose right as starting pivot
  int pivot = right;
  // Is left bigger than pivot?
  for (int i = 0; i < right; i++)
  {
	  numbers[i] = sqrt(numbers[i]);
  }

  cout << "\t Doing 100K sqrts\n";
  float wango=22020303.0f;
  for (int i=0; i<100'000; i++)
  {
    wango = sqrtf(wango);
  }
  // Call yerself
  // if(left != right)
  // quicksort(numbers,left,pivot-1);
  // quicksort(numbers,pivot+1,right);
  return true;
}

void displayArray(int* theArray, int length)
{
	cout << "\t>>>> LIST [";
	for (int i = 0; i < length; i++)
	{
		cout << theArray[i];
		if (i < length - 1) cout << ",";
	}
	cout << "]\n";
}

int main()
{
  // Make an array of ints
  const int LIST_LENGTH = 13;
  int sortMe[LIST_LENGTH]{20, 4, 1, 15, 9, 2, 24, 22, 8, 14, 5, 5, 7};

  cout << "\n";
  displayArray(sortMe, LIST_LENGTH);
  cout << "\n";

  dmac::Timer timer;
  timer.start();
  quicksort(sortMe, 0, LIST_LENGTH);
  timer.stop();
  
  cout << "\n";
  displayArray(sortMe, LIST_LENGTH);
  cout << "\n";

  cout << "\n\t-----------------------------------------\n";
  cout << "\t#######   quicksort time: " << timer.timeTakenMilli() << " milliseconds   ######\n";
  cout << "\t-----------------------------------------\n";

  //cout << "Hi bro, nice qs" << endl;
}
