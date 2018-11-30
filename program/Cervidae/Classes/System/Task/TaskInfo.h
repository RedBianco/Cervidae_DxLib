#pragma once

//=================================================================================//
//  TaskInfo.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/06.
//=================================================================================//


// タスクの処理用情報
class CTaskBaseParam
{
public:
	CTaskBaseParam();
	virtual ~CTaskBaseParam();

public:
	
	int		m_StepPriority;						// 状態推移処理の実行優先順位
	int		m_RenderPriority;					// 描画処理の実行優先順位

public:
	// 状態推移処理を行う関数へのポインタ
//	bool(*Step)(			CTaskInfo * pTInfo, float setStepTime );
	// 描画処理を行う関数へのポインタ
//	void(*Render)(		CTaskInfo * pTInfo );
	// 後始末処理を行う関数へのポインタ
//	void(*Terminate)(	CTaskInfo * pTInfo );

};

// タスクの情報
class CTaskInfo
{
public:

};

// タスクシステム情報
class CTaskSystem
{
public:

};



