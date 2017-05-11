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
//pTransition = std::unique_ptr<TBase>
//pReward = std::unique_ptr<RBase>
//
//####コンストラクタ
//Environment(const S &s0, Transition &t, Reward &r)
//
//####純粋仮想関数
//なし
template<typename S,typename A>
class Environment:public Config<S,A>
{
public:
	using pTransition = std::unique_ptr<TBase<S, A>>;
	using pReward = std::unique_ptr<RBase<S, A>>;

private:
	S s;
	pTransition t;
	pReward r;

public:
	Environment(const S &s0, pTransition &t, pReward &r)
		:s(s0), t(move(t)), r(move(r)) {}

	Environment(const S &s0, pTransition &&t, pReward &&r)
		:s(s0), t(move(t)), r(move(r)) {}

	void Transition(const A &a)
	{
		this->s = this->t->Transition(this->s, a);
	}

	typename R Reward()
	{
		auto ret = this->r->Reward(this->s);
		return ret;
	}

	S Get()
	{
		return this->s;
	}
};