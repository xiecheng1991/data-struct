#include<iostream>
#include<string>

using namespace std;

//BF算法
/*
    算法分析:   每次从第一个位置开始始主串和模式串进行匹配如果遇到一个不匹配的字符，则往后挪动一位
                如果完全匹配则匹配成功，总共需要匹配n-m+1次的原因是如果移动到某个字符后面字符少于模式串的长度时没必要再匹配
    时间复杂度: o(n*m)

*/

int brute_force( string& str1, string& str2 ) {
    int m = str1.size(), n = str2.size();
    //这里可以优化一下
    if ( m < n ) return -1;

    for ( int i = 0; i < m - n + 1; ++i ) {
        int count = 0;
        for ( int j = 0; j < n; ++j ) {
            if ( str1[j] != str2[j] ) {
                break;
            }
            count += 1;
        }
        if ( count == n ) {
            return 0;
        }
    }
    return -1;
}

int main( int argc, char* argv ) {
    string str1 = "hello";
    string str2 = "ho";
    if ( brute_force( str1, str2 ) == -1 ) {
        cout << "not find it" << endl;
    } else {
        cout << "find it" << endl; 
    }
    return 0;
}