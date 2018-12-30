
#include "DxLib.h"
#include "../dxLibDefine.h"
#include "dxLibSetup.h"
#include "dxLibInit.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../../../Common/CommonList.h"

// DXライブラリの基本開始設定処理
// ※全て DxLib_Init の前に呼ぶ必要の処理群
bool		dxLib_InitBeforeSetup( void )
{
	DxLib::SetGraphMode( DxLibCommon::Disp::DISPLAY_RESOLUTION_WIDTH,
						 DxLibCommon::Disp::DISPLAY_RESOLUTION_HEIGHT,
						 DxLibCommon::Disp::DISPLAY_PLAY_COLORBIT );

	DxLib::SetMainWindowText( CervidaeLibDefine::nAPP_EXE_NAME );

	DxLib::ChangeWindowMode( DxLibCommon::DEFAULT_SCREEN_MODE );

#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))
	// DirectXEx9を使用しないようにする。
	// ※DxLib_Init の前に呼ぶ必要がある
	// Effekseerを使用するには必ず設定する。
	DxLib::SetUseDirect3D9Ex( FALSE );
#endif

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

		//-----------------------------------------------------------------------
		//	printfDx の結果を画面に出力する際に使用するフォントのサイズを設定
		//------------------------------------------------------------------
		

		//-----------------------------------------------------------------------
		//	メインウインドウが非アクティブ状態でも処理を実行するかどうかを設定する
		//	( TRUE:実行する  FALSE:停止する( デフォルト ) )
		//	※ゲームウィンドウがフォーカスされて無く他のタブやウィンドウを操作している時にゲーム画面を止めるか止めないか
		//	※デフォルトはFALSEでフォーカスされて無いなら処理を止める
		//-----------------------------------------------------------------------
		dxInit_SetWindowAlwaysRunEnable( TRUE );

		//-----------------------------------------------------------------------
		//	ウインドウモード可変調整制御設定(フラグ情報(デフォルトはFALSE))
		//	ウインドウモードの時にウインドウのサイズを自由に変更出来るようにするかどうかを設定
		//-----------------------------------------------------------------------
		dxInit_WinSizeChangeSetEnable( FALSE );





		return true;
	}
	return false;
}

// DXライブラリ関係の毎フレーム処理
void		dxLib_SystemUpdate( void )
{

}






