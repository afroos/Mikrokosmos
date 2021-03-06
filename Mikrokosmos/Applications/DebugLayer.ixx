module;

export module Mikrokosmos.Applications.DebugLayer;

import Mikrokosmos.Applications.Layer;
import Mikrokosmos.Events;

namespace mk
{
	export
	{

		class DebugLayer : public Layer
		{

		public:

			 DebugLayer();
			~DebugLayer();

			void OnAttach() override;
			void OnDetach() override;
			void OnRender() override;

			void Begin();
			void End();

		private:

			void SetDarkThemeColors();

		};

	}
	
}