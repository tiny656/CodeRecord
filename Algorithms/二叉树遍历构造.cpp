#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//分别记录前序 中序 后序
string strPreOrd, strInOrd, strPostOrd;

//通过前序Pre和中序In构造后序Post输出
void RecoverFromPreInord(int preLeft, int preRight, int inLeft, int inRight) {
	assert(preLeft <= preRight && inLeft <= inRight);
	//调用默认遍历序列是合法的
	int root;	//记录当前根的位置
	//在中序遍历中寻找根的位置
	for (root = inLeft; root <= inRight; ++root) {
		if (strInOrd[root] == strPreOrd[preLeft]) {
			break;
		}
	}
	int leftSize = root - inLeft;
	int rightSize = inRight - root;
	//后序遍历 - 左右根
	if (leftSize > 0) RecoverFromPreInord(preLeft + 1, preLeft + leftSize, inLeft, root - 1);//递归构造左子树
	if (rightSize > 0) RecoverFromPreInord(preLeft + leftSize + 1, preRight, root+1, inRight);//递归构造右子树
	printf("%c", strInOrd[root]);//输出根
}


//通过后序Post和中序In构造前序Pre输出
void RecoverFromPostInord(int postLeft, int postRight, int inLeft, int inRight) {
	//调用默认遍历序列是合法的
	assert(postLeft <= postRight && inLeft <= inRight);
	int root;//记录当前根的位置
	//在中序遍历中寻找根的位置
	for (root = inLeft; root <= inRight; ++root) {
		if (strInOrd[root] == strPostOrd[postRight]) {
			break;
		}
	}
	int leftSize = root - inLeft;
	int rightSize = inRight - root;
	//前序遍历 - 根左右
	printf("%c", strPostOrd[postRight]);//输出根
	if (leftSize > 0) RecoverFromPostInord(postLeft, postLeft + leftSize - 1, inLeft, root - 1);//递归构造左子树
	if (rightSize > 0) RecoverFromPostInord(postLeft + leftSize, postRight - 1, root + 1, inRight);//递归构造右子树
	
}
int main() {
	
	//Pre In -> Post
	cin >> strPreOrd >> strInOrd;
	RecoverFromPreInord(0, strPreOrd.size()-1, 0, strInOrd.size()-1);
	cout << endl;
	//Post In -> Pre
	cin >> strPostOrd >> strInOrd;
	RecoverFromPostInord(0, strPostOrd.size() - 1, 0, strInOrd.size() - 1);
	cout << endl;

	return 0;
}