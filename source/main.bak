#include <iostream>
#include <dlfcn.h>
#include "nibbler.hpp"
#include "IDisplayLib.hpp"

int		main( void )
{
	{
		void *	handle;
		IDisplayLib	*(*GraphicCreator)();
		void		(*GraphicDestructor)(IDisplayLib *);

		handle = dlopen("lib/libftcurse.dylib", RTLD_NOW);
		if (!handle)
		{
			std::cout << "Error opening dynlib" << std::endl;
			return (1);
		}
	
		GraphicCreator = (IDisplayLib *(*)()) dlsym(handle, "createGraphic");
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
		obj = GraphicCreator();
		obj->introduce();
		GraphicDestructor(obj);
	
		dlclose(handle);
	}
	{
		void *	handle;
		IDisplayLib	*(*GraphicCreator)();
		void		(*GraphicDestructor)(IDisplayLib *);

		handle = dlopen("lib/libftsfml.dylib", RTLD_NOW);
		if (!handle)
		{
			std::cout << "Error opening dynlib" << std::endl;
			return (1);
		}
	
		GraphicCreator = (IDisplayLib *(*)()) dlsym(handle, "createGraphic");
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
		obj = GraphicCreator();
		obj->introduce();
		GraphicDestructor(obj);
	
		dlclose(handle);
	}
	{
		void *	handle;
		IDisplayLib	*(*GraphicCreator)();
		void		(*GraphicDestructor)(IDisplayLib *);

		handle = dlopen("lib/libftcurse.dylib", RTLD_NOW);
		if (!handle)
		{
			std::cout << "Error opening dynlib" << std::endl;
			return (1);
		}
	
		GraphicCreator = (IDisplayLib *(*)()) dlsym(handle, "createGraphic");
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
		obj = GraphicCreator();
		obj->introduce();
		GraphicDestructor(obj);
	
		dlclose(handle);
	}
	return (0);
}
