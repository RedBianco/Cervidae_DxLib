
#pragma once

///////////////////////////////////////////////////////////////////////////
//
//	グラフィックファイル管理システム
//
//	appFileGraphic
///////////////////////////////////////////////////////////////////////////

#include "appVramControl.h"

/**
 *	@class リソースファイルの登録に使用する情報
 */
namespace DxLib
{
	/**
	 * 
	 */
	class GraphicFileContainer
	{
	public:
		GraphicFileContainer() {
			gp_FileCount = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_NOUSE;
			gp_FileArch = 0;
			gp_FileNum = -1;
			gp_FileAttr = 0;
			gp_FileID = -3;
			gp_FileHandle = AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE;
			gp_LoadingFlag = AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_NOUSE;
		}
		~GraphicFileContainer() {
		}

	public:

		int				gp_FileCount;		// 使用カウント：読み込み状態(-1:何も無し)
		int				gp_FileArch;		// ファイルアーカイブINDEX
		int				gp_FileNum;			// ファイルの指定番号
		std::string		gp_FileName;		// 画像テクスチャネーム
		int				gp_FileAttr;		// ファイルの登録属性
		int				gp_FileID;			// 画像ファイルインデックス
		int				gp_FileHandle;		// 画像テクスチャロードハンドル格納用
		int				gp_LoadingFlag;		// 読み込み処理で呼ばれたものか

		int				gp_TexWidth;		// テクスチャサイズWidth
		int				gp_TexHeight;		// テクスチャサイズHeight
		int				gp_ProcessStatus;	// 
	};


	/**
	 *
	 */
	class AppFileGraphicManager : public AppVramController
	{
	public:
		AppFileGraphicManager();
		virtual ~AppFileGraphicManager();

	public:
		// ロードできる数を決めて管理
		std::array< 
				DxLib::GraphicFileContainer, 
				AppLib::Resources::ProcessStatus::GPVRAM_LOADRESOURCES_MAX >	m_graphicContainer;

		bool	isProcessClear;

	public:

		AppFileGraphicManager * 	createInstance();

		// 管理システム基本初期化
		bool	_graphicSystemInit();

		// 管理システム終了処理
		bool	_graphicSystemExit();

		// 画像タイプと画像名から絵の登録番号を返す
		int		_graphicVramFileIdBackNumCheck( const int  gp_type, const char* gp_name );

		// タイプと名前からグラフィックのロードハンドルを取得
		int		_getGraphicTexVramLoadHandle( const int  gp_type, const char* gp_name );

		// 有効(読み込み中)グラフィックハンドルの数を取得する
		int		_getGraphicValiditLoadHandle();

		// メモリへのグラフィックロード可能最大数を取得
		int		_graphicVramFileMaxCheck( const int  gp_type, int* gp_Vrammax, GraphicFileContainer** = NULL );

		// グラフィック登録数を取得
		int		_graphicVramFileEntryNumCheck( const int  gp_type = AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM );

		// グラフィック画像の登録データを削除
		int		_graphicVramFileEntryDel( const int  gp_type, char* gp_name );

		// グラフィック画像を登録(登録VRAMタイプ,画像名,登録ファイルINDEX,画像ファイル番号,画像登録属性)
		int		_graphicVramTextureEntry( const int  gp_type, const char * gp_name, const int  gp_arc, const int  gp_file, const int  gp_attr );

		// グラフィック画像データファイル単体読み込みメモリアップ
		int		_graphicVramTexUp( const int  gp_type, char* gp_name, const int  gp_mode = AppLib::Resources::ProcessStatus::eUPMODE_NORMAL, int  check_num = 1 );
								 
		// グラフィック画像データ単体削除
		int		_graphicVramTexDelete( const int  gp_type, char* gp_name, const int  gp_mode = AppLib::Resources::ProcessStatus::eUPMODE_NORMAL );

		// グラフィック画像データを読み込み（メモリにアップ）
		int		_graphicVramTexAttrUp( const int  gp_type, const int  gp_mode, const int  gp_attr );

		// グラフィック画像データ指定属性タイプ削除
		int		_graphicVramTexAttrDelete( const int  gp_type, const int  gp_mode, const int  gp_attr );

		// グラフィックのロードハンドルを削除
		int		_graphicVramFileFormat( const int  gp_type, GraphicFileContainer* pGpWork );

		// 指定グラフィックがメモリ読み込みされているかチェック
		int		_graphicVramTexUpCheck( const int  gp_type, const char* gp_name );
		int		_graphicVramTexUpCheck( const int  gp_type, const int  gp_i );

		// 指定属性の画像が全て上がってるか調べる
		int		_graphicVramAttrTexUpCheck( const int  gp_Attrtype );

		// 全属性の画像で処理中の画像が有るか調べる
		int		_graphicVramAttrTexUpCheckALL();

		// 指定ファイルの画像番号を取得(※画像ネームのみ指定)
		int		_graphicVramTexEntryNumCheck( const char* gp_name );

		// 指定ファイルの画像番号を取得(※画像タイプ指定付き)
		int		_graphicVramTexEntryNumCheckType( const int  gp_type, const char* gp_name );

		// 登録IDから名前画像名を返す
		const char * _graphicEntryNameGet( const int  gp_type, const int  index );

		// グラフィックファイルランタイム
		int		_graphicVramLibRuntime();

		// 
		int		_graphicVramUpState();

		// 指定のグラフィックハンドルと、同じグラフィックハンドルから派生している
		// グラフィックハンドル( DerivationGraph で派生したハンドル、LoadDivGraph 読み込んで作成された複数のハンドル )を一度に削除する
		int		_graphicVramSharingHandleFormat( const int  nSharHandle );

		// 画像ファイルの分割読み込み(アニメーション連番画像等)
		// ※現時点では事前登録は行わずリアルタイム読み込み
		int		_graphicAnimationGraphDivLoad(	const int  arch_type,
												char * gp_name, int  gpDivNum,
												int    gpDivSrcX, int  gpDivSrcY, int  gpDivSizeW, int  gpDivSizeH,
												int * pHandleBuf );

		// 画像が登録可能かを返す(空いている番号を返す、DXLIB_GRAPHIC_VRAM_WORKの最大分チェック)
		int		_graphicEntryUseIdCheck();


		/*
		 *	簡易化ラップ関数群
		 */

		// eFILE_GRAPHIC_SYSTEMタイプの画像VRAM登録簡易処理
		int		_wrapGraphicVramEntry( const int  gp_type, char* gp_name, const int  gp_file, const int  gp_attr );
		// eFILE_GRAPHIC_MEMORYタイプの画像VRAM登録簡易処理
		int		_wrapGraphicMemoryVramEntry( char* gp_name, const int  gp_file, const int  gp_attr );
		// 画像の登録→読み込みを一気に行う
		int		_wrapGraphicVramSetup( const int  gp_type, char* gp_name, const int  gp_file, const int  gp_attr );


	};
}


/* End appFileGraphic.h */

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 