

#include "DxLib.h"
#include "../../appCommonParam.h"
#include "UtilityMath.h"

//===================================================================================
//  UtilityMath.cpp
//
//  
//===================================================================================

//-----------------------------------------------------------------------------------
// 便利関数群
//-----------------------------------------------------------------------------------
namespace UtilityMath
{
	// 浮動小数点型の変数の値を指定の値に近づける処理を行う
	//     戻り値 : 変数の値が指定の値に達したかどうか
	//              ( true : 指定の値に達した  false : 指定の値に達していない )
	const bool	ParamChangeFloat(
		float*	Param,			// 操作対象の変数のアドレス
		float	TargetParam,	// 目標とする値
		float	StepTime,		// 推移させる時間
		float	Speed			// 値の変化速度
	)
	{
		// 変数の値が目標とする値より小さいかどうかで処理を分岐
		if (*Param < TargetParam)
		{
			// 目標の値より小さい場合は変数の値に変化値を加算する
			*Param += Speed * StepTime;

			// 目標の値に達しているかどうかの判定
			if (*Param >= TargetParam)
			{
				// 達していたら変数に目標の値を代入して true を返す
				*Param = TargetParam;
				return true;
			}
		}
		else{
			// 目標の値より小さい場合は変数の値から変化値を減算する
			*Param -= Speed * StepTime;

			// 目標の値に達しているかどうかの判定
			if (*Param <= TargetParam)
			{
				// 達していたら変数に目標の値を代入して true を返す
				*Param = TargetParam;
				return true;
			}
		}

		// ここに来たらまだ目標の値に達していないということなので false を返す
		return false;
	}

	// 浮動小数点型の変数に代入されている角度を指定の角度に近づける処理を行う
	// ( 目標とする角度と変数に代入されている角度の差が 2.0f * π 以内である必要がある )
	// 戻り値 : 変数の角度が指定の角度に達したかどうか
	//		( true : 指定の角度に達した  false : 指定の角度に達していない )
	const bool ParamChangeAngle(
		float*	Param,			// 操作対象の変数のアドレス
		float	TargetParam,	// 目標とする角度
		float	StepTime,		// 推移させる時間
		float	Speed			// 角度の変化速度
	)
	{
		float RelateAngle;

		// 目標とする角度と変数の角度との差を算出
		RelateAngle = TargetParam - *Param;

		// 角度の差が１８０度以上の場合は角度の差を求める方向を逆転させる
		if ( RelateAngle < -DX_PI_F )
		{
			RelateAngle += DX_TWO_PI_F;
		}
		else if ( RelateAngle > DX_PI_F )
		{
			RelateAngle -= DX_TWO_PI_F;
		}

		// 角度の差を０に近づける
		if ( ParamChangeFloat(&RelateAngle, 0.0f, StepTime, Speed) )
		{
			// 角度の差が０になったら目標とする角度になるということなので
			// 変数に目標の角度を代入して true を返す
			*Param = TargetParam;
			return true;
		}

		// 目標の角度から角度の差を引いたものを新しい角度とする
		*Param = TargetParam - RelateAngle;

		// まだ目標の角度に達していないので false を返す
		return false;
	}

	// 指定の範囲からランダムで決定した値を取得する( 浮動小数点値 )
	// 戻り値 : ランダムで決定した値
	const float GetRandomFloat(
		// 最大値 // 最小値
		float MaxF, float MinF )
	{
		return GetRand(10000) * (MaxF - MinF) / 10000.0f + MinF;
	}

	// 指定の範囲からランダムで決定した値を取得する( 整数値 )
	// 戻り値 : ランダムで決定した値
	const int	GetRandomInt(
		// 最大値 // 最小値
		int MaxI, int MinI )
	{
		return GetRand(MaxI - MinI) + MinI;
	}

}/** namespace UtilityMath */











