
#include "DxLib.h"
#include "../../../../Main.h"
#include "../../../../Common/appCommonParam.h"
#include "../../../../Common/appErrorCode.h"
#include "../../../../Common/appProcessCode.h"
#include "../../../../Common/CervidaeLib/Utility/UtilityForOperat.h"
#include "../appResourcesConfig.h"
#include "appFileGraphic.h"
#include "appVramFileManage.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ファイルVRAM管理処理
//	[画像の登録]
//	vramTextureFileEntry
//
//	[画像のメモリへのアップ]
//	◯単体
//	vramTextureFileSingleUpload
//
//	◯特定属性の全ファイル
//	
//
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
	[README]
*/

/**
    ファイルパスから拡張子を抽出する処理では、strrchrでパスの後方から"."の位置を取得します。
    "."は複数箇所に含まれる可能性があるため、strchrやstrstrでパスの前方から検索してはいけません。
    また、拡張子無し("."なし)のファイルパスが渡される可能性もあるため、strrchrの戻り値は必ずNULLチェックする必要があります。

    拡張子のチェック処理では、カンマ区切りで渡された拡張子をstrtokで分解し、strcmpで拡張子を比較しています。
    拡張子の大文字小文字を区別しない場合はstricmpやstrcasecmpで比較を行ってください。

    なお、比較可能な拡張子の文字列(szCmpExts)は1024文字(終端含む)で固定としています。通常の使用ではオーバーしませんが、
    必要に応じて動的にszCmpExtsを確保してください。
*/
bool    stringCheckExtension( const char* pszPath, const char* pszCmpExts )
{
    // ファイルパスの拡張子を抽出
    const char* pszExt = strrchr( pszPath, '.' );
    if( pszExt && *(pszExt + 1) != '\0' ) {
        pszExt += 1;
    }
    else{
        return false; // ファイルパスに拡張子が存在しない場合はfalse
    }

	char* ctx = {};
    // 拡張子をチェック(大文字小文字区別あり)
    char szCmpExts[1024];
	strncpy_s( szCmpExts, sizeof( szCmpExts ), pszCmpExts, sizeof( szCmpExts ) - 1);

    for( const char* pszCmpExt = strtok_s( szCmpExts, ",", &ctx ); pszCmpExt; pszCmpExt = strtok_s( NULL, ",", &ctx ) ) {
        if( strcmp( pszExt, pszCmpExt ) == 0 ){ 
            return true;
        }
    }
    return false;
}

/**
 * 
 * 
 */
DxLib::ResourcesLoadContainer *	DxLib::AppVramFileManager::getContainer( const char * fileName )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return NULL; }
#endif

    std::vector< DxLib::ResourcesLoadContainer >::iterator itr;
    for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr )
    {
        if ( itr != m_resourcesContainer.end() ) 
        {
			if( (strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0 ) ) 
			{
				return &*itr;
			}
/*
            if( (strcmp( (itr).operator*->m_vLoadTextureName.c_str(), fileName ) == 0 ) ) 
            {
                return (itr).operator*;
            }
*/
        }
    }

	ERROR_PRINT("__ERROR__ : getContainer DataFailed.\n");
    return NULL;
}

/**
 *
 */
DxLib::AppVramFileManager::AppVramFileManager() :
    m_LoadedFiles( 0 ),
	m_EnteredFiles( 0 )
{
	m_resourcesContainer.clear();

    DEBUG_PRINT("AppVramFile : VramFileManager コンストラクタ\n");
}
DxLib::AppVramFileManager::~AppVramFileManager()
{
    DEBUG_PRINT("AppVramFile : VramFileManager デストラクタ\n");
}

/**
 *
 * 
 */
bool    DxLib::AppVramFileManager::vramFileSystemInit()
{
    return true;
}

/**
 *
 * 
 */
bool    DxLib::AppVramFileManager::vramFileSystemExit()
{
    vramContainerDataClearALL();

    DEBUG_PRINT("[VramFile] vramFileSystemExit :\n" );

    return true;
}

