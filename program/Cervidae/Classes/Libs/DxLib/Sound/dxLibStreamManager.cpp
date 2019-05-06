
#include "DxLib.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../../../Common/CommonList.h"
#include "dxLibSoundManageConfig.h"
#include "dxLibStreamManager.h"

//==========================================================================//
//
//
//  Created by kashima akihiro on 2019/03/21.
//==========================================================================//


/*
 *	�R���X�g���N�^
 */
DxLib::StreamPlayManager::StreamPlayManager()
{

}
DxLib::StreamPlayManager::~StreamPlayManager()
{

}

// 
void	DxLib::StreamPlayManager::setMidiPlayMode( const int  nMidiMode )
{
	//--------------------------------------------------------------------------------------------
	// ����{MIDI�͎g�p�����S��mp3�`��
	// DX_MIDIMODE_DM  : DirectMusic �ɂ�鉉�t
	// DX_MIDIMODE_MCI : MCI�ɂ��Đ�(�f�t�H���g)
	// MCI��MIDI�t�@�C�����Đ������N�I���e�B�͊e�p�\�R���ɃC���X�g�[������Ă���MIDI�f�o�C�X�Ɉˑ����܂�
	int result_ = -1;
	result_ = DxLib::SelectMidiMode( nMidiMode );
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : StreamPlayManager::setMidiPlayMode\n"); // �ݒ�G���[
	}
}

// 
bool	DxLib::StreamPlayManager::initialize()
{
	return false;
}

//==========================================================================//
// MIDI�CWAV�C"MP3"�t�@�C�����Đ�����
//	FileName : ���t(�Đ�)����MIDI�AWAV���͂l�o�R�t�@�C���̃t�@�C���p�X�������
//			   �|�C���^
//	PlayType : ���t(�Đ�)�`��
//			   DX_PLAYTYPE_NORMAL	:	�m�[�}���Đ�
//			   DX_PLAYTYPE_BACK		:	�o�b�N�O���E���h�Đ�
//			   DX_PLAYTYPE_LOOP		:	�o�b�N�O���E���h�{���[�v�Đ�
//	�߂�l    �O�F����
//			�|�P�F�G���[����
int		DxLib::StreamPlayManager::streamPlay( char * playFileName, const int  SoundArchive, const int  playingType )
{
	char strStrmPath[ 256 ] = {};

	// �t�@�C���p�X�擾
//	dxLib_FileLoadGetAccessPath( SoundArchive, playFileName, strStrmPath );

	// �X�g���[���Đ�����
	int hStreamPlay = -1;
	hStreamPlay = DxLib::PlayMusic( strStrmPath, playingType );
	if( hStreamPlay == -1 )
	{
		ERROR_PRINT("__ERROR__ : StreamPlayManager::streamPlay[%s]\n", playFileName );// �Đ����s
		return ( -1); // ERROR
	}
	return 0;
}
int		DxLib::StreamPlayManager::streamIdPlay( const int  playFileNo, const int  SoundArchive, const int  PlayingType )
{
	//-------------------------------------------------------------------------------------------------------
	// TYPE�A�F�t�@�C���̔ԍ��̂ݎw��Ŏ����Ńl�[����ݒ肷��Ver
	// (���S�Ẵt�@�C�����ɋK�������������Đݒ肵�Ă�O��(��,1_sound.wav/2_sound.wav/3_sound.wav�̗l��)
	//-------------------------------------------------------------------------------------------------------
	char strStrmPath[ 256] = {};
	char strFileName[ 256] = {};

	// �t�@�C���l�[���쐬
	sprintf_s( strFileName, 256, "%d_Sound.mp3", playFileNo );

	// �t�@�C���p�X�擾
//	dxLib_FileLoadGetAccessPath( SoundArchive, strFileName, strStrmPath );

	// �X�g���[���Đ�����
	int playResult = -1;
	playResult = DxLib::PlayMusic( strStrmPath, PlayingType );
	if( playResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : StreamPlayManager::streamIdPlay[%s]\n", strFileName );// �Đ����s
		return ( -1 ); // ERROR
	}

	return 0;
}

//==========================================================================//
// MIDI�CWAV�C"MP3"�t�@�C���̍Đ���~
// 	  �O�F����
//	�|�P�F�G���[����
int		DxLib::StreamPlayManager::streamPlayStop()
{
	// PlayMusic�֐��ŊJ�n�����Đ����~���܂�
	const int result_ = DxLib::StopMusic();
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : StreamPlayManager::streamPlayStop()\n");
		return ( -1 );	// Error
	}
	// ��������
	return 0;
}

