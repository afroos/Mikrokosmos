module;

#include <functional>
#include <vector>

//#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Events.EventDispatcher;

import Mikrokosmos.Events.Event;
import Mikrokosmos.Events.Delegate;

namespace mk
{
	export
	{

		template <typename Event>
		class EventDispatcher
		{

		public:

			using EventCallback = Delegate<void(const Event&)>;

			EventDispatcher() = default;

			template<typename Object>
			using Method = void(Object::*)(const Event&);

			template<typename Object>
			void AddListener(Object* object, Method<Object> method)
			{
				EventCallback callback;
				callback.Bind(object, method);
				_callbacks.emplace_back(callback);
			}

			void Fire(const Event& event = Event{})
			{
				for (auto& callback : _callbacks)
				{
					callback(event);
				}
			}

		private:
			
			std::vector<EventCallback> _callbacks;

		};

	}

}

module :private;

namespace mk
{


}





/*

int Foo(float a, char b);                       // == int(*)(float, char)
int Clazz::Foo(const float& a, char b);         // == int(*Clazz::)(const float&, char)
[this](float a, char b){};                      // == ????


#include <iostream>
#include <functional>

template <typename>
class Delegate;

template <typename R, typename... Args>
class Delegate<R(Args...)>
 {
   public:
	  template<typename T>
	  void connect (T * t, R(T::*method)(Args...) )
	   { mFunction = [=](Args ... as){ (t->*method)(as...); }; }

	  R operator() (Args... args)
	   { return mFunction(args...); }

   protected:
	  std::function<R(Args...)> mFunction;
 };

class A
 { public: Delegate<void(int)> test; };

class B
 { public: void test (int a) { std::cout << a; }; };

int main()
 {
   A a;
   B b;

   a.test.connect(&b, &B::test);

   a.test(42);
 }



*/