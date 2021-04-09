module;

export module Mikrokosmos.Input.Mouse;

import Mikrokosmos.Mathematics.Algebra.Vector;

namespace mk
{
	export
	{

		class Mouse
		{

		public:

			enum class Button
			{
				Unknown,
				Left,
				Right,
				Middle,
				XButton1,
				XButton2
			};

			static bool IsButtonPressed(Button button);
			
			static Vector2i Position();

		};

		constexpr Mouse::Button ToMikrokosmosButton(int platformButton);

		constexpr int ToPlatformButton(Mouse::Button button);

	}

}