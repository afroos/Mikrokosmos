module;

#include <ostream>
#include <string>
#include <typeinfo>

//#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Events.Event;

namespace mk
{

	export
	{

		using EventType = const std::type_info&;

		class Event
		{

		public:

			virtual ~Event() = default;

			virtual std::string Name() const = 0;

			virtual std::string ToString() const;

			template <typename Other>
			bool Is() const
			{
				return typeid(*this) == typeid(Other);
			}

			bool Handled() const;

			void Handled(bool value);

		private:

			bool _handled{ false };

		};

		std::ostream& operator<<(std::ostream& output, const Event& event)
		{
			return output << "Event: " << event.ToString();
		}

	}

}

module :private;

namespace mk
{

	std::string Event::ToString() const
	{
		return Name();
	}

	bool Event::Handled() const
	{
		return _handled;
	}

	void Event::Handled(bool value)
	{
		_handled = value;
	}

}