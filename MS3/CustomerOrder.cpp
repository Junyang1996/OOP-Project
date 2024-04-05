// Name: Lawrence Wan
// Seneca Student ID: 105442230
// Seneca email:jwan27@myseneca.ca
// Date of completion: April 4 , 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <string>
#include <utility>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
// #include "Station.h"
using namespace std;
namespace seneca
{
    size_t CustomerOrder::m_widthField = 0;
    CustomerOrder::CustomerOrder() = default;
    //     a custom 1-argument constructor that takes a reference to an unmodifiable string. This constructor uses a local Utilities object to extract the tokens from the string and populate the current instance. The fields in the string are (separated by a delimiter):

    // Customer Name
    // Order Name
    // the list of items making up the order (at least one item)
    // After finishing extraction, this constructor updates CustomerOrder::m_widthField if the current value is smaller than the value stored in Utilities::m_widthField.
    CustomerOrder::CustomerOrder(const std::string &line)
    {
        Utilities utilities;
        size_t pos{};
        bool more = false;

        m_name = utilities.extractToken(line, pos, more);
        m_product = utilities.extractToken(line, pos, more);

        do
        {
            Item **new_lstItem = new Item *[m_cntItem + 1];
            for (size_t i = 0; i < m_cntItem; ++i)
            {
                new_lstItem[i] = m_lstItem[i];
            }
            delete[] m_lstItem;

            new_lstItem[m_cntItem] = new Item(utilities.extractToken(line, pos, more));
            m_lstItem = new_lstItem;
            m_cntItem++;

        } while (more);

        m_widthField = std::max(m_widthField, utilities.getFieldWidth());
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&co) noexcept
    {
        *this = std::move(co);
    }
    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&co) noexcept
    {
        if (this != &co)
        {
            // clean the current m_lstItems
            if (m_lstItem != nullptr)
            {
                for (auto i = 0u; i < m_cntItem; i++)
                    delete m_lstItem[i]; // Delete each Item
                delete[] m_lstItem;      // Delete the array of Item pointers
            }

            m_name = std::move(co.m_name);
            m_product = std::move(co.m_product);
            m_cntItem = co.m_cntItem;
            m_lstItem = co.m_lstItem;

            // clean the other co
            co.m_name.clear();
            co.m_product.clear();
            co.m_cntItem = 0;
            co.m_lstItem = nullptr;
        }
        return *this;
    }
    CustomerOrder::~CustomerOrder()
    {
        m_name.clear();
        m_product.clear();

        for (auto i = 0u; i < m_cntItem; i++)
            delete m_lstItem[i]; // Delete each Item
        delete[] m_lstItem;      // Delete the array of Item pointers
        m_cntItem = 0;
    }
    bool CustomerOrder::isOrderFilled() const
    {
        for (auto i = 0u; i < m_cntItem; i++)
        {
            if (!m_lstItem[i]->m_isFilled)
                return false;
        }
        return true;
    }
    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        for (auto i = 0u; i < m_cntItem; i++)
        {

            // false only when the item is matching but it is not filled
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
                return false;
        }
        return true;
    }
    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {

        for (auto i = 0u; i < m_cntItem; i++)
        {
            // if the order contains items handled, and the Station's inventory contains at least one item, this function fills the order with one single item.
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled)
            {
                if (station.getQuantity() > 0)
                {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                    // only fill one item, once it found the right one, exist.
                    i = m_cntItem;
                }
                else if (station.getQuantity() == 0)
                    os << "Unable to filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
            }
        }
    }
    void CustomerOrder::display(std::ostream &os) const
    {
        os << m_name << " - " << m_product << endl;
        for (auto i = 0u; i < m_cntItem; ++i)
        {
            os << '[' << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] " << setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName << " - ";
            if (!m_lstItem[i]->m_isFilled)
            {
                os << "TO BE FILLED\n";
            }
            else
            {
                os << "FILLED\n";
            }
        }
    }
}
