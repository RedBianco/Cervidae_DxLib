

#include "DxLib.h"
#include "../../../../Common/appCommonParam.h"
#include "../../../../Common/appErrorCode.h"
#include "../../../../Common/appProcessCode.h"
#include "../appResourcesConfig.h"
#include "appFileSystem.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//	リソースのファイルフォルダパスの管理
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////


//==============================================================================================//
// 
DxLib::AppFileSystem::AppFileSystem() :
	m_ASyncLoadEnable( false )
{
	fileStructureClear();
	fileLoadSystemInit();

	DEBUG_PRINT("FileSystem : AppFileSystem コンストラクタ\n");
}
DxLib::AppFileSystem::~AppFileSystem()
{
	DEBUG_PRINT("FileSystem : AppFileSystem デストラクタ\n");
}

//==============================================================================================//
//
void	DxLib::AppFileSystem::fileStructureClear( void )
{
	m_LoadList.clear();
}

//==============================================================================================//
// ファイルアクセスシステムの基本初期化処理
//
bool	DxLib::AppFileSystem::fileLoadSystemInit( void )
{
	// 非同期読み込み設定( TRUE：非同期読み込み	FALSE：同期読み込み( デフォルト ) )
	auto result = fileSetASyncLoadAccessEnable( AppLib::Resources::FileSystem::FILE_LIB_ASYNC_LOAD_FALSE );
#if PROJECT_DEBUG
	if( result == -1 ){
		return false;
	}
#endif

	// データリスト作成
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MAIN]		= "library";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SYSTEM]	= "system";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_BACKGROUND] = "system";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SCRIPT]	= "script";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_BGM]		= "bgm";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_VOICE]	= "voice";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SE]		= "se";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MOVIE]	= "movie";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_EFFECT]	= "effect";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_BINARY]	= "bin";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_DATABASE]	= "database";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SAVEDATA]	= "savedata";
	m_LoadList[ AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_3DMODEL]	= "3d";

	DEBUG_PRINT("FILE SYSTEM : LoadList Attribute Setting Clear." );

	return true;
}

//==============================================================================================//
// アクセスパス取得＋ファイル読み込み
//		@param		int  nDirIndex		:	フォルダINDEX
//		@param		char * szFileName	:	ファイルネーム
//		@param		dxLibFileCallBack	:	登録コールバック関数
//	@return		画像ロードハンドル
int		DxLib::AppFileSystem::fileLoadAccess( const int  nDirIndex, const char * szFileName, appLibFileCallBack  fCallBack )
{

#if PROJECT_DEBUG
	if( (nDirIndex < 0) || (nDirIndex >= AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_MAX) ){
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	char strLoadPath[256] = {};
	std::string	loadFilePath;

	//----------------------------------------------------------------------------
	// アーカイブタイプ SOUND
	// 基本パス"例)，(DxLIBFILELOAD_IMAGEPATH)/sound/voice/voice_01.wav"になる
	//----------------------------------------------------------------------------
	if( (nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_BGM)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_VOICE)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SE)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MOVIE) )
	{
//		sprintf_s( strLoadPath, AppLib::Resources::Info::RESOURCES_LOAD_DIR_PATH"/%s/%s/%s", "sound", libLoadDirectory[ nDirIndex ].pFolder, szFileName );
		sprintf_s( strLoadPath, "/%s/%s/%s", "sound", m_LoadList[ nDirIndex ].c_str(), szFileName );
	}else{
		// サウンドファイル以外
		loadFilePath = AppLib::Resources::Info::RESOURCES_LOAD_ROOT_PATH + "%s/%s";
		sprintf_s( strLoadPath, loadFilePath.c_str(), m_LoadList[ nDirIndex ].c_str(), szFileName );
	}

	// 画像をメモリに読み込む
	const auto loadHandle = DxLib::LoadGraph( strLoadPath, FALSE );
