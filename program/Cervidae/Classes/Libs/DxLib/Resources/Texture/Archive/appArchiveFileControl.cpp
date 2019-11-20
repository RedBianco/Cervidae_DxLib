
#include "DxLib.h"
#include "../../../../../Common/appCommonParam.h"
#include "../../../../../Common/appErrorCode.h"
#include "../../../../../Common/appProcessCode.h"
#include "../../appResourcesConfig.h"
#include "appArchiveFileControl.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//	アーカイブファイルリソース管理用クラス
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *	コンストラクタ
 */
DxLib::AppArchiveController::AppArchiveController() :
	m_LoadCounter( 0 )
{
	m_ArchiveType.assign( AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_MAX, 
						  AppLib::Resources::Archive::eARCHIVE_FILETYPE_NONE );

	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_NONE,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_RESOURCES,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_SCRIPT, ""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_BGM,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_VOICE,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_SE,		""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_MOVIE,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_EFFECT, ""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_SAVEDATA,	""));
	m_ArchiveFile.insert( std::make_pair( AppLib::Resources::Archive::eARCHIVE_FILETYPE_MODEL,	""));

#if 0
	m_ArchiveData.insert( 0, { std::make_pair( AppLib::Resources::Command::eARCHIVE_FILETYPE_NONE, "" ) });
#endif
	DEBUG_PRINT("Archive : AppArchiveController コンストラクタ\n");
}
DxLib::AppArchiveController::~AppArchiveController()
{
	DEBUG_PRINT("Archive : AppArchiveController デストラクタ\n");
}

//================================================================================================
//	@title	
//	@param	int nArchIndex
char *	DxLib::AppArchiveController::libArchiveFileNameCheck( const int nArchIndex )
{
#if PROJECT_DEBUG
	if( (nArchIndex < 0) || 
		(nArchIndex >= AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_MAX) ){
		return NULL;
	}
#endif


	DEBUG_PRINT("__LOG__ : \n" );
	return NULL;
}

//================================================================================================
//	@title	ＤＸアーカイブファイルの拡張子を変更する
//	@param	char * arcFileName
int		DxLib::AppArchiveController::libArchiveFileExtensChange( char * arcFileName )
{
	auto result = DxLib::SetDXArchiveExtension( arcFileName );
#if PROJECT_DEBUG
	if( result == -1 ){
		ERROR_PRINT("__ERROR__ : libArchiveFileExtensChange [%s]\n", arcFileName );
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR ); // エラー処理
	}
#endif
	return ( result);
}

//================================================================================================
//	@title	ＤＸアーカイブファイルのパスワードを設定
//	@param	char * filePassCode
int		DxLib::AppArchiveController::libArchiveFilePassSet( char * filePassCode )
{
	auto result = DxLib::SetDXArchiveKeyString( filePassCode );
#if PROJECT_DEBUG
	if( result == -1 ){
		ERROR_PRINT("__ERROR__ : libArchiveFilePassSet [%s]\n", filePassCode );
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR ); // エラー処理
	}
#endif
	return ( result);
}

//================================================================================================
//	@title	ＤＸアーカイブファイルとフォルダが存在した場合の優先度設定
//	( 1:フォルダを優先　 0:ＤＸアーカイブファイルを優先( デフォルト ) )
//	@param	int nLoadPriority
int		DxLib::AppArchiveController::libArchiveFileLoaderPrioritySetting( const int nLoadPriority )
{
	auto result = DxLib::SetDXArchivePriority( nLoadPriority );
#if PROJECT_DEBUG
	if( result == -1 ){
		ERROR_PRINT("__ERROR__ : libArchiveFileLoaderPrioritySetting\n");
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR ); // エラー処理
	}
#endif
	return ( result); // 成功
}

