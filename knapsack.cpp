#include<stdio.h>
#include<stdlib.h>
#include<vector>
using namespace std;

vector<int> items = { 2,2,4,6,3 }; 	//物品重量
vector<int> value = { 3,4,8,9,6 };  //物品价值
const int count = 5; 		//物品最大数量为5
const int w = 9;  			//背包所能承受的最大重量为9

//题目要求在满足背包最大重量前提下 物品的价值最高

int
main( int argc, char* argv[] ) {
	vector<int> states(w+1, 0); 	//dp状态为 当前重量的情况下 所能达到的最大价值
	//初始化第一个
	states[0] = 0;
	//放入第一个道具
	states[items[0]] = value[0];

	

	for ( int i = 1; i < count; ++i ) {

		//考虑不放的情况
		for ( int j = 0; j <= w - items[i]; ++j ) {
			if ( states[j] > 0 ) {
				states[j+items[i]] = states[j];
			}
		}	

		for ( int j = 0; j <= w - items[i]; ++j ) {
			if ( states[j] + value[i] > states[j+items[i]] ) {
				states[j+items[i]] = states[j] + value[i];
			}
		}
	}
	printf( "max value:%d\n", states[w] );

}
