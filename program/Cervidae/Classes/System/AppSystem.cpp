
#include "DxLib.h"
#include "../Common/CommonList.h"
#include "../Libs/DxLib/Initialize/dxLibInit.h"
#include "../Libs/DxLib/Initialize/dxLibSetup.h"
#include "AppSystem.h"
#include "../Libs/DxLib/dxLibDefine.h"

//======================================================================//
//  AppSystem.cpp
//  Created by on 2018/11/06.
//======================================================================//


AppSystem::AppSystem() :
		m_LowSpecMode( false ),
		m_IsExitApp( false ),
		// フレームレート計測用の変数の初期化
		m_BackDispFrameTime( DxLib::GetNowHiPerformanceCount() ),
		m_FrameCounter( 0 ),
		m_DispFrameCount( 0 )
{
}
AppSystem::~AppSystem()
{}

void		AppSystem::appSystemClean()
{

}

// ( true : 正常に処理を完了した   false : エラーが発生した )
bool		AppSystem::appSystemMain()
{
	
	if( !appSystemInitialize() )
	{
		return false;
	}


	if( !appSystemUpdate() )
	{
		return false;
	}


	appSystemTerminate();

	return true;
}

// Application起動時の初期化処理
int	AppSystem::appSystemInitialize()
{
	auto isSuccess = false;

	isSuccess = dxLib_InitBeforeSetup();
	if( isSuccess ){
	}
	isSuccess = dxInit_CheckWindowModePlay();
	if( isSuccess ){
	}
	isSuccess = dxInit_CheckLowSpecModePlay();
	if( isSuccess ) {
		setLowSpecMode( TRUE );
	}

	if( DxLib_Init() == -1 ) 
	{
		return false;
	}

	isSuccess = dxLib_InitAfterSetup();
	if( isSuccess ){
	}

	// 初期化成功
	return true;
}
// Application終了処理
void		AppSystem::appSystemTerminate()
{




	// ＤＸライブラリの終了処理
	DxLib::DxLib_End();
}

// Application毎フレーム処理
bool		AppSystem::appSystemUpdate()
{
	LONGLONG	n_NowTime;

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

#ifdef PROJECT_DEBUG
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
	}


	return true;
}

void		AppSystem::appSystemRenderUpdate()
{

	// フレームレート
	dxCommon_FramerateDisp( getDispFrameCount() );
}


