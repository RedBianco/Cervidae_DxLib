
#include "DxLib.h"
#include "../../../../Main.h"
#include "../../../../Common/appCommonParam.h"
#include "../../../../Common/appErrorCode.h"
#include "../../../../Common/appProcessCode.h"
#include "../../../../Common/CervidaeLib/Utility/UtilityForOperat.h"
#include "../appResourcesConfig.h"
#include "appFileGraphic.h"
#include "appVramFileManage.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//
//	�t�@�C��VRAM�Ǘ�����
//	[�摜�̓o�^]
//	vramTextureFileEntry
//
//	[�摜�̃������ւ̃A�b�v]
//	���P��
//	vramTextureFileSingleUpload
//
//	�����葮���̑S�t�@�C��
//	
//
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
	[README]
*/

/**
    �t�@�C���p�X����g���q�𒊏o���鏈���ł́Astrrchr�Ńp�X�̌������"."�̈ʒu���擾���܂��B
    "."�͕����ӏ��Ɋ܂܂��\�������邽�߁Astrchr��strstr�Ńp�X�̑O�����猟�����Ă͂����܂���B
    �܂��A�g���q����("."�Ȃ�)�̃t�@�C���p�X���n�����\�������邽�߁Astrrchr�̖߂�l�͕K��NULL�`�F�b�N����K�v������܂��B

    �g���q�̃`�F�b�N�����ł́A�J���}��؂�œn���ꂽ�g���q��strtok�ŕ������Astrcmp�Ŋg���q���r���Ă��܂��B
    �g���q�̑啶������������ʂ��Ȃ��ꍇ��stricmp��strcasecmp�Ŕ�r���s���Ă��������B

    �Ȃ��A��r�\�Ȋg���q�̕�����(szCmpExts)��1024����(�I�[�܂�)�ŌŒ�Ƃ��Ă��܂��B�ʏ�̎g�p�ł̓I�[�o�[���܂��񂪁A
    �K�v�ɉ����ē��I��szCmpExts���m�ۂ��Ă��������B
*/
bool    stringCheckExtension( const char* pszPath, const char* pszCmpExts )
{
    // �t�@�C���p�X�̊g���q�𒊏o
    const char* pszExt = strrchr( pszPath, '.' );
    if( pszExt && *(pszExt + 1) != '\0' ) {
        pszExt += 1;
    }
    else{
        return false; // �t�@�C���p�X�Ɋg���q�����݂��Ȃ��ꍇ��false
    }

	char* ctx = {};
    // �g���q���`�F�b�N(�啶����������ʂ���)
    char szCmpExts[1024];
	strncpy_s( szCmpExts, sizeof( szCmpExts ), pszCmpExts, sizeof( szCmpExts ) - 1);

    for( const char* pszCmpExt = strtok_s( szCmpExts, ",", &ctx ); pszCmpExt; pszCmpExt = strtok_s( NULL, ",", &ctx ) ) {
        if( strcmp( pszExt, pszCmpExt ) == 0 ){ 
            return true;
        }
    }
    return false;
}

/**
 * 
 * 
 */
DxLib::ResourcesLoadContainer *	DxLib::AppVramFileManager::getContainer( const char * fileName )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return NULL; }
#endif

    std::vector< DxLib::ResourcesLoadContainer >::iterator itr;
    for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr )
    {
        if ( itr != m_resourcesContainer.end() ) 
        {
			if( (strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0 ) ) 
			{
				return &*itr;
			}
/*
            if( (strcmp( (itr).operator*->m_vLoadTextureName.c_str(), fileName ) == 0 ) ) 
            {
                return (itr).operator*;
            }
*/
        }
    }

	ERROR_PRINT("__ERROR__ : getContainer DataFailed.\n");
    return NULL;
}

/**
 *
 */
