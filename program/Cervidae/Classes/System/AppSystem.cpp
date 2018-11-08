
#include "AppSystem.h"





AppSystem::AppSystem()
{}
AppSystem::~AppSystem()
{}




bool	AppSystem::appSystemMain()
{
	
	if( !appSystemInitialize() )
	{
		return false;
	}


	if( !appSystemUpdate() )
	{
		return false;
	}


	appSystemTerminate();

	return true;
}


bool	AppSystem::appSystemInitialize()
{
	return true;
}

void	AppSystem::appSystemTerminate()
{

}

bool	AppSystem::appSystemUpdate()
{
	return true;
}




