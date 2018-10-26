

#include "CLAppDelegate.h"
#include <windows.h>
#include "DxLib.h"
#include "Common/CervidaeLib/CLDefine.h"
#include "Common/CervidaeCommon.h"

//===================================================================================
//  CLAppDelegate.cpp
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/15.
//===================================================================================



// DXƒ‰ƒCƒuƒ‰ƒŠ
int APIENTRY  WinMain(	HINSTANCE	hInstance,
						HINSTANCE	hPrevInstance,
						LPSTR	lpszCmdLine,
						int		nCmdShow )
{
	ChangeWindowMode( CervidaeDxLib::DEFAULT_SCREEN_MODE );
	if( DxLib_Init() == -1 ){
		return -1;
	}

	
	WaitKey();
	DxLib_End();



	return 0;
}
















