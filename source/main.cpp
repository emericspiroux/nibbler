#include <iostream>
#include <dlfcn.h>
#include "nibbler.hpp"
#include "ilib.hpp"

int		main( void )
{
	{
		void *	handle;
		IGraphics	*(*GraphicCreator)();
		void		(*GraphicDestructor)(IGraphics *);

		handle = dlopen("lib/lib1.dylib", RTLD_NOW);
		if (!handle)
		{
			std::cout << "Error opening dynlib" << std::endl;
			return (1);
		}
	
		GraphicCreator = (IGraphics *(*)()) dlsym(handle, "createGraphic");
		if (!GraphicCreator)
		{
			std::cout << "Error finding symbol creator" << std::endl;
			return (1);
		}
		GraphicDestructor = (void (*)(IGraphics *)) dlsym(handle, "deleteGraphic");
		if (!GraphicDestructor)
		{
			std::cout << "Error finding symbol destructor" << std::endl;
			return (1);
		}
	
		IGraphics *	obj;
		obj = GraphicCreator();
		obj->introduce();
		GraphicDestructor(obj);
	
		dlclose(handle);
	}
	{
		void *	handle;
		IGraphics	*(*GraphicCreator)();
		void		(*GraphicDestructor)(IGraphics *);

		handle = dlopen("lib/lib2.dylib", RTLD_NOW);
		if (!handle)
		{
			std::cout << "Error opening dynlib" << std::endl;
			return (1);
		}
	
		GraphicCreator = (IGraphics *(*)()) dlsym(handle, "createGraphic");
		if (!GraphicCreator)
		{
			std::cout << "Error finding symbol creator" << std::endl;
			return (1);
		}
		GraphicDestructor = (void (*)(IGraphics *)) dlsym(handle, "deleteGraphic");
		if (!GraphicDestructor)
		{
			std::cout << "Error finding symbol destructor" << std::endl;
			return (1);
		}
	
		IGraphics *	obj;
		obj = GraphicCreator();
		obj->introduce();
		GraphicDestructor(obj);
	
		dlclose(handle);
	}
	return (0);
}
