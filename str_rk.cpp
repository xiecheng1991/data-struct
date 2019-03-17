#include<iostream>
#include<string>
#include<set>
#define proc 26         //假设只有26个小写英文字母,宏定义进制为26
using namespace std;


int pow( int nums ) {
    int ret;
    for ( int i = 0; i < nums; ++i ) {
        ret *= proc;
    }
    return ret;
}

bool str_rabin_krap( string& str1, string& str2 ) {
    int n = str1.size(), m = str2.size();
    if ( n < m ) return false;

    //先从第一个元素构建大小为m也就是模式串大小的子串的哈希值
    set<int> hash_rec;
    set<int>::iterator it = hash_rec.end();
    int hash_val = 0;
    for ( int i = 0; i < m; ++i ) {
        hash_val = hash_val * proc + str1[i] - 'a';
    } 
    hash_rec.insert( hash_val );  

    for ( int i = 1; i < n - m + 1; ++i ) {
        hash_val = ( hash_val - str1[i-1] * pow( m - 1 ) ) * proc + str1[i+m-1] - 'a';
        hash_rec.insert( hash_val );
    }   

    //构建模式串的哈希值
    int str_num2 = 0;
    for ( int i = 0; i < m; ++i ) {
        str_num2 = str_num2 * proc + str2[i] - 'a';
    }   

    it = hash_rec.find( str_num2 );
    if ( it == hash_rec.end() ) {
        return false;
    } else {
        return true;
    }
}

int main( int argc, char* argv[] ) {
    string str1 = "hello", str2 = "wo";
    if ( str_rabin_krap( str1, str2 ) ) {
        cout << "find it" << endl;
    } else {
        cout << "not find it" << endl;
    }
    return 0;
}