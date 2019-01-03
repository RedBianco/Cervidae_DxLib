
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



#endif// defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE )




















