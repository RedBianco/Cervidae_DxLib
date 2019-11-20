#pragma once

///////////////////////////////////////////////////////////////////////////
//	DXライブラリ ファイル管理システム
//
//
///////////////////////////////////////////////////////////////////////////


//*******************************************************************//
/*
	define定義
*/
//*******************************************************************//


/**
 *	@class 基本このクラスは継承専用で各親クラスに継承させて使用する
 */
namespace DxLib
{
	class AppFileSystem
	{
	public:
		AppFileSystem();
		virtual	~AppFileSystem();

	public:
		typedef int	(*appLibFileCallBack) ( void *, unsigned int );

	private:
		bool	m_ASyncLoadEnable;

		std::map<int, std::string>	m_LoadList;

	public:
		// 同期、非同期設定
		void	setASyncLoadEnable( const bool flagValue ){ m_ASyncLoadEnable = flagValue; }
		bool	getASyncLoadFlag() const { return m_ASyncLoadEnable; }

	public:

		void	fileStructureClear( void );
		// ファイルアクセスシステムの基本初期化
		bool	fileLoadSystemInit( void );
		
		// ファイル読み込み(※LoadGraph使用バージョン)
		int		fileLoadAccess( const int  nDirIndex, const char * szFileName, appLibFileCallBack  fCallBack = nullptr );
		// ファイルアクセスパスの取得
		int		fileLoadGetAccessPath( const int  nDirIndex, char * szFileName, char * szGetOutPath );
		// スクリプト(.lua)ファイルアクセスパスの取得
		int		fileLoadGetScriptPath( unsigned int  unFileIndex, char * szGetOutPath );
		// ファイルサイズを取得(※読み込みは行わない)
		int		fileAccessCheckSize( const int  nDirIndex, char * szFileName );
		// ファイルサイズを取得＋読み込み機能付き
		int		fileCheckSizeLoadAccess( const int  nDirIndex, char * szFileName, int * resFileSize, appLibFileCallBack  fCallBack = nullptr );
		// 非同期読み込みを行うかどうかを設定する(( TRUE：非同期読み込み　FALSE：同期読み込み( デフォルト ) )
		int		fileSetASyncLoadAccessEnable( const int  bASyncEnable = FALSE );
		// ハンドルの非同期読み込みが完了しているかどうかを取得( TRUE:まだ完了していない  FALSE:完了している  -1:エラー )
		int		fileGetASyncLoadHandleCheck( const int  nSyLoadHandle );
		// 非同期読み込み中の処理(ハンドル)の数を取得する
		int		fileGetASyncLoadHandleNum( void );
		// ハンドルの非同期読み込み処理の戻り値を取得する
		int		fileGraphicsASyncLoadResult( const int  nHandle );
		// アーカイブファイル読み込みパス取得セット
		int		fileLoadArchivePathCheck( const int  nArchSecIndex, char * szFileName, char * returnFile, int  _ArchFileType = 1 );
		// ファイルのメモリへのロード
		int		fileMemoryRead( char * szReadFile, char * szFileName, int nDirIndex, int * pFlag = nullptr );
		// ファイル読み込み
		// ※FileRead_read使用バージョン
		int		fileBufferRead( const int  nDirIndex, char * szFileName, void * pBuffer = nullptr );
		// ファイル読み込み
		// ※FileRead_read使用バージョン
		// ※読み込んだ画像ファイルからグラフィックハンドルを作成する
		int		fileBufferReadCreateHandle( const int  nDirIndex, char * szFileName, void * pBuffer = nullptr );
	
	};
}




/* End appFileSystem.h */