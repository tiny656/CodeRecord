const int maxn = 100000;
int fa[maxn],rank[maxn];

//初始化自身为一个集合
inline void MakeSet(int x){ fa[x] = x; rank[x] = 0;}
//查找最上面父亲节点，并进行路径压缩
inline int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
//按秩合并
inline void unionSet(int x, int y) {
	int fx = find(x);
	int fy = find(y);
	if (fx != fy) {
		if (rank[fx] > rank[fy]) fa[fy] = fx;
    	else {
	       	fa[fx] = fy;
	       	if (rank[fx] == rank[fy]) rank[fy]++;
    	}
	}
}
