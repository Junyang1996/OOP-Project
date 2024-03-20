// Name: Lawrence Wan
// Seneca Student ID: 105442230
// Seneca email:jwan27@myseneca.ca
// Date of completion: March 11, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <string>
namespace seneca
{
    class Station
    {
        int id{};
        std::string itemName{};
        std::string description{};
        size_t m_serialNumber{};
        size_t quantity{};
        static size_t m_widthField;
        static int id_generator;

    public:
        Station(const std::string &);
        const std::string &getItemName() const { return itemName; };
        size_t getNextSerialNumber() { return m_serialNumber++; };
        size_t getQuantity() const { return quantity; };
        void updateQuantity();
        void display(std::ostream &os, bool full) const;
    };
}
#endif //! SENECA_STATION_H