#include <bits/stdc++.h>
using namespace std;
#define ERROR -1

// XorNode Class
template<typename ElemType>
class XorNode {
public:
	ElemType data;
	XorNode<ElemType> *xorPtr;
	XorNode(ElemType data):data(data) { }
};

// XorLinkedList Class
template<typename ElemType>
class XorLinkedList {
public:
	XorNode<ElemType> *head;
	XorNode<ElemType> *tail;
	int size;

	// constructor function
	XorLinkedList() {
		head = NULL;
		tail = NULL;
		size = 0;
	}

	// is xorlinkedlist empty
	bool isEmpty() {
		return head == NULL && tail == NULL;
	}

	// xorlinkedlist length
	int length() {
		return size;
	}

	// add element into back
	void addBack(ElemType e) {
		XorNode<ElemType> *newNode = new XorNode<ElemType>(e);
		if (isEmpty()) {
			newNode->xorPtr = xor_func(NULL, NULL);
			head = newNode;
			tail = newNode;
		} else {
			newNode->xorPtr = xor_func(tail, NULL);
			tail->xorPtr = xor_func(xor_func(tail->xorPtr, NULL), newNode);
			tail = newNode;
		}
		size++;
	}
	
	//add element into front
	void addFront(ElemType e) {
		XorNode<ElemType> *newNode = new XorNode<ElemType>(e);
		if (isEmpty()) {
			newNode->xorPtr = xor_func(NULL, NULL);
			head = newNode;
			tail = newNode;
		} else {
			newNode->xorPtr = xor_func(NULL, head);
			head->xorPtr = xor_func(newNode, xor_func(head->xorPtr, NULL));
			head = newNode;
		}
		size++;
	}

	// pop element from back
	ElemType popBack() {
		if (isEmpty()) {
			cout << "XorLinkedList is empty." << endl;
			return ERROR;
		}
		XorNode<ElemType> *tmpNode = tail;
		ElemType ret = tail->data;

		tail = xor_func(tail->xorPtr, NULL);
		if (tail) tail->xorPtr = xor_func(xor_func(tail->xorPtr, tmpNode), NULL);
		else head = NULL;
		delete[] tmpNode;
		size--;
		return ret;
	}

	// pop element from front
	ElemType popFront() {
		if (isEmpty()) {
			cout << "XorLinkedList is empty." << endl;
			return ERROR;
		}
		XorNode<ElemType> *tmpNode = head;
		ElemType ret = head->data;
		head = xor_func(NULL, head->xorPtr);
		// if not pop last node, set the xorPtr
		if (head)  head->xorPtr = xor_func(NULL, xor_func(head->xorPtr, tmpNode));
		else tail = NULL;
		delete[] tmpNode;
		size--;
		return ret;
	}

	// return the value of pos
	ElemType getValue(int pos) {
		if (pos < 0 || pos >= length()) {
			cout << "pos ranges from " << 0 << " to " << length() - 1 << endl;
			return ERROR;
		}
		int step = 0;
		XorNode<ElemType> *curNode = NULL;
		if (pos <= length()/2) {
			curNode = head;
			step = pos;
		} else {
			curNode = tail;
			step = length() - pos - 1;
		}
		int i = 0;
		XorNode<ElemType> *otherNode = NULL, *tmpNode = NULL;
		while (i < step && curNode != NULL) {
			tmpNode = curNode;
			curNode = xor_func(curNode->xorPtr, otherNode);
			otherNode = tmpNode;
			i++;
		}
		return curNode->data;
	}

	// insert a node before pos
	void insert(ElemType e, int pos) {
		if (pos < 0 || pos > length()) {
			cout << "pos ranges from " << 0 << " to " << length() << endl;
			cout << "0: add element in front, " << length() << ": add element in back." << endl;
			return;
		}
		// deal with front and back
		if (pos == 0) addFront(e);
		else if(pos == length()) addBack(e);
		else {
			XorNode<ElemType> *curNode = NULL, *tmpNode = NULL, *otherNode = NULL;
			int i = 0;
			curNode = head;
			// find the pos
			while (i < pos && curNode != NULL) {
				tmpNode = curNode;
				curNode = xor_func(curNode->xorPtr, otherNode);
				otherNode = tmpNode;
				i++;
			}
			// insert the newNode before pos
			XorNode<ElemType> *newNode = new XorNode<ElemType>(e);
			newNode->xorPtr = xor_func(curNode, otherNode);
			otherNode->xorPtr = xor_func(xor_func(otherNode->xorPtr, curNode), newNode);
			curNode->xorPtr = xor_func(newNode, xor_func(otherNode, curNode->xorPtr));
			size++;
		}
	}

	// delete the element at pos
	void remove(int pos) {
		if (isEmpty()) {
			cout << "XorLinkedList is empty" << endl;
			return;
		}
		if (pos < 0 || pos >= length()) {
			cout << "pos ranges from " << 0 << " to " << length()-1 << endl;
			return;
		}
		if (pos == 0) popFront();
		else if (pos == length()) popBack();
		else {
			int step = 0;
			XorNode<ElemType> *curNode = NULL;
			if (pos <= length()/2) {
				curNode = head;
				step = pos;
			} else {
				curNode = tail;
				step = length() - pos - 1;
			}
			int i = 0;
			XorNode<ElemType> *otherNode = NULL, *tmpNode = NULL, *nextNode = NULL;
			while (i < step && curNode != NULL) {
				tmpNode = curNode;
				curNode = xor_func(curNode->xorPtr, otherNode);
				otherNode = tmpNode;
				i++;
			}
			nextNode = xor_func(curNode->xorPtr, otherNode);
			if (otherNode) otherNode->xorPtr = xor_func(xor_func(otherNode->xorPtr, curNode), nextNode);
			if (nextNode)  nextNode->xorPtr = xor_func(otherNode, xor_func(nextNode->xorPtr, curNode));
			delete[] curNode;
			size--;
		}

	}

	// traverse the xorlinkedlist.
	// f: head -> tail
	// r: tail -> head
	void traverse(char direction = 'f') {
		if (isEmpty()) {
			cout << "XorLinkedList is empty" << endl;
			return;
		}

		if (direction != 'f' && direction != 'r')  {
			cout << "direction error, 'f' or 'r'." << endl;
			return;
		}

		XorNode<ElemType> *curNode = NULL, *otherNode = NULL, *tmpNode = NULL;
		if (direction == 'f') curNode = head; // head -> tail
		else if (direction == 'r') curNode = tail;	// tail -> head
		do {
			cout << curNode->data << " ";
			tmpNode = curNode;
			curNode = xor_func(curNode->xorPtr, otherNode);
			otherNode = tmpNode;
		} while (curNode != NULL);
		cout << endl;
	}


private:
	XorNode<ElemType>* xor_func(XorNode<ElemType> *a, XorNode<ElemType> *b) {
		return (XorNode<ElemType>*)((unsigned long)(a) ^ (unsigned long)(b));	
	}
};


int main() {
	XorLinkedList<int> xll;
	xll.insert(1,0);
	xll.insert(2,1);
	xll.insert(3,1);
	xll.traverse('f');
	// for (int i = 0; i < 3; i++)
	// 	cout << xll.popBack() << endl; 
	xll.remove(1);
	xll.traverse('f');
	cout << endl;
	return 0;
}