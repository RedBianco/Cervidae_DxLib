
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
 *	コンストラクタ
 */
DxLib::SoundPlayManager::SoundPlayManager()
{

}
DxLib::SoundPlayManager::~SoundPlayManager()
{

}

//==========================================================================//
// 
// DX_MIDIMODE_DM  : DirectMusic による演奏
// DX_MIDIMODE_MCI : MCIによる再生(デフォルト)
void	DxLib::SoundPlayManager::setMidiPlayMode( const int  nMidiMode )
{
	//--------------------------------------------------------------------------------------------
	// ※基本MIDIは使用せず全てmp3形式
	// MCIはMIDIファイルが再生されるクオリティは各パソコンにインストールされているMIDIデバイスに依存します
	int result_ = -1;
	result_ = DxLib::SelectMidiMode( nMidiMode );
#if PROJECT_DEBUG
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : SoundPlayManager::setMidiPlayMode\n"); // 設定エラー
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
// MIDI，WAV，"MP3"ファイルを再生する
//	FileName : 演奏(再生)するMIDI、WAV又はＭＰ３ファイルのファイルパス文字列の
//			   ポインタ
//	PlayType : 演奏(再生)形式
//			   DX_PLAYTYPE_NORMAL	:	ノーマル再生
//			   DX_PLAYTYPE_BACK		:	バックグラウンド再生
//			   DX_PLAYTYPE_LOOP		:	バックグラウンド＋ループ再生
//	戻り値    ０：成功
//			－１：エラー発生
int		DxLib::SoundPlayManager::streamPlay( char * playFileName, const int  SoundArchive, const int  playingType )
{
	char strLoadPath[ 256 ] = {};

	// ファイルパス取得
	fileLoadGetAccessPath( SoundArchive, playFileName, strLoadPath );

	// ストリーム再生処理
	int hStreamPlay = -1;
	hStreamPlay = DxLib::PlayMusic( strLoadPath, playingType );
	if( hStreamPlay == -1 )
	{
		ERROR_PRINT("__ERROR__ : SoundPlayManager::streamPlay[%s]\n", playFileName );// 再生失敗
		return ( -1); // ERROR
	}

	DEBUG_PRINT("[Sound] streamPlay：[%s]\n", playFileName );
	return 0;
}
int		DxLib::SoundPlayManager::streamIdPlay( const int  playFileNo, const int  SoundArchive, const int  PlayingType )
{
	//-------------------------------------------------------------------------------------------------------
	// TYPE②：ファイルの番号のみ指定で自動でネームを設定するVer
	// (※全てのファイル名に規則性を持たせて設定してる前提(例,1_sound.wav/2_sound.wav/3_sound.wavの様に)
	//-------------------------------------------------------------------------------------------------------
	char strLoadPath[ 256] = {};
	char strFileName[ 256] = {};

	// ファイルネーム作成
	sprintf_s( strFileName, 256, "%d_Sound.mp3", playFileNo );

	// ファイルパス取得
	fileLoadGetAccessPath( SoundArchive, strFileName, strLoadPath );

	// ストリーム再生処理
	int playResult = -1;
	playResult = DxLib::PlayMusic( strLoadPath, PlayingType );
#if PROJECT_DEBUG
	if( playResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : SoundPlayManager::streamIdPlay[%s]\n", strFileName );// 再生失敗
		return ( -1 ); // ERROR
	}
#endif

	DEBUG_PRINT("[Sound] streamIdPlay：[%s]\n", strFileName );
	return 0;
}

//==========================================================================//
//	MIDI，WAV，"MP3"ファイルの再生停止
// 	  ０：成功
//	－１：エラー発生
int		DxLib::SoundPlayManager::streamPlayStop()
{
	// PlayMusic関数で開始した再生を停止します
	const int result_ = DxLib::StopMusic();
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : SoundPlayManager::streamPlayStop()\n");
		return ( -1 );	// Error
	}
	// 処理成功
	return 0;
}

