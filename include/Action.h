#pragma once

#include<algorithm>
#include"Config.h"

//$$$$ABase
//行動の基底クラス
//このクラスを継承した派生クラスを作成してください
//
//####using型
//なし
//
//####コンストラクタ
//なし
//
//####純粋仮想関数
//virtual As Capabilities(const S &s)
//virtual A SelectAction(const S &s, const QAList &qa_list)
template<typename S,typename A>
struct ABase :public Config<S,A>
{
	//可能な行動を返す
	//TODO: 派生クラスでユーザーが定義する
	virtual As Capabilities(const S &s) = 0;

	//任意の行動を返す
	//TODO: 派生クラスでユーザーが定義する
	virtual A SelectAction(const S &s, const QAList &qa_list) = 0;

	//最もQ値の高い行動を返す
	A BestAction(const S &s, const QAList &qa_list)
	{
		auto ret = max_element(begin(qa_list), end(qa_list))->second;
		return ret;
	}
};