//=====================================================================================//
//	@name	ファイルメモリアップロード
//	
//	
//=====================================================================================//
int     DxLib::AppVramFileManager::vramTextureLoad( DxLib::ResourcesLoadContainer * pfileContainer )
{
#if PROJECT_DEBUG
    if ( pfileContainer == nullptr ) { return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
#endif

	auto loadResult = fileLoadAccess( pfileContainer->m_vFileArchIndex, pfileContainer->m_vLoadTextureName.c_str(), NULL );
    if ( loadResult == -1 ) {
        ERROR_PRINT("__ERROR__ : vramTextureLoad FileResult\n");
        return App::FileProcess::eFILE_RESULT_CODE_ERROR;
    }

    // 読み込みに成功したら渡されたコンテナの指定情報を書き換えて更新する
    pfileContainer->m_vLoadFileHandle = loadResult;
	// テクスチャファイルの処理状況
    pfileContainer->m_vFileStatus = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_LOADING;

    // テクスチャのサイズ情報
    int	_TexWidth = 0, _TexHeight = 0;
    auto result = DxLib::GetGraphSize( loadResult, &_TexWidth, &_TexHeight );
#if PROJECT_DEBUG
    if ( result == -1 ) {
        ERROR_PRINT("__ERROR__ : vramTextureLoad GetFileSizeError.\n");
        return App::FileProcess::eFILE_RESULT_CODE_ERROR;
    }
#endif
	if ( _TexWidth > 0 ) {
		pfileContainer->m_vTextureObj.m_RenderW = _TexWidth;
	}
	if ( _TexHeight > 0 ) {
		pfileContainer->m_vTextureObj.m_RenderH = _TexHeight;
	}

    DEBUG_PRINT("[VramFile] TextureLoad TextureWidth[%d.px]. TextureHeight[%d.px]\n", pfileContainer->m_vTextureObj.m_RenderW, pfileContainer->m_vTextureObj.m_RenderH );
    DEBUG_PRINT("[VramFile] TextureLoad Handle[%d]. Name[\"%s\"]\n", pfileContainer->m_vLoadFileHandle, pfileContainer->m_vLoadTextureName.c_str() );

    return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=====================================================================================//
//	@name	グラフィック画像を登録
//		@param  fileVramType    :	登録VRAMタイプ
//		@param  fileName		:	画像名
//		@param  fileArchiveType :	アーカイブの登録ファイルINDEX
//		@param  fileIndex		:	画像ファイル番号
//		@param  fileAttrType    :	画像登録属性 [ ENUM_GPFILE_MAX ～ ]
//                                  
//	@return		0		-> 成功
//				0以外	-> エラー
//
//  @comment    ※画像データの登録可能最大インデックスは9999
//              ※登録のみで読み込みはしない
//
//=====================================================================================//
int		DxLib::AppVramFileManager::vramTextureFileEntry( const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE fileVramType,
													     const char*  fileName, 
													     const AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_LIST fileArchiveType,
													     const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType,
														 const AppLib::Resources::Parameter::ENUM_GRAPHIC_FILE_ENTRY_TYPE fileEntryUseType )
{
#if PROJECT_DEBUG
	// ".png"形式の画像じゃ無いならエラー
	const bool result = stringCheckExtension( fileName, "png" );
    if ( result == false ) {
        ERROR_PRINT("__ERROR__ : TextureFileEntry TextureFormatError ! [%s]\n", fileName );
		return App::ErrorCode::eRETURN_CODE_INVALID_FILEFORMAT;	
    }
    // 登録限界かチェック
	int fileListArray = getLoadingFileSize();
    if ( fileListArray >= AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX ) {
		ERROR_PRINT("__ERROR__ : TextureFileEntry 登録限界 [%d]\n", fileListArray );
        return ( -3 );
    }
	// ２重登録防止で既に登録済みかチェック
	const bool isFileExist = isFileEntryDoubleRegistration(fileName);
	if (isFileExist) {
		ERROR_PRINT("__ERROR__ : TextureFileEntry DoubleRegistration ! [%s]\n", fileName);
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

    // ※画像登録インデックスは画像ファイルの頭の文字を抜き出して設定
    const int entryFileIndex = getSetupFileNameEntryIndex( fileName );
#if PROJECT_DEBUG
    // 画像ファイルの登録インデックス範囲チェック
    if( entryFileIndex >= (AppLib::Resources::Parameter::EntryIndex::ENUM_RESOURCES_FILE_ENTRY_INDEX_MAX) ){
		ERROR_PRINT("__ERROR__ : TextureFileEntry entryFileIndex Over\n" );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    // 新規登録
	// ※C++11以降では auto_ptr<T>の使用は非推奨
	// [ unique_ptrとは ]
	// unique_ptr<T>は、あるメモリに対する所有権を持つポインタが、ただ一つであることを保証するようなスマートポインタである。 
	// auto_ptr<T>同様に、テンプレート引数で保持するポインタ型を指定し、
	// スマートポインタが破棄される際にディストラクタにおいて自動的にメモリを開放する
	// ○メモリの所有権を持つ unique_ptr<T>は、 ただ一つのみ
	// ○配列を扱うことができる
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	std::unique_ptr<DxLib::ResourcesLoadContainer>  setupFileData = std::make_unique<DxLib::ResourcesLoadContainer>();

    // 登録時に情報設定されるデータ
    {
		setupFileData->m_vLoadVramType		= fileVramType;
		setupFileData->m_vLoadTextureName	= fileName;
        setupFileData->m_vFileIndex			= entryFileIndex;
		setupFileData->m_vFileAttribute		= fileAttrType;
		setupFileData->m_vFileArchIndex		= fileArchiveType;
		setupFileData->m_vFileEntryUseType	= fileEntryUseType;
    }
    // 読み込み時に情報設定されるデータ
    {
		setupFileData->m_vLoadFileHandle	 = AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;
		setupFileData->m_vFileStatus		 = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_ENTRYCLEAR;
		setupFileData->m_vTextureObj.m_RenderW = 0;
		setupFileData->m_vTextureObj.m_RenderH = 0;
    }

	// 設定した情報をクラスに格納
	m_resourcesContainer.push_back( *setupFileData );

#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    m_LoadedFiles ++;

	DEBUG_PRINT("[VramFile] m_vTextureName:[\"%s\"] m_vFileIndex:[%d]\n", fileName,entryFileIndex );
    DEBUG_PRINT("[VramFile] m_LoadedFiles : %d\n", m_LoadedFiles );
/*
	std::string print1 = UtilityForOperat::getReplaceTextValue( "値段は%value%円です。", 19800, true );
	std::string print2 = UtilityForOperat::getReplaceText( "値段は%text%円です。", "29800", false );
	DEBUG_PRINT("[TEST] getReplaceTextValue:[\"%s\"] \n", print1.c_str());
	DEBUG_PRINT("[TEST] getReplaceText:[\"%s\"] \n", print2.c_str());
*/
    // 登録完了
    return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=====================================================================================//
//  グラフィック画像データファイル単体読み込みメモリアップ
//		@param		fileName		:	画像ファイル名
//		@param		fileUpmode		:	ファイルUPモード
//		@param		fileCheckNum	:	
//	<<戻り値>>
//		成功 -> 0
//=====================================================================================//
int		DxLib::AppVramFileManager::vramTextureFileSingleUpload( const char * fileName, 
                                                                const int fileUpmode, 
                                                                int fileCheckNum )
{
    int i = 0;
	int uploadResult = -1;
    
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }

    // まだ読み込み出来るか？
    const int dataArray = getLoadingFileSize();
    if ( dataArray >= AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX ) {
		ERROR_PRINT("__ERROR__ : LoadingFileSize dataArray Over\n");
        return App::FileVram::eRESULT_CODE_ERROR_NOARRAY;
    }

    // 既に読み込み済みか？
	const bool isFileStatus = isFileLoadDoubleRegistration( fileName );
    if ( isFileStatus ) {
		ERROR_PRINT("__ERROR__ : LoadingFileSize DoubleLoading Over\n");
        return App::FileVram::eRESULT_CODE_ERROR_DOUBLE_LOADING;
    }
 #endif

    {
        switch( fileUpmode )
		{
		//----------------------------------------------------------------//
		// 通常( カウントを足していき1になったらメモリにアップ )
		//----------------------------------------------------------------//
		case	AppLib::Resources::ProcessStatus::eUPMODE_NORMAL:
			{
			}
			break;
		//----------------------------------------------------------------//
		// VRAMに乗ってなかったらアップ､もう乗ってたらなんもせず
		//----------------------------------------------------------------//
		case	AppLib::Resources::ProcessStatus::eUPMODE_ONE:
			{
			}
			break;
		//----------------------------------------------------------------//
		// 上で復帰処理やっちゃってるからとくに何もせず
		//----------------------------------------------------------------//
		case	AppLib::Resources::ProcessStatus::eUPMODE_RETURN:
			{
			}
			break;
		default:
			break;
		}

		// 読み込もうとしてるファイル情報が登録されているならロード
        const bool isFileEntry = false;
        DxLib::ResourcesLoadContainer * pResources = getContainer( fileName );
        if ( pResources )
        {
#if PROJECT_DEBUG
            // 登録されているか
			if ( pResources->m_vFileStatus != AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_ENTRYCLEAR ) {
				ERROR_PRINT("__ERROR__ : LoadingFileSize FileStatus NoEntry. [\"%s\"]\n", fileName );
				return App::FileVram::eRESULT_CODE_ERROR_DOUBLE_LOADING;
			}
#endif
            // テクスチャのメモリへのロード
            uploadResult = vramTextureLoad( pResources );
#if PROJECT_DEBUG
            if ( uploadResult == App::FileProcess::eFILE_RESULT_CODE_ERROR ) {
                return App::FileVram::eRESULT_CODE_ERROR_LOADFAILED;
            }
#endif

			DEBUG_PRINT("[VramFile] TextureLoad Success OK. [\"%s\"]\n", fileName );
			return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
        }
    }

	DEBUG_PRINT("[VramFile] FileSingleUpload Error. : [\"%s\"]\n", fileName );
    return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

//=====================================================================================//
//  指定属性の画像ファイルを全てメモリアップ
//		@param		fileVramType	:	
//		@param		fileAttrType	:	画像ファイル登録属性
//		@param		fileUpmode		:	ファイルUPモード
//		@param		fileCheckNum	:	
//	<<戻り値>>
//		成功 -> 
//=====================================================================================//
int		DxLib::AppVramFileManager::vramSpecificAttributeFilesAllUpload( const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE fileVramType, 
                                                                        const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType, 
                                                                        const int fileUpmode, 
                                                                        int fileCheckNum )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif
	const int  fileLength = getLoadingFileSize();
    auto fileResult = 0;
    int  i;

    // 全属性全てアップか？
    if( fileAttrType == AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_ALL )
    {
        // COMMENT：全属性指定の時は全てアップする
		for( i = 0; i < fileLength; ++ i )
		{
			// 既にアップロード済みなら何もしない
            if ( isFileLoadDoubleRegistration( m_resourcesContainer[i].m_vLoadTextureName.c_str() ) ) { continue; }

            fileResult = vramTextureFileSingleUpload( m_resourcesContainer[i].m_vLoadTextureName.c_str(), 
                                                      fileUpmode,
                                                      fileCheckNum );
		}
    }
    else
    {
        if( fileVramType == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM )
        {
            for( i = 0; i < fileLength; ++ i )
            {
                // 特定属性のアップ
                if( m_resourcesContainer[i].m_vFileAttribute == fileAttrType )
                {
                    // 既にアップロード済みなら何もしない
                    if ( isFileLoadDoubleRegistration( m_resourcesContainer[i].m_vLoadTextureName.c_str()) ) { continue; }
                    // グラフィック画像データ単体アップ
                    fileResult = vramTextureFileSingleUpload( m_resourcesContainer[i].m_vLoadTextureName.c_str(), 
                                                              fileUpmode,
                                                              fileCheckNum );
                }
            }
        }
		else if ( fileVramType == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY )
		{
		}
		else
        {
            return App::FileProcess::eFILE_RESULT_CODE_ERROR;
        }
    }
    return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

// ２重登録防止で既に登録済みかチェック
bool    DxLib::AppVramFileManager::isFileEntryDoubleRegistration( const char* fileName/*, const int fileIndex*/ )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return false; }
#endif

    // 要素の中から情報を検索する
	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr = m_resourcesContainer.begin();
	for ( ; itr != m_resourcesContainer.end(); ++ itr )
	{
		if( ( strcmp( itr->m_vLoadTextureName.c_str(), fileName ) == 0 ) /*&& itr->m_vFileIndex == fileIndex*/  )
		{
			if ( itr->m_vFileStatus == AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_ENTRYCLEAR )
			{
				return true; // 登録済み
			}
		}
	}
    
    return false;
}
bool	DxLib::AppVramFileManager::isFileEntryIndexDoubleRegistration( /*const char* fileName,*/ const int fileIndex )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return false; }
#endif
 /*
	std::vector<int> dataList(
	auto fileList = std::find( m_resourcesContainer.begin(), m_resourcesContainer.end(), fileIndex );
    if ( fileList == m_resourcesContainer.end() ) {
    }
*/
	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr = m_resourcesContainer.begin();
	for ( ; itr != m_resourcesContainer.end(); ++ itr )
	{
		if ( itr != m_resourcesContainer.end() ) 
		{
			if ( itr->m_vFileIndex == fileIndex )
			{
				if ( itr->m_vFileStatus == AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_ENTRYCLEAR )
				{
					return true; // 登録済み
				}
			}
		}
	}
    return false;
}

// ２重読み込み防止で既に読み込み済みかチェック
bool	DxLib::AppVramFileManager::isFileLoadDoubleRegistration( const char* fileName )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return false; }
#endif

	// 要素の中から情報を検索する
	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr = m_resourcesContainer.begin();
	for ( ; itr != m_resourcesContainer.end(); ++ itr )
	{
		if( ( strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0 )/* && (itr)->m_vFileIndex == fileIndex*/ )
		{
            // ファイルハンドルと処理フラグ両方チェックする
            if ( ((itr)->m_vLoadFileHandle != AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE) && 
                 ((itr)->m_vFileStatus == AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_VRAMLOADING) )
            {
			    return true; // 読み込み済み
            }
		}
	}
    return false;
}

