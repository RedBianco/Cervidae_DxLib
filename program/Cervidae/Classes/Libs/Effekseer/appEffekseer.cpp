
#include "DxLib.h"
#include "../../Common/CommonList.h"
#include "../../Common/CervidaeLib/CLDefine.h"
#include "../DxLib/dxLibDefine.h"
#include "appEffekseer.h"
#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))
#include <EffekseerForDXLib.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////////
/*
    @Effekseer 2D�G�t�F�N�g���C�u����
    2018.12.27

    ��Windows8 �̊���Effekseer�N���ɂ�DirectX��EndUserRuntime���K�v
	��DX���C�u�����̎d�l�ŃG�t�F�N�g�Đ��O�ɉ�������̕`�揈�����s��Ȃ���DX���C�u�������̕`�悪�s���Ȃ�
	
	��SAMPLE��
	�� Effkseer_Init�O�ɂ�鎖

		//	DirectXEx9���g�p���Ȃ��悤�ɂ���B
		//	Effekseer���g�p����ɂ͕K���ݒ肷��B
		SetUseDirect3D9Ex( FALSE );

	�� Effkseer_Init��ɂ�鎖

		//	Z�o�b�t�@��L���ɂ���B
		//	Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
		SetUseZBuffer3D( TRUE );

		//	Z�o�b�t�@�ւ̏������݂�L���ɂ���B
		//	Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
		SetWriteZBuffer3D( TRUE );

	�� ���t���[��

		//	Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
		UpdateEffekseer2D();

		//	Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
		DrawEffekseer2D();

	���v���p�e�B�̐ݒ聄
	��32bit�̂ݑΉ��Ȃ̂Ŏ�����ƈꎞ���~
	

*/


#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))

int		AppLib::Effekseer::libSystemInit()
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

	ERROR_PRINT("[LIB] Effekseer : Effekseer::systemInitialize() CLEAR\n");

    return 0;
}
void	AppLib::Effekseer::libSetZBuffer()
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


AppEffekseerController::AppEffekseerController()
{
}
AppEffekseerController::~AppEffekseerController()
{
}

void	AppEffekseerController::libSetPlayZBuffer()
{

}

void    AppEffekseerController::libSetup()
{

}

void	AppEffekseerController::libEnd()
{
	// Effekseer���I������
	Effkseer_End();
}

int		AppEffekseerController::libFileLoad( char * szFile, int * nLoadHandle )
{
	return 0;
}

int		AppEffekseerController::libFileLoad( char * szFile )
{
	return 0;
}

int		AppEffekseerController::libEffect2DPlay( const int fileHandle )
{
	return 0;
}
int		AppEffekseerController::libEffect2DPlay( const int fileHandle, float fSetScale )
{
	return 0;
}

int		AppEffekseerController::libEffectSetPos2DPlay( const int fileHandle, float fSetX, float fSetY, float fSetScale )
{
	return 0;
}

int		AppEffekseerController::libSet2DPlayScale( const int fileHandle, float fSetScale )
{
	return 0;
}

int		AppEffekseerController::libSet2DPlayPos( const int fileHandle, float fSetX, float fSetY )
{
	return 0;
}
int		AppEffekseerController::libSet2DPlayRot( const int fileHandle, float fRotX, float fRotY, float fRotZ )
{
	return 0;
}
int		AppEffekseerController::libSet2DPlayRot( const int fileHandle, float fRotZ )
{
	return 0;
}

int		AppEffekseerController::libIsPlay2D( const int fileHandle )
{
	return 0;
}

unsigned int	AppEffekseerController::libIsEfkFileExist( char * szPlayFile )
{
	return 0;
}

int		AppEffekseerController::libPlayUpdate()
{
	return 0;
}



#endif// ( MIDDLEWARE_EFFEKSEER_USE_ENABLE )




















