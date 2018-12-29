#pragma once

//===================================================================================
//  UtilityMoveLine.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/13.
//===================================================================================

//=================================================================================//
//	計算用のマクロ
//=================================================================================//
//	スピードモード
typedef int  SML_ACC;
static const SML_ACC		SML_ACC_NORMAL = 0x01;		//*! @var	等速移動
static const SML_ACC		SML_ACC_REDUCE = 0x02;		//*! @var	減速移動
static const SML_ACC		SML_ACC_ACCELE = 0x04;		//*! @var	加速移動
static const SML_ACC		SML_ACC_AC_REDUCE = 0x08;	//*! @var	加速 -> 減速移動
static const SML_ACC		SML_ACC_RE_ACCELE = 0x10;	//*! @var	減速 -> 加速移動


class SML_Data
{
	SML_Data();

public:




};








/* End UtilityMoveLine.h */

