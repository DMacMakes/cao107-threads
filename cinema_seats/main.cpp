//////////////////////////////////////////////////////////////////////////////
//
//  CAO107 LAB 2 - Cinema seats
//
//  You run a local cinema in Ultimo. It's become so popular that your 
//  single box office sales person is smashed with orders, and you've 
//  installed 6 new registers, all staffed, to allow up to six
//  customers to buy seats at the same time. Now you can sell six times
//  as many tickets, time to get PAID.
//
//  Are things ever that simple though?
//  
//  THE CODE:
//
//  We have five cinema seats, G1-G5, and six customers. Each customer
//  is represented by the order they'd like to place; some want a single
//  seat, some want three. Some customer's orders can easily block
//  another's: If G1 and G3 are sold, the dude looking for G2 and G3 is out
//  of luck. 
//
//  THE PROGRAM SO FAR: 
// 
//  1. Shows the seats and their availability : green yes, red no.
//  2. Shows the customers waiting
//  3. Handles the orders one by one, in sequence, displaying the outcome
//  4. Displays all completed orders (that were stored in ordersCompleted)
//  5. Shows tickets sold.
//  6. Works great.
//
//T YOUR TASKS
//  1. Deploy your six new staff! That is: change from a single seller 
//     (sellSeats function) to multiple sellers (threads). This is almost
//     identical to our quicksort threading solution.
//  2. Run the program a bunch of times and observe! Do any issues emerge?
//     Does the seat availability chart match up with the orders completed?
//     Check for any problems with allocation: will everyone who was sold
//     tickets be happy? Take a SCREENSHOT of your output whenever you see
//     a problem, and write a clear description of the problem.
//  3. For each problem you've identified:
//     1. What do you think was the cause of this problem? Provide detail
//        beyond "threads did it". How did they cause the problem?
//     2. You're going to keep all six sales people, and customers are going
//        going to still be served in parallel, but small changes to the 
//        process can be made. What changes would you make to solve each problem?
//        Think about this in plain english in terms of how you'd handle the 
//        problem of several people selling from the same pool of products. 
//    3.  Refer to chapter 3 of Concurrency In Action. (See CAO107 Resources
//        page on my class notes, DMDOCS). What general type of parallel
//        programming features does C++ offer that we can use to handle 
//        these "race condition" problems?
//    4.  Write some pseudo code (basically shortened, plain english code 
//        to fix each problem, without having to use the proper syntax
//        of C++. You don't need to show the whole program, just the areas
//        you need real changes. See a pseudocde sample below in TIPS.
//        Here's an eg:
//        for each order
//          print out the order in colour
//          if all the seats are available
//            print "SOLD!" 
//            mark the order complete
//            put a copy of it in orders Completed collection
//            mark the seat unavailable
//          otherwise
//              print "unavailable"
//          end if
//        end for
//
//  TIPS: 
//  * Look in `structures.h` to see what makes up a `Seat` or an `Order`.
//  * Colours are defined in `colornames.h`
//  * Here's an eg of some PSEUDOCODE describing part of sellSeats:
//
//    for each order
//      print out the order in colour
//      if all the seats are available
//        print "SOLD!" 
//        mark the order complete
//        put a copy of it in orders Completed collection
//        mark the seat unavailable
//      otherwise
//          print "unavailable"
//      end if
//    end for
//////////////////////////////////////////////////////////////////////////////

#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <mutex>
#include "colornames.h"
#include "structures.h"
#include "chrono"
using namespace std;
// Need available movie seats
// Need booking system to attempt to book them
// 5 cashiers can be asked to make bookings
// It returns a result telling you if you succeeded, and what tickets you got.
// Tickets are dispensed to 
vector<Order> ordersCompleted;
mutex outLock;
mutex orderLock;

bool sellSeats(Order& order, vector<Seat>& seats)
{
  this_thread::sleep_for(500ms);
  //outLock.lock();
  cout << white << order.color << order.custName << white << on_black;
  //outLock.unlock();
  // if the seats in the order aren't already sold, mark them sold and return true
  bool allAvailable{ true };
  // Go through the order. If the seat 
  for (auto& seatId : order.seatIds)
  {
    for (auto& seat : seats)
    {
      // If we find the seat and it's not available, order is ded.
      if (seat.id == seatId && !seat.available)
      {
        //outLock.lock();
        cout << ": unavailable D:\n";
        //outLock.unlock();
        allAvailable = false;
        break;
      }
    }
  }
  if (allAvailable)
  {
    //outLock.lock();
    cout << ": Sold!\n";
    //outLock.unlock();
    order.sold = true;
    ordersCompleted.push_back(order);
    // oh boy, we sure wasted some time there before marking the seats
    // unavailable. What could go wrong?
    for (auto& seatId : order.seatIds)
    {
      for (auto& seat : seats)
      {
        if (seat.id == seatId) seat.available = false;
      }
    }
  }
  return allAvailable;
}

void printOrder(Order& order)
{
  outLock.lock();
  cout << white << order.color << order.custName << white << on_black << ", seats: [";
  for (auto& seatId : order.seatIds)
  {
    cout << seatId << " ";
  }
  cout << "\b]\n";   // backspace removes the space after the last seat id
  outLock.unlock();
}

void showSeats(vector<Seat>& seats)
{
  cout << "\n" << "## Seat Availability" << "\n\n";
  int seatCount = seats.size();
  string line = "-";
  for (auto i = 0; i < seatCount; ++i)
  {
    line += "-----";
  }

  //cout << line << endl;
  for (auto& seat : seats)
  {
    // If the seat is available, use green background, else red
    // if this syntax looks weird, google "universal initializers" and
    // "c++ ternary operator"
    string bg{ (seat.available) ? on_green : on_red };
    cout << "|" << white << bg << " " << seat.id << " " << white_on_black;
  }
  cout << "|" << endl;
  //cout << line << endl;
}
// LIST OF SEATS AVAILABLE
// LIST OF TICKETS SOLD
// 5 cashiers = threads
// 1 cashier can do all the work in a loop
// It gets crazy for the cashiers.

int main()
{
  auto orders = vector<Order>{
    { "Cust 1", on_red, {"G1", "G2"}},
    { "Cust 2", on_blue, {"G1"}},
    { "Cust 3", on_green, {"G4", "G5"}},
    { "Cust 4", on_yellow,  {"G5"}}, // potential disruptor here
    { "Cust 5", on_magenta, {"G4"}},
    { "Cust 6", on_cyan,  {"G3", "G4"}}  // Another cheeky one
  };

  auto seats = vector<Seat>{
    { "G1", true },
    { "G2", true },
    { "G3", true },
    { "G4", true },
    { "G5", true },
  };

  cout << "\n" << "## Customers Enter" << "\n\n";
  for (auto& order : orders)
  {
    printOrder(order);
  }
  showSeats(seats);

  cout << "\n" << "## Sales Begin" << "\n\n";
  for (Order& order : orders)
  {
    sellSeats(order, seats);
  }

  cout << "\n" << "## Successful Orders" << "\n\n";
  for (auto& order : ordersCompleted)
  {
    printOrder(order);
  }

  showSeats(seats);
}
