#pragma once

//===================================================================================
//  InitializeScene.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/15.
//===================================================================================





/*
	基本エントリーシーンクラス
*/
class InitializeScene
{

	enum SCENE_BRANCH
	{
		SCENE_READY		= 0,
	};


public:
	InitializeScene();
	~InitializeScene();



public:
	void		initScene();
	void		sceneUpdate( float msec );



};













