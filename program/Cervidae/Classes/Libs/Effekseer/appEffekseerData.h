#pragma once

#include <string>

//=================================================================================//
//  appEffekseerData.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/11.
//=================================================================================//

/*
	.efk�t�@�C���f�[�^�Ǘ��p�N���X
	�t�@�C���P�̊Ǘ��f�[�^
*/
class EffekseerFileData
{
public:
	
	EffekseerFileData();
	 ~EffekseerFileData(){}
	
public:
	// �t�@�C���n���h��
	int				m_FileHandle_;
	// �Đ��t�@�C����
	std::string		m_PlayFile;
	
};




/* End appEffekseerData.h */

