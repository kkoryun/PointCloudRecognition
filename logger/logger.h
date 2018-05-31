#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

template <class exceptionType>
class BaseLogger
{

protected:
    using T = exceptionType;

public:
    BaseLogger(const string& moduleName):
        m_moduleName(moduleName)
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

    virtual void debug(const std::string& s)
    {
        log(LOG_TYPE::DEBUG, s);
    };
    virtual void info() {};
    virtual void warn() {};
    virtual void error() {};


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
    string m_moduleName;
    
};

template <class exceptionType>
class FileLogger: public BaseLogger<exceptionType>
{
public:
    FileLogger(const std::string& moduleName, std::string logFileName = "logs.txt"): 
        BaseLogger<exceptionType>(moduleName)
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
    ConsolLogger(const std::string& moduleName, std::ostream& outStream): 
        BaseLogger<exceptionType>(moduleName)
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

