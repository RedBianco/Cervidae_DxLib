#pragma once


//=================================================================================//
//  dxLibDefine.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/28.
//=================================================================================//


//=================================================================================//
//	DX���C�u�����֌W��p��`
//=================================================================================//
namespace DxLibCommonDefine
{
	enum ENUM_EXEC_RETURN_CODE
	{
		eEXEC_RETURN_CODE_KEEP		= -1,
		eEXEC_RETURN_CODE_RUN		= 0,
		eEXEC_RETURN_CODE_SUCCESS	= 1,
		eEXEC_RETURN_CODE_EXIT		= 99
	};


	const static bool			DEFAULT_SCREEN_MODE = true;

	// ��ʉ𑜓x
	const static unsigned int	DISPLAY_RESOLUTION_WIDTH	= 1024;
	const static unsigned int	DISPLAY_RESOLUTION_HEIGHT	= 768;
	const static unsigned int	DISPLAY_PLAY_COLORBIT		= 32;



}







/* End dxLibDefine.h */












