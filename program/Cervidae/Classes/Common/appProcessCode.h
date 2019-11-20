#pragma once


//===================================================================//
//
//
//
//===================================================================//


namespace App
{
	namespace Code
	{
	}
	namespace Process
	{
		typedef enum
		{
			eSTATUS_EXE_EXIT = 0,
		} ENUM_PROCESS_STATUS_CODE;
	}
	// �������ʃR�[�h
	namespace FileProcess
	{
		typedef enum
		{
			eFILE_RESULT_CODE_ERROR = -1,		// @param	ERROR
			eFILE_RESULT_CODE_UNKNOWN = 99,		// @param	���m�F�G���[
			eFILE_RESULT_CODE_SUCCESS = 0,		// @param	CLEAR
			eFILE_RESULT_CODE_RUNNING = 1,		// @param	���s��
			eFILE_RESULT_CODE_WAITING = 2,		// @param	�����ҋ@
		} ENUM_FILE_PROCESS_CODE;
	}

	namespace FileVram
	{
		typedef enum
		{
			eRESULT_CODE_SUCCESS = 0,					// @param	��������
			eRESULT_CODE_ERROR_FAILED = -1,
			eRESULT_CODE_ERROR_SIZECHECK = -2,			// @param	�e�N�X�`���T�C�Y�擾���s
			eRESULT_CODE_ERROR_DOUBLE_LOADING = -3,		// @param	�Q�d�ǂݍ���
			eRESULT_CODE_ERROR_LOADFAILED = -4,			// @param	�ǂݍ��ݎ��s
			eRESULT_CODE_ERROR_NOARRAY = -5,			// @param	�ǂݍ��݃��X�g�ɋ󂫂�����
			eRESULT_CODE_ERROR_NOENTRYFILE = -6,		// @param	�w��t�@�C���͓o�^����Ă��Ȃ�
			eRESULT_CODE_ERROR_NOTHING_REGISTERE = -7,	// @param	�����o�^����ĂȂ�
			eRESULT_CODE_ERROR_RELEASEFAILED,

		} ENUM_FILE_VRAM_RESULT_CODE;

		// �e�N�X�`���ǂݍ��ݏ�
		typedef enum
		{
			eLOAD_STATE_NONLOAD = 0,	// �ǂݍ���ł��Ȃ�
			eLOAD_STATE_RESULTSTART,	// �ǂݍ��݊J�n
			eLOAD_STATE_RESULTOK,		// ��������
			eLOAD_STATE_RESULTDELETE,	// VRAM�������
		} ENUM_FILE_VRAM_LOAD_STATE;

		// �`�F�b�N(���t���[��)
		typedef enum
		{
			eCHECK_STATE_NON,
			eCHECK_STATE_FILELOAD = (1 << 0),	// �t�@�C�����[�h
		} ENUM_FILE_VRAM_CHECK_STATE;
	}

	namespace SoundProcess
	{
		typedef enum
		{
			eSOUND_RESULT_CODE_ERROR = -1,		// @param ERROR
			eSOUND_RESULT_CODE_STOP	= 0,		// @param 
			eSOUND_RESULT_CODE_PLAYING = 1,		// @param 
			eSOUND_RESULT_CODE_FORCED_STOP,
			eSOUND_RESULT_CODE_UNCONFIRMED,

		} ENUM_SOUND_RESULT_CODE;
	}

	namespace JsonParse
	{
		typedef enum
		{
			eJSON_RESULT_CODE_ERROR	= -1,   // @param ERROR
			eJSON_RESULT_CODE_CLEAR,

		} ENUM_JSON_RESULT_CODE;
	}
}/* namespace App */



/* End appProcessCode.h */


