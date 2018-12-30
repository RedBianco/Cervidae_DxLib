
#include "DxLib.h"
#include "../dxLibDefine.h"
#include "dxLibSetup.h"
#include "dxLibInit.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../../../Common/CommonList.h"

// DX���C�u�����̊�{�J�n�ݒ菈��
// ���S�� DxLib_Init �̑O�ɌĂԕK�v�̏����Q
bool		dxLib_InitBeforeSetup( void )
{
	DxLib::SetGraphMode( DxLibCommon::Disp::DISPLAY_RESOLUTION_WIDTH,
						 DxLibCommon::Disp::DISPLAY_RESOLUTION_HEIGHT,
						 DxLibCommon::Disp::DISPLAY_PLAY_COLORBIT );

	DxLib::SetMainWindowText( CervidaeLibDefine::nAPP_EXE_NAME );

	DxLib::ChangeWindowMode( DxLibCommon::DEFAULT_SCREEN_MODE );

#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))
	// DirectXEx9���g�p���Ȃ��悤�ɂ���B
	// ��DxLib_Init �̑O�ɌĂԕK�v������
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	DxLib::SetUseDirect3D9Ex( FALSE );
#endif

	return true;
}

// DX���C�u�����̊�{�J�n�ݒ菈��
// ���S�� DxLib_Init ���Ă΂ꂽ��ɌĂԕK�v�̂���P����菈���Q
bool		dxLib_InitAfterSetup( void )
{
	if( dxInit_IsDxLibInit() )
	{
		//------------------------------------------------------------------
		//	��ʃ��[�h�ύX��( �ƃE�C���h�E���[�h�ύX�� )�ɃO���t�B�b�N�X�V�X�e���̐ݒ��
		//	�O���t�B�b�N�n���h�������Z�b�g���邩�ǂ�����ݒ肷��( TRUE:���Z�b�g����( �f�t�H���g )  FALSE:���Z�b�g���Ȃ� )
		//	���f�t�H���g�ł� TRUE �̏�ԂɂȂ��Ă���̂ŁA
		//	DxLib_Init �̌�ɂł���񂾂�
		//	�hSetChangeScreenModeGraphicsSystemResetFlag( FALSE );�h
		//	�Ǝ��s���Ă��������A�ȍ~ ChangeWindowMode �� SetGraphMode ���Ă΂�Ă�
		//	�O���t�B�b�N�n���h���͍폜���ꂸ�ASetDrawArea �� SetDrawBlendMode �Ȃǂ�
		//	��ʐݒ�����Z�b�g����Ȃ��Ȃ�܂�
		//------------------------------------------------------------------
		DxLib::SetChangeScreenModeGraphicsSystemResetFlag( FALSE );

		//-----------------------------------------------------------------------
		//	printfDx �̌��ʂ���ʂɏo�͂���ۂɎg�p����t�H���g�̃T�C�Y��ݒ�
		//------------------------------------------------------------------
		

		//-----------------------------------------------------------------------
		//	���C���E�C���h�E����A�N�e�B�u��Ԃł����������s���邩�ǂ�����ݒ肷��
		//	( TRUE:���s����  FALSE:��~����( �f�t�H���g ) )
		//	���Q�[���E�B���h�E���t�H�[�J�X����Ė������̃^�u��E�B���h�E�𑀍삵�Ă��鎞�ɃQ�[����ʂ��~�߂邩�~�߂Ȃ���
		//	���f�t�H���g��FALSE�Ńt�H�[�J�X����Ė����Ȃ珈�����~�߂�
		//-----------------------------------------------------------------------
		dxInit_SetWindowAlwaysRunEnable( TRUE );

		//-----------------------------------------------------------------------
		//	�E�C���h�E���[�h�ϒ�������ݒ�(�t���O���(�f�t�H���g��FALSE))
		//	�E�C���h�E���[�h�̎��ɃE�C���h�E�̃T�C�Y�����R�ɕύX�o����悤�ɂ��邩�ǂ�����ݒ�
		//-----------------------------------------------------------------------
		dxInit_WinSizeChangeSetEnable( FALSE );





		return true;
	}
	return false;
}

// DX���C�u�����֌W�̖��t���[������
void		dxLib_SystemUpdate( void )
{

}






