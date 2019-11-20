#pragma once

#include "DxLib.h"

///////////////////////////////////////////////////////////////////////////
//
// リソース関係処理ステータス定義一覧
//
//
///////////////////////////////////////////////////////////////////////////

namespace AppLib
{
	namespace Resources
	{
		// @enum 画像ファイル登録属性
		namespace Attribute
		{
			typedef enum
			{
				eRESFILE_ATTRIBUTE_TYPE_ALL = -1,			// @param 全属性
				eRESFILE_ATTRIBUTE_TYPE_MAIN = 0,			// @param 今の所使わない
				eRESFILE_ATTRIBUTE_TYPE_SYSTEM,				// @param システム画像
				eRESFILE_ATTRIBUTE_TYPE_BACKGROUND,			// @param 背景画像
				eRESFILE_ATTRIBUTE_TYPE_SCRIPT,				// @param スクリプト
				eRESFILE_ATTRIBUTE_TYPE_BGM,				// @param BGM
				eRESFILE_ATTRIBUTE_TYPE_VOICE,				// @param VOICE
				eRESFILE_ATTRIBUTE_TYPE_SE,					// @param SE
				eRESFILE_ATTRIBUTE_TYPE_MOVIE,				// @param MOVIE
				eRESFILE_ATTRIBUTE_TYPE_EFFECT,				// @param エフェクト
				eRESFILE_ATTRIBUTE_TYPE_BINARY,				// @param バイナリデータ(アーカイブ)
				eRESFILE_ATTRIBUTE_TYPE_DATABASE,			// @param データベース(CSV)
				eRESFILE_ATTRIBUTE_TYPE_SAVEDATA,			// @param セーブデータ
				eRESFILE_ATTRIBUTE_TYPE_3DMODEL,			// @param 3DModel

				ENUM_RESFILE_ATTRIBUTE_TYPE_MAX,			// 登録属性リスト最大
			} ENUM_RESFILE_ATTRIBUTE_TYPE_LIST;
		}

		// @enum アーカイブ処理設定
		namespace Archive
		{
			const static char * 	ARCHIVE_FILE_EXTENS = "KAF";		// アーカイブファイルの独自拡張子
			const static char * 	ARCHIVE_FILE_PASSWORD = "PASSWORD";	// アーカイブファイルの読み込みパスワード

			// ロードプライオリティ
			const static int		ARCHIVE_FILE_LOADER_PRI_FOLDER = 1;
			const static int		ARCHIVE_FILE_LOADER_PRI_ARCHIVE = 0;

			const static int		ARCHIVE_FILE_LOADER_DXA = 1;		// 読み込み対象：アーカイブファイル本体
			const static int		ARCHIVE_FILE_LOADER_PACKFILE = 0;	// 読み込み対象：アーカイブファイルの中の個別ファイル
			
			// @enum 
			typedef enum
			{
				eARCHIVE_FILETYPE_NONE			= 0,		//! @param	今の所使わない
				eARCHIVE_FILETYPE_RESOURCES		= 1,		//! @param	システム画像(UI等)
				eARCHIVE_FILETYPE_SCRIPT		= 2,		//! @param	スクリプト
				eARCHIVE_FILETYPE_BGM,						//! @param	BGM
				eARCHIVE_FILETYPE_VOICE,					//! @param	VOICE
				eARCHIVE_FILETYPE_SE,						//! @param	SE
				eARCHIVE_FILETYPE_MOVIE,					//! @param	MOVIE
				eARCHIVE_FILETYPE_EFFECT,					//! @param	エフェクト
				eARCHIVE_FILETYPE_BINARY,					//! @param  バイナリデータ(アーカイブ)
				eARCHIVE_FILETYPE_DATABASE,					//! @param  データベース(CSV)
				eARCHIVE_FILETYPE_JSON,						//! @param	Jsonデータ
				eARCHIVE_FILETYPE_SAVEDATA,					//! @param  セーブデータ
				eARCHIVE_FILETYPE_MODEL,					//! @param  
				
				ENUM_ARCHIVE_FILETYPE_MAX,
				ENUM_ARCHIVE_FILELIST_MAX = eARCHIVE_FILETYPE_EFFECT + 1,

			} ENUM_ARCHIVE_FILETYPE_LIST;
		}

		namespace Info
		{
			// projectファイルから見ての相対パス
			const static std::string	RESOURCES_LOAD_ROOT_PATH = "../../resources/asset/";
			const static std::string	RESOURCES_SCRIPT_LOAD_ROOT_PATH = "../../resources/script/";
		}