//=====================================================================================//
//	有効(読み込み中)グラフィックハンドルの数を取得する
int		DxLib::AppVramFileManager::getVramFileValiditLoadHandle()
{
	const int effectiveHandles = DxLib::GetGraphNum();
#if PROJECT_DEBUG
	if( effectiveHandles < 0 ){
		ERROR_PRINT("__ERROR__ : NonFileHandle getVramFileValiditLoadHandle()\n");
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	return ( effectiveHandles );
}
int		DxLib::AppVramFileManager::getVramUpLoadedFiles()
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    int fileCounter = 0;
    std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr;
    for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr )
    {
        if ( itr != m_resourcesContainer.end() ) 
        {
            if( (itr)->m_vFileStatus == AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_VRAMLOADING ) {
                fileCounter ++;
            }
        }
    }
    DEBUG_PRINT("[VramFile] fileCounter : %d\n", fileCounter );
    return fileCounter;
}

//=====================================================================================//
//	指定ファイルインデックスが要素コンテナの何番目に登録されているかのインデックスを取得
int		DxLib::AppVramFileManager::getVramFileElementEntryIndex( const char* fileName, bool isLoadFile )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    // 要素の中から情報を検索する
    int index = 0;
	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr = m_resourcesContainer.begin();
    for ( ; itr != m_resourcesContainer.end(); ++ itr, ++ index )
	{
		if ( (strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0) )
		{
			return index;
		}
	}
    return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