DxLib::AppVramFileManager::AppVramFileManager() :
    m_LoadedFiles( 0 ),
	m_EnteredFiles( 0 )
{
	m_resourcesContainer.clear();

    DEBUG_PRINT("AppVramFile : VramFileManager �R���X�g���N�^\n");
}
DxLib::AppVramFileManager::~AppVramFileManager()
{
    DEBUG_PRINT("AppVramFile : VramFileManager �f�X�g���N�^\n");
}

/**
 *
 * 
 */
bool    DxLib::AppVramFileManager::vramFileSystemInit()
{
    return true;
}

/**
 *
 * 
 */
bool    DxLib::AppVramFileManager::vramFileSystemExit()
{
    vramContainerDataClearALL();

    DEBUG_PRINT("[VramFile] vramFileSystemExit :\n" );

    return true;
}

//=====================================================================================//
//	@name	�t�@�C���������A�b�v���[�h
//	
//	
//=====================================================================================//
int     DxLib::AppVramFileManager::vramTextureLoad( DxLib::ResourcesLoadContainer * pfileContainer )
{
#if PROJECT_DEBUG
    if ( pfileContainer == nullptr ) { return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
#endif

	auto loadResult = fileLoadAccess( pfileContainer->m_vFileArchIndex, pfileContainer->m_vLoadTextureName.c_str(), NULL );
    if ( loadResult == -1 ) {
        ERROR_PRINT("__ERROR__ : vramTextureLoad FileResult\n");
        return App::FileProcess::eFILE_RESULT_CODE_ERROR;
    }

    // �ǂݍ��݂ɐ���������n���ꂽ�R���e�i�̎w��������������čX�V����
    pfileContainer->m_vLoadFileHandle = loadResult;
	// �e�N�X�`���t�@�C���̏�����
    pfileContainer->m_vFileStatus = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_LOADING;

    // �e�N�X�`���̃T�C�Y���
    int	_TexWidth = 0, _TexHeight = 0;
    auto result = DxLib::GetGraphSize( loadResult, &_TexWidth, &_TexHeight );
#if PROJECT_DEBUG
    if ( result == -1 ) {
        ERROR_PRINT("__ERROR__ : vramTextureLoad GetFileSizeError.\n");
        return App::FileProcess::eFILE_RESULT_CODE_ERROR;
    }
#endif
	if ( _TexWidth > 0 ) {
		pfileContainer->m_vTextureObj.m_RenderW = _TexWidth;
	}
	if ( _TexHeight > 0 ) {
		pfileContainer->m_vTextureObj.m_RenderH = _TexHeight;
	}

    DEBUG_PRINT("[VramFile] TextureLoad TextureWidth[%d.px]. TextureHeight[%d.px]\n", pfileContainer->m_vTextureObj.m_RenderW, pfileContainer->m_vTextureObj.m_RenderH );
    DEBUG_PRINT("[VramFile] TextureLoad Handle[%d]. Name[\"%s\"]\n", pfileContainer->m_vLoadFileHandle, pfileContainer->m_vLoadTextureName.c_str() );

    return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=====================================================================================//
//	@name	�O���t�B�b�N�摜��o�^
//		@param  fileVramType    :	�o�^VRAM�^�C�v
//		@param  fileName		:	�摜��
//		@param  fileArchiveType :	�A�[�J�C�u�̓o�^�t�@�C��INDEX
//		@param  fileIndex		:	�摜�t�@�C���ԍ�
//		@param  fileAttrType    :	�摜�o�^���� [ ENUM_GPFILE_MAX �` ]
//                                  
//	@return		0		-> ����
//				0�ȊO	-> �G���[
//
//  @comment    ���摜�f�[�^�̓o�^�\�ő�C���f�b�N�X��9999
//              ���o�^�݂̂œǂݍ��݂͂��Ȃ�
//
//=====================================================================================//
int		DxLib::AppVramFileManager::vramTextureFileEntry( const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE fileVramType,
													     const char*  fileName, 
													     const AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_LIST fileArchiveType,
													     const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType,
														 const AppLib::Resources::Parameter::ENUM_GRAPHIC_FILE_ENTRY_TYPE fileEntryUseType )
{
#if PROJECT_DEBUG
	// ".png"�`���̉摜���ᖳ���Ȃ�G���[
	const bool result = stringCheckExtension( fileName, "png" );
    if ( result == false ) {
        ERROR_PRINT("__ERROR__ : TextureFileEntry TextureFormatError ! [%s]\n", fileName );
		return App::ErrorCode::eRETURN_CODE_INVALID_FILEFORMAT;	
    }
    // �o�^���E���`�F�b�N
	int fileListArray = getLoadingFileSize();
    if ( fileListArray >= AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX ) {
		ERROR_PRINT("__ERROR__ : TextureFileEntry �o�^���E [%d]\n", fileListArray );
        return ( -3 );
    }
	// �Q�d�o�^�h�~�Ŋ��ɓo�^�ς݂��`�F�b�N
	const bool isFileExist = isFileEntryDoubleRegistration(fileName);
	if (isFileExist) {
		ERROR_PRINT("__ERROR__ : TextureFileEntry DoubleRegistration ! [%s]\n", fileName);
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

    // ���摜�o�^�C���f�b�N�X�͉摜�t�@�C���̓��̕����𔲂��o���Đݒ�
    const int entryFileIndex = getSetupFileNameEntryIndex( fileName );
#if PROJECT_DEBUG
    // �摜�t�@�C���̓o�^�C���f�b�N�X�͈̓`�F�b�N
    if( entryFileIndex >= (AppLib::Resources::Parameter::EntryIndex::ENUM_RESOURCES_FILE_ENTRY_INDEX_MAX) ){
		ERROR_PRINT("__ERROR__ : TextureFileEntry entryFileIndex Over\n" );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    // �V�K�o�^
	// ��C++11�ȍ~�ł� auto_ptr<T>�̎g�p�͔񐄏�
	// [ unique_ptr�Ƃ� ]
	// unique_ptr<T>�́A���郁�����ɑ΂��鏊�L�������|�C���^���A������ł��邱�Ƃ�ۏ؂���悤�ȃX�}�[�g�|�C���^�ł���B 
	// auto_ptr<T>���l�ɁA�e���v���[�g�����ŕێ�����|�C���^�^���w�肵�A
	// �X�}�[�g�|�C���^���j�������ۂɃf�B�X�g���N�^�ɂ����Ď����I�Ƀ��������J������
	// ���������̏��L�������� unique_ptr<T>�́A ������̂�
	// ���z����������Ƃ��ł���
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	std::unique_ptr<DxLib::ResourcesLoadContainer>  setupFileData = std::make_unique<DxLib::ResourcesLoadContainer>();

    // �o�^���ɏ��ݒ肳���f�[�^
    {
		setupFileData->m_vLoadVramType		= fileVramType;
		setupFileData->m_vLoadTextureName	= fileName;
        setupFileData->m_vFileIndex			= entryFileIndex;
		setupFileData->m_vFileAttribute		= fileAttrType;
		setupFileData->m_vFileArchIndex		= fileArchiveType;
		setupFileData->m_vFileEntryUseType	= fileEntryUseType;
    }
    // �ǂݍ��ݎ��ɏ��ݒ肳���f�[�^
    {
		setupFileData->m_vLoadFileHandle	 = AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;
		setupFileData->m_vFileStatus		 = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_ENTRYCLEAR;
		setupFileData->m_vTextureObj.m_RenderW = 0;
		setupFileData->m_vTextureObj.m_RenderH = 0;
    }

	// �ݒ肵�������N���X�Ɋi�[
	m_resourcesContainer.push_back( *setupFileData );

#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    m_LoadedFiles ++;

	DEBUG_PRINT("[VramFile] m_vTextureName:[\"%s\"] m_vFileIndex:[%d]\n", fileName,entryFileIndex );
    DEBUG_PRINT("[VramFile] m_LoadedFiles : %d\n", m_LoadedFiles );
/*
	std::string print1 = UtilityForOperat::getReplaceTextValue( "�l�i��%value%�~�ł��B", 19800, true );
	std::string print2 = UtilityForOperat::getReplaceText( "�l�i��%text%�~�ł��B", "29800", false );
	DEBUG_PRINT("[TEST] getReplaceTextValue:[\"%s\"] \n", print1.c_str());
	DEBUG_PRINT("[TEST] getReplaceText:[\"%s\"] \n", print2.c_str());
*/
    // �o�^����
    return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=====================================================================================//
//  �O���t�B�b�N�摜�f�[�^�t�@�C���P�̓ǂݍ��݃������A�b�v
//		@param		fileName		:	�摜�t�@�C����
//		@param		fileUpmode		:	�t�@�C��UP���[�h
//		@param		fileCheckNum	:	
//	<<�߂�l>>
//		���� -> 0
//=====================================================================================//
int		DxLib::AppVramFileManager::vramTextureFileSingleUpload( const char * fileName, 
                                                                const int fileUpmode, 
                                                                int fileCheckNum )
{
    int i = 0;
	int uploadResult = -1;
    
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }

    // �܂��ǂݍ��ݏo���邩�H
    const int dataArray = getLoadingFileSize();
    if ( dataArray >= AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX ) {
		ERROR_PRINT("__ERROR__ : LoadingFileSize dataArray Over\n");
        return App::FileVram::eRESULT_CODE_ERROR_NOARRAY;
    }

    // ���ɓǂݍ��ݍς݂��H
	const bool isFileStatus = isFileLoadDoubleRegistration( fileName );
    if ( isFileStatus ) {
		ERROR_PRINT("__ERROR__ : LoadingFileSize DoubleLoading Over\n");
        return App::FileVram::eRESULT_CODE_ERROR_DOUBLE_LOADING;
    }
 #endif

    {
        switch( fileUpmode )
		{
		//----------------------------------------------------------------//
		// �ʏ�( �J�E���g�𑫂��Ă���1�ɂȂ����烁�����ɃA�b�v )
		//----------------------------------------------------------------//
		case	AppLib::Resources::ProcessStatus::eUPMODE_NORMAL:
			{
			}
			break;
		//----------------------------------------------------------------//
		// VRAM�ɏ���ĂȂ�������A�b�v���������Ă���Ȃ������
		//----------------------------------------------------------------//
		case	AppLib::Resources::ProcessStatus::eUPMODE_ONE:
			{
			}
			break;
		//----------------------------------------------------------------//
		// ��ŕ��A�������������Ă邩��Ƃ��ɉ�������
		//----------------------------------------------------------------//
		case	AppLib::Resources::ProcessStatus::eUPMODE_RETURN:
			{
			}
			break;
		default:
			break;
		}

		// �ǂݍ������Ƃ��Ă�t�@�C����񂪓o�^����Ă���Ȃ烍�[�h
        const bool isFileEntry = false;
        DxLib::ResourcesLoadContainer * pResources = getContainer( fileName );
        if ( pResources )
        {
#if PROJECT_DEBUG
            // �o�^����Ă��邩
			if ( pResources->m_vFileStatus != AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_ENTRYCLEAR ) {
				ERROR_PRINT("__ERROR__ : LoadingFileSize FileStatus NoEntry. [\"%s\"]\n", fileName );
				return App::FileVram::eRESULT_CODE_ERROR_DOUBLE_LOADING;
			}
#endif
            // �e�N�X�`���̃������ւ̃��[�h
            uploadResult = vramTextureLoad( pResources );
#if PROJECT_DEBUG
            if ( uploadResult == App::FileProcess::eFILE_RESULT_CODE_ERROR ) {
                return App::FileVram::eRESULT_CODE_ERROR_LOADFAILED;
            }
#endif

			DEBUG_PRINT("[VramFile] TextureLoad Success OK. [\"%s\"]\n", fileName );
			return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
        }
    }

	DEBUG_PRINT("[VramFile] FileSingleUpload Error. : [\"%s\"]\n", fileName );
    return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

//=====================================================================================//
//  �w�葮���̉摜�t�@�C����S�ă������A�b�v
//		@param		fileVramType	:	
//		@param		fileAttrType	:	�摜�t�@�C���o�^����
//		@param		fileUpmode		:	�t�@�C��UP���[�h
//		@param		fileCheckNum	:	
//	<<�߂�l>>
//		���� -> 
//=====================================================================================//
int		DxLib::AppVramFileManager::vramSpecificAttributeFilesAllUpload( const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE fileVramType, 
                                                                        const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType, 
                                                                        const int fileUpmode, 
                                                                        int fileCheckNum )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif
	const int  fileLength = getLoadingFileSize();
    auto fileResult = 0;
    int  i;

    // �S�����S�ăA�b�v���H
    if( fileAttrType == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_ALL )
    {
        // COMMENT�F�S�����w��̎��͑S�ăA�b�v����
		for( i = 0; i < fileLength; ++ i )
		{
			// ���ɃA�b�v���[�h�ς݂Ȃ牽�����Ȃ�
            if ( isFileLoadDoubleRegistration( m_resourcesContainer[i].m_vLoadTextureName.c_str() ) ) { continue; }

            fileResult = vramTextureFileSingleUpload( m_resourcesContainer[i].m_vLoadTextureName.c_str(), 
                                                      fileUpmode,
                                                      fileCheckNum );
		}
    }
    else
    {
        if( fileVramType == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM )
        {
            for( i = 0; i < fileLength; ++ i )
            {
                // ���葮���̃A�b�v
                if( m_resourcesContainer[i].m_vFileAttribute == fileAttrType )
                {
                    // ���ɃA�b�v���[�h�ς݂Ȃ牽�����Ȃ�
                    if ( isFileLoadDoubleRegistration( m_resourcesContainer[i].m_vLoadTextureName.c_str()) ) { continue; }
                    // �O���t�B�b�N�摜�f�[�^�P�̃A�b�v
                    fileResult = vramTextureFileSingleUpload( m_resourcesContainer[i].m_vLoadTextureName.c_str(), 
                                                              fileUpmode,
                                                              fileCheckNum );
                }
            }
        }
		else if ( fileVramType == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY )
		{
		}
		else
        {
            return App::FileProcess::eFILE_RESULT_CODE_ERROR;
        }
    }
    return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

// �Q�d�o�^�h�~�Ŋ��ɓo�^�ς݂��`�F�b�N
bool    DxLib::AppVramFileManager::isFileEntryDoubleRegistration( const char* fileName/*, const int fileIndex*/ )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return false; }
#endif

    // �v�f�̒����������������
	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr = m_resourcesContainer.begin();
	for ( ; itr != m_resourcesContainer.end(); ++ itr )
	{
		if( ( strcmp( itr->m_vLoadTextureName.c_str(), fileName ) == 0 ) /*&& itr->m_vFileIndex == fileIndex*/  )
		{
			if ( itr->m_vFileStatus == AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_ENTRYCLEAR )
			{
				return true; // �o�^�ς�
			}
		}
	}
    
    return false;
}
bool	DxLib::AppVramFileManager::isFileEntryIndexDoubleRegistration( /*const char* fileName,*/ const int fileIndex )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return false; }
#endif
 /*
	std::vector<int> dataList(
	auto fileList = std::find( m_resourcesContainer.begin(), m_resourcesContainer.end(), fileIndex );
    if ( fileList == m_resourcesContainer.end() ) {
    }
*/
	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr = m_resourcesContainer.begin();
	for ( ; itr != m_resourcesContainer.end(); ++ itr )
	{
		if ( itr != m_resourcesContainer.end() ) 
		{
			if ( itr->m_vFileIndex == fileIndex )
			{
				if ( itr->m_vFileStatus == AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_ENTRYCLEAR )
				{
					return true; // �o�^�ς�
				}
			}
		}
	}
    return false;
}

// �Q�d�ǂݍ��ݖh�~�Ŋ��ɓǂݍ��ݍς݂��`�F�b�N
bool	DxLib::AppVramFileManager::isFileLoadDoubleRegistration( const char* fileName )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return false; }
#endif

	// �v�f�̒����������������
	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr = m_resourcesContainer.begin();
	for ( ; itr != m_resourcesContainer.end(); ++ itr )
	{
		if( ( strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0 )/* && (itr)->m_vFileIndex == fileIndex*/ )
		{
            // �t�@�C���n���h���Ə����t���O�����`�F�b�N����
            if ( ((itr)->m_vLoadFileHandle != AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE) && 
                 ((itr)->m_vFileStatus == AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_VRAMLOADING) )
            {
			    return true; // �ǂݍ��ݍς�
            }
		}
	}
    return false;
}

