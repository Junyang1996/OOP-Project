#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include <string>
#include "Station.h"

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
        // default constructor
        CustomerOrder();
        // a custom 1-argument constructor that takes a reference to an unmodifiable string.
        CustomerOrder(const std::string &);
        // object should not allow copy
        CustomerOrder(const CustomerOrder &other)
        {
            throw std::invalid_argument("No copy constructor");
        }
        // copy operator= should be deleted.
        CustomerOrder &operator=(const CustomerOrder &) = delete;

        // This constructor should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.
        CustomerOrder(CustomerOrder &&) noexcept;

        // a move assignment operator. This operator should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.
        CustomerOrder &operator=(CustomerOrder &&) noexcept;
        ~CustomerOrder();

        // bool isOrderFilled() const – returns true if all the items in the order have been filled; false otherwise
        bool isOrderFilled() const;

        // bool isItemFilled(const std::string& itemName) const – returns true if all items specified by itemName have been filled. If the item doesn't exist in the order, this query returns true.
        bool isItemFilled(const std::string &itemName) const;

        // this modifier fills one item in the current order that the Station specified in the first parameter handles.
        void fillItem(Station &station, std::ostream &os);

        // void display(std::ostream& os) const – this query displays the state of the current object in the format (see the sample output for details)
        void display(std::ostream &os) const;
    };
}
#endif //! SENECA_CUSTOMERORDER_H