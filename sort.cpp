#include<iostream>
#include<vector>
using namespace std;

//本文件主要是排序相关代码练习文件

//通用交换函数
void swap( vector<int>& array, int i, int j ) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void PrintEle( const vector<int>& array ) {
    for ( int i = 0; i < array.size(); ++i ) {
        cout << array[i] << " ";
    }
    cout << endl;
}

//冒泡排序
void bubble_sort( vector<int>& array ) {
    int len = array.size();
    //如果数组的元素小于等于一个,就无需排序
    if ( len <= 1 ) return;
    //因为是len个元素一个要比较len次
    for ( int i = 0; i < len; ++i ) {
        bool flag = false;
        //比较一次,最后一个元素就确定是最大的了
        //比较第二次,倒数第二个元素就确定是第二大的了
        //所以j从第一个元素比较到len-i-1未确定最大元素前一个
        for ( int j = 0; j < len - i - 1; ++j ) {
            if ( array[j] > array[j+1] ) {
                swap( array, j, j+1 );
                flag = true;
            }
        }
        //这部分是优化代码,如果某一轮没有发生过交换,说明已经是有序了,就不必再继续循环
        if ( !flag ) {
            return;
        }
    }

}


int main( int argc, char* argv ) {
    vector<int> test{6,2,3,5,4,1};
    bubble_sort( test );
    PrintEle( test );
    getchar();
    return 0;
}