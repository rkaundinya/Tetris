/*
Try to avoid casting, especially dynamic casting in performance sensitive code. 
When you need to cast, try and hide the cast in a function so clients call a function instead
of putting casts in their code. 
Use C++ style casts over old-style casts.

Main C++ style casts and use cases: 

const_cast - used to cast away the cosntness of stuff. We saw this in the code that used const copy constructor
code in defining non const copy constructor code. 
dynamic_cast - used mainly to perform safe dwoncasting i.e. determine if an object is of a particular type
in an inheritance hierarchy. Only cast that might have significant runtime cost.
reinterpret_cast - used for low-level casts that give implementation-dependent (i.e. unportable) results 
like casting a pointer to an int. These are rare casts outside low-level code, book uses it in Item50 
when writing a debugging allocator for raw memory.
static_cast - used fo force implicit conversions (non-const to const, int to double, etc.). Can also 
perform casts in reverse directions e.g. void* to typed pointer, pointer to base to pointer to derived. Can't
be used to cast from const to non-const (only const_cast can do that)
*/

#include <vector>
#include <memory>

int x, y;

// Possible use case of static_cast
double d = static_cast<double>(x)/y;

/*
static_cast returns a temporary object if you use a method on a static_cast. That method 
would then be invoked on the temporary object instead of a newly generate object. 
This can cause errors like calling a function on a temporary object base class and on the current object's
class. So a temporary base class object was initialized with that function and only the derived part of the
current object used the function call causing the current object to be in an undefined state
where modifications to the base class have not been made, but modifications to the derived class have.
*/

class Window
{
    public:
        virtual void onResize() {}
};

class SpecialWindow : public Window
{
    public: 
        virtual void onResize()
        {
            // this code causes the error defined above
            // static_cast<Window>(*this).onResize();
            // So don't do that do this:
            Window::onResize();
        }
};

class SpecialWindow2 : public Window
{
    public:
        void blink();
};

typedef std::vector< std::shared_ptr<Window> > VPW;
typedef std::vector<std::shared_ptr<SpecialWindow2> > VPSW2;

VPW winPtrs;
VPSW2 winptrsBetterVersion;

int main()
{
    // This is not the code you want because it uses dynamic_cast and dynamic cast
    // has a heavy run-time cost
    for (VPW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
    {
        if (SpecialWindow2* psw2 = dynamic_cast<SpecialWindow2*>(iter->get()) )
            psw2->blink();
    }

    // Better code because it doesn't use dynamic_cast
    for (VPSW2::iterator iter = winptrsBetterVersion.begin(); iter != winptrsBetterVersion.end(); ++iter)
    {
        (*iter)->blink();
    }

    // Final alternative is just to make blink a virtual function in SpecialWindow2 and 
    // making a vector of shared_ptrs to Window. Then calling blink() on each dereferenced pointer
    // of that vector of Windows
}
