
#include "DxLib.h"
#include "../Main.h"
#include "../Common/CervidaeLib/CLDefine.h"
#include "../Common/appCommonParam.h"
#include "../Common/appErrorCode.h"
#include "../Common/appProcessCode.h"
#include "../Libs/DxLib/Initialize/dxLibInit.h"
#include "../Libs/DxLib/Initialize/dxLibSetup.h"
#include "../Libs/Effekseer/appEffekseerLib.h"
//#include "Process/Window/appWindowDialog.h"
#include "Task/TaskCore.h"
#include "Task/TaskLib.h"
#include "AppSystem.h"
#include "AppSetting.h"
#include "../Libs/DxLib/dxLibDefine.h"
#include "../Libs/DxLib/Debug/dxLibDebug.h"


//======================================================================//
//  AppSystem.cpp
//  Created by on 2018/11/06.
//======================================================================//

using SCDebugOperat = Singleton<AppLib::DebugModeOperat>;
using SCAppParameter = Singleton<AppParameter>;


/// <image url="D:\Program\Project\Develop\cervidae_lib\resources\comment\MkYg.jpg" scale="0.3" />

/**
 *
 */
AppSystem::AppSystem() :
		// フレームレート計測用の変数の初期化
		m_BackDispFrameTime( DxLib::GetNowHiPerformanceCount() ),
		m_FrameCounter( 0 ),
		m_LowSpecMode( false ),
		m_IsExitApp( false ),
		m_DispFrameCount( 0 ),
		m_LocalStep( eROUTE_INIT )
{
#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
	libDataClear();
#endif

	DEBUG_PRINT("AppSystem : AppSystem コンストラクタ\n");
}
AppSystem::~AppSystem()
{
	DEBUG_PRINT("AppSystem : AppSystem デストラクタ\n");
}

/**
 *
 */
void	AppSystem::appSystemClean()
{

}

//==============================================================================//
//	
//	( true : 正常に処理を完了した   false : エラーが発生した )
bool	AppSystem::appSystemMain()
{
	if( !appSystemInitialize() )
	{
		return false;
	}

	appDebugPrint( DxLib::DebugConfig::eDEBUG_LOG_ERROR, "AppSystem::appSystemMain()\n" );

	// FrameUpdate
	if( !appSystemUpdate() )
	{
		return false;
	}
	if( !appProcessUpdate() )
	{
		return false;
	}

	// アプリシャットダウン処理
	appSystemShutdown();

	return true;
}

//==============================================================================//
//	Application起動時の初期化処理
// 
int		AppSystem::appSystemInitialize()
{
	auto isDone = appSystemStartSetup();
	if( !isDone ){ return false; }
	// DxLib前、後処理が全て終わった

	// DUMMY
	appSystemResourcesSetup( eROUTE_RESOURCES_LODING );


#if PROJECT_DEBUG
	// DebugSetting
	isDone = appSystemDebugSetting();
	if( !isDone ){ return false; }
#endif

	DEBUG_PRINT("[Process] AppSystem::appSystemInitialize() CLEAR\n");
	// 全ての準備を終わらせてタイトルシーンへ遷移する
	return true;
}

