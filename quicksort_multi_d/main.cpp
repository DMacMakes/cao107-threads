// QuickSort_file_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

int loadRandsFile(uint16_t* destination, string fileName);
bool quickSort(uint16_t* toSort, int leftIndex, int rightIndex, int pivot);
LONGLONG qpfElapsedMicroseconds(const LARGE_INTEGER& start, const LARGE_INTEGER& end);
float microToMilliseconds(int microSeconds);

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

    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);

    for (int i = 0; i < listCount; i++)
    {
        quickSort(randlists[i], 0, listLength - 1, listLength - 1);
    }
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);

    LONGLONG elapsedMicroseconds = qpfElapsedMicroseconds(startTime, endTime);

    float elapsedMilliseconds = microToMilliseconds(elapsedMicroseconds);
    cout << "\n\t TIME TAKEN\n";
    cout << "\t ------------------\n";
    cout << "\t " << elapsedMicroseconds << " microseconds \n";
    cout << "\t " << elapsedMilliseconds << " milliseconds \n";

    return 0;
}

LONGLONG qpfElapsedMicroseconds(const LARGE_INTEGER& start, const LARGE_INTEGER& end)
{
    LARGE_INTEGER ticksPerSecond;
    QueryPerformanceFrequency(&ticksPerSecond);         // Find the speed of the counter
    LARGE_INTEGER ticksElapsed;
    ticksElapsed.QuadPart = end.QuadPart - start.QuadPart;

    LARGE_INTEGER microsecondsElapsed;
    microsecondsElapsed.QuadPart = ticksElapsed.QuadPart * 1'000'000;
    microsecondsElapsed.QuadPart /= ticksPerSecond.QuadPart;

    return microsecondsElapsed.QuadPart;
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
        toSort[i] = static_cast<uint16_t>(std::roundf(std::sqrtf(toSort[i])));
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

float microToMilliseconds(int microseconds)
{
    return static_cast<float>(microseconds) / 1000.0f;
}

