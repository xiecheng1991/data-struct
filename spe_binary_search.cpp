#include<iostream>
#include<vector>
using namespace std;

//查找第一个等于该元素的值
int findfirstequalele( vector<int>& array, int l, int r, int target ) {
    while ( l <= r ) {
        int mid = l + ((r - l) >> 1);
        if ( array[mid] == target && ( ( mid == 0 ) || array[mid-1] != target ) ) {
            return mid;
        } else if ( target <= array[mid] ) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;   
}

int main( int argc, char* argv[] ) {
    vector<int> test{1,2,3,3,4,6,7};
    int res = findfirstequalele( test, 0, test.size() - 1, 11 );
    if ( res == -1 ) {
        cout << "not find it" << endl;
    } else {
        cout << "find it" << endl;
    }
    return 0;
}