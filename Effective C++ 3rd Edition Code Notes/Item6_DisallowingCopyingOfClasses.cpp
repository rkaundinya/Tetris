/*
To prevent copying of a class you can declare its copy constructor and copy 
assignment operator as private. This way it's still acessible for member functions or friend 
functions, but anything that inherits from this base Uncopyable class will not be copyable
*/

class Uncopyable
{
    protected:
        Uncopyable() {}
        ~Uncopyable() {}

    private: 
        Uncopyable(const Uncopyable&);
        Uncopyable& operator=(const Uncopyable&);
};

// Inheritance is private simply because it doesn't need to be public
// Private inheritance means that everything public or protected is inherited as private
class ClassYouDontWantCopied : private Uncopyable
{

};