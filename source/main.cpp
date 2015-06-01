#include <iostream>
#include <dlfcn.h>
#include <unistd.h>
#include "nibbler.hpp"
#include "IDisplayLib.hpp"
#include <list>

int		main( void )
{
	void *			handle;
	IDisplayLib		*(*GraphicCreator)(int, int);
	void			(*GraphicDestructor)(IDisplayLib *);

	handle = dlopen("lib/libftcurse.dylib", RTLD_NOW);
	if (!handle)
	{
		std::cout << "Error opening dynlib" << std::endl;
		return (1);
	}

	GraphicCreator = (IDisplayLib *(*)(int, int)) dlsym(handle, "createGraphic");
	if (!GraphicCreator)
	{
		std::cout << "Error finding symbol creator" << std::endl;
		return (1);
	}
	GraphicDestructor = (void (*)(IDisplayLib *)) dlsym(handle, "deleteGraphic");
	if (!GraphicDestructor)
	{
		std::cout << "Error finding symbol destructor" << std::endl;
		return (1);
	}
	
	IDisplayLib *	obj;
	obj = GraphicCreator(50, 50);
	obj->init();

	std::list<std::pair<int, int> >	snake;

	snake.push_back(std::pair<int, int>(2, 2));
	snake.push_back(std::pair<int, int>(2, 1));
	snake.push_back(std::pair<int, int>(1, 1));
	snake.push_back(std::pair<int, int>(1, 0));

	while (42)
	{
		obj->clearScreen();
		obj->drawMap();
		obj->drawSnake(snake);
		obj->drawAll();
		usleep(2000);
	}
	GraphicDestructor(obj);

	dlclose(handle);
	return (0);
}
