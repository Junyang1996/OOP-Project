// Name: Lawrence Wan
// Seneca Student ID: 105442230
// Seneca email:jwan27@myseneca.ca
// Date of completion: March 11, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
using namespace std;
namespace seneca
{
    size_t Station::m_widthField = 0;
    int Station::id_generator = 0;
    Station::Station(const string &str)
    {
        Utilities utilities;
        size_t pos = 0;
        bool more = false;
        // try
        // {
        itemName = utilities.extractToken(str, pos, more);
        m_serialNumber = stoul(utilities.extractToken(str, pos, more));
        quantity = stoul(utilities.extractToken(str, pos, more));
        m_widthField = std::max(utilities.getFieldWidth(),m_widthField);
        description = utilities.extractToken(str, pos, more);
        

        id = ++id_generator;
        // }
        // catch (...)
        // {
        //     throw std::runtime_error("Failed to extract token.");
        // }
    }
    void Station::updateQuantity()
    {
        if (quantity > 0)
            quantity--;
        else
            throw "quantity should be more or equal to 1.";
    }
    void Station::display(std::ostream &os, bool full) const
    {
        if (!full)
        {
            os << setw(3) << setfill('0') << right << id << " | " << setfill(' ') << left << setw(Station::m_widthField) << getItemName() << " | " << setw(6) << setfill('0') << right << m_serialNumber << " | " << endl;
        }
        else
        {
            os << setw(3) << setfill('0') << right << id << " | " << setfill(' ') << left << setw(m_widthField) << getItemName() << " | " << setw(6) << setfill('0') << right << m_serialNumber << " | " << setw(4) << setfill(' ') << getQuantity() << " | " << description << endl;
        }
    }
}
