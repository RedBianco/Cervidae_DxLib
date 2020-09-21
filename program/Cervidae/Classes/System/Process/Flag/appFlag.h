
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
	//	フラグ情報管理用
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
		// DebugModeOperatのインスタンスを生成する時に、コンストラクタが呼べなかった為friend指定
		// シングルトンのテンプレート引数に自身を指定したものだけに生成をゆるす
		friend class Singleton<FlagManager>;	// Singleton でのインスタンス作成は許可

	public:


	private:
		std::vector< App::FlagObjectData>	m_FlagDataList;

		int		m_AppFlagEntry = 0;		// 通常フラグ登録数
		int		m_SystemFlagEntry = 0;	// システムフラグ登録数
		int		m_ReadMode = 0;

	public:
		static void createFlagManager( void)
		{
			DEBUG_PRINT("[Lib] App::FlagManager CreateInstance() CLEAR\n");
			return Singleton<FlagManager>::create();
		}

		// フラグ管理システム基本初期化
		void	dataSystemInit();

		// フラグ作成
		int		createFlag( const char* flagName, const int flagValue, const ENUM_CREATE_FLAG_TYPE nType, const ENUM_FLAG_CATEGORY_TAG flagCategory );

		// 指定タイプフラグの使用数を返す
		int		libFlag_isUseFlagNum( const ENUM_CREATE_FLAG_TYPE flagType );

		// 名前からフラグの登録番号を返す
		int		libFlag_FlagDataIdGet( const char* flagName, const ENUM_CREATE_FLAG_TYPE flagType );

		// フラグに数値代入
		int		libFlag_FlagNumSet( const char* flagName, const int  flagValue, const ENUM_CREATE_FLAG_TYPE flagType );
		int		libFlag_FlagNumSet( const int  listIndex, const int  flagValue, const ENUM_CREATE_FLAG_TYPE flagType );

		// フラグの値増減
		int		libFlag_FlagNumChange( const char* flagName, const int  flagValue, const ENUM_CREATE_FLAG_TYPE flagType );
		int		libFlag_FlagNumChange( const int  listIndex, const int  flagValue, const ENUM_CREATE_FLAG_TYPE flagType );

		// 指定インデックスのフラグ値参照
		int		libFlag_isFlagNumber( const char* flagName, const ENUM_CREATE_FLAG_TYPE flagType );
		int		libFlag_isFlagNumber( const int  listIndex, const ENUM_CREATE_FLAG_TYPE flagType );

		// フラグが指定の数値未満なら指定の数値にセット
		int		libFlag_FlagMinimum( const char* flagName, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType );
		int		libFlag_FlagMinimum( const int  index, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType );
		// フラグが指定の数値より上なら指定の数値にセット
		int		libFlag_FlagMaximum( const char* flagName, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType );
		int		libFlag_FlagMaximum( const int  index, const int  fNum, const ENUM_CREATE_FLAG_TYPE flagType );

		// フラグ値設定
		int		libFlag_FlagSetUp(const char* fName, const int  nSetup, const ENUM_CREATE_FLAG_TYPE  flagType);
		int		libFlag_FlagSetUp(const int  nID, const int  nSetup, const ENUM_CREATE_FLAG_TYPE flagType);

		// フラグ値設定を参照
		int		libFlag_FlagSetUpGet(const char* fName, const ENUM_CREATE_FLAG_TYPE flagType);
		int		libFlag_FlagSetUpGet(const int  nID, const ENUM_CREATE_FLAG_TYPE flagType);

		// フラグの値を配列へ代入(セーブ時用)
		int		libFlag_FlagAllGet(const ENUM_CREATE_FLAG_TYPE fType, int* pNum);
		// フラグの値を配列へ代入(ロード時用)
		int		libFlag_FlagAllSet(const ENUM_CREATE_FLAG_TYPE fType, int* pNum);


		bool	libFlag_FlagPointerGet(const ENUM_CREATE_FLAG_TYPE nType, App::FlagObjectData** tagFlag);
		bool	libFlag_FlagPointerGet(const ENUM_CREATE_FLAG_TYPE nType, App::FlagObjectData** tagFlag, const int nIndex);
		void	libFlag_AppFlagEntry();
		

		// 
		int		libFlag_NormalFlagNumCheck(const char* flagName);
		int		libFlag_SystemFlagNumCheck(const char* flagName);

	public:
		// コンストラクタ部分をpublicにしてしまうと、AppParameter  container; でインスタンスつくれてしまう
		// 「そのクラスのインスタンスが1つしか生成されないことを保証することができる」
		// と言うのに反するのでprivateにする必要がある。
		FlagManager() {		// 外部でのインスタンス作成は禁止
			dataSystemInit();
		};
//		virtual ~FlagManager();
	};

	/* @brief アクセスインターフェース
	 */
	inline FlagManager* getFlagInstancePtr(void)
	{
		return Singleton<FlagManager>::getSingletonPtr();
	}
}// namespace App










