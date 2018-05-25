#include "logger.h"


int main()
{
 
    FileLogger<std::exception> fl;
    fl.log(FileLogger<std::exception>::LOG_TYPE::DEBUG, "bbb");
    fl.log(FileLogger<std::exception>::LOG_TYPE::DEBUG, "bb");
    fl.log(FileLogger<std::exception>::LOG_TYPE::DEBUG, "b");

    system("PAUSE");
    return 0;
}