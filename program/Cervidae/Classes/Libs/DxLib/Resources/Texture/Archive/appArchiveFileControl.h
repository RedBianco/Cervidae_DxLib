
#pragma once

#include "../appFileSystem.h"

//===================================================================//
//
//
//
//===================================================================//


/**
 *	@class DXライブラリ アーカイブファイル読み込み
 */ 
namespace DxLib
{
	class AppArchiveController : public AppFileSystem
	{
	public:
		AppArchiveController();
		virtual	~AppArchiveController();
	
	public:
		int						m_LoadCounter;
		std::vector< int >		m_ArchiveType;
//		std::array< int, AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_MAX >	m_ArchiveTypeList;

		std::map< int, std::string >							m_ArchiveFile;
		std::map< int, std::map< std::string, std::string >>	m_ArchiveData;
	
	public:
		// ＤＸアーカイブファイル
		char *	libArchiveFileNameCheck( const int nArchIndex );

		// ＤＸアーカイブファイルの拡張子を変更する
		int		libArchiveFileExtensChange( char * arcFileName );

		// ＤＸアーカイブファイルのパスワードを設定
		int		libArchiveFilePassSet( char * filePassCode );

		// ＤＸアーカイブファイルとフォルダが存在した場合の優先度設定( 1:フォルダを優先　 0:ＤＸアーカイブファイルを優先( デフォルト ) )
		int		libArchiveFileLoaderPrioritySetting( const int  nLoadPriority = AppLib::Resources::Archive::ARCHIVE_FILE_LOADER_PRI_ARCHIVE );

		// 指定のＤＸＡファイルを丸ごとメモリに読み込む( 戻り値  -1:エラー  0:成功 )
		int		libArchiveFileMemLoad( char * arcFileName, const int  nArchIndex, const int  nASyncLoad = false );
		int		libArchiveFileMemLoader( char * arcFileName, const int  nArchIndex );

		// 指定のＤＸＡファイルの事前読み込みが完了したかどうかを取得する( 戻り値  TRUE:完了した FALSE:まだ )
		bool	libisArchiveFileLoadIdle( char * arcFileName, const int  nArchIndex = -1 );

		// 指定のＤＸＡファイルをメモリから解放する
		int		libArchiveFileMemFree( char * arcFileName, const int  nArchIndex = -1 );
	
		// パックしたＤＸＡファイルの中に指定のファイルが存在するかどうかを調べる
		int		libArchiveFileDirectoryCheck( char * arcFileName, int  nArchIndex, char * szArchTargetFile );
	
	
	};
}

/* End appArchiveFileControl.h */