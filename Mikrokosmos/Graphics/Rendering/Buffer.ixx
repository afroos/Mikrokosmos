module;

#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.Buffer;

import Mikrokosmos.Graphics.Rendering.Resource;

export namespace mk
{

	class Buffer : public Resource
	{
	
	public:

		struct Description
		{		
			/*std::size_t       elementCount;
			std::size_t       elementSize;
			Resource::Binding binding;
			Resource::Usage   usage;*/		
		};

		virtual ~Buffer() = default;

	protected:

		Buffer(const Description& description);

	};

}

module :private;

namespace mk
{

	Buffer::Buffer(const Buffer::Description& description)
		: 
		Resource
		{ 
		}
	{	
	}

}