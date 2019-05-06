
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
 *	コンストラクタ
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
	// ※基本MIDIは使用せず全てmp3形式
	// DX_MIDIMODE_DM  : DirectMusic による演奏
	// DX_MIDIMODE_MCI : MCIによる再生(デフォルト)
	// MCIはMIDIファイルが再生されるクオリティは各パソコンにインストールされているMIDIデバイスに依存します
	int result_ = -1;
	result_ = DxLib::SelectMidiMode( nMidiMode );
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : StreamPlayManager::setMidiPlayMode\n"); // 設定エラー
	}
}

// 
bool	DxLib::StreamPlayManager::initialize()
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
int		DxLib::StreamPlayManager::streamPlay( char * playFileName, const int  SoundArchive, const int  playingType )
{
	char strStrmPath[ 256 ] = {};

	// ファイルパス取得
//	dxLib_FileLoadGetAccessPath( SoundArchive, playFileName, strStrmPath );

	// ストリーム再生処理
	int hStreamPlay = -1;
	hStreamPlay = DxLib::PlayMusic( strStrmPath, playingType );
	if( hStreamPlay == -1 )
	{
		ERROR_PRINT("__ERROR__ : StreamPlayManager::streamPlay[%s]\n", playFileName );// 再生失敗
		return ( -1); // ERROR
	}
	return 0;
}
int		DxLib::StreamPlayManager::streamIdPlay( const int  playFileNo, const int  SoundArchive, const int  PlayingType )
{
	//-------------------------------------------------------------------------------------------------------
	// TYPE②：ファイルの番号のみ指定で自動でネームを設定するVer
	// (※全てのファイル名に規則性を持たせて設定してる前提(例,1_sound.wav/2_sound.wav/3_sound.wavの様に)
	//-------------------------------------------------------------------------------------------------------
	char strStrmPath[ 256] = {};
	char strFileName[ 256] = {};

	// ファイルネーム作成
	sprintf_s( strFileName, 256, "%d_Sound.mp3", playFileNo );

	// ファイルパス取得
//	dxLib_FileLoadGetAccessPath( SoundArchive, strFileName, strStrmPath );

	// ストリーム再生処理
	int playResult = -1;
	playResult = DxLib::PlayMusic( strStrmPath, PlayingType );
	if( playResult == -1 )
	{
		ERROR_PRINT("__ERROR__ : StreamPlayManager::streamIdPlay[%s]\n", strFileName );// 再生失敗
		return ( -1 ); // ERROR
	}

	return 0;
}

//==========================================================================//
// MIDI，WAV，"MP3"ファイルの再生停止
// 	  ０：成功
//	－１：エラー発生
int		DxLib::StreamPlayManager::streamPlayStop()
{
	// PlayMusic関数で開始した再生を停止します
	const int result_ = DxLib::StopMusic();
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : StreamPlayManager::streamPlayStop()\n");
		return ( -1 );	// Error
	}
	// 処理成功
	return 0;
}

//==========================================================================//
// MIDI，WAV，"MP3"ファイルが再生中かの情報を取得する
// ※PlayMusic関数で開始したMIDI又はＭＰ３演奏(再生)がまだ続いているか情報を得ます。
// 戻り値として０が返ってくれば演奏(再生)は終了しており、
// １が 返ってくれば演奏(再生)はまだ続いていると言うことになります。
// << 戻り値 >>
//		０：演奏(再生)中ではない
//		１：演奏(再生)中
//	　－１：エラー
int		DxLib::StreamPlayManager::streamPlayState()
{
	// PlayMusic関数で開始した再生がまだ続いているかチェック
	const int	result_ = DxLib::CheckMusic();
	if( result_ == -1 )
	{
		ERROR_PRINT("__ERROR__ : StreamPlayManager::dtreamPlayState()\n");
		return ( -1 ); // Error
	}
	return ( result_ ); // Errorじゃないなら情報を返す
}

//==========================================================================//
// MIDI，WAV，"MP3"ファイルの再生音量を設定する(※デフォルトは半分)
// int  StreamVolume ：音量(0～255)
// << 戻り値 >>
//		０：成功
//	　－１：エラー発生
// ※PlayMusic関数 で開始した演奏の音量を設定します０が無音、２５５が最大音量(デフォルト)
// ※ＭＣＩを使用したＭＩＤＩ演奏の場合は音量を変更は不可
int		DxLib::StreamPlayManager::setPlayVolumeConfig( const int  nStreamVolume )
{
	if( nStreamVolume < 0 || nStreamVolume > 255 ){
		return ( -1 );// Error ボリューム値設定エラー
	}
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
// MIDI，WAV，"MP3"ファイルのサウンドハンドルを使用したストリーム再生
int		DxLib::StreamPlayManager::streamHandlePlay( const int  nHandle, const int  nPlaying, const int  bPlayPosition )
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


//==========================================================================//
//	メモリの音声ファイルがあるかチェック
//		char * SysSoundFile_	:	サウンドファイル名
//	<戻り値>
//		失敗					:	DXLSOUND_MEMORY_MAX


//==========================================================================//
//	名前から登録ハンドルを探して返す
//		char * SysSoundFile_	:	サウンドファイル名
//	@return		サウンドハンドル


//==========================================================================//
// 	データ登録番号の登録サウンドハンドルを取得
//		int  nEntryIndex		:	データ登録番号


//==========================================================================//
//	メモリに読み込んだ音声ファイル(WAV.MP3.Ogg)の再生
//		szSoundName		： 再生する音の識別番号（サウンドハンドル）
//		SoundPlay		： 再生形式
//							DX_PLAYTYPE_NORMAL	:	ノーマル再生
//							DX_PLAYTYPE_BACK	:	バックグラウンド再生
//							DX_PLAYTYPE_LOOP	:	ループ再生
//		isTopPosition	： 再生位置を音データの先頭に移動するかどうか
//							( TRUE：移動する（デフォルト）　FALSE：移動しない )
//	<<戻り値>>
//		0->再生成功		-1->再生失敗


//==========================================================================//
//


//==========================================================================//
//





