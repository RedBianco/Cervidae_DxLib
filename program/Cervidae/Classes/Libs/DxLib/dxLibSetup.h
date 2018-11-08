#pragma once


//=================================================================================//
//  dxLibSetup.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/28.
//=================================================================================//


// DXライブラリの基本開始設定処理 ※全て DxLib_Init の前に呼ぶ必要の処理群
bool		dxLib_InitBeforeSetup( void);

// DXライブラリの基本開始設定処理(※全て DxLib_Init が呼ばれた後に呼ぶ必要のある１回限定処理群)
bool		dxLib_InitAfterSetup( void);

// DXライブラリ関係の毎フレーム処理
void		dxLib_SystemUpdate( void);


void		dxLib_StartSetup( void);

