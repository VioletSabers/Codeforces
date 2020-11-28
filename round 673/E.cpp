#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N=5e5+5;
int a[N];
set<pll>one;
ll bias, mul;
ll two, zero;

int f[100][100];

ll S(ll x){return bias+mul*x;}
ll T(ll x){return (x-bias)/mul;}

int Judge(auto it, ll lim){
    ll l=min(S(it->fi), S(it->se)), r=max(S(it->fi), S(it->se));
    if (r<1 || l>=lim) return 0;
    if (1<=l && r<=lim-1) return 2;
    return 1;
}

int main(){
    int Cas, n;
    scanf ("%d", &Cas);
    srand(time(0));
    while (Cas--){
        scanf ("%d", &n);
        for (int i=1; i<=n; i++) scanf ("%d", &a[i]);
        one.clear();
        two=-1, zero=0;
        mul=1, bias=0;
        for (int i=1; i<=n; i++){
            if (two!=-1){
                zero+=2;
                bias=0;
                mul=1;
                one.clear();
                if (two<a[i])
                    one.insert(mp(a[i]-two, a[i]-two));
                two=-1;
            }
            else{
                if (!one.empty()){
                    zero+=1;
                    bias=a[i]-bias;
                    mul=mul*(-1);
                    while (!one.empty()){
                        if (!Judge(one.begin(), a[i]))
                            one.erase(one.begin());
                        else break;
                    }

                    while (!one.empty()){
                        if (!Judge(one.rbegin(), a[i]))
                            one.erase(--one.end());
                        else break;
                    }

                    if (!one.empty() && Judge(one.begin(), a[i])==1){
                        ll x=one.begin()->fi, y=one.begin()->se;
                        ll l=min(S(x), S(y)), r=max(S(x), S(y));
                        l=max(1ll, l), r=min(r, (ll)a[i]-1);
                        //printf ("%d %d\n", l, r);
                        if (l<=r){
                            pii tmp=mp(min(T(l), T(r)), max(T(l), T(r)));
                            one.erase(one.begin());
                            one.insert(tmp);
                        }
                    }

                    if (!one.empty() && Judge(one.rbegin(), a[i])==1){
                        ll x=one.rbegin()->fi, y=one.rbegin()->se;
                        ll l=min(S(x), S(y)), r=max(S(x), S(y));
                        l=max(1ll, l), r=min(r, (ll)a[i]-1);
                        if (l<=r){
                            pii tmp=mp(min(T(l), T(r)), max(T(l), T(r)));
                            one.erase(--one.end());
                            one.insert(tmp);
                        }
                    }
                }
                else{
                    bias=0;
                    mul=1;
                    if (i!=1)
                        one.insert(mp(max(a[i]-(a[i-1]-1), 1), a[i]-1));
                }
            }
            if (a[i]%2==0){
                bool flag=0;
                ll x=a[i]/2;
                if (!one.empty()){
                    auto it=one.upper_bound(mp(T(x), 1e9));
                    if (it!=one.begin()){
                        --it;
                        ll l=min(S(it->fi), S(it->se)), r=max(S(it->fi), S(it->se));
                        if (l<=x && x<=r)
                            two=x, flag=1;
                    }
                }
                if (!flag)
                    one.insert(mp(T(x), T(x)));
            }
/*
            printf ("--------------------------\n");
            printf ("epoch = %d\n", i);
            printf ("two = %d\n", two);
            printf ("bias = %d mul = %d\n", bias, mul);
            printf ("one = \n");
            for (auto it=one.begin(); it!=one.end(); ++it){
                int l, r;
                l=min(S(it->fi), S(it->se)), r=max(S(it->fi), S(it->se));
                printf ("l=%d r=%d\n", l, r);
            }
            printf ("zero=%d\n", zero);
*/
        }
    ll ans;
    if (two!=-1)
        ans=zero+2;
    else if (!one.empty())
        ans=zero+1;
    else
        ans=zero;
    printf ("%lld\n", 2*n-ans);
    }
}

