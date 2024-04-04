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
        bool answer = false;

        if (m_order.empty())
        {
            return answer;
        }
        if (!m_order.front().isItemFilled(getItemName()) && getQuantity() == 0)
        {
            g_incomplete.push_back(std::move(m_order.front()));
            answer = true;
        }
        // if the item is not suppose to handle here or here cannot handle this
        // if the way to verify if the station item is the same as the first order's order
        if (m_order.front().isItemFilled(getItemName()))
        {
            if (m_pNextStation != nullptr)
            {
                *m_pNextStation += std::move(m_order.front());
                //  I think the better design would be this only return true the order is finished
                answer = true;
                // m_order.pop_front();
            }
            else if (m_order.front().isOrderFilled())
            {
                g_completed.push_back(std::move(m_order.front()));
                answer = true;
            }
        }
        // if there's next station
        // if there's no next station

        // if there's a next station and the order is not filled and the order which the station provide is not filled move to the next station
        // if (m_pNextStation != nullptr && !m_order.front().isOrderFilled() && m_order.front().isItemFilled(getItemName()))
        // {
        //     *m_pNextStation += std::move(m_order.front());
        //     answer = true;
        // }
        // // not sufficient amount of item but there's next station
        // else if (getQuantity() == 0 || m_pNextStation == nullptr)
        // {
        //     g_incomplete.push_back(std::move(m_order.front()));
        //     answer = true;
        // }
        // else if (m_order.front().isOrderFilled())
        // {
        //     g_completed.push_back(std::move(m_order.front()));
        //     answer = true;
        // }

        if (answer)
        {
            m_order.pop_front();
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
        m_order.push_back(std::move(newOrder));

        return *this;
    }
}
