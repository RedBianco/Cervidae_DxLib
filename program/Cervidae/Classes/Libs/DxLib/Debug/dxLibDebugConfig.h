#pragma once


//=================================================================================//
//  dxLibDebugConfig.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/31.
//=================================================================================//


namespace DxLib
{
	namespace DebugConfig
	{
		// @enum	デバッグモード登録タイプ
		typedef enum
		{
			eDEBUG_TYPE_NONE		= -1,
			eDEBUG_TYPE_MAIN		= 0,
			eDEBUG_TYPE_VRAM,				// VRAMファイルデバッグ
			eDEBUG_TYPE_DRAW,				// 描画デバッグ
			eDEBUG_TYPE_GRID,				// グリッドデバッグ
			eDEBUG_TYPE_EFFECT,

			ENUM_DEBUG_MODE_TYPE_MAX
		} ENUM_DEBUG_MODE_TYPE;

		// @enum	デバッグメニューリスト
		typedef enum
		{
			eDEBUG_PLAY_MENU_NONE	= -1,	// 選択処理をしていない
			eDEBUG_PLAY_MENU_MAIN	= 0,
			eDEBUG_PLAY_MENU_VRAM,
			eDEBUG_PLAY_MENU_DRAW,
			eDEBUG_PLAY_MENU_GRID,
			eDEBUG_PLAY_MENU_EFFECT,

			ENUM_DEBUG_PLAY_MENU_MAX
		} ENUM_DEBUG_PLAY_MENU;

		// @enum	デバッグログタイプ
		typedef enum
		{
			eDEBUG_LOG_COMMENT,			// コメント
			eDEBUG_LOG_ALERT,			// アラート
			eDEBUG_LOG_ERROR,			// エラーログ

			ENUM_DEBUG_LOG_TYPE_MAX
		} ENUM_DEBUG_LOG_TYPE;

		// @enum	デバッグ
		typedef enum
		{
			eDEBUG_FLAG_CLOSE,			// 
			eDEBUG_FLAG_AUTO,			// 
		} ENUM_DEBUG_FLAG;
	}
}


/* End dxLibDebugConfig.h */



