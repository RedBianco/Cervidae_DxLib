

#include "DxLib.h"
#include "../../../../Common/appCommonParam.h"
#include "../../../../Common/appErrorCode.h"
#include "../../../../Common/appProcessCode.h"
#include "../appResourcesConfig.h"
#include "appFileSystem.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//	���\�[�X�̃t�@�C���t�H���_�p�X�̊Ǘ�
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////


//==============================================================================================//
// 
DxLib::AppFileSystem::AppFileSystem() :
	m_ASyncLoadEnable( false )
{
	fileStructureClear();
	fileLoadSystemInit();

	DEBUG_PRINT("FileSystem : AppFileSystem �R���X�g���N�^\n");
}
DxLib::AppFileSystem::~AppFileSystem()
{
	DEBUG_PRINT("FileSystem : AppFileSystem �f�X�g���N�^\n");
}

//==============================================================================================//
//
void	DxLib::AppFileSystem::fileStructureClear( void )
{
	m_LoadList.clear();
}

//==============================================================================================//
// �t�@�C���A�N�Z�X�V�X�e���̊�{����������
//
bool	DxLib::AppFileSystem::fileLoadSystemInit( void )
{
	// �񓯊��ǂݍ��ݐݒ�( TRUE�F�񓯊��ǂݍ���	FALSE�F�����ǂݍ���( �f�t�H���g ) )
	auto result = fileSetASyncLoadAccessEnable( AppLib::Resources::FileSystem::FILE_LIB_ASYNC_LOAD_FALSE );
#if PROJECT_DEBUG
	if( result == -1 ){
		return false;
	}
#endif

	// �f�[�^���X�g�쐬
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MAIN]		= "library";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SYSTEM]	= "system";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_BACKGROUND] = "system";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SCRIPT]	= "script";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_BGM]		= "bgm";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_VOICE]	= "voice";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SE]		= "se";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MOVIE]	= "movie";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_EFFECT]	= "effect";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_BINARY]	= "bin";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_DATABASE]	= "database";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SAVEDATA]	= "savedata";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_3DMODEL]	= "3d";

	DEBUG_PRINT("FILE SYSTEM : LoadList Attribute Setting Clear." );

	return true;
}

//==============================================================================================//
// �A�N�Z�X�p�X�擾�{�t�@�C���ǂݍ���
//		@param		int  nDirIndex		:	�t�H���_INDEX
//		@param		char * szFileName	:	�t�@�C���l�[��
//		@param		dxLibFileCallBack	:	�o�^�R�[���o�b�N�֐�
//	@return		�摜���[�h�n���h��
int		DxLib::AppFileSystem::fileLoadAccess( const int  nDirIndex, const char * szFileName, appLibFileCallBack  fCallBack )
{

#if PROJECT_DEBUG
	if( (nDirIndex < 0) || (nDirIndex >= AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_MAX) ){
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	char strLoadPath[256] = {};
	std::string	loadFilePath;

	//----------------------------------------------------------------------------
	// �A�[�J�C�u�^�C�v SOUND
	// ��{�p�X"��)�C(DxLIBFILELOAD_IMAGEPATH)/sound/voice/voice_01.wav"�ɂȂ�
	//----------------------------------------------------------------------------
	if( (nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_BGM)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_VOICE)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SE)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MOVIE) )
	{
//		sprintf_s( strLoadPath, AppLib::Resources::Info::RESOURCES_LOAD_DIR_PATH"/%s/%s/%s", "sound", libLoadDirectory[ nDirIndex ].pFolder, szFileName );
		sprintf_s( strLoadPath, "/%s/%s/%s", "sound", m_LoadList[ nDirIndex ].c_str(), szFileName );
	}else{
		// �T�E���h�t�@�C���ȊO
		loadFilePath = AppLib::Resources::Info::RESOURCES_LOAD_ROOT_PATH + "%s/%s";
		sprintf_s( strLoadPath, loadFilePath.c_str(), m_LoadList[ nDirIndex ].c_str(), szFileName );
	}

	// �摜���������ɓǂݍ���
	const auto loadHandle = DxLib::LoadGraph( strLoadPath, FALSE );
#if PROJECT_DEBUG
	if( loadHandle == -1 ){
		ERROR_PRINT("__ERROR__ : DxLib::LoadGraph HandleError [%s]\n", strLoadPath );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	// �����Ȃ�摜LoadHandle��Ԃ�
	return loadHandle;
}

