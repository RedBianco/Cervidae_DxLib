#pragma once

#include <string>

//=================================================================================//
//  appEffekseerData.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/11.
//=================================================================================//

/*
	.efkファイルデータ管理用クラス
	ファイル１つの管理データ
*/
class EffekseerFileData
{
public:
	
	EffekseerFileData();
	 ~EffekseerFileData(){}
	
public:
	// ファイルハンドル
	int				m_FileHandle_;
	// 再生ファイル名
	std::string		m_PlayFile;
	
};




/* End appEffekseerData.h */

