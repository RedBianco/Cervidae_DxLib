
#include "DxLib.h"
#include "../Common/CervidaeLib/CLDefine.h"
#include "../Common/appCommonParam.h"
#include "../Common/appErrorCode.h"
#include "../Common/appProcessCode.h"
#include "../System/Task/TaskCore.h"
#include "appScene_Base.h"
#include "appScene_Start.h"

//===================================================================================
//  appScene_Start.cpp
//  Cervidae
//
//  Created by kashima akihiro on 2019/11/29.
//===================================================================================


// �R���X�g���N�^
App::Scene_Start::Scene_Start()
{
}
// �f�X�g���N�^
App::Scene_Start::~Scene_Start()
{
}


void App::Scene_Start::setBaseInfo()
{
	m_ssTaskBaseInfo.StepPriority = 8;   // ��Ԑ��ڏ����̎��s�D�揇��
	m_ssTaskBaseInfo.RenderPriority = 8; // �`�揈���̎��s�D�揇��
	//m_ssTaskBaseInfo.Step = Task_Step;
	//m_ssTaskBaseInfo.Render = Task_Render;
	//m_ssTaskBaseInfo.Terminate = Task_Terminate;
}


bool App::Scene_Start::Task_Step( STaskInfo* TInfo, float StepTime )
{
	Scene_Start* TTData = (Scene_Start*)TInfo->Data;

	DEBUG_PRINT("[Task] Scene_Start::Task_Step()\n");

	switch ( TTData->m_State )
	{
	case 0:
		break;
	case 1:
		break;
	default:
		break;
	}

	// ����I��
	return true;
}
void App::Scene_Start::Task_Render( STaskInfo* TInfo )
{
}
void App::Scene_Start::Task_Terminate( STaskInfo* TInfo )
{
}


