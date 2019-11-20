
#include "DxLib.h"
#include "../../../../Common/appCommonParam.h"
#include "../../../../Common/appErrorCode.h"
#include "../../../../Common/appProcessCode.h"
#include "../appResourcesConfig.h"
#include "appFileSystem.h"
#include "appVramContainer.h"
#include "appVramConfig.h"
#include "appVramControl.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
/*
	DX���C�u����	VRAM�Ǘ��V�X�e��
	���ǂݍ��݉\�ȉ摜�`����[ BMP, JPEG, PNG, DDS, ARGB, TGA ]�̂U���

	LastUpdate : 2019.04.23
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

/*
	�G���[ C2447 '{': �Ή�����֐��w�b�_�[������܂���(���`���̉��������X�g ? )
*/
/*
	vector�͊Ԃ̗v�f���폜����ƈȍ~�̗v�f���O�ɏ��ɃY����i�����������Ə������Ԃ��|����̂Œ��Ӂj
*/

DxLib::AppVramController::AppVramController()
{
	m_FileContainer.clear();
}
DxLib::AppVramController::~AppVramController()
{
}


//================================================================================================
// VRAM�Ǘ��V�X�e����{����������
bool	DxLib::AppVramController::gpVramFileSystemInit()
{
#if defined( PROJECT_DEBUG )
	DEBUG_PRINT("\n");
#endif

	return false;
}

//================================================================================================
// VRAM�Ǘ��V�X�e���I������
void	DxLib::AppVramController::gpVramFileSystemExit()
{
#if defined( PROJECT_DEBUG )
	DEBUG_PRINT("\n");
#endif
}

//================================================================================================
// VRAM�Ǘ��V�X�e�������^�C��
void	DxLib::AppVramController::gpVramFileRuntime()
{
#if defined( PROJECT_DEBUG )
	DEBUG_PRINT("VRAM INFO : �ǂݍ��ݐ�\n");
#endif
}

//================================================================================================
// �O���t�B�b�N�t�@�C���̃������ւ̃��[�h
//	<<����>>
//		@param		int		archive_type	:	�A�[�J�C�u�^�C�v
//		@param		char *	vvfile_name		:	�摜�t�@�C���l�[��
//		@param		int		vvram_type		:	VRAM�^�C�v
//	<<�߂�l>>
//		�|�P	  :  �G���[����
//		�|�P�ȊO  :  �O���t�B�b�N�n���h��
int		DxLib::AppVramController::gpVramFileVramLoad( const int archive_type, const char * vvfile_name, int  vvram_type )
{
	// �t�@�C���ǂݍ���
	const int loadHandle = fileLoadAccess( archive_type, vvfile_name, NULL );
#if defined( PROJECT_DEBUG )
	if( loadHandle == -1 ){
		ERROR_PRINT("__ERROR__ : gpVramFileVramLoad FileResult\n");
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
	}
#endif

	// �Q�d�ǂݍ��݂̖h�~
	const int fileExist = gpVramLoadFileHandleGet( vvfile_name );
	if( fileExist > 0 ){ return ( App::FileVram::eRESULT_CODE_ERROR_DOUBLE_LOADING ); }
	
	/**
	 * �V�K�ǂݍ��݂̏��ݒ�
	 */
	VramFileContainer	fileData_;
	// �ǂݍ��݃J�E���g
	fileData_.vv_VramCount = AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED;
	// �t�@�C���n���h��
	fileData_.vv_FileHandle = loadHandle;
	// �t�@�C���l�[��
	fileData_.vv_TextureName = vvfile_name;

	// �ǂݍ��݃T�C�Y�o�b�t�@
	fileData_.vv_ReadBuff = NULL;

	// VRAM�^�C�v
	fileData_.vv_VramType = vvram_type;

	// �e�N�X�`���̃T�C�Y���
	int	_TexWidth = 0, _TexHeight = 0;
	auto result = gpVramLoadFileGetSize( fileData_.vv_FileHandle, &_TexWidth, &_TexHeight );
	fileData_.vv_WIDTH = _TexWidth;
	fileData_.vv_HEIGHT = _TexHeight;

	// �ǂݍ��ݐ�
    DEBUG_PRINT("[GRAPH] ID[%d] VramLoad : FileName[\"%s\"]\n", fileExist, vvfile_name );
    DEBUG_PRINT("[GRAPH] ID[%d] VramLoadSize : WIDTH[%d] HEIGHT[%d]\n", fileExist, fileData_.vv_WIDTH, fileData_.vv_HEIGHT );
	DEBUG_PRINT("[GRAPH] ID[%d] VramType : vv_VramType[%d], vp_LoadCount[%d]\n", fileExist, fileData_.vv_VramType, 0 );

	m_FileContainer.push_back( fileData_ );

	// �摜���[�h�ɐ���������O���t�B�b�N�n���h�����Ԃ�
	return loadHandle;
}

