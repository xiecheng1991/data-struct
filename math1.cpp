#include<stdio.h>
#include<stdlib.h>
#include<vector>
using namespace std;


void printrewards( vector<int>& res ) {
    for ( int i = 0; i < res.size(); ++i ) {
        printf( "%d ", res[i] );
    }
    printf( "\n" );
}

void get( int max, vector<int>& res, vector<int>& rewards ) {
    if ( max == 0 ) {
        printrewards( res );
        return;
    }
    if ( max < 0 ) {
        //这种组合超过了10元
        return;
    }
    for ( int i = 0; i < rewards.size(); ++i ) {
        vector<int> copyres = res; //保存当前的状态
        copyres.push_back( rewards[i] );
        get( max - rewards[i], copyres, rewards );
    }
}

int main( int argc, char* argv[] ) {
    vector<int> rewards;//{1, 2, 5, 10};
    rewards.push_back( 1 );
    rewards.push_back( 2 );
    rewards.push_back( 5 );
    rewards.push_back( 10 );
    int max = 10;
    vector<int> res;
    get( max, res, rewards );
    return 0;
}