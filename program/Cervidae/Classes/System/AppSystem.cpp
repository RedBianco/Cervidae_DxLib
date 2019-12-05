
#include "DxLib.h"
#include "../Common/CervidaeLib/CLDefine.h"
#include "../Common/appCommonParam.h"
#include "../Common/appErrorCode.h"
#include "../Common/appProcessCode.h"
#include "../Libs/DxLib/dxLibDefine.h"
#include "../Libs/DxLib/Debug/dxLibDebug.h"
#include "../Libs/DxLib/Input/dxLibInputConfig.h"
#include "../Libs/DxLib/Input/dxLibKeyPadUtility.h"
#include "../Libs/Effekseer/appEffekseer.h"
#include "../Libs/DxLib/Resources/appResourcesConfig.h"
#include "../Libs/DxLib/Resources/appResources.h"
#include "../Libs/DxLib/Initialize/dxLibInit.h"
#include "../Libs/DxLib/Initialize/dxLibSetup.h"
#include "../Libs/Effekseer/appEffekseerLib.h"
#include "appSystem.h"
#include "appSetting.h"
#include "Task/TaskCore.h"
#include "Task/TaskLib.h"

/*
[NOTE]
�EcreateInstance()->AppSystem::AppSystem()��call��

*/


//======================================================================//
//  AppSystem.cpp
//  Created by on 2018/11/06.
//======================================================================//

#if PROJECT_DEBUG
using SCDebugOperat = Singleton<App::DebugModeOperat>;
#endif
using SCAppParameter = Singleton<AppParameter>;
using SCAppLibKeyPad = Singleton<Lib::AppKeyPadController>;

/**
 *
 */
AppSystem::AppSystem() :
		// �t���[�����[�g�v���p�̕ϐ��̏�����
		m_BackDispFrameTime( DxLib::GetNowHiPerformanceCount() ),
		m_FrameCounter( 0 ),
		m_LowSpecMode( false ),
		m_IsExitApp( false ),
		m_DispFrameCount( 0 ),
		m_LocalStep( eROUTE_INIT )
{
	COMMENT("AppSystem : AppSystem �R���X�g���N�^\n");
}
AppSystem::~AppSystem()
{
	COMMENT("AppSystem : AppSystem �f�X�g���N�^\n");
}


/**
 *
 */
AppSystem* AppSystem::createInstance()
{
#if 0
	std::unique_ptr<AppSystem>  pApp = std::make_unique<AppSystem>();
	if ( pApp )
	{
		pApp->appSystemClean();
	}
	else {
		// NOTE�F�����ŉ�������Ă����̂ŉ�������̖����͕K�v����
		pApp = NULL;
	}
	return pApp.get();
#endif
	AppSystem* pApp = new AppSystem();
	if ( pApp )
	{
		pApp->appSystemClean();
	}
	else {
		delete pApp;
		pApp = NULL;
	}
	return pApp;
}
/**
 *
 */
void	AppSystem::appSystemClean()
{
#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
	libDataClear();
#endif
}
void	AppSystem::appSystemTerminate()
{
}

//==============================================================================//
//	
//	( true : ����ɏ�������������   false : �G���[���������� )
bool	AppSystem::appSystemMain()
{
	if( !appSystemInitialize() )
	{
		return false;
	}

	appDebugPrint( DxLib::DebugConfig::eDEBUG_LOG_ERROR, "AppSystem::appSystemMain()\n" );

	// FrameUpdate
	if( !appSystemUpdate() )
	{
		return false;
	}
	if( !appProcessUpdate() )
	{
		return false;
	}

	// APP�V���b�g�_�E������
	appSystemShutdown();

	return true;
}

//==============================================================================//
//	Application�N�����̏���������
// 
int		AppSystem::appSystemInitialize()
{
	auto isDone = appSystemStartSetup();
	if( !isDone ){ return false; }
	// DxLib�O�A�㏈�����S�ďI�����

	// DUMMY
	appSystemResourcesSetup( eROUTE_RESOURCES_LODING );


#if PROJECT_DEBUG
	// DebugSetting
	isDone = appSystemDebugSetting();
	if( !isDone ){ return false; }
#endif

	DEBUG_PRINT("[Process] AppSystem::appSystemInitialize() CLEAR\n");
	// �S�Ă̏������I��点�ă^�C�g���V�[���֑J�ڂ���
	return true;
}

