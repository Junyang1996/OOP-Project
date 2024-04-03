// Name: Lawrence Wan
// Seneca Student ID: 105442230
// Seneca email:jwan27@myseneca.ca
// Date of completion: March 11, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <string>
namespace seneca
{
    class Utilities
    {
        size_t m_widthField = 1;
        static char m_delimiter;
        static std::string object;

    public:
        std::string trim(const std::string &str);
        // std::string extract_string(const std::string &str, const char delimiter);
        void setFieldWidth(size_t newWidth) { m_widthField = newWidth; }
        size_t getFieldWidth() const { return m_widthField; }
        std::string extractToken(const std::string &str, size_t &next_pos, bool &more);

        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
}

#endif //! SENECA_UTILITIES_H