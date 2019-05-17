#include<stdlib.h>
#include<stdio.h>
#include<vector>
using namespace std;
void printpath( vector<int>& res ) {
    for ( int i = 0; i < res.size(); ++i ) {
        printf( "%d ", res[i] );
    }
    printf( "\n" );
}

void get( int target, int cur, vector<int>& res ) {
    if ( cur > target ) return;
    if ( cur == target ) {
        //已经找到乘积
        printpath( res );
        return;
    }

    for ( int i = 1; i < target; ++i ) {
        vector<int> copyres = res; //copy一个状态
        if ( copyres.size() > 0 && i == 1 ) {
            continue;
        }
        copyres.push_back( i );
        get( target, cur * i, copyres );
    }

}

int main( int argc, char* argv[] ) {
    vector<int> res;
    get( 6, 1, res );
    getchar();
    return 0;
}