//==============================================================================//
//	
// 
bool	AppSystem::appSystemStartSetup()
{
	auto result = false;

	// DxLib_Init�����O����
	result = dxLib_InitBeforeSetup();
	if( result ){
	}
	// Window���[�h�N���m�F
	result = dxInit_CheckWindowModePlay();
	if( !result ){
		return false;
	}
	// �Ꮘ�����׃��[�h�N���m�F
	result = dxInit_CheckLowSpecModePlay();
	if( result ) {
		setLowSpecMode( TRUE );
	}

	// DxLib_Init���O�ɍs���V�X�e�������菈��
	result = appSystemDxBeforeProcess();
	if( result ) {
		DEBUG_PRINT("[Process] AppSystem::appSystemDxBeforeProcess() CLEAR\n");
	}

	// DX���C�u�������̏�����
	// ��DxLib_Init���O���Ɠ�����O����DxLib�̃f�o�b�O�R�����g�֐��͎g���Ȃ�
	const int isDxLibInit = DxLib_Init();
	if( isDxLibInit == -1 ) 
	{
		return false;
	}
	DEBUG_PRINT("[Process] DxLib_Init() CLEAR\n");
	
	// DxLib_Init������̃��C�u�������菈��
	result = dxLib_InitAfterSetup();
	if( result ){
		// DxLib_Init������̃V�X�e�������菈��
		result = appSystemDxAfterProcess();
		if( result ){

			/**
			 *	���C�u�����ȊO�̃A�v���P�[�V�����p���O����
			 */
			appSystemAdvanceSetup();
		}
	}

	// �^�X�N���s
	result = appSettingSceneRun();

	DEBUG_PRINT("[Process] AppSystem::appSystemStartSetup() CLEAR\n");
	return true;
}

//==============================================================================//
//	Application�I������
//
void	AppSystem::appSystemShutdown()
{
	DEBUG_PRINT("[Process] AppSystem::appSystemShutdown() EXIT\n");

	// �c�w���C�u�����̏I������
	DxLib::DxLib_End();
}

//////////////////////////////////////////////////////////////////////////////////
//	Application���t���[������
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////
bool	AppSystem::appSystemUpdate()
{
	LONGLONG n_NowTime;

	// �`����ʂ�ݒ肷��
	DxLib::SetDrawScreen( DX_SCREEN_BACK );

	// �ŏ��̃t���[���̏�Ԑ��ڎ��ԂȂǂ��Z�b�g
	this->m_PrevTime = DxLib::GetNowHiPerformanceCount();
	this->m_StepTime = MAX_DELTA_TIME;
	this->m_StepNum = 1;

	while( DxLib::ProcessMessage() == 0 )
	{
		// ��Ԑ��ڏ������s���񐔕����[�v
		{
			if( DxLib::CheckHitKey( KEY_INPUT_ESCAPE ) || isExitApp() )
			{
				// �A�v���I���t���O�𗧂Ă�
				if( !isExitApp() ){ setExitAppFlag( TRUE ); }
				break;
			}

	#if PROJECT_DEBUG
			// DEBUG
			App::getDebugOperatPtr()->debugAppUpdate();
	#endif

			// ��Ԑ��ڏ������s��
			if( !appSystemStep( this->m_StepTime ) )
			{
				return false;
			}
		}

		// �A�v�����I�����邩�ǂ����̃t���O�������Ă�����A�v���I��
		if( isExitApp() ) {
			break;
		}

		// �e�`����X�V
		appSystemRenderUpdate();

#if PROJECT_DEBUG
		// �r�L�[��������Ă�����Q�[����ʂ̃X�N���[���V���b�g��ۑ�����
		if( Lib::getKeyPadOperatPtr()->keyInputOneCheck( KEY_INPUT_S ) != DxInput::Command::INPUT_CHECK_NONE ) {
			DxLib::SaveDrawScreenToPNG( 0, 0, 1280, 720, "ScreenShot", 80 );
		}
#endif

		// ����ʂ̓��e��\��ʂɔ��f������
		// ScreenFlip�֐��͐�������������Ă��邽�߁AFPS�������I�Ƀf�B�X�v���C�̃��t���b�V�����[�g�ȉ��ɂȂ�
		if( DxLib::ScreenFlip() != 0 ){}

		// ���݂̎��Ԃ��擾
		n_NowTime = DxLib::GetNowHiPerformanceCount();

		// �O��擾�������Ԃ���̌o�ߎ��Ԃ��Z�o
		this->m_StepTime = (( n_NowTime - this->m_PrevTime ) / 1000000.0f);

		// ��Ԑ��ڏ������s���񐔂��Z�o
		this->m_StepNum  = ( int )( this->m_StepTime / MAX_DELTA_TIME );

		// ��Ԑ��ڏ������s���񐔂��O��̏ꍇ�͂P��ɂ���
		if( this->m_StepNum == 0 )
		{
			this->m_StepNum = 1;
		}
		else{
			// �O��ł͂Ȃ��ꍇ�͏�Ԑ��ڂŐi�߂鎞�Ԃ���Ԑ��ڂ��s���񐔂Ŋ���
			this->m_StepTime /= this->m_StepNum;

			// ������Ԑ��ڂ��s���񐔂��ő�l�𒴂��Ă�����ő�l�ɗ}����
			if( this->m_StepNum > MAX_FRAME_NUM )
			{
				this->m_StepNum = MAX_FRAME_NUM;
			}
		}

		// ����̎��Ԃ�ۑ�����
		this->m_PrevTime = n_NowTime;

		// �t���[�����[�g�v���p�̃J�E���^���P����
		this->m_FrameCounter ++;

		// �O��t���[�����[�g���X�V���Ă���P�b�o�߂�����\���p�t���[���J�E���g���X�V����
		if ( (n_NowTime - this->m_BackDispFrameTime) > FRAME_UPDATE_SEC )
		{
			// �\���p�t���[���J�E���g���X�V
			this->m_DispFrameCount = this->m_FrameCounter;

			// �v���p�t���[���J�E���^��������
			this->m_FrameCounter = 0;

			// �\���p�t���[���J�E���g���X�V�������Ԃ��X�V
			this->m_BackDispFrameTime = n_NowTime;
		}

		// ��ʃN���A
		DxLib::ClearDrawScreen();

	}// while( DxLib::ProcessMessage() == 0 )

	// ����I��
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
// Application���t���[������
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////
bool	AppSystem::appProcessUpdate()
{
	// ����I��
	return true;
}

//==============================================================================//
//	���t���[���`�揈���X�V
//
void	AppSystem::appSystemRenderUpdate()
{
#if 1
	int _drawHandle = -1;
	#if 0
	const int vramType = gpVramGetVVramType( AppLib::Resources::ResourcesFile_Name02 );
	_drawHandle = _getGraphicTexVramLoadHandle(
							AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
							AppLib::Resources::ResourcesFile_Name02 );
	#else
	_drawHandle = getVramFileParameterLoadHandle( AppLib::Resources::ResourcesFile_Name05, false );
	#endif
	if ( _drawHandle != -1 ){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA, 255 );
		DrawGraph( 0, 0, _drawHandle, TRUE );
	}
#endif


	// �t���[�����[�g
	dxCommon_DrawFramerate( getDispFrameCount() );
}

