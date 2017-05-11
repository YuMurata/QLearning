#pragma once

#include<memory>
#include"Transition.h"
#include"Reward.h"

//$$$$Environment
//���N���X
//��Ԃ̑J�ڂƕ�V�̕t�^���s���܂�
//�R���X�g���N�^�ɏ�����Ԃ�TBase�̔h���N���X��RBase�̔h���N���X��n���Ă�������
//
//####using�^
//pTransition = std::unique_ptr<TBase>
//pReward = std::unique_ptr<RBase>
//
//####�R���X�g���N�^
//Environment(const S &s0, Transition &t, Reward &r)
//
//####�������z�֐�
//�Ȃ�
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