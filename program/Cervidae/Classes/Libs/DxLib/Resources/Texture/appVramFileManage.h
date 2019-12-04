#pragma once

//===================================================================//
//
//
//
//===================================================================//

#include "appResourcesLoadContainer.h"
#include "appFileSystem.h"

/**
 *	@class ���\�[�X�t�@�C���̃}�l�[�W���[�N���X
 */
namespace DxLib
{
	class AppVramFileManager : public AppFileSystem
	{
	public:
		AppVramFileManager();
		virtual ~AppVramFileManager();

	public:

		// �f�[�^�Ǘ��R���e�i
		std::vector< DxLib::ResourcesLoadContainer>		m_resourcesContainer;

		// �ǂݍ��ݐ��Ǘ�
		int		m_LoadedFiles;
		int		m_EnteredFiles;
			
	public:

		// �Ǘ��V�X�e����{������
		bool	vramFileSystemInit();

		// �Ǘ��V�X�e���I������
		bool	vramFileSystemExit();

		// �t�@�C���������A�b�v���[�h
		int		vramTextureLoad( /*const char * loadFileName, */DxLib::ResourcesLoadContainer * pfileContainer );

		// �O���t�B�b�N�t�@�C���̓o�^(�o�^VRAM�^�C�v,�摜��,�o�^�t�@�C��INDEX,�摜�t�@�C���ԍ�,�摜�o�^����)
		// ���o�^�݂̂œǂݍ��݂͍s��Ȃ�
		int		vramTextureFileEntry( const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE fileVramType,
									  const char* fileName, 
									  const AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_LIST fileArchiveType,
									  const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType,
									  const AppLib::Resources::Parameter::ENUM_GRAPHIC_FILE_ENTRY_TYPE fileEntryUseType );

		// �O���t�B�b�N�摜�f�[�^����t�@�C���P�̓ǂݍ��݃������A�b�v
		int		vramTextureFileSingleUpload( const char* fileName, 
											 const int fileUpmode = AppLib::Resources::ProcessStatus::eUPMODE_NORMAL, 
											 int fileCheckNum = 1 );

		// �w�葮���̉摜�t�@�C����S�ă������A�b�v
		int		vramSpecificAttributeFilesAllUpload( const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE fileVramType,
													 const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType,
													 const int fileUpmode = AppLib::Resources::ProcessStatus::eUPMODE_NORMAL,
													 int fileCheckNum = 1 );

		// �Q�d�o�^�h�~�Ŋ��ɓo�^�ς݂��`�F�b�N
		bool	isFileEntryDoubleRegistration( const char* fileName/*, const int fileIndex*/ );
		bool	isFileEntryIndexDoubleRegistration( /*const char * fileName,*/ const int fileIndex );

		// �Q�d�ǂݍ��ݖh�~�Ŋ��ɓǂݍ��ݍς݂��`�F�b�N
		bool	isFileLoadDoubleRegistration( const char* fileName/*, const int fileIndex*/ );

		// �L��(�ǂݍ��ݒ�)�O���t�B�b�N�n���h���̐����擾����
		int		getVramFileValiditLoadHandle();
		int		getVramUpLoadedFiles();

		// �w��t�@�C���C���f�b�N�X���v�f�R���e�i�̉��Ԗڂɓo�^����Ă��邩�̃C���f�b�N�X���擾
		int		getVramFileElementEntryIndex( const char* fileName, bool isLoadFile = false );

		// �t�@�C��������o�^�C���f�b�N�X���擾�i�o�^�ς݂Ȃ�j
		int		getVramFileParameterIndex( const char* fileName, bool isLoadFile = false );

		// �t�@�C�������烍�[�h�n���h�����擾
		int		getVramFileParameterLoadHandle( const char* fileName, bool isLoadFile = false );

		// �t�@�C��������A�[�J�C�u�ݒ���擾
		int		getVramFileParameterArchiveType( const char* fileName, bool isLoadFile = false );

		// �w�葮���^�C�v�̃������ɏオ���Ă���ǂݍ��ݏ�ԃt�@�C�������擾
		int		getSpecificAttributeLoadFiles( const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttribute, 
											   bool isLoadFile = false );

		// �w��e�N�X�`���o�^�����폜����
		int		vramContainerDataClear( const char* clearTexture );
		// �w��t�@�C���n���h���̓o�^�����폜����
		int		vramContainerDataClear( const int clearHandle );
		int		vramContainerDataClearALL();

		// �o�^�A�ǂݍ��݂���C�ɍs���p
		int		vramTextureExecutionRelatedProcesses( 
									const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE	 fileVramType,
									const char* fileName, 
									const AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_LIST		 fileArchiveType,
									const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType,
									const AppLib::Resources::Parameter::ENUM_GRAPHIC_FILE_ENTRY_TYPE	 fileEntryUseType,
									const int	fileUpmode = AppLib::Resources::ProcessStatus::eUPMODE_NORMAL );

		
	public:

		DxLib::ResourcesLoadContainer *	getContainer( const char* fileName );
		DxLib::ResourcesLoadContainer * getElementRecordContainer( size_t index ) { return &m_resourcesContainer.at( index ); }
		
		// �e�N�X�`���T�C�Y�擾
		const ObjectSize	getTextureObjSize( const char* fileName ) { getContainer( fileName )->m_vTextureObj; }

		// �ǂݍ��ݐ���Ԃ�
		int		getLoadingFileCount() const { return m_LoadedFiles; }
		int		getLoadingFileSize() const { return static_cast<int>( m_resourcesContainer.size() ); }

	private:
		// �摜�t�@�C�������瓪�ɐݒ肳��Ă���o�^�C���f�b�N�X�l���擾����
		int		getSetupFileNameEntryIndex( const char * checkFile );
	};
}
#if 0
	class AppVramManager
	{
	public:
		AppVramManager();
		~AppVramManager();

	public:

		// �S�̂̃e�N�X�`���ǂݍ��ݐ�
		int					vp_LoadCount;
		// �����`�F�b�N
		std::vector< int >	vp_CheckSet;

	public:

		void	vfileInit();

	};
#endif


/* End appVramFileManage.h */


