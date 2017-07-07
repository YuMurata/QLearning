#pragma once

#include"Config.h"

//$$$$QBase
//Q�֐��̊��N���X
//���̃N���X���p�������h���N���X���쐬���Ă�������
//
//####using�^
//�Ȃ�
//
//####�R���X�g���N�^
//�Ȃ�
//
//####���z�֐�
//bool Save(const char file_name[])	
//bool Load(const char file_name[])
//
//####�������z�֐�
//void UpDate(const S &s, const A &a,const R &r,const Q &maxQ)
//Q Value(const S &s, const A &a)
//void Disp()
template<typename S,typename A>
struct QBase :public Config<S,A>
{
	//���s�ɂ����čs��a���Ƃ鉿�lq���Vr�ƍő�s�����lmaxQ���g���čX�V����
	//TODO: �h���N���X�Ń��[�U�[����`����
	virtual void UpDate(const S &s, const A &a, const R &r, const Q &maxQ) = 0;

	//���s�ɂ����čs��a���Ƃ鉿�lq��Ԃ�
	//TODO: �h���N���X�Ń��[�U�[����`����
	virtual Q Value(const S &s, const A &a) = 0;

	//Q�l�ƍs����pair�^��vector��Ԃ�
	typename QAList ValueList(const S &s, const As &pos_a)
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
	//TODO: �h���N���X�Ń��[�U�[����`����
	virtual void Disp() = 0;

	//Q�l�̕ۑ�
	virtual bool Save(const char file_name[]) 
	{
		return false;
	}
	
	//Q�l�̓ǂݏo��
	virtual bool Load(const char file_name[])
	{
		return false;
	}

	virtual void Extension() {}
};