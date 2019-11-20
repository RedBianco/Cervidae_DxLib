

#include "DxLib.h"
#include "../../../../Common/appCommonParam.h"
#include "../../../../Common/appErrorCode.h"
#include "../../../../Common/appProcessCode.h"
#include "../appResourcesConfig.h"
#include "appVramContainer.h"
#include "appVramConfig.h"
#include "appVramControl.h"
#include "appFileGraphic.h"


//////////////////////////////////////////////////////////////////////////////////////////////////
/*
	DX���C�u����	�O���t�B�b�N�t�@�C���Ǘ��V�X�e��
	
	���c�w���C�u�����ł́ALoadGraph ���̉摜�t�@�C���������֐��S�ʂ�
	  �w��̃t�@�C�����̖��[�Ɂw_a�x���t���摜�t�@�C�����݂����ꍇ
	  ���̉摜�t�@�C���𓧖����Ƃ��ēǂݍ��݂܂��B

	LastUpdate : 2019.05.02
*/
//////////////////////////////////////////////////////////////////////////////////////////////////




/*
 *	@process	
 *
 **/
DxLib::AppFileGraphicManager::AppFileGraphicManager()
{
}
DxLib::AppFileGraphicManager::~AppFileGraphicManager()
{
}
//=============================================================================================//
//  �O���t�B�N�X�t�@�C���Ǘ��V�X�e����{������
bool	DxLib::AppFileGraphicManager::_graphicSystemInit()
{
	{
		auto containerSize = static_cast<int>( m_graphicContainer.size() );
		for( int i = 0; i < containerSize; ++ i )
		{
//			m_graphicContainer[i].gp_FileCount = AppLib::Resources::FileProcess::eVRAM_ENTRY_NONE;
//			m_graphicContainer[i].gp_FileArch = 0;
//			m_graphicContainer[i].gp_FileNum = -1;
//			m_graphicContainer[i].gp_FileAttr = 0;
//			m_graphicContainer[i].gp_FileID	= -3;
//			m_graphicContainer[i].gp_FileHandle = AppLib::Resources::FileProcess::eGPFILE_HANDLE_NONUSE;
//			m_graphicContainer[i].gp_LoadingFlag = AppLib::Resources::FileProcess::eVRAM_ENTRY_NONE;
		}
	}
	return true;
}

//=============================================================================================//
//  �O���t�B�N�X�t�@�C���Ǘ��V�X�e���I������
bool	DxLib::AppFileGraphicManager::_graphicSystemExit()
{
	return false;
}

