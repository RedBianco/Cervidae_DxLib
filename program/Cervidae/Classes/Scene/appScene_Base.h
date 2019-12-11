#pragma once

//===================================================================================
//  appScene_Base.h
//  Cervidae
//
//  Created by kashima akihiro on 2019/11/29.
//===================================================================================

namespace App
{
	class SceneBase
	{
	public:
		// �e�V�[����ʂ̏�Ԑ��ڏ������s��
		//     �߂�l : ����������ɏI���������ǂ���(true:����ɏI������  false:�G���[����������)
		virtual bool Task_Step(
			STaskInfo* TInfo,		// �^�X�N�V�X�e�����\���̂̃A�h���X
			float StepTime			// ���ڂ����鎞��( �P�ʁF�b )
		) = 0;
		// �e�V�[����ʂ̕`�揈�����s��
		virtual void Task_Render(
			STaskInfo* TInfo		// �^�X�N�V�X�e�����\���̂̃A�h���X
		) = 0;
		// �e�V�[����ʂ̌�n���������s��
		virtual void Task_Terminate(
			STaskInfo* TInfo		// �^�X�N�V�X�e�����\���̂̃A�h���X
		) = 0;

		// �^�X�N�̓o�^����

	};
}

/* End appScene_Base.h */