//=====================================================================================//
//	ファイル名から登録インデックスを取得（登録済みなら）
int		DxLib::AppVramFileManager::getVramFileParameterIndex( const char* fileName, bool isLoadFile )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    // 要素の中から情報を検索する
	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr = m_resourcesContainer.begin();
    for ( ; itr != m_resourcesContainer.end(); ++ itr )
    {
        if ( (strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0) )
        {
            return (itr)->m_vFileIndex;
        }
    }
    return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

//=====================================================================================//
//	ファイル名からロードハンドルを取得
int		DxLib::AppVramFileManager::getVramFileParameterLoadHandle( const char* fileName, bool isLoadFile )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

	std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr;
    for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr ) {
        if ( itr != m_resourcesContainer.end() ) {
            // 名前が一致するか
            if( strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0 ) {
                // (gpVramFileVramLoad)が呼ばれているか調べる
                if( (itr)->m_vFileStatus == AppLib::Resources::FileVram::eDEF_VVRAM_BUFFER_FLAG_USED ) {
                    // 存在すればロードハンドルを返す
                    return (itr)->m_vLoadFileHandle;
                }
            }
        }
    }
    ERROR_PRINT("__ERROR__ : gpVramLoadFileHandleGet [\"%s\"]\n", fileName );
	// 指定した名前が無かった
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//=====================================================================================//
//	ファイル名からアーカイブ設定を取得
int		DxLib::AppVramFileManager::getVramFileParameterArchiveType( const char* fileName, bool isLoadFile )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr;
    for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr ) {
        if ( itr != m_resourcesContainer.end() ) {
            // 名前が一致するか
            if( strcmp( (itr)->m_vLoadTextureName.c_str(), fileName ) == 0 ) {
                // 登録されているか
                if( isFileEntryDoubleRegistration( (itr)->m_vLoadTextureName.c_str()) )
                {
                    // 存在すればアーカイブ設定を返す（※受け取る側でENUM_ARCHIVE_FILETYPE_LISTにキャストする）
                    return (itr)->m_vFileArchIndex;
                }
            }
        }
    }
    ERROR_PRINT("__ERROR__ : gpVramLoadFileHandleGet [\"%s\"]\n", fileName );
	// 指定した名前が無かった
	return ( App::FileVram::eRESULT_CODE_ERROR_FAILED );
}

