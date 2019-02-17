
#include "Main.h"
#include "Common/CommonList.h"
#include "Common/CervidaeLib/CLDefine.h"
#include "Libs/DxLib/dxLibDefine.h"
#include "System/AppSystem.h"
#include "Libs/DxLib/Debug/dxLibDebug.h"

//=================================================================================//
//  Main.cpp
//  Created by kashima akihiro on 2018/10/15.
//=================================================================================//


// DXライブラリ
// int main( int argc, char *argv[] )はコンソールウィンドウ表示
int APIENTRY  WinMain(	HINSTANCE	hInstance,
						HINSTANCE	hPrevInstance,
						LPSTR		lpCmdLine,
						int			nCmdShow )
{
	UNUSED_VARIABLE( hInstance);
	UNUSED_VARIABLE( hPrevInstance);
	UNUSED_VARIABLE( lpCmdLine);

	AppSystem * pAppSystem = new AppSystem();
	if( pAppSystem != nullptr )
	{
		pAppSystem->appSystemMain();
	}

	// メイン関数からreturnするとプログラムが終了する。0を返すと正常終了扱い。1を返すと異常終了扱い(エラーは出ない)
	return 0;
}
















