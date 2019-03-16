#pragma once

//============================================================================//
//  dxLibInputConfig.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/02.
//============================================================================//

namespace DxInput
{
	namespace Info
	{
		// ���{�ꕶ���Z�b�g
		const static int			CHARSET_TYPE_DEFAULT		= DX_CHARSET_DEFAULT;
		const static int			CHARSET_TYPE_SHFTJIS		= DX_CHARSET_SHFTJIS;		// �V�t�gJIS
		const static int			CHARSET_TYPE_UTF8			= DX_CHARSET_UTF8;			// UTF-8
		//	�L�[���������\�ő吔
		const static int			SAMEINPUT_MAX				= ( 4 );
		//	�W���C�p�b�h�̍ő吔
		const static int			JOYPAD_EVENT_MAX			= MAX_JOYPAD_NUM;

		const static int			INPUT_WORKBUFFER			= 256;
	}
	namespace Command
	{
		const static int			INPUT_LOCK_NONE				= 0;

		const static int			INPUT_TYPE_PAD				= -1;
		const static int			INPUT_TYPE_KEYLR			= 0;
		const static int			INPUT_TYPE_KEYUD			= 1;

		const static int			INPUT_CHECKFLAG_KEY			= DX_CHECKINPUT_KEY;		//	�L�[���͂𒲂ׂ�
		const static int			INPUT_CHECKFLAG_PAD			= DX_CHECKINPUT_PAD;		//	�p�b�h���͂𒲂ׂ�
		const static int			INPUT_CHECKFLAG_MOUSE		= DX_CHECKINPUT_MOUSE;		//	�}�E�X�{�^�����͂𒲂ׂ�
		const static int			INPUT_CHECKFLAG_ALL			= DX_CHECKINPUT_ALL;		//	���ׂĂ̓��͂𒲂ׂ�

		const static bool			INPUT_TYPE_KEYPAD			= 0;				//	����^�C�v�F�L�[����
		const static bool			INPUT_TYPE_JOYPAD			= 1;				//	����^�C�v�F�W���C�p�b�h

		const static int			INPUT_MODE_GAME				= 0;				//	���샂�[�h�F�Q�[�����[�h
		const static int			INPUT_MODE_DEBUG			= 1;				//	���샂�[�h�F�f�o�b�O���[�h

		/*! @brief	�L�[�{�[�h�L�[���X�g
		*/
		namespace lDxKey
		{
			const unsigned int			KEYINPUT_SYSTEM			= 0;
			const static unsigned int	KEYINPUT_LOCK			= (1 << 1);

			const static int			KEYINPUT_BUFFMAX		= 256;				//	
			const static int			KEYINPUT_NONUSE			= 0;				//	�L�[���͖������
			const static int			KEYINPUT_SINGLE			= 1;				//	�L�[���P�񉟂����u�Ԕ���
			const static int			KEYINPUT_DIRECT			= 2;				//	�L�[�������ςȂ�����

			const static bool			KEYINPUT_LOCKFALSE		= (false);			//	�L�[���̓��b�N�����ݒ�
			const static bool			KEYINPUT_LOCKTRUE		= (true);			//	�L�[���̓��b�N��������

