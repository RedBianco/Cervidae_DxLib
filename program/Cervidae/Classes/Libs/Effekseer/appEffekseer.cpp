
#include "DxLib.h"
#include "../../Common/appCommonParam.h"
#include "../../Common/CervidaeLib/CLDefine.h"
#include "../DxLib/dxLibDefine.h"
#include "appEffekseer.h"
#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
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

#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )


Lib::EffekseerController::EffekseerController()
{
}
Lib::EffekseerController::~EffekseerController()
{
}
void	Lib::EffekseerController::libSetPlayZBuffer()
{
}
void    Lib::EffekseerController::libSetup()
{
}
void	Lib::EffekseerController::libEnd()
{
	// Effekseerを終了する
	Effkseer_End();
}
void	Lib::EffekseerController::libDataClear()
{
}
int		Lib::EffekseerController::libFileLoad( char * szFile, int * nLoadHandle )
{
	return 0;
}
int		Lib::EffekseerController::libFileLoad( char * szFile )
{
	return 0;
}
int		Lib::EffekseerController::libEffect2DPlay( const int fileHandle )
{
	return 0;
}
int		Lib::EffekseerController::libEffect2DPlay( const int fileHandle, float fSetScale )
{
	return 0;
}
int		Lib::EffekseerController::libEffectSetPos2DPlay( const int fileHandle, float fSetX, float fSetY, float fSetScale )
{
	return 0;
}
int		Lib::EffekseerController::libSet2DPlayScale( const int fileHandle, float fSetScale )
{
	return 0;
}
int		Lib::EffekseerController::libSet2DPlayPos( const int fileHandle, float fSetX, float fSetY )
{
	return 0;
}
int		Lib::EffekseerController::libSet2DPlayRot( const int fileHandle, float fRotX, float fRotY, float fRotZ )
{
	return 0;
}
int		Lib::EffekseerController::libSet2DPlayRot( const int fileHandle, float fRotZ )
{
	return 0;
}
int		Lib::EffekseerController::libIsPlay2D( const int fileHandle )
{
	return 0;
}
unsigned int	Lib::EffekseerController::libIsEfkFileExist( char * szPlayFile )
{
	return 0;
}
int		Lib::EffekseerController::libPlayUpdate()
{
	return 0;
}



#endif// ( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )




















