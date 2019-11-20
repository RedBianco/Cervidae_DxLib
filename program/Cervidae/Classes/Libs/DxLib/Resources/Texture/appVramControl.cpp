
#include "DxLib.h"
#include "../../../../Common/appCommonParam.h"
#include "../../../../Common/appErrorCode.h"
#include "../../../../Common/appProcessCode.h"
#include "../appResourcesConfig.h"
#include "appFileSystem.h"
#include "appVramContainer.h"
#include "appVramConfig.h"
#include "appVramControl.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
/*
	DXライブラリ	VRAM管理システム
	※読み込み可能な画像形式は[ BMP, JPEG, PNG, DDS, ARGB, TGA ]の６種類

	LastUpdate : 2019.04.23
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

/*
	エラー C2447 '{': 対応する関数ヘッダーがありません(旧形式の仮引数リスト ? )
*/
/*
	vectorは間の要素を削除すると以降の要素が前に順にズレる（※数が多いと処理時間が掛かるので注意）
*/

DxLib::AppVramController::AppVramController()
{
	m_FileContainer.clear();
}
DxLib::AppVramController::~AppVramController()
{
}


//================================================================================================
// VRAM管理システム基本初期化処理
bool	DxLib::AppVramController::gpVramFileSystemInit()
{
#if defined( PROJECT_DEBUG )
	DEBUG_PRINT("\n");
#endif

	return false;
}

//================================================================================================
// VRAM管理システム終了処理
void	DxLib::AppVramController::gpVramFileSystemExit()
{
#if defined( PROJECT_DEBUG )
	DEBUG_PRINT("\n");
#endif
}

//================================================================================================
// VRAM管理システムランタイム
void	DxLib::AppVramController::gpVramFileRuntime()
{
#if defined( PROJECT_DEBUG )
	DEBUG_PRINT("VRAM INFO : 読み込み数\n");
#endif
}

//================================================================================================
// グラフィックファイルのメモリへのロード
//	<<引数>>
//		@param		int		archive_type	:	アーカイブタイプ
//		@param		char *	vvfile_name		:	画像ファイルネーム
//		@param		int		vvram_type		:	VRAMタイプ
//	<<戻り値>>
//		－１	  :  エラー発生
//		－１以外  :  グラフィックハンドル
int		DxLib::AppVramController::gpVramFileVramLoad( const int archive_type, const char * vvfile_name, int  vvram_type )
{
	// ファイル読み込み
	const int loadHandle = fileLoadAccess( archive_type, vvfile_name, NULL );
#if defined( PROJECT_DEBUG )
	if( loadHandle == -1 ){
		ERROR_PRINT("__ERROR__ : gpVramFileVramLoad FileResult\n");
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
	}
#endif

	// ２重読み込みの防止
	const int fileExist = gpVramLoadFileHandleGet( vvfile_name );
	if( fileExist > 0 ){ return ( App::FileVram::eRESULT_CODE_ERROR_DOUBLE_LOADING ); }
	
	/**
	 * 新規読み込みの情報設定
	 */
	VramFileContainer	fileData_;
	// 読み込みカウント
	fileData_.vv_VramCount = AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED;
	// ファイルハンドル
	fileData_.vv_FileHandle = loadHandle;
	// ファイルネーム
	fileData_.vv_TextureName = vvfile_name;

	// 読み込みサイズバッファ
	fileData_.vv_ReadBuff = NULL;

	// VRAMタイプ
	fileData_.vv_VramType = vvram_type;

	// テクスチャのサイズ情報
	int	_TexWidth = 0, _TexHeight = 0;
	auto result = gpVramLoadFileGetSize( fileData_.vv_FileHandle, &_TexWidth, &_TexHeight );
	fileData_.vv_WIDTH = _TexWidth;
	fileData_.vv_HEIGHT = _TexHeight;

	// 読み込み数
    DEBUG_PRINT("[GRAPH] ID[%d] VramLoad : FileName[\"%s\"]\n", fileExist, vvfile_name );
    DEBUG_PRINT("[GRAPH] ID[%d] VramLoadSize : WIDTH[%d] HEIGHT[%d]\n", fileExist, fileData_.vv_WIDTH, fileData_.vv_HEIGHT );
	DEBUG_PRINT("[GRAPH] ID[%d] VramType : vv_VramType[%d], vp_LoadCount[%d]\n", fileExist, fileData_.vv_VramType, 0 );

	m_FileContainer.push_back( fileData_ );

	// 画像ロードに成功したらグラフィックハンドルが返る
	return loadHandle;
}

