#pragma once


//============================================================================//
//  dxLibKeyPadUtility.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/04.
//============================================================================//

// NOTE:�����̓N���X�Ɍp�������Ă������Ŋe���̃f�o�b�O���[�h����������݌v��
//      �l���Ă�����
//      �E�}���`�X���b�h�I�ɓ�������o����̂������n�����o���o���ɂȂ肻��
//      �̗��R��Singleton�Ǘ��ɕύX�A����C���̉\���L��
namespace Lib
{
	/**
	 * 
	 */
	struct KeyInputOperat
	{
		char	m_KeyBuff_[256];	//*! @param �L�[�o�b�t�@
		int		m_KeyFlag_[256];	//*! @param 0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���
		int		m_KeyStatus_;		//*! @param ���̓X�e�[�^�X
		int		m_KeyInputMode_;	//*! @param ���̓L�[�{�[�h(0�F�ʏ�Q�[���A1�F�f�o�b�O)

#if PROJECT_DEBUG
		char	debKeyBuff_[256];	//*! @param	�f�o�b�O�p�F�L�[�o�b�t�@
		int		debKeyFlag_[256];	//*! @param	�f�o�b�O�p�F0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���
#endif
	};

	/**
	 * 
	 */
	struct JoypadInputOperat
	{
		int		m_ConnectNum_;		//*! @param	�W���C�p�b�h�ڑ���
		bool	m_PadEnable_;		//*! @param	�W���C�p�b�h�ڑ����� ON/OFF
		int		m_InputFlag_;		//*! @param	

		bool	m_VibFlag_;			//*! @param	�W���C�p�b�h�U���ݒ�( TRUE:�g�p����, FALSE:�g�p���Ȃ� )
		int		m_VibPower_;		//*! @param	�W���C�p�b�h�U���p���[
		int		m_VibTime_;			//*! @param	�W���C�p�b�h�U�������鎞��(�~���b�P��)

#if PROJECT_DEBUG
		int		debPadInput_;
		char	debInstInfo_[64];
		char	debDeviceInfo_[64];
#endif
	};

	/*
	 * 
	 */
	class AppKeyPadController : public Singleton<AppKeyPadController>
	{
		// DebugModeOperat�̃C���X�^���X�𐶐����鎞�ɁA�R���X�g���N�^���ĂׂȂ�������friend�w��
		// �V���O���g���̃e���v���[�g�����Ɏ��g���w�肵�����̂����ɐ�������邷
		friend class Singleton<AppKeyPadController>;	// Singleton �ł̃C���X�^���X�쐬�͋���

	private:

		KeyInputOperat		dxKeyInput;
		JoypadInputOperat	dxJoypadInput;
	
	private:

		unsigned int	uiInputLockBit_;		//*! @param	���̓��b�N�ݒ�

	public:

		// ���̓p�����[�^������
		bool			inputParamInit( void );
		// �L�[�E�p�b�h���̓V�X�e����{����������
		void			inputStatusClear( void );
		// �L�[�E�p�b�h���̓V�X�e�������^�C��
		void			updateInputControl( void );
		// �L�[�E�p�b�h���̓��b�N�ݒ�( 0:�L�[���̓V�X�e��, 1:�p�b�h���̓V�X�e�� )
		void			inputSystemApply( const bool  bInputApply, const bool  bApplyFlag );
		void			inputKeyModeSet( const int  setMode);
		int				inputKeyModeGet() const { return dxKeyInput.m_KeyInputMode_;  }
		bool			inputModeDebug( void );

		// �L�[���̓V�X�e�������^�C��(�ŐV�̑S�ẴL�[���͏�Ԃ��擾)
		int				updateKeyInput( const int  iKeyList = 0 );
		// �L�[��"�P��"���������𔻒肷��
		int				keyInputOneCheck( const int  iKeyList, int iKeyFrame = 1, int * pKeyOutFlag = nullptr );
		// �L�[�����������Ă��邩���肷��
		int				keyInputDirectCheck( const int  iKeyList, int iKeyFrame = 1, int * pKeyOutFlag = nullptr );
		// �L�[���b�N�ݒ�( TRUE:���b�N����, FALSE:���b�N���� )
		void			keyInputLockEnable( const bool  bLockFlag );
		// �L�[���b�N�ݒ���擾
		bool			isKeyInputLockEnable( void );

		////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////
		// �p�b�h�V�X�e����{������
		bool			padParamInit( void );
		// �p�b�h���̓V�X�e�����t���[������
		void			updateJoypadInput( void );
		// �W���C�p�b�h�̐ڑ������擾����
		int				getPadInputConnectNum( void );
		// �W���C�p�b�h���b�N�ݒ�( TRUE:���b�N����, FALSE:���b�N���� )
		void			padInputLockEnable( const bool  bLockFlag );
		// �W���C�p�b�h���b�N�ݒ���擾
		bool			isPadInputLockEnable( void );

		// �W���C�p�b�h�U���J�n����
		int				padInputVibActionStart( const int vibInputType, int vibTime );
		// �W���C�p�b�h�U����~����
		void			padInputVibActionEnd( const int vibInputType );
		// �W���C�p�b�h�U���p���[�l�ݒ�( 0 �` 1000 )
		void			setPadInputVibPower( int  iVibPower );
		// �W���C�p�b�h�U�����Ԏ擾(�~���b�P��)
		int				getPadInputVibActionTime( void );
		// �W���C�p�b�h�̐U���@�\���I����
		void			setPadVibActionOn( void );
		// �W���C�p�b�h�̐U���@�\�ݒ���擾
		bool			getPadVibActionFlag( void );
		// �ڑ�����Ă���W���C�p�b�h��DirectInput����擾�ł�����𓾂�
		int				getPadDeviceDirectInput( DINPUT_JOYSTATE * pGetDInput );

	#if PROJECT_DEBUG
		// 
		int		debKeyInputRuntime( const int iKeyList = 0 );
		// �L�[��"�P��"���������𔻒肷��
		int		debKeyInputOneCheck( const int iKeyList, int iKeyFrame = 1 );
		// �L�[�����������Ă��邩���肷��
		int		debKeyInputDirectCheck( const int iKeyList, int iKeyFrame = 1 );
	#endif

	public:
		// �R���X�g���N�^������public�ɂ��Ă��܂��ƁAAppParameter  container; �ŃC���X�^���X����Ă��܂�
		// �u���̃N���X�̃C���X�^���X��1������������Ȃ����Ƃ�ۏ؂��邱�Ƃ��ł���v
		// �ƌ����̂ɔ�����̂�private�ɂ���K�v������B
		AppKeyPadController() {		// �O���ł̃C���X�^���X�쐬�͋֎~
			inputParamInit();
			padParamInit();
		};
	//	virtual ~DebugModeOperat();
	};

	/* @brief �A�N�Z�X�C���^�[�t�F�[�X
	*/
	inline AppKeyPadController* getKeyPadOperatPtr(void)
	{
		return Singleton<AppKeyPadController>::getSingletonPtr();
	}
}


/* End dxLibKeyPadUtility.h */
