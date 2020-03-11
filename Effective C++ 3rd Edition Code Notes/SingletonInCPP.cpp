/*
Good design pattern for implementing a singleton in C++.
Note, constructor is private because you don't want anyone outside of the class implementation to 
be able to create an instance of the singleton. Copy constructor is marked with delete so that 
you cannot create a new singleton and assign the return from get to it thereby creating two singletons. 
Another way to combat this would be to simply make the copy constructor private.

Don't need to bother with copy assignment operator because that only runs when assigning one instantiated
object of a type to another and because the constructor is private, you cannot create a new Singleton object
that would then invoke a copy assignment.
*/

#include <iostream>

class Singleton
{
    public:
        // This works or can simply declare this in private and take out delete 
        Singleton(const Singleton&) = delete;

        static Singleton& Get()
        {
            return s_Instance;
        }

        void Function() {}

    private: 
        Singleton() {}
        
        // This also works to prevent copy constructing
        // Singleton(const Singleton&);

        static Singleton s_Instance;
};


// In a cpp file implementation of this Singleton, you would define the s_Instance somewhere in it
// and then you could call Get from main or anywhere else and use that singleton
Singleton Singleton::s_Instance;

int main()
{
    Singleton::Get().Function();
}