			const static int			KEYINPUT_ENTER			=	KEY_INPUT_RETURN;			// Enter�L�[(����)
			const static int			KEYINPUT_SPACE			=	KEY_INPUT_SPACE;			// �X�y�[�X�L�[
			const static int			KEYINPUT_DELETE			=	KEY_INPUT_DELETE;			// Delete�L�[
			const static int			KEYINPUT_INSERT			=	KEY_INPUT_INSERT;			// Insert�L�[
			const static int			KEYINPUT_END			=	KEY_INPUT_END;				// �G���h�L�[
			const static int			KEYINPUT_HOME			=	KEY_INPUT_HOME;				// �z�[���L�[
			const static int			KEYINPUT_BACKSPACE		=	KEY_INPUT_BACK;				// �o�b�N�X�y�[�X�L�[
			const static int			KEYINPUT_CANCEL			=	KEY_INPUT_BACK;				// �o�b�N�X�y�[�X�L�[(�L�����Z����`)
			const static int			KEYINPUT_CAPSLOCK		=	KEY_INPUT_CAPSLOCK;			// CaspLock�L�[
			const static int			KEYINPUT_TAB			=	KEY_INPUT_TAB;				// �^�u(Tab)�L�[
			const static int			KEYINPUT_LSHIFT			=	KEY_INPUT_LSHIFT;			// ���V�t�g�L�[
			const static int			KEYINPUT_RSHIFT			=	KEY_INPUT_RSHIFT;			// �E�V�t�g�L�[
			const static int			KEYINPUT_LCONTROL		=	KEY_INPUT_LCONTROL;			// ���R���g���[���L�[
			const static int			KEYINPUT_RCONTROL		=	KEY_INPUT_RCONTROL;			// �E�R���g���[���L�[
			const static int			KEYINPUT_LALT			=	KEY_INPUT_LALT;				// ���`�k�s�L�[
			const static int			KEYINPUT_RALT			=	KEY_INPUT_RALT;				// �E�`�k�s�L�[
			const static int			KEYINPUT_PAGEUP			=	KEY_INPUT_PGUP;				// PAGE UP�L�[
			const static int			KEYINPUT_PAGEDOWN		=	KEY_INPUT_PGDN;				// PAGE DOWN�L�[
			const static int			KEYINPUT_KEYUP			=	KEY_INPUT_UP;				// �� �L�[
			const static int			KEYINPUT_KEYDOWN		=	KEY_INPUT_DOWN;				// �� �L�[
			const static int			KEYINPUT_KEYLEFT		=	KEY_INPUT_LEFT;				// �� �L�[
			const static int			KEYINPUT_F1				=	KEY_INPUT_F1;				// �e�P�L�[
			const static int			KEYINPUT_F2				=	KEY_INPUT_F2;				// �e�Q�L�[
			const static int			KEYINPUT_F3				=	KEY_INPUT_F3;				// �e�R�L�[
			const static int			KEYINPUT_F4				=	KEY_INPUT_F4;				// �e�S�L�[
			const static int			KEYINPUT_F5				=	KEY_INPUT_F5;				// �e�T�L�[
			const static int			KEYINPUT_F6				=	KEY_INPUT_F6;				// �e�U�L�[
			const static int			KEYINPUT_F7				=	KEY_INPUT_F7;				// �e�V�L�[
			const static int			KEYINPUT_F8				=	KEY_INPUT_F8;				// �e�W�L�[
			const static int			KEYINPUT_F9				=	KEY_INPUT_F9;				// �e�X�L�[
			const static int			KEYINPUT_F10			=	KEY_INPUT_F10;				// �e�P�O�L�[
			const static int			KEYINPUT_F11			=	KEY_INPUT_F11;				// �e�P�P�L�[
			const static int			KEYINPUT_F12			=	KEY_INPUT_F12;				// �e�P�Q�L�[

			const static int			KEYINPUT_NUM0			=	KEY_INPUT_0;				// �O�L�[
			const static int			KEYINPUT_NUM1			=	KEY_INPUT_1;				// �P�L�[
			const static int			KEYINPUT_NUM2			=	KEY_INPUT_2;				// �Q�L�[
			const static int			KEYINPUT_NUM3			=	KEY_INPUT_3;				// �R�L�[
			const static int			KEYINPUT_NUM4			=	KEY_INPUT_4;				// �S�L�[
			const static int			KEYINPUT_NUM5			=	KEY_INPUT_5;				// �T�L�[
			const static int			KEYINPUT_NUM6			=	KEY_INPUT_6;				// �U�L�[
			const static int			KEYINPUT_NUM7			=	KEY_INPUT_7;				// �V�L�[
			const static int			KEYINPUT_NUM8			=	KEY_INPUT_8;				// �W�L�[
			const static int			KEYINPUT_NUM9			=	KEY_INPUT_9;				// �X�L�[

