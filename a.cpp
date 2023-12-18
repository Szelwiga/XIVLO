#include <bits/stdc++.h>
using namespace std;
void imax(int &a, int b){ a=max(a, b); }
void imin(int &a, int b){ a=min(a, b); }
void isort(int &a, int &b){ if (a>b) swap(a, b); } //DBG KIT /*
template <typename T> struct tag:reference_wrapper <T>{ using reference_wrapper <T>::reference_wrapper; };
template <typename T1, typename T2> static inline tag <ostream> operator<<(tag <ostream> os, pair<T1, T2> const& p){ return os.get()<<"{"<<p.first<<", "<<p.second<<"}", os;}
template <typename Other> static inline tag <ostream> operator<<(tag <ostream> os, Other const& o){ os.get()<<o; return os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, vector <T> const& v){ os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, set <T> const& s){ vector <T> v; for (auto i: s) v.push_back(i); os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }
/*
	WARNING: I'm using strange bracket style!
*/
const int P = 1<<19; // Taki rozmiar drzewa wystarczy
class tree{

	//TODO
	public:

	void update(int x, int y){ /* t[x] = 1 */
		//TODO
	}

	int ask(int x, int y){ /* max(t[x], t[x+1], t[x+2], ..., t[y-1], t[y]) */
		//TODO
	}
};
tree t;

#define int long long
const int SIZE = 4'100'000;
bitset <SIZE> sieve;
vector <int> primes, holes;

int goRight(int x, int res=0){ /* Counting distance between to primes */
	while (sieve[x])
		res++,
		x++;
	return res;
}
int findRightPrime(int x){ /* Finding closest prime on right */
	int low = 0, high = primes.size() - 1, mid;
	while (low+1 != high)
		mid = (low+high)/2,
		(primes[mid] < x) ? low = mid : high = mid;
	return high;
}
int findLeftPrime(int x){ /* Finding closest prime on left */
	int low = 0, high = primes.size() - 1, mid;
	while (low+1 != high)
		mid = (low+high)/2,
		(primes[mid] <= x) ? low = mid : high = mid;
	return low;
}

auto main() -> int32_t {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	for (int i=2; i<SIZE; i++) /* Just sieve */
		if (!sieve[i])
			for (int j=i*i; j<SIZE; j+=i)
				sieve[j] = true;

	/* Okazuje się, że liczba 1 jednak nie jest złożona, miałem przez to wa :( */
	//sieve[1] = true;

	for (int i=0; i<SIZE; i++) /* Vector with primes */
		if (!sieve[i])
			primes.push_back(i);
	primes.pop_back();

	for (auto i: primes)
		holes.push_back(goRight(i+1)); /* Holes between primes */

	for (int i=0; i<holes.size(); i++) /* Pusing holes to segment xmas tree */
		t.update(i, holes[i]);

	int q;
	cin>>q;
	while (q--){
		int x, y;
		cin>>x>>y;

		int px = findRightPrime(x);
		int py = findLeftPrime(y);

		if (py < px)			cout<<y-x+1<<"\n";
		else if (px == py)		cout<<max(primes[px]-x, y-primes[py])<<"\n";
		else					cout<<max({primes[px]-x, y-primes[py], t.ask(px, py-1) * 1ll})<<"\n";
	}

	return 0;
}
