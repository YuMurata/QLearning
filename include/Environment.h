#pragma once

#include<memory>
#include"Transition.h"
#include"Reward.h"

//$$$$Environment
//環境クラス
//状態の遷移と報酬の付与を行います
//コンストラクタに初期状態とTBaseの派生クラスとRBaseの派生クラスを渡してください
//
//####using型
//R = double
//pTransition = std::unique_ptr<TBase>
//pReward = std::unique_ptr<RBase>
//
//####コンストラクタ
//Environment(const S &s0, Transition &t, Reward &r)
//
//####純粋仮想関数
//void Transition(const A &a)
//R Reward()
template<typename S,typename A>
class Environment
{
public:
	using pTransition = std::unique_ptr<TBase>;
	using pReward = std::unique_ptr<RBase>;

private:
	S s;
	pTransition t;
	pReward r;

public:
	Environment(const S &s0, pTransition &t, pReward &r)
		:s(s0), t(move(t)), r(move(r)) {}

	void Transition(const A &a)
	{
		this->s = this->t->Value(this->s, a);
	}

	Config::R Reward()
	{
		auto ret = this->r->Value(this->s);
		return ret;
	}

	S Get()
	{
		return this->s;
	}
};