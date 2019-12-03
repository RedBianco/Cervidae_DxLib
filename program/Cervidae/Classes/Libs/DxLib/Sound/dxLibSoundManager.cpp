
#include "DxLib.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../../../Common/appCommonParam.h"
#include "../Resources/appResourcesConfig.h"
#include "../Resources/Texture/appFileSystem.h"
#include "Process/dxLibSoundData.h"
#include "dxLibSoundManageConfig.h"
#include "dxLibSoundManager.h"

//==========================================================================//
//
//
//  Created by kashima akihiro on 2019/03/21.
//==========================================================================//


/*
 *	�R���X�g���N�^
 */
DxLib::SoundPlayManager::SoundPlayManager()
{

}
DxLib::SoundPlayManager::~SoundPlayManager()
{

}

//==========================================================================//
// 
// DX_MIDIMODE_DM  : DirectMusic �ɂ�鉉�t
// DX_MIDIMODE_MCI : MCI�ɂ��Đ�(�f�t�H���g)
void	DxLib::SoundPlayManager::setMidiPlayMode( const int  nMidiMode )
{
	//--------------------------------------------------------------------------------------------
	// ����{MIDI�͎g�p�����S��mp3�`��
	// MCI��MIDI�t�@�C�����Đ������N�I���e�B�͊e�p�\�R���ɃC���X�g�[������Ă���MIDI�f�o�C�X�Ɉˑ����܂�
	int result_ = -1;
	result_ = DxLib::SelectMidiMode( nMidiMode );
#if PROJECT_DEBUG
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : SoundPlayManager::setMidiPlayMode\n"); // �ݒ�G���[
	}
#endif
}

//==========================================================================//
// 
//
bool	DxLib::SoundPlayManager::init()
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
int		DxLib::SoundPlayManager::streamPlay( char * playFileName, const int  SoundArchive, const int  playingType )
{
	char strLoadPath[ 256 ] = {};

	// �t�@�C���p�X�擾
	fileLoadGetAccessPath( SoundArchive, playFileName, strLoadPath );

	// �X�g���[���Đ�����
	int hStreamPlay = -1;
	hStreamPlay = DxLib::PlayMusic( strLoadPath, playingType );
	if( hStreamPlay == -1 )
	{
		ERROR_PRINT("__ERROR__ : SoundPlayManager::streamPlay[%s]\n", playFileName );// �Đ����s
		return ( -1); // ERROR
	}

	DEBUG_PRINT("[Sound] streamPlay�F[%s]\n", playFileName );
	return 0;
}
int		DxLib::SoundPlayManager::streamIdPlay( const int  playFileNo, const int  SoundArchive, const int  PlayingType )
{
	//-------------------------------------------------------------------------------------------------------
	// TYPE�A�F�t�@�C���̔ԍ��̂ݎw��Ŏ����Ńl�[����ݒ肷��Ver
	// (���S�Ẵt�@�C�����ɋK�������������Đݒ肵�Ă�O��(��,1_sound.wav/2_sound.wav/3_sound.wav�̗l��)
	//-------------------------------------------------------------------------------------------------------
	char strLoadPath[ 256] = {};
	char strFileName[ 256] = {};

	// �t�@�C���l�[���쐬
	sprintf_s( strFileName, 256, "%d_Sound.mp3", playFileNo );

	// �t�@�C���p�X�擾
	fileLoadGetAccessPath( SoundArchive, strFileName, strLoadPath );

	// �X�g���[���Đ�����
	int playResult = -1;
	playResult = DxLib::PlayMusic( strLoadPath, PlayingType );
#if PROJECT_DEBUG
	if( playResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : SoundPlayManager::streamIdPlay[%s]\n", strFileName );// �Đ����s
		return ( -1 ); // ERROR
	}
#endif

	DEBUG_PRINT("[Sound] streamIdPlay�F[%s]\n", strFileName );
	return 0;
}

