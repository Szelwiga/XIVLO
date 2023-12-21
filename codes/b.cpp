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
#define int long long
const int P = 1<<20; // Taki rozmiar drzewa wystarczy
const int INF = 1ll<<60;
class tree{
	int s[P*2+10]; /* tablica na minimalna wartosc w poddrzewie */
	int t[P*2+10]; /* wartosc delty (nasze lazy) -- o ile musimy zmodyfikowac poddrzewo */
	int A, B, C; /* Poczatek i koniec przedzialu dla każdego zapytania */
	void lazy(int u){ /* spychanie wartosci lazy w dol */
		s[u] += t[u];
		if (u<P)
			t[u*2] += t[u],
			t[u*2+1] += t[u];
		t[u] = 0;
	}
	int mid(int a, int b){ /* funkcja, ktora wyznacza "srodkowy" wierzcholek */
		return (a+b)/2;
	}
	/* funkcja update, zaczynamy od korzenia, ktorego przedzial odpowiedzialnosci to wszyskie liscie */
	void upd(int u=1, int low=0, int high=P-1){
		lazy(u);
		if (high<A || low>B)	return;
		if (A<=low && high<=B)
			return t[u] += C, lazy(u);
		upd(u*2, low, mid(low, high));
		upd(u*2+1, mid(low, high)+1, high);
		s[u] = min(s[u*2]+t[u*2], s[u*2+1]+t[u*2+1]);
	}
	/* analogicznie dla zapytania */
	int query(int u=1, int low=0, int high=P-1){
		lazy(u);
		if (high<A || low>B)
			return INF;
		if (A<=low && high<=B)
			return s[u];
		int L = query(u*2, low, mid(low, high));
		int R = query(u*2+1, mid(low, high)+1, high);
		return min(L, R);
	}
	public:
	void update(int a, int b, int c){
		A=a, B=b, C=c, upd(); /* ustawiamy A, B i C oraz wolamy prawdziwa funkcje update */
	}
	int ask(int a, int b){
		A=a, B=b; /* jak wyzej */
		return query();
	}
};
tree t;
string s;
int a, b, c, q;
auto main() -> int32_t {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin>>q;
	while (q--){
		cin>>s;
		if (s[0]=='u')	cin>>a>>b>>c,	t.update(a, b, c);
		else 			cin>>a>>b,		cout<<t.ask(a, b)<<"\n";
	}
	return 0;
}
