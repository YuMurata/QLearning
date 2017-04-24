#pragma once
#include"Config.h"

//$$$$RBase
//報酬の基底クラス
//このクラスを継承した派生クラスを作成してください
//
//####using型
//なし
//
//####コンストラクタ
//なし
//
//####純粋仮想関数
//R Value(const S &s)
template<typename S,typename A>
struct RBase :public Config<S>
{
	//状態sにおける報酬を返す
	//TODO: 派生クラスでユーザーが定義する
	virtual R Value(const S &s) = 0;
};