			const static int			KEYINPUT_SCROLLLOCK		=	KEY_INPUT_SCROLL;			// ScrollLock�L�[
			const static int			KEYINPUT_PRINTSCR		=	KEY_INPUT_SYSRQ;			// PrintScreen�L�[
			const static int			KEYINPUT_PAUSEBREAK		=	KEY_INPUT_PAUSE;			// PauseBreak�L�[

			//	�f�o�b�O�p
			const static int			INPUT_FLAG_DEBUP		=	KEYINPUT_KEYUP;
			const static int			INPUT_FLAG_DEBDOWN		=	KEYINPUT_KEYDOWN;
			const static int			INPUT_FLAG_DEBENTER		=	KEYINPUT_ENTER;
			const static int			INPUT_FLAG_DEBCANCEL	=	KEYINPUT_CANCEL;

			//	�L�[�{�[�h�L�[���X�g
			const static int			KEYINPUT_KB_A			=	KEY_INPUT_A;			// �`�L�[
			const static int			KEYINPUT_KB_B			=	KEY_INPUT_B;			// �a�L�[
			const static int			KEYINPUT_KB_C			=	KEY_INPUT_C;			// �b�L�[
			const static int			KEYINPUT_KB_D			=	KEY_INPUT_D;			// �c�L�[
			const static int			KEYINPUT_KB_E			=	KEY_INPUT_E;			// �d�L�[
			const static int			KEYINPUT_KB_F			=	KEY_INPUT_F;			// �e�L�[
			const static int			KEYINPUT_KB_G			=	KEY_INPUT_G;			// �f�L�[
			const static int			KEYINPUT_KB_H			=	KEY_INPUT_H;			// �g�L�[
			const static int			KEYINPUT_KB_I			=	KEY_INPUT_I;			// �h�L�[
			const static int			KEYINPUT_KB_J			=	KEY_INPUT_J;			// �i�L�[
			const static int			KEYINPUT_KB_K			=	KEY_INPUT_K;			// �j�L�[
			const static int			KEYINPUT_KB_L			=	KEY_INPUT_L;			// �k�L�[
			const static int			KEYINPUT_KB_M			=	KEY_INPUT_M;			// �l�L�[
			const static int			KEYINPUT_KB_N			=	KEY_INPUT_N;			// �m�L�[
			const static int			KEYINPUT_KB_O			=	KEY_INPUT_O;			// �n�L�[
			const static int			KEYINPUT_KB_P			=	KEY_INPUT_P;			// �o�L�[
			const static int			KEYINPUT_KB_Q			=	KEY_INPUT_Q;			// �p�L�[
			const static int			KEYINPUT_KB_R			=	KEY_INPUT_R;			// �q�L�[
			const static int			KEYINPUT_KB_S			=	KEY_INPUT_S;			// �r�L�[
			const static int			KEYINPUT_KB_T			=	KEY_INPUT_T;			// �s�L�[
			const static int			KEYINPUT_KB_U			=	KEY_INPUT_U;			// �t�L�[
			const static int			KEYINPUT_KB_V			=	KEY_INPUT_V;			// �u�L�[
			const static int			KEYINPUT_KB_W			=	KEY_INPUT_W;			// �v�L�[
			const static int			KEYINPUT_KB_X			=	KEY_INPUT_X;			// �w�L�[
			const static int			KEYINPUT_KB_Y			=	KEY_INPUT_Y;			// �x�L�[
			const static int			KEYINPUT_KB_Z			=	KEY_INPUT_Z;			// �y�L�[
			const static int			KEYBOARD_LIST_A			=	KEY_INPUT_A;			// 
		}

