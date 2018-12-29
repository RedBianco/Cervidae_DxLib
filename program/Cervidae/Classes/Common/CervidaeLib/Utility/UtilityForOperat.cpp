

#include "UtilityForOperat.h"


//===================================================================================
//  UtilityForOperat.cpp
//
//  
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
	void    removeLineFeed( std::string &str )
	{
		const char CR = '\r';
		const char LF = '\n';
		std::string workStr;
		
		for( const auto c : str )
		{
			if(c != CR && c != LF)
			{
				workStr += c;
			}
		}
		str = std::move( workStr );
	}

	/**
	 * UTF-8の文字長を調べる
	 * @param	buff UTF-8の文字列
	 * @return	引数で指定された文字列の長さ
	 */
	int		getUTF8StrLen( const char *buff )
	{
		// 文字列がNULLなら長さは0
		if (buff == NULL){ return 0; }

		int count = 0;
		int pos = 0;
		size_t max_bytes = strlen(buff);

		// 3byte以上あるならBOMがある可能性があるので、BOMがあればBOMを読み飛ばす
		if (max_bytes >= 3) {
			if (static_cast<unsigned char>(buff[0]) == 0xEF && static_cast<unsigned char>(buff[1]) == 0xBB && static_cast<unsigned char>(buff[2]) == 0xBF) {
				pos += 3;
			}
		}

		// 文字数をカウントする
		while (pos < max_bytes) {
			++ count;
			// 1バイト文字の場合、読み取り位置を1進める
			if ((buff[pos] & 0x80) == 0) {
				++pos;
			}
			// 複数バイト文字の場合、読み取り位置をバイト数分進める
			else {
				for(char tmp = buff[pos] & 0xfc; (tmp & 0x80); tmp = tmp << 1) {
					++ pos;
				}
			}
		}
		return count;
	}

	/**
	 * UTF-8の文字長を調べる(半角考慮版)
	 * @param	buff UTF-8の文字列
	 * @return	引数で指定された文字列の長さ(半角は0.5としてる)
	 */
	float	getUTF8StrLenSingleByte( const char *buff )
	{
		// 文字列がNULLなら長さは0
		if (buff == NULL) { return 0; }

		float count = 0;
		int pos = 0;
		size_t max_bytes = strlen(buff);

		// 3byte以上あるならBOMがある可能性があるので、BOMがあればBOMを読み飛ばす
		if (max_bytes >= 3) {
			if (static_cast<unsigned char>(buff[0]) == 0xEF && 
				static_cast<unsigned char>(buff[1]) == 0xBB && 
				static_cast<unsigned char>(buff[2]) == 0xBF) {
				pos += 3;
			}
		}

		// 文字数をカウントする
		while (pos < max_bytes) {
			// 1バイト文字の場合、読み取り位置を1進める
			if ((buff[pos] & 0x80) == 0) {
				++ pos;
				count += 0.5f;
			}
			// 複数バイト文字の場合、読み取り位置をバイト数分進める
			else {
				for (char tmp = buff[pos] & 0xfc; (tmp & 0x80); tmp = tmp << 1) {
					++ pos;
				}
				count += 1.0f;
			}
		}
		return count;
	}

	/**
	 * UTF-8文字が何バイト文字か調べる
	 * @param p UTF-8の文字(1文字)
	 * @return 引数で指定された文字のbyte数
	 */
	int		getByteInUTF8Char( const char* p )
	{
		int byte = 0;

		// 最初に1となるbitを検索
		for (int i = 0; i < 6; ++i) {
			if (((*p >> (7 - i)) & 0x01) == 0) {
				byte = i;
				break;
			}
		}

		// 10から始まる先頭バイトは存在しない
		if (byte == 1) {
			return -2;
		}
		// 0から始まる時は、1byteで1文字を表すことを考慮した計算
		else if (byte != 0) {
			-- byte;
		}

		// 2バイト目以降は、10から始まるビットパターンでなければならない
		for (int i = 1; i < byte; ++i) {
			if (((p[i] >> 6) & 0x03) != 0x02) {
				return -3; // ビットパターンの不一致
			}
		}
		return byte + 1;
	}

    /*!
     * 文字列に含まれる指定された文字列の数を返す
     * @param[in] s 元の文字列
     * @param[in] c 検索文字列
     * @return 含まれる数
     */
    int		getCountString( std::string &s, int offset, std::string c )
    {
        int count = 0;
        size_t pos0 = offset, pos = 0;
        int n = (int)c.size();
        
        while((pos = s.find(c, pos0)) != std::string::npos){
            if(pos != pos0){
                count ++;
            }
            else{
                s.erase(s.begin()+pos);
            }
            pos0 = (pos + n);
        }
        // 最後の文字列除去
        if( s.rfind(c) == s.size()-n ){
            count --;
        }
        return count;
    }

    /**
     * std::stringからdoubleへの変換
     * @param str 変換したい文字列
     * @return 変換された数値
     */
    double	stringToDouble( const std::string& str )
	{
        double result = std::strtod( str.data(), NULL );
        return result;
    }
    
    /**
     * doubleからstd::stringへの変換
     * @param d 変換したい数値
     * @return 変換された文字列
     */
    std::string doubleToString(double d)
	{
        std::ostringstream oss;
        oss << d;
        std::string result( oss.str() );
        return result;
    }

	/**
	 * std::stringからintへの変換
	 * @param str 変換したい文字列
	 * @return 変換された数値
	 */
	double	stringToInteger(const std::string& str)
	{
		double result = std::strtod(str.data(), NULL);
		return result;
	}

	/**
	 * intからstd::stringへの変換
	 * @param str 変換したい数値
	 * @return 変換された文字列
	 */
	std::string integerToString( int i )
	{
		char buff[256] = { 0 };
		snprintf(buff, sizeof(buff), "%d", i);
		return std::string(buff);
	}

    /**
     * std::stringからbigintへの変換
     * @param str 変換したい文字列
     * @return 変換された数値
     */
    long long stringToBigint(const std::string& str)
	{
        long long result;
        std::stringstream ss;
        ss << str;
        ss >> result;
        return result;
    }

    /**
     * bigintからstd::stringへの変換
     * @param str 変換したい数値
     * @return 変換された文字列
     */
    std::string bigintToString(long long i)
	{
        std::string result;
        char buff[256] = {0};
        snprintf(buff, sizeof(buff), "%lld", i);
        result = buff;
        return result;
    }

    /**
     * 文字列の置換
     * @param str 置換する文字列
     * @param from 置換前文字列
     * @param to 置換後文字列
     */
    std::string& strReplace(std::string& str, const std::string& from, const std::string& to)
	{
        std::string::size_type pos = 0;
        while(pos = str.find(from, pos), pos != std::string::npos){
            str.replace(pos, from.length(), to);
            pos += to.length();
        }
        return str;
    }

    /**
     * 文字列の分割
     * @param dest  格納先
     * @param src   元文字列
     * @param delim 区切り文字
     */
    std::vector<std::string>* SpritString( std::vector<std::string> *dest, const std::string &src, const std::string &delim )
    {
        std::string::size_type start = 0;// デリミタを検索するインデクス番号
        while( true ){
            // デリミタが現れる最初のインデクスを求める
            std::string::size_type end = src.find(delim, start);
            
            // デリミタが見つかった場合
            if(end != std::string::npos){
                dest->push_back(src.substr(start, end - start));
            }
            // デリミタが見つからなかった場合
            else
			{
                // 文末までを格納して返す
                dest->push_back(src.substr(start, src.length() - start));
                break;
            }
            // 次の開始地点へ移動
            start = end + delim.length();
        }
        return dest;
    }

    /**
     * 文字列のトリミング
     * @param src_string    元文字列
     * @param trim_targets  トリミング対象
     */
    std::string TrimmingString(const std::string& src_string, const std::string trim_targets)
    {
        std::string result = src_string;
        std::string::size_type left = src_string.find_first_not_of(trim_targets);
        if ( left != std::string::npos )
        {
            std::string::size_type right = src_string.find_last_not_of(trim_targets);
            result = src_string.substr(left, right - left + 1);
        }
        return result;
    }

	/**
	 * 指定した文字列が、半角か全角か調べる
	 * @param 
	 * @param 戻り値(バイト数)
	 */
	int   getStringWordByte( unsigned char * pWordText )
	{
		if (((*pWordText >= 0x81 && *pWordText <= 0x9f) || (*pWordText >= 0xe0 && *pWordText <= 0xfc)) &&
			((*(pWordText + 1) >= 0x40 && *(pWordText + 1) <= 0x7e) || (*(pWordText + 1) >= 0x80 && *(pWordText + 1) <= 0xfc)))
		{
			return(2);/* 全角 */
		}
		return(1);
	}

	/**
	 * タグを外した文字の長さ(半角)を出す
	 * @param
	 * @return	半角の長さ数値
	 */
	int   getStringLongTag( char * et_str )
	{
		int  RetX = 0;
		unsigned char *  pNowStr;
		pNowStr = (unsigned char*)et_str;

		while (1)
		{
			if (*pNowStr == 0)
				break;

			if (getStringWordByte(pNowStr) == 2) // 半角(1)全角(2)
			{
				RetX += 2;
				pNowStr += 2;
			}
			else {
				if (strncmp((char*)pNowStr, "#n", 2) == 0)
				{
					/*改行コード*/
					pNowStr += 2;
				}
				else  if (*pNowStr == '#')
				{
					/*エスケープシーケンス*/
					pNowStr ++;
					while (1)
					{
						if (*pNowStr == 0){
							return (RetX);
						}
						if (getStringWordByte(pNowStr) == 2) // 半角(1)全角(2)
						{
							pNowStr += 2;
						}
						else{
							if (*pNowStr == ']'){
								pNowStr ++;
								break;
							}
							pNowStr ++;
						}
					}
				}
				else{
					RetX ++;       // その他文字
					pNowStr++;
				}
			}
		}
		return (RetX);
	}

	/**
	 * タグを外した文字数(半角全角区別する)を出す
	 * @param
	 * @return	文字数(半角全角区別する)
	 */
	int   getStringNumTag( char * et_str )
	{
		int   i;
		int   j = 0, kazoe = 0, mojinum = 0;
		char  work_p[3];
		int   str_count = static_cast<int>( strlen(et_str) );

		// 文字数数え
		for (i = 0; i < str_count; i ++ )
		{
			if (et_str[i] == '#' && j == 0) // タグ初めを見つけたら
				j = 1;    // 数えモードに
			if (et_str[i] == ']' || (j == 2 && et_str[i] == 'n'))// タグ閉じ終わりか#nだったら数えるの終了
			{
				j = 0; kazoe++;
			}
			if (j > 0)
			{
				j++;  kazoe++;
			}

			sprintf_s(work_p, "%c%c", et_str[i], et_str[i + 1]);

			if (getStringWordByte((unsigned char *)work_p) == 2) // 半角(1)全角(2)
				i++;
			mojinum++;
		}
		return(mojinum - kazoe);
	}

	/**
	 * 文字数取得
	 * @param	iText	文字列
	 * @param	oNum	１行最大文字数
	 * @param	oLine	行数
	 * @return
	 */
	void    getStringNumLineGet( char* iTxt, int* oNum, int* oLine )
	{
		int	com = 0;
		int	num = 0;	//	文字数

		(*oNum) = 0;	//	最大文字数
		(*oLine) = 1;

		//	コマンド文字数の検索
		for (int i = 0; iTxt[i] != '\0'; i++)
		{
			if (iTxt[i] == '#')
			{
				if (iTxt[i + 1] == 'n')// 改行コマンド
				{
					if ((*oNum) < num)
						(*oNum) = num;
					num = 0;

					if (iTxt[i + 2] == '\0')
					{
						break;
					}
					(*oLine)++;
					i += 2;
				}
				else
				{
					com = 1;// コマンドの証
				}
			}
			else
			{
				if (!com)
					num++;

				if (iTxt[i] == ']')
				{
					com = 0;
				}
			}
		}
		if ((*oNum) < num)	(*oNum) = num;
		(*oNum)++;
		(*oNum) /= 2;
	}

	/**
	 * ミリ秒をフレーム数に変える
	 * @param	msec	カウント
	 * @return	
	 */
	int		getChangeMsecToFrame( int msec )
	{
		if (msec <= 0)
		{
			return	0;
		}
		// 例), msec = 1000 → 1000.0f * 60.0f / 1000.0f = 60.0f
		float	fFrame = (float)msec * 60.0f / 1000.0f;
		int		nFlame = (int)fFrame;

		if( nFlame <= 0 )
		{
			nFlame = 1;
		}
		return nFlame;
	}

	/**
	 * 指定した文字列から拡張子を除いた名前を取得する
	 * @param	szSrcFileFullPath	カウント
	 * @param	szDst		
	 * @param	sizeOut		
	 * @return	
	 */
	char *	getMsGetFileNameWithoutExt( char * szSrcFileFullPath, char * szDst, size_t  sizeOut )
	{
		char * pstr;
		int    nLength;

		nLength = static_cast<int>( strlen( szSrcFileFullPath ));
		if (nLength <= 0 || (unsigned int)nLength >= sizeOut) {
			szDst[0] = '\0';
			return szDst;
		}

		strncpy_s(szDst, sizeOut, szSrcFileFullPath, sizeOut - 1);
		szDst[sizeOut - 1] = '\0';
		pstr = &szSrcFileFullPath[nLength - 1];
		while (1)
		{
			if (*pstr == '.') {
				--nLength;
				break;
			}
			if (isEtcDirectoryFigure(*pstr)) {
				break;
			}
			-- pstr;
			-- nLength;
			if (nLength <= 0) { break; }
		}
		szDst[nLength] = '\0';

		return szDst;
	}

	/**
	 * ディレクトリの区切り記号であるかどうかをチェックする
	 * @param	szSrcFilePath
	 * @return	1 --> ディレクトリの区切り記号である
	 *			0 --> ディレクトリの区切り記号でない
	 */
	bool	isEtcDirectoryFigure( char szCh )
	{
		return (szCh == '\\' || szCh == '/');
	}

	/**
	 * 設定した文字列がSJISかどうかを調べる
	 * @param	*lpSrc
	 * @return
	 */
	bool	isStringCodeSJIS( const char *lpSrc )
	{
		// SJISコードであるか調べる
		bool ret = true;
		unsigned int high, low;
		low = (unsigned int)(*lpSrc) & 0xff;
		high = (unsigned int)(*(lpSrc + 1)) & 0xff;

		if ((((low ^ 0x20) - 0xa1) > 0x3b))
		{
			ret = false;
		}
		else if ((high - 0x40) > 0xbc)
		{
			ret = false;
		}
		return(ret);
	}

	/**
	 * マルチバイト文字かチェック
	 * @param	*pstr
	 * @return
	 */
	bool	isStringMultiByte( const char *pstr )
	{
		if (*pstr == '\0') {
			return 0;
		}
		if (((*pstr >= 0x80 && *pstr <= 0x9F) || (*pstr >= 0xE0 && *pstr <= 0xFC)) &&
			((*(pstr + 1) >= 0x40 && *(pstr + 1) <= 0x7E) || (*(pstr + 1) >= 0x80 && *(pstr + 1) <= 0xFC)))
		{
			return 1;
		}
		return 0;
	}

	/**
	 * 指定した配列の文字列の中から最大の文字数を返す
	 * @param	*arry[]
	 * @param	len_size
	 * @return
	 */
	int		getStrArryElement( char * arry[], int len_size )
	{
		int len = 0;
		for (int i = 0; i < len_size; i++)
		{
			int n = static_cast<int>( strlen(arry[i] ));
			if (len < n) {
				len = n;
			}
		}
		return len;
	}

	/**
	 * 
	 * @param	coefficient
	 * @param	decimal_count
	 * @return
	 */
	bool	getStringReturnCode( char * pStr, int * type )
	{
		if (strncmp(pStr, "#n", 2) == 0) {
			if (type) {
				*type = 1;
			}
			return (true);
		}
		if (strncmp(pStr, "\n", 1) == 0) {
			if (type) {
				*type = 2;
			}
			return (true);
		}
		return (false);
	}

	/**
	 * 有効桁以下を切り捨てる
	 * @param	coefficient
	 * @param	decimal_count
	 * @return
	 */
    float	floorWithDecimalCount( float coefficient, int decimal_count )
    {
        float multipli_num = pow(10.0f,decimal_count);
        coefficient = coefficient * multipli_num;
        coefficient = floorf(coefficient) / multipli_num;
        return coefficient;
    }



}











