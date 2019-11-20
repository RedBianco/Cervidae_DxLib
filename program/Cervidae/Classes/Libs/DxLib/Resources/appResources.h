#pragma once

/**
 *  【読み込みクラス図】 
 *  ※ファイルの登録可能最大数と読み込み可能最大数を分けている設計なのでクラスが登録管理用、読み込み管理用で分かれている
 * 
 *	◯大元ファイル管理
 *	class AppFileGraphicManager
 * 
 *  ◯
 * 
 */

///////////////////////////////////////////////////////////////////////////
//  VRAMファイル管理システム利用方法
//  [画像登録]
//  _graphicVramTextureEntry(	Resources::FileProcess::eFILE_GRAPHIC_SYSTEM,
//			       				"画像ファイル名.png", 
//								enum ENUM_RESFILE_FILE_ENTRY_INDEX_LIST,
//								enum ENUM_GRAPHIC_FILE_ENTRY_TYPE );
//  [画像VRAMアップ]
//  _graphicVramTexAttrUp(	Resources::FileProcess::eFILE_GRAPHIC_SYSTEM,
//							enum ENUM_VRAM_UPPROC,
//							enum ENUM_GRAPHIC_FILE_ENTRY_TYPE );
//  [アップ画像削除]
//  _graphicVramTexAttrDelete(	Resources::FileProcess::eFILE_GRAPHIC_SYSTEM, 
//								"画像ファイル名.png", 
//								enum ENUM_VRAM_DELPROC );
///////////////////////////////////////////////////////////////////////////

#include "Texture/Archive/appArchiveFileControl.h"
#include "Texture/appVramFileManage.h"
#include "Texture/appFileGraphicControl.h"
#include "Texture/appFileGraphic.h"
#include "Texture/appVramControl.h"
#include "Texture/appVramContainer.h"

#include "Texture/appVramFileManage.h"


/* End appResources.h */


