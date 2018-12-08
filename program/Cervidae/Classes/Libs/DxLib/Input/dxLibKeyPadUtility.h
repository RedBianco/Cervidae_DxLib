#pragma once

#include "DxLib.h"
//============================================================================//
//  dxLibKeyPadUtility.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/04.
//============================================================================//

class AppKeyPadController
{
public:
	AppKeyPadController();
	virtual	~AppKeyPadController();
	
public:
	char				m_KeyBuff_[256];				//	キーバッファ
	int				m_KeyFlag_[256];				//	0:入力されていない 1:入力された瞬間 2:入力されている
	int				m_KeyStatus_;					//	入力ステータス
	int				m_KeyInputMode_;			//	入力キーボード(0：通常ゲーム、1：デバッグ)

#if defined( PROJECT_DEBUG )
	char				debKeyBuff_[256];				//	デバッグ用：キーバッファ
	int				debKeyFlag_[256];				//	デバッグ用：0:入力されていない 1:入力された瞬間 2:入力されている
#endif

	unsigned int	uiInputLockBit_;				//	入力ロック設定

	struct 
	{
		int		m_ConnectNum_;			//*! @param	ジョイパッド接続数 */
		bool		m_PadEnable_;				//*! @param	ジョイパッド接続制御 ON/OFF */
		int		m_InputFlag_;				//*! @param	 */

		bool		m_VibFlag_;					//*! @param	ジョイパッド振動設定( TRUE:使用する, FALSE:使用しない ) */
		int		m_VibPower_;				//*! @param	ジョイパッド振動パワー */
		int		m_VibTime_;				//*! @param	ジョイパッド振動させる時間(ミリ秒単位) */

#if defined( PROJECT_DEBUG )
		int			debPadInput_;
		char			debInstInfo_[ 64];
		char			debDeviceInfo_[ 64];
#endif
	} dxPadlib_;

public:
	// キー・パッド入力システム基本初期化処理
	void			inputStatusClear( void );
	// キー・パッド入力システムランタイム
	void			inputRuntime( void );
	// キー・パッド入力ロック設定( 0:キー入力システム, 1:パッド入力システム )
	void			inputSystemApply( const bool  bInputApply, const bool  bApplyFlag );
	void			inputKeyModeSet( const int  setMode);
	int			inputKeyModeGet() const { return m_KeyInputMode_;  }
	bool			inputModeDebug( void );

	// キー入力システムランタイム(最新の全てのキー入力状態を取得)
	int			updateKeyInput( const int  iKeyList = 0 );
	// キーを"１回"押したかを判定する
	int			keyInputOneCheck( const int  iKeyList, int iKeyFrame = 1, int * pKeyOutFlag = nullptr );
	// キーを押し続けているか判定する
	int			keyInputDirectCheck( const int  iKeyList, int iKeyFrame = 1, int * pKeyOutFlag = nullptr );
	// キーロック設定( TRUE:ロックする, FALSE:ロック解除 )
	void			keyInputLockEnable( const bool  bLockFlag );
	// キーロック設定を取得
	bool			isKeyInputLockEnable( void );

	////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////
	// パッドシステム基本初期化
	bool			padParamInitialize( void );
	// パッド入力システム毎フレーム処理
	void			updatePadInput( void );
	// ジョイパッドの接続数を取得する
	int			getPadInputConnectNum( void );
	// ジョイパッドロック設定( TRUE:ロックする, FALSE:ロック解除 )
	void			padInputLockEnable( const bool  bLockFlag );
	// ジョイパッドロック設定を取得
	bool			isPadInputLockEnable( void );

	// ジョイパッド振動開始処理
	int			padInputVibActionStart( const int vibInputType, int vibTime );
	// ジョイパッド振動停止処理
	void			padInputVibActionEnd( const int vibInputType );
	// ジョイパッド振動パワー値設定( 0 ～ 1000 )
	void			setPadInputVibPower( int  iVibPower );
	// ジョイパッド振動時間取得(ミリ秒単位)
	int			getPadInputVibActionTime( void );
	// ジョイパッドの振動機能をオンに
	void			setPadVibActionOn( void );
	// ジョイパッドの振動機能設定を取得
	bool			getPadVibActionFlag( void );
	// 接続されているジョイパッドのDirectInputから取得できる情報を得る
	int			getPadDeviceDirectInput( DINPUT_JOYSTATE * pGetDInput );

#if defined( PROJECT_DEBUG )
	// 
	int			debKeyInputRuntime( const int  iKeyList = 0 );
	// キーを"１回"押したかを判定する
	int			debKeyInputOneCheck( const int  iKeyList, int iKeyFrame = 1 );
	// キーを押し続けているか判定する
	int			debKeyInputDirectCheck( const int  iKeyList, int iKeyFrame = 1 );
#endif
};


/* End dxLibKeyPadUtility.h */
