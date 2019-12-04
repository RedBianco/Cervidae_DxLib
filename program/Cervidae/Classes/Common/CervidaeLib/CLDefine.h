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
	#define	COMMENT				__noop			/** 無効 */
#else
	#define	DEBUG_PRINT			__noop			/** 無効 */
	#define	ERROR_PRINT(...)	printfDx( __VA_ARGS__ )
	#define	COMMENT				__noop			/** 無効 */
#endif

/** 各ミドルウェア制御マクロ */
#if defined( CERVIDAE_LIB )
	// TODO
	// 64bitReleaseでビルドすると以下エラーが出て調査中
	// エラー	C1047	オブジェクトまたはライブラリ ファイル 'x64\Release\tSingleton.obj' は、他のオブジェクトよりも古いコンパイラで作成されました。古いオブジェクトおよびライブラリをリビルドしてください
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
		// プレイ可能年齢 Parental Lock
		const static unsigned int		IAPP_RATING_LOCK_LEVEL	= 0;
		// 権利表記 Application Copyright
		const static char *				CAPP_SERVICE_COPYRIGHT	= "(C) 2019 TriangleWorks";
	}
}


/* End CLDefine.h */