#pragma once

/**
 *	@file		CLDefine.h
 *	@brief		CervidaeLibプログラム内で共通に使用する最小限の設定を置くヘッダ
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

namespace CervidaeLibDefine
{
	// Application Exe Name
	const static char *				nAPP_EXE_NAME			= "CervidaeLib.exe";
	// Application Version
	const static char *				nAPP_EXE_VERSION		= "20181129";	
	const static unsigned int		uAPP_EXE_VERSION		= 20181129;
	// Application Service ID
	const static char *				nAPP_SERVICE_NAME		= "PC0001-2018-00";
	// 視聴年齢制限 Parental Lock
	const static unsigned int		nAPP_RATING_AGE_LEVEL	= 0;
	// 著作権 Application Copyright
	const static char *				nAPP_SERVICE_COPYRIGHT	= "(C) 2018 TriangleWorks";


}



/* End CLDefine.h */