//==========================================================================//
// MIDI�CWAV�C"MP3"�t�@�C�����Đ������̏����擾����
// ��PlayMusic�֐��ŊJ�n����MIDI���͂l�o�R���t(�Đ�)���܂������Ă��邩���𓾂܂��B
// �߂�l�Ƃ��ĂO���Ԃ��Ă���Ή��t(�Đ�)�͏I�����Ă���A
// �P�� �Ԃ��Ă���Ή��t(�Đ�)�͂܂������Ă���ƌ������ƂɂȂ�܂��B
// << �߂�l >>
//		�O�F���t(�Đ�)���ł͂Ȃ�
//		�P�F���t(�Đ�)��
//	�@�|�P�F�G���[
int		DxLib::StreamPlayManager::streamPlayState()
{
	// PlayMusic�֐��ŊJ�n�����Đ����܂������Ă��邩�`�F�b�N
	const int	result_ = DxLib::CheckMusic();
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : StreamPlayManager::dtreamPlayState()\n");
		return ( -1 ); // Error
	}
	return ( result_ ); // Error����Ȃ��Ȃ����Ԃ�
}

//==========================================================================//
// MIDI�CWAV�C"MP3"�t�@�C���̍Đ����ʂ�ݒ肷��(���f�t�H���g�͔���)
// int  StreamVolume �F����(0�`255)
// << �߂�l >>
//		�O�F����
//	�@�|�P�F�G���[����
// ��PlayMusic�֐� �ŊJ�n�������t�̉��ʂ�ݒ肵�܂��O�������A�Q�T�T���ő剹��(�f�t�H���g)
// ���l�b�h���g�p�����l�h�c�h���t�̏ꍇ�͉��ʂ�ύX�͕s��
int		DxLib::StreamPlayManager::setPlayVolumeConfig( const int  nStreamVolume )
{
	if( nStreamVolume < 0 || nStreamVolume > 255 ){
		return ( -1 );// Error �{�����[���l�ݒ�G���[
	}
	// �Đ����Ȃ�{�����[����ύX
	const int result_ = streamPlayState();/* PlayMusic�֐��ŊJ�n�����Đ����܂������Ă��邩�`�F�b�N */
	if( result_ != 1 )// �G���[ or ��~��
	{
		ERROR_PRINT("__ERROR__ : dxLib_SoundPlayVolumeConfig\n");
		return ( -1 );// Error �Đ����Ă��Ȃ��̂ŕύX����Ӗ�������
	}
	// �{�����[���ύX
	DxLib::SetVolumeMusic( nStreamVolume );

	// ��������
	return ( 0 );
}

//==========================================================================//
// MIDI�CWAV�C"MP3"�t�@�C���̃T�E���h�n���h�����g�p�����X�g���[���Đ�
int		DxLib::StreamPlayManager::streamHandlePlay( const int  nHandle, const int  nPlaying, const int  bPlayPosition )
{
	if( nHandle < 0 ){ return ( -1 ); }// Error 



	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//	�������Ɏ��O�ɓǂݍ��݂�ł����^�C�v
//	��������ƃ���������������̂Œ���
//	�������[�Ɏ��O�ǂݍ��� �� �Đ�
/////////////////////////////////////////////////////////////////////////////////////////////

////==========================================================================//
// 	�����t�@�C��(WAV.MP3.Ogg)���������ɓǂ݂���
//		char * SysSoundFile_	:	�T�E���h�t�@�C����
//		int  nSoundArchive		:	�A�[�J�C�uINDEX
//	<<�߂�l>>
//		    �|�P�F�G���[
//		�|�P�ȊO�F�T�E���h�n���h��


//==========================================================================//
//	�������̉����t�@�C�������邩�`�F�b�N
//		char * SysSoundFile_	:	�T�E���h�t�@�C����
//	<�߂�l>
//		���s					:	DXLSOUND_MEMORY_MAX


//==========================================================================//
//	���O����o�^�n���h����T���ĕԂ�
//		char * SysSoundFile_	:	�T�E���h�t�@�C����
//	@return		�T�E���h�n���h��


//==========================================================================//
// 	�f�[�^�o�^�ԍ��̓o�^�T�E���h�n���h�����擾
//		int  nEntryIndex		:	�f�[�^�o�^�ԍ�


//==========================================================================//
//	�������ɓǂݍ��񂾉����t�@�C��(WAV.MP3.Ogg)�̍Đ�
//		szSoundName		�F �Đ����鉹�̎��ʔԍ��i�T�E���h�n���h���j
//		SoundPlay		�F �Đ��`��
//							DX_PLAYTYPE_NORMAL	:	�m�[�}���Đ�
//							DX_PLAYTYPE_BACK	:	�o�b�N�O���E���h�Đ�
//							DX_PLAYTYPE_LOOP	:	���[�v�Đ�
//		isTopPosition	�F �Đ��ʒu�����f�[�^�̐擪�Ɉړ����邩�ǂ���
//							( TRUE�F�ړ�����i�f�t�H���g�j�@FALSE�F�ړ����Ȃ� )
//	<<�߂�l>>
//		0->�Đ�����		-1->�Đ����s


//==========================================================================//
//


//==========================================================================//
//





