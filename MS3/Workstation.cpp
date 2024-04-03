#include <iostream>
#include "Workstation.h"
namespace seneca
{
    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};
    void Workstation::fill(std::ostream &os)
    {
        if (!m_order.front().isItemFilled(getItemName()))
            m_order.front().fillItem(*this, os);
    }
    bool Workstation::attemptToMoveOrder()
    {
        bool answer = false;
        // if the order is not filled
        if (!m_order.front().isOrderFilled())
        {
            // if the order requires no more service at this station or cannot be filled (not enough inventory),
            if (m_order.front().isItemFilled(getItemName()) || getQuantity() == 0)
            {
                if (m_pNextStation != nullptr)
                {

                    *m_pNextStation += std::move(m_order.front());
                    answer = true;
                }
                else
                {
                    g_incomplete.push_back(std::move(m_order.front()));
                    answer = true;
                }
            }
        }
        // if the order is filled
        else
        {
            g_completed.push_back(std::move(m_order.front()));
            answer = true;
        }
        return answer;
    }
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
        m_order.push_back(newOrder);
        return *this;
    }
}