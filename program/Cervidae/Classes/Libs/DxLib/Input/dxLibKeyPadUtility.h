#pragma once

#include "DxLib.h"
//============================================================================//
//  dxLibKeyPadUtility.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/04.
//============================================================================//

class AppKeyPadController
{
public:
	AppKeyPadController();
	virtual	~AppKeyPadController();
	
public:
	char				m_KeyBuff_[256];				//	�L�[�o�b�t�@
	int				m_KeyFlag_[256];				//	0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���
	int				m_KeyStatus_;					//	���̓X�e�[�^�X
	int				m_KeyInputMode_;			//	���̓L�[�{�[�h(0�F�ʏ�Q�[���A1�F�f�o�b�O)

#if defined( PROJECT_DEBUG )
	char				debKeyBuff_[256];				//	�f�o�b�O�p�F�L�[�o�b�t�@
	int				debKeyFlag_[256];				//	�f�o�b�O�p�F0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���
#endif

	unsigned int	uiInputLockBit_;				//	���̓��b�N�ݒ�

	struct 
	{
		int		m_ConnectNum_;			//*! @param	�W���C�p�b�h�ڑ��� */
		bool		m_PadEnable_;				//*! @param	�W���C�p�b�h�ڑ����� ON/OFF */
		int		m_InputFlag_;				//*! @param	 */

		bool		m_VibFlag_;					//*! @param	�W���C�p�b�h�U���ݒ�( TRUE:�g�p����, FALSE:�g�p���Ȃ� ) */
		int		m_VibPower_;				//*! @param	�W���C�p�b�h�U���p���[ */
		int		m_VibTime_;				//*! @param	�W���C�p�b�h�U�������鎞��(�~���b�P��) */

#if defined( PROJECT_DEBUG )
		int			debPadInput_;
		char			debInstInfo_[ 64];
		char			debDeviceInfo_[ 64];
#endif
	} dxPadlib_;

public:
	// �L�[�E�p�b�h���̓V�X�e����{����������
	void			inputStatusClear( void );
	// �L�[�E�p�b�h���̓V�X�e�������^�C��
	void			inputRuntime( void );
	// �L�[�E�p�b�h���̓��b�N�ݒ�( 0:�L�[���̓V�X�e��, 1:�p�b�h���̓V�X�e�� )
	void			inputSystemApply( const bool  bInputApply, const bool  bApplyFlag );
	void			inputKeyModeSet( const int  setMode);
	int			inputKeyModeGet() const { return m_KeyInputMode_;  }
	bool			inputModeDebug( void );

	// �L�[���̓V�X�e�������^�C��(�ŐV�̑S�ẴL�[���͏�Ԃ��擾)
	int			updateKeyInput( const int  iKeyList = 0 );
	// �L�[��"�P��"���������𔻒肷��
	int			keyInputOneCheck( const int  iKeyList, int iKeyFrame = 1, int * pKeyOutFlag = nullptr );
	// �L�[�����������Ă��邩���肷��
	int			keyInputDirectCheck( const int  iKeyList, int iKeyFrame = 1, int * pKeyOutFlag = nullptr );
	// �L�[���b�N�ݒ�( TRUE:���b�N����, FALSE:���b�N���� )
	void			keyInputLockEnable( const bool  bLockFlag );
	// �L�[���b�N�ݒ���擾
	bool			isKeyInputLockEnable( void );

	////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////
	// �p�b�h�V�X�e����{������
	bool			padParamInitialize( void );
	// �p�b�h���̓V�X�e�����t���[������
	void			updatePadInput( void );
	// �W���C�p�b�h�̐ڑ������擾����
	int			getPadInputConnectNum( void );
	// �W���C�p�b�h���b�N�ݒ�( TRUE:���b�N����, FALSE:���b�N���� )
	void			padInputLockEnable( const bool  bLockFlag );
	// �W���C�p�b�h���b�N�ݒ���擾
	bool			isPadInputLockEnable( void );

	// �W���C�p�b�h�U���J�n����
	int			padInputVibActionStart( const int vibInputType, int vibTime );
	// �W���C�p�b�h�U����~����
	void			padInputVibActionEnd( const int vibInputType );
	// �W���C�p�b�h�U���p���[�l�ݒ�( 0 �` 1000 )
	void			setPadInputVibPower( int  iVibPower );
	// �W���C�p�b�h�U�����Ԏ擾(�~���b�P��)
	int			getPadInputVibActionTime( void );
	// �W���C�p�b�h�̐U���@�\���I����
	void			setPadVibActionOn( void );
	// �W���C�p�b�h�̐U���@�\�ݒ���擾
	bool			getPadVibActionFlag( void );
	// �ڑ�����Ă���W���C�p�b�h��DirectInput����擾�ł�����𓾂�
	int			getPadDeviceDirectInput( DINPUT_JOYSTATE * pGetDInput );

#if defined( PROJECT_DEBUG )
	// 
	int			debKeyInputRuntime( const int  iKeyList = 0 );
	// �L�[��"�P��"���������𔻒肷��
	int			debKeyInputOneCheck( const int  iKeyList, int iKeyFrame = 1 );
	// �L�[�����������Ă��邩���肷��
	int			debKeyInputDirectCheck( const int  iKeyList, int iKeyFrame = 1 );
#endif
};


/* End dxLibKeyPadUtility.h */
