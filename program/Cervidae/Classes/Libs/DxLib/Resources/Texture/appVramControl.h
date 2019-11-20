
#pragma once

///////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////

#include "appFileSystem.h"
#include "appVramContainer.h"

/**
 *	@class リソースファイルの読み込み、削除管理に使用する情報
 */
namespace DxLib
{
	class AppVramController : public AppFileSystem
	{
	public:

		AppVramController();
		virtual ~AppVramController();

	public:

		std::vector< VramFileContainer >	m_FileContainer;
	//	std::vector< VramFileContainer* >	m_FileContainer;

	public:

		// VRAM管理システム基本初期化処理
		bool	gpVramFileSystemInit();

		// VRAM管理システム終了処理
		void	gpVramFileSystemExit();
		
		// VRAM管理システムランタイム
		void	gpVramFileRuntime();

		// グラフィックファイルのメモリへのロード
		int		gpVramFileVramLoad( const int archive_type, const char* vvfile_name, int  vvram_type );

		// 指定のグラフィックをメモリ上から削除する
		int		gpVramBuffLoadFileFormat( const int vram_type, char* vvfile_name );

		// ※ハンドル指定関数ではvector構造削除クリアはされないので直接呼ぶのは禁止※
		int		gpVramBuffLoadFileFormat( const int file_handle );

		// メモリにある画像を全て削除
		int		gpVramLoadBuffFormatALL();

		// メモリにある指定グラフィックのサイズを得る
		int		gpVramLoadFileGetSize( const int vram_type, char* vvfile_name, int* pFileRectW, int* pFileRectH );
		int		gpVramLoadFileGetSize( const int file_handle, int* pFileRectW, int* pFileRectH );

		// 名前からVRAMファイルハンドルを取得
		int		gpVramLoadFileHandleGet( const char* vvfile_name );

		// 名前からデータINDEXを取得
		int		gpVramGetDataIndex( char* vvfile_name );
		int		gpVramGetDataIndex( const int file_handle );

		// 指定ファイルのVRAMタイプ設定を取得
		int		gpVramGetVVramType( const char* vvfile_name );

		// 指定ファイルハンドルの配列登録情報を削除する
		int		gpVramEntryDataClear( const char* vvfile_name );
		// 指定ファイルネームの配列登録情報を削除する
		int		gpVramEntryDataClear( const int file_handle );
		int		gpVramEntryDataClearALL();

		// 空き番号を探す(※削除されて空きが出来たインデックスを探す)
		int		gpVramGetNotUseListIndex();

	};
}




 /* End appVramControl.h */





