

#include "../../../Common/appCommonParam.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../dxLibDefine.h"
#include "dxLibKeyPadUtility.h"
#include "dxLibInputConfig.h"

//////////////////////////////////////////////////////////////////////////
/*
	DX���C�u����	�L�[�E�p�b�h���͊Ǘ��V�X�e��
	���e�V�[���N���X�Ɍp�������Ďg�p����z��
*/
//////////////////////////////////////////////////////////////////////////

// 
bool	Lib::AppKeyPadController::inputParamInit()
{
	dxKeyInput.m_KeyStatus_ = 0;
	dxKeyInput.m_KeyInputMode_ = DxInput::Command::INPUT_MODE_GAME;

	for( int i = 0; i < DxInput::Info::INPUT_WORKBUFFER; i ++ )
	{
		dxKeyInput.m_KeyBuff_[ i ] = 0;
		dxKeyInput.m_KeyFlag_[ i ] = 0;
#if PROJECT_DEBUG
		dxKeyInput.debKeyBuff_[ i ] = 0;
		dxKeyInput.debKeyFlag_[ i ] = 0;
#endif
	}

	// �e���̓^�C�v���b�N�ݒ�
	inputSystemApply( DxInput::Command::INPUT_TYPE_KEYPAD, FALSE );

	DEBUG_PRINT("[AppLib] AppKeyPadController::inputParamInit() CLEAR\n");

	return true;
}
void	Lib::AppKeyPadController::inputStatusClear( void )
{
}
// �L�[�E�p�b�h���̓V�X�e�������^�C��
void	Lib::AppKeyPadController::updateInputControl( void )
{
	/*
	 * ���t���[���L�[���͐���
	 */
	updateKeyInput();
	/*
	 * ���t���[���W���C�p�b�h���͐���
	 */
	updateJoypadInput();
}
// �L�[�E�p�b�h���̓��b�N�ݒ�( 0:�L�[���̓V�X�e��, 1:�p�b�h���̓V�X�e�� )
void	Lib::AppKeyPadController::inputSystemApply( const bool  bInputApply, const bool  bApplyFlag )
{
	if( bInputApply == DxInput::Command::INPUT_TYPE_KEYPAD )
	{
		keyInputLockEnable( bApplyFlag ); // �L�[���̓V�X�e��
	}else{
		keyInputLockEnable( bApplyFlag ); // �p�b�h���̓V�X�e��
	}
}
// �L�[�E�p�b�h���̓��[�h�Z�b�g
void	Lib::AppKeyPadController::inputKeyModeSet( const int  setMode )
{
	dxKeyInput.m_KeyInputMode_ = setMode;
}
bool	Lib::AppKeyPadController::inputModeDebug( void )
{
	return (dxKeyInput.m_KeyInputMode_ == DxInput::Command::INPUT_MODE_DEBUG ) ? true : false;
}
//=========================================================================//
//
//=========================================================================//
int		Lib::AppKeyPadController::updateKeyInput( const int  iKeyList )
{
	if( inputKeyModeGet() == DxInput::Command::INPUT_MODE_GAME ){
		return -1;
	}
	// �S�ẴL�[���͏�Ԃ��擾(�O�F����, �|�P�F�G���[����)
	GetHitKeyStateAll( dxKeyInput.m_KeyBuff_ );
	int  i = 0;
	for( i = 0; i < DxInput::Info::INPUT_WORKBUFFER; i ++ )
	{
		// ���͏�Ԃ��擾����Ă����
		if( dxKeyInput.m_KeyBuff_[i] )
		{
			if( dxKeyInput.m_KeyFlag_[i] == 0 )
			{
				dxKeyInput.m_KeyFlag_[i] = DxInput::Command::lDxKey::KEYINPUT_SINGLE;	// �P�񉟂���
			}
			else if( dxKeyInput.m_KeyFlag_[i] == 1 ) // ���Ɉ�񉟂���Ă����Ԃł�����񉟂�(�܂艟�����ςȂ��Ȃ�)
			{
				dxKeyInput.m_KeyFlag_[i] = DxInput::Command::lDxKey::KEYINPUT_DIRECT;	// �������ςȂ�����
			}
		}else {
			dxKeyInput.m_KeyFlag_[i] = 0; // ���͂���Ă��Ȃ�
		}
	}
	return ( 0 );
}
// �L�[��"�P��"���������𔻒肷��
int		Lib::AppKeyPadController::keyInputOneCheck( const int  iKeyList, int iKeyFrame, int * pKeyOutFlag )
{
	const int i = iKeyList;

	// ���b�N�����`�F�b�N
	if( isKeyInputLockEnable() ){ return -1; };

	if( dxKeyInput.m_KeyBuff_[ i ] )
	{
		// �L�[���P�񉟂����u�Ԕ���
		if( dxKeyInput.m_KeyFlag_[ i ] == DxInput::Command::lDxKey::KEYINPUT_SINGLE )
		{
//			if( *pKeyOutFlag != nullptr ){ *pKeyOutFlag = DxInput::Command::lDxKey::KEYINPUT_SINGLE; }
			return ( 1 ); // ����N���A
		}
	}
	return ( 0 );
}
// �L�[�����������Ă��邩���肷��
int		Lib::AppKeyPadController::keyInputDirectCheck( const int  iKeyList, int iKeyFrame, int * pKeyOutFlag )
{
	const int	i = iKeyList;

	// ���b�N�����`�F�b�N
	if( isKeyInputLockEnable() ){ return -1; };

	if( dxKeyInput.m_KeyBuff_[ i ] )
	{
		// �L�[�������ςȂ�����
		if( dxKeyInput.m_KeyFlag_[ i ] == DxInput::Command::lDxKey::KEYINPUT_DIRECT )
		{
//			if( *pKeyOutFlag != nullptr ){ *pKeyOutFlag = DxInput::Command::lDxKey::KEYINPUT_DIRECT; }
			return ( 1 ); // ����N���A
		}
	}
	return ( 0 );
}
// �L�[���b�N�ݒ�( TRUE:���b�N����, FALSE:���b�N���� )
void	Lib::AppKeyPadController::keyInputLockEnable( const bool  bLockFlag )
{
	// �f�o�b�O���[�h�����K�p�����
	if( bLockFlag )
	{
		// ���b�N����
		uiInputLockBit_ |= DxInput::Command::lDxKey::KEYINPUT_LOCK;
	}else{
		// ���b�N����
		uiInputLockBit_ &= ~DxInput::Command::lDxKey::KEYINPUT_LOCK;
	}
}
// �L�[���b�N�ݒ���擾
bool	Lib::AppKeyPadController::isKeyInputLockEnable( void )
{
	return ( ( uiInputLockBit_ & DxInput::Command::lDxKey::KEYINPUT_LOCK ) != 0 );
}

