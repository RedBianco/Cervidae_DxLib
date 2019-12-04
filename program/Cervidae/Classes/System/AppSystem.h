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
	/** �}�C�N���Z�J���h */
	const unsigned int	FRAME_UPDATE_SEC = 1000000;
	/** �P�t���[���̍ő厞�� */
	const float			MAX_DELTA_TIME = (1.0f / 120.0f);
	/** ��x�ɏ�������ő�t���[���� */
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

	LONGLONG	m_PrevTime;			// ��O�̃t���[���̎���
	float		m_StepTime;			// ��Ԑ��ڏ����Ő��ڂ����鎞��
	int			m_StepNum;			// �P�t���[���ŏ�Ԑ��ڏ������s����

	// �^�X�N�V�X�e�����
	STaskSystemInfo	TaskSystemInfo;
	// �Q�[�����C���^�X�N�̃^�X�N���\���̂̃A�h���X���i�[����|�C���^�ϐ�
	STaskInfo*		GameMainTaskInfo;

	// �`��Ǘ����


	// �G�t�F�N�g�Ǘ����
#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
#endif

	// �E�B���h�E�I�u�W�F�N�g���
//	std::vector< UI::WindowObjectData*>	m_appWinObj;

private:

	LONGLONG	m_BackDispFrameTime;	// �O��t���[�����[�g�\���p�Ƀt���[���J�E���g�����Z�b�g��������
	int			m_FrameCounter;			// �t���[�����[�g�\���p�̃t���[���J�E���^
	int			m_DispFrameCount;		// �t���[�����[�g�\���ŕ\������t���[�����[�g
	bool		m_IsExitApp;			// �A�v�����I�����邩�ǂ����̃t���O
	bool		m_LowSpecMode;			// �Ꮘ�����׃��[�h���ǂ����̃t���O
	int			m_LocalStep;			// 

public:
	static AppSystem * createInstance();

	bool		appSystemMain();

	void		setLowSpecMode( const bool setValue ){ m_LowSpecMode = setValue; }
	bool		getLowSpecMode() const { return m_LowSpecMode; }

	void		setExitAppFlag( const bool setValue ) { m_IsExitApp = setValue; }
	bool		isExitApp() const { return m_IsExitApp; }

	// FPS�l�擾
	int			getDispFrameCount() const { return m_DispFrameCount; }

private:

	void		appSystemClean();
	void		appSystemTerminate();

	int			appSystemInitialize();				// Application�N�����̏���������
	bool		appSystemStartSetup();				// ��������������t���[
	void		appSystemShutdown();
	bool		appSystemUpdate();
	bool		appProcessUpdate();
	bool		appTaskUpdate();
	void		appSystemRenderUpdate();			// �`�揈���X�V

	bool		appSystemDxBeforeProcess();			// DxLib_Init()�̃R�[���O�Ɏ��s���鏈��
	bool		appSystemDxAfterProcess();			// DxLib_Init()�̃R�[����Ɏ��s���鏈��

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

	// ��Ԑ��ڏ������s��
	//     �߂�l : ����������ɏI���������ǂ���(true:����ɏI������  false:�G���[����������)
	bool		appSystemStep(
		float StepTime	// ���ڂ����鎞��( �P�� : �b )
	);

	// �t�F�[�h�����̕`����s��
	void		appSystemFadeRender( void );

};


/* End appSystem.h */