//==============================================================================//
//	DxLibInit�̃R�[���O�ɍs���Ă�������
//
bool	AppSystem::appSystemDxBeforeProcess()
{
	return true;
}

//==============================================================================//
//	DxLibInit�̃R�[����ɍs������
//
bool	AppSystem::appSystemDxAfterProcess()
{
	// App��{���̐ݒ�
	auto result = getAppContainerPtr()->setApplicationInfo();
	if( !result ){ return false; }

	// �e���C�u�����̐ݒ�
	#if( __MIDDLEWARE_EFFEKSEER_USE_ENABLE == 1 )
		// Effekseer�֌W����������
		// ���^�C�~���O��DxLib_Init���I�����DxLib�֌W�������㏈�����I�������
		App::EffekseerLib::libSystemInit();
	#endif
	
	DEBUG_PRINT("[Process] AppSystem::appSystemDxAfterProcess() CLEAR\n");

	return true;
}



//==============================================================================//
//	
//	
void	AppSystem::appSystemAdvanceSetup()
{
	this->m_LocalStep = eROUTE_ADVANCE_INIT;


	appSystemResourcesSetup( eROUTE_RESOURCES_ENTRY );

}
void	AppSystem::appSystemResourcesSetup( int processStep )
{
	// ���\�[�X�̓o�^�E�ǂݍ���
	{
#if 1
		int result = -1;

		if ( processStep == eROUTE_RESOURCES_ENTRY )
		{
		/*
		result = _graphicVramTextureEntry(
					AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
					AppLib::Resources::ResourcesFile_Name01,
					AppLib::Resources::Archive::eARCHIVE_FILETYPE_RESOURCES,
					// AppLib::Resources::Parameter::EntryIndex::eRESFILE_NAME_GAME_FICTION_IMAGE,
					AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_APPSTART,
					AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SYSTEM );
		*/
		
		//���V�d�l����Ver
		result = vramTextureFileEntry( 
					AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,						/** VRAM�^�C�v */
					AppLib::Resources::ResourcesFile_Name01,									/** �t�@�C���l�[�� */
					AppLib::Resources::Archive::eARCHIVE_FILETYPE_RESOURCES,					/** �A�[�J�C�u�t�@�C���^�C�v */
					AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SYSTEM,				/** �t�@�C���̓o�^�����^�C�v */
					AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_SCENE_TITLE				/**  */
					// AppLib::Resources::Parameter::EntryIndex::eRESFILE_NAME_GAME_TITLE_TEX_BG	/** �t�@�C���̓o�^�C���f�b�N�X */
		);
		result = vramTextureFileEntry( 
					AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,						/** VRAM�^�C�v */
					AppLib::Resources::ResourcesFile_Name05,									/** �t�@�C���l�[�� */
					AppLib::Resources::Archive::eARCHIVE_FILETYPE_RESOURCES,					/** �A�[�J�C�u�t�@�C���^�C�v */
					AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SYSTEM,				/** �t�@�C���̓o�^�����^�C�v */
					AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_SCENE_TITLE				/**  */
		);
		result = vramTextureFileEntry( 
					AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,						/** VRAM�^�C�v */
					AppLib::Resources::ResourcesFile_Name03,									/** �t�@�C���l�[�� */
					AppLib::Resources::Archive::eARCHIVE_FILETYPE_RESOURCES,					/** �A�[�J�C�u�t�@�C���^�C�v */
					AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_SYSTEM,				/** �t�@�C���̓o�^�����^�C�v */
					AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_SCENE_TITLE				/**  */
		);

		DEBUG_PRINT("[Process] AppSystem::VramTextureEntry CLEAR\n");
		}
		else if ( processStep == eROUTE_RESOURCES_LODING )
		{
		/*
		//�����d�l����Ver
		_graphicVramTexAttrUp(	AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM,
								AppLib::Resources::ProcessStatus::eUPMODE_NORMAL,
								AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_APPSTART );

		*/
		//���V�d�l����Ver
		vramTextureFileSingleUpload( AppLib::Resources::ResourcesFile_Name01,
									 AppLib::Resources::ProcessStatus::eUPMODE_NORMAL );
		vramTextureFileSingleUpload( AppLib::Resources::ResourcesFile_Name05,
									 AppLib::Resources::ProcessStatus::eUPMODE_NORMAL );
		}
#endif
	}
}


