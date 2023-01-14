// Name: Jennifer Wang
// Seneca Student ID:169554219
// Seneca email: xwang488@myseneca.ca
// Date of completion:12/1/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H_
#define SDDS_STATION_H_
#include<iostream>
#include<cstring>
#include<string>
namespace sdds
{
   class Station
   {
      size_t m_id{};
      std::string m_name{};
      std::string m_description{};
      size_t next_serial_number{};
      size_t m_item{};
      static size_t m_widthField;
      static size_t id_generator;
   public:
      Station(const std::string& record);
      const std::string& getItemName() const;
      size_t getNextSerialNumber();
      size_t getQuantity() const;
      void updateQuantity();
      void display(std::ostream& os, bool full) const;

   };
}
#endif
