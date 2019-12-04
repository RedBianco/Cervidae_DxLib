#pragma once


//=================================================================================//
//  appProcess.h
//  Cervidae
//
//  Created by kashima akihiro on 2019/12/02.
//=================================================================================//


// �����֐��}�N��
typedef int(*appProcessExec)(void);

/**
 *	@class
 */



 /**
  *	@class	�V�[���Ǘ����N���X
  */
namespace App
{
	class ProcessManager
	{
		// TODO�F�b���Singleton���^�p�A���㑼�̕��@������
	private:
		// ���̃N���X�̃C���X�^���X
		static ProcessManager* s_pInstance;

	public:
		// �R���X�^���N�^
		ProcessManager()
		{}
		// Instance���폜���鎖�͖����̂ŃR�����g�A�E�g
	//  virtual ~AppProcManager();

	private:
		// �����֐��|�C���^
		appProcessExec	m_ProcessFunc;

	public:

		// 
		bool	setProcessFunc(appProcessExec  p_Function);

		// 
		int		appProcessUpdate(void);

	public:
		// �C���X�^���X�̍쐬�A�擾
		static ProcessManager* getInstance();
	};
}


/* End appProcess.h */

