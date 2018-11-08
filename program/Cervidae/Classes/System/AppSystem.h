#pragma once

//=================================================================================//
//  AppSystem.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/06.
//=================================================================================//





class AppSystem
{
	// ���̃N���X�̃C���X�^���X
	static AppSystem *	s_pInstance;

public:
	AppSystem();
	~AppSystem();

public:
	// �Ꮘ�����׃��[�h���ǂ����̃t���O
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








