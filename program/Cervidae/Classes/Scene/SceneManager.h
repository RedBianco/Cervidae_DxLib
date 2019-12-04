#pragma once
#if 0
//===================================================================================
//  SceneManager.h
//  Cervidae
//
//  Created by kashima akihiro on 2019/07/08.
//===================================================================================


/**
 *	@class	V[ÇłNX
 */
namespace App
{
	class SceneManager : public Task
	{
	public:
		SceneManager();
		~SceneManager();

	public:

		// Ö}N
		typedef int	(*appProcessFunc)(void);

		appProcessFunc	p_funcExec;

	public:

		int		updateProcess();

		bool	setupProcessFunc(appProcessFunc  p_Func);

	};
}
#endif
/* End SceneManager.h */
