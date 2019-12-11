#pragma once

#include "appEffekseerLib.h"
#include "appEffekseerData.h"

//=================================================================================//
//  appEffekseer.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/29.
//=================================================================================//

#if 0
// 警告除去
// ※DXライブラリ用Effekseerの仕様なので必ず出る
// ※Effekseerのlibファイル関連のWarning
// warning LNK4099
#pragma warning( disable:4099)
#endif

/*
	Effekseer描画コントローラークラス
*/
namespace Lib
{
	class EffekseerController
	{
	public:
		EffekseerController();
		virtual	~EffekseerController();
	
	public:
		std::vector< Lib::EffekseerFileData> m_effectData;

		bool	m_3DPlayEnable;

	public:
	
		void	libSetPlayZBuffer(void);
		void	libSetup(void);
		void	libEnd(void);
		void	libDataClear(void);
		int		libFileLoad( const char * szLoadFile, int * nLoadHandle );
		int		libFileLoad( const char * szLoadFile );
		int		libFileRelease( const int fileHandle );
		int		libEffect2DPlay( const int fileHandle );
		int		libEffect2DPlay( const int fileHandle, float fSetScale = 25.0f );
		int		libEffectSetPos2DPlay( const int fileHandle, float fSetX = 1.0f, float fSetY = 1.0f, float fSetScale = 25.0f );
		int		libSet2DPlayScale( const int fileHandle, float fSetScale = 1.f );
		int		libSet2DPlayPos( const int fileHandle, float fSetX = 1.0f, float fSetY = 1.0f );
		int		libSet2DPlayRot( const int fileHandle, float fRotX = 1.0f, float fRotY = 1.0f, float fRotZ = 1.0f );
		int		libSet2DPlayRot( const int fileHandle, float fRotZ = 1.0f );
		int		libIsPlay2D( const int fileHandle );
		unsigned int	libEffectFileExist( char * szPlayFile );

		// 毎フレーム処理
		int		libPlayUpdate(void);


	};
}





   





/* End appEffekseer.h */

