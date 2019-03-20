#include<iostream>
#include<vector>
using namespace std;

/*
    数据结构堆的实现
*/

class CHeap {
    public:
    CHeap( int count, int capacity ):count(count),capacity(capacity){
    }
    ~CHeap(){
    }

    //从尾部插入一个元素
    void Insert( int val );
    //从顶部删除一个元素
    void Delete( int val );
 
    //从下往上的堆化,主要还是用于添加元素的操作
    void HeapModify( int i );

    //交换两个元素
    void Swap( int i, int j );

    private:
        int count;
        int capacity;
        vector<int> heap;
};

void CHeap::Swap( int i, int j ) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void CHeap::HeapModify( int i ) {
    while ( true ) {
        int maxpos = i;
        int temppos = maxpos / 2;
        if ( temppos >= 0 && heap[temppos] < heap[i] ) {
            Swap( i, temppos );
            maxpos = temppos;
        }
        if ( maxpos == i ) {
            break;
        }
    }
}

void CHeap::Insert( int val ) {
    if ( count >= capacity ) {
        cout << "堆中空间不足" << endl;
        return;
    }
    heap[count++] = val;
    //进行堆化过程
    HeapModify( count );
}

//只能删除堆顶元素
void CHeap::Delete( int val ) {
    if ( count <= 0 ) {
        cout <<"堆中没有元素删除失败" << endl;
        return;
    }

    heap[0] = heap[count--];
    //进行从上往下的堆化

}

int main( int argc, char* argv[] ) {
    return 0;
}