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

	/*
	 * SingletonClass
	 */
	class DebugModeOperat : public Singleton<DebugModeOperat>
	{
		// DebugModeOperat�̃C���X�^���X�𐶐����鎞�ɁA�R���X�g���N�^���ĂׂȂ�������friend�w��
		// �V���O���g���̃e���v���[�g�����Ɏ��g���w�肵�����̂����ɐ�������邷
		friend class Singleton<DebugModeOperat>;	// Singleton �ł̃C���X�^���X�쐬�͋���

	private:

		// �f�o�b�O���[�h
		int			m_debMode_;
		// ���C�����j���[�I��p
		int			m_debMenuSelIndex_;
		// �`��p�t���O
		int			m_debDrawEnable_;
		// �e�f�o�b�O���j���[���̃f�[�^
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
		
		// �A�b�v�f�[�g
		int		debugAppUpdate();
	
		// printfDx �ŕ\�������ȈՉ�ʏo�͗������N���A����
		void	debugDxPrintfLogClear();

	public:
		// �R���X�g���N�^������public�ɂ��Ă��܂��ƁAAppParameter  container; �ŃC���X�^���X����Ă��܂�
		// �u���̃N���X�̃C���X�^���X��1������������Ȃ����Ƃ�ۏ؂��邱�Ƃ��ł���v
		// �ƌ����̂ɔ�����̂�private�ɂ���K�v������B
		DebugModeOperat() {					// �O���ł̃C���X�^���X�쐬�͋֎~
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

	/* @brief �A�N�Z�X�C���^�[�t�F�[�X
	*/
	inline DebugModeOperat* getDebugOperatPtr(void)
	{
		return Singleton<DebugModeOperat>::getSingletonPtr();
	}
}










/* End dxLibDebug.h */



