

#include "../../../Common/CommonList.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../dxLibDefine.h"
#include "dxLibKeyPadUtility.h"
#include "dxLibInputConfig.h"

/*
	DXライブラリ	キー・パッド入力管理システム
	※各シーンクラスに継承させて使用する想定
*/

AppKeyPadController::AppKeyPadController() :
	m_KeyStatus_( 0 ),
	m_KeyInputMode_( DxInput::Command::INPUT_MODE_GAME ),
	uiInputLockBit_( DxInput::Command::INPUT_LOCK_NONE )
{
	for( int i = 0; i < DxInput::Info::INPUT_WORKBUFFER; i ++ )
	{
		m_KeyBuff_[ i ] = 0;
		m_KeyFlag_[ i ] = 0;
#if defined( PROJECT_DEBUG )
		debKeyBuff_[ i ] = 0;
		debKeyFlag_[ i ] = 0;
#endif
	}
//	memset( m_KeyFlag_, 0, sizeof( m_KeyFlag_ ) * DxInput::Info::INPUT_WORKBUFFER );

	padParamInitialize();

	// 各入力タイプロック設定
	inputSystemApply( DxInput::Command::INPUT_TYPE_KEYPAD, FALSE );
	inputSystemApply( DxInput::Command::INPUT_TYPE_JOYPAD, TRUE );
}
AppKeyPadController::~AppKeyPadController()
{
}

void		AppKeyPadController::inputStatusClear( void )
{
}
// キー・パッド入力システムランタイム
void		AppKeyPadController::inputRuntime( void )
{
	updateKeyInput();

	updatePadInput();
}
// キー・パッド入力ロック設定( 0:キー入力システム, 1:パッド入力システム )
void		AppKeyPadController::inputSystemApply( const bool  bInputApply, const bool  bApplyFlag )
{
	if( bInputApply == DxInput::Command::INPUT_TYPE_KEYPAD )
	{
		keyInputLockEnable( bApplyFlag );	//	キー入力システム
	}else{
		keyInputLockEnable( bApplyFlag );	//	パッド入力システム
	}
}
// キー・パッド入力モードセット
void		AppKeyPadController::inputKeyModeSet( const int  setMode )
{
	m_KeyInputMode_ = setMode;
}
bool		AppKeyPadController::inputModeDebug( void )
{
	return (m_KeyInputMode_ == DxInput::Command::INPUT_MODE_DEBUG ) ? true : false;
}
//=====================================================//
//
//=====================================================//
int		AppKeyPadController::updateKeyInput( const int  iKeyList )
{
	if( inputKeyModeGet() == DxInput::Command::INPUT_MODE_GAME ){
		return -1;
	}
	// 全てのキー入力状態を取得(０：成功, －１：エラー発生)
	GetHitKeyStateAll( m_KeyBuff_ );
	int  i = 0;
	for( i = 0; i < DxInput::Info::INPUT_WORKBUFFER; i ++ )
	{
		// 入力状態が取得されていれば
		if( m_KeyBuff_[i] )
		{
			if( m_KeyFlag_[i] == 0 )
			{
				m_KeyFlag_[i] = DxInput::Command::lDxKey::KEYINPUT_SINGLE;	//	１回押した
			}
			else if( m_KeyFlag_[i] == 1 ) // 既に一回押されている状態でもう一回押す(つまり押しっぱなしなら)
			{
				m_KeyFlag_[i] = DxInput::Command::lDxKey::KEYINPUT_DIRECT;	//	押しっぱなし判定
			}
		}else {
			m_KeyFlag_[i] = 0;		//	入力されていない
		}
	}
	return ( 0 );
}
// キーを"１回"押したかを判定する
int		AppKeyPadController::keyInputOneCheck( const int  iKeyList, int iKeyFrame, int * pKeyOutFlag )
{
	const int i = iKeyList;

	// ロック制限チェック
	if( isKeyInputLockEnable() ){ return -1; };

	if( m_KeyBuff_[ i ] )
	{
		//	キーを１回押した瞬間判定
		if( m_KeyFlag_[ i ] == DxInput::Command::lDxKey::KEYINPUT_SINGLE )
		{
//			if( *pKeyOutFlag != nullptr ){ *pKeyOutFlag = DxInput::Command::lDxKey::KEYINPUT_SINGLE; }
			return ( 1 );	//	判定クリア
		}
	}
	return ( 0 );
}
// キーを押し続けているか判定する
int		AppKeyPadController::keyInputDirectCheck( const int  iKeyList, int iKeyFrame, int * pKeyOutFlag )
{
	const int	i = iKeyList;

	//	ロック制限チェック
	if( isKeyInputLockEnable() ){ return -1; };

	if( m_KeyBuff_[ i ] )
	{
		//	キー押しっぱなし判定
		if( m_KeyFlag_[ i ] == DxInput::Command::lDxKey::KEYINPUT_DIRECT )
		{
//			if( *pKeyOutFlag != nullptr ){ *pKeyOutFlag = DxInput::Command::lDxKey::KEYINPUT_DIRECT; }
			return ( 1 );	//	判定クリア
		}
	}
	return ( 0 );
}
// キーロック設定( TRUE:ロックする, FALSE:ロック解除 )
void		AppKeyPadController::keyInputLockEnable( const bool  bLockFlag )
{
	//	デバッグモード時も適用される
	if( bLockFlag )
	{
		//	ロックする
		uiInputLockBit_ |= DxInput::Command::lDxKey::KEYINPUT_LOCK;
	}else{
		//	ロック解除
		uiInputLockBit_ &= ~DxInput::Command::lDxKey::KEYINPUT_LOCK;
	}
}
// キーロック設定を取得
bool		AppKeyPadController::isKeyInputLockEnable( void )
{
	return ( ( uiInputLockBit_ & DxInput::Command::lDxKey::KEYINPUT_LOCK ) != 0 );
}

