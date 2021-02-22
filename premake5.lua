workspace "ANFuck"
	architecture "x86"

	configurations
	{
		"Debug",
		"Dist",
	}

	files
	{
		"premake5.lua"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
-- IncludeDir["Dep"] = "ANFuck/vendor/Dep/include"

-- include "ANFuck/vendor/Dep"

project "ANFuck"
	location "ANFuck"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		-- "%{IncludeDir.Dep}"
	}

	links 
	{
	}

	filter "configurations:Debug"
		defines "ANFUCK_DEBUG"
		symbols "On"

	filter "configurations:Dist"
		defines "ANFUCK_DIST"
		optimize "On"
