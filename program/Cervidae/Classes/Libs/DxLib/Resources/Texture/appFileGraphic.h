
#pragma once

///////////////////////////////////////////////////////////////////////////
//
//	�O���t�B�b�N�t�@�C���Ǘ��V�X�e��
//
//	appFileGraphic
///////////////////////////////////////////////////////////////////////////

#include "appVramControl.h"

/**
 *	@class ���\�[�X�t�@�C���̓o�^�Ɏg�p������
 */
namespace DxLib
{
	/**
	 * 
	 */
	class GraphicFileContainer
	{
	public:
		GraphicFileContainer() {
			gp_FileCount = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_NOUSE;
			gp_FileArch = 0;
			gp_FileNum = -1;
			gp_FileAttr = 0;
			gp_FileID = -3;
			gp_FileHandle = AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;
			gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_NOUSE;
		}
		~GraphicFileContainer() {
		}

	public:

		int				gp_FileCount;		// �g�p�J�E���g�F�ǂݍ��ݏ��(-1:��������)
		int				gp_FileArch;		// �t�@�C���A�[�J�C�uINDEX
		int				gp_FileNum;			// �t�@�C���̎w��ԍ�
		std::string		gp_FileName;		// �摜�e�N�X�`���l�[��
		int				gp_FileAttr;		// �t�@�C���̓o�^����
		int				gp_FileID;			// �摜�t�@�C���C���f�b�N�X
		int				gp_FileHandle;		// �摜�e�N�X�`�����[�h�n���h���i�[�p
		int				gp_LoadingFlag;		// �ǂݍ��ݏ����ŌĂ΂ꂽ���̂�

		int				gp_TexWidth;		// �e�N�X�`���T�C�YWidth
		int				gp_TexHeight;		// �e�N�X�`���T�C�YHeight
		int				gp_ProcessStatus;	// 
	};


	/**
	 *
	 */
	class AppFileGraphicManager : public AppVramController
	{
	public:
		AppFileGraphicManager();
		virtual ~AppFileGraphicManager();

	public:
		// ���[�h�ł��鐔�����߂ĊǗ�
		std::array< 
				DxLib::GraphicFileContainer, 
				AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX >	m_graphicContainer;

		bool	isProcessClear;

	public:

		AppFileGraphicManager * 	createInstance();

		// �Ǘ��V�X�e����{������
		bool	_graphicSystemInit();

		// �Ǘ��V�X�e���I������
		bool	_graphicSystemExit();

		// �摜�^�C�v�Ɖ摜������G�̓o�^�ԍ���Ԃ�
		int		_graphicVramFileIdBackNumCheck( const int  gp_type, const char* gp_name );

		// �^�C�v�Ɩ��O����O���t�B�b�N�̃��[�h�n���h�����擾
		int		_getGraphicTexVramLoadHandle( const int  gp_type, const char* gp_name );

		// �L��(�ǂݍ��ݒ�)�O���t�B�b�N�n���h���̐����擾����
		int		_getGraphicValiditLoadHandle();

		// �������ւ̃O���t�B�b�N���[�h�\�ő吔���擾
		int		_graphicVramFileMaxCheck( const int  gp_type, int* gp_Vrammax, GraphicFileContainer** = NULL );

		// �O���t�B�b�N�o�^�����擾
		int		_graphicVramFileEntryNumCheck( const int  gp_type = AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM );

		// �O���t�B�b�N�摜�̓o�^�f�[�^���폜
		int		_graphicVramFileEntryDel( const int  gp_type, char* gp_name );

		// �O���t�B�b�N�摜��o�^(�o�^VRAM�^�C�v,�摜��,�o�^�t�@�C��INDEX,�摜�t�@�C���ԍ�,�摜�o�^����)
		int		_graphicVramTextureEntry( const int  gp_type, const char * gp_name, const int  gp_arc, const int  gp_file, const int  gp_attr );

		// �O���t�B�b�N�摜�f�[�^�t�@�C���P�̓ǂݍ��݃������A�b�v
		int		_graphicVramTexUp( const int  gp_type, char* gp_name, const int  gp_mode = AppLib::Resources::ProcessStatus::eUPMODE_NORMAL, int  check_num = 1 );
								 
