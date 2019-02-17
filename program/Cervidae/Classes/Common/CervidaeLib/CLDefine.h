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
#else
	#define	DEBUG_PRINT			__noop
	#define	ERROR_PRINT(...)	printfDx( __VA_ARGS__ )
#endif

#if defined( CERVIDAE_LIB )
	#define MIDDLEWARE_EFFEKSEER_USE_ENABLE		(1)
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
		const static char *				CAPP_EXE_VERSION		= "20190109";
		const static unsigned int		IAPP_EXE_VERSION		= 20190109;
		// Application Service ID
		const static char *				CAPP_SERVICE_NAME		= "PC0001-2018-00";
		// �v���C�N��� Parental Lock
		const static unsigned int		IAPP_RATING_LOCK_LEVEL	= 0;
		// ���쌠 Application Copyright
		const static char *				CAPP_SERVICE_COPYRIGHT	= "(C) 2018 TriangleWorks";
	}
}


/* End CLDefine.h */