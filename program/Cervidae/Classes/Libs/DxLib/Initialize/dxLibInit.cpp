
#include "DxLib.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../dxLibDefine.h"
#include "dxLibInit.h"


// DXライブラリが初期化されているか
bool		dxInit_IsDxLibInit()
{
	auto isInit = DxLib::DxLib_IsInit();
	if( isInit == FALSE ){
		ERROR_PRINT("");
		return false;	// 初期化されていない
	}
	return true;//	初期化されている
}
// ウインドウモードで起動するか
bool		dxInit_CheckWindowModePlay()
{
	// TODO:
	if ( MessageBox( NULL, "ウインドウモードで起動しますか？", "画面モード確認",  MB_YESNO ) == IDYES )
	{
		// 「はい」が選択された場合はウインドウモードで起動
		DxLib::ChangeWindowMode( TRUE );
		return true;
	}
	ERROR_PRINT("");
	return false;
}
// 低処理負荷モードで起動するか
bool		dxInit_CheckLowSpecModePlay()
{
	// TODO:
	if ( MessageBox( NULL, "低処理負荷モードで起動しますか？", "処理負荷モード確認",  MB_YESNO ) == IDYES )
	{
		// 「はい」が選択された場合は低処理負荷モードフラグを立てる
		dxInit_SpecModeSetEnableXAudioFlag( TRUE );
		return true;
	}
	ERROR_PRINT("");
	return false;
}
// 低処理負荷モードかどうかでXAudioを使用するかどうかの設定を変更する
bool		dxInit_SpecModeSetEnableXAudioFlag( const int setFlag )
{
	// ( TRUE:使用する(デフォルト)  FALSE:使用しない )
	auto isSuccess = DxLib::SetEnableXAudioFlag( setFlag ? FALSE : TRUE );
	if( isSuccess == 0 ){
	}

	return true;
}
// メインウインドウが非アクティブ状態でも処理を実行するかどうか
int		dxInit_SetAlwaysActiveRunEnable( const int setFlag )
{
	return 0;
}
// ウインドウモードの時にウインドウのサイズを自由に変更出来るようにするかどうかを設定する
//	@brief		メインウインドウの端を掴んでウインドウのサイズを変更できるようにするかどうかの設定を行う
//	@param		フラグ情報(デフォルトはFALSE)
//				TRUE  : 変更出来るようにする
//				FALSE : 変更出来ないようにする(デフォルト)
//	@return     なし
//	@attention  この関数はウインドウモードでソフトを動かしている時に 
//				ウインドウの枠を左クリックで抓まんでウインドウのサイズを自由に 
//				変更できるようにするかどうかを設定する関数です。
//				TRUE を渡すと変更できるようになり、FALSEを渡すと変更出来ないようになります。(起動時には FALSE の状態になっています)
//				
//			《注意》
//				この関数に TRUE を渡してサイズを自由に変更出来るようにした時は、 
//				SetDrawScreen 関数に DX_SCREEN_BACK を渡して、絶対に表画面に直接描画しないようにして下さい。
//				(表画面に直接描画すると正しい描画結果が得られません)
int     dxInit_WinSizeChangeSetEnable( const bool  bEnable )
{
	if( bEnable == FALSE )
	{
		DxLib::SetWindowSizeChangeEnableFlag( FALSE );	/* ウインドウサイズ変更：不可 */
	}else{
		DxLib::SetWindowSizeChangeEnableFlag( TRUE );	/* ウインドウサイズ変更：許可 */
	}
	
	return 0; // 設定成功
}

// メインウインドウが非アクティブ状態時の処理の実行設定
bool    dxInit_SetWindowAlwaysRunEnable( const int bEnable )
{
	auto isSuccess = DxLib::SetAlwaysRunFlag( bEnable );
	if( isSuccess == -1 ){
		return false; // エラー
	}
	return true; // 設定成功
}

// DXライブラリを使用したソフトの二重起動を可能にするかどうかの設定を行う( TRUE:可能にする FALSE:不可能にする( デフォルト ) )
bool	dxInit_SetDoubleStartValidEnable( const int bEnable )
{
	auto isSuccess = DxLib::SetDoubleStartValidFlag( bEnable );
	if( isSuccess == 0 ){
	}

	return true; // 設定成功
}

