#include<bits/stdc++.h>

using namespace std;
string getPathInput(int index){
    return "test_" + to_string(index) + ".inp";
}

int main(){
    srand(time(NULL));
    const int NMIN = 1000000 * 5 / 7;
    for (int i = 1; i <= 10; i++){
        string testCase = "test_" + to_string(i) + ".inp";
        ofstream fo;
        fo.open(testCase);
        int n = NMIN + (rand() % NMIN) * 17;
        fo << n << '\n';
        for (int j = 0; j < n; j++){
            fo << rand() % 1000000 + 1 << ' ';
        }
        fo.close();
    }
    return 0;
}