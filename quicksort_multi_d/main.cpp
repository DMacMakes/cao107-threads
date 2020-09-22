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

int main()
{
    int listCount = 6;
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
        quickSort(randlists[i], 0, listLength - 1, listLength - 1);
    }
    timer.stop();

    cout << "\n\t TIME TAKEN\n";
    cout << "\t ------------------\n";
    cout << "\t " << timer.timeTakenMilli() << " milliseconds \n";
    return 0;
}

bool quickSort(uint16_t* toSort, int leftIndex, int rightIndex, int pivot)
{
    cout << "\t *sorting* \n";
    /*
    cout << "\t first 10: ";
    
    for (int i = 0; i < 10; i++)
    {
        cout << toSort[i] << " ";
    }
    cout << "\n";
    */
    for (int i = 0; i <= rightIndex; i++)
    {
        // Square root each number to use up some clock.
        toSort[i] = static_cast<uint16_t>(std::round(std::sqrt(toSort[i])));
    }
    return true;
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
