
#include "DxLib.h"
#include "../../Common/appCommonParam.h"
#include "../../Common/CervidaeLib/CLDefine.h"
#include "../DxLib/dxLibDefine.h"
#include "appEffekseer.h"
#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
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

#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )


Lib::EffekseerController::EffekseerController()
{
}
Lib::EffekseerController::~EffekseerController()
{
}
void	Lib::EffekseerController::libSetPlayZBuffer()
{
}
void    Lib::EffekseerController::libSetup()
{
}
void	Lib::EffekseerController::libEnd()
{
	// Effekseer���I������
	Effkseer_End();
}
void	Lib::EffekseerController::libDataClear()
{
}
int		Lib::EffekseerController::libFileLoad( char * szFile, int * nLoadHandle )
{
	return 0;
}
int		Lib::EffekseerController::libFileLoad( char * szFile )
{
	return 0;
}
int		Lib::EffekseerController::libEffect2DPlay( const int fileHandle )
{
	return 0;
}
int		Lib::EffekseerController::libEffect2DPlay( const int fileHandle, float fSetScale )
{
	return 0;
}
int		Lib::EffekseerController::libEffectSetPos2DPlay( const int fileHandle, float fSetX, float fSetY, float fSetScale )
{
	return 0;
}
int		Lib::EffekseerController::libSet2DPlayScale( const int fileHandle, float fSetScale )
{
	return 0;
}
int		Lib::EffekseerController::libSet2DPlayPos( const int fileHandle, float fSetX, float fSetY )
{
	return 0;
}
int		Lib::EffekseerController::libSet2DPlayRot( const int fileHandle, float fRotX, float fRotY, float fRotZ )
{
	return 0;
}
int		Lib::EffekseerController::libSet2DPlayRot( const int fileHandle, float fRotZ )
{
	return 0;
}
int		Lib::EffekseerController::libIsPlay2D( const int fileHandle )
{
	return 0;
}
unsigned int	Lib::EffekseerController::libIsEfkFileExist( char * szPlayFile )
{
	return 0;
}
int		Lib::EffekseerController::libPlayUpdate()
{
	return 0;
}



#endif// ( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )




















