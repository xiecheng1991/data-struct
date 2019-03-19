#include<iostream>
#include<string>
#include<set>
#define proc 26;                //假设只有26个小写字母 就采用26进制
using namespace std;

int rabin_karp( string& str1, string& str2 ) {
    set<int> res;
    long hash_val = 0;
    for ( int i = 0; i < str1.size(); ++i ) {
        hash_val = hash_val * proc + str1[i] - 'a';
        res.insert( hash_val );
    }

    

    return 0;
}

int main( int argc, char* argv[] ) {

    return 0;
}