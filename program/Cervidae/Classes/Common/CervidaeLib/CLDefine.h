#pragma once

/**
 *	@file	CLDefine.h
 *	@brief	CervidaeLibプログラム内で共通に使われてほしい最小限の設定を置くヘッダ
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

namespace CervidaeDxLib
{
	// 画面サイズ定義
	const static float		SCREENSIZE_WIDTH	= 640.0f;
	const static float		SCREENSIZE_HEIGHT	= 480.0f;

}
























