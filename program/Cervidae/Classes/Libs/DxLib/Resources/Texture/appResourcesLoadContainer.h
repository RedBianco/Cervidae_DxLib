#pragma once

//===================================================================//
//	appResourcesLoadContainer
//
//
//===================================================================//

/**
 *  基本このクラスを使用する
 */
/**
 *	@class リソースファイル管理用基本クラス
 */
namespace DxLib
{
    /**
	 * 
	 */
	class ResourcesLoadContainer
	{
	public:
		ResourcesLoadContainer() : 
			m_vLoadVramType( AppLib::Resources::ProcessStatus::eFILE_GRAPHIC_SYSTEM ),
			m_vFileArchIndex( AppLib::Resources::Archive::eARCHIVE_FILETYPE_NONE ),
			m_vFileIndex( -1 ),
			m_vFileAttribute( AppLib::Resources::Attribute::eRESFILE_ATTRIBUTE_TYPE_MAIN ),
			m_vLoadFileHandle( AppLib::Resources::ProcessStatus::eGPFILE_HANDLE_NONUSE ),
			m_vFileStatus( AppLib::Resources::ProcessStatus::eVRAM_FILE_STATUS_NOUSE ),
			m_vFileEntryUseType( AppLib::Resources::Parameter::eGRAPHIC_FILE_ENTRY_NONE )
		{
			m_vTextureObj.m_RenderW = 0;
			m_vTextureObj.m_RenderH = 0;
			DEBUG_PRINT("Resources : ResourcesLoadContainer コンストラクタ\n");
		}

		~ResourcesLoadContainer() {
			DEBUG_PRINT("Resources : ResourcesLoadContainer デストラクタ\n");
		}

	public:

		AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE		m_vLoadVramType;		// テクスチャファイルをアップするVRAMタイプ
		std::string														m_vLoadTextureName;		// テクスチャファイル登録名
		AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_LIST			m_vFileArchIndex;		// テクスチャファイルのアーカイブインデックス
		int																m_vFileIndex;			// テクスチャファイルの登録インデックス
		AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST	m_vFileAttribute;		// テクスチャファイルの設定属性
		AppLib::Resources::Parameter::ENUM_GRAPHIC_FILE_ENTRY_TYPE		m_vFileEntryUseType;	// テクスチャファイルの
		int																m_vLoadFileHandle;		// テクスチャファイルのロードハンドル
		int																m_vFileStatus;			// テクスチャファイルの処理状況
		
		ObjectSize														m_vTextureObj;			// テクスチャファイルサイズ

		// 読み込みが成功した時のコールバック
		typedef int	(*resultCallBack) ( void *, int );
		
	};
}


/* End appResourcesLoadContainer.h */


