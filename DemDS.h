#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<assert.h>
#include<ctime>
#include<set>
#include<stack>
#include<map>
#include<random>
#include<queue>
#include<cstdint>
int cutoff_time = 1000;
int seed = 0;
int alpha = 90;
std::mt19937 gen(seed);
using namespace std;
long long nbIter = 90000000000;
int current_X;
class MDSP
{
public:
	vector<vector<int>>HL;
	vector<int>must_;
	vector<char>X;
	vector<char>X_minus;
	vector<char>X_plus;
	vector<int>X2_list;
	vector<int>X2;
	vector<int>DX2;
	vector<int>DX2_list;
	vector<int>X_M;//X^-
	vector<int>X_M_list;
	vector<int>L;
	vector<int>L2;//degree to X
	vector<int>L3;
	vector<vector<int>>X_to_P;
	vector<pair<int, int>>P_to_X;
	vector<int>Stion;
	int alpha = 90;
	int Beta = 1;
	bool stop = false;
	vector<vector<int>>vertex;
	int upper;
	int bbb = 0;
	int now_time = 1;
	clock_t log_time = clock();
	clock_t curr_time = clock();
	double best_time = 0;
	clock_t log2_time = clock();
	clock_t begin_time;
	int iter3;
	int ini_num;
	int x_plus;
	int x_minus;
	int x;
	int current_index = 25;
	vector<long long>age;
	int vary_length = 25;
	bool model = false;
	void calc_L();
	void remove_to_X(int u);
	void ini_greed();
	void calc_L2();
	void calc_L3();
	auto improve(long long iter) -> void;
	void remove_vertex(int num, long long iter);
	void calc_score();
	bool Dem_kDS(long long& iter);
	int select_move(int& a, int& b, long long& iter);
	void apply_move(int& a, int& b, long long iter);
	void DemDS();
	void insert_vertex(int num);
	void f1_1(int p)
	{
		if (!X_plus[p])
		{
			X_plus[p] = 1;
			x_plus++;
		}
		for (auto i : HL[p])
			L3[i]++;
	}
	void f1_2(int p)
	{
		X_minus[p] = 0;
		X_M[X_M_list[p]] = X_M[X_M.size() - 1];
		X_M_list[X_M[X_M.size() - 1]] = X_M_list[p];
		X_M_list[p] = -1;
		X_M.pop_back();
		x_minus--;
		for (auto i : HL[p])
		{
			L[i]--;
		}
	}
	void f2_1(int p)
	{
		if (L2[p] != 2)
		{
			X_plus[p] = 0;
			x_plus--;
		}
		for (auto i : HL[p])
			L3[i]--;
	}
	void f2_1(int p, int n)
	{
		if (L2[p] != 2)
		{
			X_plus[p] = 0;
			x_plus--;
		}
		for (auto i : HL[p])
			L3[i]--;
	}
	void f2_2(int p)
	{
		X_minus[p] = 1;
		X_M.push_back(p);
		X_M_list[p] = X_M.size() - 1;
		x_minus++;
		for (auto i : HL[p])
		{
			L[i]++;
		}
	}
	void f1(int p)
	{
		f1_1(p);
		f1_2(p);
	}
	void f2(int p)
	{
		f2_1(p);
		f2_2(p);
	}
	void f3(int p)
	{
		X[p] = 1;
		x++;
		f1_2(p);
		for (auto i : HL[p])
		{
			L2[i]++;
			if (X_minus[i])
			{
				P_to_X[i].first = p;
				P_to_X[i].second = X_to_P[p].size();
				X_to_P[p].push_back(i);
				f1(i);
			}
			if (L2[i] == 2 && X_plus[i])
			{
				for (auto k : HL[i])
				{
					if (X[k] && k != p)
					{
						X_to_P[k][P_to_X[i].second] = X_to_P[k][X_to_P[k].size() - 1];
						P_to_X[X_to_P[k][X_to_P[k].size() - 1]].second = P_to_X[i].second;
						X_to_P[k].pop_back();
						P_to_X[i].first = -1, P_to_X[i].second = -1;
					}
				}
				f2_1(i, p);
			}
		}


	}
	void f4(int p)
	{
		X[p] = 1;
		x++;
		for (auto i : HL[p])
			L2[i]++;
		if (L2[p] == 1)
		{
			X_to_P[P_to_X[p].first][P_to_X[p].second] = X_to_P[P_to_X[p].first][X_to_P[P_to_X[p].first].size() - 1];
			P_to_X[X_to_P[P_to_X[p].first][X_to_P[P_to_X[p].first].size() - 1]].second = P_to_X[p].second;
			X_to_P[P_to_X[p].first].pop_back();
			P_to_X[p].first = -1, P_to_X[p].second = -1;
			f2_1(p);
		}
		else
		{
			X_plus[p] = 0;
			x_plus--;
		}
		for (auto i : HL[p])
		{
			if (X_minus[i])
			{
				P_to_X[i].first = p;
				P_to_X[i].second = X_to_P[p].size();
				X_to_P[p].push_back(i);
				f1(i);
			}
			if (L2[i] == 2 && X_plus[i])
			{
				for (auto k : HL[i])
				{
					if (X[k] && k != p)
					{
						X_to_P[k][P_to_X[i].second] = X_to_P[k][X_to_P[k].size() - 1];
						P_to_X[X_to_P[k][X_to_P[k].size() - 1]].second = P_to_X[i].second;
						X_to_P[k].pop_back();
						P_to_X[i].first = -1, P_to_X[i].second = -1;
					}
				}

				f2_1(i, p);
			}
		}

	}
	void f5(int p) {
		X[p] = 0;
		x--;
		for (auto i : HL[p])
			L2[i]--;
		if (L2[p] == 1)
		{
			f1_1(p);
			for (auto i : HL[p])
			{
				if (X[i])
				{
					P_to_X[p].first = i;
					P_to_X[p].second = X_to_P[i].size();
					X_to_P[i].push_back(p);
					break;
				}
			}
		}
		else
		{
			X_plus[p] = 1;
			x_plus++;
		}
		for (auto i : HL[p])
		{
			if (L2[i] == 0 && X_plus[i])
			{

				X_to_P[p][P_to_X[i].second] = X_to_P[p][X_to_P[p].size() - 1];
				P_to_X[X_to_P[p][X_to_P[p].size() - 1]].second = P_to_X[i].second;
				X_to_P[p].pop_back();
				P_to_X[i].first = -1, P_to_X[i].second = -1;
				f2(i);
			}
			if (L2[i] == 1 && X_plus[i])
			{

				for (auto j : HL[i])
				{
					if (X[j] && j != p)
					{
						P_to_X[i].first = j;
						P_to_X[i].second = X_to_P[j].size();
						X_to_P[j].push_back(i);
						break;
					}
				}
				f1_1(i);
			}

		}

	}
	void f6(int p) {
		X[p] = 0;
		x--;
		for (auto i : HL[p])
			L2[i]--;
		f2_2(p);
		for (auto i : HL[p])
		{
			if (L2[i] == 0 && X_plus[i])
			{
				X_to_P[p][P_to_X[i].second] = X_to_P[p][X_to_P[p].size() - 1];
				P_to_X[X_to_P[p][X_to_P[p].size() - 1]].second = P_to_X[i].second;
				X_to_P[p].pop_back();
				P_to_X[i].first = -1, P_to_X[i].second = -1;
				f2(i);
			}
			if (L2[i] == 1 && X_plus[i])
			{
				for (auto j : HL[i])
				{
					if (X[j] && j != p)
					{
						P_to_X[i].first = j;
						P_to_X[i].second = X_to_P[j].size();
						X_to_P[j].push_back(i);
						break;
					}
				}
				f1_1(i);

			}
			if (L2[i] == 0 && X[i])
			{
				X2[X2_list[i]] = X2[X2.size() - 1];
				X2_list[X2[X2.size() - 1]] = X2_list[i];
				X2_list[i] = -1;
				X2.pop_back();

			}
		}
	}
	friend istream& operator >>(istream& istr, MDSP& g)//��ȡͼ
	{
		int V, value, E, value2;
		istr >> V >> E;
		g.X_minus.assign(V, 1);
		g.X_plus.assign(V, 0);
		g.X.assign(V, 0);
		g.HL.assign(V, vector<int>());
		g.must_.assign(V, 0);
		g.L.assign(V, 0);
		g.L2.assign(V, 0);
		g.L3.assign(V, 0);
		g.X2_list.assign(V, -1);
		g.DX2_list.assign(V, -1);
		g.X_M_list.assign(V, -1);
		g.x_minus = 0;
		g.x_plus = 0;
		g.x = 0;

		g.X_to_P.assign(V, vector<int>());
		g.P_to_X.assign(V, pair<int, int>(-1, -1));

		g.age.assign(V, 0);
		for (int i = 0; i < E; i++)
		{
			istr >> value >> value2;
			g.HL[value - 1].push_back(value2 - 1);
			g.HL[value2 - 1].push_back(value - 1);
		}
		for (int i = 0; i < V; i++)
		{
			sort(g.HL[i].begin(), g.HL[i].end());
		}
		return istr;
	}
};
void MDSP::calc_L()
{
	for (int i = 0; i < L.size(); i++)
	{
		for (auto& j : HL[i])
		{
			if (X_minus[j])
				L[i]++;
		}
	}
}
void MDSP::calc_score()
{
	for (auto i : X2)
	{
		for (auto j : HL[i])
		{
			if (L2[j] == 1 && X_plus[j])
			{
				P_to_X[j].first = i, P_to_X[j].second = X_to_P[i].size();
				X_to_P[i].push_back(j);
			}
		}
	}
}
void MDSP::remove_to_X(int u)
{
	X[u] = 1;
	x++;
	if (X_minus[u] == 1)
	{
		X_minus[u] = 0;
		x_minus--;
		for (auto& i : HL[u])
			L[i]--;
	}
	if (X_plus[u] == 1)
	{
		X_plus[u] = 0;
		x_plus--;
	}
	for (auto& i : HL[u])
	{
		if (X_minus[i] == 1)
		{
			X_minus[i] = 0;
			x_minus--;
			X_plus[i] = 1;
			x_plus++;
			for (auto& j : HL[i])
				L[j]--;
		}
	}
}
void MDSP::ini_greed()
{
	for (int i = 0; i < HL.size(); i++)
	{
		if (HL[i].size() == 0)
		{
			X_minus[i] = 0;
			X[i] = 1;
		}
		if (HL[i].size() == 1 && X_minus[i] == 1)
		{
			X_minus[*(HL[i].begin())] = 0;
			X_plus[*(HL[i].begin())] = 0;
			X[*(HL[i].begin())] = 1;
			must_[i] = 2147483643;
			for (auto& j : HL[*(HL[i].begin())])
			{
				if (X_minus[j] == 1)
				{
					X_minus[j] = 0;
					X_plus[j] = 1;
				}
			}
		}
		if (HL[i].size() == 2 && X_minus[i] == 1)
		{
			auto f = HL[i].begin();
			int first = *f;
			f++;
			int second = *f;
			if (HL[first].size() == 2)
			{
				auto t = HL[first].begin();
				if (*t == i)
				{
					t++;
				}
				if (*t == second)
				{
					if (X[second])
						continue;
					must_[i] = 2147483643;
					must_[first] = 2147483643;
					X[second] = 1;
					X_minus[second] = 0;
					X_plus[second] = 0;
					for (auto j : HL[second])
					{
						if (X_minus[j])
						{
							X_minus[j] = 0;
							X_plus[j] = 1;
						}
					}
				}

			}
			else if (HL[second].size() == 2)
			{
				auto t = HL[second].begin();
				if (*t == i)
				{
					t++;
				}
				if (*t == first)
				{
					if (X[first])
						continue;
					must_[i] = 2147483643;
					must_[second] = 2147483643;
					X[first] = 1;
					X_minus[first] = 0;
					X_plus[first] = 0;
					for (auto j : HL[first])
					{
						if (X_minus[j])
						{
							X_minus[j] = 0;
							X_plus[j] = 1;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < X.size(); i++)
	{
		if (X[i])
			x++;
		if (X_minus[i])
			x_minus++;
		if (X_plus[i])
			x_plus++;
	}
	ini_num = x;
	for (int i = 0; i < HL.size(); i++)
	{
		if (X[i])
		{
			X2_list[i] = X2.size();
			X2.push_back(i);
		}
	}
	calc_L();

	int mmx = -1;
	int mx = 0;
	bool ffl_1 = X_minus[0];
	bool ffl_2 = false;
	for (int i = 0; i < L.size(); i++)
	{
		ffl_2 = X_minus[i];
		if (L[i] + ffl_2 > L[mx] + ffl_1)
		{
			mx = i;
			ffl_1 = ffl_2;
		}
	}
	mmx = L[mx] + ffl_1;
	remove_to_X(mx);
	while (x_minus != 0)
	{
		int i = mx;
		for (; i < L.size(); i++)
		{
			ffl_2 = X_minus[i];
			if (mmx == L[i] + ffl_2 && mmx != 0)
			{
				ffl_1 = ffl_2;
				mx = i;
				break;
			}
			if (L[i] + ffl_2 > L[mx] + ffl_1)
				mx = i;
		}
		if (i == L.size() && mmx != 0)
		{
			for (int j = 0; j < i; j++)
			{
				ffl_2 = X_minus[j];
				if (L[j] + ffl_2 > L[mx] + ffl_1)
				{
					mx = j;
					ffl_1 = ffl_2;
				}
			}
			if (L[mx] + ffl_1 != 0)
			{
				mmx = L[mx] + ffl_1;
				mx = 0;
				ffl_1 = X_minus[0];
				continue;
			}
			else
			{
				mx = 0;
				ffl_1 = X_minus[0];
				break;
			}
		}
		ffl_1 = 0;
		remove_to_X(mx);
	}
	for (int i = 0; i < HL.size(); i++)
	{
		if (X[i])
		{
			if (X2_list[i] == -1)
			{
				X2_list[i] = X2.size();
				X2.push_back(i);
			}
		}
		else
		{
			DX2_list[i] = DX2.size();
			DX2.push_back(i);
		}
	}
}
void MDSP::calc_L2()
{
	for (int i = 0; i < L2.size(); i++)
	{
		for (auto& j : HL[i])
			if (X[j])
				L2[i]++;
	}
}
void MDSP::calc_L3()
{
	for (int i = 0; i < L3.size(); i++)
	{
		if (L2[i] == 1 && X_plus[i])
		{
			for (auto& j : HL[i])
			{
				L3[j]++;
			}
		}
	}
}
auto MDSP::improve(long long iter)->void {
	for (int i = 0; i < X2.size(); i++)
	{
		if (L3[X2[i]] == 0 && L2[X2[i]] != 0)
			remove_vertex(X2[i], iter);
	}
}
void MDSP::insert_vertex(int i)
{
	DX2[DX2_list[i]] = DX2[DX2.size() - 1];
	DX2_list[DX2[DX2.size() - 1]] = DX2_list[i];
	DX2_list[i] = -1;
	DX2.pop_back();

	X2_list[i] = X2.size();
	X2.push_back(i);

	if (X_plus[i])
		f4(i);
	else
		f3(i);
}
void MDSP::remove_vertex(int i, long long iter)
{
	X2[X2_list[i]] = X2[X2.size() - 1];
	X2_list[X2[X2.size() - 1]] = X2_list[i];
	X2_list[i] = -1;
	X2.pop_back();

	DX2_list[i] = DX2.size();
	DX2.push_back(i);


	if (L2[i] == 0)
		f6(i);
	else
		f5(i);
}
int MDSP::select_move(int& a, int& b, long long& iter)//(a,b)
{
	int sc = X.size();
	sc = -sc;
	int sc_2 = sc;
	int a2 = -1;
	int b2 = -1;
	int rd_2 = 1;
	int a1 = -1, b1 = -1;
	int rd = 1;
	int ra = gen() % X_M.size();
	auto first = X_M.begin();
	for (int i = 0; i < ra; i++)
	{
		first++;
	}
	int y = *first;
	vector<int>yy;
	for (auto i : HL[y])
		yy.push_back(i);
	yy.push_back(y);
	int s = -(int)X.size();
	for (auto& j : yy)
	{
		if (must_[j] > iter)
			continue;
		int p = (L2[j] == 0);
		if (L[j] + p > sc)
		{
			b1 = j;
			sc = L[j] + p;
		}
		else if (L[j] + p == sc)
		{
			if (age[j] < age[b1])
			{
				b1 = j;
				rd = 1;
			}
			else if (age[j] == age[b1])
			{
				rd++;
				if (!(gen() % rd))
				{
					b1 = j;
				}
			}
		}
	}
	int j = b1;
	int num = 0;
	for (auto i : HL[j])
	{
		if (X[i] && X2_list[i] >= ini_num)
		{
			num++;
			int temp = 0;
			for (auto k : X_to_P[i])
			{
				if (binary_search(HL[j].begin(), HL[j].end(), k))
					temp++;
			}
			if (P_to_X[j].first == i)
				temp++;
			temp = L[j] + temp - L3[i];
			if (!binary_search(HL[j].begin(), HL[j].end(), i))
			{
				if (L2[j] == 0)
					temp++;
				if (L2[i] == 0)
					temp--;
			}
			if (sc_2 < temp)
			{
				sc_2 = temp;
				a2 = i, b2 = j;
			}
			else if (sc_2 == temp)
			{
				if (age[i] < age[a2])
				{
					a2 = i, b2 = j;
				}
				else if (age[i] == age[a2])
				{
					if (age[j] < age[b2])
					{
						a2 = i, b2 = j;
						rd_2 = 1;
					}
					else if (age[j] == age[b2])
					{
						rd_2++;
						if (!(gen() % rd_2))
						{
							a2 = i, b2 = j;
						}

					}
				}

			}
		}
		if (P_to_X[i].first != -1)//X^+\cup L^0
		{
			int x = P_to_X[i].first;//x
			num++;
			if (X2_list[x] < ini_num)
				continue;
			int temp = 0;
			for (auto k : X_to_P[x])
			{
				if (binary_search(HL[j].begin(), HL[j].end(), k))
					temp++;
			}
			if (P_to_X[j].first == x)
				temp++;
			temp = L[j] + temp - L3[x];
			if (!binary_search(HL[j].begin(), HL[j].end(), x))
			{
				if (L2[j] == 0)
					temp++;
				if (L2[x] == 0)
					temp--;
			}
			if (sc_2 < temp)
			{
				sc_2 = temp;
				a2 = x, b2 = j;
			}
			else if (sc_2 == temp)
			{
				if (age[x] < age[a2])
				{
					a2 = x, b2 = j;
				}
				else if (age[x] == age[a2])
				{
					if (age[j] < age[b2])
					{
						a2 = x, b2 = j;
						rd_2 = 1;
					}
					else if (age[j] == age[b2])
					{
						rd_2++;
						if (!(gen() % rd_2))
						{
							a2 = x, b2 = j;
						}

					}
				}

			}
		}
	}
	num = max(Beta, num);
	for (int i = current_index; i < min(current_index + num, int(X2.size() - 1)); i++)
	{
		int temp = 0;
		int x = X2[i];
		for (auto k : X_to_P[x])
		{
			if (binary_search(HL[j].begin(), HL[j].end(), k))
				temp++;
		}
		if (P_to_X[j].first == x)
			temp++;
		temp = L[j] + temp - L3[x];
		if (!binary_search(HL[j].begin(), HL[j].end(), x))
		{
			if (L2[j] == 0)
				temp++;
			if (L2[x] == 0)
				temp--;
		}
		if (temp > s)
		{
			s = temp;
			a1 = X2[i];
		}
		else if (temp == s)
		{
			if (age[X2[i]] < age[a1])
			{
				a1 = X2[i];
				rd = 1;
			}
			else if (age[X2[i]] == age[a1])
			{
				rd++;
				if (!(gen() % rd))
				{
					a1 = X2[i];
				}
			}
		}
	}

	sc = s;
	if (sc_2 > sc) {
		a = a2, b = b2;
		sc = sc_2;
	}
	else if (sc_2 == sc)
	{
		if (gen() % 100 > alpha)
		{
			a = a2, b = b2;
			sc = sc_2;
		}
		else {
			a = a1;
			b = b1;
		}
	}
	else
	{
		a = a1;
		b = b1;
	}
	return sc;
}
void MDSP::apply_move(int& a, int& b, long long  iter)
{
	insert_vertex(b);
	age[b] = iter;
	age[a] = iter;
	remove_vertex(a, iter);
}
bool MDSP::Dem_kDS(long long& iter)
{
	if (current_index + vary_length >= upper)
		current_index = ini_num;
	if (x_minus == 0)
	{
		return true;
	}
	for (; iter < nbIter; iter++)
	{
		int a, b, c, d;
		if (iter % 1000 == 0)
		{
			curr_time = clock();
			if ((curr_time - begin_time) / CLOCKS_PER_SEC > cutoff_time)
			{
				stop = true;
				return false;
			}
		}
		// if ((curr_time - log2_time) / CLOCKS_PER_SEC > 1)
		// {
		// 	cout << "#" << iter << "  #" << current_X  << "  #" << x_minus << "  " /*<< iter / (num_it + 1) * / */ << "   " << X2.size() << "  " << current_X-X2.size() << endl;
		// 	log2_time = curr_time;
		// }

		c = select_move(a, b, iter);
		if (a != -1 && b != -1)
		{
			d = x_minus;
			apply_move(a, b, iter);
			swap(X2[current_index], X2[X2_list[b]]);
			swap(X2_list[X2[current_index]], X2_list[X2[X2_list[b]]]);
			current_index++;
		}

		if (current_index + vary_length >= upper)
		{
			current_index = ini_num;
		}
		if (x_minus == 0)
		{
			best_time = (curr_time - begin_time) / CLOCKS_PER_SEC;
			if ((curr_time - log_time) / CLOCKS_PER_SEC > 10) {
				improve(iter);
				log_time = curr_time;
				bbb++;
			}
			return true;
		}

		for (int i = current_index; i < current_index + vary_length; i++)
		{
			int rd = gen() % (X2.size() - ini_num) + ini_num;
			swap(X2[i], X2[rd]);
			swap(X2_list[X2[i]], X2_list[X2[rd]]);
		}

	}
	return false;
}
void MDSP::DemDS()
{
	ini_greed();
	calc_L2();
	calc_L3();
	calc_score();
	improve(0);
	long long iter = 0;
	current_index = ini_num + 1;
	begin_time = clock();
	while (iter < nbIter)
	{
		int num = current_index;//remove
		remove_vertex(X2[num], iter);
		upper = min(ini_num + 1000, int(X2.size() - 1));
		current_X = X2.size();
		Dem_kDS(iter);
		if (stop)
		{
			return;
		}
	}
}