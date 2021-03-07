import Mikrokosmos;

#include <Mikrokosmos/Core.h>

class Sandbox : public mk::Application
{

public:

	Sandbox()  = default;
	~Sandbox() = default;

private:


};

int main()
{
	auto application = std::make_unique<Sandbox>();

	try
	{
		application->run();
	}
	catch (const std::exception& exception)
	{
		mk::error(exception.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}