/*
Return a newly created object when you need a function to do so, do not return a reference
to a locally created, heap allocated, or static object. Local will cause return value to be undefined
for anything storing its return, heap-allocated will cause there to be a memory leak because
delete will not be called within the function, and return a reference to a static object would not work
if you need to chain the return of that function with another return of that function both operating 
on one another e.g. operator==(operator*(a,b), operator*(c,d)). If there was a static variable for the operator
overload* that both operators were referencing, then you would not get two separate results you would be
using that same static variable twice.
*/

// Rational is a class here that stores rational number fractions (numerator and denominator)
class Rational;

inline const Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
}