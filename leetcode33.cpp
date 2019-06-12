#include<iostream>
#include<vector>
using namespace std;

int main( int argc, char* argv ) {
    vector<int> test{ 4,5,6,7,0,1,2 };
    int l = 0;
    int r = test.size() - 1;
    int target = 4;
    while( l <= r ) {
        int mid = l + ( r - l ) / 2;
        if ( test[mid] == target ) {
            cout << "找到了" << endl;
            return 0;
        }
        if ( test[mid] < target ) {
            l = mid + 1;
        } else if ( test[mid] > target ) {
            if ( target >= test[l] ) {
                r = mid - 1;
            } else if ( target <= test[r] ) {
                l = mid + 1;
            }
        }
    }
    cout << "没找到" << endl;
    return 0;
}