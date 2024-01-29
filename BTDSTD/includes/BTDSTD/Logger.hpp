#pragma once

//defines a logger

#include <BTDSTD_C/Logger.h>

#include <string>
#include <vector>

namespace BTD
{
    //defines a entry in the logger

    //defines flags for settings of the logger

    //defines a logger
    class Logger
    {
        //vars

        //maps a program name to a ID
        //maps a domain name to a ID
        //maps a function name to a ID
        //maps a message str to a ID

        //methods
    public:

        //sets the program

        //sets the logger flags

        //logs a message
        static BTD_Compiler_ForceInline void LogMessage(const char* message)
        {
            BTD_LogMessage(message);
        }

        //logs a warning
        static BTD_Compiler_ForceInline void LogWarning(const char* progName, const char* domain, const char* funcName, const char* message)
        {
           BTD_LogWarning(progName, domain, funcName, message);
        }

        //logs a error
        static BTD_Compiler_ForceInline void LogError(const char* progName, const char* domain, const char* funcName, const char* message)
        {
           BTD_LogError(progName, domain, funcName, message);
        }

        //logs a fatal error
        static BTD_Compiler_ForceInline void LogFatalError(const char* progName, const char* domain, const char* funcName, const char* message)
        {
            BTD_LogFatalError(progName, domain, funcName, message);
        }

        ////logs a message
        //static BTD_Compiler_ForceInline void LogMessage(const BTD_String& message)
        //{
        //    BTD_LogMessage(message.data);
        //}

        ////logs a warning
        //static BTD_Compiler_ForceInline void LogWarning(const BTD_String& progName, const BTD_String& domain, const BTD_String& funcName, const BTD_String& message)
        //{
        //    BTD_LogWarning(progName.data, domain.data, funcName.data, message.data);
        //}

        ////logs a error
        //static BTD_Compiler_ForceInline void LogError(const BTD_String& progName, const BTD_String& domain, const BTD_String& funcName, const BTD_String& message)
        //{
        //    BTD_LogError(progName.data, domain.data, funcName.data, message.data);
        //}

        ////logs a fatal error
        //static BTD_Compiler_ForceInline void LogFatalError(const BTD_String& progName, const BTD_String& domain, const BTD_String& funcName, const BTD_String& message)
        //{
        //    BTD_LogFatalError(progName.data, domain.data, funcName.data, message.data);
        //}

        ////logs a message
        //static BTD_Compiler_ForceInline void LogMessage(const std::string& message)
        //{
        //    BTD_LogMessage(message.c_str());
        //}

        ////logs a warning
        //static BTD_Compiler_ForceInline void LogWarning(const std::string& progName, const std::string& domain, const std::string& funcName, const std::string& message)
        //{
        //    BTD_LogWarning(progName.c_str(), domain.c_str(), funcName.c_str(), message.c_str());
        //}

        ////logs a error
        //static BTD_Compiler_ForceInline void LogError(const std::string& progName, const std::string& domain, const std::string& funcName, const std::string& message)
        //{
        //    BTD_LogError(progName.c_str(), domain.c_str(), funcName.c_str(), message.c_str());
        //}

        ////logs a fatal error
        //static BTD_Compiler_ForceInline void LogFatalError(const std::string& progName, const std::string& domain, const std::string& funcName, const std::string& message)
        //{
        //    BTD_LogFatalError(progName.c_str(), domain.c_str(), funcName.c_str(), message.c_str());
        //}
    };
}