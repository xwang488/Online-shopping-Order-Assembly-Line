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
#include"Utilities.h"

using namespace std;

namespace sdds

{

   char Utilities::m_delimiter {};

   void  Utilities::setFieldWidth(size_t newWidth) {
      m_widthField = newWidth;
   }
   size_t  Utilities::getFieldWidth() const {
      return m_widthField;
   }
   std::string  Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
      int del;
      string answer{};
      if (str[next_pos] == m_delimiter) {
         more = false;
         throw - 1;
      }
      else {
         string temp{};
         temp = str.substr(next_pos);
         if ((del = temp.find_first_of(m_delimiter)) != -1) {
            answer = temp.substr(0, del);
            trim(answer);
            next_pos = next_pos+ del + 1;
            more = true;
         }
         else {
            answer = temp;
            trim(answer);
            more = false;
         }
      }
      if (m_widthField < answer.length()) {
         m_widthField = answer.length();
      }

      return answer;

   }
   void  Utilities::setDelimiter(char newDelimiter) {
      m_delimiter = newDelimiter;
   }
   char  Utilities::getDelimiter() {
      return m_delimiter;
   }
   void Utilities::trim(std::string& str) {
      if (str.length() > 0) {
         int begin = str.find_first_not_of(' ');
         size_t end = str.find_last_not_of(' ');
         if (begin == -1) str = "";
         else {
            str = str.substr(begin, end - begin + 1);
         }
      }
   }
}