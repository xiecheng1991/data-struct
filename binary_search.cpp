#include<iostream>
#include<vector>
using namespace std;

int main( int argc, char* argv[] ) {
    vector<int> test{1,2,3,4,5,6};
    int target = 3;
    int low = 0, high = 5;
    //循环方式实现二分查找
    while ( low <= high ) {
        int mid = low + ( high - low ) >> 1;
        if ( test[mid] == target ) {
            cout << "find it" << endl;
            return 0;
        } else if ( test[mid] > target ) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }   
    cout << "not find" << endl;
    return 0;
}