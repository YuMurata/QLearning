// QLearning.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include"../include/Agent.h"
#include"../include/Environment.h"

#include<map>
#include<random>
#include<iostream>
#include<conio.h>

using namespace std;

int main()
{
	using S = int;
	using A = int;
	
	enum ACT
	{
		UP,
		LEFT,
		DOWN,
		RIGHT,
	};

	struct QTable :public QBase<S,A>
	{
		using SA = std::pair<S, A>;

		map<SA,Config<S,A>::Q> table;
		void UpDate(const S &s, const A &a,const double &r,const Q &maxQ)override
		{
			auto learn_rate = 0.5;
			auto discount = 0.8;
			auto key = make_pair(s, a);
			auto &q = this->table[key];

			q=(1 - learn_rate)*q + learn_rate*(r + discount*maxQ);
		}

		Q Value(const S &s, const A &a)override
		{
			auto ret = this->table[make_pair(s, a)];
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
	
	struct Exprole :public ABase<S,A>
	{
	public:
		As Capabilities(const S &s)
		{
			As ret{ UP,LEFT,DOWN,RIGHT };
			return ret;
		}

		A SelectAction(const S &s, const Config<S,A>::QAList &qa_list)override
		{
			auto e = 0.5;
			static random_device rnd;
			static mt19937 mt(rnd());
			static uniform_real_distribution<> obj(0, 1);
			
			auto x = obj(mt);
			if ( x< e)
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

	struct Maze :public Environment<S, A>::TBase
	{
		S Value(const S &s,const A &a)override
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

	struct Faster :public Environment<S, A>::RBase
	{
		Environment<S, A>::R Value(const S &s)
		{
			Environment<S, A>::R ret;

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
	
	struct QL
	{
		Agent<S, A> agent;
		Environment<S, A> environment;

		QL
		(
			const int &s0,
			Agent<S, A>::pAction &a,
			Environment<S, A>::pReward &r,
			Environment<S, A>::pTransition &t,
			Agent<S, A>::pQFunc &q_func
		)
			:agent(s0,a, q_func), environment(s0, t, r) {}

		void Learn(const int &learn_num)
		{
			S s;
			A a;
			Environment<S, A>::R r;

				s = environment.Get();
				agent.Observe(s);
			for (int i = 0; i < learn_num; ++i)
			{
				a = agent.Action();
				environment.Transition(a);
				s = environment.Get();
				agent.Observe(s);
				r = environment.Reward();
				agent.Review(r);
			}
		}

		void Disp()
		{
			this->agent.QDisp();
		}
	};

	const vector<A> a_list =
	{
		UP,LEFT,DOWN,RIGHT,
	};

	using Agent = Agent<S, A>;
	using Env = Environment<S, A>;

	auto s0 = 5;
	Agent::pAction exp = make_unique<Exprole>();
	Env::pReward fast = make_unique<Faster>();
	Env::pTransition maze = make_unique<Maze>();
	Agent::pQFunc table = make_unique<QTable>();

	QL obj(s0,exp,fast,maze,table);
	obj.Learn(1000);



	obj.Disp();
	_getch();
    return 0;
}

