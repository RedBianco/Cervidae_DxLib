#pragma once

#include "dxLibDebugConfig.h"

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

	// SingletonClass
	class DebugModeOperat
	{
	private:

		// デバッグモード
		int			m_debMode_;
		// メインメニュー選択用
		int			m_debMenuSelIndex_;
		// 描画用フラグ
		int			m_debDrawEnable_;

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
		
		// 
		int		debugAppUpdate();
	
		// printfDx で表示した簡易画面出力履歴をクリアする
		void	debugDxPrintfLogClear();

	public:
		// インスタンスの作成、取得
		static DebugModeOperat * getInstance();

	private:
		static DebugModeOperat * s_pInstance;
		// 隠しコンストラクタ
		DebugModeOperat(){
		}
	};
}










/* End dxLibDebug.h */



