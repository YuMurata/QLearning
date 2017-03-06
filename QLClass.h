#pragma once


//http://qiita.com/icoxfog417/items/242439ecd1a477ece312


#include"stdafx.h"

#include"Filer.h"

#include<functional>
#include<memory>
#include<vector>
#include<algorithm>
#include<random>
#include<iterator>
#include<iostream>
#include<map>
#include<utility>
#include<Randomer.h>
#include<DataBase.h>
#include<queue>
#include"../../NearestNeighbor/LSH/LSH/LSH.h"
#include<sparsehash/dense_hash_map>
using namespace std;

template<typename S,typename A>
class QLClass :public Randomer,DataBase<vector<S>>
{
public:
	using SA = std::pair<S, A>;
	using Q = double;

	using HashS = function<size_t(const S &s)>;
	using HashA = function<size_t(const A &a)>;

	struct eqstr
	{
		bool operator()(const SA &left, const SA &right) const
		{
			return left==right;
		}
	};

	using QTable = google::dense_hash_map<SA, Q,hash<SA>, eqstr>;

	using SAQ = pair<SA, double>;

	using FuncR = std::function<Q(const S &s)>;
	using FuncT = std::function<S(const S &s, const A &a)>;
	using FuncAs = std::function<vector<A>(const S &s)>;
	
#ifdef UNICODE
	using FuncLoad = std::function<vector<SAQ>(const vector<vector<string>>&)>;
	using FuncWrite = function<void(const QTable&,vector<vector<string>>*)>;
#else
	using FuncLoad = std::function<vector<SAQ>(const vector<vector<wstring>>&)>;
	using FuncWrite = function<void(const QTable&,vector<vector<wstring>>*)>;
#endif // !UNICODE
	
	

protected:
	QTable q_table;
	
	FuncT T;
	FuncR R;
	FuncAs As;

	FuncLoad load;
	FuncWrite write;

	HashS hash_s;
	HashA hash_a;

	double learn_rate;
	double r;
	double e;


	A RandAction(const S &s)
	{
		auto pos_a = As(s);

		shuffle(begin(pos_a), end(pos_a), this->mt);
	
		auto ret=pos_a.front();
		auto _size = size(pos_a);
		return ret;
	}

	void Pruning()
	{
		auto _size = size(this->q_table);
		auto _sizeof=sizeof(SA);
		auto mem_size = _size*_sizeof;
		if ( mem_size< 50e3)
		{
			return;
		}
		vector<SAQ> data_list(begin(this->q_table),end(this->q_table));

		auto sum_func = [](const double &left, const SAQ &right)
		{
			auto ret = left + abs(right.second);
			return ret;
		};

		auto abs_sum = accumulate(begin(data_list), end(data_list), 0., sum_func);

		if (abs_sum == 0.)
		{
			return;
		}

		auto threshold = 0.01;
		auto pred = [](const SAQ &x, const SAQ &y)
		{
			return x.second < y.second;
		};
		sort(begin(data_list), end(data_list),pred);

		auto find_func = [&abs_sum, &threshold](const SAQ &x)
		{
			return abs(x.second) / abs_sum > threshold;
		};
		auto itr = find_if(begin(data_list), end(data_list), find_func);

		auto dist = distance(begin(data_list), itr);
		if (dist < 1000)
		{
			return;
		}

		this->q_table.clear();
		auto ins_func = [&](const SAQ &x)
		{
			this->q_table.insert(x);
		};

		for_each(itr, end(data_list), ins_func);
	}

public:
	QLClass()
		:QLClass(0.7, 0.9, 1.)
	{}

	QLClass(const double &lr, const double &r, const double &e)
		:learn_rate(lr), r(r), e(e) 
	{
		this->q_table.set_empty_key(SA(NAN,NAN));
	}

	~QLClass() {}

	virtual void QUpDate(const S &s, const A &a)
	{
		auto s2 = this->T(s, a); 
		auto a2 = BestAction(s2); 
		auto r = this->R(s2); 
		double maxE = q_table[make_pair(s2, a2)]; 

		auto &q = this->q_table[make_pair(s, a)]; 
		
		q = (1 - learn_rate)*q + this->learn_rate*( r + this->r*maxE); 
		this->Pruning();
	}
	
