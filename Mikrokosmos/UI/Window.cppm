module;

#include <memory>

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.UI.Window;

import Mikrokosmos.Graphics.Extent2D;
export import Mikrokosmos.Events.Event;
export import Mikrokosmos.Events.Delegate;
export import Mikrokosmos.Events.WindowEvents;

namespace mk
{
	export
	{

		struct WindowDescription
		{
			WindowDescription()  = default;
			~WindowDescription() = default;
			
			std::string title = "Mikrokosmos Framework";
			Extent2D    size  = { 1280, 720 };
		};

		class MK_API Window
		{

		public:

			using EventCallback = Delegate<void(Event&)>;

			virtual ~Window() = default;

			static std::unique_ptr<Window> Create(const WindowDescription& description = WindowDescription{});

			virtual void OnUpdate() = 0;

			std::size_t Width()  const;
			std::size_t Height() const;

			EventCallback callback;

		protected:

			Window(const WindowDescription& description);

		private:

			std::string _title;
			Extent2D    _size;

		};

	}
	
}

module :private;

namespace mk
{

	Window::Window(const WindowDescription& description)
		:
		_title { description.title },
		_size  { description.size  }
	{

	}

	std::size_t Window::Width() const
	{
		return _size.width;
	}

	std::size_t Window::Height() const
	{
		return _size.height;
	}
}