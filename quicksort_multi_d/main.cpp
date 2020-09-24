#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "Timer.h"
using namespace std;

int loadRandsFile(uint16_t* destination, string fileName);
bool writeRandsFile(uint16_t* randsArray, int randCount, string filename);

// Used by quicksortInts: chooses pivot number, moves lower numbers left, higher numbers right
int choosePivotAndPartition(uint16_t* numbers, int left, int right);

// Quicksort a portion (or all of) an array
// numbers: A c array of unsigned 16 bit ints. left: The left end of our array portion
// right: The right end of our array portion
void quicksort(uint16_t* numbers, int left, int right);

// Sort a basic c array of integers into ascending order provided:
// 1. Start of the array and 2. Size of the array
void sortIntArray(uint16_t* numbers, int size);

int main()
{
  int listsCount = 4;         // How many lists would you like to load and sort?
  int listLength = 100'000;   // How many numbers are in each list?
  // Create on small array of pointers, one for each list we'll load.
  // The size will equal listsCount. 
  uint16_t** randlists = new uint16_t * [listsCount];

  cout << "\n\t == Lists to sort: " << listsCount << " ==\n";
  cout << "\t == Random numbers in each list: " << listLength << " ==\n\n";
  cout << "\t [ Loading randoms from text files... ]\n\n";
  // Now create the big arrays, each one with enough memory to hold
  // `listLength` numbers. In this case, 100,000 short (16 bit) integers
  // Store the pointers to each array in "randlists".
  // Finally, load a text file for each array and fill it.
  for (int i = 0; i < listsCount; i++)
  {
    randlists[i] = new uint16_t[listLength];  // create 100,000 unsigned 16bit integer array
    // Load 100,000 random numbers from a text file into the array.
    loadRandsFile(randlists[i], "randoms/100K_rands_uint16_" + to_string(i) + ".txt");
  }

  // Create a precision timer and start timing
  dmac::Timer timer;
  timer.start();
  // Sorts our lists
  for (int i = 0; i < listsCount; i++)
  {
    //quickSort(randlists[i], 0, listLength - 1, listLength - 1);
    sortIntArray(randlists[i], listLength);
  }
  timer.stop();

  cout << "\t ---------------------------------------\n";
  cout << "\t Lists sorted! \n";
  cout << "\t Total sort time: " << timer.timeTakenMilli() << " milliseconds \n";
  cout << "\t ---------------------------------------\n";
}

int loadRandsFile(uint16_t* destination, string fileName)
{
  ifstream randsFile;
  string line;
  int lineCount = 0;
  randsFile.open(fileName, ios::in);
  while (getline(randsFile, line))
  {
    destination[lineCount] = atoi(line.c_str());
    lineCount += 1;
  }
  randsFile.close();
  return lineCount;
}

bool writeRandsFile(uint16_t* randsArray, int randCount, string fileName)
{
  ofstream randsFile;
  randsFile.open(fileName, ios::out);
  for (int i = 0; i < randCount - 1; i++)
  {
    randsFile << randsArray[i] << endl;
  }
  randsFile.close();
  return true;
}

// Kick off quicksort for an array of unsigned short integers
void sortIntArray(uint16_t* numbers, int size)
{
  quicksort(numbers, 0, size - 1);
}

void quicksort(uint16_t* numbers, int left, int right)
{
  // If our left and right indicies haven't finally collided 
  int pivotIndex = 0;
  if (left < right)
  {
    // Picks a number in (part of the) array and moves all 
    // smaller numbers left, all larger numbers right. 
    pivotIndex = choosePivotAndPartition(numbers, left, right);
    // Recursively call self for left and right sides until array is sorted.
    quicksort(numbers, left, pivotIndex - 1);
    quicksort(numbers, pivotIndex + 1, right);
  }
}

int choosePivotAndPartition(uint16_t* numbers, int left, int right)
{
  // Choose the left most number as the pivot.
  // The left wall, the last known place we moved a lower-than-pivot number.
  // Starts out as 
  auto pivotValue = numbers[left];
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
      auto subPivotValue = numbers[i];
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
  auto subPivotValue = numbers[leftWall];
  numbers[left] = subPivotValue;
  numbers[leftWall] = pivotValue;
  return leftWall;
}
