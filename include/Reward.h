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
//R Value(const S &s)
template<typename S,typename A>
struct RBase :public Config<S>
{
	//���s�ɂ������V��Ԃ�
	//TODO: �h���N���X�Ń��[�U�[����`����
	virtual R Value(const S &s) = 0;
};
