#pragma once

//===================================================================================
//  StartScene.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/27.
//===================================================================================

#include "../Libs/DxLib/Input/dxLibKeyPadUtility.h"

//==============================================================================//
//	シーンクラス
//==============================================================================//
class StartScene :
		public DxLib::AppKeyPadController
{

public:
	StartScene();
	~StartScene();

private:

	int			m_ScenePhase;
	int			m_ProcWait;

	bool		m_isRenderStart;		// 描画フラグ
	bool		m_SystemEnable;
	int			m_SystemStop;

	int			m_AlertDrawCount;
	int			m_AlertDrawAlpha;

public:
	void		initStartScene();
	void		setupStartScene();

	bool		sceneUpdate();

	void		setScenePhase( const int setPhase ) { m_ScenePhase = setPhase; }
	int			getScenePhase() const { return m_ScenePhase; }

	void		setRenderFlag( const bool setFlag ) { m_isRenderStart = setFlag; }
	bool		getRenderFlag() const { return m_isRenderStart;  }

	void		setSystemEnable( const bool setFlag ) { m_SystemEnable = setFlag; }
	bool		getSystemEnable() const { return m_SystemEnable;  }
};








