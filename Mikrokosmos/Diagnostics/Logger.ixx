module;

#include <memory>
#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Diagnostics.Logger;

namespace mk
{
	export
	{
		class Logger
		{

		public:

			MK_API static Logger& Get()
			{
				static Logger logger;
				return logger;
			}

			Logger(const Logger&)            = delete;
			Logger(Logger&&)                 = delete;
			Logger& operator=(const Logger&) = delete;
			Logger& operator=(Logger&&)      = delete;

			template<typename StringFormat, typename... Arguments>
			void Trace(const StringFormat& format, Arguments&&... arguments);

			template<typename StringFormat, typename... Arguments>
			void Info(const StringFormat& format, Arguments&&... arguments);

			template<typename StringFormat, typename... Arguments>
			void Warning(const StringFormat& format, Arguments&&... arguments);

			template<typename StringFormat, typename... Arguments>
			void Error(const StringFormat& format, Arguments&&... arguments);

		private:

			Logger();
			~Logger() = default;

		private:

			std::shared_ptr<spdlog::logger> _logger;

		};

		template<typename StringFormat, typename... Arguments>
		MK_API void Trace(const StringFormat& format, Arguments&&... arguments)
		{
			Logger::Get().Trace(format, arguments...);
		}

		template<typename StringFormat, typename... Arguments>
		MK_API void Info(const StringFormat& format, Arguments&&... arguments)
		{
			Logger::Get().Info(format, arguments...);
		}

		template<typename StringFormat, typename... Arguments>
		MK_API void Warning(const StringFormat& format, Arguments&&... arguments)
		{
			Logger::Get().Warning(format, arguments...);
		}

		template<typename StringFormat, typename... Arguments>
		MK_API void Error(const StringFormat& format, Arguments&&... arguments)
		{
			Logger::Get().Error(format, arguments...);
		}

	}

	template<typename StringFormat, typename... Arguments>
	void Logger::Trace(const StringFormat& format, Arguments&&... arguments) 
	{
		_logger->trace(format, arguments...); 
	}

	template<typename StringFormat, typename... Arguments>
	void Logger::Info(const StringFormat& format, Arguments&&... arguments) 
	{ 
		_logger->info(format, arguments...); 
	}

	template<typename StringFormat, typename... Arguments>
	void Logger::Warning(const StringFormat& format, Arguments&&... arguments) 
	{ 
		_logger->warn(format, arguments...); 
	}

	template<typename StringFormat, typename... Arguments>
	void Logger::Error(const StringFormat& format, Arguments&&... arguments) 
	{ 
		_logger->error(format, arguments...); 
	}

	void dummy() // Just to instantiate the template for export.
	{
		Logger::Get().Trace("");
		mk::Trace("");
	}

}

module :private;

namespace mk
{

	Logger::Logger()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		_logger = spdlog::stdout_color_mt("Mikrokosmos");
		_logger->set_level(spdlog::level::trace);
	}

}