

#include "../../../Common/appCommonParam.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../dxLibDefine.h"
#include "dxLibKeyPadUtility.h"
#include "dxLibInputConfig.h"

//////////////////////////////////////////////////////////////////////////
/*
	DXライブラリ	キー・パッド入力管理システム
	※各シーンクラスに継承させて使用する想定
*/
//////////////////////////////////////////////////////////////////////////

// 
bool	Lib::AppKeyPadController::inputParamInit()
{
	dxKeyInput.m_KeyStatus_ = 0;
	dxKeyInput.m_KeyInputMode_ = DxInput::Command::INPUT_MODE_GAME;

	for( int i = 0; i < DxInput::Info::INPUT_WORKBUFFER; i ++ )
	{
		dxKeyInput.m_KeyBuff_[ i ] = 0;
		dxKeyInput.m_KeyFlag_[ i ] = 0;
#if PROJECT_DEBUG
		dxKeyInput.debKeyBuff_[ i ] = 0;
		dxKeyInput.debKeyFlag_[ i ] = 0;
#endif
	}

	// 各入力タイプロック設定
	inputSystemApply( DxInput::Command::INPUT_TYPE_KEYPAD, FALSE );

	DEBUG_PRINT("[AppLib] AppKeyPadController::inputParamInit() CLEAR\n");

	return true;
}
void	Lib::AppKeyPadController::inputStatusClear( void )
{
}
// キー・パッド入力システムランタイム
void	Lib::AppKeyPadController::updateInputControl( void )
{
	/*
	 * 毎フレームキー入力制御
	 */
	updateKeyInput();
	/*
	 * 毎フレームジョイパッド入力制御
	 */
	updateJoypadInput();
}
// キー・パッド入力ロック設定( 0:キー入力システム, 1:パッド入力システム )
void	Lib::AppKeyPadController::inputSystemApply( const bool  bInputApply, const bool  bApplyFlag )
{
	if( bInputApply == DxInput::Command::INPUT_TYPE_KEYPAD )
	{
		keyInputLockEnable( bApplyFlag ); // キー入力システム
	}else{
		keyInputLockEnable( bApplyFlag ); // パッド入力システム
	}
}
// キー・パッド入力モードセット
void	Lib::AppKeyPadController::inputKeyModeSet( const int  setMode )
{
	dxKeyInput.m_KeyInputMode_ = setMode;
}
bool	Lib::AppKeyPadController::inputModeDebug( void )
{
	return (dxKeyInput.m_KeyInputMode_ == DxInput::Command::INPUT_MODE_DEBUG ) ? true : false;
}
//=========================================================================//
//
//=========================================================================//
int		Lib::AppKeyPadController::updateKeyInput( const int  iKeyList )
{
	if( inputKeyModeGet() == DxInput::Command::INPUT_MODE_GAME ){
		return -1;
	}
	// 全てのキー入力状態を取得(０：成功, －１：エラー発生)
	GetHitKeyStateAll( dxKeyInput.m_KeyBuff_ );
	int  i = 0;
	for( i = 0; i < DxInput::Info::INPUT_WORKBUFFER; i ++ )
	{
		// 入力状態が取得されていれば
		if( dxKeyInput.m_KeyBuff_[i] )
		{
			if( dxKeyInput.m_KeyFlag_[i] == 0 )
			{
				dxKeyInput.m_KeyFlag_[i] = DxInput::Command::lDxKey::KEYINPUT_SINGLE;	// １回押した
			}
			else if( dxKeyInput.m_KeyFlag_[i] == 1 ) // 既に一回押されている状態でもう一回押す(つまり押しっぱなしなら)
			{
				dxKeyInput.m_KeyFlag_[i] = DxInput::Command::lDxKey::KEYINPUT_DIRECT;	// 押しっぱなし判定
			}
		}else {
			dxKeyInput.m_KeyFlag_[i] = 0; // 入力されていない
		}
	}
	return ( 0 );
}
// キーを"１回"押したかを判定する
int		Lib::AppKeyPadController::keyInputOneCheck( const int  iKeyList, int iKeyFrame, int * pKeyOutFlag )
{
	const int i = iKeyList;

	// ロック制限チェック
	if( isKeyInputLockEnable() ){ return -1; };

	if( dxKeyInput.m_KeyBuff_[ i ] )
	{
		// キーを１回押した瞬間判定
		if( dxKeyInput.m_KeyFlag_[ i ] == DxInput::Command::lDxKey::KEYINPUT_SINGLE )
		{
//			if( *pKeyOutFlag != nullptr ){ *pKeyOutFlag = DxInput::Command::lDxKey::KEYINPUT_SINGLE; }
			return ( 1 ); // 判定クリア
		}
	}
	return ( 0 );
}
// キーを押し続けているか判定する
int		Lib::AppKeyPadController::keyInputDirectCheck( const int  iKeyList, int iKeyFrame, int * pKeyOutFlag )
{
	const int	i = iKeyList;

	// ロック制限チェック
	if( isKeyInputLockEnable() ){ return -1; };

	if( dxKeyInput.m_KeyBuff_[ i ] )
	{
		// キー押しっぱなし判定
		if( dxKeyInput.m_KeyFlag_[ i ] == DxInput::Command::lDxKey::KEYINPUT_DIRECT )
		{
//			if( *pKeyOutFlag != nullptr ){ *pKeyOutFlag = DxInput::Command::lDxKey::KEYINPUT_DIRECT; }
			return ( 1 ); // 判定クリア
		}
	}
	return ( 0 );
}
// キーロック設定( TRUE:ロックする, FALSE:ロック解除 )
void	Lib::AppKeyPadController::keyInputLockEnable( const bool  bLockFlag )
{
	// デバッグモード時も適用される
	if( bLockFlag )
	{
		// ロックする
		uiInputLockBit_ |= DxInput::Command::lDxKey::KEYINPUT_LOCK;
	}else{
		// ロック解除
		uiInputLockBit_ &= ~DxInput::Command::lDxKey::KEYINPUT_LOCK;
	}
}
// キーロック設定を取得
bool	Lib::AppKeyPadController::isKeyInputLockEnable( void )
{
	return ( ( uiInputLockBit_ & DxInput::Command::lDxKey::KEYINPUT_LOCK ) != 0 );
}

