#pragma once
#include"Config.h"

//$$$$RBase
//��V�̊��N���X
//���̃N���X���p�������h���N���X���쐬���Ă�������
//
//####using�^
//�Ȃ�
//
//####�R���X�g���N�^
//�Ȃ�
//
//####�������z�֐�
//R Reward(const S &s)
template<typename S,typename A>
struct RBase :public Config<S,A>
{
	//���s�ɂ������V��Ԃ�
	//TODO: �h���N���X�Ń��[�U�[����`����
	virtual R Reward(const S &s) = 0;
};
