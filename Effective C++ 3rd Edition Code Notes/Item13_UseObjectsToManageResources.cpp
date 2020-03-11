/*
Useful to have some sort of container that automatically deletes your data after
you no longer need it. That way you don't have to remember to call delete on everything
after you make it. Smart pointers are really useful here. Auto and shared pointers' destructors
automatically call delete on the objects they point to. 

When copying an Auto_ptr, the copied object will be set to null and the copying object will 
take over the copied one's resources. This makes it so that if an autoptr was deleted more than once, 
it won't be calling multiple destructors that would result in undefined behavior.

Shared pointer lets you have multiple pointers point to the same object, and it keeps track of how 
many reference to that same memory resource there are. Once there are 0 and the last shared_ptr has 
been deleted, then the destructor is called.

Note - std library implementations of autoptr and sharedptr will call delete and not delete[] 
in their destructors. So if you're using either of these to refer to an array, look at boost::shared_array or
boost::scoped::array

This code is an example of RAII or Resource Acquisition Is Initialization
*/

#include <memory>

class Investment;

Investment* createInvestment();

void f()
{
    // would need to remember to call delete if I used a regular pointer this way
    // Investment* pInv = createInvestment();

    // This way auto_ptr will call delete once the pointer is out of scope
    std::auto_ptr<Investment> pInv(createInvestment());
}

// So the better way is to use shared_ptr as your container and not auto_ptr. To see why
// read the last part of my header description

void f2()
{
    std::shared_ptr<Investment> pInv(createInvestment());
}