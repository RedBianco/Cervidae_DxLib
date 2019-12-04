

#include "appProcess.h"
#include "../../Libs/DxLib/dxLibDefine.h"
#include "../../Common/CervidaeLib/CLDefine.h"
#include <stdio.h>

//=================================================================================//
//  appProcess.cpp
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/04.
//=================================================================================//

App::ProcessManager* App::ProcessManager::s_pInstance;

// インスタンスが作成されていなければ作成
App::ProcessManager* App::ProcessManager::getInstance()
{
	if ( !s_pInstance )
	{
		s_pInstance = new App::ProcessManager();
		if( s_pInstance == nullptr ){
		}
	}
	return s_pInstance;
};

//=================================================================================//
// 
// 
//=================================================================================//
bool	App::ProcessManager::setProcessFunc( appProcessExec p_Function )
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
int		App::ProcessManager::appProcessUpdate()
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




