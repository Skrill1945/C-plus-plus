#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

#define all(vect) vect.begin(), vect.end()
#define pb(a) push_back(a)

using namespace std;

bool cmin(int &a, int &b) {
	if (a < b) return true;
	else swap(a, b);
	return false;
}

int gcd(int a, int b) {
	while (a != 0 && b != 0) {
		if (a > b) {
			a = a % b;
		}
		else b = b % a;
	}
	return a + b;
}

struct SegTree {
	vector<pair<int, int>> d;
	int SZ = 1;

	SegTree(vector<int> &a) {
		int n = a.size();
		while (SZ < n) SZ *= 2;
		d.resize(SZ * 2);
		build(0, 0, SZ, a);
	}

	void print() {
		cout << "\n";
		for (int i = 0; i < SZ; i++)
		{
			cout << i << " = { " << d[i].first << " " << d[i].second << " }\n";
		}
		cout << "\n";
	}

	void build(int v, int l, int r, const vector<int> &a) {
		if (r - l == 1) {
			if (l < a.size()) d[v] = { a[l], 1 };
			else d[v] = { 0, 1 };
			return;
		}
		int m = (r + l) / 2;
		build(v * 2 + 1, l, m, a);
		build(v * 2 + 2, m, r, a);
		if (d[v * 2 + 1].first == d[v * 2 + 2].first) {
			d[v] = { d[v * 2 + 1].first, d[v * 2 + 1].second + d[v * 2 + 2].second };
		} else d[v] = (d[v * 2 + 1].first > d[v * 2 + 2].first ? d[v * 2 + 1] : d[v * 2 + 2]);
	}

	pair<int, int> query(int ql, int qr, int v, int l, int r) {
		if (qr <= l || r <= ql) return { -1000, -1 };
		if (ql <= l && r <= qr) return d[v];
		int m = (r + l) / 2;
		pair<int, int> p1 = query(ql, qr, v * 2 + 1, l, m);
		pair<int, int> p2 = query(ql, qr, v * 2 + 2, m, r);
		if (p1.first == p2.first) {
			return { p1.first, p1.second + p2.second };
		}
		else return (p1.first > p2.first ? p1 : p2);
	}

	pair<int, int> query(int ql, int qr) {
		return query(ql, qr, 0, 0, SZ);
	}
};

int main() {
	int n, a, b, d;
	char c;
	cin >> n;
	vector<int> vect(n, 0);
	for (int i = 0; i < n; i++)
	{
		cin >> vect[i];
	}
	SegTree st(vect);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		//st.print();
		pair<int, int> ans = st.query(a - 1, b);
		cout << ans.first << " " << ans.second << "\n";
	}
	cin >> n;
	return 0;
}