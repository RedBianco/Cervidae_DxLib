#pragma once

#include <string>

//=================================================================================//
//  appEffekseerLib.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/11.
//=================================================================================//

#define	EFFEKSEER_DXLIB_VERSION

// 画面に表示する最大パーティクル数を設定
// ※出し過ぎると処理負荷も増える
#define	EFFEKSEER_PARTICLE_DRAW_MAX		( 1500 )

#define	EFFEKSEER_PLAY_RUN				(  0)		//	再生中
#define	EFFEKSEER_PLAY_END				( -1)		//	再生されていない、もしくは再生終了
#define	EFFEKSEER_PLAY_ERROR			( -1)		//	再生されていない、もしくは再生終了

#define	EFFEKSEER_NONHANDLE				(0xffffffff)	/*	無効なハンドル	*/



class EffekseerContainer
{
public:
	
	EffekseerContainer();
	 ~EffekseerContainer(){}
	
public:
	int		m_FileHandle_;
	std::string		m_PlayFile;
	
};















/* End appEffekseerLib.h */

