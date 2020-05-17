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

struct SegTree {
	vector<int> d;
	vector<int> flag;
	int SZ = 1;

	SegTree(vector<int> &a) {
		int n = a.size();
		while (SZ < n) SZ *= 2;
		d.resize(SZ * 2);
		flag.resize(SZ * 2, 0);
		build(0, 0, SZ, a);
	}

	void print() {
		cout << "\n";
		for (int i = 0; i < SZ; i++)
		{
			cout << i << " " << d[i] << "\n";
		}
		cout << "\n";
	}

	void build(int v, int l, int r, const vector<int> &a) {
		if (r - l == 1) {
			if (l < a.size()) d[v] = a[l];
			else d[v] = 0;
			return;
		}
		int m = (r + l) / 2;
		build(v * 2 + 1, l, m, a);
		build(v * 2 + 2, m, r, a);
		d[v] = d[v * 2 + 1] + d[v * 2 + 2];
	}

	int query(int ql, int qr, int v, int l, int r) {
		push(v, l, r);
		if (qr <= l || r <= ql) return 0;
		if (ql <= l && r <= qr)	return d[v];
		int m = (r + l) / 2;
		int p1 = query(ql, qr, v * 2 + 1, l, m);
		int p2 = query(ql, qr, v * 2 + 2, m, r);
		return p1 + p2;
	}

	void push(int v, int l, int r) {
		d[v] = d[v] + (r - l) * flag[v];
		if (r - l == 1) {
			flag[v] = 0;
			return;
		}
		flag[v * 2 + 1] += flag[v];
		flag[v * 2 + 2] += flag[v];
		flag[v] = 0;
	}

	void update(int x, int dx, int v, int l, int r) {
		push(v, l, r);
		if (x < l || x >= r) return;
		if (r - l == 1) {
			d[v] += dx;
			return;
		}
		int m = (r + l) / 2;
		update(x, dx, v * 2 + 1, l, m);
		update(x, dx, v * 2 + 2, m, r);
		d[v] = d[v * 2 + 1] + d[v * 2 + 2];
	}

	void update(int ql, int qr, int dx, int v, int l, int r) {
		push(v, l, r);
		if (qr <= l || r <= ql) return;
		if (ql <= l && r <= qr) {
			flag[v] += dx;
			push(v, l, r);
			return;
		}
		int m = (r + l) / 2;
		update(ql, qr, dx, v * 2 + 1, l, m);
		update(ql, qr, dx, v * 2 + 2, m, r);
		d[v] = d[v * 2 + 1] + d[v * 2 + 2];
	}

	void update(int x, int dx) {
		update(x, dx, 0, 0, SZ);
	}

	void update(int ql, int qr, int dx) {
		update(ql, qr, dx, 0, 0, SZ);
	}

	int query(int ql, int qr) {
		return query(ql, qr, 0, 0, SZ);
	}
};

int main() {
	int n, a, b;
	cin >> n;
	vector<int> vect(n, 0);
	SegTree st(vect);
	cin >> n;
	while(n != 0) {
		cin >> a >> b;
		if (n == 1) {
			st.update(a - 1, b);
		}
		else if (n == 2) {
			cout << st.query(a - 1, b) << "\n";
		}
		cin >> n;
	}
	cin >> n;
	return 0;
}