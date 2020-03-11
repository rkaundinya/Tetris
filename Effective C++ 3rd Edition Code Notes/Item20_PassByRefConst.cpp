/*
You want to pass by ref const to most functions unless the parameter being passed is an STL or 
built in type. It's usually less efficient to pass by const reference in those two scenarios 
because of calling a copy constructor, there being a lot of data to copy, and that the objects may 
be resizable and therefore change in size

But it's a good idea for all other cases, helps with inheritance because derived classes can get 
sliced if they're copied by value instead of reference (remember reference behaves like a pointer)
*/

#include <iostream>

// Window is a class, not defined here that is a base class for various types of windows
class Window;

void printNameAndDisplay(const Window& w)
{
    std::cout << w.name();
    w.display();
}