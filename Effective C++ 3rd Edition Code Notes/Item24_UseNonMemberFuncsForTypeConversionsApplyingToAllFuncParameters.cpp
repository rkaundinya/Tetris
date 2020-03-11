/*
Like my riduculously long title says, use non-member functiosn when you need 
a function to be able to take parameters of multiple types. Good example is a rational fraction class
which takes ints for numerator and denominator and implementing a operator* overload for this class. 
*/

#include <iostream>

class Rational
{
    public: 
        // Note this is not implemented explicitly because we want to allow for implicit type conversions
        // when operator* is called and somebody inputs only an integer
        Rational(int numerator = 0, int denominator = 1) : 
            numerator(numerator), denominator(denominator) {}
        
        int getNumerator() const
        {
            return numerator;
        }

        int getDenominator() const
        {
            return denominator;
        }

    private: 
        int numerator;
        int denominator;
};

std::ostream &operator<<(std::ostream &output, const Rational &rhs)
{
    output << rhs.getNumerator() << " " << rhs.getDenominator();
    return output;
}

const Rational operator*(const Rational& lhs, const Rational&rhs)
{
    return Rational(lhs.getNumerator() * rhs.getNumerator(), 
        lhs.getDenominator() * rhs.getDenominator());
}

int main()
{
    Rational oneFourth(1,4);
    std::cout << oneFourth << std::endl;
    Rational result;

    result = oneFourth * 2;
    std::cout << result << std::endl;
    result = 2 * oneFourth;
    std::cout << result << std::endl;
}