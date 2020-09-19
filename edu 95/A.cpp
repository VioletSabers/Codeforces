#include <bits/stdc++.h>
using namespace std;

int main(){
    int T;
    scanf ("%d", &T);
    while (T--){
        long long x, y, k;
        scanf ("%lld %lld %lld", &x, &y, &k);
        printf ("%lld\n", (y*k + k-1 + x-2)/(x-1)+k);
    }
}
