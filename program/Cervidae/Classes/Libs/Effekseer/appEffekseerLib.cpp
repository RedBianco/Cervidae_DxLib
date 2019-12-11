
#include "DxLib.h"
#include "../../Common/appCommonParam.h"
#include "../../Common/CervidaeLib/CLDefine.h"
#include "../DxLib/dxLibDefine.h"
#include "appEffekseerLib.h"
#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
#include <EffekseerForDXLib.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////////
/*
    Effekseerライブラリの共通部分処理
	※アプリケーションの起動時にコールする関数はクラスに含める意味が無いので別枠で
	ここにまとめる
    
	2019.07.10
*/


#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )

int		App::EffekseerLib::libSystemInit()
{
	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	// 成功した場合は0、失敗した場合は-1を返す
	if( Effkseer_Init( EFFEKSEER_PARTICLE_DRAW_MAX ) == -1 ){
		// エラー
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
	Effekseer_Set2DSetting( DxLibCommon::Parameter::DISPLAY_RESOLUTION_WIDTH,
							DxLibCommon::Parameter::DISPLAY_RESOLUTION_HEIGHT );

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


#endif// ( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )


