//=====================================================================================//
//	�L��(�ǂݍ��ݒ�)�O���t�B�b�N�n���h���̐����擾����
int		DxLib::AppVramFileManager::getVramFileValiditLoadHandle()
{
	const int effectiveHandles = DxLib::GetGraphNum();
#if PROJECT_DEBUG
	if( effectiveHandles < 0 ){
		ERROR_PRINT("__ERROR__ : NonFileHandle getVramFileValiditLoadHandle()\n");
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	return ( effectiveHandles );
}
int		DxLib::AppVramFileManager::getVramUpLoadedFiles()
{
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    int fileCounter = 0;
    std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr;
    for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr )
    {
        if ( itr != m_resourcesContainer.end() ) 
        {
            if( (itr)->m_vFileStatus == AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_VRAMLOADING ) {
                fileCounter ++;
            }
        }
    }
    DEBUG_PRINT("[VramFile] fileCounter : %d\n", fileCounter );
    return fileCounter;
}

//=====================================================================================//
//	�w��t�@�C���C���f�b�N�X���v�f�R���e�i�̉��Ԗڂɓo�^����Ă��邩�̃C���f�b�N�X���擾
int		DxLib::AppVramFileManager::getVramFileElementEntryIndex( const char* fileName, bool isLoadFile )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    // �v�f�̒����������������
    int index = 0;
	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr = m_resourcesContainer.begin();
    for ( ; itr != m_resourcesContainer.end(); ++ itr, ++ index )
	{
		if ( (strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0) )
		{
			return index;
		}
	}
    return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