// �p�b�h�V�X�e����{������
bool	Lib::AppKeyPadController::padParamInit( void )
{
	// �W���C�p�b�h�ڑ������擾
	dxJoypadInput.m_ConnectNum_ = DxLib::GetJoypadNum();
	dxJoypadInput.m_PadEnable_ = false;
	dxJoypadInput.m_InputFlag_ = 0;

	// �p�b�h�U�����
	dxJoypadInput.m_VibFlag_ = DxInput::Command::lDxPad::PADINPUT_VIBRATFLAG;
	dxJoypadInput.m_VibPower_ = DxInput::Command::lDxPad::PADINPUT_VIBDEFPOWER;
	dxJoypadInput.m_VibTime_ = DxInput::Command::lDxPad::PADINPUT_VIBTIME;

#if PROJECT_DEBUG
	dxJoypadInput.debPadInput_ = 0;
	dxJoypadInput.debInstInfo_[64] = {};
	dxJoypadInput.debDeviceInfo_[64] = {};
#endif

	// �e���̓^�C�v���b�N�ݒ�
	inputSystemApply( DxInput::Command::INPUT_TYPE_JOYPAD, TRUE );

	// �W���C�p�b�h�̐U���@�\���g�p���邩�ǂ�����ݒ�(���f�t�H���g�͎g�p���Ȃ�,�g�p����ꍇ�͎蓮����)
	DxLib::SetUseJoypadVibrationFlag( static_cast<int>( DxInput::Command::lDxPad::PADINPUT_VIBRATFLAG ) );

	DEBUG_PRINT("[AppLib] AppKeyPadController::padParamInitialize() CLEAR\n");

	return true;
}
// �p�b�h���̓V�X�e�����t���[������
void	Lib::AppKeyPadController::updateJoypadInput( void )
{
	if( isPadInputLockEnable() ){
		return;	// ���b�N���|�����Ă���Ȃ甲����
	}

	int nJoyPadLinkNum_ = DxLib::GetJoypadNum();	// �W���C�p�b�h���ڑ�����Ă��鐔���擾����
	if( nJoyPadLinkNum_ != dxJoypadInput.m_ConnectNum_ )
	{
		dxJoypadInput.m_ConnectNum_ = nJoyPadLinkNum_;	// ���t���[�����ăp�b�h�ڑ������ς���Ă���΍X�V����
	}
//	if( nJoyPadLinkNum_ <= 0 )
//	{
//		dxJoypadInput.m_PadEnable_ = false;
//	}
}

