#pragma once

#include "DxLib.h"

///////////////////////////////////////////////////////////////////////////
//
// ���\�[�X�֌W�����X�e�[�^�X��`�ꗗ
//
//
///////////////////////////////////////////////////////////////////////////

namespace AppLib
{
	namespace Resources
	{
		// @enum �摜�t�@�C���o�^����
		namespace Attribute
		{
			typedef enum
			{
				eRESFILE_ATTRIBUTE_TYPE_ALL = -1,			// @param �S����
				eRESFILE_ATTRIBUTE_TYPE_MAIN = 0,			// @param ���̏��g��Ȃ�
				eRESFILE_ATTRIBUTE_TYPE_SYSTEM,				// @param �V�X�e���摜
				eRESFILE_ATTRIBUTE_TYPE_BACKGROUND,			// @param �w�i�摜
				eRESFILE_ATTRIBUTE_TYPE_SCRIPT,				// @param �X�N���v�g
				eRESFILE_ATTRIBUTE_TYPE_BGM,				// @param BGM
				eRESFILE_ATTRIBUTE_TYPE_VOICE,				// @param VOICE
				eRESFILE_ATTRIBUTE_TYPE_SE,					// @param SE
				eRESFILE_ATTRIBUTE_TYPE_MOVIE,				// @param MOVIE
				eRESFILE_ATTRIBUTE_TYPE_EFFECT,				// @param �G�t�F�N�g
				eRESFILE_ATTRIBUTE_TYPE_BINARY,				// @param �o�C�i���f�[�^(�A�[�J�C�u)
				eRESFILE_ATTRIBUTE_TYPE_DATABASE,			// @param �f�[�^�x�[�X(CSV)
				eRESFILE_ATTRIBUTE_TYPE_SAVEDATA,			// @param �Z�[�u�f�[�^
				eRESFILE_ATTRIBUTE_TYPE_3DMODEL,			// @param 3DModel

				ENUM_RESFILE_ATTRIBUTE_TYPE_MAX,			// �o�^�������X�g�ő�
			} ENUM_RESFILE_ATTRIBUTE_TYPE_LIST;
		}

		// @enum �A�[�J�C�u�����ݒ�
		namespace Archive
		{
			const static char * 	ARCHIVE_FILE_EXTENS = "KAF";		// �A�[�J�C�u�t�@�C���̓Ǝ��g���q
			const static char * 	ARCHIVE_FILE_PASSWORD = "PASSWORD";	// �A�[�J�C�u�t�@�C���̓ǂݍ��݃p�X���[�h

			// ���[�h�v���C�I���e�B
			const static int		ARCHIVE_FILE_LOADER_PRI_FOLDER = 1;
			const static int		ARCHIVE_FILE_LOADER_PRI_ARCHIVE = 0;

			const static int		ARCHIVE_FILE_LOADER_DXA = 1;		// �ǂݍ��ݑΏہF�A�[�J�C�u�t�@�C���{��
			const static int		ARCHIVE_FILE_LOADER_PACKFILE = 0;	// �ǂݍ��ݑΏہF�A�[�J�C�u�t�@�C���̒��̌ʃt�@�C��
			
			// @enum 
			typedef enum
			{
				eARCHIVE_FILETYPE_NONE			= 0,		//! @param	���̏��g��Ȃ�
				eARCHIVE_FILETYPE_RESOURCES		= 1,		//! @param	�V�X�e���摜(UI��)
				eARCHIVE_FILETYPE_SCRIPT		= 2,		//! @param	�X�N���v�g
				eARCHIVE_FILETYPE_BGM,						//! @param	BGM
				eARCHIVE_FILETYPE_VOICE,					//! @param	VOICE
				eARCHIVE_FILETYPE_SE,						//! @param	SE
				eARCHIVE_FILETYPE_MOVIE,					//! @param	MOVIE
				eARCHIVE_FILETYPE_EFFECT,					//! @param	�G�t�F�N�g
				eARCHIVE_FILETYPE_BINARY,					//! @param  �o�C�i���f�[�^(�A�[�J�C�u)
				eARCHIVE_FILETYPE_DATABASE,					//! @param  �f�[�^�x�[�X(CSV)
				eARCHIVE_FILETYPE_JSON,						//! @param	Json�f�[�^
				eARCHIVE_FILETYPE_SAVEDATA,					//! @param  �Z�[�u�f�[�^
				eARCHIVE_FILETYPE_MODEL,					//! @param  
				
				ENUM_ARCHIVE_FILETYPE_MAX,
				ENUM_ARCHIVE_FILELIST_MAX = eARCHIVE_FILETYPE_EFFECT + 1,

			} ENUM_ARCHIVE_FILETYPE_LIST;
		}

		namespace Info
		{
			// project�t�@�C�����猩�Ă̑��΃p�X
			const static std::string	RESOURCES_LOAD_ROOT_PATH = "../../resources/asset/";
			const static std::string	RESOURCES_SCRIPT_LOAD_ROOT_PATH = "../../resources/script/";
		}

