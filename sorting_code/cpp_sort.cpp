#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;
const int NMAX = 1000000;

void Nhap(vector<float> &array, int n){
    for (int i = 0; i < n; i++){
        cin >> array[i];
    }
}

void Xuat(vector<float> array, int n){
    for (int i = 0; i < n; i++){
        cout << array[i] << '\n';
    }
    cout << '\n';
}

float showTime(float time_start, float time_end){
    return (time_end - time_start)/CLOCKS_PER_SEC;
}

int main(){
    freopen("test.inp", "r", stdin);
    freopen("test_cpp.out", "w", stdout);

    vector<float> arr(NMAX); // 1 trieu phan tu nen dung vector, hoac mang dong

    for (int i = 0; i < 10; i++){
        Nhap(arr, NMAX);
        float time_start, time_end;
        time_start = clock();
        sort(arr.begin(), arr.end());
        time_end = clock();
        cout << "Time " << i + 1 << ": " << showTime(time_start, time_end) << '\n'; 
        //Xuat(arr, NMAX);
    }
    cout << "Finished.";
    return 0;
}