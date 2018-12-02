#pragma once

#include <Windows.h>
#include <time.h>	
#include <math.h>	
#include <stdio.h>	
#include <stdlib.h>
#include <malloc.h>
#include <direct.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

//=================================================================================//
//  CommonList.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/07.
//=================================================================================//

// �t�@�C���ǂݍ��݌n
#define  FILE_OPEN( t, fname )					fopen_s( t, fname, "r" )		//	�e�L�X�g�t�@�C�����ǂݍ���
#define  FILE_OPEN_BIN( t, fname )			fopen_s( t, fname, "rb" )		//	�o�C�i���t�@�C���ǂݍ���
#define  FILE_WRITE( t, fname )				fopen_s( t, fname, "w" )		//	�e�L�X�g�t�@�C������������
#define  FILE_WRITE_BIN( t, fname )		fopen_s( t, fname, "wb" )	//	�o�C�i���t�@�C����������

// ���w�v�Z�n
#define  MAX( x, max )								( (x) > (max) ? (x) : (max) )
#define  MIN( x, min )								( (x) < (min) ? (x) : (min) )
#define  CLAMP( x, min, max )					( (x) < (min) ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define  ABS( x )										abs( x )
#define  ATAN2( y, x )								atan2( y, x )
#define  SIGN( x )										( x == 0 ? (x) = 0 : (x) / ABS(x) )
#define  DEG2RAD( x )								( (x) / 180.0f * PAI )
#define  RAD2DEG( x )								( (x) / PAI * 180.0f )

#define  DegToRad( Red )							(((Red) * PAI) / 180.0f)		//	�x�����W�A��
#define  RadToDeg( Red )							(((Red) * 180.0f) / PAI)		//	���W�A�����x	
#define  COMPUTE_CIRCLE( r )				(r * r * 3.14)						//	�~�̖ʐς��v�Z�Br = ���a

//	�~���b�ϊ�
#define  TICK_TIME_MSEC						( 1000000L )
//	���ԕϊ�
#define  CALC_TIME_HOUR( time )			(( time) / 3600)
#define  CALC_TIME_MINUTE( time )		(( time) % 3600 / 60)
#define  CALC_TIME_SECOND( time )		(( time) % 60)

#define  PARAM_BIT_SET( obj, val )			((obj) |= (val))						// �r�b�g�l�̐ݒ�
#define  PARAM_BIT_CLR( obj, val )			((obj) &= ~(val))					// �r�b�g�l�̃N���A
#define  PARAM_BIT_CHK( obj, val )		((obj) & (val))						// �r�b�g�l�̔���
#define  PARAM_BIT_CMP( obj, val )		(((obj) & (val)) == val )			// �r�b�g�l�̔���(��v���邩)

//	�A���C�����g
#define  VALUE_ALIGN( d, align_size )		d __attribute__(( aligned( align_size ) ))

//	�ėp���[�v�v�Z
#define  VALUE_LOOP( value, max )			((value + max) % (max))

//	���������p
#define  UNUSED_VARIABLE( x )				(void)(x)



namespace CommonList
{
//	#define  RESOURCES_LOAD_PATH_LUA					""
//	#define  RESOURCES_LOAD_PATH_2D					""
//	#define  RESOURCES_LOAD_PATH_3D					""
//	#define  RESOURCES_LOAD_PATH_EFFECT			""

	namespace Resources
	{
		enum ENUM_UI_FILE_TYPE
		{
			eUI_FILE_TYPE_SYSTEM		= 0,
			eUI_FILE_TYPE_ETC,
		};
		enum ENUM_EFFECT_FILE_TYPE
		{
			eEFFECT_FILE_TYPE_2D		= 0,
			eEFFECT_FILE_TYPE_3D
		};
	}
	const std::string		RESOURCES_LOAD_PATH_LUA			= "..\\..\\resources\\script\\lua\\";
	const std::string		RESOURCES_LOAD_PATH_ADX2		= "..\\..\\resources\\script\\sound\\";
	const std::string		RESOURCES_LOAD_PATH_2D			= "..\\..\\resources\\asset\\";
	const std::string		RESOURCES_LOAD_PATH_3D			= "..\\..\\resources\\model\\";
	const std::string		RESOURCES_LOAD_PATH_EFFECT	= "..\\..\\resources\\asset\\effect\\";

	namespace TaskEvent
	{
		static const unsigned int			EVT_CREATE		= 0;			// �^�X�N���쐬���ꂽ�u��
		static const unsigned int			EVT_DESTROY	= 1;			// �^�X�N���j�����ꂽ�u��
		static const unsigned int			EVT_RUN			= 2;			// ���s��
		static const unsigned int			EVT_USER			= 3;			// ���[�U�C��

		static const signed int				PRIORITY_HIGHEST					= 0x7FFFFFFF;		// �v���C�I���e�B�F�ō�
		static const signed int				PRIORITY_ABOVE_NORMAL		= 0x3FFFFFFF;		// �v���C�I���e�B�F����
		static const signed int				PRIORITY_NORMAL					= 0x00000000;		// �v���C�I���e�B�F�W��
		static const signed int				PRIORITY_BELOW_NORMAL		= 0xC0000000;		// �v���C�I���e�B�F�Ⴂ
		static const signed int				PRIORITY_LOWEST					= 0x80000000;		// �v���C�I���e�B�F�Œ�

		static const unsigned int			STATE_CODE_ERROR				= 0;			// �G���[
		static const unsigned int			STATE_CODE_FREE					= 1;			// ���g�p
		static const unsigned int			STATE_CODE_SUSPENDED		= 2;			// ��~��
		static const unsigned int			STATE_CODE_RESERVE				= 3;			// �\��
		static const unsigned int			STATE_CODE_RUN						= 4;			// ���s��

		static const unsigned int			EVT_TASK_SINGLE						= 0;			// 
		static const unsigned int			EVT_TASK_DOUBLE					= 1;			// 
		static const unsigned int			EVT_TASK_MULTI						= 2;			// 
		static const unsigned int			EVT_TASK_SUSPEND					= 3;			// 
		static const unsigned int			EVT_TASK_CLEAR						= 4;			// 
		static const unsigned int			EVT_TASK_DELETE					= 5;			// 
	}

	/*! �P�b(s)=1,000�~���b(ms)=1,000,000�}�C�N���b(us)=1,000,000,000�i�m�b(ns)
	*/
	/*! @var static const uint64_t g_unUsecPerFrame
	*/
	static const unsigned __int64			g_unUsecPerFrameCount = static_cast<unsigned __int64>(g_unUsecPerFrameCount);
	/*! @var static const uint64_t g_unUsecPerFrame
	*/
	static const unsigned __int64			g_unUsecPerCountLimit = 99999999;
	/*! @var static const uint64_t g_unUsecPerFrame
	*/
	static const unsigned long long		g_unUsecPerFrame = 16666;
	/*! @var static const float g_fUsecPerFrame
	*/
	static const float				g_fUsecPerFrame = 16666.6f;
	/*! @var static const float g_fInvUsecPerFrame
	*/
	static const float				g_fInvUsecPerFrame = (1.f / g_fUsecPerFrame);
	/*! @var static const float g_fUsecPerCountFrame
	*/
	static const float				g_fUsecPerCountFrame = (1.f / 60.f) * 1000.f * 1000.f;
}




/* End CommonList.h */