		namespace Parameter
		{
			namespace EntryIndex
			{
				/**
				 *	@enum	�摜�t�@�C���̓o�^�C���f�b�N�X���X�g
				 */
				typedef enum
				{
					// eRESFILE_NAME_GAME_FICTION_IMAGE				= 1,		//! @param Fiction�C���[�W
					// eRESFILE_NAME_GAME_COMPANY_LOGO				= 2,		//! @param ��Ѓ��S
					// eRESFILE_NAME_GAME_COPYRIGHTIMAGE_DXLIB		= 3,		//! @param DX���C�u�������S
					// eRESFILE_NAME_GAME_COPYRIGHTIMAGE_ADX2LE		= 4,		//! @param CRI ADX2���S
					// eRESFILE_NAME_GAME_COPYRIGHTIMAGE_EFFEKSEER	= 5,		//! @param 

					// eRESFILE_NAME_GAME_TITLE_TEX_BG				= 10,		//! @param 
					// eRESFILE_NAME_GAME_TITLE_TEX_MENU_UI			= 11,		//! @param 
					// eRESFILE_NAME_GAME_TITLE_TEX_OBJECT			= 12,

					// ERROR
					eRESFILE_NAME_APP_ERROR_TEX					= 9998,		//! @param 
					// �o�^�ő�
					ENUM_RESOURCES_FILE_ENTRY_INDEX_MAX			= 9999		//! @param 

				} ENUM_RESFILE_FILE_ENTRY_INDEX_LIST;
			}

			namespace EntryType
			{
			}
			/**
			 *	@enum	�摜�t�@�C���̓o�^�^�C�v���X�g
			 */
			typedef enum 
			{
				eGRAPHIC_FILE_ENTRY_NONE	= 0,		//! @param ���ݒ�
				eGRAPHIC_FILE_ENTRY_APPSTART,			//! @param �Q�[���N����
				eGRAPHIC_FILE_ENTRY_GLOBAL,				//! @param �O���[�o��
				eGRAPHIC_FILE_ENTRY_COMMON,				//! @param �ėp
				eGRAPHIC_FILE_ENTRY_SCENE_TITLE,		//! @param �^�C�g���V�[��
				
				ENUM_GRAPHIC_FILE_ENTRY_TYPE_MAX
			} ENUM_GRAPHIC_FILE_ENTRY_TYPE;
		}

		namespace FileSystem
		{
			// �ǂݍ��݃n���h�����N�G�X�g�\��
			const static unsigned int	LOAD_FILEHANDLE_REQUEST_MAX	= ( 15 );
			// �����ǂݍ��݃��N�G�X�g�\��
			const static unsigned int	LOAD_FILE_ASYNC_REQUEST_MAX = ( 20 );

			const static int			FILE_LIB_ASYNC_LOAD_TRUE	= 1;	// �񓯊��ǂݍ���
			const static int			FILE_LIB_ASYNC_LOAD_FALSE	= 0;	// �����ǂݍ���
			
			// �t�@�C���ǂݍ��݃p�X
			const static std::string	RESOURCES_FILELOAD_DIRECTORY	= "resources";
			const static std::string	RESOURCES_FILELOAD_ROOTDIR		= "/";
			const static std::string	RESOURCES_FILELOAD_PATH			= "/resources/asset/";

			// [DUMMY]
			const static char*			RESOURCES_FILE_ROOT = "C:/ProgramBox/Project/Develop/cervidae_lib/resources/asset";

			// @enum 
			typedef enum
			{
				eDxULIBLRMs_Non		= 0,// ���g�p
				eDxULIBLRMs_Wait	= 1,// �ҋ@���i�ǂݍ��݊J�n�O�̑ҋ@�j
				eDxULIBLRMs_Init	= 2,// ���������i�ǂݍ��݊J�n�j
				eDxULIBLRMs_Load	= 3,// �ǂݍ��ݒ�
				eDxULIBLRMs_CBWait	= 4,// �R�[���o�b�N�֐����ԑ҂�
				eDxULIBLRMs_CBRun	= 5,// �R�[���o�b�N�֐����s��
				eDxULIBLRMs_End		= 6,// �ǂݍ��ݏI��
				eDxULIBLRMs_MAX
			} ENUM_DxULIBLRMs_LIST;
		}

		namespace FileVram
		{
			const static unsigned int	DEF_SYSTEMVRAMLOAD_MAX		= 15;	//! @param �e�N�X�`���t�@�C��VRAM�ǂݍ��݉\�ő吔
			const static unsigned int	DEF_MEMORYVRAMLOAD_MAX		= 10;	//! @param 
			// �������ɏグ����ő吔
			const static unsigned int	FILE_RESOURCES_VRAMUP_POSSIBLE_MAX = 20;

			typedef enum
			{
				eDEF_VVRAM_BUFFER_FLAG_NON		= 0,		// ���g�p
				eDEF_VVRAM_BUFFER_FLAG_USED		= (1 << 0),	// �g�p�ς݂̃o�b�t�@
				eDEF_VVRAM_BUFFER_FLAG_NEW		= (1 << 1),	// �V�K�o�b�t�@
				eDEF_VVRAM_BUFFER_FLAG_CLEAR	= (1 << 2),	// �o�b�t�@�N���A����

			} ENUM_VVRAM_BUFFER_FLAG;

