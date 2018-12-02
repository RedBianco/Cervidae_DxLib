#pragma once

//===================================================================================
//  StartScene.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/27.
//===================================================================================



//==============================================================================//
//	シーンクラス
//==============================================================================//
class StartScene
{

public:
	StartScene();
	~StartScene();

private:

	int		m_ScenePhase;

public:
	void		initStartScene();
	void		setupStartScene();

	void		sceneUpdate();

	void		setScenePhase( const int setPhase ) { m_ScenePhase = setPhase; }
	int		getScenePhase() const { return m_ScenePhase; }
};
















