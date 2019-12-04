#pragma once

//=================================================================================//
//  appSystem.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/06.
//=================================================================================//

#include "../Libs/Effekseer/appEffekseer.h"
#include "../Libs/DxLib/Resources/appResourcesConfig.h"
#include "../Libs/DxLib/Resources/appResources.h"
#include "Task/TaskCore.h"

namespace UI {
	class WindowObjectData;
}
/**
 *	@class	
 *
 */
class AppSystem : 
			public DxLib::AppVramFileManager
//			, public App::WindowObjectManager
#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
			, public Lib::EffekseerController
#endif
#if ( defined( __APP_PROCESS_TASK_MANAGE ) )
			, public App::TaskManager
#endif
{
private:
	/** マイクロセカンド */
	const unsigned int	FRAME_UPDATE_SEC = 1000000;
	/** １フレームの最大時間 */
	const float			MAX_DELTA_TIME = (1.0f / 120.0f);
	/** 一度に処理する最大フレーム数 */
	const int			MAX_FRAME_NUM = (8);

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

	LONGLONG	m_PrevTime;			// 一つ前のフレームの時間
	float		m_StepTime;			// 状態推移処理で推移させる時間
	int			m_StepNum;			// １フレームで状態推移処理を行う回数

	// タスクシステム情報
	STaskSystemInfo	TaskSystemInfo;
	// ゲームメインタスクのタスク情報構造体のアドレスを格納するポインタ変数
	STaskInfo*		GameMainTaskInfo;

	// 描画管理情報


	// エフェクト管理情報
#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
#endif

	// ウィンドウオブジェクト情報
//	std::vector< UI::WindowObjectData*>	m_appWinObj;

private:

	LONGLONG	m_BackDispFrameTime;	// 前回フレームレート表示用にフレームカウントをリセットした時間
	int			m_FrameCounter;			// フレームレート表示用のフレームカウンタ
	int			m_DispFrameCount;		// フレームレート表示で表示するフレームレート
	bool		m_IsExitApp;			// アプリを終了するかどうかのフラグ
	bool		m_LowSpecMode;			// 低処理負荷モードかどうかのフラグ
	int			m_LocalStep;			// 

public:
	static AppSystem * createInstance();

	bool		appSystemMain();

	void		setLowSpecMode( const bool setValue ){ m_LowSpecMode = setValue; }
	bool		getLowSpecMode() const { return m_LowSpecMode; }

	void		setExitAppFlag( const bool setValue ) { m_IsExitApp = setValue; }
	bool		isExitApp() const { return m_IsExitApp; }

	// FPS値取得
	int			getDispFrameCount() const { return m_DispFrameCount; }

private:

	void		appSystemClean();
	void		appSystemTerminate();

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

private:

	STaskSystemInfo* System_GetTaskSystemInfo( void ) { return &TaskSystemInfo; }

	bool		appSettingSceneRun();

	// 状態推移処理を行う
	//     戻り値 : 処理が正常に終了したかどうか(true:正常に終了した  false:エラーが発生した)
	bool		appSystemStep(
		float StepTime	// 推移させる時間( 単位 : 秒 )
	);

	// フェード処理の描画を行う
	void		appSystemFadeRender( void );

};


/* End appSystem.h */








