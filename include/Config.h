#pragma once

#include<vector>
#include<utility>

//$$$$Config
//コンフィグクラス
//必要なusing型を設定します
//特にいじる必要なし
//
//####using型
//S = template
//A = template
//Q = double
//R = double
//QA = std::pair<Q, A>
//QAList = std::vector<QA>
//As = std::vector<A>
//
//####コンストラクタ
//なし
//
//####純粋仮想関数
//なし
template<typename _S,typename _A>
struct Config
{
	using S = _S;
	using A = _A;

	using Q = double;
	using R = double;

	using QA = std::pair<Q, A>;
	using QAList = std::vector<QA>;

	using As = std::vector<A>;
};