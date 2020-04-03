#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<limits.h>
using namespace std;

typedef struct Vertext{
	int id; 		//顶点编号
	int dist; 		//起始点到这个点的距离
}Vertext;

typedef struct Small_Heap{
	int cap; 							//小顶堆 容量
	int size; 							//小顶堆 数量
	vector<Vertext*> list; 				//小顶堆 底层数组
} Small_Heap;

extern void Heap( Small_Heap* sh );

//顶点与顶点之间的边数据
typedef struct Edge {
	int sid; 	//顶点的编号
	int tid; 	//结束点编号
	int w; 		//边的权重
}Edge;

//创建一条边
Edge* 
CreateEdge( int sid, int tid, int w ) {
	Edge* e = new Edge;
	e->sid = sid;
	e->tid = tid;
	e->w = w;
	return e;
}

//图的数据表示
typedef struct Graph {
	vector<vector<Edge*>> list; 		//各个顶点边的情况
	int v; 								//顶点的个数
}Graph;

//创建一个图
Graph* 
CreateGraph( int v ) {
	Graph* g = new Graph;
	g->v = v;
	for ( int i = 0; i < v; ++i ) {
		vector<Edge*> t;
		g->list.push_back( t );
	}
	return g;
}

void
AddEdge( Graph* g, int sid, int tid, int w ) {
	if ( g == NULL ) {
		printf( "图还未初始化\n" );
		return;
	}
	Edge* e = CreateEdge( sid, tid, w );
	if ( e == NULL ) {
		printf( "创建边失败\n" );
		return;
	}
	g->list[sid].push_back( e );
//	g->list[tid].push_back( e );
}


Vertext*
CreateVertext( int id, int dist ) {
	Vertext* v = new Vertext;
	v->id = id;
	v->dist = dist;
	return v;
}


Small_Heap* 
CreateSmallHeap( int cap ){
	Small_Heap* sh = new Small_Heap;
	sh->cap = cap;
	sh->size = 0;
	sh->list = vector<Vertext*>(5,NULL);
	return sh;
}

bool
Push( Small_Heap* sh, Vertext* v ) {
	if ( sh == NULL ) {
		printf( "还未初始化小顶堆\n" );
		return false;
	}

	if ( v == NULL ) {
		printf( "还未初始化v" );
		return false;
	}

	if ( sh->size == sh->cap ) {
		printf( "小顶堆已满\n" );
		return false;
	}

	sh->list[sh->size++] = v;
	Heap( sh );
	return true;
}

Vertext*
Poll( Small_Heap* sh ) {
	if ( sh == NULL || sh->size == 0 ) {
		printf( "小顶堆还未初始化或者没有元素" );
		return NULL;
	}
	Vertext* v = sh->list[0];
	sh->list[0] = sh->list[--sh->size];
	Heap( sh );
	return v;
}

void
Update( Small_Heap* sh, Vertext* v ) {
	if ( sh == NULL ) {
		printf( "小顶堆还未初始化\n" );
		return;
	}
	if ( sh->size < v->id ) {
		printf( "还未插入过该结点:%d\n", v->id );
		return;
	}
	sh->list[v->id] = v;
}

void
Heap( Small_Heap* sh ) {
	if ( sh == NULL ) {
		printf( "小顶堆还未初始化\n" );
		return;
	}

	int t = sh->size-1;
	while( t > 0 ) {
		//小顶堆堆化过程 如果该结点的值比他父结点的值还小 就需要交换
		//大顶堆堆化过程 则相反比他大 就交换
		//这里因为是以0为堆顶 所以 对应的左右子树分别为2n+1 2n+2
		//so
		int ifather = ( t - 1 ) / 2;
		if ( t % 2 == 0 ) {
			ifather = ( t - 2 ) / 2;
		}
		if ( sh->list[t]->dist < sh->list[ifather]->dist ) {
			Vertext* v = sh->list[t];
			sh->list[t] = sh->list[ifather];
			sh->list[ifather] = v;
		}
		t = ifather;
	}
}

bool 
IsEmpty( Small_Heap* sh ) {
	if ( sh == NULL ) {
		printf( "小顶堆还未初始化\n" );
		return false;
	}
	return sh->size == 0;
}

void 
print( int s, int t, int* predecessor ) {
	if ( s == t ) {
		return;
	}
	print( s, predecessor[t], predecessor );
	printf( "->%d", t );
}

void
dijkstra( Graph* g, int sid, int tid ) {
	//打印出最短路劲
	int* predecessor = new int[g->v]; 	//用来还原最短路径
	if ( predecessor == NULL ) {
		return;
	}
	Vertext** vtt = new Vertext*[g->v];
	for ( int i = 0; i < g->v; ++i ) {
		vtt[i] = CreateVertext( i, INT_MAX );
	}
	Small_Heap* sh = CreateSmallHeap( g->v );
	if ( sh == NULL ) {
		printf( "初始化小顶堆失败\n" );
		return;
	}
	bool* inqueue = new bool[g->v];
	if ( NULL == inqueue ) {
		return;
	}


	//首先把起始点入堆
	vtt[sid]->dist = 0;
	Push( sh, vtt[sid] );
	
	while( !IsEmpty( sh ) ) {
		Vertext* minvertext = Poll( sh );
		if( NULL == minvertext ) {
			continue;
		}

		if ( minvertext->id == tid ) {
			printf( "最短路径已经产生\n" );
			break;
		}

		//取它的边
		for ( int i = 0; i < g->list[minvertext->id].size(); ++i ) {
			Edge* e = g->list[minvertext->id][i];
			Vertext* nextvertext = vtt[e->tid];
			//判断和他边的顶点的距离
			if ( minvertext->dist + e->w < nextvertext->dist ) {
				//需要更新nextvertext的dist
				nextvertext->dist = minvertext->dist + e->w;
				predecessor[nextvertext->id] = minvertext->id;
				if ( inqueue[nextvertext->id] ) {
					//如果nextvertext在队列中
					Update( sh, nextvertext );
				} else {
					Push( sh, nextvertext );
					inqueue[nextvertext->id] = true;
				}
			}
		}
	}
	printf( "%d", sid );
	print( sid, tid, predecessor );
}

int 
main( int argc, char* argv[] ) {
	Graph* g = CreateGraph( 5 );
	AddEdge( g, 0, 1, 3 );
	AddEdge( g, 0, 2, 4 );
	AddEdge( g, 1, 3, 2 );
	AddEdge( g, 1, 4, 2 );
	AddEdge( g, 2, 3, 2 );
	AddEdge( g, 3, 4, 1 );
	dijkstra( g, 1, 4 );
	return 0;
}
