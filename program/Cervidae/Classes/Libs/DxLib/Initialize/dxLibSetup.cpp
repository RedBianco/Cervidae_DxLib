

#include "../dxLibDefine.h"
#include "dxLibSetup.h"
#include "dxLibInit.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../../../Common/CommonList.h"

// DXライブラリの基本開始設定処理
// ※全て DxLib_Init の前に呼ぶ必要の処理群
bool		dxLib_InitBeforeSetup( void )
{
	DxLib::SetGraphMode(	DxLibCommon::Disp::DISPLAY_RESOLUTION_WIDTH,
										DxLibCommon::Disp::DISPLAY_RESOLUTION_HEIGHT,
										DxLibCommon::Disp::DISPLAY_PLAY_COLORBIT );

	DxLib::SetMainWindowText( CervidaeLibDefine::nAPP_EXE_NAME );

	DxLib::ChangeWindowMode( DxLibCommon::DEFAULT_SCREEN_MODE );

	return true;
}

// DXライブラリの基本開始設定処理
// ※全て DxLib_Init が呼ばれた後に呼ぶ必要のある１回限定処理群
bool		dxLib_InitAfterSetup( void )
{
	if( dxInit_IsDxLibInit() )
	{
		//------------------------------------------------------------------
		//	画面モード変更時( とウインドウモード変更時 )にグラフィックスシステムの設定や
		//	グラフィックハンドルをリセットするかどうかを設定する( TRUE:リセットする( デフォルト )  FALSE:リセットしない )
		//	※デフォルトでは TRUE の状態になっているので、
		//	DxLib_Init の後にでも一回だけ
		//	”SetChangeScreenModeGraphicsSystemResetFlag( FALSE );”
		//	と実行してください、以降 ChangeWindowMode や SetGraphMode が呼ばれても
		//	グラフィックハンドルは削除されず、SetDrawArea や SetDrawBlendMode などの
		//	画面設定もリセットされなくなります
		//------------------------------------------------------------------
		DxLib::SetChangeScreenModeGraphicsSystemResetFlag( FALSE );

		return true;
	}
	return false;
}

// DXライブラリ関係の毎フレーム処理
void		dxLib_SystemUpdate( void )
{

}






