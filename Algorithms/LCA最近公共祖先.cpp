1.朴素写法，双亲法进行树存储，DFS进行节点层次记录，然后根据层次关系向父亲节点移动，直到根节点，在这条路径上就能找到公共祖先。

int level[905];//记录节点层次
/*双亲法存储树结构*/
int fa[905];//记录节点的父节点
vector<int> tree[905];//记录儿子节点

//dfs进行节点的层次标记
inline void dfs(int root, int lv) {
    int i;
    level[root] = lv;
    for(i = 0; i < tree[root].size(); i++) {
        dfs(tree[root][i], lv+1);
    }
}

/*---- 算法开始 ----*/
for(i = 1; i <= n; i++) {
	//没有父亲的节点，也就是入度为0的点就是根
    if(!fa[i]) {
        root = i;
        break;
    }
}

dfs(root, 1);//进行层次标记

scanf("%d", &search);//读入查询次数
while(search--) {
    read(a),read(b);
    while(a != b) {
        if(level[a] < level[b])			b = fa[b];
        else if(level[a] > level[b])	a = fa[a];
        else {
            a = fa[a];
            b = fa[b];
        }
    }
    //ancestor(a, b) 就是 a 或 b 
}
/*---- 算法结束 ----*/


2. LCA Tarjan离线算法
O(n+|q|)，O(n)为dfs复杂度，q为查询复杂度。从根节点调用一次
当进行后序遍历的时候，必然先访问完x的所有子树，然后才会返回到x所在的节点。这个性质就是我们使用Tarjan算法解决最近公共祖先问题的核心思想。

/*双亲表示法*/
int p[maxn];//记录父亲节点
vector<int> tree[MAXN];//存储儿子节点
vector<int> question[MAXN];//存储查询

int fa[MAXN],fs[MAXN];//用于并查集父节点， 父节点个数
int color[MAXN];//是否被访问
int ancestor[MAXN];//祖先

inline int Find(int x){return (x==fa[x])?x:(fa[x]=Find(fa[x]));}
inline void Union(int x,int y) {
    x=Find(x);y=Find(y);
    if(x==y) return;
    if(fs[x]<=fs[y]) fa[x]=y,fs[y]+=fs[x];
    else fa[y]=x,fs[x]+=fs[y];
}
inline void LCA_Tarjan(int u) {
	fa[u] = u;
	ancestor[u] = u;
	for (int i = 0; i < tree[u].size(); ++i) {
		int v = tree[u][i];
		LCA_Tarjan(v);
		Union(u, v);
		ancestor[Find(u)] = u;
	}
	color[u] = 1;
	for (int i = 0; i < question[u].size(); ++i) {
		int v = question[u][i];
		if (color[v]) {
			//Ancestor(u , v) = ancestor[Find(v)];
			printf("LCA(%d,%d):%d\n",u,v, ancestor[Find(v)]);
		}
	}
}
/*---- Main ----*/
init();//初始化数组
readData();//读入数据

/*寻找根节点*/
for(int i = 0; i < n; ++i) {
    if( p[i] == 0 ) {
        root = i;
        break;
    }
}

//存储查询
for(int i = 1; i <= m; i++) {
	a = get();
	b = get();
	question[a].push_back(b);
}
Tarjan(root);
/*---- End Main ----*/
