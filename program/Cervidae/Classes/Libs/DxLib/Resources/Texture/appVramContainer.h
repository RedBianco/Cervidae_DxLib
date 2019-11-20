#pragma once

///////////////////////////////////////////////////////////////////////////
//
//
//	2019.
///////////////////////////////////////////////////////////////////////////

using namespace AppLib::Resources;

/**
 *	@class	�t�@�C�����Ǘ��f�[�^�R���e�i�N���X
 *			����{�͐e�N���X���ɒ�`���Ďg�p����A�p���g�p����
 */
namespace DxLib
{
	class VramFileContainer
	{
	public:
		VramFileContainer(){
			DEBUG_PRINT("APP INIT : VramFileContainer �R���X�g���N�^\n");
		}
		~VramFileContainer(){
			DEBUG_PRINT("APP INIT : VramFileContainer �f�X�g���N�^\n");
		}
		
	public:

		int			vv_VramCount;		// �ǂݍ��݃J�E���g(�� eDEF_VVRAM_BUFFER_FLAG_USED ���Z�b�g����Ă���Ɠo�^���Ďg�p���Ă���)
		int			vv_FileHandle;		// �t�@�C�����[�h�n���h��
		std::string	vv_TextureName;		// �ǂݍ��݃e�N�X�`���l�[��
		char *		vv_ReadBuff;		// �ǂݍ��݃t�@�C���o�b�t�@
		int			vv_VramType;		// VRAM�^�C�v
		int			vv_WIDTH;			// �e�N�X�`���T�C�Y�v
		int			vv_HEIGHT;			// �e�N�X�`���T�C�Y�g

	public:

		void		dataInit();
	};
}



/* End appVramFileContainer.h */

