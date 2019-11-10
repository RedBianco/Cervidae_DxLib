#pragma once


//===================================================================//
//
//
//  Created by kashima akihiro on 2019/03/09.
//===================================================================//

/*
 *	�T�E���h�X�g���[���Đ��Ǘ��N���X
 */
namespace DxLib
{
	class StreamPlayManager
	{
	public:
		StreamPlayManager();
		virtual ~StreamPlayManager();

	public:
		std::vector< App::SoundDataContainer>	m_SoundData;

		int		dxSoundEntry;		// �T�E���h�t�@�C���o�^��
		int		dxSoundReadMode;
		int		dxSoundProc;

	public:

		// MIDI�t�@�C���̍Đ����[�h�ݒ�
		void	setMidiPlayMode( const int  nMidiMode = DX_MIDIMODE_MCI );

		// ������
		bool	init();

		//------------------------------------------------------------------------------//
		//	�X�g���[���Đ�
		//	�������Ă΂��x�Ƀt�@�C����ǂݍ���Ł��Đ�
		//	�󋵂ɂ���Ă͓ǂݍ��݂Ƀ��O���o��
		//------------------------------------------------------------------------------//

		// MIDI�CWAV�C"MP3"�t�@�C�����Đ�����
		int		streamPlay( char * playFileName, const int  SoundArchive, const int  playingType = DxLibSound::BaseInfo::SOUND_STREAM_BACKGRLOOP );
		int		streamIdPlay( const int  playFileNo, const int  SoundArchive, const int  playingType = DxLibSound::BaseInfo::SOUND_STREAM_BACKGRLOOP );
		// MIDI�CWAV�C"MP3"�t�@�C���̍Đ���~
		int		streamPlayStop( void);
		// MIDI�CWAV�C"MP3"�t�@�C�����Đ������̏����擾����
		int		streamPlayState( void);
		// MIDI�CWAV�C"MP3"�t�@�C���̍Đ����ʂ�ݒ肷��(���f�t�H���g�͔���)
		int		setPlayVolumeConfig( const int  nStreamVolume = 128 );
		// MIDI�CWAV�C"MP3"�t�@�C���̃T�E���h�n���h�����g�p�����X�g���[���Đ�
		int		streamHandlePlay( const int  nHandle, const int  nPlaying, const int  bPlayPosition = TRUE );

		//------------------------------------------------------------------------------//
		//	�������Ɏ��O�ɓǂݍ��݂�ł����^�C�v
		//	��������ƃ���������������̂Œ���
		//	�������[�Ɏ��O�ǂݍ��� �� �Đ�
		//------------------------------------------------------------------------------//

		// �����t�@�C��(WAV.MP3.Ogg)���������ɓǂ݂���
		int		dxLib_SoundFileMemLoad( char * loadFileName_, const int  nSoundArchive );

		// �������̉����t�@�C�������邩�`�F�b�N(soundFileName_:�����t�@�C���l�[��)
		int		dxLib_MemSoundDataCheck( char * SysSoundFile_ );

		// ���O����o�^�n���h����T���ĕԂ�
		int		dxLib_GetMemSoundDataEntryHandle( char * SysSoundFile_ );

		// �o�^�f�[�^�ԍ��̓o�^�T�E���h�n���h�����擾
		int		dxLib_GetMemSoundDataEntryIndex( const int  nEntryIndex );

		// �������ɓǂݍ��񂾉����t�@�C��(WAV.MP3.Ogg)�̍Đ�
		int		dxLib_MemSoundPlay( char * szSoundName, const int  SoundPlay = DxLibSound::BaseInfo::SOUND_STREAM_NORMALPLAY, const int isTopPosition = TRUE );
		int		dxLib_MemSoundPlay( const int  nSoundHandle, const int  SoundPlay_ = DxLibSound::BaseInfo::SOUND_STREAM_NORMALPLAY, const int isTopPosition_ = TRUE );

		// �������ɓǂݍ��񂾃T�E���h�n���h���̍Đ����~����
		int		dxLib_MemSoundPlayStop( const int  nSoundHandle );

		/**
		 *	�V�X�e���r�d�֘A�֐��Q
		 */

		// �V�X�e���r�d�t�@�C���̃������o�^
		bool	dxLib_MemEntrySystemSound( void );
		void	dxLib_MemEntrySystemSoundReregist( void );
		void	dxLib_MemEntrySystemSoundReset( void );

		// �V�X�e���r�d�t�@�C���̃������o�^�̎w�胊�X�g���폜
		int		dxLib_MemEntryDeleteSystemSound( char * SysSoundFile_ );

		// �������Ƀ��[�h�����V�X�e���r�d�t�@�C���̍Đ�
		int		dxLib_MemPlaySystemSound( char * SysSoundFile_ );

		// �������ɓǂ݂��񂾉����f�[�^���Đ��������ׂ�(�T�E���h�n���h��)
		int		dxLib_MemSoundPlayStatusCheck( const int  nSoundHandle );

		// �������ɓǂ݂��񂾓o�^�����f�[�^���Đ��������ׂ�(�T�E���h�t�@�C���l�[��)
		int		dxLib_MemSoundPlayStatusCheck( char * szSoundFile );

		// �������ɓǂ݂��񂾓o�^�����T�E���h�f�[�^���폜����(�T�E���h�n���h��)
		int		dxLib_MemLoadSoundHandleDelete( const int  nSoundHandle );
		int		dxLib_MemLoadSoundHandleDelete( char * szSoundFile );

		// �T�E���h�n���h���̃{�����[����ݒ肷��( 0 �` 255 )( 0�F����, -1�F�G���[���� )
		int		dxLib_MemSoundFileVolumeSet( const int  nSysVolumePal, const int  nSoundHandle );
		int		dxLib_MemSoundFileVolumeSet( const int  nSysVolumePal, char * szSoundFile );

		// �w��T�E���h�n���h���̃{�����[�����擾����( 0 �` 255 )
		int		dxLib_MemSoundFileVolumeGet( const int  nSoundHandle );
		int		dxLib_MemSoundFileVolumeGet( const int  nSoundHandle, char * szSoundFile );

		// �w��T�E���h�n���h���̍Đ����g����ݒ肷��
		int		dxLib_SetSoundSampleFrequency( const int  nSoundHandle );
		// �w��T�E���h�n���h���̍Đ����g�����擾����
		int		dxLib_GetSoundSampleFrequency( const int  nSoundHandle );

		// �T�E���h�n���h���̉��̑����Ԃ��~���b�P�ʂŎ擾����
		int		dxLib_GetSoundPlayingMiriTime( const int  nSoundHandle );

		// �T�E���h�V�X�e�����t���[������
		int		dxLib_SystemSound_Runtime( const int  nSoundMode = 0 );
		void	dxLib_SystemSound_ProcAtOnce( void );

		// �V�X�e��SE�Đ���~
		int		dxLib_MemSoundStop( void );

		// �Đ����̃V�X�e��SE�J�e�S���̃t�@�C����S�Ď~�߂�
		int		dxLib_MemSoundPlayGroupStop( void );

		// �{�����[���l�͈͓̔��N���b�s���O
		void	dxLib_SoundVolumeCalcClipping( int * pVolume );

	};
}









/* End dxLibStreamManager.h */


