
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../dxLibDefine.h"
#include "dxLibInit.h"


// DX���C�u����������������Ă��邩
bool		dxInit_IsDxLibInit()
{
	auto isInit = DxLib::DxLib_IsInit();
	if( isInit == FALSE ){
		DEBUG_PRINT("");
		return false;	// ����������Ă��Ȃ�
	}
	return true;//	����������Ă���
}
// �E�C���h�E���[�h�ŋN�����邩
bool		dxInit_CheckWindowModePlay()
{
	if ( MessageBox( NULL, "�E�C���h�E���[�h�ŋN�����܂����H", "��ʃ��[�h�m�F",  MB_YESNO ) == IDYES )
	{
		// �u�͂��v���I�����ꂽ�ꍇ�̓E�C���h�E���[�h�ŋN��
		DxLib::ChangeWindowMode( TRUE );
		return true;
	}
	DEBUG_PRINT("");
	return false;
}
// �Ꮘ�����׃��[�h�ŋN�����邩
bool		dxInit_CheckLowSpecModePlay()
{
	// �Ꮘ�����׃��[�h�ŋN�����邩�m�F����
	if ( MessageBox( NULL, "�Ꮘ�����׃��[�h�ŋN�����܂����H", "�������׃��[�h�m�F",  MB_YESNO ) == IDYES )
	{
		// �u�͂��v���I�����ꂽ�ꍇ�͒Ꮘ�����׃��[�h�t���O�𗧂Ă�
		dxInit_SpecModeSetEnableXAudioFlag( TRUE );
		return true;
	}
	DEBUG_PRINT("");
	return false;
}
// �Ꮘ�����׃��[�h���ǂ�����XAudio���g�p���邩�ǂ����̐ݒ��ύX����
bool		dxInit_SpecModeSetEnableXAudioFlag( const int setFlag )
{
	// ( TRUE:�g�p����(�f�t�H���g)  FALSE:�g�p���Ȃ� )
	auto isSuccess = DxLib::SetEnableXAudioFlag( setFlag ? FALSE : TRUE );

	return true;
}
// ���C���E�C���h�E����A�N�e�B�u��Ԃł����������s���邩�ǂ���
int		dxInit_SetAlwaysActiveRunEnable( const int setFlag )
{
	return 0;
}