		// �O���t�B�b�N�摜�f�[�^�P�̍폜
		int		_graphicVramTexDelete( const int  gp_type, char* gp_name, const int  gp_mode = AppLib::Resources::ProcessStatus::eUPMODE_NORMAL );

		// �O���t�B�b�N�摜�f�[�^��ǂݍ��݁i�������ɃA�b�v�j
		int		_graphicVramTexAttrUp( const int  gp_type, const int  gp_mode, const int  gp_attr );

		// �O���t�B�b�N�摜�f�[�^�w�葮���^�C�v�폜
		int		_graphicVramTexAttrDelete( const int  gp_type, const int  gp_mode, const int  gp_attr );

		// �O���t�B�b�N�̃��[�h�n���h�����폜
		int		_graphicVramFileFormat( const int  gp_type, GraphicFileContainer* pGpWork );

		// �w��O���t�B�b�N���������ǂݍ��݂���Ă��邩�`�F�b�N
		int		_graphicVramTexUpCheck( const int  gp_type, const char* gp_name );
		int		_graphicVramTexUpCheck( const int  gp_type, const int  gp_i );

		// �w�葮���̉摜���S�ďオ���Ă邩���ׂ�
		int		_graphicVramAttrTexUpCheck( const int  gp_Attrtype );

		// �S�����̉摜�ŏ������̉摜���L�邩���ׂ�
		int		_graphicVramAttrTexUpCheckALL();

		// �w��t�@�C���̉摜�ԍ����擾(���摜�l�[���̂ݎw��)
		int		_graphicVramTexEntryNumCheck( const char* gp_name );

		// �w��t�@�C���̉摜�ԍ����擾(���摜�^�C�v�w��t��)
		int		_graphicVramTexEntryNumCheckType( const int  gp_type, const char* gp_name );

		// �o�^ID���疼�O�摜����Ԃ�
		const char * _graphicEntryNameGet( const int  gp_type, const int  index );

		// �O���t�B�b�N�t�@�C�������^�C��
		int		_graphicVramLibRuntime();

		// 
		int		_graphicVramUpState();

		// �w��̃O���t�B�b�N�n���h���ƁA�����O���t�B�b�N�n���h������h�����Ă���
		// �O���t�B�b�N�n���h��( DerivationGraph �Ŕh�������n���h���ALoadDivGraph �ǂݍ���ō쐬���ꂽ�����̃n���h�� )����x�ɍ폜����
		int		_graphicVramSharingHandleFormat( const int  nSharHandle );

		// �摜�t�@�C���̕����ǂݍ���(�A�j���[�V�����A�ԉ摜��)
		// �������_�ł͎��O�o�^�͍s�킸���A���^�C���ǂݍ���
		int		_graphicAnimationGraphDivLoad(	const int  arch_type,
												char * gp_name, int  gpDivNum,
												int    gpDivSrcX, int  gpDivSrcY, int  gpDivSizeW, int  gpDivSizeH,
												int * pHandleBuf );

		// �摜���o�^�\����Ԃ�(�󂢂Ă���ԍ���Ԃ��ADXLIB_GRAPHIC_VRAM_WORK�̍ő啪�`�F�b�N)
		int		_graphicEntryUseIdCheck();


		/*
		 *	�ȈՉ����b�v�֐��Q
		 */

		// eFILE_GRAPHIC_SYSTEM�^�C�v�̉摜VRAM�o�^�ȈՏ���
		int		_wrapGraphicVramEntry( const int  gp_type, char* gp_name, const int  gp_file, const int  gp_attr );
		// eFILE_GRAPHIC_MEMORY�^�C�v�̉摜VRAM�o�^�ȈՏ���
		int		_wrapGraphicMemoryVramEntry( char* gp_name, const int  gp_file, const int  gp_attr );
		// �摜�̓o�^���ǂݍ��݂���C�ɍs��
		int		_wrapGraphicVramSetup( const int  gp_type, char* gp_name, const int  gp_file, const int  gp_attr );


	};
}


/* End appFileGraphic.h */

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 