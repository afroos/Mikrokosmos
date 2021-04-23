module;

#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.Resource;

//import Mikrokosmos.UI.Window;

export namespace mk
{

	class Resource
	{

	public:

		struct Binding
		{
			bool VertexBuffer = false;
			bool IndexBuffer  = false;
		};

		enum class Usage
		{
			Stream,
			Dynamic,
			Static
		};

		virtual ~Resource() = default;
	
	protected:

		Resource();

	protected:

		//std::size_t _elementSize;
		//std::size_t _elementCount;
		//Binding     _binding;
		//Usage       _usage;

	};

}

module :private;

namespace mk
{

	Resource::Resource()
	{
	}

}