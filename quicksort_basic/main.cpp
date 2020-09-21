#include <iostream>
#include <string>
#include <array>
using namespace std;

bool quicksort(int* numbers, int left, int right)
{
  // Choose right as starting pivot
  int pivot = right;
  // Is left bigger than pivot?
  cout << "\t *sort sort*\n";

  // Call yerself
  // if(left != right)
  // quicksort(numbers,left,pivot-1);
  // quicksort(numbers,pivot+1,right);
  return true;
}

int main()
{
  // Make an array of ints
  int sortMe[13]{20, 4, 1, 15, 9, 2, 24, 22, 8, 14, 5, 5, 7};


  // Display them
  quicksort(sortMe, 0,12);
  // display them
	//cout << "Hi bro, nice qs" << endl;
}
