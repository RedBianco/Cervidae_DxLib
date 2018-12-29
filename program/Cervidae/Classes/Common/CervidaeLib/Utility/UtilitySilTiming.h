#pragma once


/********************************************************************************/
/*
	struct
*/
/********************************************************************************/
//==============================================================================//
/*
	�������Ԍv�Z�p�����[�^
*/
//==============================================================================//
typedef struct TIMING
{
	float	fSec;

	void	setInit()
	{
		fSec	= 0.f;
	}
	void	setSecond( const float set )
	{	// �b���Ŏ��Ԃ�ݒ肷��
		fSec = set;
	}
	void	calc( const float fps )
	{	// �v������
		if( fSec > 0.0f )
		{
			fSec -= ( 1.0f / fps );
		}
	}
	bool	check( void ) const
	{	// ���Ԃ��o�߂������𔻒f����
		return ( fSec <= 0.0f );
	}
	void	reset( void )
	{
		fSec = -1.0f;
	}
} * LPTIMING;



/* End UtilityForSilTiming.h */
