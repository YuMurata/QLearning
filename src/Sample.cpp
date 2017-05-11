// QLearning.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include"../include/Agent.h"
#include"../include/Environment.h"

#include"../include/QLearningTemplate.h"

#include<map>
#include<random>
#include<iostream>
#include<conio.h>

using namespace std;

//迷路問題を解く
//行動は上下左右{-4,4,-1,1}の4通り
//状態は0～10の11通り
//   0, 1, 2,
//3, 4, 5, 6, 7,
//   8, 9, 10,
//
//5がスタート、3,7がゴール
//報酬は
//3=-10、7=-10
//他は-1
//
int main()
{
	//SとAの設定
	using S = int;
	using A = int;

	//行動の設定
	enum ACT
			{
				UP,
				LEFT,
				DOWN,
				RIGHT,
			};

	//QTableの定義
	//今回はstd::mapを使う
	struct QTable :public QBase<S, A>
	{
		using SA = std::pair<S, A>;

		map<SA, Q> table;
		void UpDate(const S &s, const A &a, const double &r, const Q &maxQ)override
		{
			auto learn_rate = 0.5;
			auto discount = 0.8;
			auto key = make_pair(s, a);
			auto &q = this->table[key];

			q = (1 - learn_rate)*q + learn_rate*(r + discount*maxQ);
		}

		Q Value(const S &s, const A &a)override
		{
			auto key = make_pair(s, a);
			auto ret = this->table[key];
			return ret;
		}

		void Disp()override
		{
			for (auto &i : this->table)
			{
				auto sa = i.first;

				auto s = sa.first;
				auto a = sa.second;
				auto q = i.second;

				auto tab = "\t";

				cout << "s:" << s << tab;
				cout << "a:" << a << tab;
				cout << "q:" << q << endl;

				cout << endl;
			}
		}
	};

	//Exproleの定義
	//今回はε-greedy法を使う
	struct Exprole :public ABase<S, A>
	{
	public:
		As Capabilities(const S &s)
		{
			As ret{ UP,LEFT,DOWN,RIGHT };
			return ret;
		}

		A SelectAction(const S &s, const QAList &qa_list)override
		{
			auto e = 0.5;
			static random_device rnd;
			static mt19937 mt(rnd());
			static uniform_real_distribution<> obj(0, 1);

			auto x = obj(mt);
			if (x < e)
			{
				auto ret = this->BestAction(s, qa_list);
				return ret;
			}
			else
			{
				auto pos_a = this->Capabilities(s);
				std::shuffle(begin(pos_a), end(pos_a), mt);
				auto ret = pos_a.front();

				return ret;
			}
		}
	};

	//Mazeの定義
	//上下左右に遷移する
	struct Maze :public TBase<S, A>
	{
		S Transition(const S &s, const A &a)override
		{
			const vector<S> s_list =
			{
				  0,1,2,
				3,4,5,6,7,
				  8,9,10,
			};

			int d[] = { -4,-1,+4,+1, };
			S ret = s_list[s] + d[a];

			auto not_up = ret < 0;
			auto not_down = ret >= 11;
			auto not_left = (a == LEFT) && (s_list[s] == 0 || s_list[s] == 8);
			auto not_right = (a == RIGHT) && (s_list[s] == 2 || s_list[s] == 10);

			if (s_list[s] == 3 || s_list[s] == 7)
			{
				ret = 5;
			}
			else if (not_up || not_down || not_left || not_right)
			{
				ret -= d[a];
			}

			return ret;
		}
	};

	//Fasterの定義
	//状態によって報酬を付与する
	struct Faster :public RBase<S, A>
	{
		R Reward(const S &s)override
		{
			R ret;

			if (s == 3)
			{
				ret = -10.;
			}
			else if (s == 7)
			{
				ret = 10.;
			}
			else
			{
				ret = -1.;
			}

			return ret;
		}
	};

	using Agent = Agent<S, A>;
	using Env = Environment<S, A>;

	auto s0 = 5;//初期状態
	Agent::pAction exp = make_unique<Exprole>();
	Env::pReward fast = make_unique<Faster>();
	Env::pTransition maze = make_unique<Maze>();
	Agent::pQFunc table = make_unique<QTable>();

	QLearningTemplate<S,A> obj(s0, exp, fast, maze, table);
	obj.Learn(1000);

	obj.Disp();
	_getch();
	return 0;
}

