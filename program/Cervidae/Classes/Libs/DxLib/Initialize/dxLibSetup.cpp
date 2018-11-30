

#include "../dxLibDefine.h"
#include "dxLibSetup.h"
#include "dxLibInit.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../../../Common/CommonList.h"

// DX���C�u�����̊�{�J�n�ݒ菈��
// ���S�� DxLib_Init �̑O�ɌĂԕK�v�̏����Q
bool		dxLib_InitBeforeSetup( void )
{
	DxLib::SetGraphMode(	DxLibCommon::Disp::DISPLAY_RESOLUTION_WIDTH,
										DxLibCommon::Disp::DISPLAY_RESOLUTION_HEIGHT,
										DxLibCommon::Disp::DISPLAY_PLAY_COLORBIT );

	DxLib::SetMainWindowText( CervidaeLibDefine::nAPP_EXE_NAME );

	DxLib::ChangeWindowMode( DxLibCommon::DEFAULT_SCREEN_MODE );

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

		return true;
	}
	return false;
}

// DX���C�u�����֌W�̖��t���[������
void		dxLib_SystemUpdate( void )
{

}






