#pragma once


//===================================================================//
//	dxLibSoundData
//
//  Created by kashima akihiro on 2019.08.03
//===================================================================//

/**
 *	�T�E���h�Đ��Ǘ��p�f�[�^
 */
namespace App
{
	class SoundDataContainer
	{
	public:
		SoundDataContainer() {};
		~SoundDataContainer() {};

	public:

		std::string		dxSoundName;	// �t�@�C���l�[��
		int				dxSoundHandle;	// �t�@�C�����[�h�n���h��
		int				dxSoundExist;	// �T�E���h�t�@�C�����݃`�F�b�N( -1:���o�^, 0:�o�^�ς� )

	public:

		int		getPlayHandle() { return dxSoundHandle; }
		int		isSoundFile( char * fileName );
	};
}







/* End dxLibSoundData.h */


