
#pragma once

#include "CLDefine.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#if( defined( SYSTEM_DEBUG ))
	#define SYSTEM_DBG_ASSERT
#endif


#if( defined( SYSTEM_DEBUG ))
	#define ___SysAssert_PrintDx(...) \
			DEBUG_PRINT( "\n\n" );                                                       \
			DEBUG_PRINT( "<======================================================>\n" ); \
			DEBUG_PRINT( "SysAssertion Failed !!!\n" );                                  \
			DEBUG_PRINT( "File:%s\n", __FILE__ );                                        \
			DEBUG_PRINT( "Line:%d\n", __LINE__ );                                        \
			DEBUG_PRINT( "Func:%s\n", __func__ );                                        \
			DEBUG_PRINT( "Info:%s\n", __VA_ARGS__ );                                     \
			DEBUG_PRINT( "\n" );                                                         \
			DEBUG_PRINT( "<======================================================>\n" );

	#define ___LibAssert_PrintDx(...) \
			DEBUG_PRINT( "\n\n" );                                                       \
			DEBUG_PRINT( "<======================================================>\n" ); \
			DEBUG_PRINT( "LibAssertion Failed !!!\n" );                                  \
			DEBUG_PRINT( "File:%s\n", __FILE__ );                                        \
			DEBUG_PRINT( "Line:%d\n", __LINE__ );                                        \
			DEBUG_PRINT( "Func:%s\n", __func__ );                                        \
			DEBUG_PRINT( "Info:%s\n", __VA_ARGS__ );                                     \
			DEBUG_PRINT( "\n" );                                                         \
			DEBUG_PRINT( "<======================================================>\n" ); 
#else
	#define ___SysAssert_Print(...) \
			printf( "\n\n" );                                                       \
			printf( "<======================================================>\n" ); \
			printf( "SysAssertion Failed !!!\n" );                                  \
			printf( "File:%s\n", __FILE__ );                                        \
			printf( "Line:%d\n", __LINE__ );                                        \
			printf( "Func:%s\n", __func__ );                                        \
			printf( "Info:%s\n", __VA_ARGS__ );                                     \
			printf( "\n" );                                                         \
			printf( "<======================================================>\n" ); 
	#define ___LibAssert_Print(...) \
			printf( "\n\n" );                                                       \
			printf( "<======================================================>\n" ); \
			printf( "LibAssertion Failed !!!\n" );                                  \
			printf( "File:%s\n", __FILE__ );                                        \
			printf( "Line:%d\n", __LINE__ );                                        \
			printf( "Func:%s\n", __func__ );                                        \
			printf( "Info:%s\n", __VA_ARGS__ );                                     \
			printf( "\n" );                                                         \
			printf( "<======================================================>\n" ); 
#endif


//====================================================================================//
//  Assertマクロ
//
//  (形式)
//    sysAssert( 条件式, メッセージ )
//
//  (説明)
//    条件式が偽の場合にメッセージを表示しプログラムを停止します。
//
//====================================================================================//

#ifdef SYSTEM_DBG_ASSERT
	#define _LIBASSERT(a,...)                                                         \
			if( !(a) ){                                                                 \
				printf( "\n" );                                                         \
				printf( "<======================================================>\n" ); \
				printf( "Assertion Failed !!!\n" );                                     \
				printf( "File:%s Line:%d\n", __FILE__, __LINE__ );                      \
				printf( __VA_ARGS__ );                                                  \
				printf( "\n" );                                                         \
				printf( "<======================================================>\n" ); \
				while(1);                                                               \
			}
#else
	#define _LIBASSERT( a, ... ) ((void)0)
#endif

#ifdef SYSTEM_DBG_ASSERT
	#ifdef __PROJECT_DEBUG__
		#define _PRINT_ASSERT(a,...)                                  \
				if( !(a) ){                                           \
					___SysAssert_Print( __VA_ARGS__ )                 \
					while(1);                                         \
				}
	#else
		#define _PRINT_ASSERT(a,...)                                  \
				if( !(a) ){                                           \
					___SysAssert_Print( __VA_ARGS__ )                 \
					assert(0);                                        \
				}
	#endif
#else
	#define _PRINT_ASSERT( a, ... ) ((void)0)
#endif



/* End CLAssert.h */