#if PROJECT_DEBUG
	if( loadHandle == -1 ){
		ERROR_PRINT("__ERROR__ : DxLib::LoadGraph HandleError [%s]\n", strLoadPath );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	// 成功なら画像LoadHandleを返す
	return loadHandle;
}

//==============================================================================================//
// ファイルアクセスパスの取得のみ
//		@param		int  nDirIndex			:	フォルダINDEX
//		@param		char * szFileName		:	ファイルネーム
//		@param		char * szGetOutPath		:	ファイルアクセスパス取得用引数
//	@return		true->成功   false->失敗
int		DxLib::AppFileSystem::fileLoadGetAccessPath( const int  nDirIndex, char * szFileName, char * szGetOutPath )
{
	char strLoadPath[256] = {};
	std::string	loadFilePath;

#if PROJECT_DEBUG
	if( (nDirIndex < 0) || (nDirIndex >= AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_MAX) ){
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	//----------------------------------------------------------------------------
	// アーカイブタイプ SOUND
	// 基本パス"例)，(DxLIBFILELOAD_IMAGEPATH)/sound/voice/voice_01.wav"になる
	//----------------------------------------------------------------------------
	if( (nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_BGM)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_VOICE)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SE)	||
		(nDirIndex == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MOVIE) )
	{
//		sprintf_s( strLoadPath, AppLib::Resources::Info::RESOURCES_LOAD_DIR_PATH"/%s/%s/%s", "sound", m_LoadList[ nDirIndex ].pFolder, szFileName );
		sprintf_s( strLoadPath, "/%s/%s/%s", "sound", m_LoadList[ nDirIndex ].c_str(), szFileName );
	}
	else{
		// サウンドファイル以外
		loadFilePath = AppLib::Resources::Info::RESOURCES_LOAD_ROOT_PATH + "%s/%s";
		sprintf_s( strLoadPath, loadFilePath.c_str(), m_LoadList[nDirIndex].c_str(), szFileName );
	}

	// ファイル名をコピーして取得
	sprintf_s( szGetOutPath, 256, strLoadPath );

	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// スクリプト(.lua)ファイルアクセスパスの取得