//==========================================================================//
//	MIDI，WAV，"MP3"ファイルが再生中かの情報を取得する
//	※PlayMusic関数で開始したMIDI又はＭＰ３演奏(再生)がまだ続いているか情報を得ます。
//	戻り値として０が返ってくれば演奏(再生)は終了しており、
//	１が 返ってくれば演奏(再生)はまだ続いていると言うことになります。
//	<< 戻り値 >>
//		０：演奏(再生)中ではない
//		１：演奏(再生)中
//	　－１：エラー
int		DxLib::SoundPlayManager::streamPlayState()
{
	// PlayMusic関数で開始した再生がまだ続いているかチェック
	const int result_ = DxLib::CheckMusic();
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : SoundPlayManager::dtreamPlayState()\n");
		return ( -1 ); // Error
	}
	return ( result_ ); // Errorじゃないなら情報を返す
}

//==========================================================================//
//	MIDI，WAV，"MP3"ファイルの再生音量を設定する(※デフォルトは半分)
//	int  StreamVolume ：音量(0～255)
//	<< 戻り値 >>
//		０：成功
//	　－１：エラー発生
//	※PlayMusic関数 で開始した演奏の音量を設定します０が無音、２５５が最大音量(デフォルト)
//	※ＭＣＩを使用したＭＩＤＩ演奏の場合は音量を変更は不可
int		DxLib::SoundPlayManager::setPlayVolumeConfig( const int  nStreamVolume )
{
#if PROJECT_DEBUG
	if( nStreamVolume < 0 || nStreamVolume > 255 ){
		return ( -1 );// Error ボリューム値設定エラー
	}
#endif
	// 再生中ならボリュームを変更
	const int result_ = streamPlayState();/* PlayMusic関数で開始した再生がまだ続いているかチェック */
	if( result_ != 1 )// エラー or 停止中
	{
		ERROR_PRINT("__ERROR__ : dxLib_SoundPlayVolumeConfig\n");
		return ( -1 );// Error 再生していないので変更する意味が無い
	}
	// ボリューム変更
	DxLib::SetVolumeMusic( nStreamVolume );

	// 処理成功
	return ( 0 );
}

