#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define N 4

struct PQNode {
    int val;
    int arrId;
    int arrPos;
    PQNode(int val, int id, int pos) {
        this->val = val;
        this->arrId = id;
        this->arrPos = pos;
    }
};

struct NodeCmp {
    bool operator()(const PQNode* a, const PQNode* b) const{
        return (a->val > b->val);
    }
};

int* mergeKArrays(int arr[][N], int k){
    priority_queue<PQNode*, vector<PQNode*>, NodeCmp> PQ;
    for(int i = 0; i < k; ++i) {
        PQNode* pq = new PQNode(arr[i][0], i, 0);
        PQ.push(pq);
    }
    int* mergedArr = new int[N*k];
    int count = 0;
    while(!PQ.empty()) {
        PQNode* el = PQ.top();
        PQ.pop();
        if(el->arrPos < N-1) {
            PQNode* pqnode = new PQNode(arr[el->arrId][el->arrPos + 1], el->arrId, el->arrPos + 1);
            PQ.push(pqnode);
        }
        mergedArr[count++] = el->val;
        delete el;
    }
    return mergedArr;
}

void printArr(int arr[], int n){
    for(int i = 0; i < n; ++i){
        cout << arr[i] << " ";//<< endl;
    }
    cout << endl;
}

int main() {
    int k = 3;
    int arr[3][N] = {{2, 6, 12, 34},
	            {1, 9, 20, 1000},
	            {23, 34, 90, 2000}
	           };
    int *mergedArr = mergeKArrays(arr, k);
    printArr(mergedArr, N*k);
    return 0;
}
