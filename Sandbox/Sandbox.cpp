#include <Mikrokosmos/Core.h>

import Mikrokosmos;

class ExampleLayer : public mk::Layer
{

public:

	ExampleLayer()
		: mk::Layer()
	{
	}

	virtual ~ExampleLayer() = default;

	void OnUpdate() override
	{
		if (mk::Keyboard::IsKeyPressed(mk::Keyboard::Key::A)) mk::Trace("Key A!");
		if (mk::Keyboard::IsKeyPressed(mk::Keyboard::Key::B)) mk::Trace("Mouse position: {}", mk::Mouse::Position());
		if (mk::Mouse::IsButtonPressed(mk::Mouse::Button::Left)) mk::Trace("Left button!");
		if (mk::Mouse::IsButtonPressed(mk::Mouse::Button::Right)) mk::Trace("Right button!");

		//mk::info("ExampleLayer::Update");
	}
	
	void OnEvent(mk::Event& event) override
	{
		//mk::trace("ExampleLayer::OnEvent");
	}

private:


};

class Sandbox : public mk::Application
{

public:

	Sandbox()
	{
		PushLayer(new ExampleLayer());

	}

	~Sandbox() = default;

private:

};

int main()
{
	auto application = std::make_unique<Sandbox>();

	try
	{
		application->Run();
	}
	catch (const std::exception& exception)
	{
		mk::Error(exception.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}