// パッドシステム基本初期化
bool	Lib::AppKeyPadController::padParamInit( void )
{
	// ジョイパッド接続数を取得
	dxJoypadInput.m_ConnectNum_ = DxLib::GetJoypadNum();
	dxJoypadInput.m_PadEnable_ = false;
	dxJoypadInput.m_InputFlag_ = 0;

	// パッド振動情報
	dxJoypadInput.m_VibFlag_ = DxInput::Command::lDxPad::PADINPUT_VIBRATFLAG;
	dxJoypadInput.m_VibPower_ = DxInput::Command::lDxPad::PADINPUT_VIBDEFPOWER;
	dxJoypadInput.m_VibTime_ = DxInput::Command::lDxPad::PADINPUT_VIBTIME;

#if PROJECT_DEBUG
	dxJoypadInput.debPadInput_ = 0;
	dxJoypadInput.debInstInfo_[64] = {};
	dxJoypadInput.debDeviceInfo_[64] = {};
#endif

	// 各入力タイプロック設定
	inputSystemApply( DxInput::Command::INPUT_TYPE_JOYPAD, TRUE );

	// ジョイパッドの振動機能を使用するかどうかを設定(※デフォルトは使用しない,使用する場合は手動解除)
	DxLib::SetUseJoypadVibrationFlag( static_cast<int>( DxInput::Command::lDxPad::PADINPUT_VIBRATFLAG ) );

	DEBUG_PRINT("[AppLib] AppKeyPadController::padParamInitialize() CLEAR\n");

	return true;
}
// パッド入力システム毎フレーム処理
void	Lib::AppKeyPadController::updateJoypadInput( void )
{
	if( isPadInputLockEnable() ){
		return;	// ロックが掛かっているなら抜ける
	}

	int nJoyPadLinkNum_ = DxLib::GetJoypadNum();	// ジョイパッドが接続されている数を取得する
	if( nJoyPadLinkNum_ != dxJoypadInput.m_ConnectNum_ )
	{
		dxJoypadInput.m_ConnectNum_ = nJoyPadLinkNum_;	// 毎フレーム見てパッド接続数が変わっていれば更新する
	}
//	if( nJoyPadLinkNum_ <= 0 )
//	{
//		dxJoypadInput.m_PadEnable_ = false;
//	}
}

