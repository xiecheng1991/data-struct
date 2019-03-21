#include<iostream>
#include<vector>
using namespace std;

/*
    数据结构堆的实现
*/

class CHeap {
    public:
    CHeap( int count, int capacity ):count(count),capacity(capacity){
        heap = vector<int>(capacity,0);
    }
    ~CHeap(){
    }

    //从尾部插入一个元素
    void Insert( int val );
    //从顶部删除一个元素
    void Delete();
 
    //从下往上的堆化,主要还是用于添加元素的操作
    void HeapModify( int i );

    //打印堆
    void PrintHeap();

    //从上往下堆化
    void HeapModifyFromUpToDown( int i );

    //交换两个元素
    void Swap( int i, int j );

    //通过堆化过程进行排序操作
    void Sort();

    private:
        int count;
        int capacity;
        vector<int> heap;
};

void CHeap::Sort() {
    int index = count;
    while ( index != 0 ) {
        //把堆顶最大的元素放到最后,然后把剩余的count-1个元素再次进行堆化，然后再执行同样的操作
        Swap( 0, --index );
        //跟删除堆顶元素一样的过程
        int i = 0;
        while ( true ) {
            int maxpos = i;
            int temp = maxpos * 2;
            if ( temp <= index-1 && heap[temp] > heap[i] ) {
                Swap( i, temp );
                i = temp;
            }
            if ( temp + 1 <= index-1 && heap[temp+1] > heap[i] ) {
                Swap( i, temp + 1 );
                i = temp + 1;
            }
            if ( maxpos == i ) {
                //已经堆化完成,满足他的左右子树都比他小
                break;
            }
        }
    }
}

void CHeap::PrintHeap(){
    for ( int i = 0; i < count; ++i ) {
        cout << i << " " << heap[i] << endl;
    }
}

//删除堆顶元素自上而下堆化
void CHeap::HeapModifyFromUpToDown( int i ) {
    if ( i > count ) return;
    while ( true ) {
        int maxpos = i;
        int temppos = maxpos * 2;
        if ( temppos <= count && heap[temppos] > heap[i] ) {
            Swap( i, temppos );
            maxpos = temppos;
        }
        if ( temppos + 1 <= count && heap[temppos+1] > heap[i] ) {
            Swap( i, temppos + 1 );
            i = temppos + 1;
        }
        //没有发生堆化，说明已经满足堆结构了
        if ( maxpos == i ) {
            break;
        }
    }
} 

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
            i = temppos;
        }
        //一次堆化都没有发生，说明已经满足堆化结构了
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
    HeapModify( count - 1 );
}

//只能删除堆顶元素
void CHeap::Delete() {
    if ( count <= 0 ) {
        cout <<"堆中没有元素删除失败" << endl;
        return;
    }

    heap[0] = heap[count--];
    //进行从上往下的堆化
    HeapModifyFromUpToDown( 0 );
}

int main( int argc, char* argv[] ) {
    //创建堆
    CHeap* pHeap = new CHeap( 0, 16 );
    
    //插入堆
    for ( int i = 0; i < 5; ++i ) {
        pHeap->Insert( i );
    }
    
    //打印堆
    pHeap->PrintHeap();

    //删除堆定元素
 //   pHeap->Delete();
    pHeap->Sort();

    //打印堆
    pHeap->PrintHeap();

    getchar();

    return 0;
}