//================================================================================================
//	指定のＤＸＡファイルを丸ごとメモリに読み込む( 戻り値  -1:エラー  0:成功 )
//		@param	char * szArchFileName	:	ファイル名
//		@param	int  nArchIndex			:	アーカイブインデックス
//		@param	int  nASyncLoad			:	同期読み込み設定(FALSE:デフォルト)
//	<<戻り値>>
//		0 : 成功
//	   -1 : 失敗(エラー)
int		DxLib::AppArchiveController::libArchiveFileMemLoad( char * arcFileName, const int  nArchIndex, const int  nASyncLoad )
{
	char strArchPath[256] = {};

	// アーカイブファイルの読み込みパスを取得
//	dxLib_ArchiveFileLoadPathCheck( nArchIndex, arcFileName, strArchPath, DxLIB_ARCHIVE_LOADER_ARCHIVE );
	fileLoadArchivePathCheck( nArchIndex, arcFileName, strArchPath, AppLib::Resources::Archive::ARCHIVE_FILE_LOADER_PRI_ARCHIVE );
	
	// ファイルロード
	auto result = DxLib::DXArchivePreLoad( strArchPath, nASyncLoad );
#if PROJECT_DEBUG
	if( result == -1 ){
		ERROR_PRINT("__ERROR__ : dxLib_ArchiveFileMemLoad\n");
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR ); // エラー処理
	}
#endif

	m_ArchiveType.push_back( nArchIndex );

	m_LoadCounter ++;

	return ( result );
}
int		DxLib::AppArchiveController::libArchiveFileMemLoader( char * arcFileName, const int  nArchIndex )
{
	return libArchiveFileMemLoad( arcFileName, nArchIndex, FALSE );
}

//================================================================================================
// 指定のＤＸＡファイルの事前読み込みが完了したかどうかを取得する( 戻り値  TRUE:完了した FALSE:まだ )
//		@param		char * szArchFileName		:	ファイルパス
//		@param		int  nArchIndex				:	アーカイブインデックス
//	<<戻り値>>
//		TRUE  : 成功
//		FALSE : 失敗(まだ)
bool	DxLib::AppArchiveController::libisArchiveFileLoadIdle( char * arcFileName, const int  nArchIndex )
{
	// 読み込みが完了したか
	auto result = DxLib::DXArchiveCheckIdle( arcFileName );
	if( result == 0 ){
		return true;	// 読み込み成功
	}
	return false;
}

//================================================================================================
// 指定のＤＸＡファイルをメモリから解放する
//		@param		char * szArchFileName	:	ファイルパス
//		@param		int  nArchIndex			:	アーカイブインデックス
//	<<戻り値>>
//		0 : 成功
//	   -1 : 失敗(エラー)
int		DxLib::AppArchiveController::libArchiveFileMemFree( char * arcFileName, const int  nArchIndex )
{
	//	メモリから解放
	auto result = DxLib::DXArchiveRelease( arcFileName );
#if PROJECT_DEBUG
	if( result == -1 ){
		ERROR_PRINT("__ERROR__ : dxLib_ArchiveFileMemFree\n");
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR );	// エラー処理
	}
#endif

	m_LoadCounter --;
	
	return ( result );
}
//================================================================================================
// パックしたＤＸＡファイルの中に指定のファイルが存在するかどうかを調べる
//	※szArchFileTarget はＤＸＡファイルをカレントフォルダとした場合のパス
//		@param		char * szArchFileName		:	ファイルパス
//		@param		int  nArchIndex				:	アーカイブインデックス
//		@param		char * szArchFileTarget		:	
//	<<戻り値>>
//		1 : ファイルがある
//		0 : 無い
//	   -1 : 失敗(エラー)
int		DxLib::AppArchiveController::libArchiveFileDirectoryCheck( char * arcFileName, int  nArchIndex, char * szArchTargetFile )
{
	auto result = DxLib::DXArchiveCheckFile( arcFileName, szArchTargetFile );
#if PROJECT_DEBUG
	if( !result ){
		ERROR_PRINT("__ERROR__ : dxLib_ArchiveFileDirectoryCheck \n");
		return ( App::FileProcess::eFILE_RESULT_CODE_ERROR );	// エラー処理
	}
#endif
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;	// ファイルが存在する
}

