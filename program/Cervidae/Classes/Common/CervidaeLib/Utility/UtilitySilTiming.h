#pragma once


/********************************************************************************/
/*
	struct
*/
/********************************************************************************/
//==============================================================================//
/*
	処理時間計算パラメータ
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
	{	// 秒数で時間を設定する
		fSec = set;
	}
	void	calc( const float fps )
	{	// 計測する
		if( fSec > 0.0f )
		{
			fSec -= ( 1.0f / fps );
		}
	}
	bool	check( void ) const
	{	// 時間が経過したかを判断する
		return ( fSec <= 0.0f );
	}
	void	reset( void )
	{
		fSec = -1.0f;
	}
} * LPTIMING;



/* End UtilityForSilTiming.h */
