#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"
namespace seneca
{
    // holds the orders to be placed onto the assembly line at the first station.
    extern std::deque<CustomerOrder> g_pending;
    // holds the orders that have been removed from the last station and have been completely filled.
    extern std::deque<CustomerOrder> g_completed;
    // holds the orders that have been removed from the last station and could not be filled completely.
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        // – is a double-ended-queue with CustomerOrders entering the back and exiting the front. These are orders that have been placed on this station to receive service (or already received service).
        std::deque<CustomerOrder> m_order{};

        // a pointer to the next Workstation on the assembly line.
        Workstation *m_pNextStation{};

    public:
        // a custom 1-argument constructor -- receives a reference to an unmodifiable reference to std::string and passes it to the Station base class.
        Workstation(const std::string &str) : Station(str){};
        // delete all copy and move operators
        Workstation(const Workstation &other) = delete;
        Workstation(Workstation &&other) = delete;
        Workstation &operator=(const Workstation &other) = delete;
        Workstation &operator=(Workstation &&other) = delete;
        // this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing.
        void fill(std::ostream &os);

        // attempts to move the order order at the front of the queue to the next station in the assembly line:
        bool attemptToMoveOrder();

        // this modifier stores the address of the referenced Workstation object in the pointer to the m_pNextStation. Parameter defaults to nullptr.
        void setNextStation(Workstation *station = nullptr) { m_pNextStation = station; };
        Workstation *getNextStation() const { return m_pNextStation; }
        void display(std::ostream &os) const;
        Workstation &operator+=(CustomerOrder &&newOrder);
    };
}
#endif //! WORKSTATION_H