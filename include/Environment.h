#pragma once

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
	using R = double;

	//####using型
	//なし
	//
	//####コンストラクタ
	//なし
	//
	//####純粋仮想関数
	//S Value(const S &s,const A &a)
	struct TBase
	{
		virtual S Value(const S &s,const A &a) = 0;
	};

	using pTransition = std::unique_ptr<TBase>;

	//####using型
	//なし
	//
	//####コンストラクタ
	//なし
	//
	//####純粋仮想関数
	//R Value(const S &s)
	struct RBase
	{
		virtual R Value(const S &s) = 0;
	};

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
		this->s = this->t->Value(this->s,a);
	}

	R Reward()
	{
		auto ret = this->r->Value(this->s);
		return ret;
	}

	S Get()
	{
		return this->s;
	}
};