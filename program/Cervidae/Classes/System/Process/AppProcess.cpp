

#include "appProcess.h"
#include "../../Libs/DxLib/dxLibDefine.h"
#include "../../Common/CervidaeLib/CLDefine.h"
#include <stdio.h>

//=================================================================================//
//  appProcess.cpp
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/04.
//=================================================================================//

App::ProcessManager* App::ProcessManager::s_pInstance;

// �C���X�^���X���쐬����Ă��Ȃ���΍쐬
App::ProcessManager* App::ProcessManager::getInstance()
{
	if ( !s_pInstance )
	{
		s_pInstance = new App::ProcessManager();
		if( s_pInstance == nullptr ){
		}
	}
	return s_pInstance;
};

//=================================================================================//
// 
// 
//=================================================================================//
bool	App::ProcessManager::setProcessFunc( appProcessExec p_Function )
{
	if( s_pInstance )
	{
		// �V�[���֐��|�C���^�Z�b�g
		m_ProcessFunc = p_Function;

		// �ݒ�m��
		return	true;
	}
	// �ݒ莸�s
	return	false;
}

//=================================================================================//
// 
// 
//=================================================================================//
int		App::ProcessManager::appProcessUpdate()
{
	int	__ProcessCode = DxLibCommon::Process::eEXEC_RETURN_CODE_KEEP;
	// �֐�����
	__ProcessCode = ( this->m_ProcessFunc )();
#if PROJECT_DEBUG
	if( __ProcessCode == DxLibCommon::Process::eEXEC_RETURN_CODE_EXIT )
	{
	}
#endif
	// eEXEC_RETURN_CODE_EXIT ��Ԃ��ƃA�v���P�[�V�����I��
	return __ProcessCode;
}




