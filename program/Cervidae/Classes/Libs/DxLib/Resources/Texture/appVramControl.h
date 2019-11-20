
#pragma once

///////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////

#include "appFileSystem.h"
#include "appVramContainer.h"

/**
 *	@class ���\�[�X�t�@�C���̓ǂݍ��݁A�폜�Ǘ��Ɏg�p������
 */
namespace DxLib
{
	class AppVramController : public AppFileSystem
	{
	public:

		AppVramController();
		virtual ~AppVramController();

	public:

		std::vector< VramFileContainer >	m_FileContainer;
	//	std::vector< VramFileContainer* >	m_FileContainer;

	public:

		// VRAM�Ǘ��V�X�e����{����������
		bool	gpVramFileSystemInit();

		// VRAM�Ǘ��V�X�e���I������
		void	gpVramFileSystemExit();
		
		// VRAM�Ǘ��V�X�e�������^�C��
		void	gpVramFileRuntime();

		// �O���t�B�b�N�t�@�C���̃������ւ̃��[�h
		int		gpVramFileVramLoad( const int archive_type, const char* vvfile_name, int  vvram_type );

		// �w��̃O���t�B�b�N���������ォ��폜����
		int		gpVramBuffLoadFileFormat( const int vram_type, char* vvfile_name );

		// ���n���h���w��֐��ł�vector�\���폜�N���A�͂���Ȃ��̂Œ��ڌĂԂ̂͋֎~��
		int		gpVramBuffLoadFileFormat( const int file_handle );

		// �������ɂ���摜��S�č폜
		int		gpVramLoadBuffFormatALL();

		// �������ɂ���w��O���t�B�b�N�̃T�C�Y�𓾂�
		int		gpVramLoadFileGetSize( const int vram_type, char* vvfile_name, int* pFileRectW, int* pFileRectH );
		int		gpVramLoadFileGetSize( const int file_handle, int* pFileRectW, int* pFileRectH );

		// ���O����VRAM�t�@�C���n���h�����擾
		int		gpVramLoadFileHandleGet( const char* vvfile_name );

		// ���O����f�[�^INDEX���擾
		int		gpVramGetDataIndex( char* vvfile_name );
		int		gpVramGetDataIndex( const int file_handle );

		// �w��t�@�C����VRAM�^�C�v�ݒ���擾
		int		gpVramGetVVramType( const char* vvfile_name );

		// �w��t�@�C���n���h���̔z��o�^�����폜����
		int		gpVramEntryDataClear( const char* vvfile_name );
		// �w��t�@�C���l�[���̔z��o�^�����폜����
		int		gpVramEntryDataClear( const int file_handle );
		int		gpVramEntryDataClearALL();

		// �󂫔ԍ���T��(���폜����ċ󂫂��o�����C���f�b�N�X��T��)
		int		gpVramGetNotUseListIndex();

	};
}




 /* End appVramControl.h */





