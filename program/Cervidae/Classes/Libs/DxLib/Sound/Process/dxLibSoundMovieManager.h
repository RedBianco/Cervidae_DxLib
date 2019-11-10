#pragma once


//===================================================================//
//	dxLibSoundMovieManager.h
//
//  Created by kashima akihiro on 2019/05/07.
//===================================================================//



/*
 *	@class	
 */
namespace DxLib
{
	class AppMoviePlayManager
	{
	public:
		AppMoviePlayManager();
		virtual ~AppMoviePlayManager();

	public:

		// ムービーファイル再生システムの基本初期化
		bool	dxLib_SofdecSystemInit();
		int		dxLib_isSofdecFilePlayHandle( char * szSofdecName );
		int		dxLib_SofdecFilePlay( char * SofdecName, int  nPlayExRate = 1, int  nPlayType = DX_MOVIEPLAYTYPE_BCANCEL, int  nPlayVolume = 255 );
		int		dxLib_SofdecFileGraphLoadReady( char * szSofdecName );
		int		dxLib_SofdecFileGraphLoadPlay( char * szSofdecName );
		int		dxLib_SofdecFileGraphHandlePlay( const int  nSofdecHandle );
		int		dxLib_SofdecGraphFileDrawMain( const int  nSofdecHandle, const int  mvPointX, const int  mvPointY, const int  mvGraphW, const int  mvGraphH, const int  mvGraphTransFlag = true, const int  mvVolume = 255 );
		int		dxLib_SofdecGraphFileDraw( const int  nSofdecHandle, const int  mvGraphW, const int  mvGraphH, const int  mvVolume = 255 );
		int		dxLib_SofdecGraphFileDraw( const int  nSofdecHandle, const int  mvGraphW, const int  mvGraphH, const int  mvGraphTransFlag, const int  mvVolume );
		int		dxLib_SofdecFileGraphPlayPause( const int  nSofdecHandle );
		int		dxLib_SofdecFileGraphPlayReStart( const int  nSofdecHandle );
		int		dxLib_SofdecGraphFileSetVolume( const int  nSetVolume, const int  nSofdecHandle );
		int		dxLib_SofdecisGraphPlayState( const int  nSofdecHandle );
		long long	dxLib_GetSofdecPlayOneFrameTime( const int  nSofdecHandle );
		int		dxLib_isSofdecPlayRunStatus( const int  nSofdecHandle );
		int		dxLib_SofdecLoadHandleReacquisit( int * pReLoadHandle, char * pLoadSofdec );
		int		dxLib_SofdecPlaySeekTimeReset( const int  nSofdecHandle );
		bool	dxLib_SofdecFileFormatCheck( char * szSofdecName );
		int		dxLib_SofdecFileExist( char * szFile );
	};
}


/* End dxLibSoundMovieManager.h */


