#pragma once

#include"Config.h"

//####using�^
//Q = double;
//
//####�R���X�g���N�^
//�Ȃ�
//
//####�������z�֐�
//void UpDate(const S &s, const A &a,const double &r,const Q &maxQ)
//Q operator()(const S &s, const A &a)
//void Disp()
template<typename S,typename A>
struct QBase:public Config<S,A>
{
	//���s�ɂ����čs��a���Ƃ鉿�lq���Vr�ƍő�s�����lmaxQ���g���čX�V����
	virtual void UpDate(const S &s, const A &a, const double &r, const Q &maxQ) = 0;

	//���s�ɂ����čs��a���Ƃ鉿�lq��Ԃ�
	virtual Q Value(const S &s, const A &a) = 0;

	QAList ValueList(const S &s, const As &pos_a)
	{
		using namespace std;

		QAList ret;
		ret.reserve(size(pos_a));

		for (auto &a : pos_a)
		{
			auto q = this->Value(s, a);
			ret.push_back(make_pair(q, a));
		}

		return ret;
	}

	//Q�l��\������
	virtual void Disp() = 0;
};