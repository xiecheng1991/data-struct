#include<iostream>
#include<vector>
using namespace std;

//查找第一个等于该元素的值
/*
    算法分析:   利用二分查找思想,如果中间结点等于他并且他是第一个元素或者左边的元素不等于它
                否则如果中间结点小于等于他则对右半边区域进行查找
                否则对左半边区域进行查找
    时间复杂度:  o(logn)
    空间复杂度:  o(1)
*/
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

//查找最后一个等于该元素的字符串
/*
    算法分析:   通过二分查找思想，如果中间结点等于他，并且他是最后一个元素或者
                最后一个元素不等于他则已经找到了
                如果中间元素大于等于他把查找区间改为左半部分
                否则改为右半部分,然后重复同样的操作
    时间复杂度: o(logn)
    空间复杂度: o(1)
*/
int findlastequalele( vector<int>& array, int l, int r, int target ) {
    int last = r;
    while ( l <= r ) {
        int mid = l + ( ( r - l ) >> 1 );
        if ( array[mid] == target && ( ( mid == last ) || ( array[mid+1] != target ) ) ) {
            return mid;
        } else if ( target > array[mid] ) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

int main( int argc, char* argv[] ) {
    vector<int> test{1,2,3,3,4,6,7};
//    int res = findfirstequalele( test, 0, test.size() - 1, 7 );
    int res = findlastequalele( test, 0, test.size() - 1, 11 );
    if ( res == -1 ) {
        cout << "not find it" << endl;
    } else {
        cout << "find it" << endl;
    }
    return 0;
}