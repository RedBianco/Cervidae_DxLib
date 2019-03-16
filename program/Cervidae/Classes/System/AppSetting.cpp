
#include "DxLib.h"
#include "../Common/CervidaeLib/CLDefine.h"
#include "../Common/CommonList.h"
#include "../Libs/DxLib/dxLibDefine.h"
#include "AppSetting.h"


//======================================================================//
//  AppSetting.cpp
//  Created by on 2018/11/29.
//======================================================================//



bool	AppParameter::settingBaseInfo()
{
	if( !AppParameter::isCreate() ){
		return false;
	}
	// アプリケーション基本情報設定
	this->m_ExeName = CervidaeLib::AppInfo::CAPP_EXE_NAME;
	this->m_ExeVersion = CervidaeLib::AppInfo::CAPP_EXE_VERSION;
	this->m_ServiceNeme = CervidaeLib::AppInfo::CAPP_SERVICE_NAME;
	this->m_RatingAgeLevel = CervidaeLib::AppInfo::IAPP_RATING_LOCK_LEVEL;
	this->m_ServiceCopyright = CervidaeLib::AppInfo::CAPP_SERVICE_COPYRIGHT;

	DEBUG_PRINT("[Process] AppParameter::settingBaseInfo() CLEAR\n");

	return true;
}















