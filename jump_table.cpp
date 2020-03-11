#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <random>
#include <ctime>
using namespace std;
#define MAX_LEVEL 16                //跳表最大索引层数

//跳表的主要核心思想就是 每一层 隔两个或者n个抽出一个到上一级索引层
//
//1->5
//1->3->5->7
//1->2->3->4->5->6->7->8

int random_level() {
    int level = 0;
    for ( int i = 0; i < MAX_LEVEL; ++i ) {
        if ( random() % 100 < 50 ) {
            level++;
        }
    }
    return level;
}
class Node {
    public:
        Node( int val ) {
            this->val = val;
        }
        ~Node();
        int val;                    //当前结点元素值
        Node* front[MAX_LEVEL];     //保存它在索引层中的后一个元素
};


class Jump_Table {
    public:
    Jump_Table( int val ) {
        head = new Node( val );
        max_level = 0;
    }
    ~Jump_Table();

    //插入元素
    void insert( int val );

	void find( int val );

	void del( int val );

	void Print();

	Node* head;
	int max_level;              //当前用到的最大索引层数
//	int max_level_nodes;        //当前用到的最大索引层中的索引结点数量
};

void
Jump_Table::Print(){
	Node* p = head;
	while( p ) {
		printf( "%d ", p->val );
		p = p->front[0];
	}
}

void Jump_Table::insert( int val ) {
    Node* node = new Node( val );
    int level = random_level();
	Node** update = ( Node** ) malloc( sizeof(Node*) * level );
	Node* p = head;
	//找好没一层的前驱结点
	for ( int i = level - 1; i >= 0; --i ) {
		//建立几层索引
		while( p->front[i] && p->front[i]->val < val ) {
			p = p->front[i];
		}
		update[i] = p;
	}
	
	//把新加入的结点插入到索引层中
	for ( int i = 0; i < level; ++i ) {
		Node* temp = update[i]->front[i];
		update[i]->front[i] = node;
		node->front[i] = temp;
	}
	
	if ( level > max_level ) {
		max_level = level;
	}
}

void 
Jump_Table::find( int val ) {
	Node* p = head;

	if ( p->val == val ) {
		printf( "find it:%d\n", p->val );
		return;
	}

	for ( int i = max_level - 1; i >= 0; --i ) {
		while( p->front[i] && p->front[i]->val < val ) {
			p = p->front[i];
		}
	}
	if ( p && p->val == val ) {
		printf( "find it:%d\n", p->val );
		return;
	}
	printf( "not find it\n" );
}

void 
Jump_Table::del( int val ) {
	Node* p = head;
	
	if ( p->val == val ) {
		//删除的是头结点
		head = head->front[0];
		//释放掉这个p结点
		free( p );
	}	

	Node** update = ( Node** ) malloc( sizeof(Node*) * max_level );
	//找出所有的前驱结点
	for ( int i = max_level - 1; i >= 0; --i ) {
		while( p->front[i] && p->front[i]->val < val ) {
			p = p->front[i];
		}
		update[i] = p;
	}

	//执行删除逻辑
	for ( int i = max_level - 1; i >= 0; --i ) {
		if ( update[i]->front[i] && update[i]->front[i]->val == val ) {
			update[i]->front[i] = update[i]->front[i]->front[i];
		}
	}

	printf( "删除完成\n" );
	return;
}



int main( int argc, char* argv[] ) {
	Jump_Table* p = new Jump_Table( 0 );
	for ( int i = 1; i < 5; ++i ) {
		p->insert( i );
	}
	
//删除中间结点的情况
/*
	printf( "find 3" );
	p->find( 3 );

	printf( "del 3" );
	p->del( 3 );

	printf( "find 3" );
	p->find( 3 );
*/

	//删除头结点的情况

	printf( "del 0\n" );
	p->del( 0 );
	p->Print();
    return 0;
}
