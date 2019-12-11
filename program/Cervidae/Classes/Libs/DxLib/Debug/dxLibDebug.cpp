

#include "DxLib.h"
#include "../../../Common/appCommonParam.h"
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


bool	App::DebugModeOperat::debugParamInitialize()
{
	m_debMode_ = 0;
	m_debMenuSelIndex_ = 0;
	m_debDrawEnable_ = 0;

	m_datDebMenu.clear();

	return false;
}

int		App::DebugModeOperat::debugMenuNameSet( const int setMode, const char * szName )
{
	if( 0 > setMode || setMode >= DxLib::DebugConfig::ENUM_DEBUG_MODE_TYPE_MAX ){
		return( -1 ); // ���[�h�ݒ�G���[
	}


	return 0;
}

// �w��̃f�o�b�O���[�h���J�n�������̊J�n�֐��Z�b�g
int		App::DebugModeOperat::debugModeStartProcSet( const int setMode, const char * szName, void(*pStartFunc)() )
{
	if( 0 > setMode || setMode >= DxLib::DebugConfig::ENUM_DEBUG_MODE_TYPE_MAX ){
		return( -1 ); // ���[�h�ݒ�G���[
	}
	DebugMenuData  startData_;
	startData_.appDebStartFunc = pStartFunc;

	m_datDebMenu.push_back( startData_ );

	return 0;
}
// �w��̃f�o�b�O���[�h���J�n�������̏I���֐��Z�b�g
int		App::DebugModeOperat::debugModeEndProcSet( const int setMode, const char * szName, void(*pEndFunc)() )
{
	if( 0 > setMode || setMode >= DxLib::DebugConfig::ENUM_DEBUG_MODE_TYPE_MAX ){
		return( -1 ); // ���[�h�ݒ�G���[
	}
	DebugMenuData  endData_;
	endData_.appDebEndFunc = pEndFunc;

	m_datDebMenu.push_back( endData_ );

	return 0;
}
// �w��̃f�o�b�O���[�h���J�n�������̏����֐��Z�b�g
int		App::DebugModeOperat::debugModeMainProcSet( const int setMode, const char * szName, int(*pMainFunc)() )
{
	if( 0 > setMode || setMode >= DxLib::DebugConfig::ENUM_DEBUG_MODE_TYPE_MAX ){
		return( -1 ); // ���[�h�ݒ�G���[
	}
	DebugMenuData  mainData_;
	mainData_.appDebMainFunc = pMainFunc;

	m_datDebMenu.push_back( mainData_ );

	return 0;
}
// �w��̃f�o�b�O���[�h���J�n�������̕`�揈���֐��Z�b�g
int		App::DebugModeOperat::debugModeRenderProcSet( const int setMode, const char * szName, void(*pRenderFunc)() )
{
	if( 0 > setMode || setMode >= DxLib::DebugConfig::ENUM_DEBUG_MODE_TYPE_MAX ){
		return( -1 ); // ���[�h�ݒ�G���[
	}
	DebugMenuData  renderData_;
	renderData_.appDebRenderFunc = pRenderFunc;

	m_datDebMenu.push_back( renderData_ );

	return 0;
}

//==================================================================//
// 
int		App::DebugModeOperat::debugAppUpdate()
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

// printfDx �ŕ\�������ȈՉ�ʏo�͗������N���A����
void	App::DebugModeOperat::debugDxPrintfLogClear()
{
	const int isDxResult = clsDx();
	if( isDxResult == -1 ){}

}





#endif// PROJECT_DEBUG

