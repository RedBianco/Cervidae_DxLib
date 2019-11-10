
#include "DxLib.h"
#include "../Common/CervidaeLib/CLDefine.h"
#include "../Common/CommonList.h"
#include "../Libs/DxLib/Initialize/dxLibInit.h"
#include "../Libs/DxLib/Initialize/dxLibSetup.h"
#include "../Libs/Effekseer/appEffekseer.h"
#include "AppSystem.h"
#include "AppSetting.h"
#include "../Libs/DxLib/dxLibDefine.h"
#include "../Libs/DxLib/Debug/dxLibDebug.h"

//======================================================================//
//  AppSystem.cpp
//  Created by on 2018/11/06.
//======================================================================//

using SDebugOperat = Singleton<AppLib::DebugModeOperat>;
using SAppParameter = Singleton<AppParameter>;


/// <image url="D:\Program\Project\Develop\cervidae_lib\resources\comment\MkYg.jpg" scale="0.3" />

AppSystem::AppSystem() :
		m_LowSpecMode( false ),
		m_IsExitApp( false ),
		// フレームレート計測用の変数の初期化
		m_BackDispFrameTime( DxLib::GetNowHiPerformanceCount() ),
		m_FrameCounter( 0 ),
		m_DispFrameCount( 0 )
{
#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))
		m_EfkData.clear();
#endif
}
AppSystem::~AppSystem()
{}

void	AppSystem::appSystemClean()
{

}

//==================================================================//
// 
// ( true : 正常に処理を完了した   false : エラーが発生した )
bool	AppSystem::appSystemMain()
{
	
	if( !appSystemInitialize() )
	{
		return false;
	}

	// FrameUpdate
	if( !appSystemUpdate() )
	{
		return false;
	}


	appSystemShutdown();

	return true;
}

bool	AppSystem::appSystemStartSetup()
{
	auto result = false;

	// DxLib_Init完了前処理
	result = dxLib_InitBeforeSetup();
	if( result ){
	}
	result = dxInit_CheckWindowModePlay();
	if( result ){
	}
	result = dxInit_CheckLowSpecModePlay();
	if( result ) {
		setLowSpecMode( TRUE );
	}

	result = appSystemDxBeforeProcess();
	if( result ) {
	}

	int success = DxLib_Init();
	if( success == -1 ) 
	{
		return false;
	}
	DEBUG_PRINT("[Process] DxLib_Init() CLEAR\n");

	result = dxLib_InitAfterSetup();
	if( result ){
		// DxLib_Init完了後の処理
		result = appSystemDxAfterProcess();
		if( result ) {
		}
	}
	DEBUG_PRINT("[Process] AppSystem::appSystemStartSetup() CLEAR\n");
	return true;
}

// Application起動時の初期化処理
int		AppSystem::appSystemInitialize()
{
	auto isDone = appSystemStartSetup();
	if( !isDone ){ return false; }
	// DxLib前、後処理が全て終わった

	// Lua File Loading


#if PROJECT_DEBUG
	// DebugSetting
	isDone = appSystemDebugSetting();
	if( !isDone ){ return false; }
#endif

	DEBUG_PRINT("[Process] AppSystem::appSystemInitialize() CLEAR\n");
	// 初期化成功
	return true;
}
// Application終了処理
void	AppSystem::appSystemShutdown()
{




	// ＤＸライブラリの終了処理
	DxLib::DxLib_End();
}

//==================================================================//
// Application毎フレーム処理
bool	AppSystem::appSystemUpdate()
{
	LONGLONG n_NowTime;

	DxLib::SetDrawScreen( DX_SCREEN_BACK );

	while( DxLib::ProcessMessage() == 0 )
	{
		{
			if( DxLib::CheckHitKey( KEY_INPUT_ESCAPE ) || isExitApp() )
			{
				if( !isExitApp() ){ setExitAppFlag( TRUE ); }
				break;
			}
		}

#if PROJECT_DEBUG
		// DEBUG
		AppLib::getDebugOperatPtr()->debugAppUpdate();
#endif

		if( isExitApp() ) {
			break;	// アプリ終了
		}

		// 各描画情報更新
		appSystemRenderUpdate();

		// 裏画面の内容を表画面に反映させる
		// ScreenFlip関数は垂直同期を取っているため、FPSが自動的にディスプレイのリフレッシュレート以下になる
		if( DxLib::ScreenFlip() != 0 )
		{
		}

		// 現在の時間を取得
		n_NowTime = DxLib::GetNowHiPerformanceCount();

		// フレームレート計測用のカウンタを１足す
		m_FrameCounter ++;
		// 前回フレームレートを更新してから１秒経過したら表示用フレームカウントを更新する
		if ( ( n_NowTime - m_BackDispFrameTime > (1000000)) )
		{
			// 表示用フレームカウントを更新
			m_DispFrameCount = m_FrameCounter;
			// 計測用フレームカウンタを初期化
			m_FrameCounter = 0;
			// 表示用フレームカウントを更新した時間を更新
			m_BackDispFrameTime = n_NowTime;
		}

		// 画面クリア
		DxLib::ClearDrawScreen();
	}// while( DxLib::ProcessMessage() == 0 )


	return true;
}

void	AppSystem::appSystemRenderUpdate()
{

	// フレームレート
	dxCommon_FramerateDisp( getDispFrameCount() );
}

// DxLibInitのコール前に行っておく処理
bool	AppSystem::appSystemDxBeforeProcess()
{
	return true;
}
bool	AppSystem::appSystemDxAfterProcess()
{
	auto result = getAppContainerPtr()->settingBaseInfo();
	if( !result ){ return false; }

	#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))
	//------------------------------------------------------
	// Effekseer関係初期化処理
	// タイミングはDxLib_Initが終わってDxLib関係初期化後処理が終わったら
	App::EffekseerLib::libSystemInit();
	#endif

	DEBUG_PRINT("[Process] AppSystem::appSystemDxAfterProcess() CLEAR\n");

	return true;
}

bool	AppSystem::appSystemDebugSetting()
{
	#if PROJECT_DEBUG
	AppLib::getDebugOperatPtr()->debugMenuNameSet(
					DxLib::DebugConfig::eDEBUG_TYPE_MAIN, "MAIN_MENU" );
	AppLib::getDebugOperatPtr()->debugModeStartProcSet(
					DxLib::DebugConfig::eDEBUG_TYPE_MAIN, "MAIN_MENU", &appSystemDebugStart );
	AppLib::getDebugOperatPtr()->debugModeEndProcSet(
					DxLib::DebugConfig::eDEBUG_TYPE_MAIN, "MAIN_MENU", &appSystemDebugEnd );
	AppLib::getDebugOperatPtr()->debugModeMainProcSet(
					DxLib::DebugConfig::eDEBUG_TYPE_MAIN, "MAIN_MENU", &appSystemDebugMain );
	AppLib::getDebugOperatPtr()->debugModeRenderProcSet(
					DxLib::DebugConfig::eDEBUG_TYPE_MAIN, "MAIN_MENU", &appSystemRenderEnd );

	DEBUG_PRINT("[Process] AppSystem::appSystemDebugSetting() CLEAR\n");

	return true;
	#else
	return false;
	#endif
}

void	AppSystem::appSystemDebugStart()
{
}
void	AppSystem::appSystemDebugEnd()
{
}
int		AppSystem::appSystemDebugMain()
{
	return 0;
}
void	AppSystem::appSystemRenderEnd()
{
}