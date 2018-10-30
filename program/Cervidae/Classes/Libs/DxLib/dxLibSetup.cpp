

#include "DxLib.h"
#include "dxLibSetup.h"



// DXライブラリの基本開始設定処理 ※全て DxLib_Init の前に呼ぶ必要の処理群
bool	dxLib_InitBeforeSetup( void)
{
	return( true );
}

// DXライブラリの基本開始設定処理(※全て DxLib_Init が呼ばれた後に呼ぶ必要のある１回限定処理群)
bool	dxLib_InitAfterSetup( void)
{
	return( true );
}

// DXライブラリ関係の毎フレーム処理
void	dxLib_SystemUpdate( void)
{

}