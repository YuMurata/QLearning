#pragma once

#include<vector>
#include<utility>

//$$$$Config
//�R���t�B�O�N���X
//�K�v��using�^��ݒ肵�܂�
//���ɂ�����K�v�Ȃ�
//
//####using�^
//Q = double
//R = double
//QA = std::pair<Q, A>
//QAList = std::vector<QA>
//As = std::vector<A>
//
//####�R���X�g���N�^
//�Ȃ�
//
//####�������z�֐�
//�Ȃ�
template<typename A>
struct Config
{
	using Q = double;
	using R = double;

	using QA = std::pair<Q, A>;
	using QAList = std::vector<QA>;

	using As = std::vector<A>;
};