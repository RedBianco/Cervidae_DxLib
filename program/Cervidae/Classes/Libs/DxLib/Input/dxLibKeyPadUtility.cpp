

#include "../../../Common/CommonList.h"
#include "../../../Common/CervidaeLib/CLDefine.h"
#include "../dxLibDefine.h"
#include "dxLibKeyPadUtility.h"
#include "dxLibInputConfig.h"

/*
	DX���C�u����	�L�[�E�p�b�h���͊Ǘ��V�X�e��
	���e�V�[���N���X�Ɍp�������Ďg�p����z��
*/

AppKeyPadController::AppKeyPadController() :
	m_KeyStatus_( 0 ),
	m_KeyInputMode_( DxInput::Command::INPUT_MODE_GAME ),
	uiInputLockBit_( DxInput::Command::INPUT_LOCK_NONE )
{
	for( int i = 0; i < DxInput::Info::INPUT_WORKBUFFER; i ++ )
	{
		m_KeyBuff_[ i ] = 0;
		m_KeyFlag_[ i ] = 0;
#if defined( PROJECT_DEBUG )
		debKeyBuff_[ i ] = 0;
		debKeyFlag_[ i ] = 0;
#endif
	}
//	memset( m_KeyFlag_, 0, sizeof( m_KeyFlag_ ) * DxInput::Info::INPUT_WORKBUFFER );

	padParamInitialize();

	// �e���̓^�C�v���b�N�ݒ�
	inputSystemApply( DxInput::Command::INPUT_TYPE_KEYPAD, FALSE );
	inputSystemApply( DxInput::Command::INPUT_TYPE_JOYPAD, TRUE );
}
AppKeyPadController::~AppKeyPadController()
{
}

void		AppKeyPadController::inputStatusClear( void )
{
}
// �L�[�E�p�b�h���̓V�X�e�������^�C��
void		AppKeyPadController::inputRuntime( void )
{
	updateKeyInput();

	updatePadInput();
}
// �L�[�E�p�b�h���̓��b�N�ݒ�( 0:�L�[���̓V�X�e��, 1:�p�b�h���̓V�X�e�� )
void		AppKeyPadController::inputSystemApply( const bool  bInputApply, const bool  bApplyFlag )
{
	if( bInputApply == DxInput::Command::INPUT_TYPE_KEYPAD )
	{
		keyInputLockEnable( bApplyFlag );	//	�L�[���̓V�X�e��
	}else{
		keyInputLockEnable( bApplyFlag );	//	�p�b�h���̓V�X�e��
	}
}
// �L�[�E�p�b�h���̓��[�h�Z�b�g
void		AppKeyPadController::inputKeyModeSet( const int  setMode )
{
	m_KeyInputMode_ = setMode;
}
bool		AppKeyPadController::inputModeDebug( void )
{
	return (m_KeyInputMode_ == DxInput::Command::INPUT_MODE_DEBUG ) ? true : false;
}
//=====================================================//
//
//=====================================================//
int		AppKeyPadController::updateKeyInput( const int  iKeyList )
{
	if( inputKeyModeGet() == DxInput::Command::INPUT_MODE_GAME ){
		return -1;
	}
	// �S�ẴL�[���͏�Ԃ��擾(�O�F����, �|�P�F�G���[����)
	GetHitKeyStateAll( m_KeyBuff_ );
	int  i = 0;
	for( i = 0; i < DxInput::Info::INPUT_WORKBUFFER; i ++ )
	{
		// ���͏�Ԃ��擾����Ă����
		if( m_KeyBuff_[i] )
		{
			if( m_KeyFlag_[i] == 0 )
			{
				m_KeyFlag_[i] = DxInput::Command::lDxKey::KEYINPUT_SINGLE;	//	�P�񉟂���
			}
			else if( m_KeyFlag_[i] == 1 ) // ���Ɉ�񉟂���Ă����Ԃł�����񉟂�(�܂艟�����ςȂ��Ȃ�)
			{
				m_KeyFlag_[i] = DxInput::Command::lDxKey::KEYINPUT_DIRECT;	//	�������ςȂ�����
			}
		}else {
			m_KeyFlag_[i] = 0;		//	���͂���Ă��Ȃ�
		}
	}
	return ( 0 );
}
// �L�[��"�P��"���������𔻒肷��
int		AppKeyPadController::keyInputOneCheck( const int  iKeyList, int iKeyFrame, int * pKeyOutFlag )
{
	const int i = iKeyList;

	// ���b�N�����`�F�b�N
	if( isKeyInputLockEnable() ){ return -1; };

	if( m_KeyBuff_[ i ] )
	{
		//	�L�[���P�񉟂����u�Ԕ���
		if( m_KeyFlag_[ i ] == DxInput::Command::lDxKey::KEYINPUT_SINGLE )
		{
//			if( *pKeyOutFlag != nullptr ){ *pKeyOutFlag = DxInput::Command::lDxKey::KEYINPUT_SINGLE; }
			return ( 1 );	//	����N���A
		}
	}
	return ( 0 );
}
// �L�[�����������Ă��邩���肷��
int		AppKeyPadController::keyInputDirectCheck( const int  iKeyList, int iKeyFrame, int * pKeyOutFlag )
{
	const int	i = iKeyList;

	//	���b�N�����`�F�b�N
	if( isKeyInputLockEnable() ){ return -1; };

	if( m_KeyBuff_[ i ] )
	{
		//	�L�[�������ςȂ�����
		if( m_KeyFlag_[ i ] == DxInput::Command::lDxKey::KEYINPUT_DIRECT )
		{
//			if( *pKeyOutFlag != nullptr ){ *pKeyOutFlag = DxInput::Command::lDxKey::KEYINPUT_DIRECT; }
			return ( 1 );	//	����N���A
		}
	}
	return ( 0 );
}
// �L�[���b�N�ݒ�( TRUE:���b�N����, FALSE:���b�N���� )
void		AppKeyPadController::keyInputLockEnable( const bool  bLockFlag )
{
	//	�f�o�b�O���[�h�����K�p�����
	if( bLockFlag )
	{
		//	���b�N����
		uiInputLockBit_ |= DxInput::Command::lDxKey::KEYINPUT_LOCK;
	}else{
		//	���b�N����
		uiInputLockBit_ &= ~DxInput::Command::lDxKey::KEYINPUT_LOCK;
	}
}
// �L�[���b�N�ݒ���擾
bool		AppKeyPadController::isKeyInputLockEnable( void )
{
	return ( ( uiInputLockBit_ & DxInput::Command::lDxKey::KEYINPUT_LOCK ) != 0 );
}

