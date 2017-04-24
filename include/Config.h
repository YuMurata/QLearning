#pragma once

#include<vector>
#include<utility>

template<typename S,typename A>
struct Config
{
	using Q = double;

	using QA = std::pair<Q, A>;
	using QAList = std::vector<QA>;

	using As = std::vector<A>;
};