//================================================================================================
//	指定のグラフィックをメモリ上から削除する
//		@param		int		vram_type		:	VRAMタイプ
//		@param		char *	vvfile_name		:	グラフィックネーム
//	<<戻り値>>
//		0	:	バッファクリアした
int		DxLib::AppVramController::gpVramBuffLoadFileFormat( const int vram_type, char * vvfile_name )
{
	// 名前からファイルハンドルを求めてそれを使用
	int fileHandle = -1;
//	fileHandle = _getGraphicTexVramLoadHandle( vram_type, vvfile_name );
#if defined( PROJECT_DEBUG )
	if( fileHandle < 0 ){ return ( App::FileVram::eRESULT_CODE_ERROR_FAILED ); }
#endif
	// vector構造から削除する
	gpVramEntryDataClear( vvfile_name );

	// ファイルハンドルを削除
	return gpVramBuffLoadFileFormat( fileHandle );
}
// ※ハンドル指定関数ではvector構造削除クリアはされないので直接呼ぶのは禁止※
int		DxLib::AppVramController::gpVramBuffLoadFileFormat( const int file_handle )
{
	// 指定のファイルハンドルを削除する
	const int formatResult = DxLib::DeleteGraph( file_handle );
#if defined( PROJECT_DEBUG )
	if( formatResult == -1 ){
		ERROR_PRINT("__ERROR__ : VramDelete : gpVramBuffLoadFileFormat( Handle[%d] )\n", formatResult );	// 削除失敗
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
	}
#endif
	
	return ( App::FileProcess::eFILE_RESULT_CODE_SUCCESS );
}

//================================================================================================
// 	メモリにある画像を全て削除
// 	※LoadDivGraph、LoadGraph、MakeGraph等で読みこんだ（作成した） グラフィックをすべて削除し、初期化します。
// 	　これによって占有されていたメモリ領域を開放することができます。
// 	@return		0->成功		-1->失敗
int		DxLib::AppVramController::gpVramLoadBuffFormatALL()
{
	// 読みこんだグラフィックデータをすべて削除する
	const int formatResult = DxLib::InitGraph();
#if defined( PROJECT_DEBUG )
	if( formatResult == -1 ){
		ERROR_PRINT("__ERROR__ : DeleteError : dxLib_gpVramLoadBuffFormatALL()\n");	// 削除失敗
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
	}
#endif
    
	// 成功
	return ( App::FileProcess::eFILE_RESULT_CODE_SUCCESS );
}

//================================================================================================
//	メモリにある指定グラフィックのサイズを得る
//	※Atlas形式で複数の絵を一枚にしている場合はその一枚のサイズを取るので中のテクスチャ個別で取ることは出来ない
//	引数	int		vram_type		:	VRAMタイプ
//			char *	vvfile_name		:	画像ファイルネーム
//			int *	pFileRectW		:	グラフィックの幅を保存するint型変数のポインタ
//			int *	pFileRectH		:	グラフィックの高さを保存するint型変数のポインタ
//	<<戻り値>>
//			  ０ :	成功
//			－１ :	エラー発生
int		DxLib::AppVramController::gpVramLoadFileGetSize( const int vram_type, char * vvfile_name, int * pFileRectW, int * pFileRectH )
{
	// VRAMタイプから
#if defined( PROJECT_DEBUG )
	if( vram_type >= AppLib::Resources::Parameter::ENUM_GRAPHIC_FILE_ENTRY_TYPE_MAX ){
		ERROR_PRINT("__ERROR__ : LoadFileGetSize VRAM_GPTYPE_MAX Over !\n" );
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
	}
#endif

	// VRAMタイプと名前からグラフィックのロードハンドルを取得
	int fileHandle = -1;
//	fileHandle = _getGraphicTexVramLoadHandle( vram_type, vvfile_name );
#if defined( PROJECT_DEBUG )
	if( fileHandle == -1 ){
		// 登録してない＋メモリに上がってない
		ERROR_PRINT("__ERROR__ : LoadFileGetSize Filed Name[%s]\n", vvfile_name );
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
	}
#endif

	return gpVramLoadFileGetSize( fileHandle, pFileRectW, pFileRectH );
}
int		DxLib::AppVramController::gpVramLoadFileGetSize( const int file_handle, int * pFileRectW, int * pFileRectH )
{
	// 指定ハンドルで調べるバージョン
	int sizeCheck = -1;
	// サイズチェック
	sizeCheck = DxLib::GetGraphSize( file_handle, pFileRectW, pFileRectH );
#if defined( PROJECT_DEBUG )
	if( sizeCheck == -1 ){
		ERROR_PRINT("__ERROR__ : gpVramLoadFileGetSize Handle [%d]\n", file_handle );
		return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );	// ファイル取得失敗
	}
	if( pFileRectW < 0 || pFileRectH < 0 ){
		ERROR_PRINT("__ERROR__ : gpVramLoadFileGetSize RectW[%d] RectH[%d]\n", pFileRectW, pFileRectH );
		return ( App::FileVram::eRESULT_CODE_ERROR_SIZECHECK );	// テクスチャサイズ取得失敗
	}
