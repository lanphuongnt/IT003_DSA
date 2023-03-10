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

void Xuat(vector<float> array, int start, int end){
    for (int i = start; i < end; i++){
        cout << array[i] << '\n';
    }
    cout << '\n';
}

float showTime(float time_start, float time_end){
    return (time_end - time_start)/CLOCKS_PER_SEC;
}

void Swap(float &x, float &y){
    float t = x;
    x = y;
    y = t;
}

void quickSort(vector<float> &array, int left, int right){
    int i, j;
    i = left;
    j = right;
    float p = array[(left + right)/2];  // chon gia tri ngan 2 ben left right (pivot)
    while (i <= j) { // ton tai doan de xet
        while (array[i] < p) i++;   // tim phan tu lon hon hoac bang pivot
        while (array[j] > p) j--;   // tim phan tu be hon hoac bang pivot
        if (i <= j){
            Swap(array[i], array[j]);       // doi cho 2 phan tu tim duoc o tren
            i++, j--;
        }
    }

    // xet tiep 2 doan-> cac so be hon pivot duoc dua ve phia dau, lon hon pivot dua ve phia cuoi.
    // xet doan [left..j], [i..right] -> thi luc doan duoc thu gon lai thanh dang ai < aj < ak
    // con khi dang xet doan lon thi mang co dang [left..i] <= pivot,  pivot <= [j..right], con [i..j] thi chua biet. 
    if (left < j) quickSort(array, left, j);        
    if (i < right) quickSort(array, i, right);    
}

int main(){
    freopen("test.inp", "r", stdin);
    freopen("test_quick.out", "w", stdout);

    vector<float> arr(NMAX);

    for (int i = 0; i < 10; i++){
        Nhap(arr, NMAX);
        float time_start, time_end;
        time_start = clock();
        quickSort(arr, 0, NMAX - 1);
        time_end = clock();
        cout << "Time " << i + 1 << ": " << showTime(time_start, time_end) << '\n'; 
        // if (i == 4) Xuat(arr, 987655, 987698);
    }
    cout << "Finished.";
    return 0;
}