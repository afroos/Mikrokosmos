module;

#include <memory>

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.UI.Window;

export namespace mk
{

	struct Extent2D
	{
		std::size_t width;
		std::size_t height;
	};

	struct WindowDescription
	{
		std::string title = "Mikrokosmos Framework";
		Extent2D    size  = {1280, 720};
	};

	class MK_EXPORT Window
	{

	public:

		virtual ~Window() = default;

		static std::unique_ptr<Window> create(const WindowDescription& description);

		virtual void onUpdate() = 0;

	private:

	};

}

module :private;
