module;

#include <memory>

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.UI.Window;

namespace mk
{
	export
	{

		struct Extent2D
		{
			std::size_t width;
			std::size_t height;
		};

		struct WindowDescription
		{
			WindowDescription()  = default;
			~WindowDescription() = default;
			std::string title = "Mikrokosmos Framework";
			Extent2D    size = { 1280, 720 };
		};

		class MK_API Window
		{

		public:

			virtual ~Window() = default;

			static std::unique_ptr<Window> create(const WindowDescription& description = WindowDescription{});

			virtual void onUpdate() = 0;

		private:

		};

	}
	
}

module :private;
