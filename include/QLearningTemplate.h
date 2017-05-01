#pragma once

#include"Agent.h"
#include"Environment.h"



//$$$$QLearningTemplate
//Q�w�K�̃e���v���[�g�N���X
//Q�w�K���s���܂�
//�R���X�g���N�^�ɏ�����Ԃ�ABase�̔h���N���X��RBase�̔h���N���X��TBase�̔h���N���X��QBase�̔h���N���X��n���Ă�������
//
//####using�^
//�Ȃ�
//
//####�R���X�g���N�^
//QLearningTemplate
//(
//	const S &s0,
//	Agent<S, A>::pAction &a,
//	Environment<S, A>::pReward &r,
//	Environment<S, A>::pTransition &t,
//	Agent<S, A>::pQFunc &q_func
//)
//
//####�������z�֐�
//�Ȃ�
template<typename S,typename A>
class QLearningTemplate
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

	//learn_num��w�K���s��
	void Learn(const int &learn_num)
	{
		S s;
		A a;
		Config<S>::R r;

		s = environment.Get();//��Ԃ̎擾
		agent.Observe(s);//�ϑ�
		for (int i = 0; i < learn_num; ++i)
		{
			a = agent.Action();//�s��
			environment.Transition(a);//�J��
			s = environment.Get();//��Ԃ̎擾
			agent.Observe(s);//�ϑ�
			r = environment.Reward();//��V
			agent.Review(r);//�w�K
		}
	}

	//Q�l��\������
	void Disp()
	{
		this->agent.QDisp();
	}
};