/**
 *	�f�o�b�O
 *
 */
bool	AppSystem::appSystemDebugSetting()
{
#if PROJECT_DEBUG
	App::getDebugOperatPtr()->debugMenuNameSet(			DxLib::DebugConfig::eDEBUG_TYPE_MAIN,
														"MAIN_MENU" );
	App::getDebugOperatPtr()->debugModeStartProcSet(	DxLib::DebugConfig::eDEBUG_TYPE_MAIN,
														"MAIN_MENU", &appSystemDebugStart );
	App::getDebugOperatPtr()->debugModeEndProcSet(		DxLib::DebugConfig::eDEBUG_TYPE_MAIN,
														"MAIN_MENU", &appSystemDebugEnd );
	App::getDebugOperatPtr()->debugModeMainProcSet(		DxLib::DebugConfig::eDEBUG_TYPE_MAIN,
														"MAIN_MENU", &appSystemDebugMain );
	App::getDebugOperatPtr()->debugModeRenderProcSet(	DxLib::DebugConfig::eDEBUG_TYPE_MAIN,
														"MAIN_MENU", &appSystemRenderEnd );

	DEBUG_PRINT("[Process] AppSystem::appSystemDebugSetting() CLEAR\n");

	return true;
#else
	return false;
#endif
}
void	AppSystem::appSystemDebugStart()
{
}
void	AppSystem::appSystemDebugEnd()
{
}
int		AppSystem::appSystemDebugMain()
{
	return 0;
}
void	AppSystem::appSystemRenderEnd()
{
}






//==============================================================================//
// 
bool	AppSystem::appSettingSceneRun()
{
	// �ŏ��̃V�[���^�X�N�����s����
	if( 1 )
	{
		return false;
	}

	return true;
}

//==============================================================================//
// ��Ԑ��ڏ������s��
//     �߂�l : ����������ɏI���������ǂ���(true:����ɏI������  false:�G���[����������)
bool	AppSystem::appSystemStep(
	float StepTime	// ���ڂ����鎞��( �P�� : �b )
)
{

	// ����I��
	return true;
}