//==============================================================================//
//	
// 
bool	AppSystem::appSystemStartSetup()
{
	auto result = false;

	// DxLib_Init完了前処理
	result = dxLib_InitBeforeSetup();
	if( result ){
	}
	// Windowモード起動確認
	result = dxInit_CheckWindowModePlay();
	if( !result ){
		return false;
	}
	// 低処理負荷モード起動確認
	result = dxInit_CheckLowSpecModePlay();
	if( result ) {
		setLowSpecMode( TRUE );
	}

	// DxLib_Initより前に行うシステム側周り処理
	result = appSystemDxBeforeProcess();
	if( result ) {
		DEBUG_PRINT("[Process] AppSystem::appSystemDxBeforeProcess() CLEAR\n");
	}

	// DXライブラリ側の初期化
	// ※DxLib_Initより前だと当たり前だがDxLibのデバッグコメント関数は使えない
	const int isDxLibInit = DxLib_Init();
	if( isDxLibInit == -1 ) 
	{
		return false;
	}
	DEBUG_PRINT("[Process] DxLib_Init() CLEAR\n");
	
	// DxLib_Init完了後のライブラリ周り処理
	result = dxLib_InitAfterSetup();
	if( result ){
		// DxLib_Init完了後のシステム側周り処理
		result = appSystemDxAfterProcess();
		if( result ){

			/**
			 *	ライブラリ以外のアプリケーション用事前準備
			 */
			appSystemAdvanceSetup();
		}
	}
	DEBUG_PRINT("[Process] AppSystem::appSystemStartSetup() CLEAR\n");
	return true;
}

//==============================================================================//
//	Application終了処理
//
void	AppSystem::appSystemShutdown()
{
	DEBUG_PRINT("[Process] AppSystem::appSystemShutdown() EXIT\n");

	// ＤＸライブラリの終了処理
	DxLib::DxLib_End();
}

//////////////////////////////////////////////////////////////////////////////////
//	Application毎フレーム処理
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////
bool	AppSystem::appSystemUpdate()
{
	LONGLONG n_NowTime;

	DxLib::SetDrawScreen( DX_SCREEN_BACK );

	while( DxLib::ProcessMessage() == 0 )
	{
		// 状態推移処理を行う回数分ループ
		{
			if( DxLib::CheckHitKey( KEY_INPUT_ESCAPE ) || isExitApp() )
			{
				// アプリ終了フラグを立てる
				if( !isExitApp() ){ setExitAppFlag( TRUE ); }
				break;
			}
		}

#if PROJECT_DEBUG
		// DEBUG
		AppLib::getDebugOperatPtr()->debugAppUpdate();
#endif

		if( isExitApp() ) {
			break;	// アプリ終了確認
		}

		// 各描画情報更新
		appSystemRenderUpdate();

		// Ｓキーが押されていたらゲーム画面のスクリーンショットを保存する
		if( DxLib::CheckHitKey( KEY_INPUT_S ) != 0 ) {
			SaveDrawScreen( 0, 0, 1280, 720, "ScreenShot.bmp" );
		}

		// 裏画面の内容を表画面に反映させる
		// ScreenFlip関数は垂直同期を取っているため、FPSが自動的にディスプレイのリフレッシュレート以下になる
		if( DxLib::ScreenFlip() != 0 ){}

		// 現在の時間を取得
		n_NowTime = DxLib::GetNowHiPerformanceCount();

		// フレームレート計測用のカウンタを１足す
		m_FrameCounter ++;
		// 前回フレームレートを更新してから１秒経過したら表示用フレームカウントを更新する
		if ( ( n_NowTime - m_BackDispFrameTime > (FRAME_UPDATE_SEC)) )
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

	// 正常終了
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
// Application毎フレーム処理
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////
bool	AppSystem::appProcessUpdate()
{
	// 正常終了
	return true;
}

bool	AppSystem::appTaskUpdate()
{
	// 正常終了
	return true;
}

//==============================================================================//
//	毎フレーム描画処理更新
//
void	AppSystem::appSystemRenderUpdate()
{
#if PROJECT_DEBUG
	int _drawHandle = -1;
	#if 0
	const int vramType = gpVramGetVVramType( AppLib::Resources::ResourcesFile_Name02 );
	_drawHandle = _getGraphicTexVramLoadHandle(
							AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
							AppLib::Resources::ResourcesFile_Name02 );
	#else
	_drawHandle = getVramFileParameterLoadHandle( AppLib::Resources::ResourcesFile_Name02, false );
	#endif
	if ( _drawHandle != -1 )
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA, 255 );
		DrawGraph( 0, 0, _drawHandle, TRUE );
	}
#endif

	// フレームレート
	dxCommon_DrawFramerate( getDispFrameCount() );
}

