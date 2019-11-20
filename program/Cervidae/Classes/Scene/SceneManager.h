#pragma once

//===================================================================================
//  SceneManager.h
//  Cervidae
//
//  Created by kashima akihiro on 2019/07/08.
//===================================================================================


/**
 *	@class	�V�[���Ǘ����N���X
 */
namespace App
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

	public:

		// �����֐��}�N��
		typedef int	(*appProcessFunc)( void );

		appProcessFunc	p_funcExec;

	public:

		int		updateProcess();

		bool	setupProcessFunc( appProcessFunc  p_Func );

	};
}






/* End SceneManager.h */







