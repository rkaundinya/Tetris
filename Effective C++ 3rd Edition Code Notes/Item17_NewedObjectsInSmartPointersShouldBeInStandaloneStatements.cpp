#include <memory>
#include <vector>

int priority();
void processVector(std::shared_ptr<std::vector<int>> pw, int priority);

/*
If you don't delcare the new in the shared pointer first, you could get a memory leak
because if the call to the method priority() occurs after creating a new vector and throws
an exception, then the new vector won't be stored in the smart pointer and we would leak its 
memory allocation.
*/

int main()
{
    std::shared_ptr<std::vector<int>> pv(new std::vector<int>);

    processVector(pv, priority());
}