#include "Camera.h"
#include <iostream>

int main(int argc, char **argv)
{
	try
	{
		Camera camera;
		camera.start();
	}
	catch (std::exception error)
	{
		std::cout << error.what();
		return 1;
	}

	return 0;
}