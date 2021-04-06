#pragma once

#include <spdlog/spdlog.h>                   // FIXIT: get rid of spdlog header dependencies.
#include <spdlog/sinks/stdout_color_sinks.h> // FIXIT: get rid of spdlog header dependencies.
#include <spdlog/fmt/ostr.h>

#ifdef MK_PLATFORM_WIN32
	#ifdef MK_BUILD_DLL
		#define MK_API __declspec(dllexport)
	#endif
#endif