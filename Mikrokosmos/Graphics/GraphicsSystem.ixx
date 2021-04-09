module;

#include <functional>
#include <map>
#include <memory>

export module Mikrokosmos.Graphics.GraphicsSystem;

import Mikrokosmos.Graphics.Rendering.GLRenderer;
import Mikrokosmos.Graphics.Rendering.Renderer;

export namespace mk
{

	class GraphicsSystem
	{

	public:

		static std::unique_ptr<Renderer> CreateRenderer(const std::string& name);

	private:


	};


}

module :private;

namespace mk
{
	std::unique_ptr<Renderer> GraphicsSystem::CreateRenderer(const std::string& name)
	{
		static std::map<
			std::string, 
			std::function<std::unique_ptr<Renderer>()>> dispatchTable
		{
			{ "OpenGL", []() { return std::make_unique<GLRenderer>(); } }
		};

		auto entry = dispatchTable.find(name);
		if (entry != dispatchTable.end())
		{
			auto [name, instance] = *entry;
			return instance();
		}
		else return nullptr;

	}
}