//=====================================================================================//
//	�t�@�C��������o�^�C���f�b�N�X���擾�i�o�^�ς݂Ȃ�j
int		DxLib::AppVramFileManager::getVramFileParameterIndex( const char* fileName, bool isLoadFile )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    // �v�f�̒����������������
	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr = m_resourcesContainer.begin();
    for ( ; itr != m_resourcesContainer.end(); ++ itr )
    {
        if ( (strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0) )
        {
            return (itr)->m_vFileIndex;
        }
    }
    return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

//=====================================================================================//
//	�t�@�C�������烍�[�h�n���h�����擾
int		DxLib::AppVramFileManager::getVramFileParameterLoadHandle( const char* fileName, bool isLoadFile )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr;
    for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr ) {
        if ( itr != m_resourcesContainer.end() ) {
            // ���O����v���邩
            if( strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0 ) {
                // (gpVramFileVramLoad)���Ă΂�Ă��邩���ׂ�
                if( (itr)->m_vFileStatus == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED ) {
                    // ���݂���΃��[�h�n���h����Ԃ�
                    return (itr)->m_vLoadFileHandle;
                }
            }
        }
    }
    ERROR_PRINT("__ERROR__ : gpVramLoadFileHandleGet [\"%s\"]\n", fileName );
	// �w�肵�����O����������
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//=====================================================================================//
//	�t�@�C��������A�[�J�C�u�ݒ���擾
int		DxLib::AppVramFileManager::getVramFileParameterArchiveType( const char* fileName, bool isLoadFile )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr;
    for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr ) {
        if ( itr != m_resourcesContainer.end() ) {
            // ���O����v���邩
            if( strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0 ) {
                // �o�^����Ă��邩
                if( isFileEntryDoubleRegistration( (itr)->m_vLoadTextureName.c_str()) )
                {
                    // ���݂���΃A�[�J�C�u�ݒ��Ԃ��i���󂯎�鑤��ENUM_ARCHIVE_FILETYPE_LIST�ɃL���X�g����j
                    return (itr)->m_vFileArchIndex;
                }
            }
        }
    }
    ERROR_PRINT("__ERROR__ : gpVramLoadFileHandleGet [\"%s\"]\n", fileName );
	// �w�肵�����O����������
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//=====================================================================================//
//	�w�葮���^�C�v�̃������ɏオ���Ă���ǂݍ��ݏ�ԃt�@�C�������擾
int		DxLib::AppVramFileManager::getSpecificAttributeLoadFiles( const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttribute, bool isLoadFile )
{
#if PROJECT_DEBUG
	// Container����
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    int fileCounter = 0;
    std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr;
    for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr )
    {
        if ( itr != m_resourcesContainer.end() ) 
        {
            if( (itr)->m_vFileAttribute == fileAttribute )
            {
                if( (itr)->m_vFileStatus == AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_LOADING ) 
                {
                    fileCounter ++;
                }
            }
        }
    }
	DEBUG_PRINT("[VramFile] SpecificAttributeLoadFiles : [%d]\n", fileCounter );
    // �P���Y���f�[�^��������΂O���Ԃ�
	return ( fileCounter );
}

