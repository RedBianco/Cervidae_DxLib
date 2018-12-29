#pragma once

#include "dxLibCommon.h"

//=================================================================================//
//  dxLibDefine.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/28.
//=================================================================================//


#define DX_FILE_OPEN( fname )		FileRead_open( fname, false )
#define DX_FILE_CLOSE( h )			FileRead_close( h )
#define DX_FILE_IDOL( h )			FileRead_idle_chk( h )
#define DX_FILE_EOF( h )			FileRead_eof( h )
#define DX_FILE_READ				FileRead_read
#define DX_FILE_SIZE( fname )		FileRead_size( fname )
#define DX_FILE_GETC( h )			FileRead_getc( h )

//=================================================================================//
//	DXライブラリ関係専用定義
//=================================================================================//
namespace DxLibCommon
{
	const static bool					DEFAULT_SCREEN_MODE						= true;

	// データのVRAMメモリ配置設定
	const static int					SETTING_MEMORY_VRAM_MAIN		= 1;		//	メインVRAM
	const static int					SETTING_MEMORY_VRAM_SYSTEM		= 0;		//	システムメモリ
	
	const static int					FONTHANDLE_SMALL_SIZE			= 24;		// 小フォントのサイズ
	const static int					FONTHANDLE_MIDIUM_SIZE			= 32;		// 中フォントのサイズ
	const static int					FONTHANDLE_BIG_SIZE				= 80;		// 大フォントのサイズ

	namespace Disp
	{
		// 画面解像度
		const static unsigned int		DISPLAY_RESOLUTION_WIDTH		= 1024;
		const static unsigned int		DISPLAY_RESOLUTION_HEIGHT		= 768;
		const static unsigned int		DISPLAY_PLAY_COLORBIT			= 32;

		const static unsigned int		DISPLAY_FLAMERATE_POS_X			= (DISPLAY_RESOLUTION_WIDTH - 100);
		const static unsigned int		DISPLAY_FLAMERATE_POS_Y			= (DISPLAY_RESOLUTION_HEIGHT - 22);


	}
	namespace Process
	{
		typedef enum 
		{
			eEXEC_RETURN_CODE_KEEP			= -1,
			eEXEC_RETURN_CODE_RUN			= 0,
			eEXEC_RETURN_CODE_SUCCESS		= 1,
			eEXEC_RETURN_CODE_EXIT			= 99
		} ENUM_EXEC_RETURN_CODE;
		typedef enum
		{
			ePROCESS_LIB_RETURN_ERROR = -1,
			ePROCESS_LIB_RETURN_RESULT,
			ePROCESS_LIB_RETURN_RUNNING,
			ePROCESS_LIB_RETURN_SUCCESS
		} ENUM_LIB_RETURN_CODE;
	}

	namespace Message
	{
		const static char *	APP_WINDOW_MODE_PLAY_MES		= "ウインドウモードで起動しますか？";
		const static char *	APP_CHECK_WINDOW_MODE_PLAY		= "画面モード確認";
		const static char *	APP_LOW_SPEC_MODE_PLAY_MES		= "低処理負荷モードで起動しますか？";
		const static char *	APP_CHECK_LOW_SPEC_MODE_PLAY	= "処理負荷モード確認";
	}
}







/* End dxLibDefine.h */












