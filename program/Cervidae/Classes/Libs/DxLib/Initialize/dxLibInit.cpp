
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../dxLibDefine.h"
#include "dxLibInit.h"


// DXライブラリが初期化されているか
bool		dxInit_IsDxLibInit()
{
	auto isInit = DxLib::DxLib_IsInit();
	if( isInit == FALSE ){
		DEBUG_PRINT("");
		return false;	// 初期化されていない
	}
	return true;//	初期化されている
}
// ウインドウモードで起動するか
bool		dxInit_CheckWindowModePlay()
{
	if ( MessageBox( NULL, "ウインドウモードで起動しますか？", "画面モード確認",  MB_YESNO ) == IDYES )
	{
		// 「はい」が選択された場合はウインドウモードで起動
		DxLib::ChangeWindowMode( TRUE );
		return true;
	}
	DEBUG_PRINT("");
	return false;
}
// 低処理負荷モードで起動するか
bool		dxInit_CheckLowSpecModePlay()
{
	// 低処理負荷モードで起動するか確認する
	if ( MessageBox( NULL, "低処理負荷モードで起動しますか？", "処理負荷モード確認",  MB_YESNO ) == IDYES )
	{
		// 「はい」が選択された場合は低処理負荷モードフラグを立てる
		dxInit_SpecModeSetEnableXAudioFlag( TRUE );
		return true;
	}
	DEBUG_PRINT("");
	return false;
}
// 低処理負荷モードかどうかでXAudioを使用するかどうかの設定を変更する
bool		dxInit_SpecModeSetEnableXAudioFlag( const int setFlag )
{
	// ( TRUE:使用する(デフォルト)  FALSE:使用しない )
	auto isSuccess = DxLib::SetEnableXAudioFlag( setFlag ? FALSE : TRUE );

	return true;
}
// メインウインドウが非アクティブ状態でも処理を実行するかどうか
int		dxInit_SetAlwaysActiveRunEnable( const int setFlag )
{
	return 0;
}






