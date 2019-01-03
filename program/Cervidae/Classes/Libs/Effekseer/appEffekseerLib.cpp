
#include "DxLib.h"
#include "../../Common/CommonList.h"
#include "../../Common/CervidaeLib/CLDefine.h"
#include "../DxLib/dxLibDefine.h"
#include "appEffekseerLib.h"
#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))
#include <EffekseerForDXLib.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////////
/*
    Effekseer���C�u����
    2019/01/11.
*/


#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))

int		App::EffekseerLib::libSystemInit()
{
	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	// ���������ꍇ��0�A���s�����ꍇ��-1��Ԃ�
	if( Effkseer_Init( EFFEKSEER_PARTICLE_DRAW_MAX ) == -1 )
	{
		//	�G���[
		ERROR_PRINT("__ERROR__ : Effekseer_LibInit() - SetUpFailed\n" );
		return -1;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	// ��ʃ��[�h�ύX��( �ƃE�C���h�E���[�h�ύX�� )�ɃO���t�B�b�N�X�V�X�e���̐ݒ��O���t�B�b�N�n���h����
	// ���Z�b�g���邩�ǂ�����ݒ肷��( TRUE:���Z�b�g����( �f�t�H���g )  FALSE:���Z�b�g���Ȃ� )
	DxLib::SetChangeScreenModeGraphicsSystemResetFlag( FALSE );

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseer��2D�`��̐ݒ������(�X�N���[���T�C�Y�ݒ�)
	Effekseer_Set2DSetting( DxLibCommon::Disp::DISPLAY_RESOLUTION_WIDTH,
							DxLibCommon::Disp::DISPLAY_RESOLUTION_HEIGHT );

	DEBUG_PRINT("[LIB] Effekseer : Effekseer::systemInitialize() CLEAR\n");

    return 0;
}
void	App::EffekseerLib::libSetZBuffer()
{
	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	// ( �R�c�`��݂̂ɉe�� )( TRUE:�y�o�b�t�@���g�p����  FALSE:�y�o�b�t�@���g�p���Ȃ�( �f�t�H���g ) )
	SetUseZBuffer3D( TRUE );

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	// ( �R�c�`��݂̂ɉe�� )( TRUE:�������݂��s��  FALSE:�������݂��s��Ȃ�( �f�t�H���g ) )
	SetWriteZBuffer3D( TRUE );
}


#endif// defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE )


























