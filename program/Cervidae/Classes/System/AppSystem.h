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
	bool		m_LowSpecMode;			// �Ꮘ�����׃��[�h���ǂ����̃t���O
	bool		m_IsExitApp;			// �A�v�����I�����邩�ǂ����̃t���O


	// �O��t���[�����[�g�\���p�Ƀt���[���J�E���g�����Z�b�g��������
	LONGLONG	m_BackDispFrameTime;
	int			m_FrameCounter;			// �t���[�����[�g�\���p�̃t���[���J�E���^
	int			m_DispFrameCount;		// �t���[�����[�g�\���ŕ\������t���[�����[�g

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
	int			appSystemInitialize();				// Application�N�����̏���������
	void		appSystemTerminate();
	bool		appSystemUpdate();
	void		appSystemRenderUpdate();

};


/* End AppSystem.h */








