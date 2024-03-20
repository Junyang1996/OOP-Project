// Name: Lawrence Wan
// Seneca Student ID: 105442230
// Seneca email:jwan27@myseneca.ca
// Date of completion: March 11, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <string>
#include "Utilities.h"
using namespace std;
namespace seneca
{
    char Utilities::m_delimiter{};
    std::string Utilities::object{};
    string Utilities::trim(const string &str)
    {
        string output = str;
        // Find the index of the first non-whitespace character
        size_t firstNonWhitespace = output.find_first_not_of(' ');
        // Erase leading whitespace characters
        output.erase(0, firstNonWhitespace);
        // Find the index of the last non-whitespace character
        size_t lastNonWhitespace = output.find_last_not_of(' ');
        // Erase trailing whitespace characters
        if (lastNonWhitespace != string::npos)
            output.erase(lastNonWhitespace + 1);
        return output;
    }
    // string Utilities::extract_string(const string &str, const char delimiter)
    // {
    //     // find the index of the delimiter
    //     size_t index = str.find(delimiter);
    //     // return the trimed string until the delimiter
    //     return trim(str.substr(0, index));
    // }

    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
    {
        size_t end = str.find(m_delimiter, next_pos);
        // if the delimiter is at the end of the string or no found any
        if (end == std::string::npos)
        {
            end = str.length();
            // when the token is at the last part of the string
            more = false;
            //            throw std::invalid_argument("Empty token");
        }
        else
        {
            more = true;
        }

        std::string token = str.substr(next_pos, end - next_pos);
        if (token.empty())
        {
            next_pos = end + 1;
            // Update next_pos before throwing the exception
            // invalid, when the delimiter is found at the next pos
            more = false;
            throw("Empty token");
        }

        next_pos = end + 1;

        if (token.length() > m_widthField)
            m_widthField = token.length();

        return trim(token);
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }

}
