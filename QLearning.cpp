// QLearning.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include"QLClass.h"
#include<conio.h>

int main()
{
	google::dense_hash_map<int, double> x; x.set_empty_key(-1);

	auto aho = x.max_bucket_count();
	auto ahoa = x.max_size();
	auto ahob = x.size();

	x[1] = 1;
	x[2] = 2;
	x[3] = 3;

	aho = x.max_bucket_count();
	 ahoa = x.max_size();
	 ahob = x.size();
	 auto fg = sizeof(pair<int, double>);
	 auto sedx = ahob*fg;
	using S = int;
	using A = int;
	using QL = QLClass<S, A>;
	using Q = QL::Q;
	using SA = QL::SA;
	using SAQ = QL::SAQ;

	enum
	{
		UP,
		LEFT,
		DOWN,
		RIGHT,
	};

	const vector<S> s_list =
	{
		  0,1,2,
		3,4,5,6,7,
		  8,9,10,
	};

	const vector<A> a_list =
	{
		UP,LEFT,DOWN,RIGHT,
	};

	QL::FuncR r = [](const S &s)
	{
		Q ret;

		if (s == 3)
		{
			ret=-10.;
		}
		else if(s==7)
		{
			ret= 10.;
		}
		else
		{
			ret= -1.;
		}

		return ret;
	};

	QL::FuncT t = [&s_list](const S &s, const A &a)
	{
		int d[] = { -4,-1,+4,+1, };
		S ret = s_list[s] + d[a];

		auto not_up = ret < 0;
		auto not_down = ret >= 11;
		auto not_left = (d[a] == LEFT) && (s_list[s] == 0 || s_list[s] == 8);
		auto not_right = (d[a] == RIGHT) && (s_list[s] == 2 || s_list[s] == 10);

		if (s_list[s] == 3 || s_list[s] == 7)
		{
			ret = 5;
		}
		else if (not_up || not_down || not_left || not_right)
		{
			ret -= d[a];
		}

		return ret;

	};

	QL::FuncAs as = [&a_list](const S &s)
	{
		vector<A> ret(begin(a_list),end(a_list));
		return ret;
	};

	QL::FuncLoad load = [](const vector<vector<string>> &str)
	{
		vector<SAQ> ret;
		return ret;
	};

	QL::FuncWrite write = [](const QL::QTable &saq,vector<vector<string>> *str)
	{
	};


	QL obj;
	obj.SetFunc(r, t, as, load, write);

	S s = 5;
	A a;

	for (int i = 0; i < 1000; ++i)
	{
		a = obj.Learn(s);
		s = t(s, a);
	}

	obj.Disp();
	_getch();
    return 0;
}