//==============================================================================//
//	DxLibInitのコール前に行っておく処理
//
bool	AppSystem::appSystemDxBeforeProcess()
{
	return true;
}

//==============================================================================//
//	DxLibInitのコール後に行う処理
//
bool	AppSystem::appSystemDxAfterProcess()
{
	// App基本情報の設定
	auto result = getAppContainerPtr()->setApplicationInfo();
	if( !result ){ return false; }

	// 各ライブラリの設定
	#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
		// Effekseer関係初期化処理
		// ※タイミングはDxLib_Initが終わってDxLib関係初期化後処理が終わったら
		App::EffekseerLib::libSystemInit();
	#endif
	
	DEBUG_PRINT("[Process] AppSystem::appSystemDxAfterProcess() CLEAR\n");

	return true;
}



//==============================================================================//
//	
//	
void	AppSystem::appSystemAdvanceSetup()
{
	m_LocalStep = eROUTE_ADVANCE_INIT;


	appSystemResourcesSetup( eROUTE_RESOURCES_ENTRY );

}
void	AppSystem::appSystemResourcesSetup( int processStep )
{
	// リソースの登録・読み込み
	{


#if PROJECT_DEBUG
		int result = -1;

		if ( processStep == eROUTE_RESOURCES_ENTRY )
		{
		/*
		result = _graphicVramTextureEntry(
					AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
					AppLib::Resources::ResourcesFile_Name01,
					AppLib::Resources::Archive::eARCHIVE_FILETYPE_RESOURCES,
					// AppLib::Resources::Parameter::EntryIndex::eRESFILE_NAME_GAME_FICTION_IMAGE,
					AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_APPSTART,
					AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SYSTEM );
		*/
		
		//※新仕様処理Ver
		result = vramTextureFileEntry( 
					AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,						/** VRAMタイプ */
					AppLib::Resources::ResourcesFile_Name01,									/** ファイルネーム */
					AppLib::Resources::Archive::eARCHIVE_FILETYPE_RESOURCES,					/** アーカイブファイルタイプ */
					AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SYSTEM,				/** ファイルの登録属性タイプ */
					AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_SCENE_TITLE				/**  */
					// AppLib::Resources::Parameter::EntryIndex::eRESFILE_NAME_GAME_TITLE_TEX_BG	/** ファイルの登録インデックス */
		);
		result = vramTextureFileEntry( 
					AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,						/** VRAMタイプ */
					AppLib::Resources::ResourcesFile_Name02,									/** ファイルネーム */
					AppLib::Resources::Archive::eARCHIVE_FILETYPE_RESOURCES,					/** アーカイブファイルタイプ */
					AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SYSTEM,				/** ファイルの登録属性タイプ */
					AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_SCENE_TITLE				/**  */
		);
		result = vramTextureFileEntry( 
					AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,						/** VRAMタイプ */
					AppLib::Resources::ResourcesFile_Name03,									/** ファイルネーム */
					AppLib::Resources::Archive::eARCHIVE_FILETYPE_RESOURCES,					/** アーカイブファイルタイプ */
					AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SYSTEM,				/** ファイルの登録属性タイプ */
					AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_SCENE_TITLE				/**  */
		);

		DEBUG_PRINT("[Process] AppSystem::VramTextureEntry CLEAR\n");
		}
		else if ( processStep == eROUTE_RESOURCES_LODING )
		{
		/*
		//※旧仕様処理Ver
		_graphicVramTexAttrUp(	AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
								AppLib::Resources::ProcessStatus::eUPMODE_NORMAL,
								AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_APPSTART );

		*/
		//※新仕様処理Ver
		vramTextureFileSingleUpload( AppLib::Resources::ResourcesFile_Name02,
									 AppLib::Resources::ProcessStatus::eUPMODE_NORMAL );

		}
#endif

	}
}


/**
 *	デバッグ
 *
 */

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