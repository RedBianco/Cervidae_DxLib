#pragma once


//=================================================================================//
//  dxLibSetup.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/28.
//=================================================================================//


// DX���C�u�����̊�{�J�n�ݒ菈�� ���S�� DxLib_Init �̑O�ɌĂԕK�v�̏����Q
bool		dxLib_InitBeforeSetup( void);

// DX���C�u�����̊�{�J�n�ݒ菈��(���S�� DxLib_Init ���Ă΂ꂽ��ɌĂԕK�v�̂���P����菈���Q)
bool		dxLib_InitAfterSetup( void);

// DX���C�u�����֌W�̖��t���[������
void		dxLib_SystemUpdate( void);


void		dxLib_StartSetup( void);

