#include <bits/stdc++.h>

using namespace std;

int main(){
    srand(time(NULL));
    freopen("test.inp", "r", stdin);
    freopen("test.inp", "w", stdout);

    int M = 103;
    int prime = 101;
    //cout << M << '\n';
    for (int i = 0; i < M; i++){
        for (int i = 0; i < 100; i++){
            cout << rand() % 2;
        }
        cout << '\n';
    }
    return 0;
}