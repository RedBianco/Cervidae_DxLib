

#include "DxLib.h"
#include "../../appCommonParam.h"
#include "UtilityMath.h"

//===================================================================================
//  UtilityMath.cpp
//
//  
//===================================================================================

//-----------------------------------------------------------------------------------
// �֗��֐��Q
//-----------------------------------------------------------------------------------
namespace UtilityMath
{
	// ���������_�^�̕ϐ��̒l���w��̒l�ɋ߂Â��鏈�����s��
	//     �߂�l : �ϐ��̒l���w��̒l�ɒB�������ǂ���
	//              ( true : �w��̒l�ɒB����  false : �w��̒l�ɒB���Ă��Ȃ� )
	const bool	ParamChangeFloat(
		float*	Param,			// ����Ώۂ̕ϐ��̃A�h���X
		float	TargetParam,	// �ڕW�Ƃ���l
		float	StepTime,		// ���ڂ����鎞��
		float	Speed			// �l�̕ω����x
	)
	{
		// �ϐ��̒l���ڕW�Ƃ���l��菬�������ǂ����ŏ����𕪊�
		if (*Param < TargetParam)
		{
			// �ڕW�̒l��菬�����ꍇ�͕ϐ��̒l�ɕω��l�����Z����
			*Param += Speed * StepTime;

			// �ڕW�̒l�ɒB���Ă��邩�ǂ����̔���
			if (*Param >= TargetParam)
			{
				// �B���Ă�����ϐ��ɖڕW�̒l�������� true ��Ԃ�
				*Param = TargetParam;
				return true;
			}
		}
		else{
			// �ڕW�̒l��菬�����ꍇ�͕ϐ��̒l����ω��l�����Z����
			*Param -= Speed * StepTime;

			// �ڕW�̒l�ɒB���Ă��邩�ǂ����̔���
			if (*Param <= TargetParam)
			{
				// �B���Ă�����ϐ��ɖڕW�̒l�������� true ��Ԃ�
				*Param = TargetParam;
				return true;
			}
		}

		// �����ɗ�����܂��ڕW�̒l�ɒB���Ă��Ȃ��Ƃ������ƂȂ̂� false ��Ԃ�
		return false;
	}

	// ���������_�^�̕ϐ��ɑ������Ă���p�x���w��̊p�x�ɋ߂Â��鏈�����s��
	// ( �ڕW�Ƃ���p�x�ƕϐ��ɑ������Ă���p�x�̍��� 2.0f * �� �ȓ��ł���K�v������ )
	// �߂�l : �ϐ��̊p�x���w��̊p�x�ɒB�������ǂ���
	//		( true : �w��̊p�x�ɒB����  false : �w��̊p�x�ɒB���Ă��Ȃ� )
	const bool ParamChangeAngle(
		float*	Param,			// ����Ώۂ̕ϐ��̃A�h���X
		float	TargetParam,	// �ڕW�Ƃ���p�x
		float	StepTime,		// ���ڂ����鎞��
		float	Speed			// �p�x�̕ω����x
	)
	{
		float RelateAngle;

		// �ڕW�Ƃ���p�x�ƕϐ��̊p�x�Ƃ̍����Z�o
		RelateAngle = TargetParam - *Param;

		// �p�x�̍����P�W�O�x�ȏ�̏ꍇ�͊p�x�̍������߂�������t�]������
		if ( RelateAngle < -DX_PI_F )
		{
			RelateAngle += DX_TWO_PI_F;
		}
		else if ( RelateAngle > DX_PI_F )
		{
			RelateAngle -= DX_TWO_PI_F;
		}

		// �p�x�̍����O�ɋ߂Â���
		if ( ParamChangeFloat(&RelateAngle, 0.0f, StepTime, Speed) )
		{
			// �p�x�̍����O�ɂȂ�����ڕW�Ƃ���p�x�ɂȂ�Ƃ������ƂȂ̂�
			// �ϐ��ɖڕW�̊p�x�������� true ��Ԃ�
			*Param = TargetParam;
			return true;
		}

		// �ڕW�̊p�x����p�x�̍������������̂�V�����p�x�Ƃ���
		*Param = TargetParam - RelateAngle;

		// �܂��ڕW�̊p�x�ɒB���Ă��Ȃ��̂� false ��Ԃ�
		return false;
	}

	// �w��͈̔͂��烉���_���Ō��肵���l���擾����( ���������_�l )
	// �߂�l : �����_���Ō��肵���l
	const float GetRandomFloat(
		// �ő�l // �ŏ��l
		float MaxF, float MinF )
	{
		return GetRand(10000) * (MaxF - MinF) / 10000.0f + MinF;
	}

	// �w��͈̔͂��烉���_���Ō��肵���l���擾����( �����l )
	// �߂�l : �����_���Ō��肵���l
	const int	GetRandomInt(
		// �ő�l // �ŏ��l
		int MaxI, int MinI )
	{
		return GetRand(MaxI - MinI) + MinI;
	}

}/** namespace UtilityMath */











