#pragma once

///////////////////////////////////////////////////////////////////////////
//
//
//	2019.
///////////////////////////////////////////////////////////////////////////

using namespace AppLib::Resources;

/**
 *	@class	ファイル毎管理データコンテナクラス
 *			※基本は親クラス内に定義して使用する、継承使用厳禁
 */
namespace DxLib
{
	class VramFileContainer
	{
	public:
		VramFileContainer(){
			DEBUG_PRINT("APP INIT : VramFileContainer コンストラクタ\n");
		}
		~VramFileContainer(){
			DEBUG_PRINT("APP INIT : VramFileContainer デストラクタ\n");
		}
		
	public:

		int			vv_VramCount;		// 読み込みカウント(※ eDEF_VVRAM_BUFFER_FLAG_USED がセットされていると登録して使用している)
		int			vv_FileHandle;		// ファイルロードハンドル
		std::string	vv_TextureName;		// 読み込みテクスチャネーム
		char *		vv_ReadBuff;		// 読み込みファイルバッファ
		int			vv_VramType;		// VRAMタイプ
		int			vv_WIDTH;			// テクスチャサイズＷ
		int			vv_HEIGHT;			// テクスチャサイズＨ

	public:

		void		dataInit();
	};
}



/* End appVramFileContainer.h */

