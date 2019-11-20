

#include "AppProcess.h"
#include "../../Libs/DxLib/dxLibDefine.h"
#include "../../Common/CervidaeLib/CLDefine.h"
#include <stdio.h>

//=================================================================================//
//  AppProcess.cpp
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/04.
//=================================================================================//

AppProcManager* AppProcManager::s_pInstance;

// インスタンスが作成されていなければ作成
AppProcManager* AppProcManager::getInstance()
{
	if ( !s_pInstance )
	{
		s_pInstance = new AppProcManager();
		if( s_pInstance == NULL ){}
	}
	return s_pInstance;
};

//=================================================================================//
// 
// 
//=================================================================================//
bool	AppProcManager::setProcessFunc( appProcessExec p_Function )
{
	if( s_pInstance )
	{
		// シーン関数ポインタセット
		m_ProcessFunc = p_Function;

		// 設定確保
		return	true;
	}
	// 設定失敗
	return	false;
}

//=================================================================================//
// 
// 
//=================================================================================//
int		AppProcManager::appProcessUpdate()
{
	int	__ProcessCode = DxLibCommon::Process::eEXEC_RETURN_CODE_KEEP;
	// 関数処理
	__ProcessCode = ( this->m_ProcessFunc )();
#if PROJECT_DEBUG
	if( __ProcessCode == DxLibCommon::Process::eEXEC_RETURN_CODE_EXIT )
	{
	}
#endif
	// eEXEC_RETURN_CODE_EXIT を返すとアプリケーション終了
	return __ProcessCode;
}




