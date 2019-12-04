#pragma once

/**
 *	@file		CLDefine.h
 *	@brief		CervidaeLib�v���O�������ŋ��ʂɎg�p����ŏ����̐ݒ��u���w�b�_
 *	@date		2018/10/16.
 *	@author		kashima akihiro
 *	@note
 *		
 *
 */


#define CERVIDAE_LIB

#if defined( _DEBUG )
	#define DEBUG_MENU
	#define SYSTEM_DEBUG
#endif

#define PROJECT_DEBUG   ( defined( SYSTEM_DEBUG ) )

#if PROJECT_DEBUG
	#define	DEBUG_PRINT			printfDx
	#define	ERROR_PRINT(...)	printfDx( __VA_ARGS__ )
	#define	COMMENT				__noop			/** ���� */
#else
	#define	DEBUG_PRINT			__noop			/** ���� */
	#define	ERROR_PRINT(...)	printfDx( __VA_ARGS__ )
	#define	COMMENT				__noop			/** ���� */
#endif

/** �e�~�h���E�F�A����}�N�� */
#if defined( CERVIDAE_LIB )
	// TODO
	// 64bitRelease�Ńr���h����ƈȉ��G���[���o�Ē�����
	// �G���[	C1047	�I�u�W�F�N�g�܂��̓��C�u���� �t�@�C�� 'x64\Release\tSingleton.obj' �́A���̃I�u�W�F�N�g�����Â��R���p�C���ō쐬����܂����B�Â��I�u�W�F�N�g����у��C�u���������r���h���Ă�������
	#define __MIDDLEWARE_EFFEKSEER_USE_ENABLE		(1)


	#define __APP_PROCESS_TASK_MANAGE				(0)
	#define __APP_PROCESS_FUNC_POINTER_ENABLE		(0)

#endif

//=================================================================================//
//	
//=================================================================================//
namespace CervidaeLib
{
	namespace AppInfo
	{
		// Application Exe Name
		const static char *				CAPP_EXE_NAME			= "CervidaeLib.exe";
		// Application Version
		const static char *				CAPP_EXE_VERSION		= "20191106";
		const static unsigned int		IAPP_EXE_VERSION		= 20191106;
		// Application Service ID
		const static char *				CAPP_SERVICE_NAME		= "PC0001-2019-00";
		// �v���C�\�N�� Parental Lock
		const static unsigned int		IAPP_RATING_LOCK_LEVEL	= 0;
		// �����\�L Application Copyright
		const static char *				CAPP_SERVICE_COPYRIGHT	= "(C) 2019 TriangleWorks";
	}
}


/* End CLDefine.h */