			namespace Info
			{

			}
		}

		namespace ProcessStatus
		{
			const unsigned int		DEF_SYSTEMVRAMLOAD_MAX		= 20;	//! @param �e�N�X�`���t�@�C��VRAM�ǂݍ��݉\�ő吔
			const unsigned int		DEF_MEMORYVRAMLOAD_MAX		= 10;	//! @param 

			/*
			 *	NOTE:�O���t�B�b�N���\�[�X�̓o�^�\���ƃ��������[�h�\���͈Ⴄ
			 */
			// �e�N�X�`���t�@�C���ő�ǂݍ��ݐ�
			const static unsigned int	GPVRAM_LOADRESOURCES_MAX = ( DEF_SYSTEMVRAMLOAD_MAX );	//! @param �e�N�X�`���t�@�C��VRAM�ǂݍ��݉\�ő吔
			const static unsigned int	OBJVRAM_LOADRESOURCES_MAX = ( DEF_MEMORYVRAMLOAD_MAX );
			// �e�N�X�`���t�@�C�����ݒ�ő�
			const static unsigned int	GPVRAM_LOADTEXFILENAME = ( 64 );
			// �e�N�X�`���t�@�C���o�^�ő吔
			const static unsigned int	GPVRAM_TEXTUREENTRY_MAX = ( 30 );

			typedef enum
			{
				eFILE_GRAPHIC_SYSTEM = 0,		// �V�X�e���e�N�X�`��
				eFILE_GRAPHIC_MEMORY,			// �������i�Z�[�u���[�h�j


				ENUM_RESOURCES_VRAM_TYPE_MAX,

			} ENUM_RESOURCES_VRAM_TYPE;

			typedef enum
			{
				eVRAM_FILE_STATUS_NOUSE = -1,	// ���g�p
				eVRAM_FILE_STATUS_ENTRYCLEAR,	// �o�^����
				eVRAM_FILE_STATUS_LOADING,		// �ǂݍ��ݒ�

			} ENUM_RESOURCES_FILE_STATUS;

			typedef enum
			{
				eUPMODE_NORMAL,					// �ʏ�i�J�E���g�𑫂��Ă���1�ɂȂ����烁�����ɃA�b�v�j
				eUPMODE_ONE,					// VRAM�ɏ���ĂȂ�������A�b�v���������Ă���Ȃ������
				eUPMODE_RETURN,					// DELMODE_DIS�������̕��A�p

			} ENUM_VRAM_UPPROCESS;

			typedef enum
			{
				eDELMODE_NORMAL,				// �ʏ�i�J�E���g�������Ă���0�ɂȂ�����폜�j
				eDELMODE_COER,					// �����폜��J�E���g��0��
				eDELMODE_DIS,					// �폜���邾����J�E���g�͎c�����܂�
				eDELMODE_COERALL,				// �ⓚ���p�őS�폜

			} ENUM_VRAM_DELPROCESS;

			typedef enum
			{
				eVRAMUP_STOP = 0,				// �Ȃ�����ĂȂ�
				eVRAMUP_LOAD,					// �ǂݍ��ݑ҂�

			} ENUM_VRAM_UPRESULT;

			typedef enum
			{
				eVRAMMODE_TEXUP = 0,			// VRAN�A�b�v
				eVRAMMODE_TEXDEL,				// VRAM�폜

				ENUM_VRAM_PROCTYPE_MAX

			} ENUM_VRAM_PROCESS_TYPE;

			typedef enum
			{
				eVRAMFILE_NOENTRY = 0,			// �摜�t�@�C���o�^
				eVRAMFILE_CLEAR = -1,			// �ǂݍ��ݏ����I���F�폜
				eVRAMFILE_LOADING,				// �ǂݍ��ݏ����J�n

			} ENUM_VRAM_FILELOAD;

			typedef enum
			{
				eGPFILE_HANDLE_NONUSE = -1,		// �t�@�C���n���h���͎g�p����Ă��Ȃ�
				eGPFILE_HANDLE_VRAMLOADING,

			} ENUM_VRAM_HANDLE_STATUS;
		}

		/**
		 *	TODO:����Ǘ����@���C���\�� 2019.07.12
		 */
		const static char* ResourcesFile_Name01 = "001_File.jpg";
		const static char* ResourcesFile_Name02 = "002_File.jpg";
		const static char* ResourcesFile_Name03 = "003_File.png";
		const static char* ResourcesFile_Name04 = "004_File.jpg";


	}/* namespace Resources */
}/* namespace AppLib */


// �t�@�C������
#define DX_FILE_OPEN( fname )	FileRead_open( fname, false )
#define DX_FILE_CLOSE( h )		FileRead_close( h )
#define DX_FILE_IDOL( h )		FileRead_idle_chk( h )
#define DX_FILE_EOF( h )		FileRead_eof( h )
#define DX_FILE_READ			FileRead_read
#define DX_FILE_SIZE( fname )	FileRead_size( fname )
#define DX_FILE_GETC( h )		FileRead_getc( h )




/* End appResourcesConfig.h */


