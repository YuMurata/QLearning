#pragma once

#include<vector>
#include<utility>

//$$$$Config
//�R���t�B�O�N���X
//�K�v��using�^��ݒ肵�܂�
//���ɂ�����K�v�Ȃ�
//
//####using�^
//S = template
//A = template
//Q = double
//R = double
//SA = std::pair<S, A>
//SAQ = std::pair<SA, Q>
//QA = std::pair<Q, A>
//QAList = std::vector<QA>
//As = std::vector<A>
//
//####�R���X�g���N�^
//�Ȃ�
//
//####�������z�֐�
//�Ȃ�
template<typename _S,typename _A>
struct Config
{
	using S = _S;
	using A = _A;

	using Q = double;
	using R = double;

	using SA = std::pair<S, A>;
	using SAQ = std::pair<SA, Q>;

	using QA = std::pair<Q, A>;
	using QAList = std::vector<QA>;

	using As = std::vector<A>;
};