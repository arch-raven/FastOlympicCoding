#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <ostream>
#include <istream>
#include <typeinfo>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <limits>
#include <fstream>
#include <array>
#include <list>
#include <functional>

#define mt make_tuple
#define x first
#define y second
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define mp make_pair
#define umap unordered_map
#define uset unordered_set
#define rt return 0;
#define elif else if
#define len(v) ((int)v.size())


using namespace std;

char string_in_buffer[(int)260];


void fast_scan(int &x) { scanf("%d", &x); }
void fast_scan(long long &x) { scanf("%lld", &x); }
void fast_scan(unsigned long long &x) { scanf("%llu", &x); }
void fast_scan(double &x) { scanf("%lf", &x); }
void fast_scan(long double &x) { scanf("%Lf", &x); }
void fast_scan(char &x) { 
	scanf("%c", &x); 
	if (x == '\n') {
		fast_scan(x);
	}
}
void fast_scan(string &x) {
	scanf("%s", string_in_buffer);
	x = string(string_in_buffer);
}

template<class TFirst, class TSecond>
void fast_scan(pair<TFirst, TSecond> &p) {
	fast_scan(p.first);
	fast_scan(p.second);
}

template <class T>
void fast_scan(vector<T> &v) {
	for (auto &x : v) fast_scan(x);
}

void fast_print(const int &x) { printf("%d", x); }
void fast_print(const long long &x) { printf("%lld", x); }
void fast_print(const unsigned long long &x) { printf("%llu", x); }
void fast_print(const double &x) { printf("%lf", x); }
void fast_print(const long double &x) { printf("%Lf", x); }
void fast_print(const char &x) { printf("%c", x); };
void fast_print(const string &x) { printf("%s", x.c_str());}

template<class TFirst, class TSecond>
void fast_print(const pair<TFirst, TSecond> &p) {
	fast_print(p.first);
	fast_print(' ');
	fast_print(p.second);
}

template <class T>
void fast_print(const vector<T> &v) {
	if (v.empty()) return;
	fast_print(v[0]);
	for (int i = 1; i < v.size(); i++) {
		fast_print(" ");
		fast_print(v[i]);
	}
}

template <class T>
void fast_print(const vector<vector<T>> &v) {
	if (v.empty()) return;
	fast_print(v[0]);
	for (int i = 1; i < v.size(); i++) {
		fast_print("\n");
		fast_print(v[i]);
	}
}



using namespace std;


namespace smart_io {

	string print_start = "";
	string sep = " ";
	bool first_print = false;

	void precall_print() {
		fast_print(print_start);
		print_start = "\n";
		first_print = true;
	}
}


template <class T>
ostream &operator,(ostream &os, const T &object) {

	if (!smart_io::first_print) {
		fast_print(smart_io::sep);
	} else {
		smart_io::first_print = false;
	}
	fast_print(object);
	return os;
}

template <class T>
istream &operator,(istream &is, T &object) {
	fast_scan(object);
	return is;
}

namespace typedefs {
	typedef long long ll;
	typedef unsigned long long ull;
	typedef vector<int> vi;
	typedef pair<int, int> pii;
	typedef vector<vector<pair<int, int>>> vvpii;
	typedef vector<vector<pair<bool, int>>> vvpbi;
}

using namespace typedefs;

#define print    \
smart_io::precall_print(); \
cout,

#define scan cin,
#define MAX_PRIME 1000

vector<bool> is_prime(MAX_PRIME, true);
vector<int> primes;

void fill_prime() {
	is_prime[1] = false;
	for (int i = 2; i < MAX_PRIME; i++) {
		if (is_prime[i]) {
			for (int j = i * i; j < MAX_PRIME; j += i) {
				is_prime[j] = false;
			}
		}
	}

	for (int i = 1; i < MAX_PRIME; i++) {
		if (is_prime[i]) {
			primes.pb(i);
		}
	}
}






void uniq(vector<int> &v) {
	set<int> s(v.begin(), v.end());
	v = vector<int>(s.begin(), s.end());
}

int main(int argc, char *argv[]) {
	int n;
	scan n;
	fill_prime();
	vector<int> p1s;
	vector<int> p2s;
	vector<vector<int>> dp(1000, vector<int>(1000));
	vector<vector<bool>> prime_arr(1000, vector<bool>(1000, false));
	// print primes;
	for (auto prime : primes) {
		string s = to_string(prime);
		if (prime < 10) continue;
		for (int i = 1; i < len(s); i++) {
			string first(s.begin(), s.begin() + i);
			string second(s.begin() + i, s.end());
			if (second[0] == '0') {
				continue;
			}
			int p1 = stoi(first);
			int p2 = stoi(second);
			if (p1 <= n && p2 <= n) {
				prime_arr[p1][p2] = true;
			}
		}
	}
	dp[0][0] = 0;
	dp[0][1] = 0;
	dp[1][0] = 0;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + prime_arr[i][j];
		}
	}
	print dp[n][n] - 1;
}