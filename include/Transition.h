#pragma once

//$$$$TBase
//��ԑJ�ڂ̊��N���X
//���̃N���X���p�������h���N���X���쐬���Ă�������
//
//####using�^
//�Ȃ�
//
//####�R���X�g���N�^
//�Ȃ�
//
//####�������z�֐�
//S Transition(const S &s,const A &a)
template<typename S,typename A>
struct TBase
{
	//���s�ɂ����čs��a���Ƃ����ꍇ�ɑJ�ڂ����Ԃ�Ԃ�
	//TODO: �h���N���X�Ń��[�U�[����`����
	virtual S Transition(const S &s, const A &a) = 0;
};