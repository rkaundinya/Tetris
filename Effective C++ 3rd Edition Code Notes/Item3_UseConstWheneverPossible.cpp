/*
You should use const whenever possible because it makes sure code behaves the right way 
in all scenarios. And there are a lot of scenarios you may not immediately think of that might come up
for which you'll be thankful you put a const in somewhere even if it doesn't seem like you need it at the moment.
*/

#include <cstddef>
#include <cstring>
#include <string>

class Rational;

// Both of these declarations below (ones with const before the *), say that the pointer value
// CANNOT be reassigned. In other words the value the pointer is point to 
// CANNOT be reassigned, but the address in memory the pointer is pointing to CAN
// Read right to left as pInt is a pointer to constant ints
void f1 (const int* pInt);
void f2 (int const* pInt);

// Read right to left as pInt is a constant pointer to ints
// So, the value that pInt points to CAN be reassigned, but the pointer's address CANNOT
void f3 (int* const pInt);

// Result of operator overload should be constant, else you could do something like (a*b) = c
const Rational operator*(const Rational& lhs, const Rational& rhs);

/*
Mutable keyword lets you modify variables in a class from a const function. 
Useful in a scenario like what I'll show below
*/

class CTextBlock
{
    public:
        std::size_t length() const
        {
            if (!lengthIsValid)
            {
                textLength = std::strlen(pText);
                lengthIsValid = true;
            }
        }

    private: 
        char* pText;
        mutable std::size_t textLength;
        mutable bool lengthIsValid;
};

/*
To avoid code duplication for member functions which are essentially identical minus being labeled as const, 
you can use a const_cast to call the const version of the method in the non-const method and cast that result
back to a non-const reference. See below for example:
*/

class TextBlock
{
    public: 
        const char& operator[] (const std::size_t position) const
        {
            // Check that position is in bounds, check that stored string data is good, then...
            return text[position];
        }
        char& operator[](const std::size_t position)
        {
            return 
                // Cast away const on op[]'s return type, add cosnt to *this's type, 
                // call cosnt version of op[]
                const_cast<char&>(
                    static_cast<const TextBlock&>(*this)
                        [position]);
        }

    private: 
        std::string text;
};