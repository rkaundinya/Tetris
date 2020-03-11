// Good options for error catching in destructors is to either
// terminate the program or swallow an exception (generally a bad idea unless you have
// good reason not to terminate program and keep running)

class DBConnection;

class DBConn
{
    public: 
        ~DBConn()
        {
            try 
            {
                db.close();
            }
            // (...) in catch means that any excption that's thrown should be handled by catch
            catch(...)
            {
                // Log that call to close failed

                // If you want to swallow the exception, then don't call abort, just 
                // log that the call to close failed
                std::abort();
            }
        }

    private: 
        DBConnection db;
};

/*
Slightly better way of making exceptions for destructors that fail in some way is below, 
but this will still terminate or swallow depending on ur implementation if a call to close were to fail
*/

class DBConn2
{
    public: 
        // This function exists so that the client (user) can react to an exception if it's thrown
        // in some way. So in words that I say and make sense to me, you have to call close() on your own
        // when using DBConn2 and if you don't THEN the destructor will run it's automatic closing 
        // using the pattern we saw above
        void close()
        {
            db.close();
            closed = true;
        }

        ~DBConn2()
        {
            if (!closed)
            {
                try 
                {
                    // Close the connection if the client didn't
                    db.close();
                }
                catch (...)
                {
                    // make log entry that call to close failed
                    // Or abort program
                }
            }
        }

    private: 
        DBConnection db;
        bool closed;
};