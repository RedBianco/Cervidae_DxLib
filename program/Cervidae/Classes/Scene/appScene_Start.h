#pragma once

//===================================================================================
//  appScene_Start.h
//  Cervidae
//
//  Created by kashima akihiro on 2019/11/29.
//===================================================================================



//==============================================================================//
//	�V�[���N���X
//==============================================================================//
namespace App
{
	class Scene_Start : public App::SceneBase
	{
		
	public:
		Scene_Start();
		~Scene_Start();

	private:
		enum {
			eSTART_SCENE_STATE_INIT = 0,


		} ENUM_START_SCENE_STATE;

		int				m_State;
		
		float			Counter;			// �ėp�J�E���^
		int				SelectPosition;		// �I�����Ă��鍀��

		STaskInfo		m_ssTaskInfo;
		STaskBaseInfo	m_ssTaskBaseInfo;

	public:
		void	setBaseInfo();

		bool	Task_Step( STaskInfo* TInfo, float StepTime ) override;
		void	Task_Render( STaskInfo* TInfo ) override;
		void	Task_Terminate( STaskInfo* TInfo ) override;
	};
}


/* End appScene_Start.h */