//==========================================================================//
//	MIDI，WAV，"MP3"ファイルのサウンドハンドルを使用したストリーム再生
//
//
int		DxLib::SoundPlayManager::streamHandlePlay( const int  nHandle, const int  nPlaying, const int  bPlayPosition )
{
	if( nHandle < 0 ){ return ( -1 ); }// Error 


	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//	メモリに事前に読み込みんでおくタイプ
//	乱発するとメモリを圧迫するので注意
//	メモリーに事前読み込み → 再生
/////////////////////////////////////////////////////////////////////////////////////////////

////==========================================================================//
// 	音声ファイル(WAV.MP3.Ogg)をメモリに読みこむ
//		char * SysSoundFile_	:	サウンドファイル名
//		int  nSoundArchive		:	アーカイブINDEX
//	<<戻り値>>
//		    －１：エラー
//		－１以外：サウンドハンドル
int		DxLib::SoundPlayManager::dxLib_SoundFileMemLoad( const char* loadFileName_, const int  nSoundArchive )
{
	int		soundHandle = -1;
	int		index = 0;
	char	strFilePath[256] = {};

	// ファイルパス取得
//	dxLib_FileLoadGetAccessPath( nSoundArchive, SysSoundFile_, strFilePath );

	// メモリへ読み込み
	soundHandle = DxLib::LoadSoundMem( strFilePath );
    if( soundHandle == -1 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_SoundFileMemLoad [%s]\n", loadFileName_ );
		return ( -1 );	// 読み込み失敗
	}

	// メモリの音声ファイルがあるかチェック(※２重読み込み防止）
	index = dxLib_MemSoundDataCheck( loadFileName_ );
	if ( index == DxLibSound::BaseInfo::SETTING_FILE_MEMORY_ENTRY_MAX )
	{
		return ( -1 ); // 空きが無い
	}
	else if ( index < 0 )
	{
		// データ登録
		index = ( -index - 1 );
		// サウンドファイルネーム
		m_SoundData[index].dxSoundName = loadFileName_;
		// データ登録設定
		m_SoundData[index].dxSoundExist = DxLibSound::Command::eSEDATA_ENTRY_SET;
		// サウンドハンドル
		m_SoundData[index].dxSoundHandle = soundHandle;

		DEBUG_PRINT("[Sound] SoundFileMemLoad：File [%s]\n", loadFileName_ );

		// データ登録数加算
		dxSoundEntry ++;

		DEBUG_PRINT("[Sound] SoundFileMemLoad：SoundEntry [%d]\n", dxSoundEntry );
	}
	return soundHandle;// 処理成功,ハンドルを返す
}

//==========================================================================//
//	メモリの音声ファイルがあるかチェック
//		char * SysSoundFile_	:	サウンドファイル名
//	<戻り値>
//		失敗					:	DXLSOUND_MEMORY_MAX
int		DxLib::SoundPlayManager::dxLib_MemSoundDataCheck( const char * SysSoundFile_ )
{
	int  i = 0;
	for ( i = 0; i < DxLibSound::BaseInfo::SETTING_FILE_MEMORY_ENTRY_MAX; i ++ )
	{
		App::SoundDataContainer* pFileData = &m_SoundData.at( i );
		if( (pFileData)->dxSoundExist < 0 ){ continue; }

		if( strcmp( (pFileData)->dxSoundName.c_str(), SysSoundFile_ ) == 0 )
		{
			return  i;	// あったら番号を返す
		}
	}
	const int entryNum = dxSoundEntry;
	// ファイルが無かった
	if( entryNum < DxLibSound::BaseInfo::SETTING_FILE_MEMORY_ENTRY_MAX )//	空きがあるなら
	{
		return  ( -1 - entryNum );
	}else{
		return  DxLibSound::BaseInfo::SETTING_FILE_MEMORY_ENTRY_MAX; //	空きがない
	}

	return 0;
}

//==========================================================================//
//	名前から登録ハンドルを探して返す
//		char * SysSoundFile_	:	サウンドファイル名
//	@return		サウンドハンドル
int		DxLib::SoundPlayManager::dxLib_GetMemSoundDataEntryHandle( const char * SysSoundFile_ )
{
	// データ登録番号取得
	int dataIndex  = 0;
	dataIndex = dxLib_MemSoundDataCheck( SysSoundFile_ );
	if( dataIndex < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemSoundDataCheck\n");
		return ( -2 );	//	データ取得エラー
	}

	// サウンドハンドル取得
	int soundHandle = 0;
	soundHandle = dxLib_GetMemSoundDataEntryIndex( dataIndex );
	if( soundHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_GetMemSoundDataEntryIndex\n");
		return ( -2 );	//	データ取得エラー
	}
	return ( soundHandle );
}

//==========================================================================//
// 	データ登録番号の登録サウンドハンドルを取得
//		int  nEntryIndex		:	データ登録番号
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
//	メモリに読み込んだ音声ファイル(WAV.MP3.Ogg)の再生
//		szSoundName		： 再生ファイル名
//		SoundPlay		： 再生形式
//							DX_PLAYTYPE_NORMAL	:	ノーマル再生
//							DX_PLAYTYPE_BACK	:	バックグラウンド再生
//							DX_PLAYTYPE_LOOP	:	ループ再生
//		isTopPosition	： 再生位置を音データの先頭に移動するかどうか
//							( TRUE：移動する（デフォルト）　FALSE：移動しない )
//	<<戻り値>>
//		0->再生成功		-1->再生失敗
int		DxLib::SoundPlayManager::dxLib_MemSoundPlay( char * szSoundName, const int  SoundPlay, const int  isTopPosition )
{
	// データ登録番号取得
	int sndDataIndex  = 0;
	sndDataIndex = dxLib_MemSoundDataCheck( szSoundName );
	if( sndDataIndex < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemSoundDataCheck\n");
		return ( -2 );   //	データ取得エラー
	}
	// サウンドハンドル取得
	int soundDataHandle = 0;
	soundDataHandle = dxLib_GetMemSoundDataEntryIndex( sndDataIndex );
	if( soundDataHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_GetMemSoundDataEntryIndex\n");
		return ( -2 );   //	データ取得エラー
	}

	// ボリューム設定(※オプションのボリューム情報を使う)
	dxLib_MemSoundFileVolumeSet( soundDataHandle, 127 );

	// サウンドハンドルで再生
	int sndResult = 0;
	sndResult = DxLib::PlaySoundMem( soundDataHandle, SoundPlay, isTopPosition );
	if( sndResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : PlaySoundMem\n");
		return ( -1 );	// 再生失敗エラー
	}

	DEBUG_PRINT("[Sound] MemSoundPlay：File[%s] Handle[%d]\n", szSoundName, soundDataHandle );
	
	return ( 0 ); // 再生成功
}

//==========================================================================//
// サウンドハンドル指定再生VER
//		nSoundHandle	： 再生する音の識別番号（サウンドハンドル）
//		SoundPlay		： 再生形式
//							DX_PLAYTYPE_NORMAL	:	ノーマル再生
//							DX_PLAYTYPE_BACK	:	バックグラウンド再生
//							DX_PLAYTYPE_LOOP	:	ループ再生
int		DxLib::SoundPlayManager::dxLib_MemSoundPlay( const int  nSoundHandle, const int  SoundPlay_, const int  isTopPosition_ )
{
	if( nSoundHandle < 0 ){ return ( -1 ); }

	int soundResult = 0;
	/*
		nSoundHandle_	:	再生する音の識別番号（サウンドハンドル）
		SoundPlay_		:	再生形式
		isTopPosition_	:	再生位置を音データの先頭に移動するかどうか
							( TRUE：移動する(デフォルト)　FALSE：移動しない )
	*/
	soundResult = DxLib::PlaySoundMem( nSoundHandle, SoundPlay_, isTopPosition_ );
	if( soundResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : MemSoundPlay Result[%d]\n", soundResult );
		return ( -1 ); // 再生失敗エラー
	}

	DEBUG_PRINT("[Sound] MemSoundPlay：Handle[%d]\n", nSoundHandle );
	return ( 0 ); // 再生成功
}

//==========================================================================//
// メモリに読み込んだサウンドハンドルの再生を停止する
// 	int  nSoundHandle_		:	指定サウンドハンドル
//
//
int		DxLib::SoundPlayManager::dxLib_MemSoundPlayStop( const int  nSoundHandle )
{
	int soundResult = 0;
	soundResult = DxLib::StopSoundMem( nSoundHandle );
	if( soundResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemSoundPlayStop Result[%d]\n", soundResult );
		return ( -1 );	// 停止失敗エラー
	}
	return ( 0 ); // 停止成功
}

/**
 *	システムＳＥ関連関数群
 *
 */

//==========================================================================//
// システムＳＥファイルのメモリ登録
//
bool	DxLib::SoundPlayManager::dxLib_MemEntrySystemSound()
{
	int handleSE = -1;
	for( int  i = 0; i < DxLibSound::BaseInfo::SETTING_FILE_MEMORY_ENTRY_MAX; i ++ )
	{
		App::SoundDataContainer* pFileData = &m_SoundData.at(i);
		// リストに登録されてるかチェック
		if( strcmp( (pFileData)->dxSoundName.c_str(), "" ) == 0 ){ break; }

		// メモリロード
		handleSE = dxLib_SoundFileMemLoad( (pFileData)->dxSoundName.c_str(), AppLib::Resources::Archive::eARCHIVE_FILETYPE_SE );
		if( handleSE == -1 )
		{
            ERROR_PRINT("__ERROR__ : dxLib_MemEntrySystemSound [%d][%s]\n", i, (pFileData)->dxSoundName.c_str() );
			return ( false);//	エラー
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
// システムＳＥファイルのメモリ登録の指定リストを削除
//
//
int		DxLib::SoundPlayManager::dxLib_MemEntryDeleteSystemSound( char* SysSoundFile_ )
{
	// データ登録番号取得
	int j = 0;
	j = dxLib_MemSoundDataCheck( SysSoundFile_ );
	if( j < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemEntryDeleteSystemSound\n");
		return ( -1 ); // データ取得エラー
	}

	{
		App::SoundDataContainer* pFileData = &m_SoundData.at(j);
		if ( pFileData )
		{
			// サウンドファイルネーム
			(pFileData)->dxSoundName = SysSoundFile_;
			// サウンドハンドル
			(pFileData)->dxSoundHandle = DxLibSound::Command::eSEHANDLE_NOTLOAD;
			// データ登録設定
			(pFileData)->dxSoundExist = DxLibSound::Command::eSEDATA_ENTRY_NON;

			DEBUG_PRINT("[Sound] MemEntryDeleteSystemSound：Handle[%s]\n", SysSoundFile_ );

			// データ登録数加算
			dxSoundEntry --;

			DEBUG_PRINT("[Sound] MemEntryDeleteSystemSound：SoundEntry [%d]\n", dxSoundEntry );

			return ( 1 );// 削除成功
		}
	}

	return ( 0 );
}

//==========================================================================//
// メモリにロードしたシステムＳＥファイルの再生
// char *  _SysSoundFile  : 再生サウンドファイル名
int		DxLib::SoundPlayManager::dxLib_MemPlaySystemSound( char * SysSoundFile_ )
{
	int playResult = -1;
	playResult =  dxLib_MemSoundPlay( SysSoundFile_, DxLibSound::BaseInfo::SOUND_STREAM_NORMALPLAY, TRUE );
	if( playResult != 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemPlaySystemSound\n");
		return ( -1 ); // 再生エラー
	}
	return ( 1 ); // 再生成功
}

//==========================================================================//
//	メモリに読みこんだ音声データが再生中か調べる(サウンドハンドル)
//	<<戻り値>>
//			１：再生中
//			０：再生されていない
//		  －１：エラー発生
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
// メモリに読みこんだ登録音声データが再生中か調べる(サウンドファイルネーム)
// char *  szSoundFile
//	<<戻り値>>
//		１：再生中
//		０：再生されていない
//	  －１：エラー発生
int		DxLib::SoundPlayManager::dxLib_MemSoundPlayStatusCheck( char *  szSoundFile )
{
	//	サウンドハンドル取得
	int _SoundHandle = 0;
	_SoundHandle = dxLib_GetMemSoundDataEntryHandle( szSoundFile );
	if( _SoundHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : Handle dxLib_MemSoundPlayStatusCheck\n");
		return ( -2 );	//	データ取得エラー
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
		nSoundStatus = DxLibSound::Command::eSOUND_ORDER_STOP; // 再生停止
	}
	else if( nSoundResult == 1 )
	{
		nSoundStatus = DxLibSound::Command::eSOUND_ORDER_PLAY; // 再生中
	}
	return ( nSoundStatus );
}

//==========================================================================//
// メモリに読みこんだ登録音声サウンドデータを削除する(サウンドハンドル)
//	<<戻り値>>
//		０：成功
//	  －１：エラー発生
//	※音の再生中に削除した場合は再生を止めてから削除
//	※削除したサウンドは再読み込みするまで使うことは出来なくなる
int		DxLib::SoundPlayManager::dxLib_MemLoadSoundHandleDelete( const int  nSoundHandle )
{
	int deleteResult = 0;
	deleteResult = DxLib::DeleteSoundMem( nSoundHandle );
	if( deleteResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_MemLoadSoundHandleDelete\n");
		return ( -1 );	// ハンドルエラー
	}
	return ( 0 );
}

//==========================================================================//
//	メモリに読みこんだ登録音声サウンドデータを削除する(サウンドファイルネーム)
//		char * szSoundFile		:	
//	<<戻り値>>
//		０：成功
//	  －１：エラー発生
//	※音の再生中に削除した場合は再生を止めてから削除
//	※削除したサウンドは再読み込みするまで使うことは出来なくなる
int		DxLib::SoundPlayManager::dxLib_MemLoadSoundHandleDelete( char * szSoundFile )
{
	// サウンドハンドル取得
	int _SoundHandle = 0;
	_SoundHandle = dxLib_GetMemSoundDataEntryHandle( szSoundFile );
	if( _SoundHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : Handle dxLib_MemLoadSoundHandleDelete\n");
		return ( -2 );	// データ取得エラー
	}

	int  _HandleDelete = 0;
	_HandleDelete = DxLib::DeleteSoundMem( _SoundHandle );
	if( _HandleDelete == -1 )
	{
		ERROR_PRINT("__ERROR__ : Delete dxLib_MemLoadSoundHandleDelete\n");
		return ( -1 );	// ハンドルエラー
	}
	return ( 0 );
}

//==========================================================================//
//	サウンドハンドルのボリュームを設定する( 0 ～ 255 )( 0：成功, -1：エラー発生 )
//	※音を再生中でも音量の変更は可能
//		int  nSysVolumePal		:	指定ボリューム
//		int  nSoundHandle		:	指定サウンドハンドル
//	<<戻り値>>
//		０：成功
//	  －１：エラー発生
int		DxLib::SoundPlayManager::dxLib_MemSoundFileVolumeSet( const int  nSysVolumePal, const int nSoundHandle )
{
	int volumeResult = 0;
	if( nSoundHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : MemSoundFileVolumeSet Handle[%d]\n", nSoundHandle );
		return ( -1 );	// ハンドルエラー
	}
	volumeResult = DxLib::ChangeVolumeSoundMem( nSysVolumePal, nSoundHandle );
	if( volumeResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : ChangeVolumeSoundMem Result[%d]\n", volumeResult );
		return ( -1 );	// ボリューム設定エラー
	}
	return ( 0 ); // 成功
}
int		DxLib::SoundPlayManager::dxLib_MemSoundFileVolumeSet( const int  nSysVolumePal, char * szSoundFile )
{
	// サウンドハンドルの取得
	int soundHandle = 0;
	soundHandle = dxLib_GetMemSoundDataEntryHandle( szSoundFile );
	if( soundHandle < 0 )
	{
		ERROR_PRINT("__ERROR__ : dxLib_GetMemSoundDataEntryHandle File[%s]\n", szSoundFile );
		return ( -1 );	// データ取得エラー
	}
	int iVolResult = 0;
	iVolResult = DxLib::ChangeVolumeSoundMem( nSysVolumePal, soundHandle );
	if( iVolResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : ChangeVolumeSoundMem Handle[%d]\n", soundHandle );
		return ( -1 );	// ボリューム設定エラー
	}
	return ( 0 ); // 成功
}

//==========================================================================//
//	指定サウンドハンドルのボリュームを取得する( 0 ～ 255 )
//		int  nSoundHandle		:	指定サウンドハンドル
//	<<戻り値>>
//		ボリューム
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
		return ( -1 );	// データ取得エラー
	}
	int soundVolume = DxLib::GetVolumeSoundMem( soundHandle );
	return ( soundVolume );	// ボリュームを返す
}

//==========================================================================//
//	指定サウンドハンドルの再生周波数を設定する
//	※基本は全サウンド固定、弄るのはオカシイ
//	int  nSoundHandle : 指定サウンドハンドル
//	
//==========================================================================//
int		DxLib::SoundPlayManager::dxLib_SetSoundSampleFrequency( const int  nSoundHandle )
{
	int soundResult = -1;
	soundResult = DxLib::SetFrequencySoundMem( ( int)DxLibSound::BaseInfo::SOUND_SAMPLE_FREQUENCY, nSoundHandle );

	return ( soundResult );
}

//==========================================================================//
//	指定サウンドハンドルの再生周波数を取得する
//
//	int  nSoundHandle : 指定サウンドハンドル
//	
//==========================================================================//
int		DxLib::SoundPlayManager::dxLib_GetSoundSampleFrequency( const int  nSoundHandle )
{
	int  nSampleFreq = 0;
	nSampleFreq = DxLib::GetFrequencySoundMem( nSoundHandle );

	return ( nSampleFreq );
}

//==========================================================================//
//	サウンドハンドルの音の総時間をミリ秒単位で取得する
//
//	int  nSoundHandle		:	指定サウンドハンドル
//==========================================================================//
int		DxLib::SoundPlayManager::dxLib_GetSoundPlayingMiriTime( const int  nSoundHandle )
{
	int  nPlayingTime = 0;
	nPlayingTime = DxLib::GetSoundTotalTime( nSoundHandle );

	return ( nPlayingTime );
}

//==========================================================================//
//	サウンドシステム毎フレーム処理
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
//	システムSE再生全停止
//
//==========================================================================//
int		DxLib::SoundPlayManager::dxLib_MemSoundStop()
{
	return dxLib_MemSoundPlayGroupStop();
}

//==========================================================================//
//	再生中のシステムSEカテゴリのファイルを全て止める
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
			return ( -1 );	// 停止失敗エラー
		}
	}
	return ( 0 );
}

//==========================================================================//
//	ボリューム値の範囲内クリッピング
//	int * pVolume		:	ボリューム値
//==========================================================================//
void	DxLib::SoundPlayManager::dxLib_SoundVolumeCalcClipping( int * pVolume )
{
	if( *pVolume >= 255 ){ *pVolume = 255; }
	if( *pVolume <= 0 ){ *pVolume = 0; }
}


