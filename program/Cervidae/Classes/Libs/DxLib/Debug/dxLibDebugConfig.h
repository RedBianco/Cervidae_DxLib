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
		// @enum	�f�o�b�O���[�h�o�^�^�C�v
		typedef enum
		{
			eDEBUG_TYPE_NONE		= -1,
			eDEBUG_TYPE_MAIN		= 0,
			eDEBUG_TYPE_VRAM,				// VRAM�t�@�C���f�o�b�O
			eDEBUG_TYPE_DRAW,				// �`��f�o�b�O
			eDEBUG_TYPE_GRID,				// �O���b�h�f�o�b�O
			eDEBUG_TYPE_EFFECT,

			ENUM_DEBUG_MODE_TYPE_MAX
		} ENUM_DEBUG_MODE_TYPE;

		// @enum	�f�o�b�O���j���[���X�g
		typedef enum
		{
			eDEBUG_PLAY_MENU_NONE	= -1,	// �I�����������Ă��Ȃ�
			eDEBUG_PLAY_MENU_MAIN	= 0,
			eDEBUG_PLAY_MENU_VRAM,
			eDEBUG_PLAY_MENU_DRAW,
			eDEBUG_PLAY_MENU_GRID,
			eDEBUG_PLAY_MENU_EFFECT,

			ENUM_DEBUG_PLAY_MENU_MAX
		} ENUM_DEBUG_PLAY_MENU;

		// @enum	�f�o�b�O���O�^�C�v
		typedef enum
		{
			eDEBUG_LOG_COMMENT,			// �R�����g
			eDEBUG_LOG_ALERT,			// �A���[�g
			eDEBUG_LOG_ERROR,			// �G���[���O

			ENUM_DEBUG_LOG_TYPE_MAX
		} ENUM_DEBUG_LOG_TYPE;

		// @enum	�f�o�b�O
		typedef enum
		{
			eDEBUG_FLAG_CLOSE,			// 
			eDEBUG_FLAG_AUTO,			// 
		} ENUM_DEBUG_FLAG;
	}
}


/* End dxLibDebugConfig.h */



