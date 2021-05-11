module;

//#include <>

export module Mikrokosmos.Graphics.Rendering.Adapter;

//import Mikrokosmos.Events.Event;

export namespace mk
{

	class Adapter
	{

	public:

		struct Description
		{
			Description() = default;
		};

		Adapter() = delete;
		Adapter(const Description& description = {});

		virtual ~Adapter() = default;

	};

}

module :private;

namespace mk
{
	Adapter::Adapter(const Adapter::Description& description)
	{

	}
}