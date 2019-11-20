

#include "DxLib.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "dxLibDebugConfig.h"
#include "dxLibDebugLog.h"
#include "../dxLibCommon.h"
#include "../dxLibDefine.h"



//=================================================================================//
//  dxLibDebugLog.cpp
//  Cervidae
//
//  Created by kashima akihiro on 2019/01/05.
//=================================================================================//

/**
 *	appDebugPrint( eDEBUG_LOG_COMMENT, "" );
 *	appDebugPrint( eDEBUG_LOG_ALERT, "" );
 *	appDebugPrint( eDEBUG_LOG_ERROR, "" );
 */
static int	debugLogPrintX = 0;
static int	debugLogPrintY = 0;


//==============================================================================//
// 
// 
int		appDebugPrint( DxLib::DebugConfig::ENUM_DEBUG_LOG_TYPE logType, const char * logStr )
{
#if PROJECT_DEBUG

	COMMENT("[COMMENT] appDebugPrint Run\n");

	auto printColor = 0;
	switch ( logType )
	{
	/** */
	case DxLib::DebugConfig::eDEBUG_LOG_COMMENT:
		printColor = DxLib::GetColor( 0, 0, 0 );
		break;
	/** */
	case DxLib::DebugConfig::eDEBUG_LOG_ALERT:
		printColor = DxLib::GetColor( 255, 255, 0 );
		break;
	/** */
	case DxLib::DebugConfig::eDEBUG_LOG_ERROR:
		printColor = DxLib::GetColor( 255, 0, 0 );
		break;
	}
	auto result = DxLib::DrawString( debugLogPrintX, debugLogPrintY, logStr, printColor, 0 );
	{
		debugLogPrintX = 0;
		debugLogPrintY = debugLogPrintY + DxLibCommon::DEFAULT_PRINT_FONTSIZE;
	}

#endif
	return -1;
}














