

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

AppProcManage* AppProcManage::s_pInstance;

// インスタンスが作成されていなければ作成
AppProcManage* AppProcManage::getInstance()
{
	if ( !s_pInstance )
	{
		s_pInstance = new AppProcManage();
		if( s_pInstance == NULL ){}
	}
	return s_pInstance;
};

bool	AppProcManage::setProcessFunc( systemProcExec pSetFunc )
{
	if( s_pInstance )
	{
		// シーン関数ポインタセット
		m_ProcessFunc = pSetFunc;

		// 設定確保
		return	true;
	}
	// 設定失敗
	return	false;
}

int		AppProcManage::systemProcessUpdate()
{
	int	nProcessCode = DxLibCommon::Process::eEXEC_RETURN_CODE_KEEP;
	// 関数処理
	nProcessCode = (m_ProcessFunc)();
#if defined( SYSTEM_DEBUG )
	if( nProcessCode == DxLibCommon::Process::eEXEC_RETURN_CODE_EXIT )
	{
	}
#endif
	// eEXEC_RETURN_CODE_EXIT を返すとアプリケーション終了
	return nProcessCode;
}