//		@param		char * szFileName		:	ファイルネーム
//		@param		char * szGetOutPath		:	ファイルアクセスパス取得用引数
//	@return		true->成功   false->失敗
int		DxLib::AppFileSystem::fileLoadGetScriptPath( unsigned int  unFileIndex, char * szGetOutPath )
{
	char strLoadPath[256] = {};

#if PROJECT_DEBUG
	if( unFileIndex < 0 ){
		ERROR_PRINT("__ERROR__ : AppFileSystem::libFileLoadGetScriptPath - Index[%d]\n", unFileIndex );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;		
	}
#endif

	std::string scriptLoadPath = AppLib::Resources::Info::RESOURCES_SCRIPT_LOAD_ROOT_PATH + "%03d.lua";

	// スクリプト(.lua)ファイルアクセスパスの取得
	sprintf_s( strLoadPath, scriptLoadPath.c_str(), unFileIndex );
	
	// ファイル名をコピーして取得
	sprintf_s( szGetOutPath, 256, strLoadPath );

	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// ファイルサイズを取得(※読み込みは行わない)
//		@param		int  nDirIndex			:	フォルダINDEX
//		@param		char * szFileName		:	ファイルネーム
//	@return		hLoadFileSize:ファイルサイズ  -1:エラー
int		DxLib::AppFileSystem::fileAccessCheckSize( const int  nDirIndex, char * szFileName )
{
	char strLoadPath[256] = {};

	// ファイルアクセスパスの取得
	fileLoadGetAccessPath( nDirIndex, szFileName, strLoadPath );

	// ファイルサイズを取得(TRUE:ファイルサイズ FALSE:－１:エラー発生)
	long long  hLoadFileSize = -1;
	hLoadFileSize = DxLib::FileRead_size( strLoadPath );
#if PROJECT_DEBUG
	// エラーが返ってきたらファイルが無い
	if( hLoadFileSize == -1 ){
		ERROR_PRINT("__ERROR__ : libFileAccessCheckSize Error[%s]\n", strLoadPath );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// ファイルサイズを返す
	return ( static_cast<int>( hLoadFileSize ));
}

//==============================================================================================//
// ファイルサイズを取得＋読み込み機能付き
//		@param		int		DirIndex		:	フォルダINDEX
//		@param		char *	FileName		:	ファイルネーム
//		@param		int *	resFileSize		:	ファイルサイズ取得用引数
//		@param		dxLibFileCallBack		:	登録コールバック関数
//	@return		画像のロードハンドル:成功  -1:失敗
int		DxLib::AppFileSystem::fileCheckSizeLoadAccess( const int  nDirIndex, char * szFileName, int * resFileSize, appLibFileCallBack  fCallBack )
{
	char strLoadPath[256] = {};

	// ファイルアクセスパスの取得
	fileLoadGetAccessPath( nDirIndex, szFileName, strLoadPath );

	// ファイルサイズを取得(TRUE:ファイルサイズ FALSE:－１:エラー発生)
	long long hLoadFileSize = -1;
	hLoadFileSize = DxLib::FileRead_size( strLoadPath );
#if PROJECT_DEBUG
	if( hLoadFileSize == -1 ){
		ERROR_PRINT("__ERROR__ : DxLib::FileRead_size : libFileCheckSizeLoadAccess\n");
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// ファイルサイズをセット
	*resFileSize = static_cast<int>( hLoadFileSize );

	// 読み込み作業
	int hFileResult = -1;
	hFileResult = DxLib::LoadGraph( strLoadPath ); // 画像をメモリに読み込む
#if PROJECT_DEBUG
	if( hFileResult == -1 ){
		ERROR_PRINT("__ERROR__ : DxLib::LoadGraph Error[%s]\n", strLoadPath );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// 問題無く成功なら画像LoadHandleを返す
	return ( hFileResult );
}

//==============================================================================================//
// 非同期読み込みを行うかどうかを設定する(( TRUE：非同期読み込み　FALSE：同期読み込み( デフォルト ) )
//	※( 非同期読み込みに対応している関数のみ有効 )( TRUE:非同期読み込みを行う  FALSE:非同期読み込みを行わない( デフォルト ) )
//		@param		int  bASyncEnable		:	読み込みフラグ
//	@return
//		０：成功
//	  －１：エラー発生
int		DxLib::AppFileSystem::fileSetASyncLoadAccessEnable( const int  bASyncEnable )
{
	int hASyncLoadEnable = -1;
	hASyncLoadEnable = DxLib::SetUseASyncLoadFlag( bASyncEnable );
#if PROJECT_DEBUG
	if( hASyncLoadEnable == -1 ){
		ERROR_PRINT("__ERROR__ : ASyncLoadEnable : Result ERROR\n");
		setASyncLoadEnable( false );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	setASyncLoadEnable( true );

	// 設定成功(非同期化)
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// ハンドルの非同期読み込みが完了しているかどうかを取得
//		@param		int  iSyLoadHandle	:	ロードハンドル
//	@return
//		TRUE	:	非同期読み込み中
//		FALSE	:	非同期読み込みは終了している
//			-1	:	エラー
int		DxLib::AppFileSystem::fileGetASyncLoadHandleCheck( const int  nSyLoadHandle )
{
	int hLoadResult = -1;
	hLoadResult = DxLib::CheckHandleASyncLoad( nSyLoadHandle );
#if PROJECT_DEBUG
	if( hLoadResult == -1 ){
		ERROR_PRINT("__ERROR__ : dxLib_FileGetASyncLoadHandleCheck [%d]\n", nSyLoadHandle );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	if( hLoadResult == TRUE )
	{
		return ( AppLib::Resources::FileSystem::FILE_LIB_ASYNC_LOAD_TRUE ); // まだ非同期読み込み中
	}
	return ( AppLib::Resources::FileSystem::FILE_LIB_ASYNC_LOAD_FALSE ); // 非同期読み込み終了
}

//==============================================================================================//
// 非同期読み込み中の処理(ハンドル)の数を取得する
//	@return
//		0:読み込み無し  0以外:実行している非同期読み込み処理の数
//	@comment
//		非同期処理が有効になってる時に意味がある
int		DxLib::AppFileSystem::fileGetASyncLoadHandleNum( void )
{
#if PROJECT_DEBUG
	if( !getASyncLoadFlag() ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
#endif

	const int mLoadNum = DxLib::GetASyncLoadNum();
	if( mLoadNum != 0 ){
		return ( mLoadNum );// 読み込み処理実行中なので読み込み中処理の数を返す
	}
	return ( AppLib::Resources::FileSystem::FILE_LIB_ASYNC_LOAD_FALSE );  // 実行している読み込みは無い
}

//==============================================================================================//
// ハンドルの非同期読み込み処理の戻り値を取得する
int		DxLib::AppFileSystem::fileGraphicsASyncLoadResult( const int  nHandle )
{
	if( !getASyncLoadFlag() ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }

	int result = -1;
	result = DxLib::GetHandleASyncLoadResult( nHandle );

#if PROJECT_DEBUG
	if( result < 0 ){
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	return ( result );
}

//==============================================================================================//
// アーカイブファイル読み込みパス取得セット
//		@param		int  nArchSecIndex		:	パックファイルID
//		@param		char * szFileName		:	.DXAファイルの中を読み込む場合のファイル名
//		@param		char * returnFile		:	取得用バッファ
//		@param		int  _ArchFileType		:	アーカイブ読み込みタイプ
//	@return
//			0->成功
int		DxLib::AppFileSystem::fileLoadArchivePathCheck( const int  nArchSecIndex, char * szFileName, char * returnFile, int  _ArchFileType )
{
	char charLoadPath[256] = {};
	
	// アーカイブファイル自体を見るか、アーカイブファイルの中のファイルを見るか
	// ※ DxLIB_ARCHIVE_FILE_ROOTPATH -> "D:/project/Application/PC_01/GameImage/bin"
	if( _ArchFileType == AppLib::Resources::Archive::ARCHIVE_FILE_LOADER_DXA )
	{
//		sprintf_s( charLoadPath, DxLIB_ARCHIVE_FILE_ROOTPATH"/%s", dxLib_ArchiveFileNameCheck( nArchSecIndex ));
	}
	else
	{
//		sprintf_s( charLoadPath, DxLIB_ARCHIVE_FILE_ROOTPATH"/%s/%s", dxLib_ArchiveFileNameCheck( nArchSecIndex ), szFileName );
	}
	
	// ファイル名をコピーして取得
	sprintf_s( returnFile, 256, charLoadPath );
	
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// ファイルのメモリへのロード
//		@param		char *	szReadFile		:	
//		@param		char *	szFileName		:	
//		@param		int		nDirIndex		:	
//		@param		int *	pFlag			:	
//	@return		0->成功
int		DxLib::AppFileSystem::fileMemoryRead( char * szReadFile, char * szFileName, int nDirIndex, int * pFlag )
{
	void *	pFileBuff = nullptr;
	int		fileSize_ = 0;
	int		fileHandle_ = 0;

	// ファイルのサイズを得る
	fileSize_ = fileAccessCheckSize( nDirIndex, szReadFile );
#if PROJECT_DEBUG
	if( fileSize_ < 0 ){
		ERROR_PRINT("__ERROR__ : FileSiza None dxLib_MemoryFileRead\n");
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// ファイルを格納するメモリ領域の確保
	pFileBuff = malloc( fileSize_ );
	
	// ファイルを開く
	fileHandle_ = DX_FILE_OPEN( szFileName );
	if( fileHandle_ == -1 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// ファイルを丸ごとメモリに読み込む(ファイルバッファ,読み出すサイズ(バイト),ファイルハンドル)
	DX_FILE_READ( pFileBuff, fileSize_, fileHandle_ );
	
	// ファイルを閉じる
	DX_FILE_CLOSE( fileHandle_ );

	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// ファイル読み込み
//	※FileRead_read使用バージョン
//	<<Comment>>
//		用途は主に閲覧可能なファイル形式のままディスクに画像データを保存しておきたくない時等に使用
//		※拡張子無しファイルにリネームしたテクスチャファイル等を読み込む時など
//	<<注意>>
int		DxLib::AppFileSystem::fileBufferRead( const int  nDirIndex, char * szFileName, void * pBuffer )
{
	LONGLONG	nFileSize_ = -1;
	void *		pFileBuff = nullptr;
	int			nFileHandle = 0;

	char strLoadPath[256] = {};

	// ファイルパスチェック
	fileLoadGetAccessPath( nDirIndex, szFileName, strLoadPath );

	// ファイルのサイズを得る
	nFileSize_ = DX_FILE_SIZE( strLoadPath );
	if( nFileSize_ < 0 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// ファイルを格納するメモリ領域の確保
	pFileBuff = malloc( (int)nFileSize_ );
	
	// 指定ファイルを開く
	nFileHandle = DX_FILE_OPEN( strLoadPath );
	if( nFileSize_ == -1 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// ファイルを丸ごとメモリに読み込む
	DX_FILE_READ( pFileBuff, (int)nFileSize_, nFileHandle );
	
	// ファイルを閉じる
	DX_FILE_CLOSE( nFileHandle );
	
	// メモリを解放する前にコピー
	pBuffer = pFileBuff;
	
	// メモリの解放
	free( pFileBuff );

	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//==============================================================================================//
// ファイル読み込み
// ※FileRead_read使用バージョン
// ※読み込んだ画像ファイルからグラフィックハンドルを作成する
//	<<Comment>>
//		用途は主に閲覧可能なファイル形式のままディスクに画像データを保存しておきたくない時等に使用
//	<<注意>>
//		この関数で作成れたグラフィックハンドルはフルスクリーン画面からタスク切り替え等で
//		一時的にデスクトップ画面に戻った場合再度フルスクリーン画面になった時に画像は自動的に復元されません
//		この場合[ SetRestoreGraphCallback ]関数で登録できる画像復元関数で画像を再度読み込む必要があります
int		DxLib::AppFileSystem::fileBufferReadCreateHandle( const int  nDirIndex, char * szFileName, void * pBuffer )
{
	LONGLONG	nFileSize_ = -1;
	void *		pFileBuff = nullptr;
	int			nFileHandle = 0;
	int			nGrHandle = 0;
	// LONGLONGからintにキャストする

	char strLoadPath[256] = {};

	// ファイルパスチェック
	fileLoadGetAccessPath( nDirIndex, szFileName, strLoadPath);

	// ファイルのサイズを得る
	nFileSize_ = DX_FILE_SIZE( strLoadPath );
	if( nFileSize_ < 0 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// ファイルを格納するメモリ領域の確保
	pFileBuff = malloc( (int)nFileSize_ );
	
	// 指定ファイルを開く
	nFileHandle = DX_FILE_OPEN( strLoadPath );
	if( nFileHandle == -1 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// ファイルを丸ごとメモリに読み込む
	DX_FILE_READ( pFileBuff, (int)nFileSize_, nFileHandle );
	
	// ファイルを閉じる
	DX_FILE_CLOSE( nFileHandle );
	
	// グラフィックハンドルの作成
	// メモリ上の画像イメージからグラフィックハンドルを作成する
	nGrHandle = DxLib::CreateGraphFromMem( pFileBuff, (int)nFileSize_ );
	if( nGrHandle == -1 ){ return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
	
	// メモリを解放する前にコピー
	pBuffer = pFileBuff;
	
	// メモリの解放
	free( pFileBuff );
	
	// グラフィックハンドルを返す
	return ( nGrHandle );
}