// ジョイパッドの接続数を取得する
int		Lib::AppKeyPadController::getPadInputConnectNum( void )
{
	return dxJoypadInput.m_ConnectNum_;
}
// ジョイパッドロック設定( TRUE:ロックする, FALSE:ロック解除 )
void	Lib::AppKeyPadController::padInputLockEnable( const bool  bLockFlag )
{
	if( bLockFlag )
	{
		uiInputLockBit_ |= DxInput::Command::lDxPad::PADINPUT_LOCK;
	}else{
		uiInputLockBit_ &= ~DxInput::Command::lDxPad::PADINPUT_LOCK;
	}
}
// ジョイパッドロック設定を取得
bool	Lib::AppKeyPadController::isPadInputLockEnable( void )
{
	return ((uiInputLockBit_ & DxInput::Command::lDxPad::PADINPUT_LOCK) != 0);
}
//=========================================================================//
// ジョイパッド振動開始処理
//	InputType	:	振動を開始するパッドの識別子
//					DX_INPUT_PAD1		:	パッド１
//					DX_INPUT_PAD2		:	パッド２
//					DX_INPUT_PAD3		:	パッド３
//					DX_INPUT_PAD4		:	パッド４
//		Power	:	振動の強さ(0～1000)
//		 Time	:	振動させる時間(ミリ秒単位)
//			-1 で StopJoypadVibration が呼ばれるまで振動し続ける
//	戻り値	  ０ : 成功
//			－１ : エラー発生
//	【例】パッド１を最大の振動の強さで２秒間振動させます。
//	StartJoypadVibration( DX_INPUT_PAD1, 1000, 2000 ) ;
int		Lib::AppKeyPadController::padInputVibActionStart( const int vibInputType, int vibTime )
{
	if( vibTime < 0 ){
		vibTime = 1000;
	}

	// 振動開始
	auto nvibRResult_ = DxLib::StartJoypadVibration( vibInputType, dxJoypadInput.m_VibPower_, vibTime );
	if( nvibRResult_ == -1 )
	{
		// エラー
		return ( -1 );
	}
	// 振動の強さ
	dxJoypadInput.m_VibPower_ = dxJoypadInput.m_VibPower_;
	// 振動させる時間
	dxJoypadInput.m_VibTime_ = vibTime;

	return ( 0 );
}
// ジョイパッド振動停止処理
void	Lib::AppKeyPadController::padInputVibActionEnd( const int vibInputType )
{
	if( getPadInputVibActionTime() == -1 )
	{
		DxLib::StopJoypadVibration( vibInputType );
	}
}
// ジョイパッド振動パワー値設定( 0 ～ 1000 )
void	Lib::AppKeyPadController::setPadInputVibPower( int  setVibPower )
{
	if( setVibPower > DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX ){
		ERROR_PRINT("__ERROR__ : dxLib_SetPadInputVibPower VibPowerOver[%d]\n", DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX );
		setVibPower = DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX;
	}
	dxJoypadInput.m_VibPower_ = setVibPower;
}
// ジョイパッド振動時間取得(ミリ秒単位)
int		Lib::AppKeyPadController::getPadInputVibActionTime( void )
{
	return ( dxJoypadInput.m_VibTime_ );
}
// ジョイパッドの振動機能をオンに
void	Lib::AppKeyPadController::setPadVibActionOn( void )
{
	// ジョイパッドの振動機能を使用解除
	DxLib::SetUseJoypadVibrationFlag( true );
	dxJoypadInput.m_VibFlag_ = true;
}
// ジョイパッドの振動機能設定を取得
bool	Lib::AppKeyPadController::getPadVibActionFlag( void )
{
	return ( dxJoypadInput.m_VibFlag_ );
}
//=========================================================================//
// 接続されているジョイパッドのDirectInputから取得できる情報を得る
//	<引数>
//		InputType : 入力状態を取得するパッドの識別子
//							DX_INPUT_PAD1　　　　: パッド１
//							DX_INPUT_PAD2　　　　: パッド２
//							DX_INPUT_PAD3　　　　: パッド３
//							DX_INPUT_PAD4　　　　: パッド４
//		DInputState	: DirectInputから得られる情報を代入する DINPUT_JOYSTATE 型構造体のアドレス
//	<戻る>
//		　０：成功
//		－１：エラー発生
int		Lib::AppKeyPadController::getPadDeviceDirectInput( DINPUT_JOYSTATE * pGetDInput )
{
	// 入力状態を取得
	DxLib::GetJoypadDirectInputState( DX_INPUT_PAD1, pGetDInput ) ;
	if( pGetDInput == nullptr ){
		return ( -1 ); // 取得に失敗
	}
	// 取得は成功
	return 0;
}

#if PROJECT_DEBUG
// 
int		Lib::AppKeyPadController::debKeyInputRuntime( const int  iKeyList )
{
	return 0;
}
// キーを"１回"押したかを判定する
int		Lib::AppKeyPadController::debKeyInputOneCheck( const int  iKeyList, int iKeyFrame )
{
	return 0;
}
// キーを押し続けているか判定する
int		Lib::AppKeyPadController::debKeyInputDirectCheck( const int  iKeyList, int iKeyFrame )
{
	return 0;
}
#endif