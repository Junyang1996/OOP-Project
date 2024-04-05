// Name: Lawrence Wan
// Seneca Student ID: 105442230
// Seneca email:jwan27@myseneca.ca
// Date of completion: April 4 , 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Workstation.h"
namespace seneca
{
    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};
    void Workstation::fill(std::ostream &os)
    {
        if (!m_order.empty())
            m_order.front().fillItem(*this, os);
    }
    bool Workstation::attemptToMoveOrder()
    {
        if (m_order.empty())
        {
            return false;
        }
        // if the order is not been found in this station, or the station has no quantity to fill the item
        else if (m_order.front().isItemFilled(getItemName()) || getQuantity() == 0)
        {
            // if there's a next station
            if (getNextStation() != nullptr)
            {
                *m_pNextStation += std::move(m_order.front());
                m_order.pop_front();
                return true;
            }
            else
            {

                if (!m_order.front().isOrderFilled())
                {

                    g_incomplete.push_back(std::move(m_order.front()));
                    m_order.pop_front();
                    return true;
                }
                else
                {
                    g_completed.push_back(std::move(m_order.front()));
                    m_order.pop_front();
                    return true;
                }
            }
        }
        return false;
    }
    // {

    //     g_incomplete.push_back(std::move(m_order.front()));
    //     m_order.pop_front();
    //     return true;
    // }
    // if (m_pNextStation != nullptr && (getQuantity() == 0 || m_order.front().isItemFilled(getItemName())))
    // {

    //     *m_pNextStation += std::move(m_order.front());
    //     m_order.pop_front();
    //     return true;
    // }
    // else if (m_pNextStation == nullptr)
    // {
    //     if (m_order.front().isItemFilled(getItemName()))
    //     {
    //         g_completed.push_back(std::move(m_order.front()));
    //         m_order.pop_front();
    //         return true;
    //     }
    // }
    // return false;
    // if (!m_order.front().isItemFilled(getItemName()))
    // {
    //     if (getQuantity() == 0)
    //     {
    //         if (m_pNextStation != nullptr)
    //         {
    //             *m_pNextStation += std::move(m_order.front());
    //             m_order.pop_front();
    //             return true;
    //         }
    //         else
    //         {
    //             g_incomplete.push_back(std::move(m_order.front()));
    //             m_order.pop_front();
    //             return true;
    //         }
    //     }
    // }
    // else
    // {
    //     if (m_pNextStation != nullptr)
    //     {
    //         *m_pNextStation += std::move(m_order.front());
    //         m_order.pop_front();
    //         return true;
    //     }
    //     else
    //     {
    //         g_completed.push_back(std::move(m_order.front()));
    //         m_order.pop_front();
    //         return true;
    //     }
    // }

    // return false;

    void Workstation::display(std::ostream &os) const
    {
        os << getItemName() << " --> ";
        if (m_pNextStation != nullptr)
        {
            os << m_pNextStation->getItemName();
        }
        else
        {
            os << "End of Line";
        }
        os << std::endl;
    }

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {
        m_order.push_back(std::move(newOrder));

        return *this;
    }
}
