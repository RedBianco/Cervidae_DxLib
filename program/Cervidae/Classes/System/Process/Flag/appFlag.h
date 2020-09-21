
#pragma once


//=================================================================================//
//  appFlag.h
//  Cervidae
//
//  Created by kashima akihiro on 2019/12/11.
//=================================================================================//


typedef enum
{
	eFLAG_CATEGORY_APP = 0,
	eFLAG_CATEGORY_SYSTEM,
	eFLAG_CATEGORY_TITLE,
	eFLAG_CATEGORY_ADV,

	ENUM_FLAG_CATEGORY_MAX

} ENUM_FLAG_CATEGORY_TAG;

typedef enum
{
	eFLAG_TYPE_APPDATA,
	eFLAG_TYPE_SYSTEM,

	ENUM_FLAG_TYPE_MAX,

} ENUM_CREATE_FLAG_TYPE;


namespace App
{
	//-------------------------------------------------------
	//	�t���O���Ǘ��p
	//	
	struct FlagObjectData
	{
		ENUM_CREATE_FLAG_TYPE		m_FlagType;
		std::string					m_FlagName;
		int							m_Num;
		int							m_Setup;
		int							m_Init;
		ENUM_FLAG_CATEGORY_TAG		m_FlagCategory;
	};

	//-------------------------------------------------------
	//
	//
	//
	//
	class FlagManager : public Singleton<FlagManager>
	{
		// DebugModeOperat�̃C���X�^���X�𐶐����鎞�ɁA�R���X�g���N�^���ĂׂȂ�������friend�w��
		// �V���O���g���̃e���v���[�g�����Ɏ��g���w�肵�����̂����ɐ�������邷
		friend class Singleton<FlagManager>;	// Singleton �ł̃C���X�^���X�쐬�͋���

	public:


	private:
		std::vector< App::FlagObjectData>	m_FlagDataList;

		int		m_AppFlagEntry = 0;		// �ʏ�t���O�o�^��
		int		m_SystemFlagEntry = 0;	// �V�X�e���t���O�o�^��
		int		m_ReadMode = 0;

	public:
		static void createFlagManager( void)
		{
			DEBUG_PRINT("[Lib] App::FlagManager CreateInstance() CLEAR\n");
			return Singleton<FlagManager>::create();
		}

		// �t���O�Ǘ��V�X�e����{������
		void	dataSystemInit();

		// �t���O�쐬
		int		createFlag( const char* flagName, const int flagValue, const ENUM_CREATE_FLAG_TYPE nType, const ENUM_FLAG_CATEGORY_TAG flagCategory );

		// �w��^�C�v�t���O�̎g�p����Ԃ�
		int		libFlag_isUseFlagNum( const ENUM_CREATE_FLAG_TYPE flagType );

		// ���O����t���O�̓o�^�ԍ���Ԃ�
		int		libFlag_FlagDataIdGet( const char* flagName, const ENUM_CREATE_FLAG_TYPE flagType );

		// �t���O�ɐ��l���
		int		libFlag_FlagNumSet( const char* flagName, const int  flagValue, const ENUM_CREATE_FLAG_TYPE flagType );
		int		libFlag_FlagNumSet( const int  listIndex, const int  flagValue, const ENUM_CREATE_FLAG_TYPE flagType );

		// �t���O�̒l����
		int		libFlag_FlagNumChange( const char* flagName, const int  flagValue, const ENUM_CREATE_FLAG_TYPE flagType );
		int		libFlag_FlagNumChange( const int  listIndex, const int  flagValue, const ENUM_CREATE_FLAG_TYPE flagType );

		// �w��C���f�b�N�X�̃t���O�l�Q��
		int		libFlag_isFlagNumber( const char* flagName, const ENUM_CREATE_FLAG_TYPE flagType );
		int		libFlag_isFlagNumber( const int  listIndex, const ENUM_CREATE_FLAG_TYPE flagType );

		// �t���O���w��̐��l�����Ȃ�w��̐��l�ɃZ�b�g
		int		libFlag_FlagMinimum( const char* flagName, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType );
		int		libFlag_FlagMinimum( const int  index, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType );
		// �t���O���w��̐��l����Ȃ�w��̐��l�ɃZ�b�g
		int		libFlag_FlagMaximum( const char* flagName, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType );
		int		libFlag_FlagMaximum( const int  index, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType );

		// �t���O�l�ݒ�
		int		libFlag_FlagSetUp(const char* fName, const int  nSetup, const ENUM_CREATE_FLAG_TYPE  flagType);
		int		libFlag_FlagSetUp(const int  nID, const int  nSetup, const ENUM_CREATE_FLAG_TYPE flagType);

		// �t���O�l�ݒ���Q��
		int		libFlag_FlagSetUpGet(const char* fName, const ENUM_CREATE_FLAG_TYPE flagType);
		int		libFlag_FlagSetUpGet(const int  nID, const ENUM_CREATE_FLAG_TYPE flagType);

		// �t���O�̒l��z��֑��(�Z�[�u���p)
		int		libFlag_FlagAllGet(const ENUM_CREATE_FLAG_TYPE fType, int* pNum);
		// �t���O�̒l��z��֑��(���[�h���p)
		int		libFlag_FlagAllSet(const ENUM_CREATE_FLAG_TYPE fType, int* pNum);


		bool	libFlag_FlagPointerGet(const ENUM_CREATE_FLAG_TYPE nType, App::FlagObjectData** tagFlag);
		bool	libFlag_FlagPointerGet(const ENUM_CREATE_FLAG_TYPE nType, App::FlagObjectData** tagFlag, const int nIndex);
		void	libFlag_AppFlagEntry();
		

		// 
		int		libFlag_NormalFlagNumCheck(const char* flagName);
		int		libFlag_SystemFlagNumCheck(const char* flagName);

	public:
		// �R���X�g���N�^������public�ɂ��Ă��܂��ƁAAppParameter  container; �ŃC���X�^���X����Ă��܂�
		// �u���̃N���X�̃C���X�^���X��1������������Ȃ����Ƃ�ۏ؂��邱�Ƃ��ł���v
		// �ƌ����̂ɔ�����̂�private�ɂ���K�v������B
		FlagManager() {		// �O���ł̃C���X�^���X�쐬�͋֎~
			dataSystemInit();
		};
//		virtual ~FlagManager();
	};

	/* @brief �A�N�Z�X�C���^�[�t�F�[�X
	 */
	inline FlagManager* getFlagInstancePtr(void)
	{
		return Singleton<FlagManager>::getSingletonPtr();
	}
}// namespace App










