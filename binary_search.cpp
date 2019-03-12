#include<iostream>
#include<vector>
using namespace std;

int helper( vector<int>& array, int low, int high, int target ) {
    if ( low > high ) return -1; //没有找到
    int mid = low + ( ( high - low ) >> 1 );
    if ( array[mid] == target ) {
        return mid;
    } else if ( array[mid] > target  ) {
        return helper( array, low, mid - 1, target );
    } else {
        return helper( array, mid + 1, high, target );
    }
}

int main( int argc, char* argv[] ) {
    vector<int> test{1,2,3,4,5,6};
    int target = 100;
    int low = 0, high = 5;
    //用递归方式实现二分查找
    int res = helper( test, low, high, target );
    if ( res == -1 ) {
        cout << "not find it" << endl;
    } else {
        cout << "find it" << endl;
    }
    /*
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
    */
    return 0;
}