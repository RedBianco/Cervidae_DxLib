#pragma once


// �����֐��}�N��
typedef int( *appProcessExec )( void );

/**
 *	@class	�V�[���Ǘ����N���X
 */
class AppProcManager
{
// TODO�F�b���Singleton���^�p�A���㑼�̕��@������
private:
	// ���̃N���X�̃C���X�^���X
	static AppProcManager *	s_pInstance;

public:
	// �R���X�^���N�^
	AppProcManager()
	{}
	// Instance���폜���鎖�͖����̂ŃR�����g�A�E�g
//  virtual ~AppProcManager();

private:
	// �����֐��|�C���^
	appProcessExec	m_ProcessFunc;

public:

	// 
	bool	setProcessFunc( appProcessExec  p_Function );

	// 
	int		appProcessUpdate( void );

public:
	// �C���X�^���X�̍쐬�A�擾
	static AppProcManager *    getInstance();
};














