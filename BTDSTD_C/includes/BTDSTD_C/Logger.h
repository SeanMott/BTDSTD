#pragma once

//defines a logger in the C API

#include <stdio.h>
#include <stdlib.h>

#include <BTDSTD_C/CompilerCommands/FunctionModifiers.h>

#if defined(__cplusplus)
	extern "C" { 
	#endif

    //logs a message
    static BTD_Compiler_ForceInline void BTD_LogMessage(const char* message)
    {
        printf("%s\n", message);
    }

    //logs a warning
    static BTD_Compiler_ForceInline void BTD_LogWarning(const char* progName, const char* domain, const char* funcName, const char* message)
    {
        printf("%s Warning: %s, Func: \"%s\" || %s\n", progName, domain, funcName, message);
    }

    //generates a log error message

    //logs a error
    static BTD_Compiler_ForceInline void BTD_LogError(const char* progName, const char* domain, const char* funcName, const char* message)
    {
        printf("%s Error: %s, Func: \"%s\" || %s\n", progName, domain, funcName, message);
    }

    //generates a log warning message

    //logs a fatal error
    static BTD_Compiler_ForceInline void BTD_LogFatalError(const char* progName, const char* domain, const char* funcName, const char* message)
    {
        printf("%s Fatal Error: %s, Func: \"%s\" || %s\n", progName, domain, funcName, message);
        getchar();
        exit(-1);
    }

#if defined(__cplusplus)
	}
	#endif