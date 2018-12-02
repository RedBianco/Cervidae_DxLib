#pragma once


#include "AppProcess.h"




//==============================================================================//
//	�����֐��}�N��
//==============================================================================//
typedef int( *systemProcExec )( void );


//==============================================================================//
//	
//==============================================================================//
class AppProcManage
{
// TODO�F�b���Singleton���^�p�A���㑼�̕��@������
private:
	// ���̃N���X�̃C���X�^���X
	static AppProcManage *	s_pInstance;

public:
	// �R���X�^���N�^
	AppProcManage()
	{}
	// Instance���폜���鎖�͖����̂ŃR�����g�A�E�g
//  virtual ~AppProcManage();

public:
	// �����֐��|�C���^
	systemProcExec	m_ProcessFunc;

public:
	bool	setProcessFunc( systemProcExec  pSetFunc );

	int		systemProcessUpdate( void );

public:
	// �C���X�^���X�̍쐬�A�擾
	static AppProcManage *    getInstance();
};