//================================================================================================
//	�w��̃O���t�B�b�N���������ォ��폜����
//		@param		int		vram_type		:	VRAM�^�C�v
//		@param		char *	vvfile_name		:	�O���t�B�b�N�l�[��
//	<<�߂�l>>
//		0	:	�o�b�t�@�N���A����
int		DxLib::AppVramController::gpVramBuffLoadFileFormat( const int vram_type, char * vvfile_name )
{
	// ���O����t�@�C���n���h�������߂Ă�����g�p
	int fileHandle = -1;
//	fileHandle = _getGraphicTexVramLoadHandle( vram_type, vvfile_name );
#if defined( PROJECT_DEBUG )
	if( fileHandle < 0 ){ return ( App::FileVram::eRESULT_CODE_ERROR_FAILED ); }
#endif
	// vector�\������폜����
	gpVramEntryDataClear( vvfile_name );

	// �t�@�C���n���h�����폜
	return gpVramBuffLoadFileFormat( fileHandle );
}
// ���n���h���w��֐��ł�vector�\���폜�N���A�͂���Ȃ��̂Œ��ڌĂԂ̂͋֎~��
int		DxLib::AppVramController::gpVramBuffLoadFileFormat( const int file_handle )
{
	// �w��̃t�@�C���n���h�����폜����
	const int formatResult = DxLib::DeleteGraph( file_handle );
#if defined( PROJECT_DEBUG )
	if( formatResult == -1 ){
		ERROR_PRINT("__ERROR__ : VramDelete : gpVramBuffLoadFileFormat( Handle[%d] )\n", formatResult );	// �폜���s
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
	}
#endif
	
	return ( App::FileProcess::eFILE_RESULT_CODE_SUCCESS );
}

//================================================================================================
// 	�������ɂ���摜��S�č폜
// 	��LoadDivGraph�ALoadGraph�AMakeGraph���œǂ݂��񂾁i�쐬�����j �O���t�B�b�N�����ׂč폜���A���������܂��B
// 	�@����ɂ���Đ�L����Ă����������̈���J�����邱�Ƃ��ł��܂��B
// 	@return		0->����		-1->���s
int		DxLib::AppVramController::gpVramLoadBuffFormatALL()
{
	// �ǂ݂��񂾃O���t�B�b�N�f�[�^�����ׂč폜����
	const int formatResult = DxLib::InitGraph();
#if defined( PROJECT_DEBUG )
	if( formatResult == -1 ){
		ERROR_PRINT("__ERROR__ : DeleteError : dxLib_gpVramLoadBuffFormatALL()\n");	// �폜���s
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
	}
#endif
    
	// ����
	return ( App::FileProcess::eFILE_RESULT_CODE_SUCCESS );
}

