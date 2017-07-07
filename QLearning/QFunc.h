#pragma once

#include"Config.h"

//$$$$QBase
//Q関数の基底クラス
//このクラスを継承した派生クラスを作成してください
//
//####using型
//なし
//
//####コンストラクタ
//なし
//
//####仮想関数
//bool Save(const char file_name[])	
//bool Load(const char file_name[])
//
//####純粋仮想関数
//void UpDate(const S &s, const A &a,const R &r,const Q &maxQ)
//Q Value(const S &s, const A &a)
//void Disp()
template<typename S,typename A>
struct QBase :public Config<S,A>
{
	//状態sにおいて行動aをとる価値qを報酬rと最大行動価値maxQを使って更新する
	//TODO: 派生クラスでユーザーが定義する
	virtual void UpDate(const S &s, const A &a, const R &r, const Q &maxQ) = 0;

	//状態sにおいて行動aをとる価値qを返す
	//TODO: 派生クラスでユーザーが定義する
	virtual Q Value(const S &s, const A &a) = 0;

	//Q値と行動のpair型のvectorを返す
	typename QAList ValueList(const S &s, const As &pos_a)
	{
		using namespace std;

		QAList ret;
		ret.reserve(size(pos_a));

		for (auto &a : pos_a)
		{
			auto q = this->Value(s, a);
			ret.push_back(make_pair(q, a));
		}

		return ret;
	}

	//Q値を表示する
	//TODO: 派生クラスでユーザーが定義する
	virtual void Disp() = 0;

	//Q値の保存
	virtual bool Save(const char file_name[]) 
	{
		return false;
	}
	
	//Q値の読み出し
	virtual bool Load(const char file_name[])
	{
		return false;
	}

	virtual void Extension() {}
};