//==============================================================================================//
// �t�@�C���A�N�Z�X�p�X�̎擾�̂�
//		@param		int  nDirIndex			:	�t�H���_INDEX
//		@param		char * szFileName		:	�t�@�C���l�[��
//		@param		char * szGetOutPath		:	�t�@�C���A�N�Z�X�p�X�擾�p����
//	@return		true->����   false->���s
int		DxLib::AppFileSystem::fileLoadGetAccessPath( const int  nDirIndex, char * szFileName, char * szGetOutPath )
{
	char strLoadPath[256] = {};
	std::string	loadFilePath;

#if PROJECT_DEBUG
	if( (nDirIndex < 0) || (nDirIndex >= AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_MAX) ){
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	//----------------------------------------------------------------------------
	// �A�[�J�C�u�^�C�v SOUND
	// ��{�p�X"��)�C(DxLIBFILELOAD_IMAGEPATH)/sound/voice/voice_01.wav"�ɂȂ�
	//----------------------------------------------------------------------------
	if( (nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_BGM)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_VOICE)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SE)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MOVIE) )
	{
//		sprintf_s( strLoadPath, AppLib::Resources::Info::RESOURCES_LOAD_DIR_PATH"/%s/%s/%s", "sound", m_LoadList[ nDirIndex ].pFolder, szFileName );
		sprintf_s( strLoadPath, "/%s/%s/%s", "sound", m_LoadList[ nDirIndex ].c_str(), szFileName );
	}
	else{
		// �T�E���h�t�@�C���ȊO
		loadFilePath = AppLib::Resources::Info::RESOURCES_LOAD_ROOT_PATH + "%s/%s";
		sprintf_s( strLoadPath, loadFilePath.c_str(), m_LoadList[nDirIndex].c_str(), szFileName );
	}

	// �t�@�C�������R�s�[���Ď擾
	sprintf_s( szGetOutPath, 256, strLoadPath );

	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// �X�N���v�g(.lua)�t�@�C���A�N�Z�X�p�X�̎擾
