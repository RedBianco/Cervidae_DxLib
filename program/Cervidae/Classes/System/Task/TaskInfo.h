#pragma once

//=================================================================================//
//  TaskInfo.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/11/06.
//=================================================================================//


// �^�X�N�̏����p���
class CTaskBaseParam
{
public:
	CTaskBaseParam();
	virtual ~CTaskBaseParam();

public:
	
	int		m_StepPriority;						// ��Ԑ��ڏ����̎��s�D�揇��
	int		m_RenderPriority;					// �`�揈���̎��s�D�揇��

public:
	// ��Ԑ��ڏ������s���֐��ւ̃|�C���^
//	bool(*Step)(			CTaskInfo * pTInfo, float setStepTime );
	// �`�揈�����s���֐��ւ̃|�C���^
//	void(*Render)(		CTaskInfo * pTInfo );
	// ��n���������s���֐��ւ̃|�C���^
//	void(*Terminate)(	CTaskInfo * pTInfo );

};

// �^�X�N�̏��
class CTaskInfo
{
public:

};

// �^�X�N�V�X�e�����
class CTaskSystem
{
public:

};