//================================================================================================
//	�������ɂ���w��O���t�B�b�N�̃T�C�Y�𓾂�
//	��Atlas�`���ŕ����̊G���ꖇ�ɂ��Ă���ꍇ�͂��̈ꖇ�̃T�C�Y�����̂Œ��̃e�N�X�`���ʂŎ�邱�Ƃ͏o���Ȃ�
//	����	int		vram_type		:	VRAM�^�C�v
//			char *	vvfile_name		:	�摜�t�@�C���l�[��
//			int *	pFileRectW		:	�O���t�B�b�N�̕���ۑ�����int�^�ϐ��̃|�C���^
//			int *	pFileRectH		:	�O���t�B�b�N�̍�����ۑ�����int�^�ϐ��̃|�C���^
//	<<�߂�l>>
//			  �O :	����
//			�|�P :	�G���[����
int		DxLib::AppVramController::gpVramLoadFileGetSize( const int vram_type, char * vvfile_name, int * pFileRectW, int * pFileRectH )
{
	// VRAM�^�C�v����
#if defined( PROJECT_DEBUG )
	if( vram_type >= AppLib::Resources::Parameter::ENUM_GRAPHIC_FILE_ENTRY_TYPE_MAX ){
		ERROR_PRINT("__ERROR__ : LoadFileGetSize VRAM_GPTYPE_MAX Over !\n" );
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
	}
#endif

	// VRAM�^�C�v�Ɩ��O����O���t�B�b�N�̃��[�h�n���h�����擾
	int fileHandle = -1;
//	fileHandle = _getGraphicTexVramLoadHandle( vram_type, vvfile_name );
#if defined( PROJECT_DEBUG )
	if( fileHandle == -1 ){
		// �o�^���ĂȂ��{�������ɏオ���ĂȂ�
		ERROR_PRINT("__ERROR__ : LoadFileGetSize Filed Name[%s]\n", vvfile_name );
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
	}
#endif

	return gpVramLoadFileGetSize( fileHandle, pFileRectW, pFileRectH );
}
int		DxLib::AppVramController::gpVramLoadFileGetSize( const int file_handle, int * pFileRectW, int * pFileRectH )
{
	// �w��n���h���Œ��ׂ�o�[�W����
	int sizeCheck = -1;
	// �T�C�Y�`�F�b�N
	sizeCheck = DxLib::GetGraphSize( file_handle, pFileRectW, pFileRectH );
#if defined( PROJECT_DEBUG )
	if( sizeCheck == -1 ){
		ERROR_PRINT("__ERROR__ : gpVramLoadFileGetSize Handle [%d]\n", file_handle );
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );	// �t�@�C���擾���s
	}
	if( pFileRectW < 0 || pFileRectH < 0 ){
		ERROR_PRINT("__ERROR__ : gpVramLoadFileGetSize RectW[%d] RectH[%d]\n", pFileRectW, pFileRectH );
		return ( App::FileVram::eRESULT_CODE_ERROR_SIZECHECK );	// �e�N�X�`���T�C�Y�擾���s
	}
#endif

	return ( App::FileProcess::eFILE_RESULT_CODE_SUCCESS );
}



