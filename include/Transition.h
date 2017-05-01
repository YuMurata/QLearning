#pragma once

//$$$$TBase
//状態遷移の基底クラス
//このクラスを継承した派生クラスを作成してください
//
//####using型
//なし
//
//####コンストラクタ
//なし
//
//####純粋仮想関数
//S Transition(const S &s,const A &a)
template<typename S,typename A>
struct TBase
{
	//状態sにおいて行動aをとった場合に遷移する状態を返す
	//TODO: 派生クラスでユーザーが定義する
	virtual S Transition(const S &s, const A &a) = 0;
};