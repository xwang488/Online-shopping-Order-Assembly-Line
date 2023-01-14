
// Name: Jennifer Wang
// Seneca Student ID:169554219
// Seneca email: xwang488@myseneca.ca
// Date of completion:12/1/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include<vector>
#include<fstream>
#include <algorithm>
#include <string>
#include"LineManager.h"
#include"Utilities.h"

using namespace std;
namespace sdds
{
   LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
      ifstream f(file);
      string temp{}, itemname{}, from{}, to{};
      size_t pos{0};
      bool more{ true };
      Utilities ut;
      ut.setDelimiter('|');
      vector<Workstation*> first;
      while (!f.eof()) {
         getline(f, temp);
         pos = 0;
         more =true;
         itemname = ut.extractToken(temp, pos, more);
         Workstation* ws{};
         ws = *(find_if(stations.begin(), stations.end(), [&](Workstation* wosn) {return wosn->getItemName() == itemname;}));
         m_activeLine.push_back(ws);
         first.push_back(ws);
      }

      f.seekg(0, ios::beg);
      while (!f.eof()) {
         getline(f, temp);
         pos = 0;
         more = true;
         from = ut.extractToken(temp, pos, more);
         if (more) {
            Workstation* fromws, * tows;
            to = ut.extractToken(temp, pos, more);
            tows = *(find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* wosn) {return wosn->getItemName() == to;}));
            auto x = remove(first.begin(), first.end(), tows);
            first.erase(x);
            // first.erase(x,first.end());
            fromws = *(find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* wosn) {return wosn->getItemName() == from;}));

            fromws->setNextStation(tows);
         }

      }

      m_cntCustomerOrder = g_pending.size();

      m_firstStation = first.front();
   }

   void LineManager::reorderStations() {
      std::vector<Workstation*> temp;
      Workstation* ws;
      temp.push_back(m_firstStation);
      while ((ws = temp.back()->getNextStation())) {
         temp.push_back(ws);
      }
      m_activeLine = temp;
   }
   bool LineManager::run(std::ostream& os) {
      static size_t count{};
      count++;
      os << "Line Manager Iteration: " << count << endl;
      if (!g_pending.empty()) {
         *m_firstStation += move(g_pending.front());
         g_pending.pop_front();
      }
      for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
         ws->fill(os);
         });
      for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
         ws->attemptToMoveOrder();
         });

      return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
   }
   void LineManager::display(std::ostream& os) const {
      for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
         ws->display(os);
         });
   }
}