		namespace Parameter
		{
			namespace EntryIndex
			{
				/**
				 *	@enum	画像ファイルの登録インデックスリスト
				 */
				typedef enum
				{
					// eRESFILE_NAME_GAME_FICTION_IMAGE				= 1,		//! @param Fictionイメージ
					// eRESFILE_NAME_GAME_COMPANY_LOGO				= 2,		//! @param 会社ロゴ
					// eRESFILE_NAME_GAME_COPYRIGHTIMAGE_DXLIB		= 3,		//! @param DXライブラリロゴ
					// eRESFILE_NAME_GAME_COPYRIGHTIMAGE_ADX2LE		= 4,		//! @param CRI ADX2ロゴ
					// eRESFILE_NAME_GAME_COPYRIGHTIMAGE_EFFEKSEER	= 5,		//! @param 

					// eRESFILE_NAME_GAME_TITLE_TEX_BG				= 10,		//! @param 
					// eRESFILE_NAME_GAME_TITLE_TEX_MENU_UI			= 11,		//! @param 
					// eRESFILE_NAME_GAME_TITLE_TEX_OBJECT			= 12,

					// ERROR
					eRESFILE_NAME_APP_ERROR_TEX					= 9998,		//! @param 
					// 登録最大
					ENUM_RESOURCES_FILE_ENTRY_INDEX_MAX			= 9999		//! @param 

				} ENUM_RESFILE_FILE_ENTRY_INDEX_LIST;
			}

			namespace EntryType
			{
			}
			/**
			 *	@enum	画像ファイルの登録タイプリスト
			 */
			typedef enum 
			{
				eGRAPHIC_FILE_ENTRY_NONE	= 0,		//! @param 未設定
				eGRAPHIC_FILE_ENTRY_APPSTART,			//! @param ゲーム起動時
				eGRAPHIC_FILE_ENTRY_GLOBAL,				//! @param グローバル
				eGRAPHIC_FILE_ENTRY_COMMON,				//! @param 汎用
				eGRAPHIC_FILE_ENTRY_SCENE_TITLE,		//! @param タイトルシーン
				
				ENUM_GRAPHIC_FILE_ENTRY_TYPE_MAX
			} ENUM_GRAPHIC_FILE_ENTRY_TYPE;
		}

		namespace FileSystem
		{
			// 読み込みハンドルリクエスト可能数
			const static unsigned int	LOAD_FILEHANDLE_REQUEST_MAX	= ( 15 );
			// 同時読み込みリクエスト可能数
			const static unsigned int	LOAD_FILE_ASYNC_REQUEST_MAX = ( 20 );

			const static int			FILE_LIB_ASYNC_LOAD_TRUE	= 1;	// 非同期読み込み
			const static int			FILE_LIB_ASYNC_LOAD_FALSE	= 0;	// 同期読み込み
			
			// ファイル読み込みパス
			const static std::string	RESOURCES_FILELOAD_DIRECTORY	= "resources";
			const static std::string	RESOURCES_FILELOAD_ROOTDIR		= "/";
			const static std::string	RESOURCES_FILELOAD_PATH			= "/resources/asset/";

			// [DUMMY]
			const static char*			RESOURCES_FILE_ROOT = "C:/ProgramBox/Project/Develop/cervidae_lib/resources/asset";

			// @enum 
			typedef enum
			{
				eDxULIBLRMs_Non		= 0,// 未使用
				eDxULIBLRMs_Wait	= 1,// 待機中（読み込み開始前の待機）
				eDxULIBLRMs_Init	= 2,// 初期化中（読み込み開始）
				eDxULIBLRMs_Load	= 3,// 読み込み中
				eDxULIBLRMs_CBWait	= 4,// コールバック関数順番待ち
				eDxULIBLRMs_CBRun	= 5,// コールバック関数実行中
				eDxULIBLRMs_End		= 6,// 読み込み終了
				eDxULIBLRMs_MAX
			} ENUM_DxULIBLRMs_LIST;
		}

		namespace FileVram
		{
			const static unsigned int	DEF_SYSTEMVRAMLOAD_MAX		= 15;	//! @param テクスチャファイルVRAM読み込み可能最大数
			const static unsigned int	DEF_MEMORYVRAMLOAD_MAX		= 10;	//! @param 
			// メモリに上げられる最大数
			const static unsigned int	FILE_RESOURCES_VRAMUP_POSSIBLE_MAX = 20;

			typedef enum
			{
				eDEF_VVRAM_BUFFER_FLAG_NON		= 0,		// 未使用
				eDEF_VVRAM_BUFFER_FLAG_USED		= (1 << 0),	// 使用済みのバッファ
				eDEF_VVRAM_BUFFER_FLAG_NEW		= (1 << 1),	// 新規バッファ
				eDEF_VVRAM_BUFFER_FLAG_CLEAR	= (1 << 2),	// バッファクリアした

			} ENUM_VVRAM_BUFFER_FLAG;

