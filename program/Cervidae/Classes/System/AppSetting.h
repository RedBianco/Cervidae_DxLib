#pragma once

//=================================================================================//
//  AppSetting.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/29.
//=================================================================================//


class AppParameter// : Singleton<AppParameter>
{
//	friend class Singleton<AppParameter>;

private:
	std::string				m_ExeName;				//! Application Exe Name
	std::string				m_ExeVersion;			//! Application Version
	std::string				m_ServiceNeme;			//! Application Service ID
	unsigned int			m_RatingAgeLevel;		//! Application Parental Lock
	std::string				m_ServiceCopyright;		//! Application Copyright

public:

	void		settingAppParameter();


};




/* End AppSetting.h */








