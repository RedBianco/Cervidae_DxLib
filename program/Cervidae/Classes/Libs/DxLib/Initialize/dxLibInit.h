#pragma once


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



/* End dxLibInit.h */