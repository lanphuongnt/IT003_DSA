#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;
const int NMAX = 1000000;

float result[4][10];

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

void printResult(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 10; j++){
            cout << result[i][j] << '\t';
        }
        cout << '\n';
    }
}

float Time(float time_start, float time_end){
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

void sortingCpp(vector<float> &array){
    sort(array.begin(), array.end());
}

void sorts(vector<float> array, int indexInput){
    vector<float> a1, a2, a3, a0;
    float time_start, time_end;
    a0 = a1 = a2 = a3 = array;
    //QuickSort
    time_start = clock();
    quickSort(a0, 0, NMAX - 1);
    time_end = clock();
    result[0][indexInput] = Time(time_start, time_end);

    //HeapSort
    time_start = clock();
    heapSort(a1, NMAX);
    time_end = clock();
    result[1][indexInput] = Time(time_start, time_end);

    //MergeSort
    time_start = clock();
    mergeSort(a2, 0, NMAX - 1);
    time_end = clock();
    result[2][indexInput] = Time(time_start, time_end);

    //Sort C++
    time_start = clock();
    sortingCpp(a3);
    time_end = clock();
    result[3][indexInput] = Time(time_start, time_end);
}


int main(){
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);

    vector<float> arr(NMAX);

    for (int i = 0; i < 10; i++){
        Nhap(arr, NMAX);
        sorts(arr, i);
    }
    printResult();
    cout << "Finished.";
    return 0;
}