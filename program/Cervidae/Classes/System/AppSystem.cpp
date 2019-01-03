
#include "DxLib.h"
#include "../Common/CervidaeLib/CLDefine.h"
#include "../Common/CommonList.h"
#include "../Libs/DxLib/Initialize/dxLibInit.h"
#include "../Libs/DxLib/Initialize/dxLibSetup.h"
#include "../Libs/Effekseer/appEffekseer.h"
#include "AppSystem.h"
#include "../Libs/DxLib/dxLibDefine.h"

//======================================================================//
//  AppSystem.cpp
//  Created by on 2018/11/06.
//======================================================================//


AppSystem::AppSystem() :
		m_LowSpecMode( false ),
		m_IsExitApp( false ),
		// �t���[�����[�g�v���p�̕ϐ��̏�����
		m_BackDispFrameTime( DxLib::GetNowHiPerformanceCount() ),
		m_FrameCounter( 0 ),
		m_DispFrameCount( 0 )
{
#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))
	m_EfkData.clear();
#endif
}
AppSystem::~AppSystem()
{}

void	AppSystem::appSystemClean()
{

}

// ( true : ����ɏ�������������   false : �G���[���������� )
bool	AppSystem::appSystemMain()
{
	
	if( !appSystemInitialize() )
	{
		return false;
	}

	// FrameUpdate
	if( !appSystemUpdate() )
	{
		return false;
	}


	appSystemTerminate();

	return true;
}

bool	AppSystem::appSystemStartSetup()
{
	auto result = false;

	// DxLib_Init�����O����
	result = dxLib_InitBeforeSetup();
	if( result ){
	}
	result = dxInit_CheckWindowModePlay();
	if( result ){
	}
	result = dxInit_CheckLowSpecModePlay();
	if( result ) {
		setLowSpecMode( TRUE );
	}

	result = appSystemDxBeforeProcess();
	if( result ) {
	}

	int success = DxLib_Init();
	if( success == -1 ) 
	{
		return false;
	}
	DEBUG_PRINT("[AppSystem] DxLib_Init() CLEAR\n");

	result = dxLib_InitAfterSetup();
	if( result ){
		// DxLib_Init������̏���
		result = appSystemDxAfterProcess();
		if( result ) {
		}
	}

	return true;
}

// Application�N�����̏���������
int		AppSystem::appSystemInitialize()
{
	auto isInitDone = appSystemStartSetup();
	if( !isInitDone ){ return false; }
	// DxLib�O�A�㏈�����S�ďI�����
	// Lua File Loading


	// ����������
	return true;
}
// Application�I������
void	AppSystem::appSystemTerminate()
{




	// �c�w���C�u�����̏I������
	DxLib::DxLib_End();
}

// Application���t���[������
bool	AppSystem::appSystemUpdate()
{
	LONGLONG	n_NowTime;

	DxLib::SetDrawScreen( DX_SCREEN_BACK );

	while( DxLib::ProcessMessage() == 0 )
	{
		{
			if( DxLib::CheckHitKey( KEY_INPUT_ESCAPE ) || isExitApp() )
			{
				if( !isExitApp() ){ setExitAppFlag( TRUE ); }
				break;
			}
		}

#ifdef PROJECT_DEBUG
#endif

		if( isExitApp() ) {
			break;	// �A�v���I��
		}

		// �e�`����X�V
		appSystemRenderUpdate();

		// ����ʂ̓��e��\��ʂɔ��f������
		// ScreenFlip�֐��͐�������������Ă��邽�߁AFPS�������I�Ƀf�B�X�v���C�̃��t���b�V�����[�g�ȉ��ɂȂ�
		if( DxLib::ScreenFlip() != 0 )
		{
		}

		// ���݂̎��Ԃ��擾
		n_NowTime = DxLib::GetNowHiPerformanceCount();

		// �t���[�����[�g�v���p�̃J�E���^���P����
		m_FrameCounter ++;
		// �O��t���[�����[�g���X�V���Ă���P�b�o�߂�����\���p�t���[���J�E���g���X�V����
		if ( ( n_NowTime - m_BackDispFrameTime > (1000000)) )
		{
			// �\���p�t���[���J�E���g���X�V
			m_DispFrameCount = m_FrameCounter;
			// �v���p�t���[���J�E���^��������
			m_FrameCounter = 0;
			// �\���p�t���[���J�E���g���X�V�������Ԃ��X�V
			m_BackDispFrameTime = n_NowTime;
		}

		// ��ʃN���A
		DxLib::ClearDrawScreen();
	}


	return true;
}

void	AppSystem::appSystemRenderUpdate()
{

	// �t���[�����[�g
	dxCommon_FramerateDisp( getDispFrameCount() );
}


bool	AppSystem::appSystemDxBeforeProcess()
{
	return true;
}
bool	AppSystem::appSystemDxAfterProcess()
{
	#if( defined( MIDDLEWARE_EFFEKSEER_USE_ENABLE ))
	//------------------------------------------------------
	// Effekseer�֌W����������
	// �^�C�~���O��DxLib_Init���I�����DxLib�֌W�������㏈�����I�������
	App::EffekseerLib::libSystemInit();
	#endif

	DEBUG_PRINT("[AppSystem] appSystemDxAfterProcess() CLEAR\n");

	return true;
}