// �W���C�p�b�h�̐ڑ������擾����
int		Lib::AppKeyPadController::getPadInputConnectNum( void )
{
	return dxJoypadInput.m_ConnectNum_;
}
// �W���C�p�b�h���b�N�ݒ�( TRUE:���b�N����, FALSE:���b�N���� )
void	Lib::AppKeyPadController::padInputLockEnable( const bool  bLockFlag )
{
	if( bLockFlag )
	{
		uiInputLockBit_ |= DxInput::Command::lDxPad::PADINPUT_LOCK;
	}else{
		uiInputLockBit_ &= ~DxInput::Command::lDxPad::PADINPUT_LOCK;
	}
}
// �W���C�p�b�h���b�N�ݒ���擾
bool	Lib::AppKeyPadController::isPadInputLockEnable( void )
{
	return ((uiInputLockBit_ & DxInput::Command::lDxPad::PADINPUT_LOCK) != 0);
}
//=========================================================================//
// �W���C�p�b�h�U���J�n����
//	InputType	:	�U�����J�n����p�b�h�̎��ʎq
//					DX_INPUT_PAD1		:	�p�b�h�P
//					DX_INPUT_PAD2		:	�p�b�h�Q
//					DX_INPUT_PAD3		:	�p�b�h�R
//					DX_INPUT_PAD4		:	�p�b�h�S
//		Power	:	�U���̋���(0�`1000)
//		 Time	:	�U�������鎞��(�~���b�P��)
//			-1 �� StopJoypadVibration ���Ă΂��܂ŐU����������
//	�߂�l	  �O : ����
//			�|�P : �G���[����
//	�y��z�p�b�h�P���ő�̐U���̋����łQ�b�ԐU�������܂��B
//	StartJoypadVibration( DX_INPUT_PAD1, 1000, 2000 ) ;
int		Lib::AppKeyPadController::padInputVibActionStart( const int vibInputType, int vibTime )
{
	if( vibTime < 0 ){
		vibTime = 1000;
	}

	// �U���J�n
	auto nvibRResult_ = DxLib::StartJoypadVibration( vibInputType, dxJoypadInput.m_VibPower_, vibTime );
	if( nvibRResult_ == -1 )
	{
		// �G���[
		return ( -1 );
	}
	// �U���̋���
	dxJoypadInput.m_VibPower_ = dxJoypadInput.m_VibPower_;
	// �U�������鎞��
	dxJoypadInput.m_VibTime_ = vibTime;

	return ( 0 );
}
// �W���C�p�b�h�U����~����
void	Lib::AppKeyPadController::padInputVibActionEnd( const int vibInputType )
{
	if( getPadInputVibActionTime() == -1 )
	{
		DxLib::StopJoypadVibration( vibInputType );
	}
}
// �W���C�p�b�h�U���p���[�l�ݒ�( 0 �` 1000 )
void	Lib::AppKeyPadController::setPadInputVibPower( int  setVibPower )
{
	if( setVibPower > DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX ){
		ERROR_PRINT("__ERROR__ : dxLib_SetPadInputVibPower VibPowerOver[%d]\n", DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX );
		setVibPower = DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX;
	}
	dxJoypadInput.m_VibPower_ = setVibPower;
}
// �W���C�p�b�h�U�����Ԏ擾(�~���b�P��)
int		Lib::AppKeyPadController::getPadInputVibActionTime( void )
{
	return ( dxJoypadInput.m_VibTime_ );
}
// �W���C�p�b�h�̐U���@�\���I����
void	Lib::AppKeyPadController::setPadVibActionOn( void )
{
	// �W���C�p�b�h�̐U���@�\���g�p����
	DxLib::SetUseJoypadVibrationFlag( true );
	dxJoypadInput.m_VibFlag_ = true;
}
// �W���C�p�b�h�̐U���@�\�ݒ���擾
bool	Lib::AppKeyPadController::getPadVibActionFlag( void )
{
	return ( dxJoypadInput.m_VibFlag_ );
}
//=========================================================================//
// �ڑ�����Ă���W���C�p�b�h��DirectInput����擾�ł�����𓾂�
//	<����>
//		InputType : ���͏�Ԃ��擾����p�b�h�̎��ʎq
//							DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//							DX_INPUT_PAD2�@�@�@�@: �p�b�h�Q
//							DX_INPUT_PAD3�@�@�@�@: �p�b�h�R
//							DX_INPUT_PAD4�@�@�@�@: �p�b�h�S
//		DInputState	: DirectInput���瓾������������� DINPUT_JOYSTATE �^�\���̂̃A�h���X
//	<�߂�>
//		�@�O�F����
//		�|�P�F�G���[����
int		Lib::AppKeyPadController::getPadDeviceDirectInput( DINPUT_JOYSTATE * pGetDInput )
{
	// ���͏�Ԃ��擾
	DxLib::GetJoypadDirectInputState( DX_INPUT_PAD1, pGetDInput ) ;
	if( pGetDInput == nullptr ){
		return ( -1 ); // �擾�Ɏ��s
	}
	// �擾�͐���
	return 0;
}

#if PROJECT_DEBUG
// 
int		Lib::AppKeyPadController::debKeyInputRuntime( const int  iKeyList )
{
	return 0;
}
// �L�[��"�P��"���������𔻒肷��
int		Lib::AppKeyPadController::debKeyInputOneCheck( const int  iKeyList, int iKeyFrame )
{
	return 0;
}
// �L�[�����������Ă��邩���肷��
int		Lib::AppKeyPadController::debKeyInputDirectCheck( const int  iKeyList, int iKeyFrame )
{
	return 0;
}
#endif