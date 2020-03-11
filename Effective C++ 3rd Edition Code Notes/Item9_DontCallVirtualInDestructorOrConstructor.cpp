#include <string>

class Transaction
{
    public: 
        explicit Transaction(const std::string& logInfo);
        void logTransaction(const std::string& logInfo) const;

};

Transaction::Transaction(const std::string& logInfo)
{
    // call a non-virtual function to log rather than a virtual one
    logTransaction(logInfo);
}

class BuyTransaction : public Transaction
{
    public: 
        BuyTransaction(/* paramters */) 
        : Transaction(createLogString(/* parameters */))
        {}

    private:
        static std::string createLogString(/* parameters */);
}