//================================================================================================
// ���O����VRAM�t�@�C���n���h�����擾
//	��dxLib_gpVramFileVramLoad���Ă񂾌�Ŗ����Ƌ@�\���Ȃ�
//		@param		char * vvfile_name		:	�摜�t�@�C���l�[��
//	@return		����->�O���t�B�b�N�̃��[�h�n���h��	-1->���s
int		DxLib::AppVramController::gpVramLoadFileHandleGet( const char * vvfile_name )
{
	const int fileLength = 0;
	{
		std::vector< DxLib::VramFileContainer>::const_iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr ) {
			if ( itr != m_FileContainer.end() ) {
				// ���O����v���邩
				if( strcmp( itr->vv_TextureName.c_str(), vvfile_name ) == 0 ) {
					// (gpVramFileVramLoad)���Ă΂�Ă��邩���ׂ�
					if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED ) {
						// ���݂���΃��[�h�n���h����Ԃ�
						return itr->vv_FileHandle;
					}
				}
			}
		}
	}

	ERROR_PRINT("__ERROR__ : gpVramLoadFileHandleGet [%s]\n", vvfile_name );
	// �w�肵�����O����������
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//================================================================================================
//	���O����f�[�^INDEX���擾
//	��dxLib_gpVramFileVramLoad���Ă񂾌�Ŗ����Ƌ@�\���Ȃ�
//		@param		char * vvfile_name		:	�摜�t�@�C���l�[��
//	@return		-1->���s
int		DxLib::AppVramController::gpVramGetDataIndex( char * vvfile_name )
{
	{
#if 0
		// ���O����v���邩���ׂ�
//		decltype( DxLib::VramFileContainer )::iterator itr = std::find( m_FileContainer.begin(), m_FileContainer.end(), vvfile_name );
		std::vector< DxLib::VramFileContainer>::iterator itr = std::find( m_FileContainer.begin(), m_FileContainer.end(), vvfile_name );
		if ( itr != m_FileContainer.end() ){
			// (gpVramFileVramLoad)���Ă΂�Ă��邩���ׂ�
			if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED ){
				// ��v����΃f�[�^INDEX��Ԃ�
				return ( *itr );
			}
		}
		else{
			// ���݂��Ȃ�����
		}
#else
		// ���O����v���邩���ׂ�
		int index = 0;
		std::vector< DxLib::VramFileContainer>::const_iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr, ++ index ) {
			if ( itr != m_FileContainer.end() ) {
				if( strcmp( itr->vv_TextureName.c_str(), vvfile_name ) == 0 ) {
					// (gpVramFileVramLoad)���Ă΂�Ă��邩���ׂ�
					if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED )
					{
						// ��v����΃f�[�^INDEX��Ԃ�
						return ( index );
					}
				}
			}
		}
#endif
	}
	ERROR_PRINT("__ERROR__ : gpVramGetDataIndex [%s]\n", vvfile_name );
	// �w�肵�����O����������(���܂�o�^����Ă��Ȃ�)
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

int		DxLib::AppVramController::gpVramGetDataIndex( const int file_handle )
{
	{
#if 0
		// �t�@�C���n���h������v���邩���ׂ�
		std::vector< DxLib::VramFileContainer>::iterator itr = std::find( m_FileContainer.begin(), m_FileContainer.end(), file_handle );
		if ( itr != m_FileContainer.end() ){
			// (gpVramFileVramLoad)���Ă΂�Ă��邩���ׂ�
			if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED ){
				// ��v����΃f�[�^INDEX��Ԃ�
				return ( *itr );
			}
		}
		else{
			// ���݂��Ȃ�����
		}
#else
		// �t�@�C���n���h������v���邩���ׂ�
		int index = 0;
		std::vector< DxLib::VramFileContainer>::const_iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr, ++ index ) {
			if ( itr != m_FileContainer.end() ) {
				if( itr->vv_FileHandle == file_handle ) {
					// (gpVramFileVramLoad)���Ă΂�Ă��邩���ׂ�
					if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED )
					{
						// ��v����΃f�[�^INDEX��Ԃ�
						return ( index );
					}
				}
			}
		}
#endif
	}
	ERROR_PRINT("__ERROR__ : gpVramGetDataIndexHandle [%d]\n", file_handle );
	// �w�肵���n���h������������(���܂�VRAM�ɃA�b�v����Ă��Ȃ�)
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//================================================================================================
//	�w��t�@�C����VRAM�^�C�v�ݒ���擾
//	��dxLib_gpVramFileVramLoad���Ă񂾌�Ŗ����Ƌ@�\���Ȃ�
//		@param		char * vvfile_name		:	�摜�t�@�C���l�[��
//	@return		����-> VRAM�^�C�v
//				���s-> -1
int		DxLib::AppVramController::gpVramGetVVramType( const char * vvfile_name )
{
	{
#if 0
		// ���O����v���邩���ׂ�
		std::vector< DxLib::VramFileContainer>::iterator itr = std::find( m_FileContainer.begin(), m_FileContainer.end(), vvfile_name );
		if ( itr != m_FileContainer.end() ){
			// (gpVramFileVramLoad)���Ă΂�Ă��邩���ׂ�
			if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED ){
				// ��v�����VRAM�^�C�v��Ԃ�
				return ( itr->vv_VramType );
			}
		}
		else{
			// ���݂��Ȃ�����
		}
#else
		const int length = static_cast<int>( m_FileContainer.size() );

		// ���O����v���邩���ׂ�
		std::vector< DxLib::VramFileContainer>::const_iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr ) {
			if ( itr != m_FileContainer.end() ) {
				if( strcmp( itr->vv_TextureName.c_str(), vvfile_name ) == 0 ) {
					// (gpVramFileVramLoad)���Ă΂�Ă��邩���ׂ�
					if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED )
					{
						// ��v�����VRAM�^�C�v��Ԃ�
						return ( itr->vv_VramType );
					}
				}
			}
		}
