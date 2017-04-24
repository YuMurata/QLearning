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
//R = double
//pTransition = std::unique_ptr<TBase>
//pReward = std::unique_ptr<RBase>
//
//####�R���X�g���N�^
//Environment(const S &s0, Transition &t, Reward &r)
//
//####�������z�֐�
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