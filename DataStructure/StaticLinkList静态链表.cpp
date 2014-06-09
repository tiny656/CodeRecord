开辟一块数组空间用来在非指针的程序中维护数组链表。
定义：
SLinkList共有MAX个元素，节点是有数据域Data和游标域Cur组成
其中第一个元素节点SLinkList[0]用来记录备用链表的头节点。最后一个节点SLinkList[maxn - 1]用来记录链表的头结点。
如果链表头结点的Cur为0，则链表为空。
备用链表节点即是未使用的节点空间。


const int maxn = 1000;//定义链表中的节点元素个数
//1.Node节点定义
/*静态链表节点元素*/
template <class ElemType>
class Node {
public:
    ElemType data;
    int cur;
};
//2.静态链表定义
/*静态链表*/
template<class ElemType>
class StaticLinkList {
public:
    void Init(); //初始化链表
    bool Insert(int pos, ElemType e); //在链表的第pos个位置插入元素
    bool Insert(ElemType e); //在链表的末尾插入元素
    bool Delete(int pos); //删除第pos个位置的元素
    int  Length(); //获取链表的长度
    bool Empty(); //判断链表是否为空
    void Traverse(); //遍历链表
    bool GetElement(int pos, ElemType &e); //获取第pos位置的元素
private:
    //链表
    Node <ElemType> SLinkList[maxn];
    int len;
    //处理备用链表用，分配和回收节点
    int Malloc(); //分配备用链表中的一个空位置
    void Free(int pos); //将位置为pos的空闲节点释放
};
//3.初始化链表，链表头结点为空，其余元素连接组成备用链表。
/*初始化静态链表*/
template<class ElemType>
void StaticLinkList<ElemType>::Init() {
    cout << "----Init the Link List----" << endl;

    //初始化备用链表
    for (int i = 0; i < maxn - 1; i++)
        SLinkList[i].cur = i + 1;

    SLinkList[maxn - 2].cur = 0; //作为备用链表的末尾保护，指向0空 或 可以认为指向循环备用链表的头结点
    SLinkList[maxn - 1].cur = 0; //链表头结点为空
    this->len = 0;  //链表长度为0
}
//4.插入元素
//4.1在pos位置插入元素
/*在第Pos个位置插入元素*/
template<class ElemType>
bool StaticLinkList<ElemType>::Insert(int pos, ElemType e) {
    cout << "----Insert Element in pos---- -> " << pos << " : " << e << endl;

    if (pos < 1 || pos > this->Length() + 1)
        cout << "----Failed : Input Pos Error----" << endl;

    int cur_idx = maxn - 1;
    int mac_idx = this->Malloc();

    if (mac_idx != 0) {
        SLinkList[mac_idx].data = e;

        //寻找第pos个元素
        for (int i = 1; i <= pos - 1; i++)
            cur_idx = SLinkList[cur_idx].cur;

        SLinkList[mac_idx].cur = SLinkList[cur_idx].cur; //第pos个元素的cur指向 cur_idx之后的元素
        SLinkList[cur_idx].cur = mac_idx; //cur_idx指向当前插入对象
        this->len++;
        return true;
    } else return false;
}
//4.2 插入元素到最后
/*在链表的末尾插入元素*/
template<class ElemType>
bool StaticLinkList<ElemType>::Insert(ElemType e) {
    cout << "----Insert Element in back---- -> " << e << endl;

    int cur_idx = maxn - 1;
    int mac_idx = this->Malloc();

    if (mac_idx != 0) {
        SLinkList[mac_idx].data = e;

        //寻找第pos个元素
        for (int i = 1; i <= this->Length(); i++)
            cur_idx = SLinkList[cur_idx].cur;

        SLinkList[mac_idx].cur = SLinkList[cur_idx].cur; //第pos个元素的cur指向 cur_idx之后的元素
        SLinkList[cur_idx].cur = mac_idx; //cur_idx指向当前插入对象
        this->len++;
        return true;
    } else return false;
}

//5删除pos位置的元素
/*删除第pos个位置的元素*/
template<class ElemType>
bool StaticLinkList<ElemType>::Delete(int pos) {
    cout << "----Delete List from pos---- -> " << pos << endl;

    if (pos < 1 || pos > this->Length()) {
        cout << "----Failed : Input Pos Error----" << endl;
        return false;
    }

    int cur_idx = maxn - 1;

    for (int i = 1; i <= pos - 1; i++)
        cur_idx = SLinkList[cur_idx].cur;

    int aim_idx = SLinkList[cur_idx].cur;
    SLinkList[cur_idx].cur = SLinkList[pos].cur;
    this->len--;
    Free(aim_idx);
    return true;
}
//6.获取链表的长度
/*获取静态链表的长度*/
template<class ElemType>
int StaticLinkList<ElemType>::Length() {
    //cout << "----Get Link List Length----" << endl;
    return len;
    /*
    int cur_idx = SLinkList[maxn - 1].cur;
    int cnt = 0;
    //统计所有元素，直到cur为0
    while (cur_idx != 0) {
    cur_idx = SLinkList[cur_idx].cur;
    cnt++;
    }
    return cnt;
    */
}

//7.判断链表是否为空
/*判断链表是否为空*/
template<class ElemType>
bool StaticLinkList<ElemType>::Empty() {
    return SLinkList[maxn - 1].cur == 0;
}
//8.遍历链表
/*遍历静态链表*/
template<class ElemType>
void StaticLinkList<ElemType>::Traverse() {
    cout << "----Traverse Link List----" << endl;
    int cur_idx = SLinkList[maxn - 1].cur;
    int idx = 1;

    //输出Node的数据
    while (cur_idx != 0) {
        cout << "Node " << (idx++) << " : " << SLinkList[cur_idx].data << endl;
        cur_idx = SLinkList[cur_idx].cur;
    }
}
//9.获取第pos位置的元素
/*获取第pos位置的元素*/
template<class ElemType>
bool StaticLinkList<ElemType>::GetElement(int pos, ElemType & e) {
    if (pos < 1 || pos > this->Length() + 1) {
        cout << "----Failed : Input Pos Error----" << endl;
        return false;
    }

    int cur_idx = maxn - 1;

    for (int i = 1; i <= pos; i++)
        cur_idx = SLinkList[cur_idx].cur;

    e = SLinkList[cur_idx].data;
    return true;
}

//10.分配备用链表中的一个位置用于插入元素
/*分配备用链表的一个节点*/
template<class ElemType>
int StaticLinkList<ElemType>::Malloc() {
    int cur_idx = SLinkList[0].cur;
    if (cur_idx != 0) {
        SLinkList[0].cur = SLinkList[cur_idx].cur;
        return cur_idx;
    } else {
        cout << "----Failed : Spare Link List is Empty----" << endl;
        exit(0);
    }

}
//11.释放链表中的pos位置，并插入到备用链表中
/*释放pos位置空闲节点*/
template<class ElemType>
void StaticLinkList<ElemType>::Free(int pos) {
    SLinkList[pos].cur = SLinkList[0].cur; /*把第一个元素的cur值赋给要删除的分量cur */
    SLinkList[0].cur = pos; /* 把要删除的分量下标赋值给第一个元素的cur */
}
