

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

AppProcManage* AppProcManage::s_pInstance;

// �C���X�^���X���쐬����Ă��Ȃ���΍쐬
AppProcManage* AppProcManage::getInstance()
{
	if ( !s_pInstance )
	{
		s_pInstance = new AppProcManage();
		if( s_pInstance == NULL ){}
	}
	return s_pInstance;
};

bool	AppProcManage::setProcessFunc( systemProcExec pSetFunc )
{
	if( s_pInstance )
	{
		// �V�[���֐��|�C���^�Z�b�g
		m_ProcessFunc = pSetFunc;

		// �ݒ�m��
		return	true;
	}
	// �ݒ莸�s
	return	false;
}

int		AppProcManage::systemProcessUpdate()
{
	int	nProcessCode = DxLibCommon::Process::eEXEC_RETURN_CODE_KEEP;
	// �֐�����
	nProcessCode = (m_ProcessFunc)();
#if defined( SYSTEM_DEBUG )
	if( nProcessCode == DxLibCommon::Process::eEXEC_RETURN_CODE_EXIT )
	{
	}
#endif
	// eEXEC_RETURN_CODE_EXIT ��Ԃ��ƃA�v���P�[�V�����I��
	return nProcessCode;
}




