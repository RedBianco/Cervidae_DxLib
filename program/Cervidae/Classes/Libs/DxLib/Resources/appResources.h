#pragma once

/**
 *  �y�ǂݍ��݃N���X�}�z 
 *  ���t�@�C���̓o�^�\�ő吔�Ɠǂݍ��݉\�ő吔�𕪂��Ă���݌v�Ȃ̂ŃN���X���o�^�Ǘ��p�A�ǂݍ��݊Ǘ��p�ŕ�����Ă���
 * 
 *	���匳�t�@�C���Ǘ�
 *	class AppFileGraphicManager
 * 
 *  ��
 * 
 */

///////////////////////////////////////////////////////////////////////////
//  VRAM�t�@�C���Ǘ��V�X�e�����p���@
//  [�摜�o�^]
//  _graphicVramTextureEntry(	Resources::FileProcess::eFILE_GRAPHIC_SYSTEM,
//			       				"�摜�t�@�C����.png", 
//								enum ENUM_RESFILE_FILE_ENTRY_INDEX_LIST,
//								enum ENUM_GRAPHIC_FILE_ENTRY_TYPE );
//  [�摜VRAM�A�b�v]
//  _graphicVramTexAttrUp(	Resources::FileProcess::eFILE_GRAPHIC_SYSTEM,
//							enum ENUM_VRAM_UPPROC,
//							enum ENUM_GRAPHIC_FILE_ENTRY_TYPE );
//  [�A�b�v�摜�폜]
//  _graphicVramTexAttrDelete(	Resources::FileProcess::eFILE_GRAPHIC_SYSTEM, 
//								"�摜�t�@�C����.png", 
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


