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

void heapify(vector<float> &array, int index, int n){
    // khoi tao root largest
    int largest = index;
 
    // left = 2*i + 1
    int left = 2 * index + 1;
 
    // right = 2*i + 2
    int right = 2 * index + 2;
 
    // so sanh left child va root largest
    if (left < n && array[left] > array[largest])
 
        largest = left;
 
    // so sanh right child va cai largest.
    // tuc la tim max cua 3 cai, so sanh voi largest de xem co swap hay khong
    if (right < n && array[right] > array[largest])
 
        largest = right;
 
    // neu root duoc khoi tao ban dau khac voi largest tim duoc thi swap, va cap nhat cai nhanh cua cai child vua duoc swap
    if (largest != index) {
        Swap(array[index], array[largest]);
        // sub-tree
        heapify(array, largest, n);
    }
}

// Main function to do heap sort
void heapSort(vector<float> &array, int n)
{
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, i, n);

    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
        Swap(array[0], array[i]);
        // Lay cai phan tu lon nhat (root) ra khoi heap
        // root lai
        heapify(array, 0, i);
    }
}

int main(){
    freopen("test.inp", "r", stdin);
    freopen("test_heap.out", "w", stdout);

    vector<float> arr(NMAX);

    for (int i = 0; i < 10; i++){
        Nhap(arr, NMAX);
        float time_start, time_end;
        time_start = clock();
        heapSort(arr, NMAX);
        time_end = clock();
        cout << "Time " << i + 1 << ": " << showTime(time_start, time_end) << '\n'; 
        // if (i == 4) Xuat(arr, 987655, 987698);
    }
    cout << "Finished.";
    return 0;
}