// 版本1： 一般并查集
const int maxn = 100000;
int fa[maxn], rank[maxn], component;//记录祖先、秩、集合个数

// 初始化
void init(int n){ 
	component = n; 
	for (int i = 0; i <= n; i++) { 
		fa[i] = i; 
		rank[i] = 0; 
	} 
}

// 查找最上面父亲节点，并进行路径压缩
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

bool connected(int p, int q) { return find(p) == find(q); }

//按秩合并
<<<<<<< HEAD
inline void union_set(int p, int q) {
	int fp = find(p);
	int fq = find(q);
	if (fp == fq) return;
	if (rank[fp] > rank[fq]) fa[fq] = fp;
	else {
		fa[fp] = fq;
		if (rank[fp] == rank[fq]) rank[fq]++;
	}
	component--;
}


// 版本2： 记录点到根距离
const int maxn = 30005;
int fa[maxn], sz[maxn], up[maxn], component;
void init(int n) {
	component = n;
	for (int i = 0; i <= n; i++) {
		fa[i] = i;
		sz[i] = 1;
		up[i] = 0;//up记录当前点到root点的距离，自身为root的话距离为0， 关键就在于up的维护。  当前点到root的距离是一个相对值。
	}
}

bool connected(int p, int q) { return find(p) == find(q); }

int find(int x) {
	int tmp = fa[x];
	if (x == fa[x])	return x;
	fa[x] = find(fa[x]);
	up[x] += up[tmp];//求解当前点到root的距离
	return fa[x];
}

void union_set(int p, int q) {
	//把p所在的栈放在q所在栈上面
	int fp = find(p);
	int fq = find(q);
	if (fp == fq) return;
	fa[fq] = fp;//fq指向fp
	up[fq] += sz[fp];//更新q的root节点到新的p的根节点的距离
	sz[fp] += sz[fq];//更新p的root的节点个数
	component--;
}

// 使用的时候注意，在用up[]时候，调用一下find()操作，把相对的距离更新一遍
=======
inline void unionSet(int x, int y) {
	int fx = find(x);
	int fy = find(y);
	if (fx != fy) {
		if (rank[fx] > rank[fy]) {
			fa[fy] = fx;
		} else {
	       		fa[fx] = fy;
	       		if (rank[fx] == rank[fy]) rank[fy]++;
    		}
	}
}
>>>>>>> origin/HEAD
