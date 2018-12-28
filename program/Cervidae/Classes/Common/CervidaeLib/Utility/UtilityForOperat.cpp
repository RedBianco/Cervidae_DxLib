

#include "UtilityForOperat.h"


//===================================================================================
//  UtilityForOperat.cpp
//
//  
//===================================================================================

//-----------------------------------------------------------------------------------
// �֗��֐��Q
//-----------------------------------------------------------------------------------
namespace UtilityForOperat
{
	/**
	 * ��������̉��s�R�[�h�폜
	 * @param src    �Ώە�����
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
	 * UTF-8�̕������𒲂ׂ�
	 * @param	buff UTF-8�̕�����
	 * @return	�����Ŏw�肳�ꂽ������̒���
	 */
	int		getUTF8StrLen( const char *buff )
	{
		// ������NULL�Ȃ璷����0
		if (buff == NULL){ return 0; }

		int count = 0;
		int pos = 0;
		size_t max_bytes = strlen(buff);

		// 3byte�ȏ゠��Ȃ�BOM������\��������̂ŁABOM�������BOM��ǂݔ�΂�
		if (max_bytes >= 3) {
			if (static_cast<unsigned char>(buff[0]) == 0xEF && static_cast<unsigned char>(buff[1]) == 0xBB && static_cast<unsigned char>(buff[2]) == 0xBF) {
				pos += 3;
			}
		}

		// ���������J�E���g����
		while (pos < max_bytes) {
			++ count;
			// 1�o�C�g�����̏ꍇ�A�ǂݎ��ʒu��1�i�߂�
			if ((buff[pos] & 0x80) == 0) {
				++pos;
			}
			// �����o�C�g�����̏ꍇ�A�ǂݎ��ʒu���o�C�g�����i�߂�
			else {
				for(char tmp = buff[pos] & 0xfc; (tmp & 0x80); tmp = tmp << 1) {
					++ pos;
				}
			}
		}
		return count;
	}