		/*! @brief	�p�b�h�L�[���X�g
		*/
		namespace	lDxPad
		{
			const static unsigned int		PADINPUT_SYSTEM				= (1);
			const static unsigned int		PADINPUT_LOCK				= (1 << 1);

			const static bool				PADINPUT_LOCKFALSE			= (false);			//	�p�b�h���̓��b�N����
			const static bool				PADINPUT_LOCKTRUE			= (true);			//	�p�b�h���̓��b�N����

			const static unsigned int		PADINPUT_CONTROLL_MAX		= (2);				//	�R���g���[���[�̐�
			const static unsigned int		PADINPUT_CONTROLL_01		= (0);				//	�R���g���[���[ID1
			const static unsigned int		PADINPUT_CONTROLL_02		= (1);				//	�R���g���[���[ID2

			const static bool				PADINPUT_VIBRATFLAG			= (false);			//	�p�b�h�U���t���O( TRUE:�g�p����, FALSE:�g�p���Ȃ� )
			const static int				PADINPUT_VIBPOWER_MAX		= (1000);			//	�p�b�h�U���p���[�ő�
			const static int				PADINPUT_VIBDEFPOWER		= (1000);			//	�p�b�h�U���p���[( 0 �` 1000 )
			const static int				PADINPUT_VIBTIME			= (2000);			//	�p�b�h�U������(�~���b�P��)
			const static int				PADINPUT_VIBNONSTOP			= (-1);				//	�p�b�h�U�����Ԗ�����(��~�֐����ĂԂ܂ŐU����������)

			const static int				PADINPUT_01					= DX_INPUT_PAD1;
			const static int				PADINPUT_02					= DX_INPUT_PAD2;
			const static int				PADINPUT_03					= DX_INPUT_PAD3;
			const static int				PADINPUT_04					= DX_INPUT_PAD4;
			const static int				PADINPUT_05					= DX_INPUT_PAD5;
			const static int				PADINPUT_06					= DX_INPUT_PAD6;
			const static int				PADINPUT_07					= DX_INPUT_PAD7;
			const static int				PADINPUT_08					= DX_INPUT_PAD8;
			const static int				PADINPUT_09					= DX_INPUT_PAD9;
			const static int				PADINPUT_10					= DX_INPUT_PAD10;
			const static int				PADINPUT_11					= DX_INPUT_PAD11;
			const static int				PADINPUT_12					= DX_INPUT_PAD12;
			const static int				PADINPUT_13					= DX_INPUT_PAD13;
			const static int				PADINPUT_14					= DX_INPUT_PAD14;
			const static int				PADINPUT_15					= DX_INPUT_PAD15;
			const static int				PADINPUT_16					= DX_INPUT_PAD16;

			const static int				PADINPUT_UP					= PAD_INPUT_UP;			// (0x00000001)���F�p�b�h�`�F�b�N�}�X�N
			const static int				PADINPUT_DOWN				= PAD_INPUT_DOWN;		// (0x00000002)���F�p�b�h�`�F�b�N�}�X�N
			const static int				PADINPUT_LEFT				= PAD_INPUT_LEFT;		// (0x00000004)���F�p�b�h�`�F�b�N�}�X�N
			const static int				PADINPUT_RIGHT				= PAD_INPUT_RIGHT;		// (0x00000008)���F�p�b�h�`�F�b�N�}�X�N

			const static int				PADINPUT_UPLEFT				= (PAD_INPUT_UP | PADINPUT_LEFT);		// ����
			const static int				PADINPUT_UPRIGHT			= (PAD_INPUT_UP | PADINPUT_RIGHT);		// �E��
			const static int				PADINPUT_DOWNLEFT			= (PADINPUT_DOWN | PADINPUT_LEFT);		// ����
			const static int				PADINPUT_DOWNRIGHT			= (PADINPUT_DOWN | PADINPUT_RIGHT);		// �E��

