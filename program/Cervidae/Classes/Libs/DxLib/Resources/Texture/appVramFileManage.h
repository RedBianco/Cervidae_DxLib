#pragma once

//===================================================================//
//
//
//
//===================================================================//

#include "appResourcesLoadContainer.h"
#include "appFileSystem.h"

/**
 *	@class リソースファイルのマネージャークラス
 */
namespace DxLib
{
	class AppVramFileManager : public AppFileSystem
	{
	public:
		AppVramFileManager();
		virtual ~AppVramFileManager();

	public:

		// データ管理コンテナ
		std::vector< DxLib::ResourcesLoadContainer>		m_resourcesContainer;

		// 読み込み数管理
		int		m_LoadedFiles;
		int		m_EnteredFiles;
			
	public:

		// 管理システム基本初期化
		bool	vramFileSystemInit();

		// 管理システム終了処理
		bool	vramFileSystemExit();

		// ファイルメモリアップロード
		int		vramTextureLoad( /*const char * loadFileName, */DxLib::ResourcesLoadContainer * pfileContainer );

		// グラフィックファイルの登録(登録VRAMタイプ,画像名,登録ファイルINDEX,画像ファイル番号,画像登録属性)
		// ※登録のみで読み込みは行わない
		int		vramTextureFileEntry( const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE fileVramType,
									  const char* fileName, 
									  const AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_LIST fileArchiveType,
									  const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType,
									  const AppLib::Resources::Parameter::ENUM_GRAPHIC_FILE_ENTRY_TYPE fileEntryUseType );

		// グラフィック画像データ特定ファイル単体読み込みメモリアップ
		int		vramTextureFileSingleUpload( const char* fileName, 
											 const int fileUpmode = AppLib::Resources::ProcessStatus::eUPMODE_NORMAL, 
											 int fileCheckNum = 1 );

		// 指定属性の画像ファイルを全てメモリアップ
		int		vramSpecificAttributeFilesAllUpload( const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE fileVramType,
													 const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType,
													 const int fileUpmode = AppLib::Resources::ProcessStatus::eUPMODE_NORMAL,
													 int fileCheckNum = 1 );

		// ２重登録防止で既に登録済みかチェック
		bool	isFileEntryDoubleRegistration( const char* fileName/*, const int fileIndex*/ );
		bool	isFileEntryIndexDoubleRegistration( /*const char * fileName,*/ const int fileIndex );

		// ２重読み込み防止で既に読み込み済みかチェック
		bool	isFileLoadDoubleRegistration( const char* fileName/*, const int fileIndex*/ );

		// 有効(読み込み中)グラフィックハンドルの数を取得する
		int		getVramFileValiditLoadHandle();
		int		getVramUpLoadedFiles();

		// 指定ファイルインデックスが要素コンテナの何番目に登録されているかのインデックスを取得
		int		getVramFileElementEntryIndex( const char* fileName, bool isLoadFile = false );

		// ファイル名から登録インデックスを取得（登録済みなら）
		int		getVramFileParameterIndex( const char* fileName, bool isLoadFile = false );

		// ファイル名からロードハンドルを取得
		int		getVramFileParameterLoadHandle( const char* fileName, bool isLoadFile = false );

		// ファイル名からアーカイブ設定を取得
		int		getVramFileParameterArchiveType( const char* fileName, bool isLoadFile = false );

		// 指定属性タイプのメモリに上がっている読み込み状態ファイル数を取得
		int		getSpecificAttributeLoadFiles( const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttribute, 
											   bool isLoadFile = false );

		// 指定テクスチャ登録情報を削除する
		int		vramContainerDataClear( const char* clearTexture );
		// 指定ファイルハンドルの登録情報を削除する
		int		vramContainerDataClear( const int clearHandle );
		int		vramContainerDataClearALL();

		// 登録、読み込みを一気に行う用
		int		vramTextureExecutionRelatedProcesses( 
									const AppLib::Resources::ProcessStatus::ENUM_RESOURCES_VRAM_TYPE	 fileVramType,
									const char* fileName, 
									const AppLib::Resources::Archive::ENUM_ARCHIVE_FILETYPE_LIST		 fileArchiveType,
									const AppLib::Resources::Attribute::ENUM_RESFILE_ATTRIBUTE_TYPE_LIST fileAttrType,
									const AppLib::Resources::Parameter::ENUM_GRAPHIC_FILE_ENTRY_TYPE	 fileEntryUseType,
									const int	fileUpmode = AppLib::Resources::ProcessStatus::eUPMODE_NORMAL );

		
	public:

		DxLib::ResourcesLoadContainer *	getContainer( const char* fileName );
		DxLib::ResourcesLoadContainer * getElementRecordContainer( size_t index ) { return &m_resourcesContainer.at( index ); }
		
		// テクスチャサイズ取得
		const ObjectSize	getTextureObjSize( const char* fileName ) { getContainer( fileName )->m_vTextureObj; }

		// 読み込み数を返す
		int		getLoadingFileCount() const { return m_LoadedFiles; }
		int		getLoadingFileSize() const { return static_cast<int>( m_resourcesContainer.size() ); }

	private:
		// 画像ファイル名から頭に設定されている登録インデックス値を取得する
		int		getSetupFileNameEntryIndex( const char * checkFile );
	};
}
#if 0
	class AppVramManager
	{
	public:
		AppVramManager();
		~AppVramManager();

	public:

		// 全体のテクスチャ読み込み数
		int					vp_LoadCount;
		// 処理チェック
		std::vector< int >	vp_CheckSet;

	public:

		void	vfileInit();

	};
#endif


/* End appVramFileManage.h */