//=============================================================================================//
//  �摜�^�C�v�Ɖ摜������G�̓o�^�ԍ���Ԃ�
//		@param		int		gp_type		:	�o�^VRAM�^�C�v
//		@param		char *	gp_name		:	�摜�t�@�C����
//	@return		����->�o�^�ԍ�	
int		DxLib::AppFileGraphicManager::_graphicVramFileIdBackNumCheck( const int  gp_type, const char* gp_name )
{
	int	i = 0;
	int	gp_Blank = -1;
	int gp_EntryMax = 0;
	{
		// �O���t�B�b�N���[�h�\�ő吔���擾
		i = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax, NULL );
#if PROJECT_DEBUG
		if( i < 0 ){
			return ( AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX);
		}
#endif

		// �������O�̃t���O��T��
		for( i = 0; i < gp_EntryMax; ++ i ) {
			if( m_graphicContainer[i].gp_FileCount == -1 ) {
				// �}�C�i�X�Ȃ�󂫂̏ꏊ�Ƃ��ĕԂ�
				if( gp_Blank == -1 ){
					gp_Blank = i;
				}
				continue;
			}
			// ��������ԍ���Ԃ�
			if( strcmp( m_graphicContainer[i].gp_FileName.c_str(), gp_name ) == 0 )
			{
				return  i;
			}
		}

		// ����Ȗ��O�͌����炸
		if( gp_Blank == -1 )
		{
			return  gp_EntryMax;
		}else{
			return  -(gp_Blank + 1);// �l���|(�}�C�i�X)�ŕԂ�
		}
	}
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  �^�C�v�Ɩ��O����O���t�B�b�N�̃��[�h�n���h�����擾
//		@param		int		gp_type		:	�o�^VRAM�^�C�v
//		@param		char *	gp_name		:	�摜�t�@�C����
//	@return		����->�O���t�B�b�N���[�h�n���h��   ���s->-1
int		DxLib::AppFileGraphicManager::_getGraphicTexVramLoadHandle( const int  gp_type, const char* gp_name )
{
	int		i = 0;
	int		gp_EntryMax = 0;
	int		gp_Result = -1;
	
	{
		// �O���t�B�b�N���[�h�\�ő吔���擾
		i = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
		if( i < 0 ){
			return ( AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX);
		}
#endif
		// �������O��T��
		for( i = 0; i < gp_EntryMax; ++ i ){
			// ���O�`�F�b�N
			if( strcmp( m_graphicContainer[i].gp_FileName.c_str(), gp_name ) == 0 ){
				gp_Result = i;// �C���f�b�N�X��ۑ�
				return ( m_graphicContainer[i].gp_FileHandle );// ����΃��[�h�n���h����Ԃ�
			}
		}
		// ���O��������Ȃ������A�܂胁�����ɃA�b�v����ĂȂ�
		if( gp_Result == -1 )
		{
			ERROR_PRINT("__ERROR__ : _getGraphicTexVramLoadHandle Result[%d]\n", gp_Result );
			return App::FileProcess::eFILE_RESULT_CODE_ERROR;
		}
	}
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  �L��(�ǂݍ��ݒ�)�O���t�B�b�N�n���h���̐����擾����
//	@return		-1->�G���[  ����ȊO->�O���t�B�b�N�n���h��
int		DxLib::AppFileGraphicManager::_getGraphicValiditLoadHandle()
{
	const int	graphHandle = DxLib::GetGraphNum();
#if PROJECT_DEBUG
	if( graphHandle < 0 ){
		ERROR_PRINT("__ERROR__ : NonClearHandle GetValiditLoadHandle()\n");
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	return ( graphHandle );
}

//=============================================================================================//
//  �������ւ̃O���t�B�b�N���[�h�\�ő吔���擾
//		@param		int		gp_type		:	�o�^VRAM�^�C�v
//		@param		int *	gp_Vrammax	:	
//	@return		0�ȊO->�G���[
int		DxLib::AppFileGraphicManager::_graphicVramFileMaxCheck( const int  gp_type, int * gp_Vrammax, GraphicFileContainer ** gpData )
{
	switch( gp_type % AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE_MAX )
	{
	//--------------------------------------------//
	// �V�X�e��
	//--------------------------------------------//
	case	AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM:
		{
			*gp_Vrammax = AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX;
		}
		break;
	//--------------------------------------------//
	// �������[
	//--------------------------------------------//
	case	AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY:
		{
			*gp_Vrammax = AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX;
		}
		break;
	default:
		// �G���[
#if PROJECT_DEBUG
		ERROR_PRINT("__ERROR__ : _graphicVramFileMaxCheck gpType\n");
#endif
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  �摜�o�^�����擾
//	���������ɏオ���Ă��鐔�ł͖���
//	��FileGraphicContainer�ɓo�^����Ă��鐔
//		@param		int  gp_type		:	�o�^VRAM�^�C�v
//	@return		0�ȊO->�G���[
int		DxLib::AppFileGraphicManager::_graphicVramFileEntryNumCheck( const int  gp_type )
{
	int	i = 0, count = 0;
	int	gp_EntryMax = 0;

	{
		i = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
		if( i < 0 ){
			return ( AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX);
		}
#endif
		for( i = 0; i < gp_EntryMax; ++ i ){
			// �o�^���Ă�Ȃ�J�E���g
			if( m_graphicContainer[i].gp_FileCount > -1 ){
				count ++;
			}
		}
		// �摜�o�^����Ԃ�
		return ( count );
	}
	ERROR_PRINT("__ERROR__ : _graphicVramFileEntryNumCheck\n");
	return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

//=============================================================================================//
//
//	�O���t�B�b�N�摜��o�^
//		@param		int		gp_type		:	�o�^VRAM�^�C�v
//		@param		char *	gp_name		:	�摜��
//		@param		int		gp_arc		:	�A�[�J�C�u�̓o�^�t�@�C��INDEX
//		@param		int		gp_file		:	�摜�t�@�C���ԍ�
//		@param		int		gp_attr		:	�摜�o�^���� [ ENUM_GPFILE_MAX �` ]
//											���摜�f�[�^�̓o�^�\�ő�C���f�b�N�X��9999
//	@return		0->����		0�ȊO->�G���[
//
//=============================================================================================//
int		DxLib::AppFileGraphicManager::_graphicVramTextureEntry( const int  gp_type, 
																const char * gp_name, 
																const int  gp_arc, 
																const int  gp_file, 
																const int  gp_attr )
{
#if PROJECT_DEBUG
	// ".png"�`���̉摜���ᖳ���Ȃ�G���[
/*	if( EtcStrSpeciWordCheck( gp_name, ".png" ) == false ){
		ERROR_PRINT("__ERROR__ : VramGpEntry TextureFormatError ! [%s]\n", gp_name );
		return App::ErrorCode::eRETURN_CODE_INVALID_FILEFORMAT;	
	}*/
#endif
	int	index = 0;
	int n = 0;
	int gp_EntryMax = 0;

	n = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
	if( n < 0 ){
		ERROR_PRINT("__ERROR__ : Entry _graphicVramFileMaxCheck\n");
		return ( -3 );// �G���[ MaxCheck Error
	}
#endif

	// �摜�^�C�v�Ɖ摜��������ɓo�^�ς݂��ǂ������ׂ�
	index = _graphicVramFileIdBackNumCheck( gp_type, gp_name );
#if PROJECT_DEBUG
	if( index >= gp_EntryMax ){
		ERROR_PRINT("__ERROR__ : Entry _graphicVramFileIdBackNumCheck\n");
		return ( -2 );	// �G���[ EntryMax Over Error
	}
	else if( index >= 0 ){
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// �o�^�ԍ�
	index = ( index + 1 ) * -1;

#if PROJECT_DEBUG
	// ����C���f�b�N�X�œo�^���Ȃ��l��(�ی�)
	if( gp_file >= ( AppLib::Resources::Parameter::EntryIndex::ENUM_RESOURCES_FILE_ENTRY_INDEX_MAX + 1 )){
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// �摜�t�@�C���̏��o�^
	m_graphicContainer[index].gp_FileCount = 0;					// �g�p�J�E���g(VRAM�グ�̎w�����󂯂邽�тɑ���
	m_graphicContainer[index].gp_FileArch = gp_arc;				// �A�[�J�C�u�t�@�C���ԍ�
	m_graphicContainer[index].gp_FileNum = gp_file;				// �t�@�C���̒��̔ԍ�
	m_graphicContainer[index].gp_FileAttr = gp_attr;			// �����A���������̊G���A�b�v������폜�����肷��
	m_graphicContainer[index].gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAMFILE_CLEAR;	// �ǂݍ��ݏ����ŌĂ΂ꂽ���̂� 

	// ���O�o�^
	m_graphicContainer[index].gp_FileName = gp_name;

	// �摜�e�N�X�`�����[�h�n���h��(�o�^�����̈�)
	m_graphicContainer[index].gp_FileHandle	= AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;
	
	// �����󋵁i�o�^�͏I����Ă���̂��ǂݍ��ݍς݂Ȃ̂����g�p�Ȃ̂����j
	m_graphicContainer[index].gp_ProcessStatus = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_ENTRYCLEAR;

	ERROR_PRINT("_graphicVramTextureEntry �o�^�n�j[ID:%d][\"%s\"]\n", index, m_graphicContainer[index].gp_FileName.c_str() );
	
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  �O���t�B�b�N�摜�̓o�^�f�[�^���폜
//		@param		int		gp_type		:	�o�^VRAM�^�C�v
//		@param		char *	gp_name		:	�摜�t�@�C����
//	@return		�C���f�b�N�X->����	-1->�G���[
int		DxLib::AppFileGraphicManager::_graphicVramFileEntryDel( const int  gp_type, char* gp_name )
{
	int i = 0;
	int gp_EntryMax = 0;

	// �������ւ̃O���t�B�b�N���[�h�\�ő吔���擾
	i = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
	if( i < 0 ){
		ERROR_PRINT("__ERROR__ : [ i ] _graphicVramFileEntryDel\n");
		return ( -2 );	// ERROR
	}
#endif

	// �摜�^�C�v�Ɖ摜������G�̓o�^�ԍ���Ԃ�
	i = _graphicVramFileIdBackNumCheck( gp_type, gp_name );
#if PROJECT_DEBUG
	if( i >= gp_EntryMax || i < 0 ){
		ERROR_PRINT("__ERROR__ : _graphicVramFileEntryDel\n");
		return ( -2 );	// ERROR
	}
#endif

	if( (i < gp_EntryMax) && i >= 0 )
	{
		if( m_graphicContainer[i].gp_FileCount > 0 )
		{
			auto result = 0;
			switch( gp_type )
			{
				//--------------------------------------------//
				// �V�X�e���^�C�v
				case AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM:
					result = _graphicVramTexDelete( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
													const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), AppLib::Resources::ProcessStatus::eDELMODE_COER );
					break;
				//--------------------------------------------//
				// �������[�^�C�v
				case AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY:
					result = _graphicVramTexDelete( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
													const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), AppLib::Resources::ProcessStatus::eDELMODE_COER );
					break;
			default:
				return App::FileProcess::eFILE_RESULT_CODE_ERROR;
			}
		}
		// ���g�p��
		m_graphicContainer[i].gp_FileCount = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_NOUSE;
		// ��������
		return ( i );
	}

	ERROR_PRINT("__ERROR__ : _graphicVramFileEntryDel NotTexture\n");
	// �����G���폜���悤�Ƃ���
	return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

//=============================================================================================//
//  �O���t�B�b�N�摜�f�[�^�t�@�C���P�̓ǂݍ��݃������A�b�v
//		@param		int		gp_type		:	�o�^VRAM�^�C�v
//		@param		char *	gp_name		:	�摜�t�@�C����
//		@param		int		gp_mode		:	�摜�A�b�v���[�h
//		@param		int		check_num	:	
//	<<�߂�l>>
//		����->���[�h�n���h��
int		DxLib::AppFileGraphicManager::_graphicVramTexUp( const int  gp_type, char* gp_name, const int  gp_mode, int  check_num )
{
	int i = 0;
	int gp_Result = 0;
	int gp_EntryMax = 0;

	gp_Result = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
	if( gp_Result < 0 ){
		ERROR_PRINT("__ERROR__ : _graphicVramTexUp\n");
		return ( -2 );	// ERROR
	}
#endif

	// �摜�^�C�v�Ɖ摜������G�̓o�^�ԍ���Ԃ�
	i = _graphicVramFileIdBackNumCheck( gp_type, gp_name );
#if PROJECT_DEBUG
	if( i >= gp_EntryMax || i < 0 ){
		ERROR_PRINT("__ERROR__ : _graphicVramTexUp\n");
		return ( -2 );	// ERROR
	}
#endif

	if( 1 )
	{
		switch( gp_mode )
		{
		//----------------------------------------------------------------//
		// �ʏ�( �J�E���g�𑫂��Ă���1�ɂȂ����烁�����ɃA�b�v )
		//----------------------------------------------------------------//
		case	AppLib::Resources::ProcessStatus::eUPMODE_NORMAL:
			{
				if( check_num > 0 ){
					m_graphicContainer[i].gp_FileCount += check_num;
				}else{
					m_graphicContainer[i].gp_FileCount ++;
				}
				if( m_graphicContainer[i].gp_FileID < -1 ){
					// �t�@�C���ǂݍ���
					gp_Result = gpVramFileVramLoad( m_graphicContainer[i].gp_FileArch, gp_name, gp_type );
					m_graphicContainer[i].gp_FileID = -1;								// �t�@�C��ID
					m_graphicContainer[i].gp_FileHandle	= gp_Result;					// �t�@�C���n���h���Z�b�g
					m_graphicContainer[i].gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAMFILE_LOADING;	// �ǂݍ��ݏ�ԁF�����J�n
					m_graphicContainer[i].gp_ProcessStatus = 0;
					ERROR_PRINT("eUPMODE_NORMAL : VramLoad Handle[%d] Name[\"%s\"]\n", m_graphicContainer[i].gp_FileHandle, gp_name );
				}
			}
			break;
		//----------------------------------------------------------------//
		// VRAM�ɏ���ĂȂ�������A�b�v���������Ă���Ȃ������
		//----------------------------------------------------------------//
		case	AppLib::Resources::ProcessStatus::eUPMODE_ONE:
			{
				if( m_graphicContainer[i].gp_FileCount == 0 )
				{
					// �t�@�C���ǂݍ���
					gp_Result = gpVramFileVramLoad( m_graphicContainer[i].gp_FileArch, gp_name, gp_type );
					m_graphicContainer[i].gp_FileCount	= 1;								// �ǂݍ��ݏ��(-1:��������)
					m_graphicContainer[i].gp_FileID		= -1;								// �t�@�C��ID
					m_graphicContainer[i].gp_FileHandle	= gp_Result;						// �t�@�C���n���h���Z�b�g
					m_graphicContainer[i].gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAMFILE_LOADING; // �ǂݍ��ݏ�ԁF�����J�n
					m_graphicContainer[i].gp_ProcessStatus = 0;
					DEBUG_PRINT("eUPMODE_ONE : VramLoad Handle[%d] Name[\"%s\"]\n", m_graphicContainer[i].gp_FileHandle, gp_name );
				}
			}
			break;
		// ��ŕ��A�������������Ă邩��Ƃ��ɉ�������
		case	AppLib::Resources::ProcessStatus::eUPMODE_RETURN:
			{
			}
			break;
		default:
			break;
		}
	}
#if PROJECT_DEBUG
	if( gp_Result == -1 ){
		ERROR_PRINT("__ERROR__ : GraphicVramTexUp nVramRet[%d]\n", gp_Result );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;	// VRAM�グ�Ɏ��s��G���[
	}
#endif
	// �摜���[�h������n���h�����Ԃ��Ă���(DX���C�u�����̕s�ւ�)
	return gp_Result;
}

//=============================================================================================//
//  �O���t�B�b�N�摜�f�[�^�P�̍폜
//		@param		int		gp_type		:	�o�^VRAM�^�C�v
//		@param		char *	gp_name		:	�摜�t�@�C����
//		@param		int		gp_mode		:	�폜�^�C�v
//	@return		0->����  0�ȊO->���s
int		DxLib::AppFileGraphicManager::_graphicVramTexDelete( const int  gp_type, char* gp_name, const int  gp_mode )
{
	// �摜�����O�ɓo�^���Ă����^�C�v����
	int i = 0;
	int vramRet = 0, gp_EntryMax = 0;

	vramRet = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
	if( vramRet < 0 ){
		ERROR_PRINT("__ERROR__ : _graphicVramTexDelete[%d]\n", vramRet );
		return ( -2 );	// ERROR
	}
#endif

	// �摜�^�C�v�Ɖ摜������G�̓o�^�ԍ���Ԃ�
	i = _graphicVramFileIdBackNumCheck( gp_type, gp_name );
#if PROJECT_DEBUG
	if( i >= gp_EntryMax || i < 0 ){
		ERROR_PRINT("__ERROR__ : _graphicVramFileIdBackNumCheck[%d]\n", i );
		return ( -2 );	// ERROR
	}
#endif

	// �J�E���g���O�ɂȂ�����폜
	{
		auto result = 0;
		switch( gp_mode )
		{
		//----------------------------------------------------------------//
		// �ʏ�i�J�E���g�������Ă���0�ɂȂ�����폜
		//----------------------------------------------------------------//
		case AppLib::Resources::ProcessStatus::eDELMODE_NORMAL:
			{
				if( m_graphicContainer[i].gp_FileCount > 0 ){
					m_graphicContainer[i].gp_FileCount --;
				}
				if( m_graphicContainer[i].gp_FileCount == 0 )
				{
					m_graphicContainer[i].gp_FileCount	=   0;
					// �O���t�B�b�N�̃��[�h�n���h�����폜
					result = _graphicVramFileFormat( gp_type, &m_graphicContainer[i] );
					m_graphicContainer[i].gp_FileID = -3;								// �t�@�C���ԍ�
					m_graphicContainer[i].gp_FileHandle	= AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;	// ���[�h�n���h��������
					m_graphicContainer[i].gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAMFILE_CLEAR;		// �ǂݍ��ݏ����I���F�폜
					DEBUG_PRINT("eDELMODE_NORMAL : VramLoad Handle[%d] Name[\"%s\"]\n", m_graphicContainer[i].gp_FileHandle, gp_name );
				}
			}
			break;
		//----------------------------------------------------------------//
		// �����폜��J�E���g��0��
		//----------------------------------------------------------------//
		case AppLib::Resources::ProcessStatus::eDELMODE_COER:
			{
				// �����폜
				if( m_graphicContainer[i].gp_FileCount > 0 )
				{
					m_graphicContainer[i].gp_FileCount	=  0;
					// �O���t�B�b�N�̃��[�h�n���h�����폜
					result = _graphicVramFileFormat( gp_type, &m_graphicContainer[i] );
					m_graphicContainer[i].gp_FileHandle = AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;	// ���[�h�n���h��������
					m_graphicContainer[i].gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAMFILE_CLEAR;		// �ǂݍ��ݏ����I���F�폜
					DEBUG_PRINT("eDELMODE_COER : VramLoad Handle[%d] Name[\"%s\"]\n", m_graphicContainer[i].gp_FileHandle, gp_name );
				}
				// �B�����𖳌���
				m_graphicContainer[i].gp_FileID = -3;
			}
			break;
		//----------------------------------------------------------------//
		// �폜���邾����J�E���g�͎c�����܂�
		//----------------------------------------------------------------//
		case AppLib::Resources::ProcessStatus::eDELMODE_DIS:
			{
				if( m_graphicContainer[i].gp_FileCount > 0 )
				{
					// �O���t�B�b�N�̃��[�h�n���h�����폜
					result = _graphicVramFileFormat( gp_type, &m_graphicContainer[i] );
					// �B�����̈󂵃`�F�b�N
					m_graphicContainer[i].gp_FileID = -2;
				}
			}
			break;
		//----------------------------------------------------------------//
		// �ⓚ���p�őS�폜
		//----------------------------------------------------------------//
		case AppLib::Resources::ProcessStatus::eDELMODE_COERALL:
			{
				(void)(gp_name);
				(void)(gp_mode);
				// �I�[���t�H�[�}�b�g
				result = gpVramLoadBuffFormatALL();
			}
			break;
		}
	}
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  �O���t�B�b�N�摜�f�[�^��ǂݍ��݁i�������ɃA�b�v�j
//		@param		int		gp_type		:	�摜�������o�^
//		@param		int		gp_mode		:	�摜�A�b�v�^�C�v
//		@param		int		gp_attr		:	�o�^����(-1�őS�ď悹��)
//	@return		0->����  0�ȊO->���s
int		DxLib::AppFileGraphicManager::_graphicVramTexAttrUp( const int  gp_type, const int  gp_mode, const int  gp_attr )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_graphicContainer.empty() ) { return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
#endif

	int i;
	auto result = 0;
	// gp_type = -1��eFILE_GRAPHIC_SYSTEM�œo�^���Ă���S�����摜���グ��
	if( gp_type == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM || (gp_type < 0) )
	{
		for( i = 0; i < AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX; ++ i )
		{
			// �����`�F�b�N
			if( m_graphicContainer[i].gp_FileAttr == gp_attr || ( gp_attr < 0 ) )
			{
				// �O���t�B�b�N�摜�f�[�^�P�̃A�b�v
				result = _graphicVramTexUp( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
								   			const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), gp_mode, 1 );
			}
		}
	}
	else{
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
	// gp_type = -1��eFILE_GRAPHIC_MEMORY�œo�^���Ă���S�����摜���グ��
	if( gp_type == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY || (gp_type < 0) )
	{
		for( i = 0; i < AppLib::Resources::ProcessStatus::OBJVRAM_LOADRESOURCES_MAX; ++ i )
		{
			// �����`�F�b�N
			if( m_graphicContainer[i].gp_FileAttr == gp_attr || gp_attr < 0 )
			{
				// �O���t�B�b�N�摜�f�[�^�P�̃A�b�v
				result = _graphicVramTexUp( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
								   			const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), gp_mode, 1 );
			}
		}
	}
	else{
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
	DEBUG_PRINT("AppFileGraphic::VramTexAttrUp CLEAR\n");
	// ��������
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  �O���t�B�b�N�̃��[�h�n���h�����폜
//		@param		int		gp_type		:	�o�^VRAM�^�C�v
//		@param		int		gp_mode		:	�摜�A�b�v�^�C�v
//		@param		int		gp_attr		:	�o�^����(-1�őS�č폜)
//	@return		0->����  0�ȊO->���s
int		DxLib::AppFileGraphicManager::_graphicVramTexAttrDelete( const int  gp_type, const int  gp_mode, const int  gp_attr )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_graphicContainer.empty() ) { return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
#endif

	int	i;
	auto result = 0;
	// gp_type = -1��eFILE_GRAPHIC_SYSTEM�œo�^���Ă���S�����摜���폜����
	if( gp_type == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM || (gp_type < 0) )
	{
		for( i = 0; i < AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX; ++ i )
		{
			// �����`�F�b�N
			if( m_graphicContainer[i].gp_FileAttr == gp_attr || (gp_attr < 0) )
			{
				// �O���t�B�b�N�摜�f�[�^�P�̍폜
				result = _graphicVramTexDelete( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
									   			const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), gp_mode );
			}
		}
	}
	else{
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
	// gp_type = -1��eFILE_GRAPHIC_MEMORY�œo�^���Ă���S�����摜���폜����
	if( gp_type == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY || (gp_type < 0) )
	{
		for( i = 0; i < AppLib::Resources::ProcessStatus::OBJVRAM_LOADRESOURCES_MAX; ++ i )
		{
			// �����`�F�b�N
			if( m_graphicContainer[i].gp_FileAttr == gp_attr || (gp_attr < 0) )
			{
				// �O���t�B�b�N�摜�f�[�^�P�̍폜
				result = _graphicVramTexDelete( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
									   			const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), gp_mode );
			}
		}
	}
	else{
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
	// ��������
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  �O���t�B�b�N�̃��[�h�n���h�����폜
//		@param		int		gp_type				:	�o�^VRAM�^�C�v
//		@param		FileGraphicContainer*		:	�N���X�|�C���^
//	@return		0 -> ����
int		DxLib::AppFileGraphicManager::_graphicVramFileFormat( const int  gp_type, GraphicFileContainer* pGpWork )
{
	auto result = 0;
	int returnCode = App::FileProcess::eFILE_RESULT_CODE_ERROR;
	char * targetFileName = nullptr;
	// �w��̃O���t�B�b�N���������ォ��폜����
	switch( gp_type % AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE_MAX )
	{
	// �V�X�e��
	case AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM:
		{
			// �O���t�B�b�N���������ォ��폜����
//			result = dxLib_gpVramBuffLoadFileFormat( (pGpWork)->gp_FileHandle );
			result = gpVramBuffLoadFileFormat( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM, const_cast<char*>( (pGpWork)->gp_FileName.c_str() ) );
			if ( result != -1 ) {
				returnCode = App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
			}
		}
		break;
	// �������[
	case AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY:
		{
			// �O���t�B�b�N���������ォ��폜����
//			result = dxLib_gpVramBuffLoadFileFormat( (pGpWork)->gp_FileHandle );
			result = gpVramBuffLoadFileFormat( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY, const_cast<char*>( (pGpWork)->gp_FileName.c_str() ) );
			if ( result != -1 ) {
				returnCode = App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
			}
		}
		break;
	default:
		// �ُ�P�[�X
#if PROJECT_DEBUG
		ERROR_PRINT("__ERROR__ : VramGpFormat Expectation Error[\"%s\"]\n", (pGpWork)->gp_FileName.c_str() );
#endif
		return returnCode;
	}
	// ��������
	return returnCode;
}

//=============================================================================================//
//  �w��O���t�B�b�N���������ǂݍ��݂���Ă��邩�`�F�b�N
//		@param		int	gp_type		�F	�o�^VRAM�^�C�v
//		@param		int	gp_name		�F	�摜��
//	@return		1	->����Ă�
//				0	->�悹��
//			   -1	->�悹���߂��Ă΂�ĂȂ�
int		DxLib::AppFileGraphicManager::_graphicVramTexUpCheck( const int  gp_type, const char* gp_name )
{
	int checkHandle_ = 0;
	// ���O����O���t�B�b�N�̃��[�h�n���h�����擾
	checkHandle_ = _getGraphicTexVramLoadHandle( gp_type, gp_name );
#if PROJECT_DEBUG
	if( checkHandle_ == -1 ){
		ERROR_PRINT("__ERROR__ : GraphicVramTexUpCheck gp_name[\"%s\"]\n", gp_name );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;	// �G���[
	}
#endif
	return  _graphicVramTexUpCheck( gp_type, checkHandle_ );
}
int		DxLib::AppFileGraphicManager::_graphicVramTexUpCheck( const int  gp_type, const int  gp_i )
{
	// �O���t�B�b�N�n���h�����w��o�[�W����
	int vramRet = 0, gp_BuffMax = 0;

	// �������ւ̃O���t�B�b�N���[�h�\�ő吔���擾
	vramRet = _graphicVramFileMaxCheck( gp_type, &gp_BuffMax );
#if PROJECT_DEBUG
	if( vramRet < 0 ){
		ERROR_PRINT("__ERROR__ : GraphicVramGpMaxCheck vramRet[%d]\n", vramRet );
		return ( -2 );	// �G���[
	}
	if( gp_i >= gp_BuffMax || gp_i < 0 ){
		ERROR_PRINT("__ERROR__ : GraphicVramTexUpCheck gp_i[%d]\n", gp_i );
		return ( -3 );	// ID�����������Ȃ�I��
	}
#endif

	if( m_graphicContainer[gp_i].gp_FileCount > 0 && m_graphicContainer[gp_i].gp_FileID == -1 )
	{
		switch( gp_type % AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE_MAX )
		{
		//----------------------------------------------
		// �V�X�e��
		//----------------------------------------------
		case	AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM:
			// �摜�^�C�v�Ɖ摜������G�̓o�^�ԍ����擾
			m_graphicContainer[gp_i].gp_FileID = _graphicVramFileIdBackNumCheck( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
																				 const_cast<char*>( m_graphicContainer[gp_i].gp_FileName.c_str() ) );// ( char*)��"const char*"���L���X�g���Ă�
			break;
		//----------------------------------------------
		// �������[
		//----------------------------------------------
		case	AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY:
			// �摜�^�C�v�Ɖ摜������G�̓o�^�ԍ����擾
			m_graphicContainer[gp_i].gp_FileID = _graphicVramFileIdBackNumCheck( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
																		         const_cast<char*>( m_graphicContainer[gp_i].gp_FileName.c_str() ) );// ( char*)��"const char*"���L���X�g���Ă�
			break;
		default:
			return App::FileProcess::eFILE_RESULT_CODE_ERROR;
		}
	}
	if( m_graphicContainer[gp_i].gp_FileCount > 0 )
	{
		if( m_graphicContainer[gp_i].gp_FileID >= 0 ){
			return ( 1 );	// ����Ă�
		}else{
			return ( 0 );	// �悹��
		}
	}
	return App::FileProcess::eFILE_RESULT_CODE_ERROR;	// �悹���߂��Ȃ�
}

//=============================================================================================//
//  �w�葮���̉摜���S�ďオ���Ă邩���ׂ�
//	��ENUM_GPFILE_LIST�`
//	���w��^�C�v�̂݃s���|�C���g�Œ��ׂ�p
//		@param		int  gp_Attrtype	:	�摜�o�^����
//	@return		1->����(�S�ďオ���Ă�) 
int		DxLib::AppFileGraphicManager::_graphicVramAttrTexUpCheck( const int  gp_Attrtype )
{
	int i;
	for( i = 0; i < AppLib::Resources::ProcessStatus::OBJVRAM_LOADRESOURCES_MAX; ++ i )
	{
		// �����������ǂ������ׂ�
		if( m_graphicContainer[i].gp_FileAttr == gp_Attrtype )
		{
			// �ǂݍ��ݏ����ŌĂ΂ꂽ���̂����ׂ�
			// ���o�^������VRAM�ɏグ�Ė����ꍇ�͒e��
			if( m_graphicContainer[i].gp_LoadingFlag == AppLib::Resources::ProcessStatus::eVRAMFILE_LOADING )// �ǂݍ��݊J�n���������ǂ���
			{
				// ���[�h�n���h���𒲂ׂ�(�ǂݍ���ł��邩)
				if( m_graphicContainer[i].gp_FileHandle != AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE )
				{
					// �ǂݍ��݂��������Ă�H
					// ���ǂݍ��݂��������Ă���΃��[�h�n���h����gp_FileHandle�ɓ����Ă���͂�
				}else{
					// �܂��ǂݍ��ݒ����������Ȃ̂�true�͕Ԃ��Ȃ�
//					return ( 2 );
				}
			}else{
				// �ǂݍ��ݎ��̖��߂��ĂȂ�
			}
		}else{
			// �w�肵�������ƈႤ
			return App::FileProcess::eFILE_RESULT_CODE_ERROR;
		}
	}
	DEBUG_PRINT("[GRAPH] _graphicVramAttrTexUpCheck() �| ALL CLEAR\n");
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;// �S�ďオ���Ă�
}

//=============================================================================================//
//  �S�����̉摜�ŏ������̉摜���L�邩���ׂ�
//	<<�߂�l>>
//		0->�ǂݍ��ݏ�����	1->�ǂݍ��ݑS�I��
int		DxLib::AppFileGraphicManager::_graphicVramAttrTexUpCheckALL()
{
	// ���S�^�C�v���ׂ�p
	int nCount__ = 0;
	int nResult__ = 0;

	int nGpTypeMax = AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE_MAX;
	int i;
	for( i = 0; i < nGpTypeMax; ++ i )
	{
		// �S�������ׂ�
		nResult__ = _graphicVramAttrTexUpCheck( i );
		if( nResult__ == 1 )
		{
			nCount__ ++;
			if( nCount__ >= nGpTypeMax ){
				DEBUG_PRINT("[GRAPH] _graphicVramAttrTexUpCheckALL() �| CLEAR\n");
				return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;// �S�����̓ǂݍ��݂��I����Ă���
			}
		}
	}
	// �ǂݍ��ݏ������Ȃ̂��L��
	return App::FileProcess::eFILE_RESULT_CODE_RUNNING;
}

//=============================================================================================//
//  �w��t�@�C���̉摜�ԍ����擾
//		@param		char * gp_name			:	�e�N�X�`���t�@�C����
//	@return		�o�^���Ă���t�@�C���ԍ� 
int		DxLib::AppFileGraphicManager::_graphicVramTexEntryNumCheck( const char* gp_name )
{
	// �摜�^�C�v�Ɖ摜������G�̓o�^�ԍ���Ԃ�
	int i = _graphicVramFileIdBackNumCheck(AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM, gp_name );
	int nGraphID_ = 0;

	nGraphID_ = m_graphicContainer[i].gp_FileNum;// �t�@�C���̎w��ԍ�
#if PROJECT_DEBUG
	if( nGraphID_ == -1 ){
		ERROR_PRINT("__ERROR__ : _graphicVramTexEntryNumCheck ID[%d]\n", nGraphID_ );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	// �o�^���Ă���t�@�C���ԍ���Ԃ�
	return ( nGraphID_ );
}

//=============================================================================================//
//  �w��t�@�C���̉摜�ԍ����擾(���摜�^�C�v�w��@�\�t��)
//	@param
//		int		gp_type		:	�o�^VRAM�^�C�v
//		char *	gp_name		:	�e�N�X�`���t�@�C����
//	@return
//		����->�o�^�t�@�C���ԍ�	���s->-1 
int		DxLib::AppFileGraphicManager::_graphicVramTexEntryNumCheckType( const int  gp_type, const char* gp_name )
{
	// �摜�^�C�v�Ɖ摜������G�̓o�^�ԍ���Ԃ�
	int i = _graphicVramFileIdBackNumCheck( gp_type, gp_name );
	int nGraphID_ = 0;
	
	nGraphID_ = m_graphicContainer[i].gp_FileNum;// �t�@�C���̎w��ԍ�
#if PROJECT_DEBUG
	if( nGraphID_ == -1 ){
		ERROR_PRINT("__ERROR__ : GpVramPointerSearch ID[%d]\n", nGraphID_ );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	// �o�^���Ă���t�@�C���ԍ���Ԃ�
	return ( nGraphID_ );
}

//=============================================================================================//
//  �o�^ID���疼�O�摜����Ԃ�
//		@param		int	gp_type			:	�o�^VRAM�^�C�v
//		@param		int	index			:	�o�^ID
//	@return		�o�^���Ă���t�@�C���� 
const char *	DxLib::AppFileGraphicManager::_graphicEntryNameGet( const int  gp_type, const int  index )
{
	int gp_EntryMax = 0;
	int i = 0;
	i = index;//dxLibGpVramPointerSearch( index );
#if PROJECT_DEBUG
	if( _graphicVramFileMaxCheck( gp_type, &gp_EntryMax ) < 0 ){
		return NULL;
	}
#endif
	const char * returnStr = m_graphicContainer[i].gp_FileName.c_str();
	return returnStr;
}

//=============================================================================================//
//  �O���t�B�b�N�Ǘ��V�X�e�������^�C��
//  �����t���[���R�[�� 
int		DxLib::AppFileGraphicManager::_graphicVramLibRuntime()
{
#if 0
	int i = 0;
	
	if( (gpGraphic_dxProc)->gp_ProcId > -1 )
	{
		if( (gpGraphic_dxProc)->gp_ProcState == DxLibGp::eVRAMUP_STOP )
		{
			(gpGraphic_dxProc)->gp_ProcState = DxLibGp::eVRAMUP_LOAD;
		}
		else
		{
			// �󂫂��Ȃ����L�^����Ă�󂫂��ID���������Ȃ�
			if( (gpGraphic_dxProc)->gp_ProcAkiId > (gpGraphic_dxProc)->gp_ProcId )
				(gpGraphic_dxProc)->gp_ProcAkiId = (gpGraphic_dxProc)->gp_ProcId;
			
			(gpGraphic_dxProc)->gp_ProcId		= -1;
			(gpGraphic_dxProc)->gp_ProcState	= DxLibGp::eVRAMUP_STOP;// �����̏�
			
			for( i = 0; i < AppLib::Resources::FileProcess::GPVRAM_TEXTUREENTRY_MAX; i ++ )
			{
				if( (gpGraphic_dxSys + i)->gp_FileNum >= 0 )	// UNI�t�@�C���ԍ��A�}�C�i�X�Ȃ疢�g�p
				{
					(gpGraphic_dxProc)->gp_ProcId = i;	// ��������ID,�}�C�i�X�Ȃ珈�����ĂȂ�
					break;
				}
			}
			return ( 1 );
		}
	}
#endif
	return ( 0 );
}

//=============================================================================================//
//  
//  
int		DxLib::AppFileGraphicManager::_graphicVramUpState()
{
#if 0
	if( (gpGraphic_dxProc) == NULL ){ return ( -1 ); }
	
	// �ǂݍ��ނ��̂��Ȃ�
	if( (gpGraphic_dxProc)->gp_ProcId < 0 )	// ��������ID,�}�C�i�X�Ȃ珈�����ĂȂ�
	{
		return ( 0 );
	}
	else if( (gpGraphic_dxProc)->gp_ProcState == DxLibGp::eVRAMUP_STOP )	// �ǂݍ��ނƂ���
	{
		return ( 1 );
	}
	else
	{
		return ( 2 );	// �t�@�C���ǂݍ��ݒ�
	}
#else
	return ( 0 );
#endif
}

//=============================================================================================//
//  �w��̃O���t�B�b�N�n���h���ƁA�����O���t�B�b�N�n���h������h�����Ă���
//	�O���t�B�b�N�n���h��( DerivationGraph �Ŕh�������n���h���ALoadDivGraph �ǂݍ���ō쐬���ꂽ�����̃n���h�� )��
//	��x�ɍ폜����
//	�߂�l		�O�F����
//			  �|�P�F�G���[���� 
int		DxLib::AppFileGraphicManager::_graphicVramSharingHandleFormat( const int  nSharHandle )
{
	const int nReturn = DxLib::DeleteSharingGraph( nSharHandle );
#if PROJECT_DEBUG
	// �G���[�`�F�b�N
	if( nReturn == -1 ){
		ERROR_PRINT("__ERROR__ : DeleteSharingGraph Handle[%d]\n", nSharHandle );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//	�摜�t�@�C���̕����ǂݍ���(�A�j���[�V�����A�ԉ摜��)
//	�������_�ł͎��O�o�^�͍s�킸�����ǂݍ���
//	����	arch_type				:	�A�[�J�C�u�^�C�v
//			gp_name			        :	�����ǂݍ��݂���摜�t�@�C��������̃|�C���^
//			gpDivNum				:	�摜�̕�������
//			gpDivSrcX, gpDivSrcY    :	�摜�̉������ɑ΂��镪�����Əc�ɑ΂��镪����
//			gpDivSizeW, gpDivSizeH	:	�������ꂽ�摜��̑傫��
//			pHandleBuf				:	�����ǂݍ��݂��ē����O���t�B�b�N�n���h����
//										�ۑ�����int�^�̔z��ւ̃|�C���^ 
//	�߂�l	   �O�F���� 
//			 �|�P�F�G���[���� 
int		DxLib::AppFileGraphicManager::_graphicAnimationGraphDivLoad(const int  arch_type,
																	char * gp_name, int  gpDivNum,
																	int    gpDivSrcX, int  gpDivSrcY, int  gpDivSizeW, int  gpDivSizeH,
																	int * pHandleBuf )
{
	int	fileResult = 0;

	char strLoadPath[256] = {};

	// �p�X�擾
	fileLoadGetAccessPath( arch_type, gp_name, strLoadPath );
	
	// �������ēǂݍ��݁A������[ int * HandleBuf ]�Ƀ��[�h�n���h�����i�[�����
	fileResult = DxLib::LoadDivGraph( strLoadPath, gpDivNum, gpDivSrcX, gpDivSrcY, gpDivSizeW, gpDivSizeH, pHandleBuf ) ;
#if PROJECT_DEBUG
	// �G���[�`�F�b�N
	if( fileResult == -1 ){
		ERROR_PRINT("__ERROR__ : LoadDivGraph Name[%s]\n", gp_name );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	return ( fileResult );
}

//=============================================================================================//
//  �摜���o�^�\����Ԃ�
//	(�󂢂Ă���ԍ���Ԃ��ADXLIB_GRAPHIC_VRAM_WORK�̍ő啪�`�F�b�N)
//	@return		����->�󂫃C���f�b�N�X		-1:�G���[
int		DxLib::AppFileGraphicManager::_graphicEntryUseIdCheck()
{
	int i = 0;
	// ���g�p�ӏ�(ID)��T��
	for( i = 0; i < AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX; i ++ )
	{
		// eGPFILE_HANDLE_NONUSE �Ȃ疢�o�^�����ɂȂ��Ă���
		// ���o�^���ǂ���
		if( m_graphicContainer[i].gp_FileHandle == AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE )
		{
			// ������΃C���f�b�N�X��Ԃ�
			return ( i );
		}
	}
	// �S�Ďg���Ă��ċ󂫂�����
	ERROR_PRINT("__ERROR__ : dxLib_gpGraphicEntryUseIdCheck NotUseID\n");
	return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

///////////////////////////////////////////////////////////////////////////////////////
/*
*	�ȈՉ����b�v�֐��Q
*/
///////////////////////////////////////////////////////////////////////////////////////

//=============================================================================================//
// 	�摜�t�@�C���o�^����(�����ȗ�����)
//	ARCHIVE_SYSTEM �Œ�
//		@param		int  gp_type			:	�o�^VRAM�^�C�v
//		@param		char * gp_name			:	�摜�t�@�C����
//		@param		int  gp_file			:	�摜�t�@�C���C���f�b�N�X
//		@param		int  gp_attr			:	�摜�t�@�C������
int		DxLib::AppFileGraphicManager::_wrapGraphicVramEntry( const int gp_type, char* gp_name, const int  gp_file, const int  gp_attr )
{
	return _graphicVramTextureEntry( gp_type, 
									 gp_name, 
									 AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
									 gp_file, 
									 gp_attr );
}
int		DxLib::AppFileGraphicManager::_wrapGraphicMemoryVramEntry( char* gp_name, const int  gp_file, const int  gp_attr )
{
	return _graphicVramTextureEntry( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
									 gp_name, 
									 AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
									 gp_file, 
									 gp_attr );
}
//=============================================================================================//
//	�摜�̓o�^���ǂݍ��݂���C�ɍs��
//		@param		int  gp_type			:	�o�^VRAM�^�C�v
//		@param		char * gp_name			:	�摜�t�@�C����
//		@param		int  gp_file			:	�摜�t�@�C���C���f�b�N�X
//		@param		int  gp_attr			:	�摜�t�@�C������
//	@return
//		����	->	���[�h�n���h��
//		���s	->	-1
int		DxLib::AppFileGraphicManager::_wrapGraphicVramSetup( const int  gp_type, char* gp_name, const int  gp_file, const int  gp_attr )
{
	// �摜�̓o�^
	int	nHandle = -1;
	nHandle = _graphicVramTextureEntry( gp_type, gp_name, AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM, gp_file, gp_attr );
	if( nHandle != 0 ){
		ERROR_PRINT("__ERROR__ : WrapGraphicVramSetup Name[\"%s\"]\n", gp_name );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;	// �G���[
	}

	// �摜�̃������ւ̓ǂݍ���
	int	nResult	= _graphicVramTexAttrUp( gp_type, AppLib::Resources::ProcessStatus::eUPMODE_ONE, gp_attr );
	if( nResult != 0 ){
		ERROR_PRINT("__ERROR__ : GraphicVramTexAttrUp Failed\n");
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;	// �G���[
	}
	return ( nHandle );	// ���[�h�n���h����Ԃ�
}



