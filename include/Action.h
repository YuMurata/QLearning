#pragma once

#include<algorithm>
#include"Config.h"

//$$$$ABase
//�s���̊��N���X
//���̃N���X���p�������h���N���X���쐬���Ă�������
//
//####using�^
//�Ȃ�
//
//####�R���X�g���N�^
//�Ȃ�
//
//####�������z�֐�
//virtual As Capabilities(const S &s)
//virtual A SelectAction(const S &s, const QAList &qa_list)
template<typename S,typename A>
struct ABase :public Config<S,A>
{
	//�\�ȍs����Ԃ�
	//TODO: �h���N���X�Ń��[�U�[����`����
	virtual As Capabilities(const S &s) = 0;

	//�C�ӂ̍s����Ԃ�
	//TODO: �h���N���X�Ń��[�U�[����`����
	virtual A SelectAction(const S &s, const QAList &qa_list) = 0;

	//�ł�Q�l�̍����s����Ԃ�
	A BestAction(const S &s, const QAList &qa_list)
	{
		auto ret = max_element(begin(qa_list), end(qa_list))->second;
		return ret;
	}
};