//=====================================================================================//
//	�w��e�N�X�`���o�^�����폜����
//	���K��VRAM����e�N�X�`���폜���̂݌Ăԗl��
//	@param		char * clearTexture		:	�摜�t�@�C���l�[��
//	@return		0 -> ����
//             -1 -> ���s
//=====================================================================================//
int		DxLib::AppVramFileManager::vramContainerDataClear( const char* clearTexture )
{
	int index = 0;
	std::vector< DxLib::ResourcesLoadContainer>::iterator itr;
	for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr, ++ index )
	{
		if ( itr != m_resourcesContainer.end() )
		{
			if( strcmp( itr->m_vLoadTextureName.c_str(), clearTexture ) == 0 )
			{
				// �w��v�f�폜
				itr->m_vLoadVramType = AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM;
				itr->m_vFileArchIndex = AppLib::Resources::Archive::eARCHIVE_FILETYPE_NONE;
				itr->m_vFileIndex = 0;
				itr->m_vFileAttribute = AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MAIN;
				itr->m_vFileEntryUseType = AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_NONE;
				itr->m_vLoadFileHandle = AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;
				itr->m_vFileStatus = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_NOUSE;
				itr->m_vTextureObj.m_RenderW = 0;
				itr->m_vTextureObj.m_RenderH = 0;

				m_resourcesContainer.erase( m_resourcesContainer.begin() + index );

				DEBUG_PRINT("[VramFile] ContainerDataClear : [%d]\n", index );

				return ( App::FileVram::eRESULT_CODE_SUCCESS );
			}
		}
	}
	ERROR_PRINT("__ERROR__ : vramContainerDataClear [\"%s\"]\n", clearTexture );
	return ( App::FileVram::eRESULT_CODE_ERROR_RELEASEFAILED );
}

