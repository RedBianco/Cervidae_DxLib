#pragma once


//=================================================================================//
//  appProcess.h
//  Cervidae
//
//  Created by kashima akihiro on 2019/12/02.
//=================================================================================//


// 処理関数マクロ
typedef int(*appProcessExec)(void);

/**
 *	@class
 */



 /**
  *	@class	シーン管理元クラス
  */
namespace App
{
	class ProcessManager
	{
		// TODO：暫定でSingleton化運用、今後他の方法を検討
	private:
		// このクラスのインスタンス
		static ProcessManager* s_pInstance;

	public:
		// コンスタラクタ
		ProcessManager()
		{}
		// Instanceを削除する事は無いのでコメントアウト
	//  virtual ~AppProcManager();

	private:
		// 処理関数ポインタ
		appProcessExec	m_ProcessFunc;

	public:

		// 
		bool	setProcessFunc(appProcessExec  p_Function);

		// 
		int		appProcessUpdate(void);

	public:
		// インスタンスの作成、取得
		static ProcessManager* getInstance();
	};
}


/* End appProcess.h */