//=====================================================================================//
//	指定属性タイプのメモリに上がっている読み込み状態ファイル数を取得
int		DxLib::AppVramFileManager::getSpecificAttributeLoadFiles( const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttribute, bool isLoadFile )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_resourcesContainer.empty() ) { return App::FileVram::eRESULT_CODE_ERROR_NOTHING_REGISTERE; }
#endif

    int fileCounter = 0;
    std::vector< DxLib::ResourcesLoadContainer >::const_iterator itr;
    for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr )
    {
        if ( itr != m_resourcesContainer.end() ) 
        {
            if( (itr)->m_vFileAttribute == fileAttribute )
            {
                if( (itr)->m_vFileStatus == AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_LOADING ) 
                {
                    fileCounter ++;
                }
            }
        }
    }
	DEBUG_PRINT("[VramFile] SpecificAttributeLoadFiles : [%d]\n", fileCounter );
    // １つも該当データが無ければ０が返る
	return ( fileCounter );
}

//=====================================================================================//
//	指定テクスチャ登録情報を削除する
//	※必ずVRAMからテクスチャ削除時のみ呼ぶ様に
//	@param		char * clearTexture		:	画像ファイルネーム
//	@return		0 -> 成功
//             -1 -> 失敗
//=====================================================================================//
int		DxLib::AppVramFileManager::vramContainerDataClear( const char* clearTexture )
{
	int index = 0;
	std::vector< DxLib::ResourcesLoadContainer>::iterator itr;
	for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr, ++ index )
	{
		if ( itr != m_resourcesContainer.end() )
		{
			if( strcmp( itr->m_vLoadTextureName.c_str(), clearTexture ) == 0 )
			{
				// 指定要素削除
				itr->m_vLoadVramType = AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM;
				itr->m_vFileArchIndex = AppLib::Resources::Archive::eARCHIVE_FILETYPE_NONE;
				itr->m_vFileIndex = 0;
				itr->m_vFileAttribute = AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MAIN;
				itr->m_vFileEntryUseType = AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_NONE;
				itr->m_vLoadFileHandle = AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;
				itr->m_vFileStatus = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_NOUSE;
				itr->m_vTextureObj.m_RenderW = 0;
				itr->m_vTextureObj.m_RenderH = 0;

				m_resourcesContainer.erase( m_resourcesContainer.begin() + index );

				DEBUG_PRINT("[VramFile] ContainerDataClear : [%d]\n", index );

				return ( App::FileVram::eRESULT_CODE_SUCCESS );
			}
		}
	}
	ERROR_PRINT("__ERROR__ : vramContainerDataClear [\"%s\"]\n", clearTexture );
	return ( App::FileVram::eRESULT_CODE_ERROR_RELEASEFAILED );
}

