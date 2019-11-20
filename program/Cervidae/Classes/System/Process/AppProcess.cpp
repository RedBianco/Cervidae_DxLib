

#include "AppProcess.h"
#include "../../Libs/DxLib/dxLibDefine.h"
#include "../../Common/CervidaeLib/CLDefine.h"
#include <stdio.h>

//=================================================================================//
//  AppProcess.cpp
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/04.
//=================================================================================//

AppProcManager* AppProcManager::s_pInstance;

// �C���X�^���X���쐬����Ă��Ȃ���΍쐬
AppProcManager* AppProcManager::getInstance()
{
	if ( !s_pInstance )
	{
		s_pInstance = new AppProcManager();
		if( s_pInstance == NULL ){}
	}
	return s_pInstance;
};

//=================================================================================//
// 
// 
//=================================================================================//
bool	AppProcManager::setProcessFunc( appProcessExec p_Function )
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
int		AppProcManager::appProcessUpdate()
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




