
#pragma once

#include "../appFileSystem.h"

//===================================================================//
//
//
//
//===================================================================//


/**
 *	@class DX���C�u���� �A�[�J�C�u�t�@�C���ǂݍ���
 */ 
namespace DxLib
{
	class AppArchiveController : public AppFileSystem
	{
	public:
		AppArchiveController();
		virtual	~AppArchiveController();
	
	public:
		int						m_LoadCounter;
		std::vector< int >		m_ArchiveType;
//		std::array< int, AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_MAX >	m_ArchiveTypeList;

		std::map< int, std::string >							m_ArchiveFile;
		std::map< int, std::map< std::string, std::string >>	m_ArchiveData;
	
	public:
		// �c�w�A�[�J�C�u�t�@�C��
		char *	libArchiveFileNameCheck( const int nArchIndex );

		// �c�w�A�[�J�C�u�t�@�C���̊g���q��ύX����
		int		libArchiveFileExtensChange( char * arcFileName );

		// �c�w�A�[�J�C�u�t�@�C���̃p�X���[�h��ݒ�
		int		libArchiveFilePassSet( char * filePassCode );

		// �c�w�A�[�J�C�u�t�@�C���ƃt�H���_�����݂����ꍇ�̗D��x�ݒ�( 1:�t�H���_��D��@ 0:�c�w�A�[�J�C�u�t�@�C����D��( �f�t�H���g ) )
		int		libArchiveFileLoaderPrioritySetting( const int  nLoadPriority = AppLib::Resources::Archive::ARCHIVE_FILE_LOADER_PRI_ARCHIVE );

		// �w��̂c�w�`�t�@�C�����ۂ��ƃ������ɓǂݍ���( �߂�l  -1:�G���[  0:���� )
		int		libArchiveFileMemLoad( char * arcFileName, const int  nArchIndex, const int  nASyncLoad = false );
		int		libArchiveFileMemLoader( char * arcFileName, const int  nArchIndex );

		// �w��̂c�w�`�t�@�C���̎��O�ǂݍ��݂������������ǂ������擾����( �߂�l  TRUE:�������� FALSE:�܂� )
		bool	libisArchiveFileLoadIdle( char * arcFileName, const int  nArchIndex = -1 );

		// �w��̂c�w�`�t�@�C��������������������
		int		libArchiveFileMemFree( char * arcFileName, const int  nArchIndex = -1 );
	
		// �p�b�N�����c�w�`�t�@�C���̒��Ɏw��̃t�@�C�������݂��邩�ǂ����𒲂ׂ�
		int		libArchiveFileDirectoryCheck( char * arcFileName, int  nArchIndex, char * szArchTargetFile );
	
	
	};
}

/* End appArchiveFileControl.h */