// �p�b�h�V�X�e����{������
bool		AppKeyPadController::padParamInitialize( void )
{
	//	�W���C�p�b�h�ڑ������擾
	dxPadlib_.m_ConnectNum_	= DxLib::GetJoypadNum();
	dxPadlib_.m_PadEnable_		= false;

	//	�p�b�h�U�����
	dxPadlib_.m_VibFlag_			= DxInput::Command::lDxPad::PADINPUT_VIBRATFLAG;
	dxPadlib_.m_VibPower_			= DxInput::Command::lDxPad::PADINPUT_VIBDEFPOWER;
	dxPadlib_.m_VibTime_			= DxInput::Command::lDxPad::PADINPUT_VIBTIME;

	// �W���C�p�b�h�̐U���@�\���g�p���邩�ǂ�����ݒ�(���f�t�H���g�͎g�p���Ȃ�,�g�p����ꍇ�͎蓮����)
	SetUseJoypadVibrationFlag( static_cast<int>( DxInput::Command::lDxPad::PADINPUT_VIBRATFLAG ) );

	ERROR_PRINT( "" );

	return true;
}
// �p�b�h���̓V�X�e�����t���[������
void		AppKeyPadController::updatePadInput( void )
{
	if( isPadInputLockEnable() ){
		return;	//	���b�N���|�����Ă���Ȃ甲����
	}

	int nJoyPadLinkNum_ = DxLib::GetJoypadNum();	//	�W���C�p�b�h���ڑ�����Ă��鐔���擾����
	if( nJoyPadLinkNum_ != dxPadlib_.m_ConnectNum_ )
	{
		dxPadlib_.m_ConnectNum_ = nJoyPadLinkNum_;	//	���t���[�����ăp�b�h�ڑ������ς���Ă���΍X�V����
	}
//	if( nJoyPadLinkNum_ <= 0 )
//	{
//		dxPadlib_.m_PadEnable_ = false;
//	}
}

