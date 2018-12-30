
#include "DxLib.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../dxLibDefine.h"
#include "dxLibInit.h"


// DX���C�u����������������Ă��邩
bool		dxInit_IsDxLibInit()
{
	auto isInit = DxLib::DxLib_IsInit();
	if( isInit == FALSE ){
		ERROR_PRINT("");
		return false;	// ����������Ă��Ȃ�
	}
	return true;//	����������Ă���
}
// �E�C���h�E���[�h�ŋN�����邩
bool		dxInit_CheckWindowModePlay()
{
	// TODO:
	if ( MessageBox( NULL, "�E�C���h�E���[�h�ŋN�����܂����H", "��ʃ��[�h�m�F",  MB_YESNO ) == IDYES )
	{
		// �u�͂��v���I�����ꂽ�ꍇ�̓E�C���h�E���[�h�ŋN��
		DxLib::ChangeWindowMode( TRUE );
		return true;
	}
	ERROR_PRINT("");
	return false;
}
// �Ꮘ�����׃��[�h�ŋN�����邩
bool		dxInit_CheckLowSpecModePlay()
{
	// TODO:
	if ( MessageBox( NULL, "�Ꮘ�����׃��[�h�ŋN�����܂����H", "�������׃��[�h�m�F",  MB_YESNO ) == IDYES )
	{
		// �u�͂��v���I�����ꂽ�ꍇ�͒Ꮘ�����׃��[�h�t���O�𗧂Ă�
		dxInit_SpecModeSetEnableXAudioFlag( TRUE );
		return true;
	}
	ERROR_PRINT("");
	return false;
}
// �Ꮘ�����׃��[�h���ǂ�����XAudio���g�p���邩�ǂ����̐ݒ��ύX����
bool		dxInit_SpecModeSetEnableXAudioFlag( const int setFlag )
{
	// ( TRUE:�g�p����(�f�t�H���g)  FALSE:�g�p���Ȃ� )
	auto isSuccess = DxLib::SetEnableXAudioFlag( setFlag ? FALSE : TRUE );
	if( isSuccess == 0 ){
	}

	return true;
}
// ���C���E�C���h�E����A�N�e�B�u��Ԃł����������s���邩�ǂ���
int		dxInit_SetAlwaysActiveRunEnable( const int setFlag )
{
	return 0;
}
// �E�C���h�E���[�h�̎��ɃE�C���h�E�̃T�C�Y�����R�ɕύX�o����悤�ɂ��邩�ǂ�����ݒ肷��
//	@brief		���C���E�C���h�E�̒[��͂�ŃE�C���h�E�̃T�C�Y��ύX�ł���悤�ɂ��邩�ǂ����̐ݒ���s��
//	@param		�t���O���(�f�t�H���g��FALSE)
//				TRUE  : �ύX�o����悤�ɂ���
//				FALSE : �ύX�o���Ȃ��悤�ɂ���(�f�t�H���g)
//	@return     �Ȃ�
//	@attention  ���̊֐��̓E�C���h�E���[�h�Ń\�t�g�𓮂����Ă��鎞�� 
//				�E�C���h�E�̘g�����N���b�N�ŝS�܂�ŃE�C���h�E�̃T�C�Y�����R�� 
//				�ύX�ł���悤�ɂ��邩�ǂ�����ݒ肷��֐��ł��B
//				TRUE ��n���ƕύX�ł���悤�ɂȂ�AFALSE��n���ƕύX�o���Ȃ��悤�ɂȂ�܂��B(�N�����ɂ� FALSE �̏�ԂɂȂ��Ă��܂�)
//				
//			�s���Ӂt
//				���̊֐��� TRUE ��n���ăT�C�Y�����R�ɕύX�o����悤�ɂ������́A 
//				SetDrawScreen �֐��� DX_SCREEN_BACK ��n���āA��΂ɕ\��ʂɒ��ڕ`�悵�Ȃ��悤�ɂ��ĉ������B
//				(�\��ʂɒ��ڕ`�悷��Ɛ������`�挋�ʂ������܂���)
int     dxInit_WinSizeChangeSetEnable( const bool  bEnable )
{
	if( bEnable == FALSE )
	{
		DxLib::SetWindowSizeChangeEnableFlag( FALSE );	/* �E�C���h�E�T�C�Y�ύX�F�s�� */
	}else{
		DxLib::SetWindowSizeChangeEnableFlag( TRUE );	/* �E�C���h�E�T�C�Y�ύX�F���� */
	}
	
	return 0; // �ݒ萬��
}

// ���C���E�C���h�E����A�N�e�B�u��Ԏ��̏����̎��s�ݒ�
bool    dxInit_SetWindowAlwaysRunEnable( const int bEnable )
{
	auto isSuccess = DxLib::SetAlwaysRunFlag( bEnable );
	if( isSuccess == -1 ){
		return false; // �G���[
	}
	return true; // �ݒ萬��
}

// DX���C�u�������g�p�����\�t�g�̓�d�N�����\�ɂ��邩�ǂ����̐ݒ���s��( TRUE:�\�ɂ��� FALSE:�s�\�ɂ���( �f�t�H���g ) )
bool	dxInit_SetDoubleStartValidEnable( const int bEnable )
{
	auto isSuccess = DxLib::SetDoubleStartValidFlag( bEnable );
	if( isSuccess == 0 ){
	}

	return true; // �ݒ萬��
}

