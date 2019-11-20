
#include "Main.h"
#include "Common/appCommonParam.h"
#include "System/AppSystem.h"

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

	/**
	 *	���C���t���[
	 */
	{
		AppSystem * pAppSystem = new AppSystem();
		if ( pAppSystem != nullptr )
		{
			pAppSystem->appSystemMain();
		}
	}

	// ���C���֐�����return����ƃv���O�������I������B0��Ԃ��Ɛ���I�������B1��Ԃ��ƈُ�I������(�G���[�͏o�Ȃ�)
	return 0;
}