//		@param		char * szFileName		:	�t�@�C���l�[��
//		@param		char * szGetOutPath		:	�t�@�C���A�N�Z�X�p�X�擾�p����
//	@return		true->����   false->���s
int		DxLib::AppFileSystem::fileLoadGetScriptPath( unsigned int  unFileIndex, char * szGetOutPath )
{
	char strLoadPath[256] = {};

#if PROJECT_DEBUG
	if( unFileIndex < 0 ){
		ERROR_PRINT("__ERROR__ : AppFileSystem::libFileLoadGetScriptPath - Index[%d]\n", unFileIndex );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;		
	}
#endif

	std::string scriptLoadPath = AppLib::Resources::Info::RESOURCES_SCRIPT_LOAD_ROOT_PATH + "%03d.lua";

	// �X�N���v�g(.lua)�t�@�C���A�N�Z�X�p�X�̎擾
	sprintf_s( strLoadPath, scriptLoadPath.c_str(), unFileIndex );
	
	// �t�@�C�������R�s�[���Ď擾
	sprintf_s( szGetOutPath, 256, strLoadPath );

	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// �t�@�C���T�C�Y���擾(���ǂݍ��݂͍s��Ȃ�)
//		@param		int  nDirIndex			:	�t�H���_INDEX
//		@param		char * szFileName		:	�t�@�C���l�[��
//	@return		hLoadFileSize:�t�@�C���T�C�Y  -1:�G���[
int		DxLib::AppFileSystem::fileAccessCheckSize( const int  nDirIndex, char * szFileName )
{
	char strLoadPath[256] = {};

	// �t�@�C���A�N�Z�X�p�X�̎擾
	fileLoadGetAccessPath( nDirIndex, szFileName, strLoadPath );

	// �t�@�C���T�C�Y���擾(TRUE:�t�@�C���T�C�Y FALSE:�|�P:�G���[����)
	long long  hLoadFileSize = -1;
	hLoadFileSize = DxLib::FileRead_size( strLoadPath );
#if PROJECT_DEBUG
	// �G���[���Ԃ��Ă�����t�@�C��������
	if( hLoadFileSize == -1 ){
		ERROR_PRINT("__ERROR__ : libFileAccessCheckSize Error[%s]\n", strLoadPath );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// �t�@�C���T�C�Y��Ԃ�
	return ( static_cast<int>( hLoadFileSize ));
}

//==============================================================================================//
// �t�@�C���T�C�Y���擾�{�ǂݍ��݋@�\�t��
//		@param		int		DirIndex		:	�t�H���_INDEX
//		@param		char *	FileName		:	�t�@�C���l�[��
//		@param		int *	resFileSize		:	�t�@�C���T�C�Y�擾�p����
//		@param		dxLibFileCallBack		:	�o�^�R�[���o�b�N�֐�
//	@return		�摜�̃��[�h�n���h��:����  -1:���s
int		DxLib::AppFileSystem::fileCheckSizeLoadAccess( const int  nDirIndex, char * szFileName, int * resFileSize, appLibFileCallBack  fCallBack )
{
	char strLoadPath[256] = {};

	// �t�@�C���A�N�Z�X�p�X�̎擾
	fileLoadGetAccessPath( nDirIndex, szFileName, strLoadPath );

	// �t�@�C���T�C�Y���擾(TRUE:�t�@�C���T�C�Y FALSE:�|�P:�G���[����)
	long long hLoadFileSize = -1;
	hLoadFileSize = DxLib::FileRead_size( strLoadPath );
#if PROJECT_DEBUG
	if( hLoadFileSize == -1 ){
		ERROR_PRINT("__ERROR__ : DxLib::FileRead_size : libFileCheckSizeLoadAccess\n");
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// �t�@�C���T�C�Y���Z�b�g
	*resFileSize = static_cast<int>( hLoadFileSize );

	// �ǂݍ��ݍ��
	int hFileResult = -1;
	hFileResult = DxLib::LoadGraph( strLoadPath ); // �摜���������ɓǂݍ���
#if PROJECT_DEBUG
	if( hFileResult == -1 ){
		ERROR_PRINT("__ERROR__ : DxLib::LoadGraph Error[%s]\n", strLoadPath );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// ��薳�������Ȃ�摜LoadHandle��Ԃ�
	return ( hFileResult );
}

//==============================================================================================//
// �񓯊��ǂݍ��݂��s�����ǂ�����ݒ肷��(( TRUE�F�񓯊��ǂݍ��݁@FALSE�F�����ǂݍ���( �f�t�H���g ) )
//	��( �񓯊��ǂݍ��݂ɑΉ����Ă���֐��̂ݗL�� )( TRUE:�񓯊��ǂݍ��݂��s��  FALSE:�񓯊��ǂݍ��݂��s��Ȃ�( �f�t�H���g ) )
//		@param		int  bASyncEnable		:	�ǂݍ��݃t���O
//	@return
//		�O�F����
//	  �|�P�F�G���[����
int		DxLib::AppFileSystem::fileSetASyncLoadAccessEnable( const int  bASyncEnable )
{
	int hASyncLoadEnable = -1;
	hASyncLoadEnable = DxLib::SetUseASyncLoadFlag( bASyncEnable );
#if PROJECT_DEBUG
	if( hASyncLoadEnable == -1 ){
		ERROR_PRINT("__ERROR__ : ASyncLoadEnable : Result ERROR\n");
		setASyncLoadEnable( false );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	setASyncLoadEnable( true );

	// �ݒ萬��(�񓯊���)
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// �n���h���̔񓯊��ǂݍ��݂��������Ă��邩�ǂ������擾
//		@param		int  iSyLoadHandle	:	���[�h�n���h��
//	@return
//		TRUE	:	�񓯊��ǂݍ��ݒ�
//		FALSE	:	�񓯊��ǂݍ��݂͏I�����Ă���
//			-1	:	�G���[
int		DxLib::AppFileSystem::fileGetASyncLoadHandleCheck( const int  nSyLoadHandle )
{
	int hLoadResult = -1;
	hLoadResult = DxLib::CheckHandleASyncLoad( nSyLoadHandle );
#if PROJECT_DEBUG
	if( hLoadResult == -1 ){
		ERROR_PRINT("__ERROR__ : dxLib_FileGetASyncLoadHandleCheck [%d]\n", nSyLoadHandle );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	if( hLoadResult == TRUE )
	{
		return ( AppLib::Resources::FileSystem::FILE_LIB_ASYNC_LOAD_TRUE ); // �܂��񓯊��ǂݍ��ݒ�
	}
	return ( AppLib::Resources::FileSystem::FILE_LIB_ASYNC_LOAD_FALSE ); // �񓯊��ǂݍ��ݏI��
}

//==============================================================================================//
// �񓯊��ǂݍ��ݒ��̏���(�n���h��)�̐����擾����
//	@return
//		0:�ǂݍ��ݖ���  0�ȊO:���s���Ă���񓯊��ǂݍ��ݏ����̐�
//	@comment
//		�񓯊��������L���ɂȂ��Ă鎞�ɈӖ�������
int		DxLib::AppFileSystem::fileGetASyncLoadHandleNum( void )
{
#if PROJECT_DEBUG
	if( !getASyncLoadFlag() ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
#endif

	const int mLoadNum = DxLib::GetASyncLoadNum();
	if( mLoadNum != 0 ){
		return ( mLoadNum );// �ǂݍ��ݏ������s���Ȃ̂œǂݍ��ݒ������̐���Ԃ�
	}
	return ( AppLib::Resources::FileSystem::FILE_LIB_ASYNC_LOAD_FALSE );  // ���s���Ă���ǂݍ��݂͖���
}

//==============================================================================================//
// �n���h���̔񓯊��ǂݍ��ݏ����̖߂�l���擾����
int		DxLib::AppFileSystem::fileGraphicsASyncLoadResult( const int  nHandle )
{
	if( !getASyncLoadFlag() ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }

	int result = -1;
	result = DxLib::GetHandleASyncLoadResult( nHandle );

#if PROJECT_DEBUG
	if( result < 0 ){
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	return ( result );
}

//==============================================================================================//
// �A�[�J�C�u�t�@�C���ǂݍ��݃p�X�擾�Z�b�g
//		@param		int  nArchSecIndex		:	�p�b�N�t�@�C��ID
//		@param		char * szFileName		:	.DXA�t�@�C���̒���ǂݍ��ޏꍇ�̃t�@�C����
//		@param		char * returnFile		:	�擾�p�o�b�t�@
//		@param		int  _ArchFileType		:	�A�[�J�C�u�ǂݍ��݃^�C�v
//	@return
//			0->����
int		DxLib::AppFileSystem::fileLoadArchivePathCheck( const int  nArchSecIndex, char * szFileName, char * returnFile, int  _ArchFileType )
{
	char charLoadPath[256] = {};
	
	// �A�[�J�C�u�t�@�C�����̂����邩�A�A�[�J�C�u�t�@�C���̒��̃t�@�C�������邩
	// �� DxLIB_ARCHIVE_FILE_ROOTPATH -> "D:/project/Application/PC_01/GameImage/bin"
	if( _ArchFileType == AppLib::Resources::Archive::ARCHIVE_FILE_LOADER_DXA )
	{
//		sprintf_s( charLoadPath, DxLIB_ARCHIVE_FILE_ROOTPATH"/%s", dxLib_ArchiveFileNameCheck( nArchSecIndex ));
	}
	else
	{
//		sprintf_s( charLoadPath, DxLIB_ARCHIVE_FILE_ROOTPATH"/%s/%s", dxLib_ArchiveFileNameCheck( nArchSecIndex ), szFileName );
	}
	
	// �t�@�C�������R�s�[���Ď擾
	sprintf_s( returnFile, 256, charLoadPath );
	
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// �t�@�C���̃������ւ̃��[�h
//		@param		char *	szReadFile		:	
//		@param		char *	szFileName		:	
//		@param		int		nDirIndex		:	
//		@param		int *	pFlag			:	
//	@return		0->����
int		DxLib::AppFileSystem::fileMemoryRead( char * szReadFile, char * szFileName, int nDirIndex, int * pFlag )
{
	void *	pFileBuff = nullptr;
	int		fileSize_ = 0;
	int		fileHandle_ = 0;

	// �t�@�C���̃T�C�Y�𓾂�
	fileSize_ = fileAccessCheckSize( nDirIndex, szReadFile );
#if PROJECT_DEBUG
	if( fileSize_ < 0 ){
		ERROR_PRINT("__ERROR__ : FileSiza None dxLib_MemoryFileRead\n");
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// �t�@�C�����i�[���郁�����̈�̊m��
	pFileBuff = malloc( fileSize_ );
	
	// �t�@�C�����J��
	fileHandle_ = DX_FILE_OPEN( szFileName );
	if( fileHandle_ == -1 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// �t�@�C�����ۂ��ƃ������ɓǂݍ���(�t�@�C���o�b�t�@,�ǂݏo���T�C�Y(�o�C�g),�t�@�C���n���h��)
	DX_FILE_READ( pFileBuff, fileSize_, fileHandle_ );
	
	// �t�@�C�������
	DX_FILE_CLOSE( fileHandle_ );

	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// �t�@�C���ǂݍ���
//	��FileRead_read�g�p�o�[�W����
//	<<Comment>>
//		�p�r�͎�ɉ{���\�ȃt�@�C���`���̂܂܃f�B�X�N�ɉ摜�f�[�^��ۑ����Ă��������Ȃ������Ɏg�p
//		���g���q�����t�@�C���Ƀ��l�[�������e�N�X�`���t�@�C������ǂݍ��ގ��Ȃ�
//	<<����>>
int		DxLib::AppFileSystem::fileBufferRead( const int  nDirIndex, char * szFileName, void * pBuffer )
{
	LONGLONG	nFileSize_ = -1;
	void *		pFileBuff = nullptr;
	int			nFileHandle = 0;

	char strLoadPath[256] = {};

	// �t�@�C���p�X�`�F�b�N
	fileLoadGetAccessPath( nDirIndex, szFileName, strLoadPath );

	// �t�@�C���̃T�C�Y�𓾂�
	nFileSize_ = DX_FILE_SIZE( strLoadPath );
	if( nFileSize_ < 0 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// �t�@�C�����i�[���郁�����̈�̊m��
	pFileBuff = malloc( (int)nFileSize_ );
	
	// �w��t�@�C�����J��
	nFileHandle = DX_FILE_OPEN( strLoadPath );
	if( nFileSize_ == -1 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// �t�@�C�����ۂ��ƃ������ɓǂݍ���
	DX_FILE_READ( pFileBuff, (int)nFileSize_, nFileHandle );
	
	// �t�@�C�������
	DX_FILE_CLOSE( nFileHandle );
	
	// ���������������O�ɃR�s�[
	pBuffer = pFileBuff;
	
	// �������̉��
	free( pFileBuff );

	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// �t�@�C���ǂݍ���
// ��FileRead_read�g�p�o�[�W����
// ���ǂݍ��񂾉摜�t�@�C������O���t�B�b�N�n���h�����쐬����
//	<<Comment>>
//		�p�r�͎�ɉ{���\�ȃt�@�C���`���̂܂܃f�B�X�N�ɉ摜�f�[�^��ۑ����Ă��������Ȃ������Ɏg�p
//	<<����>>
//		���̊֐��ō쐬�ꂽ�O���t�B�b�N�n���h���̓t���X�N���[����ʂ���^�X�N�؂�ւ�����
//		�ꎞ�I�Ƀf�X�N�g�b�v��ʂɖ߂����ꍇ�ēx�t���X�N���[����ʂɂȂ������ɉ摜�͎����I�ɕ�������܂���
//		���̏ꍇ[ SetRestoreGraphCallback ]�֐��œo�^�ł���摜�����֐��ŉ摜���ēx�ǂݍ��ޕK�v������܂�
int		DxLib::AppFileSystem::fileBufferReadCreateHandle( const int  nDirIndex, char * szFileName, void * pBuffer )
{
	LONGLONG	nFileSize_ = -1;
	void *		pFileBuff = nullptr;
	int			nFileHandle = 0;
	int			nGrHandle = 0;
	// LONGLONG����int�ɃL���X�g����

	char strLoadPath[256] = {};

	// �t�@�C���p�X�`�F�b�N
	fileLoadGetAccessPath( nDirIndex, szFileName, strLoadPath);

	// �t�@�C���̃T�C�Y�𓾂�
	nFileSize_ = DX_FILE_SIZE( strLoadPath );
	if( nFileSize_ < 0 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// �t�@�C�����i�[���郁�����̈�̊m��
	pFileBuff = malloc( (int)nFileSize_ );
	
	// �w��t�@�C�����J��
	nFileHandle = DX_FILE_OPEN( strLoadPath );
	if( nFileHandle == -1 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// �t�@�C�����ۂ��ƃ������ɓǂݍ���
	DX_FILE_READ( pFileBuff, (int)nFileSize_, nFileHandle );
	
	// �t�@�C�������
	DX_FILE_CLOSE( nFileHandle );
	
	// �O���t�B�b�N�n���h���̍쐬
	// ��������̉摜�C���[�W����O���t�B�b�N�n���h�����쐬����
	nGrHandle = DxLib::CreateGraphFromMem( pFileBuff, (int)nFileSize_ );
	if( nGrHandle == -1 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// ���������������O�ɃR�s�[
	pBuffer = pFileBuff;
	
	// �������̉��
	free( pFileBuff );
	
	// �O���t�B�b�N�n���h����Ԃ�
	return ( nGrHandle );
}














