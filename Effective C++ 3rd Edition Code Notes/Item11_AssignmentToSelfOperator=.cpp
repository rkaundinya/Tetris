#include <algorithm>
using std::swap;

class Bitmap;

class Widget
{
    public:
        Widget& Widget::operator=(const Widget& rhs)
        {
            // Run an identity test in case you're assigning a value to itself
            // If you delete pb before assignment takes place you could be left with a 
            // dangling pointer
            if (this == &rhs)
                return *this;

            delete pb;
            pb = new Bitmap(*rhs.pb);
            return *this;
        }
        
        // Another way to do the same thing as above is like this - rearrange
        // the delete so it only occurs after making a copy of original, copying data from rhs, 
        // and then deleting original
        Widget& Widget::operator=(const Widget& rhs)
        {
            Bitmap* pOrig = pb;
            pb = new Bitmap(*rhs.pb);
            delete pOrig;

            return *this;
        }

        // Perhaps the best way to do this is through what is known as the copy and swap idiom
        // That looks like this (I'll show a more consise way right after this):
        Widget& Widget::operator=(const Widget& rhs)
        {
            // Make a copy of rhs data
            Widget temp(rhs);
            
            // Swap *this's data with the copy's
            swap(temp);

            return *this;
        }

        // Cleaner version looks like this. This works because it takes a Widget by value as a paramter
        // and then performs the swap which can be more efficient than making a copy 
        // in the body of the function
        Widget& Widget::operator=(Widget rhs)
        {
            swap(rhs);

            return *this;
        }

    private:
        Bitmap* pb;
}
