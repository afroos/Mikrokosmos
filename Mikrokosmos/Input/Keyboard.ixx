module;

#include <Mikrokosmos/Core.h>

export module Mikrokosmos.Input.Keyboard;

export namespace mk
{
	class MK_API Keyboard
	{

	public:

		enum class Key
		{
			Unknown,
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			Num0,
			Num1,
			Num2,
			Num3,
			Num4,
			Num5,
			Num6,
			Num7,
			Num8,
			Num9,
			Escape,
			LControl,
			LShift,
			LAlt,
			LSystem,
			RControl,
			RShift,
			RAlt,
			RSystem,
			Menu,
			LBracket,
			RBracket,
			Semicolon,
			Comma,
			Period,
			Apostrophe,
			Slash,
			Backslash,
			Tilde,
			Equal,
			Hyphen,
			Space,
			Enter,
			Backspace,
			Tab,
			PageUp,
			PageDown,
			End,
			Home,
			Insert,
			Delete,
			Add,
			Subtract,
			Multiply,
			Divide,
			Left,
			Right,
			Up,
			Down,
			Numpad0,
			Numpad1,
			Numpad2,
			Numpad3,
			Numpad4,
			Numpad5,
			Numpad6,
			Numpad7,
			Numpad8,
			Numpad9,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			Pause
		};

		static bool IsKeyPressed(Key key);

	};

	constexpr Keyboard::Key ToMikrokosmosKey(int platformKey);
	
	constexpr int ToPlatformKey(Keyboard::Key key);
	
}