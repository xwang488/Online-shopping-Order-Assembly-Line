
// Name: Jennifer Wang
// Seneca Student ID:169554219
// Seneca email: xwang488@myseneca.ca
// Date of completion:12/1/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H_
#define SDDS_UTILITIES_H_
#include<iostream>
#include<cstring>
#include<string>
namespace sdds
{
   class Utilities
   {
      size_t m_widthField{ 1 };
      static char m_delimiter;
   public:
      void setFieldWidth(size_t newWidth);
      size_t getFieldWidth() const;
      std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
      static void setDelimiter(char newDelimiter);
      static char getDelimiter();
      void trim(std::string& str);

   };
}



#endif