			const static int				PADINPUT_L					= PAD_INPUT_L;			// (0x00000400)�k�{�^���`�F�b�N�}�X�N
			const static int				PADINPUT_R					= PAD_INPUT_R;			// (0x00000800)�q�{�^���`�F�b�N�}�X�N
			const static int				PADINPUT_START				= PAD_INPUT_START;		// (0x00001000)�r�s�`�q�s�{�^���`�F�b�N�}�X�N

			const static int				PADINPUT_LL					= PAD_INPUT_LL;
			const static int				PADINPUT_RR					= PAD_INPUT_RR;

			const static int				PADINPUT_BUTTONA			= PAD_INPUT_A;
			const static int				PADINPUT_BUTTONB			= PAD_INPUT_B;
			const static int				PADINPUT_BUTTONC			= PAD_INPUT_C;
			const static int				PADINPUT_BUTTONX			= PAD_INPUT_X;
			const static int				PADINPUT_BUTTONY			= PAD_INPUT_Y;
			const static int				PADINPUT_BUTTONZ			= PAD_INPUT_Z;

			const static int				PADINPUT_OK					= 0;
			const static int				PADINPUT_CANCEL				= 0;
		}
		/*! @brief	�}�E�X�L�[���X�g
		*/
		namespace	lDxMouse
		{
			const static unsigned int		MOUSEINPUT_SYSTEM			= (2);
			const static unsigned int		MOUSEINPUT_LOCK				= (1 << 2);
			const static unsigned int		MOUSEINPUT_LIMITFLAG		= (false);

			const static int				MOUSEINPUT_LEFT				= MOUSE_INPUT_LEFT;		//	(0x0001) �}�E�X���{�^��
			const static int				MOUSEINPUT_CENTER			= MOUSE_INPUT_MIDDLE;	//	(0x0004) �}�E�X�����{�^��
			const static int				MOUSEINPUT_RIGHT			= MOUSE_INPUT_RIGHT;	//	(0x0002) �}�E�X�E�{�^��
		};
	}

	enum ENUM_INPUT_STATE
	{
		eINPUT_STATE_ERROR = -1,
		eINPUT_STATE_NONE,
		eINPUT_STATE_CLEAR,
	};
	enum ENUM_INPUT_SELECT
	{
		eINPUT_CHECK_SELYES = 0,		//	�I���F[�͂�]
		eINPUT_CHECK_SELNO,				//	�I���F[������]

		ENUM_INPUT_SELECT_SELMAX,
	};
}

#define DXINPUT_ENABLE_ALL				( 0x7fffffff )		//	�S�Ă̓��͂�L���ɂ���
#define DXINPUT_DISABLE_ALL				( 0x00000000 )		//	�S�Ă̓��͂𖳌��ɂ���


//**************************************************************************************//
/*
	�ȈՐݒ�
*/
//**************************************************************************************//

//	�L�[����(�P�񔻒�)�ȈՃ}�N��
#define DX_ONEINPUT_KEYUP()				(DxInput::Command::lDxKey::KEYINPUT_KEYUP)
#define DX_ONEINPUT_KEYDOWN()			(DxInput::Command::lDxKey::KEYINPUT_KEYDOWN)
#define DX_ONEINPUT_KEYLEFT()			(DxInput::Command::lDxKey::KEYINPUT_KEYLEFT)
#define DX_ONEINPUT_KEYRIGHT()			(DxInput::Command::lDxKey::KEYINPUT_KEYRIGHT)
#define DX_ONEINPUT_ENTER()				(DxInput::Command::lDxKey::EYINPUT_ENTER)
#define DX_ONEINPUT_CANCEL()			(DxInput::Command::lDxKey::KEYINPUT_CANCEL)

//	�L�[����(�������ςȂ�����)�ȈՃ}�N��
#define DX_DIRECTINPUT_ENTER()			(DxInput::Command::lDxKey::KEYINPUT_ENTER)
#define DX_DIRECTINPUT_CANCEL()			(DxInput::Command::lDxKey::KEYINPUT_CANCEL)





/* End dxLibInputConfig.h */

