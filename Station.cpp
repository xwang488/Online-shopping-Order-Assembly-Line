
// Name: Jennifer Wang
// Seneca Student ID:169554219
// Seneca email: xwang488@myseneca.ca
// Date of completion:12/1/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<iostream>
#include<cstring>
#include<string>
#include <iomanip>
#include"Station.h"
#include"Utilities.h"
using namespace std;

namespace sdds
{

   size_t Station::m_widthField{};

   size_t Station::id_generator{};

   Station::Station(const std::string& record) {

      size_t pos = 0;
      bool more = true;
      Utilities temp;
      m_id = ++id_generator;
      try {
         m_name = temp.extractToken(record, pos, more);
         next_serial_number = stoi(temp.extractToken(record, pos, more));
         m_item = stoi(temp.extractToken(record, pos, more));
         Station::m_widthField = Station::m_widthField > temp.getFieldWidth() ? 
         Station::m_widthField : temp.getFieldWidth();
        
        // Station::m_widthField = Station::m_widthField > temp.getFieldWidth() ? Station::m_widthField : temp.getFieldWidth();
         m_description = temp.extractToken(record, pos, more);
      }
      catch (std::invalid_argument& e) {
         throw e;
      }
   }

   const std::string& Station::getItemName() const {
      return  m_name;
   }


   size_t Station::getNextSerialNumber() {

      return next_serial_number++;

   }
   size_t Station::getQuantity() const {
      return  m_item;
   }
   void Station::updateQuantity() {
      if (m_item >= 1) {
         m_item--;
      }
   }
   void Station::display(std::ostream& os, bool full) const {
      
      os << setw(3) << setfill('0') << right << m_id << " | "
         << setw(m_widthField) << setfill(' ') << left << getItemName() << "  | "
         << setw(6) << setfill('0') << right << next_serial_number << " | ";
         
      if (full) {
         os << setw(4) << setfill(' ') << right << getQuantity()
            << " | " << m_description;
      }
      os << endl;

   }
}