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
	// 処理結果コード
	namespace FileProcess
	{
		typedef enum
		{
			eFILE_RESULT_CODE_ERROR = -1,		// @param	ERROR
			eFILE_RESULT_CODE_UNKNOWN = 99,		// @param	未確認エラー
			eFILE_RESULT_CODE_SUCCESS = 0,		// @param	CLEAR
			eFILE_RESULT_CODE_RUNNING = 1,		// @param	実行中
			eFILE_RESULT_CODE_WAITING = 2,		// @param	処理待機
		} ENUM_FILE_PROCESS_CODE;
	}

	namespace FileVram
	{
		typedef enum
		{
			eRESULT_CODE_SUCCESS = 0,					// @param	処理成功
			eRESULT_CODE_ERROR_FAILED = -1,
			eRESULT_CODE_ERROR_SIZECHECK = -2,			// @param	テクスチャサイズ取得失敗
			eRESULT_CODE_ERROR_DOUBLE_LOADING = -3,		// @param	２重読み込み
			eRESULT_CODE_ERROR_LOADFAILED = -4,			// @param	読み込み失敗
			eRESULT_CODE_ERROR_NOARRAY = -5,			// @param	読み込みリストに空きが無い
			eRESULT_CODE_ERROR_NOENTRYFILE = -6,		// @param	指定ファイルは登録されていない
			eRESULT_CODE_ERROR_NOTHING_REGISTERE = -7,	// @param	何も登録されてない
			eRESULT_CODE_ERROR_RELEASEFAILED,

		} ENUM_FILE_VRAM_RESULT_CODE;

		// テクスチャ読み込み状況
		typedef enum
		{
			eLOAD_STATE_NONLOAD = 0,	// 読み込んでいない
			eLOAD_STATE_RESULTSTART,	// 読み込み開始
			eLOAD_STATE_RESULTOK,		// 準備完了
			eLOAD_STATE_RESULTDELETE,	// VRAMから消去
		} ENUM_FILE_VRAM_LOAD_STATE;

		// チェック(毎フレーム)
		typedef enum
		{
			eCHECK_STATE_NON,
			eCHECK_STATE_FILELOAD = (1 << 0),	// ファイルロード
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


