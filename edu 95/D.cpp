#include <bits/stdc++.h>
using namespace std;

const int N=1e5+5;
const int inf=1e9+5;
int n, q;
int a[N];
set<int>pos;
multiset<int>gap;
int cnt;

int L(auto it, int k=1){while (k--) it--; return *it;}
int R(auto it, int k=1){while (k--) it++; return *it;}

int main(){
    scanf ("%d %d", &n, &q);
    pos.insert(inf);
    pos.insert(-inf);
    for (int i=1; i<=n; i++){
        scanf ("%d", &a[i]);
        pos.insert(a[i]);
    }
    sort(a+1, a+1+n);
    for (int i=2; i<=n; i++)
        gap.insert(a[i]-a[i-1]);

    cnt=n;
    if (cnt>=3)
        printf ("%d\n", L(pos.end(), 2)-R(pos.begin())-*gap.rbegin());
    else printf ("0\n");
    while (q--){
        int op, x;
        scanf ("%d %d", &op, &x);
        if (!op){
            auto it = pos.find(x);
            pos.erase(it++);
            if (*it!=inf && L(it)!=-inf)
                gap.insert(*it-L(it)), gap.erase(gap.find(*it-x)), gap.erase(gap.find(x-L(it)));
            else
                if (*it==inf && L(it)!=-inf)
                    gap.erase(gap.find(x-L(it)));
                else if (*it!=inf && L(it)==-inf)
                        gap.erase(gap.find(*it-x));
            cnt--;
        }
        else{
            pos.insert(x);
            auto it = pos.find(x);
            if (L(it)!=-inf && R(it)!=inf)
                gap.erase(gap.find(R(it)-L(it))), gap.insert(*it-L(it)), gap.insert(R(it)-*it);
            else
                if (R(it)==inf && L(it)!=-inf)
                    gap.insert(*it-L(it));
                else if (R(it)!=inf && L(it)==-inf)
                        gap.insert(R(it)-*it);
            cnt++;
        }
        if (cnt>=3)
            printf ("%d\n", L(pos.end(), 2)-R(pos.begin())-*gap.rbegin());
        else printf ("0\n");
    }
}
