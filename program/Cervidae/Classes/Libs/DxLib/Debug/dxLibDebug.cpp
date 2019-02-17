

#include "DxLib.h"
#include "../../../Common/CommonList.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "dxLibDebugConfig.h"
#include "dxLibDebug.h"
#include "../dxLibCommon.h"
#include "../dxLibDefine.h"

#if PROJECT_DEBUG

//=================================================================================//
//  dxLibDebug.cpp
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/30.
//=================================================================================//

/////////////////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////
AppLib::DebugMenuData::DebugMenuData() :
	m_debCount_(0),
	m_debModeType_(0),
	appDebStartFunc(NULL),
	appDebEndFunc(NULL),
	appDebMainFunc(NULL),
	appDebRenderFunc(NULL)
{
}
AppLib::DebugMenuData::~DebugMenuData()
{
}


AppLib::DebugModeOperat* AppLib::DebugModeOperat::s_pInstance;

// Instance Make
AppLib::DebugModeOperat* AppLib::DebugModeOperat::getInstance()
{
	if( !s_pInstance )
	{
		s_pInstance = new AppLib::DebugModeOperat();
		if( s_pInstance ){
			s_pInstance->debugParamInitialize();
		}
	}
	return s_pInstance;
};

bool	AppLib::DebugModeOperat::debugParamInitialize()
{
	m_debMode_ = 0;
	m_debMenuSelIndex_ = 0;
	m_debDrawEnable_ = 0;

	m_datDebMenu.clear();

	return false;
}

int		AppLib::DebugModeOperat::debugMenuNameSet( const int setMode, const char * szName )
{
	if( 0 > setMode || setMode >= DxLib::DebugConfig::ENUM_DEBUG_MODE_TYPE_MAX ){
		return( -1 ); // モード設定エラー
	}





	return 0;
}

// 指定のデバッグモードを開始した時の開始関数セット
int		AppLib::DebugModeOperat::debugModeStartProcSet( const int setMode, const char * szName, void(*pStartFunc)() )
{
	if( 0 > setMode || setMode >= DxLib::DebugConfig::ENUM_DEBUG_MODE_TYPE_MAX ){
		return( -1 ); // モード設定エラー
	}
	DebugMenuData  startData_;
	startData_.appDebStartFunc = pStartFunc;

	m_datDebMenu.push_back( startData_ );

	return 0;
}
// 指定のデバッグモードを開始した時の終了関数セット
int		AppLib::DebugModeOperat::debugModeEndProcSet( const int setMode, const char * szName, void(*pEndFunc)() )
{
	if( 0 > setMode || setMode >= DxLib::DebugConfig::ENUM_DEBUG_MODE_TYPE_MAX ){
		return( -1 ); // モード設定エラー
	}
	DebugMenuData  endData_;
	endData_.appDebEndFunc = pEndFunc;

	m_datDebMenu.push_back( endData_ );

	return 0;
}
// 指定のデバッグモードを開始した時の処理関数セット
int		AppLib::DebugModeOperat::debugModeMainProcSet( const int setMode, const char * szName, int(*pMainFunc)() )
{
	if( 0 > setMode || setMode >= DxLib::DebugConfig::ENUM_DEBUG_MODE_TYPE_MAX ){
		return( -1 ); // モード設定エラー
	}
	DebugMenuData  mainData_;
	mainData_.appDebMainFunc = pMainFunc;

	m_datDebMenu.push_back( mainData_ );

	return 0;
}
// 指定のデバッグモードを開始した時の描画処理関数セット
int		AppLib::DebugModeOperat::debugModeRenderProcSet( const int setMode, const char * szName, void(*pRenderFunc)() )
{
	if( 0 > setMode || setMode >= DxLib::DebugConfig::ENUM_DEBUG_MODE_TYPE_MAX ){
		return( -1 ); // モード設定エラー
	}
	DebugMenuData  renderData_;
	renderData_.appDebRenderFunc = pRenderFunc;

	m_datDebMenu.push_back( renderData_ );

	return 0;
}

//==================================================================//
// 
int		AppLib::DebugModeOperat::debugAppUpdate()
{
	if( DxLib::CheckHitKey( KEY_INPUT_LSHIFT ) && 
		DxLib::CheckHitKey( KEY_INPUT_D ) )
	{
		DEBUG_PRINT("[AppSystem] appSystemUpdate() DEBUG MODE SETUP\n");
	}
	else if( DxLib::CheckHitKey( KEY_INPUT_SPACE ) )
	{
		debugDxPrintfLogClear();
	}

	
	return 0;
}

// printfDx で表示した簡易画面出力履歴をクリアする
void	AppLib::DebugModeOperat::debugDxPrintfLogClear()
{
	const int isDxResult = clsDx();
	if( isDxResult == -1 ){}

}





#endif// PROJECT_DEBUG