#endif

	return ( App::FileProcess::eFILE_RESULT_CODE_SUCCESS );
}



//================================================================================================
// 名前からVRAMファイルハンドルを取得
//	※dxLib_gpVramFileVramLoadを呼んだ後で無いと機能しない
//		@param		char * vvfile_name		:	画像ファイルネーム
//	@return		成功->グラフィックのロードハンドル	-1->失敗
int		DxLib::AppVramController::gpVramLoadFileHandleGet( const char * vvfile_name )
{
	const int fileLength = 0;
	{
		std::vector< DxLib::VramFileContainer>::const_iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr ) {
			if ( itr != m_FileContainer.end() ) {
				// 名前が一致するか
				if( strcmp( itr->vv_TextureName.c_str(), vvfile_name ) == 0 ) {
					// (gpVramFileVramLoad)が呼ばれているか調べる
					if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED ) {
						// 存在すればロードハンドルを返す
						return itr->vv_FileHandle;
					}
				}
			}
		}
	}

	ERROR_PRINT("__ERROR__ : gpVramLoadFileHandleGet [%s]\n", vvfile_name );
	// 指定した名前が無かった
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//================================================================================================
//	名前からデータINDEXを取得
//	※dxLib_gpVramFileVramLoadを呼んだ後で無いと機能しない
//		@param		char * vvfile_name		:	画像ファイルネーム
//	@return		-1->失敗
int		DxLib::AppVramController::gpVramGetDataIndex( char * vvfile_name )
{
	{
#if 0
		// 名前が一致するか調べる
//		decltype( DxLib::VramFileContainer )::iterator itr = std::find( m_FileContainer.begin(), m_FileContainer.end(), vvfile_name );
		std::vector< DxLib::VramFileContainer>::iterator itr = std::find( m_FileContainer.begin(), m_FileContainer.end(), vvfile_name );
		if ( itr != m_FileContainer.end() ){
			// (gpVramFileVramLoad)が呼ばれているか調べる
			if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED ){
				// 一致すればデータINDEXを返す
				return ( *itr );
			}
		}
		else{
			// 存在しなかった
		}
#else
		// 名前が一致するか調べる
		int index = 0;
		std::vector< DxLib::VramFileContainer>::const_iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr, ++ index ) {
			if ( itr != m_FileContainer.end() ) {
				if( strcmp( itr->vv_TextureName.c_str(), vvfile_name ) == 0 ) {
					// (gpVramFileVramLoad)が呼ばれているか調べる
					if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED )
					{
						// 一致すればデータINDEXを返す
						return ( index );
					}
				}
			}
		}
#endif
	}
	ERROR_PRINT("__ERROR__ : gpVramGetDataIndex [%s]\n", vvfile_name );
	// 指定した名前が無かった(※つまり登録されていない)
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

int		DxLib::AppVramController::gpVramGetDataIndex( const int file_handle )
{
	{
#if 0
		// ファイルハンドルが一致するか調べる
		std::vector< DxLib::VramFileContainer>::iterator itr = std::find( m_FileContainer.begin(), m_FileContainer.end(), file_handle );
		if ( itr != m_FileContainer.end() ){
			// (gpVramFileVramLoad)が呼ばれているか調べる
			if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED ){
				// 一致すればデータINDEXを返す
				return ( *itr );
			}
		}
		else{
			// 存在しなかった
		}
#else
		// ファイルハンドルが一致するか調べる
		int index = 0;
		std::vector< DxLib::VramFileContainer>::const_iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr, ++ index ) {
			if ( itr != m_FileContainer.end() ) {
				if( itr->vv_FileHandle == file_handle ) {
					// (gpVramFileVramLoad)が呼ばれているか調べる
					if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED )
					{
						// 一致すればデータINDEXを返す
						return ( index );
					}
				}
			}
		}
