
#include "DxLib.h"
#include "dxLibCommon.h"
#include "dxLibDefine.h"
#include "../../Common/CommonList.h"

//==========================================================//
//
//
//==========================================================//


void		dxCommon_FramerateDisp( const int renderRate )
{
	DxLib::SetDrawBlendMode( DX_BLENDMODE_ALPHA, 255 );

	DxLib::DrawFormatString(	DxLibCommon::Disp::DISPLAY_FLAMERATE_POS_X,
								DxLibCommon::Disp::DISPLAY_FLAMERATE_POS_Y,
								GetColor( 255, 255, 255 ), "FPS : %d", renderRate );
}