	/**
	 * UTF-8�̕������𒲂ׂ�(���p�l����)
	 * @param	buff UTF-8�̕�����
	 * @return	�����Ŏw�肳�ꂽ������̒���(���p��0.5�Ƃ��Ă�)
	 */
	float	getUTF8StrLenSingleByte( const char *buff )
	{
		// ������NULL�Ȃ璷����0
		if (buff == NULL) { return 0; }

		float count = 0;
		int pos = 0;
		size_t max_bytes = strlen(buff);

		// 3byte�ȏ゠��Ȃ�BOM������\��������̂ŁABOM�������BOM��ǂݔ�΂�
		if (max_bytes >= 3) {
			if (static_cast<unsigned char>(buff[0]) == 0xEF && 
				static_cast<unsigned char>(buff[1]) == 0xBB && 
				static_cast<unsigned char>(buff[2]) == 0xBF) {
				pos += 3;
			}
		}

		// ���������J�E���g����
		while (pos < max_bytes) {
			// 1�o�C�g�����̏ꍇ�A�ǂݎ��ʒu��1�i�߂�
			if ((buff[pos] & 0x80) == 0) {
				++ pos;
				count += 0.5f;
			}
			// �����o�C�g�����̏ꍇ�A�ǂݎ��ʒu���o�C�g�����i�߂�
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
	 * UTF-8���������o�C�g���������ׂ�
	 * @param p UTF-8�̕���(1����)
	 * @return �����Ŏw�肳�ꂽ������byte��
	 */
	int		getByteInUTF8Char( const char* p )
	{
		int byte = 0;

		// �ŏ���1�ƂȂ�bit������
		for (int i = 0; i < 6; ++i) {
			if (((*p >> (7 - i)) & 0x01) == 0) {
				byte = i;
				break;
			}
		}

		// 10����n�܂�擪�o�C�g�͑��݂��Ȃ�
		if (byte == 1) {
			return -2;
		}
		// 0����n�܂鎞�́A1byte��1������\�����Ƃ��l�������v�Z
		else if (byte != 0) {
			-- byte;
		}

		// 2�o�C�g�ڈȍ~�́A10����n�܂�r�b�g�p�^�[���łȂ���΂Ȃ�Ȃ�
		for (int i = 1; i < byte; ++i) {
			if (((p[i] >> 6) & 0x03) != 0x02) {
				return -3; // �r�b�g�p�^�[���̕s��v
			}
		}
		return byte + 1;
	}

    /*!
     * ������Ɋ܂܂��w�肳�ꂽ������̐���Ԃ�
     * @param[in] s ���̕�����
     * @param[in] c ����������
     * @return �܂܂�鐔
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
        // �Ō�̕����񏜋�
        if( s.rfind(c) == s.size()-n ){
            count --;
        }
        return count;
    }

    /**
     * std::string����double�ւ̕ϊ�
     * @param str �ϊ�������������
     * @return �ϊ����ꂽ���l
     */
    double	stringToDouble( const std::string& str )
	{
        double result = std::strtod( str.data(), NULL );
        return result;
    }
    
    /**
     * double����std::string�ւ̕ϊ�
     * @param d �ϊ����������l
     * @return �ϊ����ꂽ������
     */
    std::string doubleToString(double d)
	{
        std::ostringstream oss;
        oss << d;
        std::string result( oss.str() );
        return result;
    }

	/**
	 * std::string����int�ւ̕ϊ�
	 * @param str �ϊ�������������
	 * @return �ϊ����ꂽ���l
	 */
	double	stringToInteger(const std::string& str)
	{
		double result = std::strtod(str.data(), NULL);
		return result;
	}

	/**
	 * int����std::string�ւ̕ϊ�
	 * @param str �ϊ����������l
	 * @return �ϊ����ꂽ������
	 */
	std::string integerToString( int i )
	{
		char buff[256] = { 0 };
		snprintf(buff, sizeof(buff), "%d", i);
		return std::string(buff);
	}

    /**
     * std::string����bigint�ւ̕ϊ�
     * @param str �ϊ�������������
     * @return �ϊ����ꂽ���l
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
     * bigint����std::string�ւ̕ϊ�
     * @param str �ϊ����������l
     * @return �ϊ����ꂽ������
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
     * ������̒u��
     * @param str �u�����镶����
     * @param from �u���O������
     * @param to �u���㕶����
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
     * ������̕���
     * @param dest  �i�[��
     * @param src   ��������
     * @param delim ��؂蕶��
     */
    std::vector<std::string>* SpritString( std::vector<std::string> *dest, const std::string &src, const std::string &delim )
    {
        std::string::size_type start = 0;// �f���~�^����������C���f�N�X�ԍ�
        while( true ){
            // �f���~�^�������ŏ��̃C���f�N�X�����߂�
            std::string::size_type end = src.find(delim, start);
            
            // �f���~�^�����������ꍇ
            if(end != std::string::npos){
                dest->push_back(src.substr(start, end - start));
            }
            // �f���~�^��������Ȃ������ꍇ
            else
			{
                // �����܂ł��i�[���ĕԂ�
                dest->push_back(src.substr(start, src.length() - start));
                break;
            }
            // ���̊J�n�n�_�ֈړ�
            start = end + delim.length();
        }
        return dest;
    }

    /**
     * ������̃g���~���O
     * @param src_string    ��������
     * @param trim_targets  �g���~���O�Ώ�
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
	 * �w�肵�������񂪁A���p���S�p�����ׂ�
	 * @param 
	 * @param �߂�l(�o�C�g��)
	 */
	int   getStringWordByte( unsigned char * pWordText )
	{
		if (((*pWordText >= 0x81 && *pWordText <= 0x9f) || (*pWordText >= 0xe0 && *pWordText <= 0xfc)) &&
			((*(pWordText + 1) >= 0x40 && *(pWordText + 1) <= 0x7e) || (*(pWordText + 1) >= 0x80 && *(pWordText + 1) <= 0xfc)))
		{
			return(2);/* �S�p */
		}
		return(1);
	}

	/**
	 * �^�O���O���������̒���(���p)���o��
	 * @param
	 * @return	���p�̒������l
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

			if (getStringWordByte(pNowStr) == 2) // ���p(1)�S�p(2)
			{
				RetX += 2;
				pNowStr += 2;
			}
			else {
				if (strncmp((char*)pNowStr, "#n", 2) == 0)
				{
					/*���s�R�[�h*/
					pNowStr += 2;
				}
				else  if (*pNowStr == '#')
				{
					/*�G�X�P�[�v�V�[�P���X*/
					pNowStr ++;
					while (1)
					{
						if (*pNowStr == 0){
							return (RetX);
						}
						if (getStringWordByte(pNowStr) == 2) // ���p(1)�S�p(2)
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
					RetX ++;       // ���̑�����
					pNowStr++;
				}
			}
		}
		return (RetX);
	}

	/**
	 * �^�O���O����������(���p�S�p��ʂ���)���o��
	 * @param
	 * @return	������(���p�S�p��ʂ���)
	 */
	int   getStringNumTag( char * et_str )
	{
		int   i;
		int   j = 0, kazoe = 0, mojinum = 0;
		char  work_p[3];
		int   str_count = static_cast<int>( strlen(et_str) );

		// ����������
		for (i = 0; i < str_count; i ++ )
		{
			if (et_str[i] == '#' && j == 0) // �^�O���߂���������
				j = 1;    // �������[�h��
			if (et_str[i] == ']' || (j == 2 && et_str[i] == 'n'))// �^�O���I��肩#n�������琔����̏I��
			{
				j = 0; kazoe++;
			}
			if (j > 0)
			{
				j++;  kazoe++;
			}

			sprintf_s(work_p, "%c%c", et_str[i], et_str[i + 1]);

			if (getStringWordByte((unsigned char *)work_p) == 2) // ���p(1)�S�p(2)
				i++;
			mojinum++;
		}
		return(mojinum - kazoe);
	}

	/**
	 * �������擾
	 * @param	iText	������
	 * @param	oNum	�P�s�ő啶����
	 * @param	oLine	�s��
	 * @return
	 */
	void    getStringNumLineGet( char* iTxt, int* oNum, int* oLine )
	{
		int	com = 0;
		int	num = 0;	//	������

		(*oNum) = 0;	//	�ő啶����
		(*oLine) = 1;

		//	�R�}���h�������̌���
		for (int i = 0; iTxt[i] != '\0'; i++)
		{
			if (iTxt[i] == '#')
			{
				if (iTxt[i + 1] == 'n')// ���s�R�}���h
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
					com = 1;// �R�}���h�̏�
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
	 * �~���b���t���[�����ɕς���
	 * @param	msec	�J�E���g
	 * @return	
	 */
	int		getChangeMsecToFrame( int msec )
	{
		if (msec <= 0)
		{
			return	0;
		}
		// ��), msec = 1000 �� 1000.0f * 60.0f / 1000.0f = 60.0f
		float	fFrame = (float)msec * 60.0f / 1000.0f;
		int		nFlame = (int)fFrame;

		if( nFlame <= 0 )
		{
			nFlame = 1;
		}
		return nFlame;
	}

	/**
	 * �w�肵�������񂩂�g���q�����������O���擾����
	 * @param	szSrcFileFullPath	�J�E���g
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
	 * �f�B���N�g���̋�؂�L���ł��邩�ǂ������`�F�b�N����
	 * @param	szSrcFilePath
	 * @return	1 --> �f�B���N�g���̋�؂�L���ł���
	 *			0 --> �f�B���N�g���̋�؂�L���łȂ�
	 */
	bool	isEtcDirectoryFigure( char szCh )
	{
		return (szCh == '\\' || szCh == '/');
	}

	/**
	 * �ݒ肵��������SJIS���ǂ����𒲂ׂ�
	 * @param	*lpSrc
	 * @return
	 */
	bool	isStringCodeSJIS( const char *lpSrc )
	{
		// SJIS�R�[�h�ł��邩���ׂ�
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
	 * �}���`�o�C�g�������`�F�b�N
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
	 * �w�肵���z��̕�����̒�����ő�̕�������Ԃ�
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
	 * �L�����ȉ���؂�̂Ă�
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











