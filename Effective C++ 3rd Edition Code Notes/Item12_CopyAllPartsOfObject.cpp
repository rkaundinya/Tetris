// Remember that when declaring a class that inherits from a base class
// and wanting to define copy constructors and assignment operators, to 
// call the constructor of the base class in the initialization list
// Else you can forget to add initializations to new elements you might add to the derived
// class or you may end up calling a default initializer on your base class instead of 
// the paramters you may have included in your constructor call

// Assume here that prioritycustomer is a derived class from customer

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs) 
:   Customer(rhs), 
    priority(rhs.priority) 
{
    // do whatever else is necessary in method
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
    // assign the base class parts by calling base class copy assignment operator
    Customer::operator=(rhs);
    priority = rhs.priorty;

    return *this;
}