#pragma once


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
namespace Lib
{
	struct EffekseerFileData
	{
		// ファイルハンドル
		int				m_FileHandle;
		// 再生ファイル名
		std::string		m_FileName;
		// 座標情報
		// スケール情報
	};
}



/* End appEffekseerData.h */

