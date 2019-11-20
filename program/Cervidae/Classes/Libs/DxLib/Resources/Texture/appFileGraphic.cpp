

#include "DxLib.h"
#include "../../../../Common/appCommonParam.h"
#include "../../../../Common/appErrorCode.h"
#include "../../../../Common/appProcessCode.h"
#include "../appResourcesConfig.h"
#include "appVramContainer.h"
#include "appVramConfig.h"
#include "appVramControl.h"
#include "appFileGraphic.h"


//////////////////////////////////////////////////////////////////////////////////////////////////
/*
	DXライブラリ	グラフィックファイル管理システム
	
	※ＤＸライブラリでは、LoadGraph 等の画像ファイルを扱う関数全般で
	  指定のファイル名の末端に『_a』が付く画像ファイルが在った場合
	  その画像ファイルを透明情報として読み込みます。

	LastUpdate : 2019.05.02
*/
//////////////////////////////////////////////////////////////////////////////////////////////////




/*
 *	@process	
 *
 **/
DxLib::AppFileGraphicManager::AppFileGraphicManager()
{
}
DxLib::AppFileGraphicManager::~AppFileGraphicManager()
{
}
//=============================================================================================//
//  グラフィクスファイル管理システム基本初期化
bool	DxLib::AppFileGraphicManager::_graphicSystemInit()
{
	{
		auto containerSize = static_cast<int>( m_graphicContainer.size() );
		for( int i = 0; i < containerSize; ++ i )
		{
//			m_graphicContainer[i].gp_FileCount = AppLib::Resources::FileProcess::eVRAM_ENTRY_NONE;
//			m_graphicContainer[i].gp_FileArch = 0;
//			m_graphicContainer[i].gp_FileNum = -1;
//			m_graphicContainer[i].gp_FileAttr = 0;
//			m_graphicContainer[i].gp_FileID	= -3;
//			m_graphicContainer[i].gp_FileHandle = AppLib::Resources::FileProcess::eGPFILE_HANDLE_NONUSE;
//			m_graphicContainer[i].gp_LoadingFlag = AppLib::Resources::FileProcess::eVRAM_ENTRY_NONE;
		}
	}
	return true;
}

//=============================================================================================//
//  グラフィクスファイル管理システム終了処理
bool	DxLib::AppFileGraphicManager::_graphicSystemExit()
{
	return false;
}

