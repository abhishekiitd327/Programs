#include <iostream>
#include <queue>
using namespace std;

struct Node{
	Node* left;
	Node* right;
	char data;
	Node* nextRight;
	Node(char c):data(c), left(NULL), right(NULL), nextRight(NULL){}
};

void createNextRight(Node* root){
	if(root == NULL)
		return;
	queue<Node*> Q;
	Q.push(root);
	Node* front = root;
	int remaining = 1;
	while(!Q.empty()){
		Q.pop();
		if(front->left)
		    Q.push(front->left);
		if(front->right)
		    Q.push(front->right);
		remaining--;
		if(remaining == 0){
		    front->nextRight = NULL;
		    remaining = Q.size();
		}
		else
			front->nextRight = Q.front();
		front = Q.front();
	}
}

void printNextRight(Node* root){
	if(root == NULL)
	    return;
	cout << root->data << " --> " ;
	if(root->nextRight)
	    cout << root->nextRight->data << endl;
	else
	    cout << "NULL" << endl;
	printNextRight(root->left);
	printNextRight(root->right);
}

int main() {
	Node a('A'), b('B'), c('C'), d('D'), e('E'), f('F');
	a.left = &b;	a.right = &c;
	b.left = &d;	b.right = &e;
	c.right = &f;
	createNextRight(&a);
	printNextRight(&a);
	
	return 0;
}