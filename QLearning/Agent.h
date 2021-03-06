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
class Agent :public Config<S,A>
{
public:
	using pQFunc = std::unique_ptr<QBase<S, A>>;
	using pAction = std::unique_ptr<ABase<S, A>>;
	

private:
	pQFunc q_func;
	pAction action;

	S old_s;
	S new_s;

	A a;

public:
	Agent() {}

	Agent(const S &s0, pAction &a, pQFunc &q_func)
		:new_s(s0), old_s(s0), q_func(move(q_func)), action(move(a)) {}

	Agent(const S &s0, pAction &&a, pQFunc &&q_func)
		:new_s(s0), old_s(s0), q_func(move(q_func)), action(move(a)) {}

	//初期化する
	//コンストラクタで初期化しなかった場合用
	void Init(const S &s0, pAction &a, pQFunc &q_func)
	{
		this->new_s = s0;
		this->old_s = s0;
		this->q_func = move(q);
		this->action = move(a);
	}

	//初期化する
	//コンストラクタで初期化しなかった場合用
	void Init(const S &s0, pAction &&a, pQFunc &&q_func)
	{
		this->new_s = s0;
		this->old_s = s0;
		this->q_func = move(q);
		this->action = move(a);
	}

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
	void Review(const typename R &r)
	{
		auto pos_a = this->action->Capabilities(this->new_s);
		auto qa_list = this->q_func->ValueList(this->new_s, pos_a);
		auto best_a = this->action->BestAction(this->new_s, qa_list);
		auto maxQ = this->q_func->Value(this->new_s, best_a);
		this->q_func->UpDate(this->old_s, this->a, r, maxQ);
	}

	//任意の
	//遷移前の状態old_s
	//行動a
	//遷移後の状態new_s
	//報酬r
	//を用いてQ値を更新する
	void Review(const typename S &old_s,const typename A &a,const typename S &new_s,const typename R &r)
	{
		auto pos_a = this->action->Capabilities(new_s);
		auto qa_list = this->q_func->ValueList(new_s, pos_a);
		auto best_a = this->action->BestAction(new_s, qa_list);
		auto maxQ = this->q_func->Value(new_s, best_a);
		this->q_func->UpDate(old_s, a, r, maxQ);
	}

	void BatchReview(const std::vector<typename QBase<S,A>::Sampling> &samples,const int &batch_size)
	{
		this->q_func->BatchUpDate(samples,batch_size);
	}

	//Q値を表示する
	void QDisp()
	{
		this->q_func->Disp();
	}

	bool Save(const char file_name[])const
	{
		return this->q_func->Save(file_name);
	}

	bool Load(const char file_name[])const
	{
		return this->q_func->Load(file_name);
	}

	void Extension(void)
	{
		this->q_func->Extension();
	}
};