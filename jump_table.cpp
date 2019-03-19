#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <random>
#include <ctime>
using namespace std;
#define MAX_LEVEL 16                //跳表最大索引层数

int random_level() {
    int level = 0;
    for ( int i = 0; i < MAX_LEVEL; ++i ) {
        if ( random( 0, 1 ) ) {
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
    private:
        int val;                    //当前结点元素值
        Node* front[MAX_LEVEL];     //保存它在索引层中的后一个元素
};



class Jump_Table {
    public:
    Jump_Table() {
        head = new Node(-1);
        max_level = 0;
        max_level_nodes = 0;
    }
    ~Jump_Table();

    //插入元素
    void insert( int val );

    private:
        Node* head;
        int max_level;              //当前用到的最大索引层数
        int max_level_nodes;        //当前用到的最大索引层中的索引结点数量
};

void Jump_Table::insert( int val ) {
    Node* node = new Node( val );
    int level = randomlev
}


int main( int argc, char* argv[] ) {
    return 0;
}