#include <iostream>
#include <string>
#include <array>
#include <chrono>
#include <cmath>
#include "Timer.h"
using namespace std;

// Selects a pivot int in the provided range and places 
// lower ints to left, higher ints to right.
int choosePivotAndPartition(int* numbers, int left, int right);

// Use the quicksort algorithm to sort ints given:
// 1. The address of a basic c array in memory
// 2. The left index of the section of array we're sorting
// 3. The right index of the section.
bool quicksortInts(int* numbers, int left, int right);

// Sort a basic c array of integers provided:
// 1. the start of the array and 2. the number of ints.
void sortIntsAscending(int* integers, int size);
void displayArray(int* theArray, int length);

int main()
{
  // Make an array of ints
  const int LIST_LENGTH = 17;
  int randomInts[LIST_LENGTH]{13, 4, 20, 15, 13, 9, 2, 17, 1, 24, 22, 8, 14, 5, 13, 5, 7};

  cout << "\n";
  displayArray(randomInts, LIST_LENGTH);
  cout << "\n";

  dmac::Timer timer;
  timer.start();
  sortIntsAscending(randomInts, LIST_LENGTH);
  timer.stop();
  
  cout << "\n";
  displayArray(randomInts, LIST_LENGTH);
  cout << "\n";

  cout << "\n\t-----------------------------------------\n";
  cout << "\t#######   quicksort time: " << timer.timeTakenMilli() << " milliseconds   ######\n";
  cout << "\t-----------------------------------------\n";

  //cout << "Hi bro, nice qs" << endl;
}

void sortIntsAscending(int* integers, int size)
{
	bool success = quicksortInts(integers, 0, size - 1);

}

bool quicksortInts(int* numbers, int left, int right)
{
	// If our left and right indicies haven't finally collided 
	int pivot = 0;
	int pivotIndex = 0;
	if (left < right)
	{
		// Split the collection, sort the left and right sides.
		pivotIndex = choosePivotAndPartition(numbers, left, right);
		// Call quicksort on segment left of the pivot
		quicksortInts(numbers, left, pivotIndex - 1);
		// Do the sam on right.
		quicksortInts(numbers, pivotIndex + 1, right);
	}

	return true;
}

int choosePivotAndPartition(int* numbers, int left, int right)
{
	// Choose the left most number as the pivot.
	// The left wall, the last known place we moved a lower-than-pivot number.
	// Starts out as 
	int pivotValue = numbers[left];
	int leftWall = left;

	for (int i = leftWall + 1; i <= right; i++)
	{
		// Beginning at a point right of the wall, check if the number there
		// is less than the pivot. if so swap them and move the left wall forward,
		// collecting smaller numbers in safety.
		// The pivot will be pushed out ahead on the first swap to position wall+1
		if (numbers[i] < pivotValue)
		{
			// save the tasty small number
			int subPivotValue = numbers[i];
			// swap it whatever is right of the wall.
			numbers[i] = numbers[leftWall + 1];
			numbers[leftWall + 1] = subPivotValue;
			leftWall += 1;	// Move the wall to gobble up the nice low value.
		} // else left wall stands still while i marches on looking for a new lower than pivot value.

	}
	// Finally the left wall is our last found smaller-than-pivot value, and
	// everything to the right of it is pivot sized or higher. Our first value though,
	// at numbers[low] still holds the pivot value. Swap the two and the left wall spot
	// now holds the pivot (followed by values equal to or higher than it), and numbers[low]
	// holds a smaller value
	int subPivotValue = numbers[leftWall];
	numbers[left] = subPivotValue;
	numbers[leftWall] = pivotValue;
	return leftWall;
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