//=============================================================================================//
//  画像タイプと画像名から絵の登録番号を返す
//		@param		int		gp_type		:	登録VRAMタイプ
//		@param		char *	gp_name		:	画像ファイル名
//	@return		成功->登録番号	
int		DxLib::AppFileGraphicManager::_graphicVramFileIdBackNumCheck( const int  gp_type, const char* gp_name )
{
	int	i = 0;
	int	gp_Blank = -1;
	int gp_EntryMax = 0;
	{
		// グラフィックロード可能最大数を取得
		i = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax, NULL );
#if PROJECT_DEBUG
		if( i < 0 ){
			return ( AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX);
		}
#endif

		// 同じ名前のフラグを探す
		for( i = 0; i < gp_EntryMax; ++ i ) {
			if( m_graphicContainer[i].gp_FileCount == -1 ) {
				// マイナスなら空きの場所として返す
				if( gp_Blank == -1 ){
					gp_Blank = i;
				}
				continue;
			}
			// あったら番号を返す
			if( strcmp( m_graphicContainer[i].gp_FileName.c_str(), gp_name ) == 0 )
			{
				return  i;
			}
		}

		// そんな名前は見つからず
		if( gp_Blank == -1 )
		{
			return  gp_EntryMax;
		}else{
			return  -(gp_Blank + 1);// 値を－(マイナス)で返す
		}
	}
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  タイプと名前からグラフィックのロードハンドルを取得
//		@param		int		gp_type		:	登録VRAMタイプ
//		@param		char *	gp_name		:	画像ファイル名
//	@return		成功->グラフィックロードハンドル   失敗->-1
int		DxLib::AppFileGraphicManager::_getGraphicTexVramLoadHandle( const int  gp_type, const char* gp_name )
{
	int		i = 0;
	int		gp_EntryMax = 0;
	int		gp_Result = -1;
	
	{
		// グラフィックロード可能最大数を取得
		i = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
		if( i < 0 ){
			return ( AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX);
		}
#endif
		// 同じ名前を探す
		for( i = 0; i < gp_EntryMax; ++ i ){
			// 名前チェック
			if( strcmp( m_graphicContainer[i].gp_FileName.c_str(), gp_name ) == 0 ){
				gp_Result = i;// インデックスを保存
				return ( m_graphicContainer[i].gp_FileHandle );// あればロードハンドルを返す
			}
		}
		// 名前が見つからなかった、つまりメモリにアップされてない
		if( gp_Result == -1 )
		{
			ERROR_PRINT("__ERROR__ : _getGraphicTexVramLoadHandle Result[%d]\n", gp_Result );
			return App::FileProcess::eFILE_RESULT_CODE_ERROR;
		}
	}
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  有効(読み込み中)グラフィックハンドルの数を取得する
//	@return		-1->エラー  それ以外->グラフィックハンドル
int		DxLib::AppFileGraphicManager::_getGraphicValiditLoadHandle()
{
	const int	graphHandle = DxLib::GetGraphNum();
#if PROJECT_DEBUG
	if( graphHandle < 0 ){
		ERROR_PRINT("__ERROR__ : NonClearHandle GetValiditLoadHandle()\n");
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	return ( graphHandle );
}

//=============================================================================================//
//  メモリへのグラフィックロード可能最大数を取得
//		@param		int		gp_type		:	登録VRAMタイプ
//		@param		int *	gp_Vrammax	:	
//	@return		0以外->エラー
int		DxLib::AppFileGraphicManager::_graphicVramFileMaxCheck( const int  gp_type, int * gp_Vrammax, GraphicFileContainer ** gpData )
{
	switch( gp_type % AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE_MAX )
	{
	//--------------------------------------------//
	// システム
	//--------------------------------------------//
	case	AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM:
		{
			*gp_Vrammax = AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX;
		}
		break;
	//--------------------------------------------//
	// メモリー
	//--------------------------------------------//
	case	AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY:
		{
			*gp_Vrammax = AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX;
		}
		break;
	default:
		// エラー
#if PROJECT_DEBUG
		ERROR_PRINT("__ERROR__ : _graphicVramFileMaxCheck gpType\n");
#endif
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  画像登録数を取得
//	※メモリに上がっている数では無い
//	※FileGraphicContainerに登録されている数
//		@param		int  gp_type		:	登録VRAMタイプ
//	@return		0以外->エラー
int		DxLib::AppFileGraphicManager::_graphicVramFileEntryNumCheck( const int  gp_type )
{
	int	i = 0, count = 0;
	int	gp_EntryMax = 0;

	{
		i = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
		if( i < 0 ){
			return ( AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX);
		}
#endif
		for( i = 0; i < gp_EntryMax; ++ i ){
			// 登録してるならカウント
			if( m_graphicContainer[i].gp_FileCount > -1 ){
				count ++;
			}
		}
		// 画像登録数を返す
		return ( count );
	}
	ERROR_PRINT("__ERROR__ : _graphicVramFileEntryNumCheck\n");
	return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

//=============================================================================================//
//
//	グラフィック画像を登録
//		@param		int		gp_type		:	登録VRAMタイプ
//		@param		char *	gp_name		:	画像名
//		@param		int		gp_arc		:	アーカイブの登録ファイルINDEX
//		@param		int		gp_file		:	画像ファイル番号
//		@param		int		gp_attr		:	画像登録属性 [ ENUM_GPFILE_MAX ～ ]
//											※画像データの登録可能最大インデックスは9999
//	@return		0->成功		0以外->エラー
//
//=============================================================================================//
int		DxLib::AppFileGraphicManager::_graphicVramTextureEntry( const int  gp_type, 
																const char * gp_name, 
																const int  gp_arc, 
																const int  gp_file, 
																const int  gp_attr )
{
#if PROJECT_DEBUG
	// ".png"形式の画像じゃ無いならエラー
/*	if( EtcStrSpeciWordCheck( gp_name, ".png" ) == false ){
		ERROR_PRINT("__ERROR__ : VramGpEntry TextureFormatError ! [%s]\n", gp_name );
		return App::ErrorCode::eRETURN_CODE_INVALID_FILEFORMAT;	
	}*/
#endif
	int	index = 0;
	int n = 0;
	int gp_EntryMax = 0;

	n = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
	if( n < 0 ){
		ERROR_PRINT("__ERROR__ : Entry _graphicVramFileMaxCheck\n");
		return ( -3 );// エラー MaxCheck Error
	}
#endif

	// 画像タイプと画像名から既に登録済みかどうか調べる
	index = _graphicVramFileIdBackNumCheck( gp_type, gp_name );
#if PROJECT_DEBUG
	if( index >= gp_EntryMax ){
		ERROR_PRINT("__ERROR__ : Entry _graphicVramFileIdBackNumCheck\n");
		return ( -2 );	// エラー EntryMax Over Error
	}
	else if( index >= 0 ){
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// 登録番号
	index = ( index + 1 ) * -1;

#if PROJECT_DEBUG
	// 特大インデックスで登録しない様に(保険)
	if( gp_file >= ( AppLib::Resources::Parameter::EntryIndex::ENUM_RESOURCES_FILE_ENTRY_INDEX_MAX + 1 )){
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif

	// 画像ファイルの情報登録
	m_graphicContainer[index].gp_FileCount = 0;					// 使用カウント(VRAM上げの指示を受けるたびに増え
	m_graphicContainer[index].gp_FileArch = gp_arc;				// アーカイブファイル番号
	m_graphicContainer[index].gp_FileNum = gp_file;				// ファイルの中の番号
	m_graphicContainer[index].gp_FileAttr = gp_attr;			// 属性、同じ属性の絵をアップしたり削除したりする
	m_graphicContainer[index].gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAMFILE_CLEAR;	// 読み込み処理で呼ばれたものか 

	// 名前登録
	m_graphicContainer[index].gp_FileName = gp_name;

	// 画像テクスチャロードハンドル(登録完了の印)
	m_graphicContainer[index].gp_FileHandle	= AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;
	
	// 処理状況（登録は終わっているのか読み込み済みなのか未使用なのか等）
	m_graphicContainer[index].gp_ProcessStatus = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_ENTRYCLEAR;

	ERROR_PRINT("_graphicVramTextureEntry 登録ＯＫ[ID:%d][\"%s\"]\n", index, m_graphicContainer[index].gp_FileName.c_str() );
	
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  グラフィック画像の登録データを削除
//		@param		int		gp_type		:	登録VRAMタイプ
//		@param		char *	gp_name		:	画像ファイル名
//	@return		インデックス->成功	-1->エラー
int		DxLib::AppFileGraphicManager::_graphicVramFileEntryDel( const int  gp_type, char* gp_name )
{
	int i = 0;
	int gp_EntryMax = 0;

	// メモリへのグラフィックロード可能最大数を取得
	i = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
	if( i < 0 ){
		ERROR_PRINT("__ERROR__ : [ i ] _graphicVramFileEntryDel\n");
		return ( -2 );	// ERROR
	}
#endif

	// 画像タイプと画像名から絵の登録番号を返す
	i = _graphicVramFileIdBackNumCheck( gp_type, gp_name );
#if PROJECT_DEBUG
	if( i >= gp_EntryMax || i < 0 ){
		ERROR_PRINT("__ERROR__ : _graphicVramFileEntryDel\n");
		return ( -2 );	// ERROR
	}
#endif

	if( (i < gp_EntryMax) && i >= 0 )
	{
		if( m_graphicContainer[i].gp_FileCount > 0 )
		{
			auto result = 0;
			switch( gp_type )
			{
				//--------------------------------------------//
				// システムタイプ
				case AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM:
					result = _graphicVramTexDelete( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
													const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), AppLib::Resources::ProcessStatus::eDELMODE_COER );
					break;
				//--------------------------------------------//
				// メモリータイプ
				case AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY:
					result = _graphicVramTexDelete( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
													const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), AppLib::Resources::ProcessStatus::eDELMODE_COER );
					break;
			default:
				return App::FileProcess::eFILE_RESULT_CODE_ERROR;
			}
		}
		// 未使用に
		m_graphicContainer[i].gp_FileCount = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_NOUSE;
		// 処理成功
		return ( i );
	}

	ERROR_PRINT("__ERROR__ : _graphicVramFileEntryDel NotTexture\n");
	// 無い絵を削除しようとした
	return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

//=============================================================================================//
//  グラフィック画像データファイル単体読み込みメモリアップ
//		@param		int		gp_type		:	登録VRAMタイプ
//		@param		char *	gp_name		:	画像ファイル名
//		@param		int		gp_mode		:	画像アップモード
//		@param		int		check_num	:	
//	<<戻り値>>
//		成功->ロードハンドル
int		DxLib::AppFileGraphicManager::_graphicVramTexUp( const int  gp_type, char* gp_name, const int  gp_mode, int  check_num )
{
	int i = 0;
	int gp_Result = 0;
	int gp_EntryMax = 0;

	gp_Result = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
	if( gp_Result < 0 ){
		ERROR_PRINT("__ERROR__ : _graphicVramTexUp\n");
		return ( -2 );	// ERROR
	}
#endif

	// 画像タイプと画像名から絵の登録番号を返す
	i = _graphicVramFileIdBackNumCheck( gp_type, gp_name );
#if PROJECT_DEBUG
	if( i >= gp_EntryMax || i < 0 ){
		ERROR_PRINT("__ERROR__ : _graphicVramTexUp\n");
		return ( -2 );	// ERROR
	}
#endif

	if( 1 )
	{
		switch( gp_mode )
		{
		//----------------------------------------------------------------//
		// 通常( カウントを足していき1になったらメモリにアップ )
		//----------------------------------------------------------------//
		case	AppLib::Resources::ProcessStatus::eUPMODE_NORMAL:
			{
				if( check_num > 0 ){
					m_graphicContainer[i].gp_FileCount += check_num;
				}else{
					m_graphicContainer[i].gp_FileCount ++;
				}
				if( m_graphicContainer[i].gp_FileID < -1 ){
					// ファイル読み込み
					gp_Result = gpVramFileVramLoad( m_graphicContainer[i].gp_FileArch, gp_name, gp_type );
					m_graphicContainer[i].gp_FileID = -1;								// ファイルID
					m_graphicContainer[i].gp_FileHandle	= gp_Result;					// ファイルハンドルセット
					m_graphicContainer[i].gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAMFILE_LOADING;	// 読み込み状態：処理開始
					m_graphicContainer[i].gp_ProcessStatus = 0;
					ERROR_PRINT("eUPMODE_NORMAL : VramLoad Handle[%d] Name[\"%s\"]\n", m_graphicContainer[i].gp_FileHandle, gp_name );
				}
			}
			break;
		//----------------------------------------------------------------//
		// VRAMに乗ってなかったらアップ､もう乗ってたらなんもせず
		//----------------------------------------------------------------//
		case	AppLib::Resources::ProcessStatus::eUPMODE_ONE:
			{
				if( m_graphicContainer[i].gp_FileCount == 0 )
				{
					// ファイル読み込み
					gp_Result = gpVramFileVramLoad( m_graphicContainer[i].gp_FileArch, gp_name, gp_type );
					m_graphicContainer[i].gp_FileCount	= 1;								// 読み込み状態(-1:何も無し)
					m_graphicContainer[i].gp_FileID		= -1;								// ファイルID
					m_graphicContainer[i].gp_FileHandle	= gp_Result;						// ファイルハンドルセット
					m_graphicContainer[i].gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAMFILE_LOADING; // 読み込み状態：処理開始
					m_graphicContainer[i].gp_ProcessStatus = 0;
					DEBUG_PRINT("eUPMODE_ONE : VramLoad Handle[%d] Name[\"%s\"]\n", m_graphicContainer[i].gp_FileHandle, gp_name );
				}
			}
			break;
		// 上で復帰処理やっちゃってるからとくに何もせず
		case	AppLib::Resources::ProcessStatus::eUPMODE_RETURN:
			{
			}
			break;
		default:
			break;
		}
	}
#if PROJECT_DEBUG
	if( gp_Result == -1 ){
		ERROR_PRINT("__ERROR__ : GraphicVramTexUp nVramRet[%d]\n", gp_Result );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;	// VRAM上げに失敗､エラー
	}
#endif
	// 画像ロードしたらハンドルが返ってくる(DXライブラリの不便さ)
	return gp_Result;
}

//=============================================================================================//
//  グラフィック画像データ単体削除
//		@param		int		gp_type		:	登録VRAMタイプ
//		@param		char *	gp_name		:	画像ファイル名
//		@param		int		gp_mode		:	削除タイプ
//	@return		0->成功  0以外->失敗
int		DxLib::AppFileGraphicManager::_graphicVramTexDelete( const int  gp_type, char* gp_name, const int  gp_mode )
{
	// 画像を事前に登録しておくタイプ処理
	int i = 0;
	int vramRet = 0, gp_EntryMax = 0;

	vramRet = _graphicVramFileMaxCheck( gp_type, &gp_EntryMax );
#if PROJECT_DEBUG
	if( vramRet < 0 ){
		ERROR_PRINT("__ERROR__ : _graphicVramTexDelete[%d]\n", vramRet );
		return ( -2 );	// ERROR
	}
#endif

	// 画像タイプと画像名から絵の登録番号を返す
	i = _graphicVramFileIdBackNumCheck( gp_type, gp_name );
#if PROJECT_DEBUG
	if( i >= gp_EntryMax || i < 0 ){
		ERROR_PRINT("__ERROR__ : _graphicVramFileIdBackNumCheck[%d]\n", i );
		return ( -2 );	// ERROR
	}
#endif

	// カウントが０になったら削除
	{
		auto result = 0;
		switch( gp_mode )
		{
		//----------------------------------------------------------------//
		// 通常（カウントを引いていき0になったら削除
		//----------------------------------------------------------------//
		case AppLib::Resources::ProcessStatus::eDELMODE_NORMAL:
			{
				if( m_graphicContainer[i].gp_FileCount > 0 ){
					m_graphicContainer[i].gp_FileCount --;
				}
				if( m_graphicContainer[i].gp_FileCount == 0 )
				{
					m_graphicContainer[i].gp_FileCount	=   0;
					// グラフィックのロードハンドルを削除
					result = _graphicVramFileFormat( gp_type, &m_graphicContainer[i] );
					m_graphicContainer[i].gp_FileID = -3;								// ファイル番号
					m_graphicContainer[i].gp_FileHandle	= AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;	// ロードハンドル初期化
					m_graphicContainer[i].gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAMFILE_CLEAR;		// 読み込み処理終了：削除
					DEBUG_PRINT("eDELMODE_NORMAL : VramLoad Handle[%d] Name[\"%s\"]\n", m_graphicContainer[i].gp_FileHandle, gp_name );
				}
			}
			break;
		//----------------------------------------------------------------//
		// 強制削除､カウントも0に
		//----------------------------------------------------------------//
		case AppLib::Resources::ProcessStatus::eDELMODE_COER:
			{
				// 強制削除
				if( m_graphicContainer[i].gp_FileCount > 0 )
				{
					m_graphicContainer[i].gp_FileCount	=  0;
					// グラフィックのロードハンドルを削除
					result = _graphicVramFileFormat( gp_type, &m_graphicContainer[i] );
					m_graphicContainer[i].gp_FileHandle = AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;	// ロードハンドル初期化
					m_graphicContainer[i].gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAMFILE_CLEAR;		// 読み込み処理終了：削除
					DEBUG_PRINT("eDELMODE_COER : VramLoad Handle[%d] Name[\"%s\"]\n", m_graphicContainer[i].gp_FileHandle, gp_name );
				}
				// 隠し中を無効に
				m_graphicContainer[i].gp_FileID = -3;
			}
			break;
		//----------------------------------------------------------------//
		// 削除するだけ､カウントは残したまま
		//----------------------------------------------------------------//
		case AppLib::Resources::ProcessStatus::eDELMODE_DIS:
			{
				if( m_graphicContainer[i].gp_FileCount > 0 )
				{
					// グラフィックのロードハンドルを削除
					result = _graphicVramFileFormat( gp_type, &m_graphicContainer[i] );
					// 隠し中の印しチェック
					m_graphicContainer[i].gp_FileID = -2;
				}
			}
			break;
		//----------------------------------------------------------------//
		// 問答無用で全削除
		//----------------------------------------------------------------//
		case AppLib::Resources::ProcessStatus::eDELMODE_COERALL:
			{
				(void)(gp_name);
				(void)(gp_mode);
				// オールフォーマット
				result = gpVramLoadBuffFormatALL();
			}
			break;
		}
	}
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  グラフィック画像データを読み込み（メモリにアップ）
//		@param		int		gp_type		:	画像メモリ登録
//		@param		int		gp_mode		:	画像アップタイプ
//		@param		int		gp_attr		:	登録属性(-1で全て乗せる)
//	@return		0->成功  0以外->失敗
int		DxLib::AppFileGraphicManager::_graphicVramTexAttrUp( const int  gp_type, const int  gp_mode, const int  gp_attr )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_graphicContainer.empty() ) { return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
#endif

	int i;
	auto result = 0;
	// gp_type = -1でeFILE_GRAPHIC_SYSTEMで登録してある全属性画像を上げる
	if( gp_type == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM || (gp_type < 0) )
	{
		for( i = 0; i < AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX; ++ i )
		{
			// 属性チェック
			if( m_graphicContainer[i].gp_FileAttr == gp_attr || ( gp_attr < 0 ) )
			{
				// グラフィック画像データ単体アップ
				result = _graphicVramTexUp( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
								   			const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), gp_mode, 1 );
			}
		}
	}
	else{
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
	// gp_type = -1でeFILE_GRAPHIC_MEMORYで登録してある全属性画像を上げる
	if( gp_type == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY || (gp_type < 0) )
	{
		for( i = 0; i < AppLib::Resources::ProcessStatus::OBJVRAM_LOADRESOURCES_MAX; ++ i )
		{
			// 属性チェック
			if( m_graphicContainer[i].gp_FileAttr == gp_attr || gp_attr < 0 )
			{
				// グラフィック画像データ単体アップ
				result = _graphicVramTexUp( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
								   			const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), gp_mode, 1 );
			}
		}
	}
	else{
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
	DEBUG_PRINT("AppFileGraphic::VramTexAttrUp CLEAR\n");
	// 処理成功
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  グラフィックのロードハンドルを削除
//		@param		int		gp_type		:	登録VRAMタイプ
//		@param		int		gp_mode		:	画像アップタイプ
//		@param		int		gp_attr		:	登録属性(-1で全て削除)
//	@return		0->成功  0以外->失敗
int		DxLib::AppFileGraphicManager::_graphicVramTexAttrDelete( const int  gp_type, const int  gp_mode, const int  gp_attr )
{
#if PROJECT_DEBUG
	// Containerが空か
	if ( m_graphicContainer.empty() ) { return App::FileProcess::eFILE_RESULT_CODE_ERROR; }
#endif

	int	i;
	auto result = 0;
	// gp_type = -1でeFILE_GRAPHIC_SYSTEMで登録してある全属性画像を削除する
	if( gp_type == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM || (gp_type < 0) )
	{
		for( i = 0; i < AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX; ++ i )
		{
			// 属性チェック
			if( m_graphicContainer[i].gp_FileAttr == gp_attr || (gp_attr < 0) )
			{
				// グラフィック画像データ単体削除
				result = _graphicVramTexDelete( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
									   			const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), gp_mode );
			}
		}
	}
	else{
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
	// gp_type = -1でeFILE_GRAPHIC_MEMORYで登録してある全属性画像を削除する
	if( gp_type == AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY || (gp_type < 0) )
	{
		for( i = 0; i < AppLib::Resources::ProcessStatus::OBJVRAM_LOADRESOURCES_MAX; ++ i )
		{
			// 属性チェック
			if( m_graphicContainer[i].gp_FileAttr == gp_attr || (gp_attr < 0) )
			{
				// グラフィック画像データ単体削除
				result = _graphicVramTexDelete( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
									   			const_cast<char*>( m_graphicContainer[i].gp_FileName.c_str() ), gp_mode );
			}
		}
	}
	else{
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
	// 処理成功
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//  グラフィックのロードハンドルを削除
//		@param		int		gp_type				:	登録VRAMタイプ
//		@param		FileGraphicContainer*		:	クラスポインタ
//	@return		0 -> 成功
int		DxLib::AppFileGraphicManager::_graphicVramFileFormat( const int  gp_type, GraphicFileContainer* pGpWork )
{
	auto result = 0;
	int returnCode = App::FileProcess::eFILE_RESULT_CODE_ERROR;
	char * targetFileName = nullptr;
	// 指定のグラフィックをメモリ上から削除する
	switch( gp_type % AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE_MAX )
	{
	// システム
	case AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM:
		{
			// グラフィックをメモリ上から削除する
//			result = dxLib_gpVramBuffLoadFileFormat( (pGpWork)->gp_FileHandle );
			result = gpVramBuffLoadFileFormat( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM, const_cast<char*>( (pGpWork)->gp_FileName.c_str() ) );
			if ( result != -1 ) {
				returnCode = App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
			}
		}
		break;
	// メモリー
	case AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY:
		{
			// グラフィックをメモリ上から削除する
//			result = dxLib_gpVramBuffLoadFileFormat( (pGpWork)->gp_FileHandle );
			result = gpVramBuffLoadFileFormat( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY, const_cast<char*>( (pGpWork)->gp_FileName.c_str() ) );
			if ( result != -1 ) {
				returnCode = App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
			}
		}
		break;
	default:
		// 異常ケース
#if PROJECT_DEBUG
		ERROR_PRINT("__ERROR__ : VramGpFormat Expectation Error[\"%s\"]\n", (pGpWork)->gp_FileName.c_str() );
#endif
		return returnCode;
	}
	// 処理成功
	return returnCode;
}

//=============================================================================================//
//  指定グラフィックがメモリ読み込みされているかチェック
//		@param		int	gp_type		：	登録VRAMタイプ
//		@param		int	gp_name		：	画像名
//	@return		1	->乗ってる
//				0	->乗せ中
//			   -1	->乗せ命令が呼ばれてない
int		DxLib::AppFileGraphicManager::_graphicVramTexUpCheck( const int  gp_type, const char* gp_name )
{
	int checkHandle_ = 0;
	// 名前からグラフィックのロードハンドルを取得
	checkHandle_ = _getGraphicTexVramLoadHandle( gp_type, gp_name );
#if PROJECT_DEBUG
	if( checkHandle_ == -1 ){
		ERROR_PRINT("__ERROR__ : GraphicVramTexUpCheck gp_name[\"%s\"]\n", gp_name );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;	// エラー
	}
#endif
	return  _graphicVramTexUpCheck( gp_type, checkHandle_ );
}
int		DxLib::AppFileGraphicManager::_graphicVramTexUpCheck( const int  gp_type, const int  gp_i )
{
	// グラフィックハンドル直指定バージョン
	int vramRet = 0, gp_BuffMax = 0;

	// メモリへのグラフィックロード可能最大数を取得
	vramRet = _graphicVramFileMaxCheck( gp_type, &gp_BuffMax );
#if PROJECT_DEBUG
	if( vramRet < 0 ){
		ERROR_PRINT("__ERROR__ : GraphicVramGpMaxCheck vramRet[%d]\n", vramRet );
		return ( -2 );	// エラー
	}
	if( gp_i >= gp_BuffMax || gp_i < 0 ){
		ERROR_PRINT("__ERROR__ : GraphicVramTexUpCheck gp_i[%d]\n", gp_i );
		return ( -3 );	// IDがおかしいなら終了
	}
#endif

	if( m_graphicContainer[gp_i].gp_FileCount > 0 && m_graphicContainer[gp_i].gp_FileID == -1 )
	{
		switch( gp_type % AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE_MAX )
		{
		//----------------------------------------------
		// システム
		//----------------------------------------------
		case	AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM:
			// 画像タイプと画像名から絵の登録番号を取得
			m_graphicContainer[gp_i].gp_FileID = _graphicVramFileIdBackNumCheck( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
																				 const_cast<char*>( m_graphicContainer[gp_i].gp_FileName.c_str() ) );// ( char*)は"const char*"をキャストしてる
			break;
		//----------------------------------------------
		// メモリー
		//----------------------------------------------
		case	AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY:
			// 画像タイプと画像名から絵の登録番号を取得
			m_graphicContainer[gp_i].gp_FileID = _graphicVramFileIdBackNumCheck( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
																		         const_cast<char*>( m_graphicContainer[gp_i].gp_FileName.c_str() ) );// ( char*)は"const char*"をキャストしてる
			break;
		default:
			return App::FileProcess::eFILE_RESULT_CODE_ERROR;
		}
	}
	if( m_graphicContainer[gp_i].gp_FileCount > 0 )
	{
		if( m_graphicContainer[gp_i].gp_FileID >= 0 ){
			return ( 1 );	// 乗ってる
		}else{
			return ( 0 );	// 乗せ中
		}
	}
	return App::FileProcess::eFILE_RESULT_CODE_ERROR;	// 乗せ命令もなし
}

//=============================================================================================//
//  指定属性の画像が全て上がってるか調べる
//	※ENUM_GPFILE_LIST～
//	※指定タイプのみピンポイントで調べる用
//		@param		int  gp_Attrtype	:	画像登録属性
//	@return		1->成功(全て上がってる) 
int		DxLib::AppFileGraphicManager::_graphicVramAttrTexUpCheck( const int  gp_Attrtype )
{
	int i;
	for( i = 0; i < AppLib::Resources::ProcessStatus::OBJVRAM_LOADRESOURCES_MAX; ++ i )
	{
		// 同じ属性かどうか調べる
		if( m_graphicContainer[i].gp_FileAttr == gp_Attrtype )
		{
			// 読み込み処理で呼ばれたものか調べる
			// ※登録だけでVRAMに上げて無い場合は弾く
			if( m_graphicContainer[i].gp_LoadingFlag == AppLib::Resources::ProcessStatus::eVRAMFILE_LOADING )// 読み込み開始処理中かどうか
			{
				// ロードハンドルを調べる(読み込んでいるか)
				if( m_graphicContainer[i].gp_FileHandle != AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE )
				{
					// 読み込みが完了してる？
					// ※読み込みが完了していればロードハンドルがgp_FileHandleに入っているはず
				}else{
					// まだ読み込み中か処理中なのでtrueは返さない
//					return ( 2 );
				}
			}else{
				// 読み込み自体命令してない
			}
		}else{
			// 指定した属性と違う
			return App::FileProcess::eFILE_RESULT_CODE_ERROR;
		}
	}
	DEBUG_PRINT("[GRAPH] _graphicVramAttrTexUpCheck() － ALL CLEAR\n");
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;// 全て上がってる
}

//=============================================================================================//
//  全属性の画像で処理中の画像が有るか調べる
//	<<戻り値>>
//		0->読み込み処理中	1->読み込み全終了
int		DxLib::AppFileGraphicManager::_graphicVramAttrTexUpCheckALL()
{
	// ※全タイプ調べる用
	int nCount__ = 0;
	int nResult__ = 0;

	int nGpTypeMax = AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE_MAX;
	int i;
	for( i = 0; i < nGpTypeMax; ++ i )
	{
		// 全属性調べる
		nResult__ = _graphicVramAttrTexUpCheck( i );
		if( nResult__ == 1 )
		{
			nCount__ ++;
			if( nCount__ >= nGpTypeMax ){
				DEBUG_PRINT("[GRAPH] _graphicVramAttrTexUpCheckALL() － CLEAR\n");
				return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;// 全属性の読み込みが終わっている
			}
		}
	}
	// 読み込み処理中なのが有る
	return App::FileProcess::eFILE_RESULT_CODE_RUNNING;
}

//=============================================================================================//
//  指定ファイルの画像番号を取得
//		@param		char * gp_name			:	テクスチャファイル名
//	@return		登録してあるファイル番号 
int		DxLib::AppFileGraphicManager::_graphicVramTexEntryNumCheck( const char* gp_name )
{
	// 画像タイプと画像名から絵の登録番号を返す
	int i = _graphicVramFileIdBackNumCheck(AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM, gp_name );
	int nGraphID_ = 0;

	nGraphID_ = m_graphicContainer[i].gp_FileNum;// ファイルの指定番号
#if PROJECT_DEBUG
	if( nGraphID_ == -1 ){
		ERROR_PRINT("__ERROR__ : _graphicVramTexEntryNumCheck ID[%d]\n", nGraphID_ );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	// 登録してあるファイル番号を返す
	return ( nGraphID_ );
}

//=============================================================================================//
//  指定ファイルの画像番号を取得(※画像タイプ指定機能付き)
//	@param
//		int		gp_type		:	登録VRAMタイプ
//		char *	gp_name		:	テクスチャファイル名
//	@return
//		成功->登録ファイル番号	失敗->-1 
int		DxLib::AppFileGraphicManager::_graphicVramTexEntryNumCheckType( const int  gp_type, const char* gp_name )
{
	// 画像タイプと画像名から絵の登録番号を返す
	int i = _graphicVramFileIdBackNumCheck( gp_type, gp_name );
	int nGraphID_ = 0;
	
	nGraphID_ = m_graphicContainer[i].gp_FileNum;// ファイルの指定番号
#if PROJECT_DEBUG
	if( nGraphID_ == -1 ){
		ERROR_PRINT("__ERROR__ : GpVramPointerSearch ID[%d]\n", nGraphID_ );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	// 登録してあるファイル番号を返す
	return ( nGraphID_ );
}

//=============================================================================================//
//  登録IDから名前画像名を返す
//		@param		int	gp_type			:	登録VRAMタイプ
//		@param		int	index			:	登録ID
//	@return		登録してあるファイル名 
const char *	DxLib::AppFileGraphicManager::_graphicEntryNameGet( const int  gp_type, const int  index )
{
	int gp_EntryMax = 0;
	int i = 0;
	i = index;//dxLibGpVramPointerSearch( index );
#if PROJECT_DEBUG
	if( _graphicVramFileMaxCheck( gp_type, &gp_EntryMax ) < 0 ){
		return NULL;
	}
#endif
	const char * returnStr = m_graphicContainer[i].gp_FileName.c_str();
	return returnStr;
}

//=============================================================================================//
//  グラフィック管理システムランタイム
//  ※毎フレームコール 
int		DxLib::AppFileGraphicManager::_graphicVramLibRuntime()
{
#if 0
	int i = 0;
	
	if( (gpGraphic_dxProc)->gp_ProcId > -1 )
	{
		if( (gpGraphic_dxProc)->gp_ProcState == DxLibGp::eVRAMUP_STOP )
		{
			(gpGraphic_dxProc)->gp_ProcState = DxLibGp::eVRAMUP_LOAD;
		}
		else
		{
			// 空きがないか記録されてる空きよりIDが小さいなら
			if( (gpGraphic_dxProc)->gp_ProcAkiId > (gpGraphic_dxProc)->gp_ProcId )
				(gpGraphic_dxProc)->gp_ProcAkiId = (gpGraphic_dxProc)->gp_ProcId;
			
			(gpGraphic_dxProc)->gp_ProcId		= -1;
			(gpGraphic_dxProc)->gp_ProcState	= DxLibGp::eVRAMUP_STOP;// 処理の状況
			
			for( i = 0; i < AppLib::Resources::FileProcess::GPVRAM_TEXTUREENTRY_MAX; i ++ )
			{
				if( (gpGraphic_dxSys + i)->gp_FileNum >= 0 )	// UNIファイル番号、マイナスなら未使用
				{
					(gpGraphic_dxProc)->gp_ProcId = i;	// 処理中のID,マイナスなら処理してない
					break;
				}
			}
			return ( 1 );
		}
	}
#endif
	return ( 0 );
}

//=============================================================================================//
//  
//  
int		DxLib::AppFileGraphicManager::_graphicVramUpState()
{
#if 0
	if( (gpGraphic_dxProc) == NULL ){ return ( -1 ); }
	
	// 読み込むものがない
	if( (gpGraphic_dxProc)->gp_ProcId < 0 )	// 処理中のID,マイナスなら処理してない
	{
		return ( 0 );
	}
	else if( (gpGraphic_dxProc)->gp_ProcState == DxLibGp::eVRAMUP_STOP )	// 読み込むところ
	{
		return ( 1 );
	}
	else
	{
		return ( 2 );	// ファイル読み込み中
	}
#else
	return ( 0 );
#endif
}

//=============================================================================================//
//  指定のグラフィックハンドルと、同じグラフィックハンドルから派生している
//	グラフィックハンドル( DerivationGraph で派生したハンドル、LoadDivGraph 読み込んで作成された複数のハンドル )を
//	一度に削除する
//	戻り値		０：成功
//			  －１：エラー発生 
int		DxLib::AppFileGraphicManager::_graphicVramSharingHandleFormat( const int  nSharHandle )
{
	const int nReturn = DxLib::DeleteSharingGraph( nSharHandle );
#if PROJECT_DEBUG
	// エラーチェック
	if( nReturn == -1 ){
		ERROR_PRINT("__ERROR__ : DeleteSharingGraph Handle[%d]\n", nSharHandle );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	return App::FileProcess::eFILE_RESULT_CODE_SUCCESS;
}

//=============================================================================================//
//	画像ファイルの分割読み込み(アニメーション連番画像等)
//	※現時点では事前登録は行わず随時読み込む
//	引数	arch_type				:	アーカイブタイプ
//			gp_name			        :	分割読み込みする画像ファイル文字列のポインタ
//			gpDivNum				:	画像の分割総数
//			gpDivSrcX, gpDivSrcY    :	画像の横向きに対する分割数と縦に対する分割数
//			gpDivSizeW, gpDivSizeH	:	分割された画像一つの大きさ
//			pHandleBuf				:	分割読み込みして得たグラフィックハンドルを
//										保存するint型の配列へのポインタ 
//	戻り値	   ０：成功 
//			 －１：エラー発生 
int		DxLib::AppFileGraphicManager::_graphicAnimationGraphDivLoad(const int  arch_type,
																	char * gp_name, int  gpDivNum,
																	int    gpDivSrcX, int  gpDivSrcY, int  gpDivSizeW, int  gpDivSizeH,
																	int * pHandleBuf )
{
	int	fileResult = 0;

	char strLoadPath[256] = {};

	// パス取得
	fileLoadGetAccessPath( arch_type, gp_name, strLoadPath );
	
	// 分割して読み込み、引数の[ int * HandleBuf ]にロードハンドルが格納される
	fileResult = DxLib::LoadDivGraph( strLoadPath, gpDivNum, gpDivSrcX, gpDivSrcY, gpDivSizeW, gpDivSizeH, pHandleBuf ) ;
#if PROJECT_DEBUG
	// エラーチェック
	if( fileResult == -1 ){
		ERROR_PRINT("__ERROR__ : LoadDivGraph Name[%s]\n", gp_name );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;
	}
#endif
	return ( fileResult );
}

//=============================================================================================//
//  画像が登録可能かを返す
//	(空いている番号を返す、DXLIB_GRAPHIC_VRAM_WORKの最大分チェック)
//	@return		成功->空きインデックス		-1:エラー
int		DxLib::AppFileGraphicManager::_graphicEntryUseIdCheck()
{
	int i = 0;
	// 未使用箇所(ID)を探す
	for( i = 0; i < AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX; i ++ )
	{
		// eGPFILE_HANDLE_NONUSE なら未登録扱いになっている
		// 未登録かどうか
		if( m_graphicContainer[i].gp_FileHandle == AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE )
		{
			// 見つかればインデックスを返す
			return ( i );
		}
	}
	// 全て使われていて空きが無い
	ERROR_PRINT("__ERROR__ : dxLib_gpGraphicEntryUseIdCheck NotUseID\n");
	return App::FileProcess::eFILE_RESULT_CODE_ERROR;
}

///////////////////////////////////////////////////////////////////////////////////////
/*
*	簡易化ラップ関数群
*/
///////////////////////////////////////////////////////////////////////////////////////

//=============================================================================================//
// 	画像ファイル登録処理(引数簡略化版)
//	ARCHIVE_SYSTEM 固定
//		@param		int  gp_type			:	登録VRAMタイプ
//		@param		char * gp_name			:	画像ファイル名
//		@param		int  gp_file			:	画像ファイルインデックス
//		@param		int  gp_attr			:	画像ファイル属性
int		DxLib::AppFileGraphicManager::_wrapGraphicVramEntry( const int gp_type, char* gp_name, const int  gp_file, const int  gp_attr )
{
	return _graphicVramTextureEntry( gp_type, 
									 gp_name, 
									 AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
									 gp_file, 
									 gp_attr );
}
int		DxLib::AppFileGraphicManager::_wrapGraphicMemoryVramEntry( char* gp_name, const int  gp_file, const int  gp_attr )
{
	return _graphicVramTextureEntry( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
									 gp_name, 
									 AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_MEMORY,
									 gp_file, 
									 gp_attr );
}
//=============================================================================================//
//	画像の登録→読み込みを一気に行う
//		@param		int  gp_type			:	登録VRAMタイプ
//		@param		char * gp_name			:	画像ファイル名
//		@param		int  gp_file			:	画像ファイルインデックス
//		@param		int  gp_attr			:	画像ファイル属性
//	@return
//		成功	->	ロードハンドル
//		失敗	->	-1
int		DxLib::AppFileGraphicManager::_wrapGraphicVramSetup( const int  gp_type, char* gp_name, const int  gp_file, const int  gp_attr )
{
	// 画像の登録
	int	nHandle = -1;
	nHandle = _graphicVramTextureEntry( gp_type, gp_name, AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM, gp_file, gp_attr );
	if( nHandle != 0 ){
		ERROR_PRINT("__ERROR__ : WrapGraphicVramSetup Name[\"%s\"]\n", gp_name );
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;	// エラー
	}

	// 画像のメモリへの読み込み
	int	nResult	= _graphicVramTexAttrUp( gp_type, AppLib::Resources::ProcessStatus::eUPMODE_ONE, gp_attr );
	if( nResult != 0 ){
		ERROR_PRINT("__ERROR__ : GraphicVramTexAttrUp Failed\n");
		return App::FileProcess::eFILE_RESULT_CODE_ERROR;	// エラー
	}
	return ( nHandle );	// ロードハンドルを返す
}



