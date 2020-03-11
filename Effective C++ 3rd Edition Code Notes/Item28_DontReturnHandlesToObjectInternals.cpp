/*
Member functions that return references to object internals make it so that class is only as 
private as its most accessible member. So these member functions break encapsulation to a degree
because if that function is called outside the class, then you have access to a data member that was 
previously encapsulated. So, don't return by reference, pointer or iterator if you want to keep 
encapsulation and if you do, make sure that you return const but be wary of the fact that you are
making your data less encapsulated. 
*/

// Example of return which will break encapsulation and allow you to modify data members
// outside of the class

#include <iostream>
#include <memory>

class Point 
{
    public: 
        Point(int x, int y)
        : _x(x), _y(y) {}

        void setX(int newVal)
        {
            _x = newVal;
        }

        void setY(int newVal)
        {
            _y = newVal;
        }
        
        int getX() const
        {
            return _x;
        }

        int getY() const
        {
            return _y;
        }

    private: 
        int _x;
        int _y;
};

struct RectData
{
    RectData(Point upperleft, Point lowerRight) 
    : ulhc(upperleft), 
      lrhc(lowerRight) {}

    // Upper left hand corner, lower right hand corner
    // The only two points you need to store information about a rectangle's dimensions
    Point ulhc;
    Point lrhc;
};

class Rectangle
{
    public: 
        Rectangle(Point upperleft, Point lowerRight)
        : pData(std::make_shared<RectData>(upperleft, lowerRight)) {} 

        Point& upperleft() const
        {
            return pData->ulhc;
        }
        Point& lowerRight() const
        {
            return pData->lrhc;
        }

    private: 
        std::shared_ptr<RectData> pData;
};

// With the return values of upperleft() not being const, if I call 
// rec.upperleft().setX(50) on a Rectangle object, I can modify a supposedly const 
// object and private data through a function which is not supposed to be able to modify data
/* int main()
{
    Point coord1(0, 0);
    Point coord2(100, 100);

    const Rectangle rect(coord1, coord2);

    // I've modified a supposedly const object with a supposedly const function
    // rect will now have a coord1 value of (50, 0) instead of (0, 0)
    rect.upperleft().setX(50);

    std::cout << rect.upperleft().getX() << std::endl;
} */

/*
So to avoid that, make sure that your rectangle class returns const Point& rahter than simply Point&
*/

class BetterRectangle
{
    public: 
        BetterRectangle(Point upperleft, Point lowerright) 
        : _pData(std::make_shared<RectData>(upperleft, lowerright)) {}

        const Point& upperLeft() const 
        {
            return _pData->ulhc;
        }

        const Point& lowerRight() const
        {
            return _pData->lrhc;
        }

    private: 
        std::shared_ptr<RectData> _pData;
};

int main()
{
    Point coord1(0, 0);
    Point coord2(100, 100);

    const BetterRectangle rect(coord1, coord2);

    // Now this code is no longer be legal
    // rect.upperleft().setX(50);

    std::cout << rect.lowerRight().getX() << std::endl;
}