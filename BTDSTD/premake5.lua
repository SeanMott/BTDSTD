
include "C:\\SmokSDK\\Libraries\\BTD-Libs\\yaml-cpp"
include "C:\\SmokSDK\\BTDSTD\\BTDSTD_C"

    configurations
    {
        "Debug",
        "Release",
        "Dist" --,

        --"Desktop_Debug",
        --"Desktop_Release",
        --"Desktop_Dist",

        --"Android_Debug",
        --"Android_Release",
        --"Android_Dist",

        --"IOS_Debug",
        --"IOS_Release",
        --"IOS_Dist",
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}"

    project "BTDSTD"
    kind "StaticLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
    
    
    files 
    {
        "includes/**.h",
        "src/**.c",
        "includes/**.hpp",
        "src/**.cpp",
    }

    includedirs
    {
        "includes",
        
        "C:\\SmokSDK\\Libraries\\BTD-Libs\\yaml-cpp\\include",
        "C:\\SmokSDK\\Libraries\\BTD-Libs\\glm",
        "C:\\SmokSDK\\Libraries\\BTD-Libs\\glfw\\include",
        "C:\\SmokSDK\\BTDSTD\\BTDSTD_C\\includes"
    }
    
    links
    {
        "yaml-cpp",
        "GLFW",
        "BTDSTD_C"
    }
    
    defines
    {
        "GLFW_INCLUDE_NONE",
        "GLM_FORCE_RADIANS",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
        "GLM_ENABLE_EXPERIMENTAL"
    }
    
    flags
    {
        "NoRuntimeChecks",
        "MultiProcessorCompile"
    }
    
    --platforms
    filter "system:windows"
        cppdialect "C++17"
      --  cdialect "C99"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build",
            "Desktop_Build"
        }
    
    --configs
    filter "configurations:Debug"
        defines "BTD_DEBUG"
        symbols "On"
    
        links
        {
           -- "C:\\GameDev\\Libraries\\yaml-cpp\\bin\\Debug-windows-x86_64\\yaml-cpp\\yaml-cpp.lib",
            --"C:\\GameDev\\Libraries\\glfw\\bin\\Debug-windows-x86_64\\GLFW\\GLFW.lib"
        }
    
    filter "configurations:Release"
        defines "BTD_RELEASE"
        optimize "On"
    
        flags
        {
            
        }

        links
        {
           -- "C:\\GameDev\\Libraries\\yaml-cpp\\bin\\Release-windows-x86_64\\yaml-cpp\\yaml-cpp.lib",
           -- "C:\\GameDev\\Libraries\\glfw\\bin\\Release-windows-x86_64\\GLFW\\GLFW.lib"
        }
    
    filter "configurations:Dist"
        defines "BTD_DIST"
        optimize "On"
    
        defines
        {
            "NDEBUG"
        }
    
        flags
        {
           
        }
    
        links
        {
           -- "C:\\GameDev\\Libraries\\yaml-cpp\\bin\\Dist-windows-x86_64\\yaml-cpp\\yaml-cpp.lib",
           -- "C:\\GameDev\\Libraries\\glfw\\bin\\Dist-windows-x86_64\\GLFW\\GLFW.lib"
        }