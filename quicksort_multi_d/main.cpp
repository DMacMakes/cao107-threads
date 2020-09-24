// QuickSort_file_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "Timer.h"
using namespace std;

int loadRandsFile(uint16_t* destination, string fileName);
bool quickSort(uint16_t* toSort, int leftIndex, int rightIndex, int pivot);

// Selects a pivot int in the provided range and places 
// lower ints to left, higher ints to right.
int choosePivotAndPartition(uint16_t* numbers, int left, int right);

// Use the quicksort algorithm to sort ints given:
// 1. A c array of unsigned 16 bit ints.
// 2. The left index of the section of array we're sorting
// 3. The right index of the section.
bool quicksortInts(uint16_t* numbers, int left, int right);

// Sort a basic c array of integers provided:
// 1. the start of the array and 2. the number of ints.
void sortIntsAscending(uint16_t* integers, int size);

bool writeRandsFile(uint16_t* randsArray, int randCount, string filename);

int main()
{
    int listCount = 8;
    int listLength = 100'000;
    uint16_t** randlists = new uint16_t * [listCount];

    for (int i = 0; i < listCount; i++)
    {
        randlists[i] = new uint16_t[listLength];
        loadRandsFile(randlists[i], "randoms/100K_rands_uint16_" + to_string(i) + ".txt");
    }

    cout << "\n\t == lists to sort: " << listCount << " ==\n";
    cout << "\n\t == rands per list: " << listLength << " ==\n\n";

    dmac::Timer timer;

    timer.start();
    for (int i = 0; i < listCount; i++)
    {
        //quickSort(randlists[i], 0, listLength - 1, listLength - 1);
        sortIntsAscending(randlists[i], listLength);
    }
    timer.stop();

    cout << "\n\t TIME TAKEN\n";
    cout << "\t ------------------\n";
    cout << "\t " << timer.timeTakenMilli() << " milliseconds \n";
 //   writeRandsFile(randlists[0], listLength, "sorted_rands_1.txt");
    return 0;
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
    for (int i = 0; i < randCount -1; i++)
    {
        randsFile << randsArray[i] << endl;
    }
    randsFile.close();
    return true;
}

void sortIntsAscending(uint16_t* integers, int size)
{
    bool success = quicksortInts(integers, 0, size - 1);
}

bool quicksortInts(uint16_t* numbers, int left, int right)
{
    // If our left and right indicies haven't finally collided 
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
