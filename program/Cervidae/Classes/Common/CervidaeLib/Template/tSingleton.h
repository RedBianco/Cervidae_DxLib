#pragma once

//=================================================================================//
/*
	TemplateSingletonClass Sample
*/
//=================================================================================//


/**
 *  @brief  シングルトンホルダー
 */
template <class _Ty>
#if 1
class Singleton
#else
class Singleton final	// 派生クラスの定義禁止
#endif
{
public:
    typedef	_Ty		InstanceType;

public:
	// 生成
	static void create(){
		if( _pInstance == nullptr ) {
			_pInstance = new InstanceType();
		}
	}
	// 破棄
	static void destroy(){
		if( _pInstance != nullptr ) {
			delete _pInstance;
			_pInstance = nullptr;
		}
	}

	// インスタンスゲット
	static InstanceType* getInstance( void ){
		return *_pInstance;
	}
	// インスタンス参照ゲット
	static InstanceType& getInstanceRef( void ){
		return *_pInstance;
	}
	// インスタンスポインタゲット
	static InstanceType* getInstancePtr( void ){
		return _pInstance;
	}
	static InstanceType* getSingletonPtr( void ){
		if ( !_pInstance ) { _pInstance = new InstanceType(); }
		return _pInstance;
	}

	// 生成済み？
	static bool isCreate() { return _pInstance != nullptr; };
	// 破棄済み？
	static bool isDestroy() { return _pInstance == nullptr; };

private:
	// satatic で一度作ったら保持し続ける
	/*inline */static InstanceType *   _pInstance;        //!< 唯一のインスタンス

protected:
	// 明示的に書いてなくても派生クラスのコンストラクタは基底クラスのコンストラクタを必ず呼びますが、privateだと呼べません。
	// このようなケースでは派生先を限定したくないのでfriend指定もできません。
	// 外部から使うことを想定しないのでpublicにするのはあまりよくないのでprotected指定
	Singleton() {}

public:
	~Singleton(){}
	Singleton(Singleton const&) = delete;				/** コピーコンストラクタ（使用禁止） */
	Singleton& operator=(Singleton const&) = delete;	/** 代入演算子（使用禁止） */
	Singleton(Singleton&&) = delete;					/** copy/move constructorとassgin operatorをdelete指定 */
	Singleton& operator=(Singleton&&) = delete;
};

#if 1
template <class _Ty>
typename Singleton<_Ty>::InstanceType* Singleton<_Ty>::_pInstance = nullptr;
#else
template <typename _Ty> _Ty* Singleton<_Ty>::_pInstance = nullptr;
#endif


/* End tSingleton.h */

