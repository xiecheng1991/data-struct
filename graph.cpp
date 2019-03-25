/*
    图的表示以及基本操作
*/
#include<iostream>
#include<vector>
#include<queue>
#include<map>
using namespace std;

typedef struct vertex {
    vertex( int val ) {
        this->val = val;
        pnext = NULL;
    }
    int val;
    struct vertex* pnext;
} vertex;

class CGraph {
    public:
        CGraph( int num ) { 
            vertexnum = num;
            vertexInfo = vector<vertex*>( vertexnum, NULL );
         }
         ~CGraph() {
         }
         
         //建立顶点3和顶点t之间的边关系
        void AddEdge( int s, int t );

        //往某一个顶点里插入边的关系
        void Insert( vertex* psrc, vertex* pdest );

        //bfs遍历 广度优先 遍历图
        void bfs ( int s, int t );
    private:
        int vertexnum;         //图的顶点数量
        vector<vertex*>  vertexInfo; //图的各个顶点所能到达顶点
};

void printpath( map<int, int>& pre, int s, int t ) {
    if ( pre[t] != -1 && t != s ) {
        printpath( pre, s, pre[t] );
    }
    cout << t << "->" << endl;
}

void CGraph::bfs( int s, int t ) {
    map<int, int> pre;
    vector<bool> visited( vertexnum, false );
    queue<int> q;
    for ( int i = 1; i <= vertexnum; ++i ) {
        pre[i] = -1;
    }

    q.push( s );
    while ( !q.empty() ) {
        for ( int i = 0; i < q.size(); ++i ) {
            int vid = q.front();
            if ( vid == t ) {
                //已经找到了,打印路径
                return;
            }
            q.pop();
            if ( !visited[vid] ) {
                visited[vid] = true;
                vertex* ptemp = vertexInfo[s];
                while ( ptemp != NULL ) {
                    q.push( ptemp->val );
                    ptemp = ptemp->pnext;
                    pre[ptemp->val] = vid;
                }
            }
        }
    }

}

void CGraph::Insert( vertex* psrc, vertex* pdest ) {
    if ( psrc == NULL ) {
        return;
    }
    while ( psrc->pnext != NULL ) {
        psrc = psrc->pnext;
    }
    psrc->pnext = pdest;
}

void CGraph::AddEdge( int s, int t ) {
    vertex* pvs = new vertex(s);
    vertex* pvt = new vertex(t);
    vertex* ptemp = vertexInfo[s];
    if ( ptemp == NULL ) {
        vertexInfo[s] = pvt;
    } else {
        Insert( ptemp, pvt );
    }
    
    ptemp = vertexInfo[t];
    if ( ptemp == NULL ) {
        vertexInfo[t] = pvs;
    } else {
        Insert( ptemp, pvs );
    }
}

int main( int argc, char* argv[] ) {
    CGraph* p = new CGraph(3);
    p->AddEdge( 1, 2 );
    p->AddEdge( 1, 3 );
    p->bfs( 1, 3 );
    return 0;
}