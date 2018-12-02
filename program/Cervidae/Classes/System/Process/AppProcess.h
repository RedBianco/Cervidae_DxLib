#pragma once


#include "AppProcess.h"




//==============================================================================//
//	処理関数マクロ
//==============================================================================//
typedef int( *systemProcExec )( void );


//==============================================================================//
//	
//==============================================================================//
class AppProcManage
{
// TODO：暫定でSingleton化運用、今後他の方法を検討
private:
	// このクラスのインスタンス
	static AppProcManage *	s_pInstance;

public:
	// コンスタラクタ
	AppProcManage()
	{}
	// Instanceを削除する事は無いのでコメントアウト
//  virtual ~AppProcManage();

public:
	// 処理関数ポインタ
	systemProcExec	m_ProcessFunc;

public:
	bool	setProcessFunc( systemProcExec  pSetFunc );

	int		systemProcessUpdate( void );

public:
	// インスタンスの作成、取得
	static AppProcManage *    getInstance();
};












