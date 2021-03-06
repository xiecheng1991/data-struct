#include<iostream>
#include<vector>
using namespace std;

//本文件主要是排序相关代码练习文件

//通用交换函数
void swap( vector<int>& array, int i, int j ) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void PrintEle( const vector<int>& array ) {
    for ( int i = 0; i < array.size(); ++i ) {
        cout << array[i] << " ";
    }
    cout << endl;
}

//冒泡排序
/*
    算法分析:
    时间复杂度分析: 最好情况已经有序复杂度为o1
                   最坏情况全部逆序时间复杂度为0n
    空间复杂度分析: 未使用额外的空间,所以空间复杂度为01，也叫原地排序
    稳定性分析:     相同元素前后顺序未发生改变,所以是稳定的
*/
void bubble_sort( vector<int>& array ) {
    int len = array.size();
    //如果数组的元素小于等于一个,就无需排序
    if ( len <= 1 ) return;
    //因为是len个元素一个要比较len次
    for ( int i = 0; i < len; ++i ) {
        bool flag = false;
        //比较一次,最后一个元素就确定是最大的了
        //比较第二次,倒数第二个元素就确定是第二大的了
        //所以j从第一个元素比较到len-i-1未确定最大元素前一个
        for ( int j = 0; j < len - i - 1; ++j ) {
            if ( array[j] > array[j+1] ) {
                swap( array, j, j+1 );
                flag = true;
            }
        }
        //这部分是优化代码,如果某一轮没有发生过交换,说明已经是有序了,就不必再继续循环
        if ( !flag ) {
            return;
        }
    }

}

//插入排序
/*
    算法分析: 时间复杂度: o(n平方)
            空间复杂: 0(1)未使用额外的空间,原地排序
            稳定排序: 相同元素位置未发生改变所以是稳定排序
*/
void insert_sort( vector<int>& array ) {
    int len = array.size();
    //如果数组元素小于等于一个就无需排序
    if ( len <= 1 ) return;
    //默认第一个元素已经有序了,从第二个元素开始往前找到合适的位置插入
    for ( int i = 1; i < len; ++i ) {
        int value = array[i];
        int j = i - 1;
        // 这里粗心犯了个错--j 写成了++j 粗心
        for ( ; j >= 0; --j ) {
            //如果当前元素比value(要插入元素大,则将该元素往后移动一位)
            if ( array[j] > value ) {
                array[j+1] = array[j];
            } else {
                //找到了合适的位置
                break;
            }
        }
        //放入合适的位置,因为是往后移动一位当第j个元素比他小那么合适的位置为j+1
        array[j+1] = value;
    }
}

//选择排序
/*
    算法分析: 
            时间复杂度: 每一轮都会把未排序区间内的所有元素都遍历一遍所以为o(n平方)
            空间复杂度: 未使用额外的空间,所以为01， 原地排序
            稳定性: 因为是进行元素的交换,所以破坏了稳定性,是不稳定排序
*/
void select_sort( vector<int>& array ) {
    int len = array.size();
    if ( len <= 1 ) {
        return;
    }
    //类似插入排序 也分为已排序和未排序 每次从未排序的区间中找到一个最小的元素进行插入
    //并和当前第i个元素进行交换
    for ( int i = 0; i < len; ++i ) {
        int min = i;
        for ( int j = i; j < len; ++j ) {
            min = array[min] <= array[j] ? min : j;
        }
        if ( i != min ) {
            swap( array, min, i );
        }
    } 
}

//合并两个已排序区间
void merge( vector<int>& array, int ll, int lr, int rl, int rr ) {
    vector<int> tmp;
    int templl = ll;
    int index = 0;
    while ( ll <= lr && rl <= rr ) {
        if ( array[ll] <= array[rl] ) {
            tmp.push_back( array[ll] );
            ll++;
        } else {
            tmp.push_back( array[rl] );
            rl++;
        }
    }
    int start = ll, end = lr;
    if ( rl <= rr ) {
        start = rl;
        end = rr;
    }
    while ( start <= end ) {
        tmp.push_back( array[start++] );
    }
    //把临时数组内的内容拷贝到要合并的区间
    for ( int i = 0; i < tmp.size(); ++i ) {
        array[templl+i] = tmp[i];
    }
}

//归并排序
/*
    算法分析:
        时间复杂度: o(nlogn)分析过程太复杂
        空间复杂度: 要额外申请内容空间，保存排序好的元素 o(n) 非原地
        稳定性:    排序后相同元素前后顺序未发生变化所以是稳定的(关键看merge函数的实现)
*/
void merge_sort( vector<int>& array, int l, int r ) {
    if ( l >= r ) return;
    int mid = l + ( r - l ) / 2;
    merge_sort( array, l, mid );
    merge_sort( array, mid + 1, r );
    merge( array, l, mid, mid+1, r );
}

int partition( vector<int>& array, int l, int r ) {
    int i = l; //游标
    int temp = array[r]; //这个位置当时犯了个错,没有把要比较的值保存起来,导致要比较的值其实已经变了
    for ( int j = l; j < r; ++j ) {
        if ( array[j] < temp ) {
            swap( array, i, j );
            i++;
        }
    }
    swap( array, i, r );
    return i;
}

void quick_sort_c( vector<int>& array, int l, int r ) {
    if ( l >= r ) return;
    int pvoit = partition( array, l, r );
    //******************************重点 分区的时候 左右两边不能包含分界点或者会死循环
    //这里也犯了个错误 pvoit没有-1 导致死循环
    quick_sort_c( array, l, pvoit - 1 );
    quick_sort_c( array, pvoit+1, r );
}

//快速排序
/*
    //核心原理: 找到一个分界点,使得左边的元素都比他小右边的元素都比他大
    //          然后对左边和右边都进行同样的处理 直到分区区间只有一个元素
    //            为止就完成排序
    快速排序分析:
            时间复杂度分析: o( nlogn )
            空间复杂度: o(1) 未使用额外的空间,原地排序
            稳定性:     涉及到元素的交换,非稳定性排序
*/
void quick_sort( vector<int>& array ) {
    //元素数量小于等于1就没必要排序
    int len = array.size();
    if ( len <= 1 ) return;
    quick_sort_c( array, 0, len - 1 );
} 

int main( int argc, char* argv ) {
    vector<int> test{6,2,3,5,4,1};
 //   bubble_sort( test );
 //   insert_sort( test );
 //   select_sort( test );
 //   merge_sort( test, 0, test.size()-1 );
    quick_sort( test );
    PrintEle( test );
    getchar();
    return 0;
}