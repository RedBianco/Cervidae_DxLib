#pragma once

//=================================================================================//
//  AppSystem.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/06.
//=================================================================================//





class AppSystem
{
	// このクラスのインスタンス
	static AppSystem *	s_pInstance;

public:
	AppSystem();
	~AppSystem();

public:
	// 低処理負荷モードかどうかのフラグ
	bool		m_LowSpecMode;

public:
	bool		appSystemMain();

	void		setLowSpecMode( const bool setValue ){ m_LowSpecMode = setValue; }
	bool		getLowSpecMode() const { return m_LowSpecMode; }
	
private:
	
	bool		appSystemInitialize();
	void		appSystemTerminate();
	bool		appSystemUpdate();


};




/* End AppSystem.h */








