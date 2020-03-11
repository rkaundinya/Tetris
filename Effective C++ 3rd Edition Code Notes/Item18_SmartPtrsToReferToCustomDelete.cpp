/*
If you want a function to return a pointer and make it easily managable, return a smart pointer. 
Using shared is probably the best one to use (see Item13). Return shared_ptr from function
allows you to also tie a custom delete function for whatever object you're using shared_ptr to refer to.

So say you have an investment class and you want to return pointer to Investment, but investment has some 
resources for which you want to specify a custom delete function.Then you can do something like this:
*/

#include <memory>

class Investment;

std::shared_ptr<Investment> CreateIvestment()
{
    // Create the investment object and store it somewhere that is not local
    // Then you can include that investment pointer in your retVal to start with
    // But if you need to create the pointer after you've already defined the 
    // smart pointer that'll manage deletion (retVal) and store your created Investment, 
    // then you can initialize the shared_ptr to nullptr of Investment* like so:
    std::shared_ptr<Investment> retVal(static_cast<Investment*>(0), getRidOfInvestment);

    // getRidOfInvestment() is some custom deleter function. So you're storing a function pointer here
    // tied to that smart pointer
    return retVal;
}