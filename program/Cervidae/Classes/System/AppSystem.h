#pragma once

//=================================================================================//
//  AppSystem.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/06.
//=================================================================================//

#include "../Libs/DxLib/Input/dxLibKeyPadUtility.h"

class AppSystem : 
			public AppKeyPadController
{
public:
	AppSystem();
	~AppSystem();

public:
	bool		m_LowSpecMode;			// 低処理負荷モードかどうかのフラグ
	bool		m_IsExitApp;			// アプリを終了するかどうかのフラグ


	// 前回フレームレート表示用にフレームカウントをリセットした時間
	LONGLONG	m_BackDispFrameTime;
	int			m_FrameCounter;			// フレームレート表示用のフレームカウンタ
	int			m_DispFrameCount;		// フレームレート表示で表示するフレームレート

public:
	bool		appSystemMain();

	void		setLowSpecMode( const bool setValue ){ m_LowSpecMode = setValue; }
	bool		getLowSpecMode() const { return m_LowSpecMode; }

	void		setExitAppFlag( const bool setValue ) { m_IsExitApp = setValue; }
	bool		isExitApp() const { return m_IsExitApp; }

	int			getDispFrameCount() const { return m_DispFrameCount; }

private:
	void		appSystemClean();
	
	bool		appSystemStartSetup();
	int			appSystemInitialize();				// Application起動時の初期化処理
	void		appSystemTerminate();
	bool		appSystemUpdate();
	void		appSystemRenderUpdate();

};


/* End AppSystem.h */








