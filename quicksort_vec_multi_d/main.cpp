#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Timer.h"
using namespace std;

int loadRandsFile(vector<int>& destination, string fileName);
bool writeRandsFile(vector<int>& randsArray, string filename);
void swap(int& left, int& right);

// Sort a basic c array of integers into ascending order provided:
// 1. Start of the array and 2. Size of the array
void sortIntArray(vector<int>& numbers);
// Quicksort a portion (or all of) a list of ints
// right: The right end of our array portion
void quicksort(vector<int>& numbers, int start, int end);
// Used by quicksortInts: chooses pivot number, moves lower numbers left, higher numbers right
int partition(vector<int>& numbers, int start, int end);

int main()
{
  int listsCount = 4;         // How many lists would you like to load and sort?
  int listLength = 100'000;   // How many numbers are in each list?
  vector<vector<int>> randlists(listsCount);
  
  cout << "\n\t == Lists to sort: " << listsCount << " ==\n";
  cout << "\t == Random numbers in each list: " << listLength << " ==\n\n";
  cout << "\t [ Loading randoms from text files... ]\n\n";

  //Allocate some nice big vectors and load 100K randoms into each
  for (int i = 0; i < listsCount; i++)
  {
    randlists[i] = (vector<int>(listLength,0));  // create 100,000 integer array
    // Load 100,000 random numbers from a text file into the vector
    loadRandsFile(randlists[i], "../randoms/100K_rands_uint16_" + to_string(i) + ".txt");
  }
  cout << "\t Beginning sort\n";
  // Create a precision timer and start timing
  dmac::Timer timer;
  timer.start();
  // Sorts our lists
  for (int i = 0; i < listsCount; i++)
  {
    sortIntArray(randlists[i]);
  }
  timer.stop();

  cout << "\t ---------------------------------------\n";
  cout << "\t Lists sorted! \n";
  cout << "\t Total sort time: " << timer.timeTakenMilli() << " milliseconds \n";
  cout << "\t ---------------------------------------\n";
  writeRandsFile(randlists[0], "rands0_out.txt");
}

int loadRandsFile(vector<int>& destination, string fileName)
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

bool writeRandsFile(vector<int>& randsArray, string fileName)
{
  ofstream randsFile;
  randsFile.open(fileName, ios::out);
  // Take each int from randsArray and dump it in randsFile
  for (int rand : randsArray)
  {
    randsFile << rand << endl;
  }
  randsFile.close();
  return true;
}

// Kick off quicksort for an array of integers
void sortIntArray(vector<int>& numbers)
{
  quicksort(numbers, 0, numbers.size()-1);
}

void quicksort(vector<int>& numbers, int start, int end)
{
  // If our left and right indicies haven't finally collided 
  int pivotIndex = 0;
  if (start < end)
  {
    // Picks a number in (part of the) array and moves all 
    // smaller numbers left, all larger numbers right. 
    pivotIndex = partition(numbers, start, end);
    // Recursively call self for left and right sides until array is sorted.
    quicksort(numbers, start, pivotIndex - 1);
    quicksort(numbers, pivotIndex + 1, end);
  }
}

int partition(vector<int>& numbers, int left, int right)
{
  // Choose the left most number as the pivot.
  int pivotValue = numbers[left];
  int leftWall = left;  // Set up a wall always at latest lower-than-pivot-value index
  for (int i = leftWall + 1; i <= right; i++)
  {
    if (numbers[i] < pivotValue)
    {
      // Swap the small number with the large one next to the wall 
      swap(numbers[i], numbers[leftWall + 1]);
      leftWall += 1;	// Move the wall to gobble up the nice low value.
    } 
  }
  // Swap original pivot (first item in list) with small number at wall
  swap(numbers[leftWall], numbers[left]);
  return leftWall;
}

void swap(int& left, int& right)
{
  int temp = left;
  left = right;
  right = temp;
}
