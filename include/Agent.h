#pragma once

#include<memory>

#include"Action.h"
#include"QFunc.h"

//$$$$Agent
//エージェントクラス
//状態の観測と行動を行います
//コンストラクタに初期状態とABaseの派生クラスとQBaseの派生クラスを渡してください
//
//####using型
//pQFunc = std::unique_ptr<QBase<S, A>>
//pAction = std::unique_ptr<ABase<S, A>>
//
//####コンストラクタ
//Agent(const S &s0, pAction &a, pQFunc &q_func)
//
//####純粋仮想関数
//なし
template<typename S,typename A>
class Agent
{
public:
	using pQFunc = std::unique_ptr<QBase<S, A>>;
	using pAction = std::unique_ptr<ABase<S, A>>;

protected:
	pQFunc q_func;
	pAction action;

	S old_s;
	S new_s;

	A a;

public:
	Agent(const S &s0, pAction &a, pQFunc &q_func)
		:new_s(s0), old_s(s0), q_func(move(q_func)), action(move(a)) {}

	//状態sを観測する
	void Observe(const S &s)
	{
		this->old_s = this->new_s;
		this->new_s = s;
	}

	//任意の行動をとる
	A Action()
	{
		auto pos_a = this->action->Capabilities(this->new_s);
		auto qa_list = this->q_func->ValueList(this->new_s, pos_a);
		this->a = this->action->SelectAction(this->new_s, qa_list);
		return this->a;
	}

	//Q値を更新する
	void Review(const typename Config<A>::R &r)
	{
		auto pos_a = this->action->Capabilities(this->new_s);
		auto qa_list = this->q_func->ValueList(this->new_s, pos_a);
		auto best_a = this->action->BestAction(this->new_s, qa_list);
		auto maxQ = this->q_func->Value(this->new_s, best_a);
		this->q_func->UpDate(this->old_s, this->a, r, maxQ);
	}

	//Q値を表示する
	void QDisp()
	{
		this->q_func->Disp();
	}
};