#pragma once


//=================================================================================//
//  UtilityRenderObject.h
//  Cervidae
//
//  Created by kashima akihiro on 2019.11.22
//=================================================================================//

//=================================================================================//
//	�ėp�N���X
//=================================================================================//

namespace Utility
{
	struct ObjectSize
	{
		int		m_RenderW;
		int		m_RenderH;
	};

	struct ObjectPoint
	{
		int		m_RenderX;
		int		m_RenderY;
		int		m_RenderZ;
	};

	struct ObjectScale
	{
		int		m_RenderScaleX;
		int		m_RenderScaleY;
		int		m_RenderScaleZ;
	};

	struct ObjectBase
	{
		ObjectSize		m_ObjSize;
		ObjectPoint		m_ObjPoint;
		ObjectScale		m_ObjScale;
		int				m_ObjAlpha;
		int				m_PriorityIndexZ;
	};
}

class RenderManager
{
	// ���W�A�T�C�Y���ƕ`�惁�\�b�h��o�^����

	int		(*renderFunc)();
};

/* End UtilityRenderObject.h */


