#pragma once

/**
 *	@file	CLDefine.h
 *	@brief	CervidaeLibプログラム内で共通に使用する最小限の設定を置くヘッダ
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
	const static char *			nAPP_TITLE_NAME			= "CervidaeLib";		// アプリケーションタイトルネーム
	const static char *			nAPP_TITLE_VERSION		= "20181025";			// アプリケーションのバージョン
	// Service ID
	const static char *			nAPP_SERVICE_ID			= "PC0001-2018-00";
	// 視聴年齢制限年齢 parental lock
	const static unsigned int	nAPP_RATING_AGE_LEVEL	= 0;




}






/* End CLDefine.h */