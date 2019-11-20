#pragma once

///////////////////////////////////////////////////////////////////////////
//	DX���C�u���� �t�@�C���Ǘ��V�X�e��
//
//
///////////////////////////////////////////////////////////////////////////


//*******************************************************************//
/*
	define��`
*/
//*******************************************************************//


/**
 *	@class ��{���̃N���X�͌p����p�Ŋe�e�N���X�Ɍp�������Ďg�p����
 */
namespace DxLib
{
	class AppFileSystem
	{
	public:
		AppFileSystem();
		virtual	~AppFileSystem();

	public:
		typedef int	(*appLibFileCallBack) ( void *, unsigned int );

	private:
		bool	m_ASyncLoadEnable;

		std::map<int, std::string>	m_LoadList;

	public:
		// �����A�񓯊��ݒ�
		void	setASyncLoadEnable( const bool flagValue ){ m_ASyncLoadEnable = flagValue; }
		bool	getASyncLoadFlag() const { return m_ASyncLoadEnable; }

	public:

		void	fileStructureClear( void );
		// �t�@�C���A�N�Z�X�V�X�e���̊�{������
		bool	fileLoadSystemInit( void );
		
		// �t�@�C���ǂݍ���(��LoadGraph�g�p�o�[�W����)
		int		fileLoadAccess( const int  nDirIndex, const char * szFileName, appLibFileCallBack  fCallBack = nullptr );
		// �t�@�C���A�N�Z�X�p�X�̎擾
		int		fileLoadGetAccessPath( const int  nDirIndex, char * szFileName, char * szGetOutPath );
		// �X�N���v�g(.lua)�t�@�C���A�N�Z�X�p�X�̎擾
		int		fileLoadGetScriptPath( unsigned int  unFileIndex, char * szGetOutPath );
		// �t�@�C���T�C�Y���擾(���ǂݍ��݂͍s��Ȃ�)
		int		fileAccessCheckSize( const int  nDirIndex, char * szFileName );
		// �t�@�C���T�C�Y���擾�{�ǂݍ��݋@�\�t��
		int		fileCheckSizeLoadAccess( const int  nDirIndex, char * szFileName, int * resFileSize, appLibFileCallBack  fCallBack = nullptr );
		// �񓯊��ǂݍ��݂��s�����ǂ�����ݒ肷��(( TRUE�F�񓯊��ǂݍ��݁@FALSE�F�����ǂݍ���( �f�t�H���g ) )
		int		fileSetASyncLoadAccessEnable( const int  bASyncEnable = FALSE );
		// �n���h���̔񓯊��ǂݍ��݂��������Ă��邩�ǂ������擾( TRUE:�܂��������Ă��Ȃ�  FALSE:�������Ă���  -1:�G���[ )
		int		fileGetASyncLoadHandleCheck( const int  nSyLoadHandle );
		// �񓯊��ǂݍ��ݒ��̏���(�n���h��)�̐����擾����
		int		fileGetASyncLoadHandleNum( void );
		// �n���h���̔񓯊��ǂݍ��ݏ����̖߂�l���擾����
		int		fileGraphicsASyncLoadResult( const int  nHandle );
		// �A�[�J�C�u�t�@�C���ǂݍ��݃p�X�擾�Z�b�g
		int		fileLoadArchivePathCheck( const int  nArchSecIndex, char * szFileName, char * returnFile, int  _ArchFileType = 1 );
		// �t�@�C���̃������ւ̃��[�h
		int		fileMemoryRead( char * szReadFile, char * szFileName, int nDirIndex, int * pFlag = nullptr );
		// �t�@�C���ǂݍ���
		// ��FileRead_read�g�p�o�[�W����
		int		fileBufferRead( const int  nDirIndex, char * szFileName, void * pBuffer = nullptr );
		// �t�@�C���ǂݍ���
		// ��FileRead_read�g�p�o�[�W����
		// ���ǂݍ��񂾉摜�t�@�C������O���t�B�b�N�n���h�����쐬����
		int		fileBufferReadCreateHandle( const int  nDirIndex, char * szFileName, void * pBuffer = nullptr );
	
	};
}




/* End appFileSystem.h */