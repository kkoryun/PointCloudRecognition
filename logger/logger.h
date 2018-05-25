#include <iostream>
#include <fstream>
#include <string>

using namespace std;
template <class exceptionType>
class BaseLogger
{

protected:
    using T = exceptionType;

public:
    BaseLogger() 
    {}
    ~BaseLogger() = default;

    enum class LOG_TYPE
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    virtual void log(LOG_TYPE t, const T& e) {};
    virtual void log(LOG_TYPE t, const std::string& s) {};

protected:
    string getLogTypeStr(const LOG_TYPE& t)
    {
        string logTypeStr = "";
        switch(t)
        {
        case LOG_TYPE::DEBUG:
        {
            logTypeStr = "DEBUG";
            break;
        }
        case LOG_TYPE::INFO:
        {
            logTypeStr = "INFO";
            break;
        }
        case LOG_TYPE::WARN:
        {
            logTypeStr = "WARN";
            break;
        }
        case LOG_TYPE::ERROR:
        {
            logTypeStr = "ERROR";
            break;
        }
        default:
            break;
        }
        return logTypeStr;
    }
};

template <class exceptionType>
class FileLogger: public BaseLogger<exceptionType>
{
public:
    FileLogger(std::string logFileName = "logs.txt"): BaseLogger<exceptionType>()
    {
        openFile(logFileName);
    }
    ~FileLogger()
    {
        m_file.close();
    }
    void log(LOG_TYPE t, const T& e) override
    {
        e.what();
    }

    void log(LOG_TYPE t, const std::string& s) override
    {
        m_file << "[" << getLogTypeStr(t).c_str() << "]: " << s.c_str() << endl;
        m_file.flush();
    }


protected:
    std::ofstream m_file;
    void openFile(std::string logFileName = "logs.txt")
    {
        m_file.open(logFileName, ios::out | ios::app | ios::ate);
        if(!m_file.is_open())
        {

        }
    }
};

template <class exceptionType>
class ConsolLogger: public BaseLogger<exceptionType>
{
public:
    ConsolLogger(std::ostream& outStream): BaseLogger<exceptionType>()
    {
        m_outStream = outStream;
    }
    ~ConsolLogger() = default;

    void log(LOG_TYPE t, const T& e) override
    {}

    void log(LOG_TYPE t, const std::string& s) override
    {
        m_outStream << "[" << getLogTypeStr(t) << "]: " << s << endl;
        m_outStream.flush();
    }

protected:
    std::ostream& m_outStream;
};

