#include <iostream>

template <class exceptionType>
class BaseLogger
{

protected:
    using T = exceptionType;

public:
    BaseLogger();
    ~BaseLogger();
    void info(const T& e)
    {

    }

protected:

};

