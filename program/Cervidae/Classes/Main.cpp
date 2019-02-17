
#include "Main.h"
#include "Common/CommonList.h"
#include "Common/CervidaeLib/CLDefine.h"
#include "Libs/DxLib/dxLibDefine.h"
#include "System/AppSystem.h"
#include "Libs/DxLib/Debug/dxLibDebug.h"

//=================================================================================//
//  Main.cpp
//  Created by kashima akihiro on 2018/10/15.
//=================================================================================//


// DX���C�u����
// int main( int argc, char *argv[] )�̓R���\�[���E�B���h�E�\��
int APIENTRY  WinMain(	HINSTANCE	hInstance,
						HINSTANCE	hPrevInstance,
						LPSTR		lpCmdLine,
						int			nCmdShow )
{
	UNUSED_VARIABLE( hInstance);
	UNUSED_VARIABLE( hPrevInstance);
	UNUSED_VARIABLE( lpCmdLine);

	AppSystem * pAppSystem = new AppSystem();
	if( pAppSystem != nullptr )
	{
		pAppSystem->appSystemMain();
	}

	// ���C���֐�����return����ƃv���O�������I������B0��Ԃ��Ɛ���I�������B1��Ԃ��ƈُ�I������(�G���[�͏o�Ȃ�)
	return 0;
}
















