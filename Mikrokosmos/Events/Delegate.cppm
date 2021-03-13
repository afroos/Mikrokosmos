module;

#include <functional>

//#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Events.Delegate;

import Mikrokosmos.Events.Event;

namespace mk
{

	export
	{

		template <typename>
		class Delegate;

		template <typename ReturnType, typename... Arguments>
		class Delegate<ReturnType(Arguments...)>
		{

		public:

			template<typename Object>
			using Method = ReturnType(Object::*)(Arguments...);

			template<typename Object>
			void Bind(Object* object, Method<Object> method)
			{
				_function = [=](Arguments... arguments) { (object->*method)(arguments...); };
			}

			ReturnType operator()(Arguments... arguments)
			{
				return _function(arguments...);
			}

		private:

			std::function<ReturnType(Arguments...)> _function;

		};

	}

}

module :private;

namespace mk
{

}