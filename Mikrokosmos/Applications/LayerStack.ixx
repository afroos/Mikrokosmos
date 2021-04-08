module;

#include <vector>

export module Mikrokosmos.Applications.LayerStack;

import Mikrokosmos.Applications.Layer;

namespace mk
{
	export
	{

		class LayerStack
		{

		public:

			using LayerList            = std::vector<Layer*>;
			
			using Iterator             = LayerList::iterator;
			using ConstIterator        = LayerList::const_iterator;
			using ReverseIterator      = LayerList::reverse_iterator;
			using ConstReverseIterator = LayerList::const_reverse_iterator;

			LayerStack() = default;
			~LayerStack();

			void PushLayer   (Layer* layer  );
			void PushOverlay (Layer* overlay);
			void PopLayer    (Layer* layer  );
			void PopOverlay  (Layer* overlay);

			Iterator              begin()       { return _layers.begin();  }
			ConstIterator         begin() const { return _layers.begin();  }
			Iterator                end()       { return _layers.end();    }
			ConstIterator           end() const { return _layers.end();    }
			
			ReverseIterator      rbegin()       { return _layers.rbegin(); }
			ConstReverseIterator rbegin() const { return _layers.rbegin(); }
			ReverseIterator        rend()       { return _layers.rend();   }
			ConstReverseIterator   rend() const { return _layers.rend();   }

		private:

			using Index = std::size_t;

			LayerList _layers;
			Index     _insertIndex { 0 };

		};

	}
	
}

module : private;

namespace mk
{

	LayerStack::~LayerStack()
	{
		for (auto layer : _layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		_layers.emplace(_layers.begin() + _insertIndex, layer);
		_insertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		_layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto layerPosition = std::find(_layers.begin(), _layers.begin() + _insertIndex, layer);
		if (layerPosition != _layers.begin() + _insertIndex)
		{
			layer->OnDetach();
			_layers.erase(layerPosition);
			_insertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto layerPosition = std::find(_layers.begin() + _insertIndex, _layers.end(), overlay);
		if (layerPosition != _layers.end())
		{
			overlay->OnDetach();
			_layers.erase(layerPosition);
		}
	}
	
}