#pragma once

//=================================================================================//
/*
	TemplateSingletonClass Sample
*/
//=================================================================================//


/**
 *  @brief  �V���O���g���z���_�[
 */
template <class _Ty>
#if 1
class Singleton
#else
class Singleton final	// �h���N���X�̒�`�֎~
#endif
{
public:
    typedef	_Ty		InstanceType;

public:
	// ����
	static void create(){
		if( _pInstance == nullptr ) {
			_pInstance = new InstanceType();
		}
	}
	// �j��
	static void destroy(){
		if( _pInstance != nullptr ) {
			delete _pInstance;
			_pInstance = nullptr;
		}
	}

	// �C���X�^���X�Q�b�g
	static InstanceType* getInstance( void ){
		return *_pInstance;
	}
	// �C���X�^���X�Q�ƃQ�b�g
	static InstanceType& getInstanceRef( void ){
		return *_pInstance;
	}
	// �C���X�^���X�|�C���^�Q�b�g
	static InstanceType* getInstancePtr( void ){
		return _pInstance;
	}
	static InstanceType* getSingletonPtr( void ){
		if ( !_pInstance ) { _pInstance = new InstanceType(); }
		return _pInstance;
	}

	// �����ς݁H
	static bool isCreate() { return _pInstance != nullptr; };
	// �j���ς݁H
	static bool isDestroy() { return _pInstance == nullptr; };

private:
	// satatic �ň�x�������ێ���������
	/*inline */static InstanceType *   _pInstance;        //!< �B��̃C���X�^���X

protected:
	// �����I�ɏ����ĂȂ��Ă��h���N���X�̃R���X�g���N�^�͊��N���X�̃R���X�g���N�^��K���Ăт܂����Aprivate���ƌĂׂ܂���B
	// ���̂悤�ȃP�[�X�ł͔h��������肵�����Ȃ��̂�friend�w����ł��܂���B
	// �O������g�����Ƃ�z�肵�Ȃ��̂�public�ɂ���̂͂��܂�悭�Ȃ��̂�protected�w��
	Singleton() {}

public:
	~Singleton(){}
	Singleton(Singleton const&) = delete;				/** �R�s�[�R���X�g���N�^�i�g�p�֎~�j */
	Singleton& operator=(Singleton const&) = delete;	/** ������Z�q�i�g�p�֎~�j */
	Singleton(Singleton&&) = delete;					/** copy/move constructor��assgin operator��delete�w�� */
	Singleton& operator=(Singleton&&) = delete;
};

#if 1
template <class _Ty>
typename Singleton<_Ty>::InstanceType* Singleton<_Ty>::_pInstance = nullptr;
#else
template <typename _Ty> _Ty* Singleton<_Ty>::_pInstance = nullptr;
#endif


/* End tSingleton.h */

