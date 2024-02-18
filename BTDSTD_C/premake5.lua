include "C:\\SmokSDK\\Libraries\\BTD-Libs\\glfw"

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

    project "BTDSTD_C"
    kind "StaticLib"
    language "C"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
    
    
    files 
    {
        "includes/**.h",
        "src/**.c",
        --"includes/**.hpp",
       -- "src/**.cpp",
    }

    includedirs
    {
        "includes",
        "C:\\SmokSDK\\Libraries\\BTD-Libs\\glfw\\include"
    }
    
    links
    {
        "GLFW"
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
       -- cppdialect "C++17"
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
    
    filter "configurations:Release"
        defines "BTD_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "BTD_DIST"
        optimize "On"
    
        defines
        {
            "NDEBUG"
        }