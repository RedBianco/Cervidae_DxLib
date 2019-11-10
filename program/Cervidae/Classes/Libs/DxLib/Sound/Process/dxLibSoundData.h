#pragma once


//===================================================================//
//	dxLibSoundData
//
//  Created by kashima akihiro on 2019.08.03
//===================================================================//

/**
 *	サウンド再生管理用データ
 */
namespace App
{
	class SoundDataContainer
	{
	public:
		SoundDataContainer() {};
		~SoundDataContainer() {};

	public:

		std::string		dxSoundName;	// ファイルネーム
		int				dxSoundHandle;	// ファイルロードハンドル
		int				dxSoundExist;	// サウンドファイル存在チェック( -1:未登録, 0:登録済み )

	public:

		int		getPlayHandle() { return dxSoundHandle; }
		int		isSoundFile( char * fileName );
	};
}







/* End dxLibSoundData.h */


