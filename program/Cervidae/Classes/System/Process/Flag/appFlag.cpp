
#include "DxLib.h"
#include "../../../Common/CervidaeLib/Template/tSingleton.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../../../Common/appCommonParam.h"
#include "../../../Common/appErrorCode.h"
#include "appFlag.h"


//=================================================================================//
//  appFlag.cpp
//  Created by kashima akihiro on 2019/12/11.
//=================================================================================//


//=================================================================================//
//  
//  
//=================================================================================//
void	App::FlagManager::dataSystemInit()
{
	DEBUG_PRINT("[Lib] App::FlagManager dataSystemInit() CLEAR\n");
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::createFlag( const char* flagName, const int flagValue, const ENUM_CREATE_FLAG_TYPE nType, const ENUM_FLAG_CATEGORY_TAG flagCategory )
{
	int mId = 0, mUseNum = 0;

	mUseNum = libFlag_isUseFlagNum( nType );
#if PROJECT_DEBUG
	const int flagMax = ((nType == eFLAG_TYPE_APPDATA) ? CommonList::GameSystem::APP_FLAGDATA_ENTRY_MAX : CommonList::GameSystem::SYSTEM_FLAGDATA_ENTRY_MAX);
	if( mUseNum >= flagMax ) {
		ERROR_PRINT("__ERROR__ : CreateFlag UseFlagNumOver.\n");
		return App::ErrorCode::eRETURN_CODE_FLAG_LISTOVER;
	}
#endif

	mId = libFlag_FlagDataIdGet( flagName, nType );
#if PROJECT_DEBUG
	if( ( nType == eFLAG_TYPE_APPDATA && mUseNum >= CommonList::GameSystem::APP_FLAGDATA_ENTRY_MAX) || ( nType == eFLAG_TYPE_SYSTEM && mUseNum >= CommonList::GameSystem::SYSTEM_FLAGDATA_ENTRY_MAX)){
		ERROR_PRINT("__ERROR__ : CreateFlag ListNotFreeNo !!!.\n");
		return App::ErrorCode::eRETURN_CODE_FLAG_DATAIDERROR;
	}
#endif

	// 各詳細データ設定
	std::unique_ptr<App::FlagObjectData>  flagObject = std::make_unique<App::FlagObjectData>();

	flagObject->m_FlagType = nType;
	flagObject->m_FlagName = flagName;
	flagObject->m_Num = flagValue;
	flagObject->m_Setup = 0;
	flagObject->m_FlagCategory = flagCategory;

	DEBUG_PRINT("[Lib] App::FlagManager CreateFlag( Name:\"%s\", Num:%d ).\n", flagObject->m_FlagName.c_str(), flagValue);
	m_FlagDataList.push_back( *flagObject);

	// フラグ数加算
	if( nType == eFLAG_TYPE_APPDATA )
	{
		this->m_AppFlagEntry ++;
		DEBUG_PRINT("[Lib] App::FlagManager CreateFlag m_AppFlagEntry [%d].\n", this->m_AppFlagEntry );
	}else{
		this->m_SystemFlagEntry ++;
		DEBUG_PRINT("[Lib] App::FlagManager CreateFlag m_SystemFlagEntry [%d].\n", this->m_SystemFlagEntry );
	}
	DEBUG_PRINT("[Lib] App::FlagManager FlagDataNum( Size:%d ).\n", m_FlagDataList.size());
	DEBUG_PRINT("[Lib] App::FlagManager FlagDataNum( Capacity:%d ).\n", m_FlagDataList.capacity());
	
	return ( mId );
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_isUseFlagNum( const ENUM_CREATE_FLAG_TYPE flagType )
{
	if( flagType == eFLAG_TYPE_APPDATA )
	{
		return this->m_AppFlagEntry;	// フラグ数
	}else{
		return this->m_SystemFlagEntry;	// SPフラグ数
	}
	return( -1);
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_FlagDataIdGet( const char* flagName, const ENUM_CREATE_FLAG_TYPE flagType )
{
	if ( m_FlagDataList.empty() ) { return ( -1); }

	int index = 0;
	std::vector< App::FlagObjectData>::iterator itr = m_FlagDataList.begin();
	for ( ; itr != m_FlagDataList.end(); ++ itr, ++ index )
	{
		if( strcmp( itr->m_FlagName.c_str(), flagName ) == 0 )
		{
			return index;
		}
	}
	// 名前が見つからず
	return ( -1);
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_FlagNumSet( const char* flagName, const int flagValue, const ENUM_CREATE_FLAG_TYPE flagType )
{
	int i = libFlag_FlagDataIdGet( flagName, flagType );
	if( i < 0 || i >= libFlag_isUseFlagNum( flagType ) ){
		ERROR_PRINT("__ERROR__ : libFlag_FlagNumSet IndexError[%d]\n", i );
		return ( -1 );
	}
	libFlag_FlagNumSet( i, flagValue, flagType );

	return ( 0);
}
int		App::FlagManager::libFlag_FlagNumSet( const int  listIndex, const int flagValue, const ENUM_CREATE_FLAG_TYPE flagType )
{
	if (m_FlagDataList.empty() == true) { return (-1); }

	if( listIndex < 0 || listIndex >= libFlag_isUseFlagNum( flagType ) ){
		ERROR_PRINT("__ERROR__ : libFlag_FlagNumSet IDError[%d]\n", listIndex);
		return ( -1 );
	}

	// 値代入
	m_FlagDataList.at(listIndex).m_Num = flagValue;

	return ( 0 );
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_FlagNumChange( const char * flagName, const int flagValue, const ENUM_CREATE_FLAG_TYPE flagType )
{
	int i = libFlag_FlagDataIdGet( flagName, flagType );
	if( i < 0 || i >= libFlag_isUseFlagNum( flagType) ){
		ERROR_PRINT("__ERROR__ : libFlag_FlagNumChange IndexError[%d]\n", i);
		return ( -1 );
	}
	libFlag_FlagNumChange( i, flagValue, flagType );
	
	return ( 0 );
}
int		App::FlagManager::libFlag_FlagNumChange( const int  listIndex, const int flagValue, const ENUM_CREATE_FLAG_TYPE flagType )
{
	if (m_FlagDataList.empty() == true) { return (-1); }

	if( listIndex < 0 || listIndex >= libFlag_isUseFlagNum( flagType ) ){
		ERROR_PRINT("__ERROR__ : libFlag_FlagNumChange IDError[%d]\n", listIndex);
		return ( -1 );
	}
	m_FlagDataList.at(listIndex).m_Num += flagValue;
	
	return ( 0 );
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_isFlagNumber( const char* flagName, const ENUM_CREATE_FLAG_TYPE flagType )
{
	int i = libFlag_FlagDataIdGet( flagName, flagType );
	if( i < 0 || i >= libFlag_isUseFlagNum( flagType ) ){
		ERROR_PRINT("__ERROR__ : libFlag_isFlagNumber IndexError[%d]\n", i);
		return -20000;
	}
	return libFlag_isFlagNumber( i, flagType );
}
int		App::FlagManager::libFlag_isFlagNumber( const int  listIndex, const ENUM_CREATE_FLAG_TYPE flagType )
{
	if (m_FlagDataList.empty() == true) { return (-1); }

	if( listIndex < 0 || listIndex >= libFlag_isUseFlagNum( flagType ) ){
		ERROR_PRINT("__ERROR__ : libFlag_isFlagNumber IDError[%d]\n", listIndex);
		return -20000;
	}
	
	return m_FlagDataList.at( listIndex).m_Num;
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_FlagMinimum( const char* flagName, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType )
{
	int i = libFlag_FlagDataIdGet(flagName, flagType);
	if( i < 0 || i >= libFlag_isUseFlagNum(flagType) ){
		ERROR_PRINT("__ERROR__ : libFlag_FlagMinimum ID[%d]\n", i );
		return ( -1 );
	}
	return libFlag_FlagMinimum(i, fNum, flagType);
}
int		App::FlagManager::libFlag_FlagMinimum( const int index, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType )
{
	if (m_FlagDataList.empty() == true) { return (-1); }

	if (index < 0 || index >= libFlag_isUseFlagNum(flagType)) {
		ERROR_PRINT("__ERROR__ : libFlag_FlagMinimum ID[%d]\n", index);
		return (-1);
	}

	if(m_FlagDataList.at(index).m_Num < fNum )
	{
		m_FlagDataList.at(index).m_Num = fNum;
		return ( 1 );
	}

	return (0);
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_FlagMaximum( const char* flagName, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType)
{
	int i = libFlag_FlagDataIdGet(flagName, flagType);
	if (i < 0 || i >= libFlag_isUseFlagNum(flagType)) {
		ERROR_PRINT("__ERROR__ : libFlag_FlagMaximum ID[%d]\n", i);
		return (-1);
	}
	return libFlag_FlagMaximum(i, fNum, flagType);
}
int		App::FlagManager::libFlag_FlagMaximum( const int index, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType)
{
	if (m_FlagDataList.empty() == true) { return (-1); }

	if (index < 0 || index >= libFlag_isUseFlagNum(flagType)) {
		ERROR_PRINT("__ERROR__ : libFlag_FlagMaximum nID[%d]\n", index);
		return (-1);
	}
	if (m_FlagDataList.at(index).m_Num > fNum)
	{
		m_FlagDataList.at(index).m_Num = fNum;
		return (1);
	}
	return (0);	//	変更なし
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_FlagSetUp( const char* fName, const int  nSetup, const ENUM_CREATE_FLAG_TYPE flagType)
{
	int i = libFlag_FlagDataIdGet(fName, flagType);
	if (i < 0 || i >= libFlag_isUseFlagNum(flagType)) {
		ERROR_PRINT("__ERROR__ : libFlag_FlagSetUp ID[%d]\n", i);
		return (-1);
	}
	libFlag_FlagSetUp(i, nSetup, flagType);

	return (0);
}
int		App::FlagManager::libFlag_FlagSetUp( const int  nID, const int  nSetup, const ENUM_CREATE_FLAG_TYPE flagType)
{
	if(m_FlagDataList.empty() == true){ return (-1); }

	if (nID < 0 || nID >= libFlag_isUseFlagNum(flagType)) {
		ERROR_PRINT("__ERROR__ : libFlag_FlagSetUp nID[%d]\n", nID);
		return (-1);
	}
	m_FlagDataList.at(nID).m_Setup = nSetup;

	return (0);
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_FlagSetUpGet( const char* fName, const ENUM_CREATE_FLAG_TYPE flagType)
{
	int i = libFlag_FlagDataIdGet(fName, flagType);
	if (i < 0 || i >= libFlag_isUseFlagNum(flagType)) {
		ERROR_PRINT("__ERROR__ : \n");
		return (-1);
	}
	return libFlag_FlagSetUpGet(i, flagType);
}
int		App::FlagManager::libFlag_FlagSetUpGet( const int  nID, const ENUM_CREATE_FLAG_TYPE flagType)
{
	if (m_FlagDataList.empty() == true) { return (-1); }

	if (nID < 0 || nID >= libFlag_isUseFlagNum(flagType)) {
		ERROR_PRINT("__ERROR__ : \n");
		return (-1);
	}
	
	return m_FlagDataList.at(nID).m_Setup;
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_FlagAllGet( const ENUM_CREATE_FLAG_TYPE fType, int* pNum )
{
	int  i = 0, nMax = 0;

	nMax = libFlag_isUseFlagNum(fType);
	if (m_FlagDataList.empty() == true) { return (-1); }

	for (i = 0; i < nMax; i++)
	{
		*(pNum + i) = m_FlagDataList.at(i).m_Num;
	}
	return (0);
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_FlagAllSet( const ENUM_CREATE_FLAG_TYPE fType, int* pNum )
{
	int  i = 0, nMax = 0;

	nMax = libFlag_isUseFlagNum(fType);
	if (m_FlagDataList.empty() == true) { return (-1); }

	for (i = 0; i < nMax; i++)
	{
		m_FlagDataList.at(i).m_Num = *(pNum + i);
	}
	return (0);
}
//=================================================================================//
//  
//  
//=================================================================================//
int		App::FlagManager::libFlag_NormalFlagNumCheck( const char* flagName )
{
	return libFlag_isFlagNumber( flagName, eFLAG_TYPE_APPDATA );
}
int		App::FlagManager::libFlag_SystemFlagNumCheck( const char* flagName )
{
	return libFlag_isFlagNumber( flagName, eFLAG_TYPE_SYSTEM );
}



bool	App::FlagManager::libFlag_FlagPointerGet( const ENUM_CREATE_FLAG_TYPE nType, App::FlagObjectData** tagFlag )
{
	if( nType == eFLAG_TYPE_APPDATA )
	{
	}else{
	}
	return( true );
}
bool	App::FlagManager::libFlag_FlagPointerGet( const ENUM_CREATE_FLAG_TYPE nType, App::FlagObjectData** tagFlag, const int nIndex )
{
	if( nType == eFLAG_TYPE_APPDATA )
	{
	}else{
	}
	return( true );
}
void	App::FlagManager::libFlag_AppFlagEntry()
{
}