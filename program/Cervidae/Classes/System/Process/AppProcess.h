#pragma once


// 処理関数マクロ
typedef int( *appProcessExec )( void );

/**
 *	@class	シーン管理元クラス
 */
class AppProcManager
{
// TODO：暫定でSingleton化運用、今後他の方法を検討
private:
	// このクラスのインスタンス
	static AppProcManager *	s_pInstance;

public:
	// コンスタラクタ
	AppProcManager()
	{}
	// Instanceを削除する事は無いのでコメントアウト
//  virtual ~AppProcManager();

private:
	// 処理関数ポインタ
	appProcessExec	m_ProcessFunc;

public:

	// 
	bool	setProcessFunc( appProcessExec  p_Function );

	// 
	int		appProcessUpdate( void );

public:
	// インスタンスの作成、取得
	static AppProcManager *    getInstance();
};