//=====================================================================================//
//	指定ファイルハンドルの登録情報を削除する
//	※必ずVRAMからテクスチャ削除時のみ呼ぶ様に
//	@param		int clearHandle		:	画像ファイルハンドル
//	@return		0 -> 成功
//             -1 -> 失敗
//=====================================================================================//
int		DxLib::AppVramFileManager::vramContainerDataClear( const int clearHandle )
{
	int index = 0;
	std::vector< DxLib::ResourcesLoadContainer>::iterator itr;
	for ( itr = m_resourcesContainer.begin(); itr != m_resourcesContainer.end(); ++ itr, ++ index )
	{
		if ( itr != m_resourcesContainer.end() )
		{
			if ( itr->m_vLoadFileHandle == clearHandle )
			{
                // 指定要素削除
				itr->m_vLoadVramType = AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM;
				itr->m_vFileArchIndex = AppLib::Resources::Archive::eARCHIVE_FILETYPE_NONE;
				itr->m_vFileIndex = 0;
				itr->m_vFileAttribute = AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MAIN;
				itr->m_vFileEntryUseType = AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_NONE;
				itr->m_vLoadFileHandle = AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;
				itr->m_vFileStatus = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_NOUSE;
				itr->m_vTextureObj.m_RenderW = 0;
				itr->m_vTextureObj.m_RenderH = 0;

				m_resourcesContainer.erase( m_resourcesContainer.begin() + index );

                DEBUG_PRINT("[VramFile] ContainerDataClear : [%d]\n", index );

				return ( App::FileVram::eRESULT_CODE_SUCCESS );
			}
		}
	}

	ERROR_PRINT("__ERROR__ : vramContainerDataClear [%d]\n", clearHandle );
	return ( App::FileVram::eRESULT_CODE_ERROR_RELEASEFAILED );
}

