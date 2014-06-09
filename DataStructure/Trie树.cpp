Trie树的基本性质，利用公共前缀来减少存储空间，但是内存消耗也是很大的。
1. 根节点不包含字符，除根节点外每一个节点都只包含一个字符。
2. 从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串。
3. 每个节点的所有子节点包含的字符都不相同。

1. 静态Trie树
注意修改这里的定义
----------------------------------------------
const int trieNodeNum = 100000;//静态空间节点个数  节点个数为字符串长度Lx字符串个数n （nL）
const int branchNum = 10;//trie分叉个数
const char startChar = '0';//分叉起始字符
----------------------------------------------
//TrieNode节点
class TrieNode {
public:
    int num; //记录到达这个点的串
    bool isStr; //判断是否可以构成一个串
    TrieNode * next[branchNum]; //指向后面的branch

    TrieNode(); //构造一个新节点
};

TrieNode::TrieNode() {
    memset(next, NULL, sizeof(next));
    isStr = false;
    num = 1;
}

//静态空间
int allocateNum;//已分配出去的节点数
TrieNode NodeList[trieNodeNum];//静态分配空间

//Trie树定义
class Trie {
    public:
    Trie(); //构造Trie树
    void Insert(string str); //插入
    bool Find(string str); //查找
    TrieNode * Root; //Trie的根
};

Trie::Trie() {
    allocateNum = 0;
    Root = &NodeList[allocateNum++];
    Root->num = 0;
}

void Trie::Insert(string str) {
    int i, idx;
    TrieNode * location = Root;
    for (i = 0; i < str.size(); i++) {
        idx = str[i] - startChar;
        if (location->next[idx] == NULL) { //不存在就建立节点
            TrieNode * tmp = &NodeList[allocateNum++];
            location->next[idx] = tmp;
        }
        else {
            location->next[idx]->num += 1;
        }
        location = location->next[idx];
    }
    location->isStr = true; //到达了字符串的尾部，标记
}

bool Trie::Find(string str) {
    int i, idx;
    TrieNode * location = Root;
    for (i = 0; i < str.size() && location != NULL; i++) {
        idx = str[i] - startChar;
        location = location->next[idx];
    }
    return (location != NULL && location->isStr);
}

Usage:
Trie t;
修改上面const变量定义



2.动态Trie树
const int branchNum = 26;//字数的个数
const char startChar = 'a';//起始的字母
class TrieNode {
public:
    int num;//记录有多少个串可以到达这个结点
    bool isStr;//记录Trie树在此是否能构成一个串
    TrieNode *next[branchNum];//指向各个字数的指针，0-25代表26个字符
    TrieNode() :isStr(false),num(1) {
        memset(next, NULL, sizeof(next));
    }
};
class Trie {
public:
    Trie();
    void Insert(string str);
    bool Find(string str);
    void DeleteTrie(TrieNode *root);
    TrieNode *Root;
};

Trie::Trie() {
    Root = new TrieNode();
    Root->num = 0;
}

void Trie::Insert(string str) {
    TrieNode *location = Root;
    int i, idx;
    for (i = 0; i < str.size(); i++) {
        idx = str[i] - startChar;
        if (location->next[idx] == NULL) {//不存在就建立节点
            TrieNode *tmp = new TrieNode();
            location->next[idx] = tmp;
        } else {
            location->next[idx]->num += 1;
        }
        location = location->next[idx];
    }
    location->isStr = true;//到达了字符串的尾部，标记
}

bool Trie::Find(string str) {
    TrieNode *location = Root;
    int i, idx;
    for (int i = 0; i < str.size() && location != NULL; i++) {
        idx = str[i] - startChar;
        location = location->next[idx];
    }
    return (location != NULL && location ->isStr);
}

void Trie::DeleteTrie(TrieNode *root) {
    int i;
    for (i = 0; i < branchNum; ++i) {
        if (root->next[i] != NULL) {
            DeleteTrie(root->next[i]);
        }
    }
    delete root;
}

使用方法
int main() {
    Trie tt;
    tt.Insert("abcdefg");
    tt.Insert("abcdefg");
    if (tt.Find("abcdefg")) {
        cout << "Bingo" << endl;
    } else {
        cout << "ooops" << endl;
    }
    tt.DeleteTrie(tt.Root);
    return 0;
}
