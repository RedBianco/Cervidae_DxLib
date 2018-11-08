
#include <windows.h>
#include "DxLib.h"
#include "CLAppDelegate.h"
#include "Libs/DxLib/dxLibDefine.h"
#include "System/AppSystem.h"
#include "Common/CervidaeLib/CLDefine.h"
#include "Common/CommonList.h"

//=================================================================================//
//  CLAppDelegate.cpp
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/15.
//=================================================================================//



// DXライブラリ
// int main( int argc, char *argv[] )はコンソールウィンドウ表示
int APIENTRY  WinMain(	HINSTANCE	hInstance,
						HINSTANCE	hPrevInstance,
						LPSTR		lpszCmdLine,
						int			nCmdShow )
{
	SetGraphMode( DxLibCommonDefine::DISPLAY_RESOLUTION_WIDTH, DxLibCommonDefine::DISPLAY_RESOLUTION_HEIGHT, 32 );
	SetMainWindowText( CervidaeLibDefine::nAPP_TITLE_NAME );
	ChangeWindowMode( DxLibCommonDefine::DEFAULT_SCREEN_MODE );
	if( DxLib_Init() == -1 ){
		return -1;
	}

	AppSystem * pAppSystem = new AppSystem();
	if( pAppSystem != nullptr )
	{
		pAppSystem->appSystemMain();
	}

	
	WaitKey();
	DxLib_End();



	return 0;
}
















