#include<stdio.h>
#include<stdlib.h>
#include<vector>
using namespace std;

void helper( char* p, char* pw, vector<char>& res ) {
    if ( res.size() == 4 ) {
        int i = 0;
        for ( ; i < 4; ++i ) {
            if ( p[i] != res[i] ) return;
        }
        if ( i == 4 ){
            printf("find mima\n");
        } 
        return;
    }
    for ( int i = 0; i < 5; ++i ) {
        vector<char> path = res;
        path.push_back( p[i] );
        helper( p, pw, path );
    }
}

int main( int argc, char* argv[] ) {
    char p[] = { 'a', 'b', 'c', 'd', 'e' };
    char* password = "bcda";
    vector<char> res;
    helper( p, password, res );
    return 0;
}