// パッドシステム基本初期化
bool		AppKeyPadController::padParamInitialize( void )
{
	//	ジョイパッド接続数を取得
	dxPadlib_.m_ConnectNum_	= DxLib::GetJoypadNum();
	dxPadlib_.m_PadEnable_		= false;

	//	パッド振動情報
	dxPadlib_.m_VibFlag_			= DxInput::Command::lDxPad::PADINPUT_VIBRATFLAG;
	dxPadlib_.m_VibPower_			= DxInput::Command::lDxPad::PADINPUT_VIBDEFPOWER;
	dxPadlib_.m_VibTime_			= DxInput::Command::lDxPad::PADINPUT_VIBTIME;

	// ジョイパッドの振動機能を使用するかどうかを設定(※デフォルトは使用しない,使用する場合は手動解除)
	SetUseJoypadVibrationFlag( static_cast<int>( DxInput::Command::lDxPad::PADINPUT_VIBRATFLAG ) );

	ERROR_PRINT( "" );

	return true;
}
// パッド入力システム毎フレーム処理
void		AppKeyPadController::updatePadInput( void )
{
	if( isPadInputLockEnable() ){
		return;	//	ロックが掛かっているなら抜ける
	}

	int nJoyPadLinkNum_ = DxLib::GetJoypadNum();	//	ジョイパッドが接続されている数を取得する
	if( nJoyPadLinkNum_ != dxPadlib_.m_ConnectNum_ )
	{
		dxPadlib_.m_ConnectNum_ = nJoyPadLinkNum_;	//	毎フレーム見てパッド接続数が変わっていれば更新する
	}
//	if( nJoyPadLinkNum_ <= 0 )
//	{
//		dxPadlib_.m_PadEnable_ = false;
//	}
}

// ジョイパッドの接続数を取得する
int		AppKeyPadController::getPadInputConnectNum( void )
{
	return dxPadlib_.m_ConnectNum_;
}
// ジョイパッドロック設定( TRUE:ロックする, FALSE:ロック解除 )
void		AppKeyPadController::padInputLockEnable( const bool  bLockFlag )
{
	if( bLockFlag )
	{
		uiInputLockBit_ |= DxInput::Command::lDxPad::PADINPUT_LOCK;
	}else{
		uiInputLockBit_ &= ~DxInput::Command::lDxPad::PADINPUT_LOCK;
	}
}
// ジョイパッドロック設定を取得
bool		AppKeyPadController::isPadInputLockEnable( void )
{
	return ((uiInputLockBit_ & DxInput::Command::lDxPad::PADINPUT_LOCK) != 0);
}
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
int		AppKeyPadController::padInputVibActionStart( const int vibInputType, int vibTime )
{
	if( vibTime < 0 ){
		vibTime = 1000;
	}

	//	振動開始
	auto	nvibRResult_ = DxLib::StartJoypadVibration( vibInputType, dxPadlib_.m_VibPower_, vibTime );
	if( nvibRResult_ == -1 )
	{
		//	エラー
		return ( -1 );
	}
	//	振動の強さ
	dxPadlib_.m_VibPower_	= dxPadlib_.m_VibPower_;
	//	振動させる時間
	dxPadlib_.m_VibTime_	=  vibTime;

	return ( 0 );
}
// ジョイパッド振動停止処理
void			AppKeyPadController::padInputVibActionEnd( const int vibInputType )
{
	if( getPadInputVibActionTime() == -1 )
	{
		DxLib::StopJoypadVibration( vibInputType );
	}
}
// ジョイパッド振動パワー値設定( 0 ～ 1000 )
void			AppKeyPadController::setPadInputVibPower( int  setVibPower )
{
	if( setVibPower > DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX ){
		ERROR_PRINT("__ERROR__ : dxLib_SetPadInputVibPower VibPowerOver[%d]\n", DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX );
		setVibPower = DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX;
	}
	dxPadlib_.m_VibPower_	= setVibPower;
}
// ジョイパッド振動時間取得(ミリ秒単位)
int			AppKeyPadController::getPadInputVibActionTime( void )
{
	return ( dxPadlib_.m_VibTime_ );
}
// ジョイパッドの振動機能をオンに
void			AppKeyPadController::setPadVibActionOn( void )
{
	// ジョイパッドの振動機能を使用解除
	DxLib::SetUseJoypadVibrationFlag( true );
	dxPadlib_.m_VibFlag_ = true;
}
// ジョイパッドの振動機能設定を取得
bool			AppKeyPadController::getPadVibActionFlag( void )
{
	return ( dxPadlib_.m_VibFlag_ );
}
// 接続されているジョイパッドのDirectInputから取得できる情報を得る
//	<引数>
//		InputType : 入力状態を取得するパッドの識別子
//							DX_INPUT_PAD1　　　　: パッド１
//							DX_INPUT_PAD2　　　　: パッド２
//							DX_INPUT_PAD3　　　　: パッド３
//							DX_INPUT_PAD4　　　　: パッド４
//		DInputState	: DirectInputから得られる情報を代入する DINPUT_JOYSTATE 型構造体のアドレス
//	<戻る>
//			０：成功
//		－１：エラー発生
int			AppKeyPadController::getPadDeviceDirectInput( DINPUT_JOYSTATE * pGetDInput )
{
	// 入力状態を取得
	DxLib::GetJoypadDirectInputState( DX_INPUT_PAD1, pGetDInput ) ;
	if( pGetDInput == nullptr ){
		return ( -1 );	//	取得に失敗
	}
	// 取得は成功
	return 0;
}

#if defined( PROJECT_DEBUG )
#endif







