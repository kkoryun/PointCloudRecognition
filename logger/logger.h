#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>



#define VS_
#ifdef VS_
#include <Windows.h>
#endif // VS_

using namespace std;

template <class exceptionType>
class BaseLogger
{

protected:
    using T = exceptionType;

public:
    BaseLogger(const string& moduleName) :
        m_moduleName(moduleName)
    {}
    ~BaseLogger() = default;

    enum class LOG_TYPE
    {
        LOG_DEBUG,
        LOG_INFO,
        LOG_WARN,
        LOG_ERROR
    };

    virtual void log(LOG_TYPE t, const T& e) {};
    virtual void log(LOG_TYPE t, const std::string& s) {};

    virtual void debug(const std::string& s)
    {
        log(LOG_TYPE::LOG_DEBUG, s);
    };
    virtual void info(const std::string& s)
    {
        log(LOG_TYPE::LOG_INFO, s);
    };
    virtual void warn(const std::string& s)
    {
        log(LOG_TYPE::LOG_WARN, s);
    };
    virtual void error(const std::string& s)
    {
        log(LOG_TYPE::LOG_ERROR, s);
    };


protected:
    std::string getLogMetadata(const LOG_TYPE& t)
    {
        return (string("[") + getLogTypeStr(t) + "]" + "Module:" + m_moduleName + "  ");
    }
    string getLogTypeStr(const LOG_TYPE& t)
    {
        string logTypeStr = "";
        switch (t)
        {
        case LOG_TYPE::LOG_DEBUG:
        {
            logTypeStr = "DEBUG";
            break;
        }
        case LOG_TYPE::LOG_INFO:
        {
            logTypeStr = "INFO";
            break;
        }
        case LOG_TYPE::LOG_WARN:
        {
            logTypeStr = "WARN";
            break;
        }
        case LOG_TYPE::LOG_ERROR:
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
class FileLogger : public BaseLogger<exceptionType>
{
public:
    FileLogger(const std::string& moduleName, std::string logFileName = "logs.txt") :
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
        try
        {
            m_file << e.what() << endl;
        }
        catch (const std::exception& e)
        {
            if (m_file.is_open())
            {
                m_file << e.what() << endl;
            }
            else
            {
                std::cerr << e.what() << endl;
            }
        }

    }

    void log(LOG_TYPE t, const std::string& s) override
    {
        m_file << getLogMetadata(t).c_str() << s.c_str() << endl;
        m_file.flush();
    }


protected:
    std::ofstream m_file;
    void openFile(std::string logFileName = "logs.txt")
    {
        m_file.open(logFileName, ios::out | ios::app | ios::ate);
        if (!m_file.is_open())
        {
            std::cerr << "File not opened" << endl;
        }
    }
};

template <class exceptionType>
class ConsolLogger : public BaseLogger<exceptionType>
{
public:
    ConsolLogger(const std::string& moduleName, std::ostream& outStream = std::cout) :
        BaseLogger<exceptionType>(moduleName),
        m_outStream(outStream)
    {
        //m_outStream = outStream;
    }
    ~ConsolLogger() = default;

    void log(LOG_TYPE t, const T& e) override
    {}

    void log(LOG_TYPE t, const std::string& s) override
    {
        m_outStream << getLogMetadata(t).c_str() << s << endl;
        m_outStream.flush();
    }

protected:
    std::ostream& m_outStream;
};

template <class exceptionType>
class VSOutputLogger : public BaseLogger<exceptionType>
{
public:
    VSOutputLogger(const std::string& moduleName) :
        BaseLogger<exceptionType>(moduleName)
    {
        //m_outStream = outStream;
    }
    ~VSOutputLogger() = default;

    void log(LOG_TYPE t, const T& e) override
    {
        try
        {
            OutputDebugString(e.what());
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << endl;
        }
    }

    void log(LOG_TYPE t, const std::string& s) override
    {
        string outString = getLogMetadata() + s;
        OutputDebugString(outString.c_str());
    }

protected:

};


//using StdBaseLogger = BaseLogger<std::exception>;
//using StdFileLogger = FileLogger<std::exception>;
//using StdConsolLogger = ConsolLogger<std::exception>;

typedef BaseLogger<std::exception> StdBaseLogger;
typedef FileLogger<std::exception> StdFileLogger;
typedef ConsolLogger<std::exception> StdConsolLogger;