
#include "DxLib.h"
#include "../../Common/CommonList.h"
#include "../../Common/CervidaeLib/CLDefine.h"
#include "../DxLib/dxLibDefine.h"
#include "appEffekseerLib.h"
#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))
#include <EffekseerForDXLib.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////////
/*
    Effekseerライブラリ
    2019/01/11.
*/


#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))

int		App::EffekseerLib::libSystemInit()
{
	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	// 成功した場合は0、失敗した場合は-1を返す
	if( Effkseer_Init( EFFEKSEER_PARTICLE_DRAW_MAX ) == -1 )
	{
		//	エラー
		ERROR_PRINT("__ERROR__ : Effekseer_LibInit() - SetUpFailed\n" );
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	// 画面モード変更時( とウインドウモード変更時 )にグラフィックスシステムの設定やグラフィックハンドルを
	// リセットするかどうかを設定する( TRUE:リセットする( デフォルト )  FALSE:リセットしない )
	DxLib::SetChangeScreenModeGraphicsSystemResetFlag( FALSE );

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseerに2D描画の設定をする(スクリーンサイズ設定)
	Effekseer_Set2DSetting( DxLibCommon::Disp::DISPLAY_RESOLUTION_WIDTH,
							DxLibCommon::Disp::DISPLAY_RESOLUTION_HEIGHT );

	DEBUG_PRINT("[LIB] Effekseer : Effekseer::systemInitialize() CLEAR\n");

    return 0;
}
void	App::EffekseerLib::libSetZBuffer()
{
	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	// ( ３Ｄ描画のみに影響 )( TRUE:Ｚバッファを使用する  FALSE:Ｚバッファを使用しない( デフォルト ) )
	SetUseZBuffer3D( TRUE );

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	// ( ３Ｄ描画のみに影響 )( TRUE:書き込みを行う  FALSE:書き込みを行わない( デフォルト ) )
	SetWriteZBuffer3D( TRUE );
}


#endif// defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE )


























