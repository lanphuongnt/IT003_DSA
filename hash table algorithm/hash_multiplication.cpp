#include <bits/stdc++.h>

using namespace std;
const double A = 0.61803398;

int getHashBit(string bit, int mod){
    double res = 0;
    double base = 3;
    for (int i = 0; i < bit.size(); i++){
        res = (res * base + (bit[i] - '0' + 1) * A);
        res = res - (int)res;
    }
    return (int) (mod * res);
}

int getFirstHash(string bit, int mod){
    return getHashBit(bit, mod);
}

int getSecondHash(string bit, int prime){
    return prime - getHashBit(bit, prime);
}

int getHash(bool hashTable[], string bit, int mod, int prime){
    int hash1 = getFirstHash(bit, mod);
    int hash2 = getSecondHash(bit, prime);
    int hash = hash1;
    while (hashTable[hash]){
        hash = (hash + hash2) % mod;
    }
    return hash;
}



int main(){
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);

    int M = 11;      
    int prime = 7;    
    bool hashTable[M] = {false};
    for (int i = 0; i < M; i++){
        string bit;
        cin >> bit;
        int ID = getHash(hashTable, bit, M, prime);
        cout << ID << '\n';
        hashTable[ID] = true;     
    }
   cout << "This is hashtable: \n";
   for (int i = 0; i < M; i++){
       cout << hashTable[i] << ' ';
   }
    return 0;
}