#pragma once


//===================================================================//
//
//
//  Created by kashima akihiro on 2019/03/09.
//===================================================================//

/*
 *	サウンドストリーム再生管理クラス
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

		int		dxSoundEntry;		// サウンドファイル登録数
		int		dxSoundReadMode;
		int		dxSoundProc;

	public:

		// MIDIファイルの再生モード設定
		void	setMidiPlayMode( const int  nMidiMode = DX_MIDIMODE_MCI );

		// 初期化
		bool	init();

		//------------------------------------------------------------------------------//
		//	ストリーム再生
		//	処理が呼ばれる度にファイルを読み込んで→再生
		//	状況によっては読み込みにラグが出る
		//------------------------------------------------------------------------------//

		// MIDI，WAV，"MP3"ファイルを再生する
		int		streamPlay( char * playFileName, const int  SoundArchive, const int  playingType = DxLibSound::BaseInfo::SOUND_STREAM_BACKGRLOOP );
		int		streamIdPlay( const int  playFileNo, const int  SoundArchive, const int  playingType = DxLibSound::BaseInfo::SOUND_STREAM_BACKGRLOOP );
		// MIDI，WAV，"MP3"ファイルの再生停止
		int		streamPlayStop( void);
		// MIDI，WAV，"MP3"ファイルが再生中かの情報を取得する
		int		streamPlayState( void);
		// MIDI，WAV，"MP3"ファイルの再生音量を設定する(※デフォルトは半分)
		int		setPlayVolumeConfig( const int  nStreamVolume = 128 );
		// MIDI，WAV，"MP3"ファイルのサウンドハンドルを使用したストリーム再生
		int		streamHandlePlay( const int  nHandle, const int  nPlaying, const int  bPlayPosition = TRUE );

		//------------------------------------------------------------------------------//
		//	メモリに事前に読み込みんでおくタイプ
		//	乱発するとメモリを圧迫するので注意
		//	メモリーに事前読み込み → 再生
		//------------------------------------------------------------------------------//

		// 音声ファイル(WAV.MP3.Ogg)をメモリに読みこむ
		int		dxLib_SoundFileMemLoad( char * loadFileName_, const int  nSoundArchive );

		// メモリの音声ファイルがあるかチェック(soundFileName_:音声ファイルネーム)
		int		dxLib_MemSoundDataCheck( char * SysSoundFile_ );

		// 名前から登録ハンドルを探して返す
		int		dxLib_GetMemSoundDataEntryHandle( char * SysSoundFile_ );

		// 登録データ番号の登録サウンドハンドルを取得
		int		dxLib_GetMemSoundDataEntryIndex( const int  nEntryIndex );

		// メモリに読み込んだ音声ファイル(WAV.MP3.Ogg)の再生
		int		dxLib_MemSoundPlay( char * szSoundName, const int  SoundPlay = DxLibSound::BaseInfo::SOUND_STREAM_NORMALPLAY, const int isTopPosition = TRUE );
		int		dxLib_MemSoundPlay( const int  nSoundHandle, const int  SoundPlay_ = DxLibSound::BaseInfo::SOUND_STREAM_NORMALPLAY, const int isTopPosition_ = TRUE );

		// メモリに読み込んだサウンドハンドルの再生を停止する
		int		dxLib_MemSoundPlayStop( const int  nSoundHandle );

		/**
		 *	システムＳＥ関連関数群
		 */

		// システムＳＥファイルのメモリ登録
		bool	dxLib_MemEntrySystemSound( void );
		void	dxLib_MemEntrySystemSoundReregist( void );
		void	dxLib_MemEntrySystemSoundReset( void );

		// システムＳＥファイルのメモリ登録の指定リストを削除
		int		dxLib_MemEntryDeleteSystemSound( char * SysSoundFile_ );

		// メモリにロードしたシステムＳＥファイルの再生
		int		dxLib_MemPlaySystemSound( char * SysSoundFile_ );

		// メモリに読みこんだ音声データが再生中か調べる(サウンドハンドル)
		int		dxLib_MemSoundPlayStatusCheck( const int  nSoundHandle );

		// メモリに読みこんだ登録音声データが再生中か調べる(サウンドファイルネーム)
		int		dxLib_MemSoundPlayStatusCheck( char * szSoundFile );

		// メモリに読みこんだ登録音声サウンドデータを削除する(サウンドハンドル)
		int		dxLib_MemLoadSoundHandleDelete( const int  nSoundHandle );
		int		dxLib_MemLoadSoundHandleDelete( char * szSoundFile );

		// サウンドハンドルのボリュームを設定する( 0 ～ 255 )( 0：成功, -1：エラー発生 )
		int		dxLib_MemSoundFileVolumeSet( const int  nSysVolumePal, const int  nSoundHandle );
		int		dxLib_MemSoundFileVolumeSet( const int  nSysVolumePal, char * szSoundFile );

		// 指定サウンドハンドルのボリュームを取得する( 0 ～ 255 )
		int		dxLib_MemSoundFileVolumeGet( const int  nSoundHandle );
		int		dxLib_MemSoundFileVolumeGet( const int  nSoundHandle, char * szSoundFile );

		// 指定サウンドハンドルの再生周波数を設定する
		int		dxLib_SetSoundSampleFrequency( const int  nSoundHandle );
		// 指定サウンドハンドルの再生周波数を取得する
		int		dxLib_GetSoundSampleFrequency( const int  nSoundHandle );

		// サウンドハンドルの音の総時間をミリ秒単位で取得する
		int		dxLib_GetSoundPlayingMiriTime( const int  nSoundHandle );

		// サウンドシステム毎フレーム処理
		int		dxLib_SystemSound_Runtime( const int  nSoundMode = 0 );
		void	dxLib_SystemSound_ProcAtOnce( void );

		// システムSE再生停止
		int		dxLib_MemSoundStop( void );

		// 再生中のシステムSEカテゴリのファイルを全て止める
		int		dxLib_MemSoundPlayGroupStop( void );

		// ボリューム値の範囲内クリッピング
		void	dxLib_SoundVolumeCalcClipping( int * pVolume );

	};
}









/* End dxLibStreamManager.h */


