#pragma once

#include"Config.h"

//####using型
//Q = double;
//
//####コンストラクタ
//なし
//
//####純粋仮想関数
//void UpDate(const S &s, const A &a,const double &r,const Q &maxQ)
//Q operator()(const S &s, const A &a)
//void Disp()
template<typename S,typename A>
struct QBase:public Config<S,A>
{
	//状態sにおいて行動aをとる価値qを報酬rと最大行動価値maxQを使って更新する
	virtual void UpDate(const S &s, const A &a, const double &r, const Q &maxQ) = 0;

	//状態sにおいて行動aをとる価値qを返す
	virtual Q Value(const S &s, const A &a) = 0;

	QAList ValueList(const S &s, const As &pos_a)
	{
		using namespace std;

		QAList ret;
		ret.reserve(size(pos_a));

		for (auto &a : pos_a)
		{
			auto q = this->Value(s, a);
			ret.push_back(make_pair(q, a));
		}

		return ret;
	}

	//Q値を表示する
	virtual void Disp() = 0;
};