//==========================================================================//
//	MIDI�CWAV�C"MP3"�t�@�C���̍Đ���~
// 	  �O�F����
//	�|�P�F�G���[����
int		DxLib::SoundPlayManager::streamPlayStop()
{
	// PlayMusic�֐��ŊJ�n�����Đ����~���܂�
	const int result_ = DxLib::StopMusic();
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : SoundPlayManager::streamPlayStop()\n");
		return ( -1 );	// Error
	}
	// ��������
	return 0;
}

//==========================================================================//
//	MIDI�CWAV�C"MP3"�t�@�C�����Đ������̏����擾����
//	��PlayMusic�֐��ŊJ�n����MIDI���͂l�o�R���t(�Đ�)���܂������Ă��邩���𓾂܂��B
//	�߂�l�Ƃ��ĂO���Ԃ��Ă���Ή��t(�Đ�)�͏I�����Ă���A
//	�P�� �Ԃ��Ă���Ή��t(�Đ�)�͂܂������Ă���ƌ������ƂɂȂ�܂��B
//	<< �߂�l >>
//		�O�F���t(�Đ�)���ł͂Ȃ�
//		�P�F���t(�Đ�)��
//	�@�|�P�F�G���[
int		DxLib::SoundPlayManager::streamPlayState()
{
	// PlayMusic�֐��ŊJ�n�����Đ����܂������Ă��邩�`�F�b�N
	const int result_ = DxLib::CheckMusic();
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : SoundPlayManager::dtreamPlayState()\n");
		return ( -1 ); // Error
	}
	return ( result_ ); // Error����Ȃ��Ȃ����Ԃ�
}

