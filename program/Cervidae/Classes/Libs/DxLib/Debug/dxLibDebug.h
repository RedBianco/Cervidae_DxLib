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
		// �f�o�b�O���[�h�ݒ�J�E���g
		int				m_debCount_;
		// �\������f�o�b�O���[�h�^�C�v
		int				m_debModeType_;
		// �\������f�o�b�O���j���[�ݒ�p
		std::string		m_debMenuName_;

		void	(*appDebStartFunc)();	// �w��̃f�o�b�O���[�h���J�n�������̊J�n�֐�
		void	(*appDebEndFunc)();		// �w��̃f�o�b�O���[�h���J�n�������̏I���֐�
		int		(*appDebMainFunc)();	// �w��̃f�o�b�O���[�h���J�n�������̏����֐�
		void	(*appDebRenderFunc)();	// �w��̃f�o�b�O���[�h���J�n�������̕`��֐�
	};

	// SingletonClass
	class DebugModeOperat
	{
	private:

		// �f�o�b�O���[�h
		int			m_debMode_;
		// ���C�����j���[�I��p
		int			m_debMenuSelIndex_;
		// �`��p�t���O
		int			m_debDrawEnable_;

		std::vector<DebugMenuData>	m_datDebMenu;
		
	public:
		// �f�o�b�O��{�ݒ菈��
		bool	debugParamInitialize();
		// �f�o�b�N�̃��j���[���Z�b�g
		int		debugMenuNameSet( const int setMode, const char * szName );

		// �w��̃f�o�b�O���[�h���J�n�������̊J�n�֐��Z�b�g
		int		debugModeStartProcSet( const int setMode, const char * szName, void(*pStartFunc)() );
		// �w��̃f�o�b�O���[�h���J�n�������̏I���֐��Z�b�g
		int		debugModeEndProcSet( const int setMode, const char * szName, void(*pEndFunc)() );
		// �w��̃f�o�b�O���[�h���J�n�������̏����֐��Z�b�g
		int		debugModeMainProcSet( const int setMode, const char * szName, int(*pMainFunc)() );
		// �w��̃f�o�b�O���[�h���J�n�������̕`�揈���֐��Z�b�g
		int		debugModeRenderProcSet( const int setMode, const char * szName, void(*pRenderFunc)() );
		
		// 
		int		debugAppUpdate();
	
		// printfDx �ŕ\�������ȈՉ�ʏo�͗������N���A����
		void	debugDxPrintfLogClear();

	public:
		// �C���X�^���X�̍쐬�A�擾
		static DebugModeOperat * getInstance();

	private:
		static DebugModeOperat * s_pInstance;
		// �B���R���X�g���N�^
		DebugModeOperat(){
		}
	};
}










/* End dxLibDebug.h */



