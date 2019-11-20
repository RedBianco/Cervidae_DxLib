
#include "DxLib.h"
#include "../../../../../Common/appCommonParam.h"
#include "../../../../../Common/appErrorCode.h"
#include "../../../../../Common/appProcessCode.h"
#include "../../appResourcesConfig.h"
#include "appArchiveFileControl.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//	�A�[�J�C�u�t�@�C�����\�[�X�Ǘ��p�N���X
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *	�R���X�g���N�^
 */
DxLib::AppArchiveController::AppArchiveController() :
	m_LoadCounter( 0 )
{
	m_ArchiveType.assign( AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_MAX, 
						  AppLib::Resources::Archive::eARCHIVE_FILETYPE_NONE );

	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_NONE,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_RESOURCES,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_SCRIPT, ""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_BGM,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_VOICE,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_SE,		""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_MOVIE,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_EFFECT, ""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_SAVEDATA,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_MODEL,	""));

#if 0
	m_ArchiveData.insert( 0, { std::make_pair( AppLib::Resources::Command::eARCHIVE_FILETYPE_NONE, "" ) });
#endif
	DEBUG_PRINT("Archive : AppArchiveController �R���X�g���N�^\n");
}
DxLib::AppArchiveController::~AppArchiveController()
{
	DEBUG_PRINT("Archive : AppArchiveController �f�X�g���N�^\n");
}

//================================================================================================
//	@title	
//	@param	int nArchIndex
char *	DxLib::AppArchiveController::libArchiveFileNameCheck( const int nArchIndex )
{
#if PROJECT_DEBUG
	if( (nArchIndex < 0) || 
		(nArchIndex >= AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_MAX) ){
		return NULL;
	}
#endif


	DEBUG_PRINT("__LOG__ : \n" );
	return NULL;
}

//================================================================================================
//	@title	�c�w�A�[�J�C�u�t�@�C���̊g���q��ύX����
//	@param	char * arcFileName
int		DxLib::AppArchiveController::libArchiveFileExtensChange( char * arcFileName )
{
	auto result = DxLib::SetDXArchiveExtension( arcFileName );
#if PROJECT_DEBUG
	if( result == -1 ){
		ERROR_PRINT("__ERROR__ : libArchiveFileExtensChange [%s]\n", arcFileName );
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR ); // �G���[����
	}
#endif
	return ( result);
}

//================================================================================================
//	@title	�c�w�A�[�J�C�u�t�@�C���̃p�X���[�h��ݒ�
//	@param	char * filePassCode
int		DxLib::AppArchiveController::libArchiveFilePassSet( char * filePassCode )
{
	auto result = DxLib::SetDXArchiveKeyString( filePassCode );
#if PROJECT_DEBUG
	if( result == -1 ){
		ERROR_PRINT("__ERROR__ : libArchiveFilePassSet [%s]\n", filePassCode );
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR ); // �G���[����
	}
#endif
	return ( result);
}

//================================================================================================
//	@title	�c�w�A�[�J�C�u�t�@�C���ƃt�H���_�����݂����ꍇ�̗D��x�ݒ�
//	( 1:�t�H���_��D��@ 0:�c�w�A�[�J�C�u�t�@�C����D��( �f�t�H���g ) )
//	@param	int nLoadPriority
int		DxLib::AppArchiveController::libArchiveFileLoaderPrioritySetting( const int nLoadPriority )
{
	auto result = DxLib::SetDXArchivePriority( nLoadPriority );
#if PROJECT_DEBUG
	if( result == -1 ){
		ERROR_PRINT("__ERROR__ : libArchiveFileLoaderPrioritySetting\n");
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR ); // �G���[����
	}
#endif
	return ( result); // ����
}