	A Learn(const S &s)
	{
		uniform_real_distribution<> prop;

		A a;

		if (prop(this->mt) < this->e)
		{
			a = this->RandAction(s);
		}
		else
		{
			a = this->BestAction(s);
		}
		this->QUpDate(s, a);

		return a;
	}

	A BestAction(const S &s)
	{
		auto pos_a = As(s);

		A best_a = pos_a.front(); 
		auto maxQ = this->q_table[make_pair(s, best_a)]; 

		vector<SA> sas;
		//vector<pair<const S&, const A&>>sas;
		sas.reserve(size(pos_a));
	
		for (auto &a : pos_a)
		{
			sas.push_back(make_pair(s, a));
		}
		
		auto NotFound = [&](const SA &sa)
		{
			auto itr = this->q_table.find(sa);
			auto ret = itr == end(this->q_table);

			return ret;
		};

		for (auto &sa : sas)
		{
			auto itr = this->q_table.find(sa);
			if (itr==end(this->q_table))
			{
				continue;
			}
			auto q = itr->second;
			if ( q> maxQ)
			{
				best_a = sa.second;
				maxQ = q;
			}
		}
		
		return best_a;
	}

	void Disp()
	{
		for (auto &i : this->q_table)
		{
			auto s = i.first.first;
			auto a = i.first.second;

			auto q = i.second;

			cout << "[" << s << "," << a << "]:" << q << endl;
		}
	}

	//FuncR = Q(const S &s);
	//FuncT = S(const S &s, const A &a);
	//FuncAs = vector<A>(const S &s);
	//FuncLoad = vector<SAQ>(const vector<vector<string>>&);
	//FuncWrite = vector<vector<string>>(const QTable&);
	void SetFunc
		(
			const FuncR &func_r,
			const FuncT &func_t,
			const FuncAs &func_as,
			const FuncLoad &func_load,
			const FuncWrite &func_write
			)
	{
		this->R = func_r;
		this->T = func_t;
		this->As = func_as;
		this->load = func_load;
		this->write = func_write;
	}

#ifdef UNICODE
	bool LoadFile(const string &file_name)override
	{
		auto data_list = this->PreLoad(file_name);

		auto Qs = this->load(data_list);

		for (auto &i : Qs)
		{
//			this->q_table.emplace_hint(begin(this->q_table), i.first, i.second);
			this->q_table[i.first] = i.second;
		}

		return !data_list.empty();
	}

	bool WriteFile(const string &file_name)override
	{
		vector<vector<string>> data_list;
		this->write(this->q_table,&data_list);

		this->PreWrite(file_name, data_list);

		return true;
	}
#else
	bool LoadFile(const wstring &file_name)override
	{
		auto data_list = this->PreLoad(file_name);

		auto Qs = this->load(data_list);

		for (auto &i : Qs)
		{
			//			this->q_table.emplace_hint(begin(this->q_table), i.first, i.second);
			this->q_table[i.first] = i.second;
		}

		return !data_list.empty();
	}

	bool WriteFile(const wstring &file_name)override
	{
		vector<vector<wstring>> data_list;
		this->write(this->q_table, &data_list);

		this->PreWrite(file_name, data_list);

		return true;
	}
#endif

};


	// unordered_map�g�����߂̕������ꉻ
	template<typename S,typename A>
	struct std::hash<std::pair<S,A>>
	{
		size_t operator()(const std::pair<S,A> &sa) const
		{
			const size_t idx = 19780211;
			return std::hash<S>()(sa.first) + idx*std::hash<A>()(sa.second);
		}
	};

	template<typename S, typename A>
	struct std::less<std::pair<std::pair<S, A>,double>>
	{
		bool operator()(const std::pair<std::pair<S,A>,double> &x, const std::pair<std::pair<S, A>, double> &y) const
		{
			return x.second < y.second;
		}
	};

	template<typename S, typename A>
	struct std::greater<std::pair<std::pair<S, A>, double>>
	{
		bool operator()(const std::pair<std::pair<S, A>, double> &x, const std::pair<std::pair<S, A>, double> &y) const
		{
			return x.second > y.second;
		}
	};