// �W���C�p�b�h�̐ڑ������擾����
int		AppKeyPadController::getPadInputConnectNum( void )
{
	return dxPadlib_.m_ConnectNum_;
}
// �W���C�p�b�h���b�N�ݒ�( TRUE:���b�N����, FALSE:���b�N���� )
void		AppKeyPadController::padInputLockEnable( const bool  bLockFlag )
{
	if( bLockFlag )
	{
		uiInputLockBit_ |= DxInput::Command::lDxPad::PADINPUT_LOCK;
	}else{
		uiInputLockBit_ &= ~DxInput::Command::lDxPad::PADINPUT_LOCK;
	}
}
// �W���C�p�b�h���b�N�ݒ���擾
bool		AppKeyPadController::isPadInputLockEnable( void )
{
	return ((uiInputLockBit_ & DxInput::Command::lDxPad::PADINPUT_LOCK) != 0);
}
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
int		AppKeyPadController::padInputVibActionStart( const int vibInputType, int vibTime )
{
	if( vibTime < 0 ){
		vibTime = 1000;
	}

	//	�U���J�n
	auto	nvibRResult_ = DxLib::StartJoypadVibration( vibInputType, dxPadlib_.m_VibPower_, vibTime );
	if( nvibRResult_ == -1 )
	{
		//	�G���[
		return ( -1 );
	}
	//	�U���̋���
	dxPadlib_.m_VibPower_	= dxPadlib_.m_VibPower_;
	//	�U�������鎞��
	dxPadlib_.m_VibTime_	=  vibTime;

	return ( 0 );
}
// �W���C�p�b�h�U����~����
void			AppKeyPadController::padInputVibActionEnd( const int vibInputType )
{
	if( getPadInputVibActionTime() == -1 )
	{
		DxLib::StopJoypadVibration( vibInputType );
	}
}
// �W���C�p�b�h�U���p���[�l�ݒ�( 0 �` 1000 )
void			AppKeyPadController::setPadInputVibPower( int  setVibPower )
{
	if( setVibPower > DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX ){
		ERROR_PRINT("__ERROR__ : dxLib_SetPadInputVibPower VibPowerOver[%d]\n", DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX );
		setVibPower = DxInput::Command::lDxPad::PADINPUT_VIBPOWER_MAX;
	}
	dxPadlib_.m_VibPower_	= setVibPower;
}
// �W���C�p�b�h�U�����Ԏ擾(�~���b�P��)
int			AppKeyPadController::getPadInputVibActionTime( void )
{
	return ( dxPadlib_.m_VibTime_ );
}
// �W���C�p�b�h�̐U���@�\���I����
void			AppKeyPadController::setPadVibActionOn( void )
{
	// �W���C�p�b�h�̐U���@�\���g�p����
	DxLib::SetUseJoypadVibrationFlag( true );
	dxPadlib_.m_VibFlag_ = true;
}
// �W���C�p�b�h�̐U���@�\�ݒ���擾
bool			AppKeyPadController::getPadVibActionFlag( void )
{
	return ( dxPadlib_.m_VibFlag_ );
}
// �ڑ�����Ă���W���C�p�b�h��DirectInput����擾�ł�����𓾂�
//	<����>
//		InputType : ���͏�Ԃ��擾����p�b�h�̎��ʎq
//							DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//							DX_INPUT_PAD2�@�@�@�@: �p�b�h�Q
//							DX_INPUT_PAD3�@�@�@�@: �p�b�h�R
//							DX_INPUT_PAD4�@�@�@�@: �p�b�h�S
//		DInputState	: DirectInput���瓾������������� DINPUT_JOYSTATE �^�\���̂̃A�h���X
//	<�߂�>
//			�O�F����
//		�|�P�F�G���[����
int			AppKeyPadController::getPadDeviceDirectInput( DINPUT_JOYSTATE * pGetDInput )
{
	// ���͏�Ԃ��擾
	DxLib::GetJoypadDirectInputState( DX_INPUT_PAD1, pGetDInput ) ;
	if( pGetDInput == nullptr ){
		return ( -1 );	//	�擾�Ɏ��s
	}
	// �擾�͐���
	return 0;
}

#if defined( PROJECT_DEBUG )
#endif







