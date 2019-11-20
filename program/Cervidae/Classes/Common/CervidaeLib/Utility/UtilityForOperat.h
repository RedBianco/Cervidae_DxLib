#pragma once

//===================================================================================
//  UtilityForOperat.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/13.
//===================================================================================


//-----------------------------------------------------------------------------------
// 便利関数群
//-----------------------------------------------------------------------------------
namespace UtilityForOperat
{
	/**
	 * 文字列内の改行コード削除
	 * @param src    対象文字列
	 */
	void	removeLineFeed( std::string &str );

	/**
	 * UTF-8の文字長を調べる
	 * @param	buff UTF-8の文字列
	 * @return	引数で指定された文字列の長さ
	 */
	const int	getUTF8StrLen( const char *buff );
    
	/**
	 * UTF-8の文字長を調べる(半角考慮版)
	 * @param	buff UTF-8の文字列
	 * @return	引数で指定された文字列の長さ(半角は0.5としてる)
	 */
	const float	getUTF8StrLenSingleByte( const char *buff );

    /**
     * UTF-8文字が何バイト文字か調べる
     * @param p UTF-8の文字(1文字)
     * @return 引数で指定された文字のbyte数
     */
    int		getByteInUTF8Char( const char* p );

    /*!
     * 文字列に含まれる指定された文字列の数を返す
     * @param[in] s 元の文字列
     * @param[in] c 検索文字列
     * @return 含まれる数
     */
    int		getCountString( std::string &s, int offset, std::string c );

	/**
	 * std::stringからdoubleへの変換
	 * @param	str 変換したい文字列
	 * @return	変換された数値
	 */
	double	stringToDouble( const std::string& str );

	/**
	 * intからstd::stringへの変換
	 * @param	d 変換したい数値
	 * @return	変換された文字列
	 */
	std::string  doubleToString( double d );

    /**
     * std::stringからintへの変換
     * @param str 変換したい文字列
     * @return 変換された数値
     */
	double	stringToInteger( const std::string& str );
    
    /**
     * intからstd::stringへの変換
     * @param str 変換したい数値
     * @return 変換された文字列
     */
    std::string integerToString( int i );

	/**
	 * std::stringからbigintへの変換
	 * @param str 変換したい文字列
	 * @return 変換された数値
	 */
	long long stringToBigint(const std::string& str);

	/**
	 * bigintからstd::stringへの変換
	 * @param str 変換したい数値
	 * @return 変換された文字列
	 */
	std::string bigintToString(long long i);

	/**
	 * unsigned longからstd::stringへの変換
	 * @param str 変換したい数値
	 * @return 変換された文字列
	 */
	std::string ulongToString(unsigned long l);

	/**
	 * 文字列の置換
	 * @param str 置換する文字列
	 * @param from 置換前文字列
	 * @param to 置換後文字列
	 */
	std::string& strReplace(std::string& str, const std::string& from, const std::string& to);

	/**
	 * 文字列の分割
	 * @param dest  格納先
	 * @param src   元文字列
	 * @param delim 区切り文字
	 */
	std::vector<std::string>* SpritString(std::vector<std::string> *dest, const std::string &src, const std::string &delim);

	/**
	 * 文字列のトリミング
	 * @param src_string    元文字列
	 * @param trim_targets  トリミング対象
	 */
	std::string TrimmingString(const std::string& src_string, const std::string trim_targets = " \t\r\n");

	/**
	 * 指定した文字列が、半角か全角か調べる
	 * @param 
	 * @param 戻り値(バイト数)
	 */
	int		getStringWordByte( unsigned char * pWordText );

	/**
	 * タグを外した文字の長さ(半角)を出す
	 * @param	
	 * @return	半角の長さ数値
	 */
	const int	getStringLongTag( char * et_str );

	/**
	 * タグを外した文字数(半角全角区別する)を出す
	 * @param	
	 * @return	文字数(半角全角区別する)
	 */
	const int	getStringNumTag( char * et_str );

	/**
	 * 文字数取得
	 * @param	iText	文字列
	 * @param	oNum	１行最大文字数
	 * @param	oLine	行数
	 * @return	
	 */
	void    getStringNumLineGet(char* iTxt, int* oNum, int* oLine);

	/**
	 * ミリ秒をフレーム数に変える
	 * @param	msec	カウント
	 * @return	
	 */
	int		getChangeMsecToFrame( int msec );

	/**
	 * 指定した文字列から拡張子を除いた名前を取得する
	 * @param	szSrcFileFullPath
	 * @param	szDst		
	 * @param	sizeOut		
	 * @return	
	 */
	char *	getMsGetFileNameWithoutExt( char * szSrcFileFullPath, char * szDst, size_t  sizeOut );
	
	/**
	 * ディレクトリの区切り記号であるかどうかをチェックする
	 * @param	szSrcFilePath
	 * @return	
	 */
	const bool	isEtcDirectoryFigure( char szCh );
	
	/**
	 * 設定した文字列がSJISかどうかを調べる
	 * @param
	 * @return
	 */
	const bool	isStringCodeSJIS( const char *lpSrc );

	/**
	 * マルチバイト文字かチェック
	 * @param
	 * @return
	 */
	const bool	isStringMultiByte( const char *pstr);

	/**
	 * 指定した配列の文字列の中から最大の文字数を返す
	 * @param	*arry[]
	 * @param	len_size
	 * @return
	 */
	const int	getStringArryElement( char* arry[], int len_size );

	/**
	 * 両方の文字列の長い方を返す
	 * @param
	 * @param
	 * @return
	 */
	const char* getStringMaxLen( const char* strx, const char* stry );
	/**
	 * セットした複数文字列の中から一番長い文字列の文字数を返す
	 * @param
	 * @param
	 * @return
	 */
	const char* getStringArryMaxLen( std::vector<std::string> arry );

	/**
	 * 有効桁以下を切り捨てる
	 * @param	coefficient
	 * @param	decimal_count
	 * @return
	 */
	float	floorWithDecimalCount( float coefficient, int decimal_count );

	/**
	 * 
	 * @param	coefficient
	 * @param	decimal_count
	 * @return
	 */
	bool	getStringReturnCode( char * pStr, int * type );

	/**
	 * 特定ワードを設定文字に置換する( %Value% )
	 * @param	char* baseText
	 * @param	int replaceValue
	 * @return
	 */
	const std::string	getReplaceTextValue( const char* baseText, int replaceValue, bool isComma = false );

	/**
	 * 特定ワードを設定文字に置換する( %text% )
	 * @param	char* baseText
	 * @param	char* setText
	 * @return
	 */
	const std::string	getReplaceText( const char* baseText, const char* setText, bool isComma = false );
}





/* End UtilityForOperat.h */

