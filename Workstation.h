// Name: Jennifer Wang
// Seneca Student ID:169554219
// Seneca email: xwang488@myseneca.ca
// Date of completion:12/1/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H_
#define SDDS_WORKSTATION_H_
#include<iostream>
#include<cstring>
#include<string>
#include <deque>
#include"CustomerOrder.h"
#include"Station.h"

namespace sdds
{
   extern std::deque<CustomerOrder> g_pending;
   extern std::deque<CustomerOrder> g_completed;
   extern std::deque<CustomerOrder> g_incomplete;

   class Workstation: public Station
   {
      std::deque<CustomerOrder> m_orders{};
      Workstation* m_pNextStation{nullptr};
   public:
      Workstation(const std::string& str);
      void fill(std::ostream& os);
      bool attemptToMoveOrder();
      void setNextStation(Workstation* station);
      Workstation* getNextStation() const;
      void display(std::ostream& os) const;
      Workstation& operator+=(CustomerOrder&& newOrder);
      ~Workstation();
      Workstation(const Workstation& w) = delete;
      Workstation& operator=(const Workstation& w) = delete;
      Workstation(Workstation&& w) = delete;
      Workstation& operator=(Workstation && w) = delete;
      //std::ostream& operator<<(std::ostream& os, const Streamable& OR);
     // std::istream& operator>>(std::istream& is, Streamable& OR);
  
   };
   
}
#endif
