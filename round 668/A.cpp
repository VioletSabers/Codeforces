#include <bits/stdc++.h>
using namespace std;

const int N=3e5+5;
int n, K;
char s[N];

int main(){
    int T;
    scanf ("%d", &T);
    while (T--){
        int n, K;
        scanf ("%d %d", &n, &K);
        scanf ("%s",s+1);
        bool flag=1;
        for (int i=K+1; i<=n; i++){
            if (s[i]=='?' && s[i-K]=='?') continue;
            if (s[i]=='?' && s[i-K]!='?') {s[i]=s[i-K]; continue;}
            if (s[i]!='?' && s[i-K]!='?' && s[i]!=s[i-K]) flag=0;
        }
        if (!flag){
            printf ("NO\n");
            continue;
        }
        for (int i=n-K; i>=1; i--){
            if (s[i]=='?' && s[i+K]=='?') continue;
            if (s[i]=='?' && s[i+K]!='?') {s[i]=s[i+K]; continue;}
            if (s[i]!='?' && s[i+K]!='?' && s[i]!=s[i+K]) flag=0;
        }
        if (!flag){
            printf ("NO\n");
            continue;
        }

        int num0, num1, num2;
        num0=num1=num2=0;
        for (int i=1; i<=K; i++){
            if (s[i]=='0') num0++;
            if (s[i]=='1') num1++;
            if (s[i]=='?') num2++;
        }
        if (min(num0, num1)+num2>=max(num0, num1) && K%2==0)
            printf ("YES\n");
        else
            printf ("NO\n");

    }
}
