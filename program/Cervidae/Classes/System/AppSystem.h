#pragma once

//=================================================================================//
//  AppSystem.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/06.
//=================================================================================//

#include "../Libs/DxLib/Input/dxLibKeyPadUtility.h"
#include "../Libs/Effekseer/appEffekseer.h"
#include "../Libs/DxLib/Resources/appResourcesConfig.h"
#include "../Libs/DxLib/Resources/appResources.h"

/**
 *	@class	
 *
 */
class AppSystem : 
			public DxLib::AppKeyPadController,
			public DxLib::AppVramFileManager
#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
			, public Lib::EffekseerController
#endif
{
private:

	const unsigned int   FRAME_UPDATE_SEC = 1000000;  // マイクロセカンド

	enum {
		eROUTE_INIT = 0,
		eROUTE_ADVANCE_INIT,
		eROUTE_RESOURCES_ENTRY,
		eROUTE_RESOURCES_LODING,

		eROUTE_APP_EXIT,

	} ENUM_APP_PROCESS_ROUTE;


public:
	AppSystem();
	~AppSystem();

public:

	// 一つ前のフレームの時間
	LONGLONG	m_PrevTime;
	// 状態推移処理で推移させる時間
	float		m_StepTime;
	// １フレームで状態推移処理を行う回数
	int			m_StepNum;

	// タスクシステム情報
//	STaskSystemInfo		m_TaskSystemInfo;
	// ゲームメインタスクのタスク情報構造体のアドレスを格納するポインタ変数
//	STaskInfo*			m_appTaskInfo;

	// 描画管理情報


	// Windows情報
//	UI::WindowObjectData*	m_appBaseWin;

private:

	LONGLONG	m_BackDispFrameTime;	// 前回フレームレート表示用にフレームカウントをリセットした時間
	int			m_FrameCounter;			// フレームレート表示用のフレームカウンタ
	int			m_DispFrameCount;		// フレームレート表示で表示するフレームレート
	bool		m_IsExitApp;			// アプリを終了するかどうかのフラグ
	bool		m_LowSpecMode;			// 低処理負荷モードかどうかのフラグ
	int			m_LocalStep;			// 

public:
	AppSystem * createInstance();

	bool		appSystemMain();

	void		setLowSpecMode( const bool setValue ){ m_LowSpecMode = setValue; }
	bool		getLowSpecMode() const { return m_LowSpecMode; }

	void		setExitAppFlag( const bool setValue ) { m_IsExitApp = setValue; }
	bool		isExitApp() const { return m_IsExitApp; }

	// FPS値取得
	int			getDispFrameCount() const { return m_DispFrameCount; }

private:

	void		appSystemClean();

	int			appSystemInitialize();				// Application起動時の初期化処理
	bool		appSystemStartSetup();				// 初期化処理制御フロー
	void		appSystemShutdown();
	bool		appSystemUpdate();
	bool		appProcessUpdate();
	bool		appTaskUpdate();
	void		appSystemRenderUpdate();			// 描画処理更新

	bool		appSystemDxBeforeProcess();			// DxLib_Init()のコール前に実行する処理
	bool		appSystemDxAfterProcess();			// DxLib_Init()のコール後に実行する処理

	void		appSystemAdvanceSetup();
	void		appSystemResourcesSetup( int processStep = 0 );


	// PROJECT_DEBUG
	bool			appSystemDebugSetting();
	static void		appSystemDebugStart();
	static void		appSystemDebugEnd();
	static int		appSystemDebugMain();
	static void		appSystemRenderEnd();
};


/* End AppSystem.h */








