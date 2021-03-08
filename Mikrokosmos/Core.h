#pragma once

#include <spdlog/spdlog.h>                   // FIXIT: get rid of spdlog header dependencies.
#include <spdlog/sinks/stdout_color_sinks.h> // FIXIT: get rid of spdlog header dependencies.

#ifdef MK_PLATFORM_WINDOWS
	#ifdef MK_BUILD_DLL
		#define MK_API __declspec(dllexport)
	#endif
#endif