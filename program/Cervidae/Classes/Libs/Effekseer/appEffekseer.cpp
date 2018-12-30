
#include "DxLib.h"
#include "../../Common/CommonList.h"
#include "../../Common/CervidaeLib/CLDefine.h"
#include "../DxLib/dxLibDefine.h"
#include "appEffekseer.h"
#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))
#include <EffekseerForDXLib.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////////
/*
    @Effekseer 2Dエフェクトライブラリ
    2018.12.27

    ※Windows8 の環境でEffekseer起動にはDirectXのEndUserRuntimeが必要
	※DXライブラリの仕様でエフェクト再生前に何かしらの描画処理を行わないとDXライブラリ側の描画が行われない
	
	＜SAMPLE＞
	→ Effkseer_Init前にやる事

		//	DirectXEx9を使用しないようにする。
		//	Effekseerを使用するには必ず設定する。
		SetUseDirect3D9Ex( FALSE );

	→ Effkseer_Init後にやる事

		//	Zバッファを有効にする。
		//	Effekseerを使用する場合、2DゲームでもZバッファを使用する。
		SetUseZBuffer3D( TRUE );

		//	Zバッファへの書き込みを有効にする。
		//	Effekseerを使用する場合、2DゲームでもZバッファを使用する。
		SetWriteZBuffer3D( TRUE );

	→ 毎フレーム

		//	Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer2D();

		//	Effekseerにより再生中のエフェクトを描画する。
		DrawEffekseer2D();

	＜プロパティの設定＞
	※32bitのみ対応なので実装作業一時中止
	

*/


#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))

int		AppLib::Effekseer::libSystemInit()
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

	ERROR_PRINT("[LIB] Effekseer : Effekseer::systemInitialize() CLEAR\n");

    return 0;
}
void	AppLib::Effekseer::libSetZBuffer()
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


AppEffekseerController::AppEffekseerController()
{
}
AppEffekseerController::~AppEffekseerController()
{
}

void	AppEffekseerController::libSetPlayZBuffer()
{

}

void    AppEffekseerController::libSetup()
{

}

void	AppEffekseerController::libEnd()
{
	// Effekseerを終了する
	Effkseer_End();
}

int		AppEffekseerController::libFileLoad( char * szFile, int * nLoadHandle )
{
	return 0;
}

int		AppEffekseerController::libFileLoad( char * szFile )
{
	return 0;
}

int		AppEffekseerController::libEffect2DPlay( const int fileHandle )
{
	return 0;
}
int		AppEffekseerController::libEffect2DPlay( const int fileHandle, float fSetScale )
{
	return 0;
}

int		AppEffekseerController::libEffectSetPos2DPlay( const int fileHandle, float fSetX, float fSetY, float fSetScale )
{
	return 0;
}

int		AppEffekseerController::libSet2DPlayScale( const int fileHandle, float fSetScale )
{
	return 0;
}

int		AppEffekseerController::libSet2DPlayPos( const int fileHandle, float fSetX, float fSetY )
{
	return 0;
}
int		AppEffekseerController::libSet2DPlayRot( const int fileHandle, float fRotX, float fRotY, float fRotZ )
{
	return 0;
}
int		AppEffekseerController::libSet2DPlayRot( const int fileHandle, float fRotZ )
{
	return 0;
}

int		AppEffekseerController::libIsPlay2D( const int fileHandle )
{
	return 0;
}

unsigned int	AppEffekseerController::libIsEfkFileExist( char * szPlayFile )
{
	return 0;
}

int		AppEffekseerController::libPlayUpdate()
{
	return 0;
}



#endif// ( MIDDLEWARE_EFFEKSEER_USE_ENABLE )




















