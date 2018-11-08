#pragma once

/**
 *	@file	CLDefine.h
 *	@brief	CervidaeLib�v���O�������ŋ��ʂɎg�p����ŏ����̐ݒ��u���w�b�_
 *	@date	2018/10/16.
 *	@author	kashima akihiro
 *	@note
 *		
 *
 */


#define CERVIDAE_LIB

#if defined( _DEBUG )
	#define DEBUG_MENU
	#define SYSTEM_DEBUG
#endif


//=================================================================================//
//	
//=================================================================================//

namespace CervidaeLibDefine
{
	const static char *			nAPP_TITLE_NAME			= "CervidaeLib";		// �A�v���P�[�V�����^�C�g���l�[��
	const static char *			nAPP_TITLE_VERSION		= "20181025";			// �A�v���P�[�V�����̃o�[�W����
	// Service ID
	const static char *			nAPP_SERVICE_ID			= "PC0001-2018-00";
	// �����N����N�� parental lock
	const static unsigned int	nAPP_RATING_AGE_LEVEL	= 0;




}






/* End CLDefine.h */