//==========================================================================//
//	MIDI�CWAV�C"MP3"�t�@�C���̍Đ����ʂ�ݒ肷��(���f�t�H���g�͔���)
//	int  StreamVolume �F����(0�`255)
//	<< �߂�l >>
//		�O�F����
//	�@�|�P�F�G���[����
//	��PlayMusic�֐� �ŊJ�n�������t�̉��ʂ�ݒ肵�܂��O�������A�Q�T�T���ő剹��(�f�t�H���g)
//	���l�b�h���g�p�����l�h�c�h���t�̏ꍇ�͉��ʂ�ύX�͕s��
int		DxLib::SoundPlayManager::setPlayVolumeConfig( const int  nStreamVolume )
{
#if PROJECT_DEBUG
	if( nStreamVolume < 0 || nStreamVolume > 255 ){
		return ( -1 );// Error �{�����[���l�ݒ�G���[
	}
#endif
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
//	MIDI�CWAV�C"MP3"�t�@�C���̃T�E���h�n���h�����g�p�����X�g���[���Đ�
//
//
int		DxLib::SoundPlayManager::streamHandlePlay( const int  nHandle, const int  nPlaying, const int  bPlayPosition )
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
int		DxLib::SoundPlayManager::dxLib_SoundFileMemLoad( const char* loadFileName_, const int  nSoundArchive )
{
	int		soundHandle = -1;
	int		index = 0;
	char	strFilePath[256] = {};

	// �t�@�C���p�X�擾
//	dxLib_FileLoadGetAccessPath( nSoundArchive, SysSoundFile_, strFilePath );

	// �������֓ǂݍ���
	soundHandle = DxLib::LoadSoundMem( strFilePath );
    if( soundHandle == -1 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_SoundFileMemLoad [%s]\n", loadFileName_ );
		return ( -1 );	// �ǂݍ��ݎ��s
	}

	// �������̉����t�@�C�������邩�`�F�b�N(���Q�d�ǂݍ��ݖh�~�j
	index = dxLib_MemSoundDataCheck( loadFileName_ );
	if ( index == DxLibSound::BaseInfo::SETTING_FILE_MEMORY_ENTRY_MAX )
	{
		return ( -1 ); // �󂫂�����
	}
	else if ( index < 0 )
	{
		// �f�[�^�o�^
		index = ( -index - 1 );
		// �T�E���h�t�@�C���l�[��
		m_SoundData[index].dxSoundName = loadFileName_;
		// �f�[�^�o�^�ݒ�
		m_SoundData[index].dxSoundExist = DxLibSound::Command::eSEDATA_ENTRY_SET;
		// �T�E���h�n���h��
		m_SoundData[index].dxSoundHandle = soundHandle;

		DEBUG_PRINT("[Sound] SoundFileMemLoad�FFile [%s]\n", loadFileName_ );

		// �f�[�^�o�^�����Z
		dxSoundEntry ++;

		DEBUG_PRINT("[Sound] SoundFileMemLoad�FSoundEntry [%d]\n", dxSoundEntry );
	}
	return soundHandle;// ��������,�n���h����Ԃ�
}

//==========================================================================//
//	�������̉����t�@�C�������邩�`�F�b�N
//		char * SysSoundFile_	:	�T�E���h�t�@�C����
//	<�߂�l>
//		���s					:	DXLSOUND_MEMORY_MAX
int		DxLib::SoundPlayManager::dxLib_MemSoundDataCheck( const char * SysSoundFile_ )
{
	int  i = 0;
	for ( i = 0; i < DxLibSound::BaseInfo::SETTING_FILE_MEMORY_ENTRY_MAX; i ++ )
	{
		App::SoundDataContainer* pFileData = &m_SoundData.at( i );
		if( (pFileData)->dxSoundExist < 0 ){ continue; }

		if( strcmp( (pFileData)->dxSoundName.c_str(), SysSoundFile_ ) == 0 )
		{
			return  i;	// ��������ԍ���Ԃ�
		}
	}
	const int entryNum = dxSoundEntry;
	// �t�@�C������������
	if( entryNum < DxLibSound::BaseInfo::SETTING_FILE_MEMORY_ENTRY_MAX )//	�󂫂�����Ȃ�
	{
		return  ( -1 - entryNum );
	}else{
		return  DxLibSound::BaseInfo::SETTING_FILE_MEMORY_ENTRY_MAX; //	�󂫂��Ȃ�
	}

	return 0;
}

//==========================================================================//
//	���O����o�^�n���h����T���ĕԂ�
//		char * SysSoundFile_	:	�T�E���h�t�@�C����
//	@return		�T�E���h�n���h��
int		DxLib::SoundPlayManager::dxLib_GetMemSoundDataEntryHandle( const char * SysSoundFile_ )
{
	// �f�[�^�o�^�ԍ��擾
	int dataIndex  = 0;
	dataIndex = dxLib_MemSoundDataCheck( SysSoundFile_ );
	if( dataIndex < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemSoundDataCheck\n");
		return ( -2 );	//	�f�[�^�擾�G���[
	}

	// �T�E���h�n���h���擾
	int soundHandle = 0;
	soundHandle = dxLib_GetMemSoundDataEntryIndex( dataIndex );
	if( soundHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_GetMemSoundDataEntryIndex\n");
		return ( -2 );	//	�f�[�^�擾�G���[
	}
	return ( soundHandle );
}

//==========================================================================//
// 	�f�[�^�o�^�ԍ��̓o�^�T�E���h�n���h�����擾
//		int  nEntryIndex		:	�f�[�^�o�^�ԍ�
int		DxLib::SoundPlayManager::dxLib_GetMemSoundDataEntryIndex( const int  nEntryIndex )
{
	App::SoundDataContainer* pFileData = &m_SoundData.at( nEntryIndex );
#if PROJECT_DEBUG
	if( pFileData == NULL ){
		ERROR_PRINT("__ERROR__ : dxLib_GetMemSoundDataEntryIndex\n");
		return ( -1 );
	}
#endif
	return (pFileData)->dxSoundHandle;
}

//==========================================================================//
//	�������ɓǂݍ��񂾉����t�@�C��(WAV.MP3.Ogg)�̍Đ�
//		szSoundName		�F �Đ��t�@�C����
//		SoundPlay		�F �Đ��`��
//							DX_PLAYTYPE_NORMAL	:	�m�[�}���Đ�
//							DX_PLAYTYPE_BACK	:	�o�b�N�O���E���h�Đ�
//							DX_PLAYTYPE_LOOP	:	���[�v�Đ�
//		isTopPosition	�F �Đ��ʒu�����f�[�^�̐擪�Ɉړ����邩�ǂ���
//							( TRUE�F�ړ�����i�f�t�H���g�j�@FALSE�F�ړ����Ȃ� )
//	<<�߂�l>>
//		0->�Đ�����		-1->�Đ����s
int		DxLib::SoundPlayManager::dxLib_MemSoundPlay( char * szSoundName, const int  SoundPlay, const int  isTopPosition )
{
	// �f�[�^�o�^�ԍ��擾
	int sndDataIndex  = 0;
	sndDataIndex = dxLib_MemSoundDataCheck( szSoundName );
	if( sndDataIndex < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemSoundDataCheck\n");
		return ( -2 );   //	�f�[�^�擾�G���[
	}
	// �T�E���h�n���h���擾
	int soundDataHandle = 0;
	soundDataHandle = dxLib_GetMemSoundDataEntryIndex( sndDataIndex );
	if( soundDataHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_GetMemSoundDataEntryIndex\n");
		return ( -2 );   //	�f�[�^�擾�G���[
	}

	// �{�����[���ݒ�(���I�v�V�����̃{�����[�������g��)
	dxLib_MemSoundFileVolumeSet( soundDataHandle, 127 );

	// �T�E���h�n���h���ōĐ�
	int sndResult = 0;
	sndResult = DxLib::PlaySoundMem( soundDataHandle, SoundPlay, isTopPosition );
	if( sndResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : PlaySoundMem\n");
		return ( -1 );	// �Đ����s�G���[
	}

	DEBUG_PRINT("[Sound] MemSoundPlay�FFile[%s] Handle[%d]\n", szSoundName, soundDataHandle );
	
	return ( 0 ); // �Đ�����
}

//==========================================================================//
// �T�E���h�n���h���w��Đ�VER
//		nSoundHandle	�F �Đ����鉹�̎��ʔԍ��i�T�E���h�n���h���j
//		SoundPlay		�F �Đ��`��
//							DX_PLAYTYPE_NORMAL	:	�m�[�}���Đ�
//							DX_PLAYTYPE_BACK	:	�o�b�N�O���E���h�Đ�
//							DX_PLAYTYPE_LOOP	:	���[�v�Đ�
int		DxLib::SoundPlayManager::dxLib_MemSoundPlay( const int  nSoundHandle, const int  SoundPlay_, const int  isTopPosition_ )
{
	if( nSoundHandle < 0 ){ return ( -1 ); }

	int soundResult = 0;
	/*
		nSoundHandle_	:	�Đ����鉹�̎��ʔԍ��i�T�E���h�n���h���j
		SoundPlay_		:	�Đ��`��
		isTopPosition_	:	�Đ��ʒu�����f�[�^�̐擪�Ɉړ����邩�ǂ���
							( TRUE�F�ړ�����(�f�t�H���g)�@FALSE�F�ړ����Ȃ� )
	*/
	soundResult = DxLib::PlaySoundMem( nSoundHandle, SoundPlay_, isTopPosition_ );
	if( soundResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : MemSoundPlay Result[%d]\n", soundResult );
		return ( -1 ); // �Đ����s�G���[
	}

	DEBUG_PRINT("[Sound] MemSoundPlay�FHandle[%d]\n", nSoundHandle );
	return ( 0 ); // �Đ�����
}

//==========================================================================//
// �������ɓǂݍ��񂾃T�E���h�n���h���̍Đ����~����
// 	int  nSoundHandle_		:	�w��T�E���h�n���h��
//
//
int		DxLib::SoundPlayManager::dxLib_MemSoundPlayStop( const int  nSoundHandle )
{
	int soundResult = 0;
	soundResult = DxLib::StopSoundMem( nSoundHandle );
	if( soundResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemSoundPlayStop Result[%d]\n", soundResult );
		return ( -1 );	// ��~���s�G���[
	}
	return ( 0 ); // ��~����
}

/**
 *	�V�X�e���r�d�֘A�֐��Q
 *
 */

//==========================================================================//
// �V�X�e���r�d�t�@�C���̃������o�^
//
bool	DxLib::SoundPlayManager::dxLib_MemEntrySystemSound()
{
	int handleSE = -1;
	for( int  i = 0; i < DxLibSound::BaseInfo::SETTING_FILE_MEMORY_ENTRY_MAX; i ++ )
	{
		App::SoundDataContainer* pFileData = &m_SoundData.at(i);
		// ���X�g�ɓo�^����Ă邩�`�F�b�N
		if( strcmp( (pFileData)->dxSoundName.c_str(), "" ) == 0 ){ break; }

		// ���������[�h
		handleSE = dxLib_SoundFileMemLoad( (pFileData)->dxSoundName.c_str(), AppLib::Resources::Archive::eARCHIVE_FILETYPE_SE );
		if( handleSE == -1 )
		{
            ERROR_PRINT("__ERROR__ : dxLib_MemEntrySystemSound [%d][%s]\n", i, (pFileData)->dxSoundName.c_str() );
			return ( false);//	�G���[
		}
	}
	return ( true );
}
void	DxLib::SoundPlayManager::dxLib_MemEntrySystemSoundReregist()
{
	if( dxSoundReadMode == 0 )
	{
		dxSoundReadMode = 1;
	}
}
void	DxLib::SoundPlayManager::dxLib_MemEntrySystemSoundReset()
{
	if( dxSoundReadMode == 1 )
	{
		dxSoundReadMode = 0;
	}
}

//==========================================================================//
// �V�X�e���r�d�t�@�C���̃������o�^�̎w�胊�X�g���폜
//
//
int		DxLib::SoundPlayManager::dxLib_MemEntryDeleteSystemSound( char* SysSoundFile_ )
{
	// �f�[�^�o�^�ԍ��擾
	int j = 0;
	j = dxLib_MemSoundDataCheck( SysSoundFile_ );
	if( j < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemEntryDeleteSystemSound\n");
		return ( -1 ); // �f�[�^�擾�G���[
	}

	{
		App::SoundDataContainer* pFileData = &m_SoundData.at(j);
		if ( pFileData )
		{
			// �T�E���h�t�@�C���l�[��
			(pFileData)->dxSoundName = SysSoundFile_;
			// �T�E���h�n���h��
			(pFileData)->dxSoundHandle = DxLibSound::Command::eSEHANDLE_NOTLOAD;
			// �f�[�^�o�^�ݒ�
			(pFileData)->dxSoundExist = DxLibSound::Command::eSEDATA_ENTRY_NON;

			DEBUG_PRINT("[Sound] MemEntryDeleteSystemSound�FHandle[%s]\n", SysSoundFile_ );

			// �f�[�^�o�^�����Z
			dxSoundEntry --;

			DEBUG_PRINT("[Sound] MemEntryDeleteSystemSound�FSoundEntry [%d]\n", dxSoundEntry );

			return ( 1 );// �폜����
		}
	}

	return ( 0 );
}

//==========================================================================//
// �������Ƀ��[�h�����V�X�e���r�d�t�@�C���̍Đ�
// char *  _SysSoundFile  : �Đ��T�E���h�t�@�C����
int		DxLib::SoundPlayManager::dxLib_MemPlaySystemSound( char * SysSoundFile_ )
{
	int playResult = -1;
	playResult =  dxLib_MemSoundPlay( SysSoundFile_, DxLibSound::BaseInfo::SOUND_STREAM_NORMALPLAY, TRUE );
	if( playResult != 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemPlaySystemSound\n");
		return ( -1 ); // �Đ��G���[
	}
	return ( 1 ); // �Đ�����
}

//==========================================================================//
//	�������ɓǂ݂��񂾉����f�[�^���Đ��������ׂ�(�T�E���h�n���h��)
//	<<�߂�l>>
//			�P�F�Đ���
//			�O�F�Đ�����Ă��Ȃ�
//		  �|�P�F�G���[����
int		DxLib::SoundPlayManager::dxLib_MemSoundPlayStatusCheck( const int  nSoundHandle )
{
	int nSoundResult = 0, nSoundStatus = 0;
	nSoundResult = DxLib::CheckSoundMem( nSoundHandle );
	if( nSoundResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemSoundPlayStatusCheck\n");
		return ( -1 );
	}
	if( nSoundResult == 0 )
	{
		nSoundStatus = DxLibSound::Command::eSOUND_ORDER_STOP;
	}
	else if( nSoundResult == 1 )
	{
		nSoundStatus = DxLibSound::Command::eSOUND_ORDER_PLAY;
	}
	return ( nSoundStatus );
}

//==========================================================================//
// �������ɓǂ݂��񂾓o�^�����f�[�^���Đ��������ׂ�(�T�E���h�t�@�C���l�[��)
// char *  szSoundFile
//	<<�߂�l>>
//		�P�F�Đ���
//		�O�F�Đ�����Ă��Ȃ�
//	  �|�P�F�G���[����
int		DxLib::SoundPlayManager::dxLib_MemSoundPlayStatusCheck( char *  szSoundFile )
{
	//	�T�E���h�n���h���擾
	int _SoundHandle = 0;
	_SoundHandle = dxLib_GetMemSoundDataEntryHandle( szSoundFile );
	if( _SoundHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : Handle dxLib_MemSoundPlayStatusCheck\n");
		return ( -2 );	//	�f�[�^�擾�G���[
	}
	//	
	int nSoundResult = 0, nSoundStatus = 0;
	nSoundResult = DxLib::CheckSoundMem( _SoundHandle );
	if( nSoundResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : Result dxLib_MemSoundPlayStatusCheck\n");
		return ( -1 );
	}
	if( nSoundResult == 0 )
	{
		nSoundStatus = DxLibSound::Command::eSOUND_ORDER_STOP; // �Đ���~
	}
	else if( nSoundResult == 1 )
	{
		nSoundStatus = DxLibSound::Command::eSOUND_ORDER_PLAY; // �Đ���
	}
	return ( nSoundStatus );
}

//==========================================================================//
// �������ɓǂ݂��񂾓o�^�����T�E���h�f�[�^���폜����(�T�E���h�n���h��)
//	<<�߂�l>>
//		�O�F����
//	  �|�P�F�G���[����
//	�����̍Đ����ɍ폜�����ꍇ�͍Đ����~�߂Ă���폜
//	���폜�����T�E���h�͍ēǂݍ��݂���܂Ŏg�����Ƃ͏o���Ȃ��Ȃ�
int		DxLib::SoundPlayManager::dxLib_MemLoadSoundHandleDelete( const int  nSoundHandle )
{
	int deleteResult = 0;
	deleteResult = DxLib::DeleteSoundMem( nSoundHandle );
	if( deleteResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemLoadSoundHandleDelete\n");
		return ( -1 );	// �n���h���G���[
	}
	return ( 0 );
}

//==========================================================================//
//	�������ɓǂ݂��񂾓o�^�����T�E���h�f�[�^���폜����(�T�E���h�t�@�C���l�[��)
//		char * szSoundFile		:	
//	<<�߂�l>>
//		�O�F����
//	  �|�P�F�G���[����
//	�����̍Đ����ɍ폜�����ꍇ�͍Đ����~�߂Ă���폜
//	���폜�����T�E���h�͍ēǂݍ��݂���܂Ŏg�����Ƃ͏o���Ȃ��Ȃ�
int		DxLib::SoundPlayManager::dxLib_MemLoadSoundHandleDelete( char * szSoundFile )
{
	// �T�E���h�n���h���擾
	int _SoundHandle = 0;
	_SoundHandle = dxLib_GetMemSoundDataEntryHandle( szSoundFile );
	if( _SoundHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : Handle dxLib_MemLoadSoundHandleDelete\n");
		return ( -2 );	// �f�[�^�擾�G���[
	}

	int  _HandleDelete = 0;
	_HandleDelete = DxLib::DeleteSoundMem( _SoundHandle );
	if( _HandleDelete == -1 )
	{
		ERROR_PRINT("__ERROR__ : Delete dxLib_MemLoadSoundHandleDelete\n");
		return ( -1 );	// �n���h���G���[
	}
	return ( 0 );
}

//==========================================================================//
//	�T�E���h�n���h���̃{�����[����ݒ肷��( 0 �` 255 )( 0�F����, -1�F�G���[���� )
//	�������Đ����ł����ʂ̕ύX�͉\
//		int  nSysVolumePal		:	�w��{�����[��
//		int  nSoundHandle		:	�w��T�E���h�n���h��
//	<<�߂�l>>
//		�O�F����
//	  �|�P�F�G���[����
int		DxLib::SoundPlayManager::dxLib_MemSoundFileVolumeSet( const int  nSysVolumePal, const int nSoundHandle )
{
	int volumeResult = 0;
	if( nSoundHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : MemSoundFileVolumeSet Handle[%d]\n", nSoundHandle );
		return ( -1 );	// �n���h���G���[
	}
	volumeResult = DxLib::ChangeVolumeSoundMem( nSysVolumePal, nSoundHandle );
	if( volumeResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : ChangeVolumeSoundMem Result[%d]\n", volumeResult );
		return ( -1 );	// �{�����[���ݒ�G���[
	}
	return ( 0 ); // ����
}
int		DxLib::SoundPlayManager::dxLib_MemSoundFileVolumeSet( const int  nSysVolumePal, char * szSoundFile )
{
	// �T�E���h�n���h���̎擾
	int soundHandle = 0;
	soundHandle = dxLib_GetMemSoundDataEntryHandle( szSoundFile );
	if( soundHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_GetMemSoundDataEntryHandle File[%s]\n", szSoundFile );
		return ( -1 );	// �f�[�^�擾�G���[
	}
	int iVolResult = 0;
	iVolResult = DxLib::ChangeVolumeSoundMem( nSysVolumePal, soundHandle );
	if( iVolResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : ChangeVolumeSoundMem Handle[%d]\n", soundHandle );
		return ( -1 );	// �{�����[���ݒ�G���[
	}
	return ( 0 ); // ����
}

//==========================================================================//
//	�w��T�E���h�n���h���̃{�����[�����擾����( 0 �` 255 )
//		int  nSoundHandle		:	�w��T�E���h�n���h��
//	<<�߂�l>>
//		�{�����[��
//	
//==========================================================================//
int		DxLib::SoundPlayManager::dxLib_MemSoundFileVolumeGet( const int nSoundHandle )
{
	int soundVolume = DxLib::GetVolumeSoundMem( nSoundHandle );
	if( soundVolume < 0 )
	{
		ERROR_PRINT("__ERROR__ : MemSoundFileVolumeGet Volume[%d]\n", soundVolume );
	}
	return ( soundVolume );
}
int		DxLib::SoundPlayManager::dxLib_MemSoundFileVolumeGet( const int nSoundHandle, char * szSoundFile )
{
	int soundHandle = 0;
	soundHandle = dxLib_GetMemSoundDataEntryHandle( szSoundFile );
	if( soundHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemSoundFileVolumeGet\n");
		return ( -1 );	// �f�[�^�擾�G���[
	}
	int soundVolume = DxLib::GetVolumeSoundMem( soundHandle );
	return ( soundVolume );	// �{�����[����Ԃ�
}

//==========================================================================//
//	�w��T�E���h�n���h���̍Đ����g����ݒ肷��
//	����{�͑S�T�E���h�Œ�A�M��̂̓I�J�V�C
//	int  nSoundHandle : �w��T�E���h�n���h��
//	
//==========================================================================//
int		DxLib::SoundPlayManager::dxLib_SetSoundSampleFrequency( const int  nSoundHandle )
{
	int soundResult = -1;
	soundResult = DxLib::SetFrequencySoundMem( ( int)DxLibSound::BaseInfo::SOUND_SAMPLE_FREQUENCY, nSoundHandle );

	return ( soundResult );
}

//==========================================================================//
//	�w��T�E���h�n���h���̍Đ����g�����擾����
//
//	int  nSoundHandle : �w��T�E���h�n���h��
//	
//==========================================================================//
int		DxLib::SoundPlayManager::dxLib_GetSoundSampleFrequency( const int  nSoundHandle )
{
	int  nSampleFreq = 0;
	nSampleFreq = DxLib::GetFrequencySoundMem( nSoundHandle );

	return ( nSampleFreq );
}

//==========================================================================//
//	�T�E���h�n���h���̉��̑����Ԃ��~���b�P�ʂŎ擾����
//
//	int  nSoundHandle		:	�w��T�E���h�n���h��
//==========================================================================//
int		DxLib::SoundPlayManager::dxLib_GetSoundPlayingMiriTime( const int  nSoundHandle )
{
	int  nPlayingTime = 0;
	nPlayingTime = DxLib::GetSoundTotalTime( nSoundHandle );

	return ( nPlayingTime );
}

//==========================================================================//
//	�T�E���h�V�X�e�����t���[������
//
//==========================================================================//
int		DxLib::SoundPlayManager::dxLib_SystemSound_Runtime( const int  nSoundMode )
{
	return 0;
}
void	DxLib::SoundPlayManager::dxLib_SystemSound_ProcAtOnce( void )
{
}

//==========================================================================//
//	�V�X�e��SE�Đ��S��~
//
//==========================================================================//
int		DxLib::SoundPlayManager::dxLib_MemSoundStop()
{
	return dxLib_MemSoundPlayGroupStop();
}

//==========================================================================//
//	�Đ����̃V�X�e��SE�J�e�S���̃t�@�C����S�Ď~�߂�
//
//==========================================================================//
int		DxLib::SoundPlayManager::dxLib_MemSoundPlayGroupStop( void )
{
	int  nSound = 0;
	for( int  i = 0; i < DxLibSound::BaseInfo::SETTING_FILE_MEMORY_ENTRY_MAX; i ++ )
	{
		App::SoundDataContainer* pFileData = &m_SoundData.at(i);
		nSound = dxLib_MemSoundPlayStop( (pFileData)->dxSoundHandle );
		if( nSound == -1 )
		{
			ERROR_PRINT("__ERROR__ : dxLib_MemSoundPlayGroupStop\n");
			return ( -1 );	// ��~���s�G���[
		}
	}
	return ( 0 );
}

//==========================================================================//
//	�{�����[���l�͈͓̔��N���b�s���O
//	int * pVolume		:	�{�����[���l
//==========================================================================//
void	DxLib::SoundPlayManager::dxLib_SoundVolumeCalcClipping( int * pVolume )
{
	if( *pVolume >= 255 ){ *pVolume = 255; }
	if( *pVolume <= 0 ){ *pVolume = 0; }
}


