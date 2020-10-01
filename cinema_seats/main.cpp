#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
// Need available movie seats
// Need booking system to attempt to book them
// 5 cashiers can be asked to make bookings
// It returns a result telling you if you succeeded, and what tickets you got.
// Tickets are dispensed to 

const string red = "\033[31m";
const string white = "\033[37m";
const string green = "\033[32m";
const string yellow = "\033[33m";
const string blue = "\033[34m";
const string magenta = "\033[35m";
const string cyan = "\033[36m";
const string on_grey = "\033[40m";

struct Order
{
  string custName;
  string color;
  vector<string> seatIds;
};
vector<Order> ordersCompleted;

struct Seat
{
  string id;
  bool available {true};
};

void handleOrder(Order& order)
{
  cout << "Handling order for " << order.custName << "\n";
  ordersCompleted.push_back(order);
}

void printOrder(Order& order)
{
  cout << "Order: \n";
  cout << "\tcustomer: " << order.color << order.custName << white << ", seats: ";
  for ( auto& seatId : order.seatIds )
  {
    cout << seatId << " ";
  }
  cout << "\n";
}

// LIST OF SEATS AVAILABLE
// LIST OF TICKETS SOLD
// 5 cashiers = threads
// 1 cashier can do all the work in a loop
// It gets crazy for the cashiers.

int main()
{
  auto orders = vector<Order> { 
    { "Cust 1", red, {"G1", "G2", "G3"}},
    { "Cust 2", blue, {"G4", "G5"}},
    { "Cust 3", green,  {"G3", "G4"}},
    { "Cust 4", yellow, {"G1", "G2", "G3"}},
    { "Cust 5", magenta,  {"G2","G3","G4"}},
    { "Cust 6", cyan,  {"G2","G3"}},
    };

  auto seats = vector<Seat> {
    { "G1", true },
    { "G2", true },
    { "G3", true },
    { "G4", true },
    { "G5", true },
  };

  cout << "Orders ready to fly: " << orders.size() << "\n";

  // Try doing it on after another, with one cashier.
  vector<thread> threads;
  for ( Order& order : orders )
  {
    threads.push_back( thread(handleOrder, ref(order) ));
  }

  for ( thread& thread : threads)
  {
    thread.join();
  }

  cout << "Orders completed: \n";
  for ( auto& order: ordersCompleted)
  {
    printOrder(order);
  }

  return 0;
}
