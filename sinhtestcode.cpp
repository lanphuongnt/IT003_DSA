#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;
const int NMAX = 1000000;
const double min_rand = -100000;
const double max_rand = 100000;

vector<double> arr(NMAX); // mang gia tri random 

// random so thuc trong doan min max
float random_real(double min = min_rand, double max = max_rand){
    random_device rd;
    default_random_engine generator(rd());
    uniform_real_distribution<double> distribution(min,max); 
    return distribution(generator);
}

// random 1 mang/vector so thuc 
vector<double> random_vector(vector<double> &array, int n = NMAX){
    for (int i = 0; i < n; i++){
        array[i] = random_real();
    }
    return array;
}

// in ra vector a
void print_array(vector<double> array){
    for (double element : array){
        cout << element << ' ';
    }
    cout << '\n';
}

int main(){
    freopen("test.out", "r", stdin);
    freopen("test.inp", "w", stdout);

    // day thu nhat co thu tu tang dan
    random_vector(arr);
    sort(arr.begin(), arr.end());
    print_array(arr);
   
    // day thu hai co thu tu giam dan
    random_vector(arr);
    sort(arr.begin(), arr.end(), greater<double>());
    print_array(arr);
   
    // 8 day con lai thu tu ngau nhien
    for (int i = 0; i < 8; i++){
        random_vector(arr);
        print_array(arr);
    }

    return 0;
}