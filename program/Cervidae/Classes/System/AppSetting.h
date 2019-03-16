#pragma once

//=================================================================================//
//  AppSetting.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/29.
//=================================================================================//7777

#include "../Common/CervidaeLib/Template/tSingleton.h"

class AppParameter : public Singleton<AppParameter>
{
	// AppParameterのインスタンスを生成する時に、コンストラクタが呼べなかった為friend指定
	// シングルトンのテンプレート引数に自身を指定したものだけに生成を許す
	friend class Singleton<AppParameter>;		// Singleton でのインスタンス作成は許可

private:
	std::string		m_ExeName;				//! Application Exe Name
	std::string		m_ExeVersion;			//! Application Version
	std::string		m_ServiceNeme;			//! Application Service ID
	unsigned int	m_RatingAgeLevel;		//! Application Parental Lock
	std::string		m_ServiceCopyright;		//! Application Copyright

public:

	bool	settingBaseInfo();

	// コンストラクタ部分をpublicにしてしまうと、AppParameter  container; でインスタンスつくれてしまう
	// 「そのクラスのインスタンスが1つしか生成されないことを保証することができる」
	// と言うのに反するのでprivateにする必要がある。
	AppParameter() {					// 外部でのインスタンス作成は禁止
		m_RatingAgeLevel = 0;
		m_ExeName.clear();
		m_ExeVersion.clear();
		m_ServiceNeme.clear();
		m_ServiceCopyright.clear();
	};
//	virtual ~AppParameter();

};

/* @brief アクセスインターフェース
*/
inline AppParameter* getAppContainerPtr(void)
{
	return Singleton<AppParameter>::getSingletonPtr();
}


/* End AppSetting.h */








