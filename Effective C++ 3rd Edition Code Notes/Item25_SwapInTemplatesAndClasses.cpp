/*
Something called the pointer to implementation idom or "pimpl idiom" ( I didn't come up with these stupid names)
is when your class stores a pointer to an object storing all its data rather than having its data in it. 
In this case, when swapping values of two objects of that class, you just really need to swap the values of their
pointers and don't need to copy the whole object along with its pointer. So then you would want to implement your
own swap that's more efficient. To do that, you can specialize a template for the particular swap you have in 
mind. This is called total template specialization
*/

#include <algorithm>

class Widget
{
    public: 
        Widget(const Widget& rhs);
        Widget& operator=(const Widget& rhs)
        {
            *pImpl = *(rhs.pImpl);
            return *this;
        }

        void swap (Widget& other)
        {
            using std::swap;

            swap(pImpl, other.pImpl);
        }

    private: 
        WidgetImpl *pImpl;
};

// Widget Implementation class that holds some data (implementation not important)
class WidgetImpl
{
    public: 

    private: 
        int a, b, c;
};

namespace std
{
    template<>
    void swap<Widget>(Widget& a, Widget& b)
    {
        a.swap(b);
    }
}

/*
This works well when you're just dealing with a single class, but if Widget and WidgetImpl are 
template classes, usually you would just overload the swap function with a new template. But you can't 
do that for std library stuff because C++ wants to make sure that whatever is added into the std is 
thoroughly vetted. So what you end up doing is adding a non-member swap function template in the same 
NAMESPACE as Widget and WidgetImpl. If you're not using namespaces in code, you should!
*/

namespace WidgetStuff
{
    template <typename T>
    class Widget
    {
        // Widget is a template class taking type of T as its defining variable type
        public: 
            void swap (Widget& other)
            {
                using std::swap;

                swap(pImpl, other.pImpl);
            }
        private: 
            WidgetImpl* pImpl;
    };

    template <typename T>
    class WidgetImpl
    {
        // Make WidgetImpl in terms of a general template format specified by T
    };

    // Have this general template non-member swap function call the swap within Widget
    // that's the templatized swap version
    template <typename T>
    void swap(Widget<T>& a, Widget<T>& b)
    {
        a.swap(b);
    }
}

/*
If you're trying to call swap for a template function, if you don't specify using std::swap 
in the template function, the compiler will not know whether to call swap from std or a 
template specific namespace swap. So to make the compiler say execute swap for the T-specific
vesrion if there is one, but use std version if not, use this syntax: 
*/

template <typename T>
void doSomething (T&obj1, T&obj2)
{
    // make std::swap available in this function
    using std::swap;

    // Call the best swap for objects of Type T
    swap(obj1, obj2);
}

/*
Note - always call swap just as swap and not as std::swap. #include <algorithm> so you can use it, but
simply call swap so that you can allow for the compiler to find a template or class specific swap if you
desire to. 
*/