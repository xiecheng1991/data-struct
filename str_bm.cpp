#include<iostream>
#include<string>
#include<map>
using namespace std;

map< int, int > bc;

void generatorbc( string& str2 ) {
    //对模式串进行哈希映射
    for ( int i = 0; i < str2.size(); ++i ) {
        //map[int(str2[i])] = i;
        int ascii = int( str2[i] );
        bc[ascii] = i;
    }
}

int badcharacter( string& str1, string& str2 ) {
    int n = str1.size(), m = str2.size();
    generatorbc( str2 );
    int i = 0;  //模式串和主串开始匹配时i在主串中的下标
    while ( i < n - m ) {
        for ( int j = m - 1; j >= 0; --j ) {
            if ( str1[i+j] != str2[j] ) {
                //找到一个不匹配的,是从后往前匹配
                break;
            }
            if ( j < 0 ) {
                //已经完全匹配了
                return 0;
            } else {
                int index = str1[i+j];
                i = i + ( j - bc[index] );
            }
        }
    }
    return -1;
}

int main( int argc, char* argv ) {
    string s1( "hello", "lo" );
    if ( badcharacter( "aba", "ab" ) == -1 ) {
        cout << "未匹配成功" << endl;
    } else {
        cout << "匹配成功" << endl;
    }
    return 0;
}