#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include <string>
namespace seneca
{

    class CustomerOrder
    {
        struct Item
        {
            std::string m_itemName{};
            size_t m_serialNumber{0};
            bool m_isFilled{false};

            Item(const std::string &src) : m_itemName(src){};
        };
        static size_t m_widthField;
        // the name of the customer (e.g., John, Sara, etc)
        std::string m_name{};
        // the name of the product being assembled (e.g., Desktop, Laptop, etc)
        std::string m_product{};
        //  a count of the number of items in the customer's order
        size_t m_cntItem{};
        // a dynamically allocated array of pointers. Each element of the array points to a dynamically allocated object of type Item (see below). This is the resource that your class must manage.
        Item **m_lstItem{};

    public:
        CustomerOrder();
        CustomerOrder(std::string &);
        CustomerOrder(const CustomerOrder &other)
        {
            throw std::invalid_argument("No copy constructor");
        }
        CustomerOrder &operator=(const CustomerOrder &) = delete;
        CustomerOrder(CustomerOrder &&) noexcept;
        CustomerOrder &operator=(CustomerOrder &&) noexcept;
        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string &itemName) const;
        void fillItem(Station &station, std::ostream &os);
        void display(std::ostream &os) const;
    };
}
#endif //! CUSTOMERORDER_H
