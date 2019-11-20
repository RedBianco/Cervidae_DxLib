#pragma once

#include "dxLibDebugConfig.h"
#include "../../../Common/CervidaeLib/Template/tSingleton.h"
#include "dxLibDebugLog.h"

//=================================================================================//
//  dxLibDebug.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/30.
//=================================================================================//


namespace AppLib
{
	// DebugModeManageData
	class DebugMenuData
	{
	public:
		DebugMenuData();
		virtual ~DebugMenuData();

	public:
		// デバッグモード設定カウント
		int				m_debCount_;
		// 表示するデバッグモードタイプ
		int				m_debModeType_;
		// 表示するデバッグメニュー設定用
		std::string		m_debMenuName_;

		void	(*appDebStartFunc)();	// 指定のデバッグモードを開始した時の開始関数
		void	(*appDebEndFunc)();		// 指定のデバッグモードを開始した時の終了関数
		int		(*appDebMainFunc)();	// 指定のデバッグモードを開始した時の処理関数
		void	(*appDebRenderFunc)();	// 指定のデバッグモードを開始した時の描画関数
	};

	/*
	 * SingletonClass
	 */
	class DebugModeOperat : public Singleton<DebugModeOperat>
	{
		// DebugModeOperatのインスタンスを生成する時に、コンストラクタが呼べなかった為friend指定
		// シングルトンのテンプレート引数に自身を指定したものだけに生成をゆるす
		friend class Singleton<DebugModeOperat>;	// Singleton でのインスタンス作成は許可

	private:

		// デバッグモード
		int			m_debMode_;
		// メインメニュー選択用
		int			m_debMenuSelIndex_;
		// 描画用フラグ
		int			m_debDrawEnable_;
		// 各デバッグメニュー毎のデータ
		std::vector<DebugMenuData>	m_datDebMenu;
		
	public:
		// デバッグ基本設定処理
		bool	debugParamInitialize();
		// デバックのメニュー名セット
		int		debugMenuNameSet( const int setMode, const char * szName );

		// 指定のデバッグモードを開始した時の開始関数セット
		int		debugModeStartProcSet( const int setMode, const char * szName, void(*pStartFunc)() );
		// 指定のデバッグモードを開始した時の終了関数セット
		int		debugModeEndProcSet( const int setMode, const char * szName, void(*pEndFunc)() );
		// 指定のデバッグモードを開始した時の処理関数セット
		int		debugModeMainProcSet( const int setMode, const char * szName, int(*pMainFunc)() );
		// 指定のデバッグモードを開始した時の描画処理関数セット
		int		debugModeRenderProcSet( const int setMode, const char * szName, void(*pRenderFunc)() );
		
		// アップデート
		int		debugAppUpdate();
	
		// printfDx で表示した簡易画面出力履歴をクリアする
		void	debugDxPrintfLogClear();

	public:
		// コンストラクタ部分をpublicにしてしまうと、AppParameter  container; でインスタンスつくれてしまう
		// 「そのクラスのインスタンスが1つしか生成されないことを保証することができる」
		// と言うのに反するのでprivateにする必要がある。
		DebugModeOperat() {					// 外部でのインスタンス作成は禁止
			m_debMode_ = 0;
			m_debMenuSelIndex_ = 0;
			m_debDrawEnable_ = 0;
		};
	//	virtual ~DebugModeOperat();
	};

	class DebugModeMenu
	{
	public:
		DebugModeMenu();
		~DebugModeMenu();

	public:
	};

	/* @brief アクセスインターフェース
	*/
	inline DebugModeOperat* getDebugOperatPtr(void)
	{
		return Singleton<DebugModeOperat>::getSingletonPtr();
	}
}










/* End dxLibDebug.h */