//=====================================================================================//
//	�w��t�@�C���n���h���̓o�^�����폜����
//	���K��VRAM����e�N�X�`���폜���̂݌Ăԗl��
//	@param		int clearHandle		:	�摜�t�@�C���n���h��
//	@return		0 -> ����
//             -1 -> ���s
//=====================================================================================//
int		DxLib::AppVramFileManager::vramContainerDataClear( const int clearHandle )
{
	int index = 0;
	std::vector< DxLib::ResourcesLoadContainer>::iterator itr;
	for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr, ++ index )
	{
		if ( itr != m_resourcesContainer.end() )
		{
			if ( itr->m_vLoadFileHandle == clearHandle )
			{
                // �w��v�f�폜
				itr->m_vLoadVramType = AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM;
				itr->m_vFileArchIndex = AppLib::Resources::Archive::eARCHIVE_FILETYPE_NONE;
				itr->m_vFileIndex = 0;
				itr->m_vFileAttribute = AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MAIN;
				itr->m_vFileEntryUseType = AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_NONE;
				itr->m_vLoadFileHandle = AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;
				itr->m_vFileStatus = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_NOUSE;
				itr->m_vTextureObj.m_RenderW = 0;
				itr->m_vTextureObj.m_RenderH = 0;

				m_resourcesContainer.erase( m_resourcesContainer.begin() + index );

                DEBUG_PRINT("[VramFile] ContainerDataClear : [%d]\n", index );

				return ( App::FileVram::eRESULT_CODE_SUCCESS );
			}
		}
	}

	ERROR_PRINT("__ERROR__ : vramContainerDataClear [%d]\n", clearHandle );
	return ( App::FileVram::eRESULT_CODE_ERROR_RELEASEFAILED );
}

