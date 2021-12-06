#include "Camera.h"
#include "Executor.h"
#include <iostream>

int main(int argc, char **argv)
{
	try
	{
		Executor exec(argc, argv);
		Camera camera(exec);
		camera.start();
	}
	catch (std::exception error)
	{
		std::cout << error.what();
		return 1;
	}

	return 0;
}