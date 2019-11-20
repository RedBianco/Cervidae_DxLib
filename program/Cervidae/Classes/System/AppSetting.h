#pragma once

//=================================================================================//
//  AppSetting.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/29.
//=================================================================================//7777


class AppParameter : public Singleton<AppParameter>
{
	// AppParameter�̃C���X�^���X�𐶐����鎞�ɁA�R���X�g���N�^���ĂׂȂ�������friend�w��
	// �V���O���g���̃e���v���[�g�����Ɏ��g���w�肵�����̂����ɐ���������
	friend class Singleton<AppParameter>;		// Singleton �ł̃C���X�^���X�쐬�͋���

private:
	std::string		m_ExeName;				//! Application Exe Name
	std::string		m_ExeVersion;			//! Application Version
	std::string		m_ServiceNeme;			//! Application Service ID
	unsigned int	m_RatingAgeLevel;		//! Application Parental Lock
	std::string		m_ServiceCopyright;		//! Application Copyright

	bool			m_isSetting;

public:

	bool	setApplicationInfo();

public:

	// �R���X�g���N�^������public�ɂ��Ă��܂��ƁAAppParameter  container; �ŃC���X�^���X����Ă��܂�
	// �u���̃N���X�̃C���X�^���X��1������������Ȃ����Ƃ�ۏ؂��邱�Ƃ��ł���v
	// �ƌ����̂ɔ�����̂�private�ɂ���K�v������B
	AppParameter() {					// �O���ł̃C���X�^���X�쐬�͋֎~
		m_RatingAgeLevel = 0;
		m_ExeName.clear();
		m_ExeVersion.clear();
		m_ServiceNeme.clear();
		m_ServiceCopyright.clear();

		m_isSetting = false;
	};
	//	virtual ~AppParameter();

};

/* @brief �A�N�Z�X�C���^�[�t�F�[�X
*/
inline AppParameter* getAppContainerPtr(void)
{
	return Singleton<AppParameter>::getSingletonPtr();
}


typedef struct	GAME_PARAM_SETTING
{
	struct
	{	// screen info
		unsigned int		width;
		unsigned int		height;
	} screen;
	struct
	{	// file info
		unsigned int		maxRequest;
	} file;
	struct
	{	// multimedia info
		int					maxChannel;
		int					maxSoundStream;
		int					SampleFreq;
	} multimedia;
	struct
	{	// memory info
		unsigned int		size;
		unsigned int		block;
	} memory;

} *LPGAME_PARAM_SETTING;


/* End AppSetting.h */