//=====================================================================================//
//	
//	@return		0 -> ����
int		DxLib::AppVramFileManager::vramContainerDataClearALL()
{
    // �̈�̉���i���g����ɂ��邾������Ȃ����������������j
	m_resourcesContainer.shrink_to_fit();
#if 0
     for ( std::vector< DxLib::ResourcesLoadContainer>::const_iterator i = m_resourcesContainer.begin (); i != m_resourcesContainer.end (); i ++ )
     {
     }
#endif
    return ( App::FileVram::eRESULT_CODE_SUCCESS );
}

//=====================================================================================//
//	�o�^->�ǂݍ��݂܂ňꊇ�ōs��
//	��FileEntry��Upload��A���ŌĂ�ł������������ʂȂ̂ł܂Ƃ߂�
int		DxLib::AppVramFileManager::vramTextureExecutionRelatedProcesses(
												const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE	 fileVramType,
												const char* fileName,
												const AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_LIST		 fileArchiveType,
												const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType,
												const AppLib::Resources::Parameter::ENUM_GRAPHIC_FILE_ENTRY_TYPE	 fileEntryUseType,
												const int	fileUpmode )
{
	int  result = -1;
	// �o�^
	result = vramTextureFileEntry( fileVramType,fileName,fileArchiveType,fileAttrType,fileEntryUseType );
	if ( result == App::FileProcess::eFILE_RESULT_CODE_SUCCESS )
	{
		// �ǂݍ���
		result = vramTextureFileSingleUpload( fileName, fileUpmode );

		return (App::FileVram::eRESULT_CODE_SUCCESS);
	}
	return (App::FileVram::eRESULT_CODE_ERROR_FAILED);
}


//=====================================================================================//
//	�摜�t�@�C�������瓪�ɐݒ肳��Ă���o�^�C���f�b�N�X�l���擾����
//	��100_Texture.png�Ȃ�100��Ԃ�
int		DxLib::AppVramFileManager::getSetupFileNameEntryIndex( const char* checkFile )
{
    int configFileIndex = -1;

    std::string setupFile = checkFile;
    const size_t strofIndex = setupFile.find_first_of('_');
	// 0�Ԗڂ���w�萔��������𔲂��o��
    std::string setupFileStr = setupFile.substr( 0, strofIndex );

    configFileIndex = std::stoi( setupFileStr );

    DEBUG_PRINT("[VramFile] configEntryFileIndex : [%d]\n", configFileIndex );

    return configFileIndex;
}


