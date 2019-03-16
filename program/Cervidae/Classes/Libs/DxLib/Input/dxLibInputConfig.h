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
		// 日本語文字セット
		const static int			CHARSET_TYPE_DEFAULT		= DX_CHARSET_DEFAULT;
		const static int			CHARSET_TYPE_SHFTJIS		= DX_CHARSET_SHFTJIS;		// シフトJIS
		const static int			CHARSET_TYPE_UTF8			= DX_CHARSET_UTF8;			// UTF-8
		//	キー同時押し可能最大数
		const static int			SAMEINPUT_MAX				= ( 4 );
		//	ジョイパッドの最大数
		const static int			JOYPAD_EVENT_MAX			= MAX_JOYPAD_NUM;

		const static int			INPUT_WORKBUFFER			= 256;
	}
	namespace Command
	{
		const static int			INPUT_LOCK_NONE				= 0;

		const static int			INPUT_TYPE_PAD				= -1;
		const static int			INPUT_TYPE_KEYLR			= 0;
		const static int			INPUT_TYPE_KEYUD			= 1;

		const static int			INPUT_CHECKFLAG_KEY			= DX_CHECKINPUT_KEY;		//	キー入力を調べる
		const static int			INPUT_CHECKFLAG_PAD			= DX_CHECKINPUT_PAD;		//	パッド入力を調べる
		const static int			INPUT_CHECKFLAG_MOUSE		= DX_CHECKINPUT_MOUSE;		//	マウスボタン入力を調べる
		const static int			INPUT_CHECKFLAG_ALL			= DX_CHECKINPUT_ALL;		//	すべての入力を調べる

		const static bool			INPUT_TYPE_KEYPAD			= 0;				//	操作タイプ：キー入力
		const static bool			INPUT_TYPE_JOYPAD			= 1;				//	操作タイプ：ジョイパッド

		const static int			INPUT_MODE_GAME				= 0;				//	操作モード：ゲームモード
		const static int			INPUT_MODE_DEBUG			= 1;				//	操作モード：デバッグモード

		/*! @brief	キーボードキーリスト
		*/
		namespace lDxKey
		{
			const unsigned int			KEYINPUT_SYSTEM			= 0;
			const static unsigned int	KEYINPUT_LOCK			= (1 << 1);

			const static int			KEYINPUT_BUFFMAX		= 256;				//	
			const static int			KEYINPUT_NONUSE			= 0;				//	キー入力無し状態
			const static int			KEYINPUT_SINGLE			= 1;				//	キーを１回押した瞬間判定
			const static int			KEYINPUT_DIRECT			= 2;				//	キー押しっぱなし判定

			const static bool			KEYINPUT_LOCKFALSE		= (false);			//	キー入力ロック制限設定
			const static bool			KEYINPUT_LOCKTRUE		= (true);			//	キー入力ロック制限解除

			const static int			KEYINPUT_ENTER			=	KEY_INPUT_RETURN;			// Enterキー(決定)
			const static int			KEYINPUT_SPACE			=	KEY_INPUT_SPACE;			// スペースキー
			const static int			KEYINPUT_DELETE			=	KEY_INPUT_DELETE;			// Deleteキー
			const static int			KEYINPUT_INSERT			=	KEY_INPUT_INSERT;			// Insertキー
			const static int			KEYINPUT_END			=	KEY_INPUT_END;				// エンドキー
			const static int			KEYINPUT_HOME			=	KEY_INPUT_HOME;				// ホームキー
			const static int			KEYINPUT_BACKSPACE		=	KEY_INPUT_BACK;				// バックスペースキー
			const static int			KEYINPUT_CANCEL			=	KEY_INPUT_BACK;				// バックスペースキー(キャンセル定義)
			const static int			KEYINPUT_CAPSLOCK		=	KEY_INPUT_CAPSLOCK;			// CaspLockキー
			const static int			KEYINPUT_TAB			=	KEY_INPUT_TAB;				// タブ(Tab)キー
			const static int			KEYINPUT_LSHIFT			=	KEY_INPUT_LSHIFT;			// 左シフトキー
			const static int			KEYINPUT_RSHIFT			=	KEY_INPUT_RSHIFT;			// 右シフトキー
			const static int			KEYINPUT_LCONTROL		=	KEY_INPUT_LCONTROL;			// 左コントロールキー
			const static int			KEYINPUT_RCONTROL		=	KEY_INPUT_RCONTROL;			// 右コントロールキー
			const static int			KEYINPUT_LALT			=	KEY_INPUT_LALT;				// 左ＡＬＴキー
			const static int			KEYINPUT_RALT			=	KEY_INPUT_RALT;				// 右ＡＬＴキー
			const static int			KEYINPUT_PAGEUP			=	KEY_INPUT_PGUP;				// PAGE UPキー
			const static int			KEYINPUT_PAGEDOWN		=	KEY_INPUT_PGDN;				// PAGE DOWNキー
			const static int			KEYINPUT_KEYUP			=	KEY_INPUT_UP;				// △ キー
			const static int			KEYINPUT_KEYDOWN		=	KEY_INPUT_DOWN;				// ▽ キー
			const static int			KEYINPUT_KEYLEFT		=	KEY_INPUT_LEFT;				// ← キー
			const static int			KEYINPUT_F1				=	KEY_INPUT_F1;				// Ｆ１キー
			const static int			KEYINPUT_F2				=	KEY_INPUT_F2;				// Ｆ２キー
			const static int			KEYINPUT_F3				=	KEY_INPUT_F3;				// Ｆ３キー
			const static int			KEYINPUT_F4				=	KEY_INPUT_F4;				// Ｆ４キー
			const static int			KEYINPUT_F5				=	KEY_INPUT_F5;				// Ｆ５キー
			const static int			KEYINPUT_F6				=	KEY_INPUT_F6;				// Ｆ６キー
			const static int			KEYINPUT_F7				=	KEY_INPUT_F7;				// Ｆ７キー
			const static int			KEYINPUT_F8				=	KEY_INPUT_F8;				// Ｆ８キー
			const static int			KEYINPUT_F9				=	KEY_INPUT_F9;				// Ｆ９キー
			const static int			KEYINPUT_F10			=	KEY_INPUT_F10;				// Ｆ１０キー
			const static int			KEYINPUT_F11			=	KEY_INPUT_F11;				// Ｆ１１キー
			const static int			KEYINPUT_F12			=	KEY_INPUT_F12;				// Ｆ１２キー

			const static int			KEYINPUT_NUM0			=	KEY_INPUT_0;				// ０キー
			const static int			KEYINPUT_NUM1			=	KEY_INPUT_1;				// １キー
			const static int			KEYINPUT_NUM2			=	KEY_INPUT_2;				// ２キー
			const static int			KEYINPUT_NUM3			=	KEY_INPUT_3;				// ３キー
			const static int			KEYINPUT_NUM4			=	KEY_INPUT_4;				// ４キー
			const static int			KEYINPUT_NUM5			=	KEY_INPUT_5;				// ５キー
			const static int			KEYINPUT_NUM6			=	KEY_INPUT_6;				// ６キー
			const static int			KEYINPUT_NUM7			=	KEY_INPUT_7;				// ７キー
			const static int			KEYINPUT_NUM8			=	KEY_INPUT_8;				// ８キー
			const static int			KEYINPUT_NUM9			=	KEY_INPUT_9;				// ９キー

			const static int			KEYINPUT_SCROLLLOCK		=	KEY_INPUT_SCROLL;			// ScrollLockキー
			const static int			KEYINPUT_PRINTSCR		=	KEY_INPUT_SYSRQ;			// PrintScreenキー
			const static int			KEYINPUT_PAUSEBREAK		=	KEY_INPUT_PAUSE;			// PauseBreakキー

			//	デバッグ用
			const static int			INPUT_FLAG_DEBUP		=	KEYINPUT_KEYUP;
			const static int			INPUT_FLAG_DEBDOWN		=	KEYINPUT_KEYDOWN;
			const static int			INPUT_FLAG_DEBENTER		=	KEYINPUT_ENTER;
			const static int			INPUT_FLAG_DEBCANCEL	=	KEYINPUT_CANCEL;

			//	キーボードキーリスト
			const static int			KEYINPUT_KB_A			=	KEY_INPUT_A;			// Ａキー
			const static int			KEYINPUT_KB_B			=	KEY_INPUT_B;			// Ｂキー
			const static int			KEYINPUT_KB_C			=	KEY_INPUT_C;			// Ｃキー
			const static int			KEYINPUT_KB_D			=	KEY_INPUT_D;			// Ｄキー
			const static int			KEYINPUT_KB_E			=	KEY_INPUT_E;			// Ｅキー
			const static int			KEYINPUT_KB_F			=	KEY_INPUT_F;			// Ｆキー
			const static int			KEYINPUT_KB_G			=	KEY_INPUT_G;			// Ｇキー
			const static int			KEYINPUT_KB_H			=	KEY_INPUT_H;			// Ｈキー
			const static int			KEYINPUT_KB_I			=	KEY_INPUT_I;			// Ｉキー
			const static int			KEYINPUT_KB_J			=	KEY_INPUT_J;			// Ｊキー
			const static int			KEYINPUT_KB_K			=	KEY_INPUT_K;			// Ｋキー
			const static int			KEYINPUT_KB_L			=	KEY_INPUT_L;			// Ｌキー
			const static int			KEYINPUT_KB_M			=	KEY_INPUT_M;			// Ｍキー
			const static int			KEYINPUT_KB_N			=	KEY_INPUT_N;			// Ｎキー
			const static int			KEYINPUT_KB_O			=	KEY_INPUT_O;			// Ｏキー
			const static int			KEYINPUT_KB_P			=	KEY_INPUT_P;			// Ｐキー
			const static int			KEYINPUT_KB_Q			=	KEY_INPUT_Q;			// Ｑキー
			const static int			KEYINPUT_KB_R			=	KEY_INPUT_R;			// Ｒキー
			const static int			KEYINPUT_KB_S			=	KEY_INPUT_S;			// Ｓキー
			const static int			KEYINPUT_KB_T			=	KEY_INPUT_T;			// Ｔキー
			const static int			KEYINPUT_KB_U			=	KEY_INPUT_U;			// Ｕキー
			const static int			KEYINPUT_KB_V			=	KEY_INPUT_V;			// Ｖキー
			const static int			KEYINPUT_KB_W			=	KEY_INPUT_W;			// Ｗキー
			const static int			KEYINPUT_KB_X			=	KEY_INPUT_X;			// Ｘキー
			const static int			KEYINPUT_KB_Y			=	KEY_INPUT_Y;			// Ｙキー
			const static int			KEYINPUT_KB_Z			=	KEY_INPUT_Z;			// Ｚキー
			const static int			KEYBOARD_LIST_A			=	KEY_INPUT_A;			// 
		}

		/*! @brief	パッドキーリスト
		*/
		namespace	lDxPad
		{
			const static unsigned int		PADINPUT_SYSTEM				= (1);
			const static unsigned int		PADINPUT_LOCK				= (1 << 1);

			const static bool				PADINPUT_LOCKFALSE			= (false);			//	パッド入力ロック制限
			const static bool				PADINPUT_LOCKTRUE			= (true);			//	パッド入力ロック制限

			const static unsigned int		PADINPUT_CONTROLL_MAX		= (2);				//	コントローラーの数
			const static unsigned int		PADINPUT_CONTROLL_01		= (0);				//	コントローラーID1
			const static unsigned int		PADINPUT_CONTROLL_02		= (1);				//	コントローラーID2

			const static bool				PADINPUT_VIBRATFLAG			= (false);			//	パッド振動フラグ( TRUE:使用する, FALSE:使用しない )
			const static int				PADINPUT_VIBPOWER_MAX		= (1000);			//	パッド振動パワー最大
			const static int				PADINPUT_VIBDEFPOWER		= (1000);			//	パッド振動パワー( 0 ～ 1000 )
			const static int				PADINPUT_VIBTIME			= (2000);			//	パッド振動時間(ミリ秒単位)
			const static int				PADINPUT_VIBNONSTOP			= (-1);				//	パッド振動時間無制限(停止関数を呼ぶまで振動し続ける)

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

			const static int				PADINPUT_UP					= PAD_INPUT_UP;			// (0x00000001)↓：パッドチェックマスク
			const static int				PADINPUT_DOWN				= PAD_INPUT_DOWN;		// (0x00000002)←：パッドチェックマスク
			const static int				PADINPUT_LEFT				= PAD_INPUT_LEFT;		// (0x00000004)→：パッドチェックマスク
			const static int				PADINPUT_RIGHT				= PAD_INPUT_RIGHT;		// (0x00000008)↑：パッドチェックマスク

			const static int				PADINPUT_UPLEFT				= (PAD_INPUT_UP | PADINPUT_LEFT);		// 左上
			const static int				PADINPUT_UPRIGHT			= (PAD_INPUT_UP | PADINPUT_RIGHT);		// 右上
			const static int				PADINPUT_DOWNLEFT			= (PADINPUT_DOWN | PADINPUT_LEFT);		// 左下
			const static int				PADINPUT_DOWNRIGHT			= (PADINPUT_DOWN | PADINPUT_RIGHT);		// 右下

			const static int				PADINPUT_L					= PAD_INPUT_L;			// (0x00000400)Ｌボタンチェックマスク
			const static int				PADINPUT_R					= PAD_INPUT_R;			// (0x00000800)Ｒボタンチェックマスク
			const static int				PADINPUT_START				= PAD_INPUT_START;		// (0x00001000)ＳＴＡＲＴボタンチェックマスク

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
		/*! @brief	マウスキーリスト
		*/
		namespace	lDxMouse
		{
			const static unsigned int		MOUSEINPUT_SYSTEM			= (2);
			const static unsigned int		MOUSEINPUT_LOCK				= (1 << 2);
			const static unsigned int		MOUSEINPUT_LIMITFLAG		= (false);

			const static int				MOUSEINPUT_LEFT				= MOUSE_INPUT_LEFT;		//	(0x0001) マウス左ボタン
			const static int				MOUSEINPUT_CENTER			= MOUSE_INPUT_MIDDLE;	//	(0x0004) マウス中央ボタン
			const static int				MOUSEINPUT_RIGHT			= MOUSE_INPUT_RIGHT;	//	(0x0002) マウス右ボタン
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
		eINPUT_CHECK_SELYES = 0,		//	選択：[はい]
		eINPUT_CHECK_SELNO,				//	選択：[いいえ]

		ENUM_INPUT_SELECT_SELMAX,
	};
}

#define DXINPUT_ENABLE_ALL				( 0x7fffffff )		//	全ての入力を有効にする
#define DXINPUT_DISABLE_ALL				( 0x00000000 )		//	全ての入力を無効にする


//**************************************************************************************//
/*
	簡易設定
*/
//**************************************************************************************//

//	キー入力(１回判定)簡易マクロ
#define DX_ONEINPUT_KEYUP()				(DxInput::Command::lDxKey::KEYINPUT_KEYUP)
#define DX_ONEINPUT_KEYDOWN()			(DxInput::Command::lDxKey::KEYINPUT_KEYDOWN)
#define DX_ONEINPUT_KEYLEFT()			(DxInput::Command::lDxKey::KEYINPUT_KEYLEFT)
#define DX_ONEINPUT_KEYRIGHT()			(DxInput::Command::lDxKey::KEYINPUT_KEYRIGHT)
#define DX_ONEINPUT_ENTER()				(DxInput::Command::lDxKey::EYINPUT_ENTER)
#define DX_ONEINPUT_CANCEL()			(DxInput::Command::lDxKey::KEYINPUT_CANCEL)

//	キー入力(押しっぱなし判定)簡易マクロ
#define DX_DIRECTINPUT_ENTER()			(DxInput::Command::lDxKey::KEYINPUT_ENTER)
#define DX_DIRECTINPUT_CANCEL()			(DxInput::Command::lDxKey::KEYINPUT_CANCEL)





/* End dxLibInputConfig.h */

