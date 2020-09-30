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

struct Order
{
  string custName;
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
  cout << "\tcustomer: " << order.custName << ", seats: ";
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
    { "red1",   {"G1", "G2", "G3"}},
    { "green2", {"G4", "G5"}},
    { "blue3",  {"G3", "G4"}},
    { "yellow4",{"G1", "G2", "G3"}},
    { "pink5",  {"G2","G3","G4"}},
    { "grey6",  {"G2","G3"}},
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
