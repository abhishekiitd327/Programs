#include <iostream>
using namespace std;

struct Node{
	Node* left;
	Node* right;
	int data;
	Node(int val):data(val), left(NULL), right(NULL){}
};
void MorrisInorder(Node* root){
	if(root == NULL)
		return;
	if(root->left == NULL && root->right == NULL){
		cout << root->data;
		return;
	}
	Node* curr = root;
	while(curr != NULL){
		if(curr->left == NULL){
			cout << curr->data << "  ";
			curr = curr->right;
		}
		else{ // make inorder predecessor of curr point to curr
			Node* iop = curr->left;
			while(iop->right && iop->right != curr)
				iop = iop->right;
			if(iop->right){
			    iop->right = NULL;
			    cout << curr->data << "  ";
			    curr = curr->right;
			}
			else {
				iop->right = curr;
				curr = curr->left;
			}
		}
	}
}

int main() {
	Node n1(1), n3(3), n4(4), n5(5), n6(6), n7(7), n8(8), n9(9), n11(11), n13(13);
	n6.left = &n3;		n6.right = &n8;
	n3.left = &n1;		n3.right = &n4;
	n4.right = &n5;
	n8.left = &n7;		n8.right = &n11;
	n11.left = &n9;		n11.right = &n13;
	MorrisInorder(&n6);
	
	return 0;
}