#endif
	}
	ERROR_PRINT("__ERROR__ : gpVramGetVVramType [%s]\n", vvfile_name );
	// �w�肵�����O����������(���܂�o�^����Ă��Ȃ�)
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//================================================================================================
//	�w��n���h���C���f�b�N�X�̔z��o�^�����폜����
//	���K��VRAM����e�N�X�`���폜���̂݌Ăԗl��
//		@param		char * vvfile_name		:	�摜�t�@�C���l�[��
//	@return		0->����		-1->���s
int		DxLib::AppVramController::gpVramEntryDataClear( const char * vvfile_name )
{
	// �v�f�����ڂ�����������񂶂�Ȃ��v�f���Ə�������
	{
#if 0
		std::vector< DxLib::VramFileContainer>::iterator itr = std::find( m_FileContainer.begin(), m_FileContainer.end(), vvfile_name );
		if ( itr != m_FileContainer.end() ){
			// �w��v�f�폜
			m_FileContainer.erase( m_FileContainer.begin() + *itr );
		}
		else{
			// �w��v�f����������
		}
#else
		// ���O����v���邩���ׂ�
		int index = 0;
		std::vector< DxLib::VramFileContainer>::iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr, ++ index ) {
			if ( itr != m_FileContainer.end() ) {
				if( strcmp( itr->vv_TextureName.c_str(), vvfile_name ) == 0 ) {
					// �w��v�f�폜
					itr->vv_VramCount = AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_NON;
					itr->vv_FileHandle = -1;
					itr->vv_ReadBuff = nullptr;
					itr->vv_VramType = 0;
					itr->vv_WIDTH = 0;
					itr->vv_HEIGHT = 0;
					m_FileContainer.erase( m_FileContainer.begin() + index );

					return ( App::FileVram::eRESULT_CODE_SUCCESS );
				}
			}
		}
#endif
	}
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}
int		DxLib::AppVramController::gpVramEntryDataClear( const int file_handle )
{
	{
		// �t�@�C���n���h������v���邩���ׂ�
		int index = 0;
		std::vector< DxLib::VramFileContainer>::iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr, ++ index ) {
			if ( itr != m_FileContainer.end() ) {
				if( itr->vv_FileHandle == file_handle ) {
					// �w��v�f�폜
					itr->vv_VramCount = AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_NON;
					itr->vv_FileHandle = -1;
					itr->vv_ReadBuff = nullptr;
					itr->vv_VramType = 0;
					itr->vv_WIDTH = 0;
					itr->vv_HEIGHT = 0;
					m_FileContainer.erase( m_FileContainer.begin() + index );

					return ( App::FileVram::eRESULT_CODE_SUCCESS );
				}
			}
		}
	}
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//================================================================================================
//	�S�v�f�S�č폜����
int		DxLib::AppVramController::gpVramEntryDataClearALL()
{
	// ���v�f�����ڂ���ɂ���̂Ŗ����m�۔z��S�Ă��N���A����̂�Length��0�ɂȂ�
	{
	}
	return ( App::FileVram::eRESULT_CODE_SUCCESS );
}

//================================================================================================
//	�󂫔ԍ���T��(���폜����ċ󂫂��o�����C���f�b�N�X��T��)
int		DxLib::AppVramController::gpVramGetNotUseListIndex()
{
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
/*
	VRAM �f�o�b�O�֌W
*/
//////////////////////////////////////////////////////////////////////////////////////////////////








