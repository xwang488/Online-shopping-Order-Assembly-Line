// Name: Jennifer Wang
// Seneca Student ID:169554219
// Seneca email: xwang488@myseneca.ca
// Date of completion:12/1/2022
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<iostream>
#include<cstring>
#include<string>
#include <iomanip>
#include<vector>
#include"CustomerOrder.h"
#include"Station.h"
#include"Utilities.h"

using namespace std;
namespace sdds
{
   size_t CustomerOrder::m_widthField{ 0 };

	CustomerOrder::CustomerOrder() {};
	CustomerOrder::CustomerOrder(const std::string& str) {
		size_t pos = 0;
		bool more = true;
		Utilities uti;

		m_name = uti.extractToken(str, pos, more);
		m_product = uti.extractToken(str, pos, more);
		vector< Item*> tempVector;
		Item* tempItem;
		while (more) {
			tempItem = new Item(uti.extractToken(str, pos, more));
			tempVector.push_back(tempItem);
		}
		m_cntItem = tempVector.size();
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = tempVector[i];
		}
		CustomerOrder::m_widthField = CustomerOrder::m_widthField > uti.getFieldWidth() ? CustomerOrder::m_widthField : uti.getFieldWidth();
	};

	CustomerOrder::CustomerOrder(const CustomerOrder& Cu) {
		throw - 1;
	};

	CustomerOrder::CustomerOrder(CustomerOrder&& Cu) noexcept {
		*this = move(Cu);
	};

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& Cu) noexcept {
		if (this != &Cu) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];		
			} 
			delete [] m_lstItem;
			m_name = Cu.m_name;
			m_product = Cu.m_product;
			m_cntItem = Cu.m_cntItem;
			m_lstItem = Cu.m_lstItem;
			Cu.m_lstItem = nullptr;
			Cu.m_cntItem = 0;
		}
		return *this;	
	};

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}			
		delete [] m_lstItem;	
	};

	bool CustomerOrder::isOrderFilled() const {
		bool result = true;
		for (size_t i = 0; result && i < m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled == false) {
				result = false;
			}
		}
		return result;
	};

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool result = true;
		for (size_t i = 0; result && i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && m_lstItem[i]->m_isFilled == false) {
				result = false;
			}
		}
		return result;
	};

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool found = false;
		for (size_t i = 0; i < m_cntItem && !found; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() >= 1) {
					found = true;
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << setw(6) << setfill('0') << right << m_lstItem[i]->m_serialNumber << "] " 
				<< setw(m_widthField) <<left<< setfill(' ') << m_lstItem[i]->m_itemName << "   - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
	};


}