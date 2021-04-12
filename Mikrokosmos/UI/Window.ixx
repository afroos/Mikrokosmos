module;

#include <memory>
#include <string>

export module Mikrokosmos.UI.Window;

import Mikrokosmos.Mathematics.Algebra.Vector;
export import Mikrokosmos.Events.Event;
export import Mikrokosmos.Events.Delegate;

namespace mk
{
	export
	{

		class Window
		{

		public:

			struct Description
			{
				Description() = default;
				~Description() = default;

				std::string title = "Mikrokosmos Framework";
				Vector2u    size = { 1280, 720 };
			};

			using Callback = Delegate<void(Event&)>;

			virtual ~Window() = default;

			static std::unique_ptr<Window> Create(const Description& description = Description{});

			virtual void OnUpdate() = 0;

			Vector2u    Size()   const;
			std::size_t Width()  const;
			std::size_t Height() const;

			Callback EventCallback;

			virtual void* NativeHandle() const = 0;

		protected:

			Window(const Description& description);

		private:

			std::string _title;
			Vector2u    _size;

		};

	}
	
}

module :private;

namespace mk
{

	Window::Window(const Window::Description& description)
		:
		_title { description.title },
		_size  { description.size  }
	{

	}

	Vector2u Window::Size() const
	{
		return _size;
	}

	std::size_t Window::Width() const
	{
		return _size.X();
	}

	std::size_t Window::Height() const
	{
		return _size.Y();
	}

}