//================================================================================================
//	�w��̂c�w�`�t�@�C�����ۂ��ƃ������ɓǂݍ���( �߂�l  -1:�G���[  0:���� )
//		@param	char * szArchFileName	:	�t�@�C����
//		@param	int  nArchIndex			:	�A�[�J�C�u�C���f�b�N�X
//		@param	int  nASyncLoad			:	�����ǂݍ��ݐݒ�(FALSE:�f�t�H���g)
//	<<�߂�l>>
//		0 : ����
//	   -1 : ���s(�G���[)
int		DxLib::AppArchiveController::libArchiveFileMemLoad( char * arcFileName, const int  nArchIndex, const int  nASyncLoad )
{
	char strArchPath[256] = {};

	// �A�[�J�C�u�t�@�C���̓ǂݍ��݃p�X���擾
//	dxLib_ArchiveFileLoadPathCheck( nArchIndex, arcFileName, strArchPath, DxLIB_ARCHIVE_LOADER_ARCHIVE );
	fileLoadArchivePathCheck( nArchIndex, arcFileName, strArchPath, AppLib::Resources::Archive::ARCHIVE_FILE_LOADER_PRI_ARCHIVE );
	
	// �t�@�C�����[�h
	auto result = DxLib::DXArchivePreLoad( strArchPath, nASyncLoad );
#if PROJECT_DEBUG
	if( result == -1 ){
		ERROR_PRINT("__ERROR__ : dxLib_ArchiveFileMemLoad\n");
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR ); // �G���[����
	}
#endif

	m_ArchiveType.push_back( nArchIndex );

	m_LoadCounter ++;

	return ( result );
}
int		DxLib::AppArchiveController::libArchiveFileMemLoader( char * arcFileName, const int  nArchIndex )
{
	return libArchiveFileMemLoad( arcFileName, nArchIndex, FALSE );
}

//================================================================================================
// �w��̂c�w�`�t�@�C���̎��O�ǂݍ��݂������������ǂ������擾����( �߂�l  TRUE:�������� FALSE:�܂� )
//		@param		char * szArchFileName		:	�t�@�C���p�X
//		@param		int  nArchIndex				:	�A�[�J�C�u�C���f�b�N�X
//	<<�߂�l>>
//		TRUE  : ����
//		FALSE : ���s(�܂�)
bool	DxLib::AppArchiveController::libisArchiveFileLoadIdle( char * arcFileName, const int  nArchIndex )
{
	// �ǂݍ��݂�����������
	auto result = DxLib::DXArchiveCheckIdle( arcFileName );
	if( result == 0 ){
		return true;	// �ǂݍ��ݐ���
	}
	return false;
}

//================================================================================================
// �w��̂c�w�`�t�@�C��������������������
//		@param		char * szArchFileName	:	�t�@�C���p�X
//		@param		int  nArchIndex			:	�A�[�J�C�u�C���f�b�N�X
//	<<�߂�l>>
//		0 : ����
//	   -1 : ���s(�G���[)
int		DxLib::AppArchiveController::libArchiveFileMemFree( char * arcFileName, const int  nArchIndex )
{
	//	������������
	auto result = DxLib::DXArchiveRelease( arcFileName );
#if PROJECT_DEBUG
	if( result == -1 ){
		ERROR_PRINT("__ERROR__ : dxLib_ArchiveFileMemFree\n");
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR );	// �G���[����
	}
#endif

	m_LoadCounter --;
	
	return ( result );
}
//================================================================================================
// �p�b�N�����c�w�`�t�@�C���̒��Ɏw��̃t�@�C�������݂��邩�ǂ����𒲂ׂ�
//	��szArchFileTarget �͂c�w�`�t�@�C�����J�����g�t�H���_�Ƃ����ꍇ�̃p�X
//		@param		char * szArchFileName		:	�t�@�C���p�X
//		@param		int  nArchIndex				:	�A�[�J�C�u�C���f�b�N�X
//		@param		char * szArchFileTarget		:	
//	<<�߂�l>>
//		1 : �t�@�C��������
//		0 : ����
//	   -1 : ���s(�G���[)
int		DxLib::AppArchiveController::libArchiveFileDirectoryCheck( char * arcFileName, int  nArchIndex, char * szArchTargetFile )
{
	auto result = DxLib::DXArchiveCheckFile( arcFileName, szArchTargetFile );
#if PROJECT_DEBUG
	if( !result ){
		ERROR_PRINT("__ERROR__ : dxLib_ArchiveFileDirectoryCheck \n");
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR );	// �G���[����
	}
#endif
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;	// �t�@�C�������݂���
}

