#pragma once

//===================================================================================
//  SceneManager.h
//  Cervidae
//
//  Created by kashima akihiro on 2019/07/08.
//===================================================================================


/**
 *	@class	シーン管理元クラス
 */
namespace App
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

	public:

		// 処理関数マクロ
		typedef int	(*appProcessFunc)( void );

		appProcessFunc	p_funcExec;

	public:

		int		updateProcess();

		bool	setupProcessFunc( appProcessFunc  p_Func );

	};
}






/* End SceneManager.h */







