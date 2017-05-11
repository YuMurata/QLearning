#pragma once

#include"Agent.h"
#include"Environment.h"



//$$$$QLearningTemplate
//Q学習のテンプレートクラス
//Q学習を行います
//コンストラクタに初期状態とABaseの派生クラスとRBaseの派生クラスとTBaseの派生クラスとQBaseの派生クラスを渡してください
//
//####using型
//なし
//
//####コンストラクタ
//QLearningTemplate
//(
//	const S &s0,
//	Agent<S, A>::pAction &a,
//	Environment<S, A>::pReward &r,
//	Environment<S, A>::pTransition &t,
//	Agent<S, A>::pQFunc &q_func
//)
//
//####純粋仮想関数
//なし
template<typename S,typename A>
class QLearningTemplate:public Config<S,A>
{
private:
	Agent<S, A> agent;
	Environment<S, A> environment;

public:
	QLearningTemplate
	(
		const S &s0,
		typename Agent<S, A>::pAction &a,
		typename Environment<S, A>::pReward &r,
		typename Environment<S, A>::pTransition &t,
		typename Agent<S, A>::pQFunc &q_func
	)
		:agent(s0, a, q_func), environment(s0, t, r) {}

	QLearningTemplate
	(
		const S &s0,
		typename Agent<S, A>::pAction &&a,
		typename Environment<S, A>::pReward &&r,
		typename Environment<S, A>::pTransition &&t,
		typename Agent<S, A>::pQFunc &&q_func
	)
		:agent(s0, a, q_func), environment(s0, t, r) {}

	//learn_num回学習を行う
	void Learn(const int &learn_num)
	{
		S s;
		A a;
		R r;

		s = environment.Get();//状態の取得
		agent.Observe(s);//観測
		for (int i = 0; i < learn_num; ++i)
		{
			a = agent.Action();//行動
			environment.Transition(a);//遷移
			s = environment.Get();//状態の取得
			agent.Observe(s);//観測
			r = environment.Reward();//報酬
			agent.Review(r);//学習
		}
	}

	//Q値を表示する
	void Disp()
	{
		this->agent.QDisp();
	}
};