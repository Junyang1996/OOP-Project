#include <string>
#include "CustomerOrder.h"

namespace seneca
{
    int m_widthField = 0;
    CustomerOrder::CustomerOrder()
    {
    }
    CustomerOrder::CustomerOrder(std::string &line)
    {
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&) noexcept
    {
    }
    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&) noexcept
    {
    }
    CustomerOrder::~CustomerOrder()
    {
    }
    bool CustomerOrder::isOrderFilled() const
    {
    }
    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
    }
    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {
    }
    void CustomerOrder::display(std::ostream &os) const
    {
    }
}