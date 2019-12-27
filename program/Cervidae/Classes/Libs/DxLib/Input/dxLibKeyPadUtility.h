#pragma once


//============================================================================//
//  dxLibKeyPadUtility.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/04.
//============================================================================//

// NOTE:当初はクラスに継承させてそっちで各自のデバッグモードを実装する設計を
//      考えていたが
//      ・マルチスレッド的に同時操作出来るのか処理系統がバラバラになりそう
//      の理由でSingleton管理に変更、今後修正の可能性有り
namespace Lib
{
	/**
	 * 
	 */
	struct KeyInputOperat
	{
		char	m_KeyBuff_[256];	//*! @param キーバッファ
		int		m_KeyFlag_[256];	//*! @param 0:入力されていない 1:入力された瞬間 2:入力されている
		int		m_KeyStatus_;		//*! @param 入力ステータス
		int		m_KeyInputMode_;	//*! @param 入力キーボード(0：通常ゲーム、1：デバッグ)

#if PROJECT_DEBUG
		char	debKeyBuff_[256];	//*! @param	デバッグ用：キーバッファ
		int		debKeyFlag_[256];	//*! @param	デバッグ用：0:入力されていない 1:入力された瞬間 2:入力されている
#endif
	};

	/**
	 * 
	 */
	struct JoypadInputOperat
	{
		int		m_ConnectNum_;		//*! @param	ジョイパッド接続数
		bool	m_PadEnable_;		//*! @param	ジョイパッド接続制御 ON/OFF
		int		m_InputFlag_;		//*! @param	

		bool	m_VibFlag_;			//*! @param	ジョイパッド振動設定( TRUE:使用する, FALSE:使用しない )
		int		m_VibPower_;		//*! @param	ジョイパッド振動パワー
		int		m_VibTime_;			//*! @param	ジョイパッド振動させる時間(ミリ秒単位)

#if PROJECT_DEBUG
		int		debPadInput_;
		char	debInstInfo_[64];
		char	debDeviceInfo_[64];
#endif
	};

	/*
	 * 
	 */
	class AppKeyPadController : public Singleton<AppKeyPadController>
	{
		// DebugModeOperatのインスタンスを生成する時に、コンストラクタが呼べなかった為friend指定
		// シングルトンのテンプレート引数に自身を指定したものだけに生成をゆるす
		friend class Singleton<AppKeyPadController>;	// Singleton でのインスタンス作成は許可

	private:

		KeyInputOperat		dxKeyInput;
		JoypadInputOperat	dxJoypadInput;
	
	private:

		unsigned int	uiInputLockBit_;		//*! @param	入力ロック設定

	public:

		// 入力パラメータ初期化
		bool			inputParamInit( void );
		// キー・パッド入力システム基本初期化処理
		void			inputStatusClear( void );
		// キー・パッド入力システムランタイム
		void			updateInputControl( void );
		// キー・パッド入力ロック設定( 0:キー入力システム, 1:パッド入力システム )
		void			inputSystemApply( const bool  bInputApply, const bool  bApplyFlag );
		void			inputKeyModeSet( const int  setMode);
		int				inputKeyModeGet() const { return dxKeyInput.m_KeyInputMode_;  }
		bool			inputModeDebug( void );

		// キー入力システムランタイム(最新の全てのキー入力状態を取得)
		int				updateKeyInput( const int  iKeyList = 0 );
		// キーを"１回"押したかを判定する
		int				keyInputOneCheck( const int  iKeyList, int iKeyFrame = 1, int * pKeyOutFlag = nullptr );
		// キーを押し続けているか判定する
		int				keyInputDirectCheck( const int  iKeyList, int iKeyFrame = 1, int * pKeyOutFlag = nullptr );
		// キーロック設定( TRUE:ロックする, FALSE:ロック解除 )
		void			keyInputLockEnable( const bool  bLockFlag );
		// キーロック設定を取得
		bool			isKeyInputLockEnable( void );

		////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////
		// パッドシステム基本初期化
		bool			padParamInit( void );
		// パッド入力システム毎フレーム処理
		void			updateJoypadInput( void );
		// ジョイパッドの接続数を取得する
		int				getPadInputConnectNum( void );
		// ジョイパッドロック設定( TRUE:ロックする, FALSE:ロック解除 )
		void			padInputLockEnable( const bool  bLockFlag );
		// ジョイパッドロック設定を取得
		bool			isPadInputLockEnable( void );

		// ジョイパッド振動開始処理
		int				padInputVibActionStart( const int vibInputType, int vibTime );
		// ジョイパッド振動停止処理
		void			padInputVibActionEnd( const int vibInputType );
		// ジョイパッド振動パワー値設定( 0 ～ 1000 )
		void			setPadInputVibPower( int  iVibPower );
		// ジョイパッド振動時間取得(ミリ秒単位)
		int				getPadInputVibActionTime( void );
		// ジョイパッドの振動機能をオンに
		void			setPadVibActionOn( void );
		// ジョイパッドの振動機能設定を取得
		bool			getPadVibActionFlag( void );
		// 接続されているジョイパッドのDirectInputから取得できる情報を得る
		int				getPadDeviceDirectInput( DINPUT_JOYSTATE * pGetDInput );

	#if PROJECT_DEBUG
		// 
		int		debKeyInputRuntime( const int iKeyList = 0 );
		// キーを"１回"押したかを判定する
		int		debKeyInputOneCheck( const int iKeyList, int iKeyFrame = 1 );
		// キーを押し続けているか判定する
		int		debKeyInputDirectCheck( const int iKeyList, int iKeyFrame = 1 );
	#endif

	public:
		// コンストラクタ部分をpublicにしてしまうと、AppParameter  container; でインスタンスつくれてしまう
		// 「そのクラスのインスタンスが1つしか生成されないことを保証することができる」
		// と言うのに反するのでprivateにする必要がある。
		AppKeyPadController() {		// 外部でのインスタンス作成は禁止
			inputParamInit();
			padParamInit();
		};
	//	virtual ~DebugModeOperat();
	};

	/* @brief アクセスインターフェース
	*/
	inline AppKeyPadController* getKeyPadOperatPtr(void)
	{
		return Singleton<AppKeyPadController>::getSingletonPtr();
	}
}


/* End dxLibKeyPadUtility.h */