			namespace Info
			{

			}
		}

		namespace ProcessStatus
		{
			const unsigned int		DEF_SYSTEMVRAMLOAD_MAX		= 20;	//! @param テクスチャファイルVRAM読み込み可能最大数
			const unsigned int		DEF_MEMORYVRAMLOAD_MAX		= 10;	//! @param 

			/*
			 *	NOTE:グラフィックリソースの登録可能数とメモリロード可能数は違う
			 */
			// テクスチャファイル最大読み込み数
			const static unsigned int	GPVRAM_LOADRESOURCES_MAX = ( DEF_SYSTEMVRAMLOAD_MAX );	//! @param テクスチャファイルVRAM読み込み可能最大数
			const static unsigned int	OBJVRAM_LOADRESOURCES_MAX = ( DEF_MEMORYVRAMLOAD_MAX );
			// テクスチャファイル名設定最大
			const static unsigned int	GPVRAM_LOADTEXFILENAME = ( 64 );
			// テクスチャファイル登録最大数
			const static unsigned int	GPVRAM_TEXTUREENTRY_MAX = ( 30 );

			typedef enum
			{
				eFILE_GRAPHIC_SYSTEM = 0,		// システムテクスチャ
				eFILE_GRAPHIC_MEMORY,			// メモリ（セーブロード）


				ENUM_RESOURCES_VRAM_TYPE_MAX,

			} ENUM_RESOURCES_VRAM_TYPE;

			typedef enum
			{
				eVRAM_FILE_STATUS_NOUSE = -1,	// 未使用
				eVRAM_FILE_STATUS_ENTRYCLEAR,	// 登録完了
				eVRAM_FILE_STATUS_LOADING,		// 読み込み中

			} ENUM_RESOURCES_FILE_STATUS;

			typedef enum
			{
				eUPMODE_NORMAL,					// 通常（カウントを足していき1になったらメモリにアップ）
				eUPMODE_ONE,					// VRAMに乗ってなかったらアップ､もう乗ってたらなんもせず
				eUPMODE_RETURN,					// DELMODE_DISした時の復帰用

			} ENUM_VRAM_UPPROCESS;

			typedef enum
			{
				eDELMODE_NORMAL,				// 通常（カウントを引いていき0になったら削除）
				eDELMODE_COER,					// 強制削除､カウントも0に
				eDELMODE_DIS,					// 削除するだけ､カウントは残したまま
				eDELMODE_COERALL,				// 問答無用で全削除

			} ENUM_VRAM_DELPROCESS;

			typedef enum
			{
				eVRAMUP_STOP = 0,				// なんもしてない
				eVRAMUP_LOAD,					// 読み込み待ち

			} ENUM_VRAM_UPRESULT;

			typedef enum
			{
				eVRAMMODE_TEXUP = 0,			// VRANアップ
				eVRAMMODE_TEXDEL,				// VRAM削除

				ENUM_VRAM_PROCTYPE_MAX

			} ENUM_VRAM_PROCESS_TYPE;

			typedef enum
			{
				eVRAMFILE_NOENTRY = 0,			// 画像ファイル登録
				eVRAMFILE_CLEAR = -1,			// 読み込み処理終了：削除
				eVRAMFILE_LOADING,				// 読み込み処理開始

			} ENUM_VRAM_FILELOAD;

			typedef enum
			{
				eGPFILE_HANDLE_NONUSE = -1,		// ファイルハンドルは使用されていない
				eGPFILE_HANDLE_VRAMLOADING,

			} ENUM_VRAM_HANDLE_STATUS;
		}

		/**
		 *	TODO:今後管理方法を修正予定 2019.07.12
		 */
		const static char* ResourcesFile_Name01 = "001_File.jpg";
		const static char* ResourcesFile_Name02 = "002_File.jpg";
		const static char* ResourcesFile_Name03 = "003_File.png";
		const static char* ResourcesFile_Name04 = "004_File.jpg";


	}/* namespace Resources */
}/* namespace AppLib */


// ファイル操作
#define DX_FILE_OPEN( fname )	FileRead_open( fname, false )
#define DX_FILE_CLOSE( h )		FileRead_close( h )
#define DX_FILE_IDOL( h )		FileRead_idle_chk( h )
#define DX_FILE_EOF( h )		FileRead_eof( h )
#define DX_FILE_READ			FileRead_read
#define DX_FILE_SIZE( fname )	FileRead_size( fname )
#define DX_FILE_GETC( h )		FileRead_getc( h )




/* End appResourcesConfig.h */


