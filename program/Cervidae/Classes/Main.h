
#pragma once


//=================================================================================//
//  Main.h
//  Cervidae
//
//  Created by kashima akihiro on 2018/10/15.
//=================================================================================//
// −	Windows7 64bit
// −	VisualStudio 2019 Community
// −	DXライブラリ					<DxLib_VC3.21b>
// −	CRI ADX2LE                      <>
// −	Effekseer For DXライブラリ		<1.43d>
// −	Lua                             <>

typedef struct {
	int		m_RenderW;
	int		m_RenderH;
} ObjectSize;

typedef struct {
	int		m_RenderX;
	int		m_RenderY;
} ObjectPoint;

/*
# 概要
 *

# 内容
 *

# テスト内容
- [ ] XXXXXXXX
- [ ] XXXXXXXX

# 補足
*/

/**
【補足】
○ヘッダーファイルにヘッダーを不用意に書く
お互いがお互いを呼び合ってどうにもならなくなる。
ヘッダの中で他のクラス型を使用したい場合は
class AAAAA;
とすればコンパイルは通る
○不完全な型は使用できません
→　ヘッダの#include忘れの可能性
○error C2236: 予期しない 'struct' 'structName' です
たいていは、直前のインクルードファイルの最後がおかしい
構造体の最後は }；
○error C2258: 純粋仮想関数の宣言に構文上の誤りがあります、'=0' でなければなりません。
たいていは、インクルードファイルのカッコの構成が合っていない。
○error C2653: 'className' : 識別子がｸﾗｽ名でも名前空間名でもありません。
たいていは、インクルードファイルの指定モレ
○error C2629: 'class className (' は不正です。
クラスの中に、未定義の型があった場合にもある。class や、enum型に注意



*/



/* End Main.h */



/*
・E0167	型 "const char *" の引数は型 "char *" のパラメーターと互換性がありません
文字列リテラルを単なるcharポインタに設定しようとすると出る


// _dialogPinkPlaneに指定の子が存在するかチェックしたらその子が_dialogPinkPlaneの何番目にChildされているか取得して
// そのインデックスの子を削除する
const object = this._dialogPinkPlane.getChildByName( "_emptyText" );
if ( object ) {
	const removeIndex = this._dialogPinkPlane.getChildIndex( object );
	this._dialogPinkPlane.removeChildAt( removeIndex );
}


*/