//=====================================================================================//
//	
//	@return		0 -> 成功
int		DxLib::AppVramFileManager::vramContainerDataClearALL()
{
    // 領域の解放（中身を空にするだけじゃなくメモリも解放する）
	m_resourcesContainer.shrink_to_fit();
#if 0
     for ( std::vector< DxLib::ResourcesLoadContainer>::const_iterator i = m_resourcesContainer.begin (); i != m_resourcesContainer.end (); i ++ )
     {
     }
#endif
    return ( App::FileVram::eRESULT_CODE_SUCCESS );
}

//=====================================================================================//
//	登録->読み込みまで一括で行う
//	※FileEntryとUploadを連続で呼んでも同じだが無駄なのでまとめる
int		DxLib::AppVramFileManager::vramTextureExecutionRelatedProcesses(
												const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE	 fileVramType,
												const char* fileName,
												const AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_LIST		 fileArchiveType,
												const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType,
												const AppLib::Resources::Parameter::ENUM_GRAPHIC_FILE_ENTRY_TYPE	 fileEntryUseType,
												const int	fileUpmode )
{
	int  result = -1;
	// 登録
	result = vramTextureFileEntry( fileVramType,fileName,fileArchiveType,fileAttrType,fileEntryUseType );
	if ( result == App::FileProcess::eFILE_RESULT_CODE_SUCCESS )
	{
		// 読み込み
		result = vramTextureFileSingleUpload( fileName, fileUpmode );

		return (App::FileVram::eRESULT_CODE_SUCCESS);
	}
	return (App::FileVram::eRESULT_CODE_ERROR_FAILED);
}


//=====================================================================================//
//	画像ファイル名から頭に設定されている登録インデックス値を取得する
//	※100_Texture.pngなら100を返す
int		DxLib::AppVramFileManager::getSetupFileNameEntryIndex( const char* checkFile )
{
    int configFileIndex = -1;

    std::string setupFile = checkFile;
    const size_t strofIndex = setupFile.find_first_of('_');
	// 0番目から指定数分文字列を抜き出す
    std::string setupFileStr = setupFile.substr( 0, strofIndex );

    configFileIndex = std::stoi( setupFileStr );

    DEBUG_PRINT("[VramFile] configEntryFileIndex : [%d]\n", configFileIndex );

    return configFileIndex;
}


