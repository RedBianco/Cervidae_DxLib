#pragma once


//=================================================================================//
//  dxLibInit.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/28.
//=================================================================================//


// DX���C�u����������������Ă��邩
bool	dxInit_IsDxLibInit( void );

// �E�C���h�E���[�h�ŋN�����邩
bool	dxInit_CheckWindowModePlay( void );

// �Ꮘ�����׃��[�h�ŋN�����邩
bool	dxInit_CheckLowSpecModePlay( void );

// �Ꮘ�����׃��[�h���ǂ�����XAudio���g�p���邩�ǂ����̐ݒ��ύX����
bool	dxInit_SpecModeSetEnableXAudioFlag( const int setFlag );

// ���C���E�C���h�E����A�N�e�B�u��Ԃł����������s���邩�ǂ���
int		dxInit_SetAlwaysActiveRunEnable( const int setFlag );

// �E�C���h�E���[�h�̎��ɃE�C���h�E�̃T�C�Y�����R�ɕύX�o����悤�ɂ��邩�ǂ�����ݒ肷��
int     dxInit_WinSizeChangeSetEnable( const bool  bEnable = 0);

// ���C���E�C���h�E����A�N�e�B�u��Ԏ��̏����̎��s�ݒ�
bool    dxInit_SetWindowAlwaysRunEnable( const int bEnable = 0);

// DX���C�u�������g�p�����\�t�g�̓�d�N�����\�ɂ��邩�ǂ����̐ݒ���s��( TRUE:�\�ɂ��� FALSE:�s�\�ɂ���( �f�t�H���g ) )
bool	dxInit_SetDoubleStartValidEnable( const int bEnable = 0 );







/* End dxLibInit.h */