module;

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Applications.Application;

import Mikrokosmos.Diagnostics.Logger;

export namespace mk
{
	class MK_EXPORT Application
	{

	public:

		Application() = default;
		virtual ~Application() = default;

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		void run()
		{
			mk::trace("Application starting.");
			while (true);
		}

	private:

	};

}

module :private;



