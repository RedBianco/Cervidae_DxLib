#pragma once

//=================================================================================//
//  AppSystem.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/06.
//=================================================================================//

#include "../Libs/DxLib/Input/dxLibKeyPadUtility.h"
#include "../Libs/Effekseer/appEffekseer.h"
#include "../Libs/DxLib/Resources/appResourcesConfig.h"
#include "../Libs/DxLib/Resources/appResources.h"

/**
 *	@class	
 *
 */
class AppSystem : 
			public DxLib::AppKeyPadController,
			public DxLib::AppVramFileManager
#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
			, public Lib::EffekseerController
#endif
{
private:

	const unsigned int   FRAME_UPDATE_SEC = 1000000;  // �}�C�N���Z�J���h

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

	// ��O�̃t���[���̎���
	LONGLONG	m_PrevTime;
	// ��Ԑ��ڏ����Ő��ڂ����鎞��
	float		m_StepTime;
	// �P�t���[���ŏ�Ԑ��ڏ������s����
	int			m_StepNum;

	// �^�X�N�V�X�e�����
//	STaskSystemInfo		m_TaskSystemInfo;
	// �Q�[�����C���^�X�N�̃^�X�N���\���̂̃A�h���X���i�[����|�C���^�ϐ�
//	STaskInfo*			m_appTaskInfo;

	// �`��Ǘ����


	// Windows���
//	UI::WindowObjectData*	m_appBaseWin;

private:

	LONGLONG	m_BackDispFrameTime;	// �O��t���[�����[�g�\���p�Ƀt���[���J�E���g�����Z�b�g��������
	int			m_FrameCounter;			// �t���[�����[�g�\���p�̃t���[���J�E���^
	int			m_DispFrameCount;		// �t���[�����[�g�\���ŕ\������t���[�����[�g
	bool		m_IsExitApp;			// �A�v�����I�����邩�ǂ����̃t���O
	bool		m_LowSpecMode;			// �Ꮘ�����׃��[�h���ǂ����̃t���O
	int			m_LocalStep;			// 

public:
	AppSystem * createInstance();

	bool		appSystemMain();

	void		setLowSpecMode( const bool setValue ){ m_LowSpecMode = setValue; }
	bool		getLowSpecMode() const { return m_LowSpecMode; }

	void		setExitAppFlag( const bool setValue ) { m_IsExitApp = setValue; }
	bool		isExitApp() const { return m_IsExitApp; }

	// FPS�l�擾
	int			getDispFrameCount() const { return m_DispFrameCount; }

private:

	void		appSystemClean();

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
};


/* End AppSystem.h */








