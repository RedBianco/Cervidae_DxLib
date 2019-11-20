#pragma once

//===================================================================================
//  UtilityForOperat.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/12/13.
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
	void	removeLineFeed( std::string &str );

	/**
	 * UTF-8�̕������𒲂ׂ�
	 * @param	buff UTF-8�̕�����
	 * @return	�����Ŏw�肳�ꂽ������̒���
	 */
	const int	getUTF8StrLen( const char *buff );
    
	/**
	 * UTF-8�̕������𒲂ׂ�(���p�l����)
	 * @param	buff UTF-8�̕�����
	 * @return	�����Ŏw�肳�ꂽ������̒���(���p��0.5�Ƃ��Ă�)
	 */
	const float	getUTF8StrLenSingleByte( const char *buff );

    /**
     * UTF-8���������o�C�g���������ׂ�
     * @param p UTF-8�̕���(1����)
     * @return �����Ŏw�肳�ꂽ������byte��
     */
    int		getByteInUTF8Char( const char* p );

    /*!
     * ������Ɋ܂܂��w�肳�ꂽ������̐���Ԃ�
     * @param[in] s ���̕�����
     * @param[in] c ����������
     * @return �܂܂�鐔
     */
    int		getCountString( std::string &s, int offset, std::string c );

	/**
	 * std::string����double�ւ̕ϊ�
	 * @param	str �ϊ�������������
	 * @return	�ϊ����ꂽ���l
	 */
	double	stringToDouble( const std::string& str );

	/**
	 * int����std::string�ւ̕ϊ�
	 * @param	d �ϊ����������l
	 * @return	�ϊ����ꂽ������
	 */
	std::string  doubleToString( double d );

    /**
     * std::string����int�ւ̕ϊ�
     * @param str �ϊ�������������
     * @return �ϊ����ꂽ���l
     */
	double	stringToInteger( const std::string& str );
    
    /**
     * int����std::string�ւ̕ϊ�
     * @param str �ϊ����������l
     * @return �ϊ����ꂽ������
     */
    std::string integerToString( int i );

	/**
	 * std::string����bigint�ւ̕ϊ�
	 * @param str �ϊ�������������
	 * @return �ϊ����ꂽ���l
	 */
	long long stringToBigint(const std::string& str);

	/**
	 * bigint����std::string�ւ̕ϊ�
	 * @param str �ϊ����������l
	 * @return �ϊ����ꂽ������
	 */
	std::string bigintToString(long long i);

	/**
	 * unsigned long����std::string�ւ̕ϊ�
	 * @param str �ϊ����������l
	 * @return �ϊ����ꂽ������
	 */
	std::string ulongToString(unsigned long l);

	/**
	 * ������̒u��
	 * @param str �u�����镶����
	 * @param from �u���O������
	 * @param to �u���㕶����
	 */
	std::string& strReplace(std::string& str, const std::string& from, const std::string& to);

	/**
	 * ������̕���
	 * @param dest  �i�[��
	 * @param src   ��������
	 * @param delim ��؂蕶��
	 */
	std::vector<std::string>* SpritString(std::vector<std::string> *dest, const std::string &src, const std::string &delim);

	/**
	 * ������̃g���~���O
	 * @param src_string    ��������
	 * @param trim_targets  �g���~���O�Ώ�
	 */
	std::string TrimmingString(const std::string& src_string, const std::string trim_targets = " \t\r\n");

	/**
	 * �w�肵�������񂪁A���p���S�p�����ׂ�
	 * @param 
	 * @param �߂�l(�o�C�g��)
	 */
	int		getStringWordByte( unsigned char * pWordText );

	/**
	 * �^�O���O���������̒���(���p)���o��
	 * @param	
	 * @return	���p�̒������l
	 */
	const int	getStringLongTag( char * et_str );

	/**
	 * �^�O���O����������(���p�S�p��ʂ���)���o��
	 * @param	
	 * @return	������(���p�S�p��ʂ���)
	 */
	const int	getStringNumTag( char * et_str );

	/**
	 * �������擾
	 * @param	iText	������
	 * @param	oNum	�P�s�ő啶����
	 * @param	oLine	�s��
	 * @return	
	 */
	void    getStringNumLineGet(char* iTxt, int* oNum, int* oLine);

	/**
	 * �~���b���t���[�����ɕς���
	 * @param	msec	�J�E���g
	 * @return	
	 */
	int		getChangeMsecToFrame( int msec );

	/**
	 * �w�肵�������񂩂�g���q�����������O���擾����
	 * @param	szSrcFileFullPath
	 * @param	szDst		
	 * @param	sizeOut		
	 * @return	
	 */
	char *	getMsGetFileNameWithoutExt( char * szSrcFileFullPath, char * szDst, size_t  sizeOut );
	
	/**
	 * �f�B���N�g���̋�؂�L���ł��邩�ǂ������`�F�b�N����
	 * @param	szSrcFilePath
	 * @return	
	 */
	const bool	isEtcDirectoryFigure( char szCh );
	
	/**
	 * �ݒ肵��������SJIS���ǂ����𒲂ׂ�
	 * @param
	 * @return
	 */
	const bool	isStringCodeSJIS( const char *lpSrc );

	/**
	 * �}���`�o�C�g�������`�F�b�N
	 * @param
	 * @return
	 */
	const bool	isStringMultiByte( const char *pstr);

	/**
	 * �w�肵���z��̕�����̒�����ő�̕�������Ԃ�
	 * @param	*arry[]
	 * @param	len_size
	 * @return
	 */
	const int	getStringArryElement( char* arry[], int len_size );

	/**
	 * �����̕�����̒�������Ԃ�
	 * @param
	 * @param
	 * @return
	 */
	const char* getStringMaxLen( const char* strx, const char* stry );
	/**
	 * �Z�b�g��������������̒������Ԓ���������̕�������Ԃ�
	 * @param
	 * @param
	 * @return
	 */
	const char* getStringArryMaxLen( std::vector<std::string> arry );

	/**
	 * �L�����ȉ���؂�̂Ă�
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
	 * ���胏�[�h��ݒ蕶���ɒu������( %Value% )
	 * @param	char* baseText
	 * @param	int replaceValue
	 * @return
	 */
	const std::string	getReplaceTextValue( const char* baseText, int replaceValue, bool isComma = false );

	/**
	 * ���胏�[�h��ݒ蕶���ɒu������( %text% )
	 * @param	char* baseText
	 * @param	char* setText
	 * @return
	 */
	const std::string	getReplaceText( const char* baseText, const char* setText, bool isComma = false );
}





/* End UtilityForOperat.h */

