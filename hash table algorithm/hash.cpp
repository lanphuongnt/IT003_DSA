#include <iostream>
#include <string>

using namespace std;

// Chuyen day bit thanh dang hash va chia lay du cho mod
int getHashBit(string bit, int mod){
    long long res = 0;
    /*
        * Chon base la so nguyen to lon hon so ki tu khac nhau cua day bit, tuc la 0 va 1
        * De tranh tinh trang dung do (collision)
    */
    int base = 3;  
    for (int i = 0; i < bit.size(); i++){
        res = (res * base + bit[i] - '0' + 1) % mod; // co them +1 de tranh bi hack (ma hoa ki tu '0' thanh 0)
    }
    return (int) res; // tra ve gia tri trong pham vi mod -> co kieu int
}

/*
    * Vi su dung Double Hashing de tranh dung do, nen co 2 ham hash.
*/
int getFirstHash(string bit, int mod){
    return getHashBit(bit, mod);
}

/*
    * Prime la so nguyen to lon nhat be hon so phan tu cua Hash Table
*/
int getSecondHash(string bit, int prime){
    return prime - getHashBit(bit, prime);
}


/*
    * mod la so phan tu cua Hash Table, nen la so nguyen to de tranh dung do
    * Ham duoi day su dung Double Hashing
*/
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
    freopen("test.ans", "w", stdout);

    int M = 11;        //
    int prime = 7;     // So nguyen to lon nhat nho hon M - kich thuoc Hash Table
    
    bool hashTable[M] = {false};    // Kieu du lieu la bool vi trong chuong trinh nay chi xet xem hash function co bam dung hay khong

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