#endif
	}
	ERROR_PRINT("__ERROR__ : gpVramGetDataIndexHandle [%d]\n", file_handle );
	// 指定したハンドルが無かった(※つまりVRAMにアップされていない)
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//================================================================================================
//	指定ファイルのVRAMタイプ設定を取得
//	※dxLib_gpVramFileVramLoadを呼んだ後で無いと機能しない
//		@param		char * vvfile_name		:	画像ファイルネーム
//	@return		成功-> VRAMタイプ
//				失敗-> -1
int		DxLib::AppVramController::gpVramGetVVramType( const char * vvfile_name )
{
	{
#if 0
		// 名前が一致するか調べる
		std::vector< DxLib::VramFileContainer>::iterator itr = std::find( m_FileContainer.begin(), m_FileContainer.end(), vvfile_name );
		if ( itr != m_FileContainer.end() ){
			// (gpVramFileVramLoad)が呼ばれているか調べる
			if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED ){
				// 一致すればVRAMタイプを返す
				return ( itr->vv_VramType );
			}
		}
		else{
			// 存在しなかった
		}
#else
		const int length = static_cast<int>( m_FileContainer.size() );

		// 名前が一致するか調べる
		std::vector< DxLib::VramFileContainer>::const_iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr ) {
			if ( itr != m_FileContainer.end() ) {
				if( strcmp( itr->vv_TextureName.c_str(), vvfile_name ) == 0 ) {
					// (gpVramFileVramLoad)が呼ばれているか調べる
					if( itr->vv_VramCount == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED )
					{
						// 一致すればVRAMタイプを返す
						return ( itr->vv_VramType );
					}
				}
			}
		}
#endif
	}
	ERROR_PRINT("__ERROR__ : gpVramGetVVramType [%s]\n", vvfile_name );
	// 指定した名前が無かった(※つまり登録されていない)
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//================================================================================================
//	指定ハンドルインデックスの配列登録情報を削除する
//	※必ずVRAMからテクスチャ削除時のみ呼ぶ様に
//		@param		char * vvfile_name		:	画像ファイルネーム
//	@return		0->成功		-1->失敗
int		DxLib::AppVramController::gpVramEntryDataClear( const char * vvfile_name )
{
	// 要素内項目を初期化するんじゃなく要素ごと消し去る
	{
#if 0
		std::vector< DxLib::VramFileContainer>::iterator itr = std::find( m_FileContainer.begin(), m_FileContainer.end(), vvfile_name );
		if ( itr != m_FileContainer.end() ){
			// 指定要素削除
			m_FileContainer.erase( m_FileContainer.begin() + *itr );
		}
		else{
			// 指定要素が無かった
		}
#else
		// 名前が一致するか調べる
		int index = 0;
		std::vector< DxLib::VramFileContainer>::iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr, ++ index ) {
			if ( itr != m_FileContainer.end() ) {
				if( strcmp( itr->vv_TextureName.c_str(), vvfile_name ) == 0 ) {
					// 指定要素削除
					itr->vv_VramCount = AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_NON;
					itr->vv_FileHandle = -1;
					itr->vv_ReadBuff = nullptr;
					itr->vv_VramType = 0;
					itr->vv_WIDTH = 0;
					itr->vv_HEIGHT = 0;
					m_FileContainer.erase( m_FileContainer.begin() + index );

					return ( App::FileVram::eRESULT_CODE_SUCCESS );
				}
			}
		}
#endif
	}
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}
int		DxLib::AppVramController::gpVramEntryDataClear( const int file_handle )
{
	{
		// ファイルハンドルが一致するか調べる
		int index = 0;
		std::vector< DxLib::VramFileContainer>::iterator itr;
		for ( itr = m_FileContainer.begin(); itr != m_FileContainer.end(); ++ itr, ++ index ) {
			if ( itr != m_FileContainer.end() ) {
				if( itr->vv_FileHandle == file_handle ) {
					// 指定要素削除
					itr->vv_VramCount = AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_NON;
					itr->vv_FileHandle = -1;
					itr->vv_ReadBuff = nullptr;
					itr->vv_VramType = 0;
					itr->vv_WIDTH = 0;
					itr->vv_HEIGHT = 0;
					m_FileContainer.erase( m_FileContainer.begin() + index );

					return ( App::FileVram::eRESULT_CODE_SUCCESS );
				}
			}
		}
	}
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//================================================================================================
//	全要素全て削除する
int		DxLib::AppVramController::gpVramEntryDataClearALL()
{
	// ※要素内項目を空にするので無く確保配列全てをクリアするのでLengthは0になる
	{
	}
	return ( App::FileVram::eRESULT_CODE_SUCCESS );
}

//================================================================================================
//	空き番号を探す(※削除されて空きが出来たインデックスを探す)
int		DxLib::AppVramController::gpVramGetNotUseListIndex()
{
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
/*
	VRAM デバッグ関係
*/
//////////////////////////////////////////////////////////////////////////////////////////////////








