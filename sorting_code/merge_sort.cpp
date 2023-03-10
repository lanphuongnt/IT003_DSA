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

void merge(vector<float> &array, int left, int mid, int right){
    int subArrayOne = mid - left + 1;
    int subArrayTwo = right - mid;
  
    //Tao 2 cai mang left va right
    float *leftArray = new float[subArrayOne],
         *rightArray = new float[subArrayTwo];
  
    // Copy 2 cai mang left va right
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
  
    int indexOfSubArrayOne = 0, // Khoi tao index cua cai array ben trai
        indexOfSubArrayTwo = 0; // Khoi tao index cua cai array ben phai
    int indexOfMergedArray = left; // Cai vi tri duoc merge 
  
    // Merge the temp arrays back into array[left..right]
    // Giong nhu 2 con tro di song song-> boc tung cai element xep vo mang array
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]){
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy may cai con lai zo array, -> tai truong hop het mang right -> chi con mang left
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Tuong tu voi while o tren
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    // Giai phong bo nho
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(vector<float> &array, int left, int right){
    if (left >= right)
        return; 

    int mid = left + (right - left) / 2;
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
}

int main(){
    freopen("test.inp", "r", stdin);
    freopen("test_merge.out", "w", stdout);

    vector<float> arr(NMAX); // 1 trieu phan tu nen dung vector, hoac mang dong

    for (int i = 0; i < 10; i++){
        Nhap(arr, NMAX);
        float time_start, time_end;
        time_start = clock();
        mergeSort(arr, 0, NMAX - 1);
        time_end = clock();
        cout << "Time " << i + 1 << ": " << showTime(time_start, time_end) << '\n'; 
//        if (i == 3) Xuat(arr, 20);
    }
    cout << "Finished.";
    return 0;
}