#pragma once

#include<memory>

#include"Action.h"
#include"QFunc.h"

//$$$$Agent
//�G�[�W�F���g�N���X
//��Ԃ̊ϑ��ƍs�����s���܂�
//�R���X�g���N�^�ɏ�����Ԃ�ABase�̔h���N���X��QBase�̔h���N���X��n���Ă�������
//
//####using�^
//pQFunc = std::unique_ptr<QBase<S, A>>
//pAction = std::unique_ptr<ABase<S, A>>
//
//####�R���X�g���N�^
//Agent(const S &s0, pAction &a, pQFunc &q_func)
//
//####�������z�֐�
//�Ȃ�
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

	//����������
	//�R���X�g���N�^�ŏ��������Ȃ������ꍇ�p
	void Init(const S &s0, pAction &a, pQFunc &q_func)
	{
		this->new_s = s0;
		this->old_s = s0;
		this->q_func = move(q);
		this->action = move(a);
	}

	//����������
	//�R���X�g���N�^�ŏ��������Ȃ������ꍇ�p
	void Init(const S &s0, pAction &&a, pQFunc &&q_func)
	{
		this->new_s = s0;
		this->old_s = s0;
		this->q_func = move(q);
		this->action = move(a);
	}

	//���s���ϑ�����
	void Observe(const S &s)
	{
		this->old_s = this->new_s;
		this->new_s = s;
	}

	//�C�ӂ̍s�����Ƃ�
	A Action()
	{
		auto pos_a = this->action->Capabilities(this->new_s);
		auto qa_list = this->q_func->ValueList(this->new_s, pos_a);
		this->a = this->action->SelectAction(this->new_s, qa_list);
		return this->a;
	}

	//Q�l���X�V����
	void Review(const typename R &r)
	{
		auto pos_a = this->action->Capabilities(this->new_s);
		auto qa_list = this->q_func->ValueList(this->new_s, pos_a);
		auto best_a = this->action->BestAction(this->new_s, qa_list);
		auto maxQ = this->q_func->Value(this->new_s, best_a);
		this->q_func->UpDate(this->old_s, this->a, r, maxQ);
	}

	//Q�l��\������
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
};