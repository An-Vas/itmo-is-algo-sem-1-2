#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

struct Node {
  long long key;
  Node* left;
  Node* right;
  Node* parent;
  int height;
};
int getHeight (Node* node){
    if (node == NULL) return 0;
    else return node->height;
}

int getBalance (Node* node){
    if (node == NULL) return 0;
    return getHeight(node->right) - getHeight(node->left);
}

int fixOneHeight (Node* root){
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    if (leftHeight > rightHeight) {
        root->height = 1+leftHeight;
        return 1+leftHeight;
    } else {
        root->height = 1+rightHeight;
        return 1+rightHeight;
    }
}

Node* rotateLeft (Node* node){
    Node* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    fixOneHeight(node);
    fixOneHeight(rightChild);
    return rightChild;
}

Node* rotateRight (Node* node){
    Node* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    fixOneHeight(node);
    fixOneHeight(leftChild);
    return leftChild;
}

Node* balanceNode(Node* node){
    fixOneHeight(node);
    int curBalance = getBalance(node);
    Node* rChild = node->right;
    Node* lChild = node->left;


    if (curBalance > 1) {
        int rightChildBalance = getBalance(rChild);


        if (rightChildBalance < 0){
            node->right = rotateRight(rChild);
        }
        return rotateLeft(node);

    } else if (curBalance < -1){
        int leftChildBalance = getBalance(lChild);

        if (leftChildBalance > 0){
            node->left = rotateLeft(lChild);
        }
        return rotateRight(node);

    } else

    return node;

}



Node* treeMin (Node* rootPointer);
void InorderTreeWalk(Node* rootPointer);
Node* treeFindNext (Node* curNodePointer);
Node* insertX(Node* rootPointer, Node* newNode);

Node* addNewNode(long long key, Node* &rootPointer){

    Node* newNode = new Node;
    newNode->key = key;
    newNode->parent = 0;
    newNode->left = 0;
    newNode->right = 0;
    newNode->height = 1;

    if (rootPointer == 0){
        rootPointer = newNode;
        return rootPointer;
        }
    else {
        return insertX (rootPointer, newNode);
    }

}

Node* insertX(Node* rootPointer, Node* newNode){
     //printf("insertNode, root = %d, numOfNew = %d\n", root, numOfNew);
    if (rootPointer == 0) { /*fixOneHeight(arr, root);*/ return newNode;}
    if (rootPointer->key ==  newNode->key) return rootPointer;
    if (rootPointer->key > newNode->key){
        //printf("LeftCh = %d\n",arr[root].left);
        rootPointer->left = insertX (rootPointer->left, newNode);
    } else {
        //printf("rightCh = %d\n",arr[root].right);
        rootPointer->right = insertX (rootPointer->right, newNode);
    }
    //printf("Inserted root = %d\n", root);

    return balanceNode(rootPointer);
}


Node* findRightestNode (Node* root){
    if (root->right!=0){
        return findRightestNode(root->right);
    } else {
        return root;
    }
}

Node* deleteX(Node* &rootPointer, int keyToDel){
    //printf("Start deleting; rootPointer = %d, nodeTodel = %d\n", rootPointer->key, keyToDel);
    if (rootPointer == 0){
        return 0;
    } else if (keyToDel < rootPointer->key) {
        rootPointer->left = deleteX(rootPointer->left, keyToDel);
    } else if (keyToDel > rootPointer->key) {
        rootPointer->right = deleteX(rootPointer->right, keyToDel);
    } else if ( rootPointer->left==0) {
        return rootPointer->right;
    } else {
        Node* prevNode = findRightestNode(rootPointer->left);
        rootPointer->key = prevNode->key;
        rootPointer->left = deleteX (rootPointer->left, prevNode->key);
    }
    fixOneHeight(rootPointer);
    return balanceNode(rootPointer);

}

Node* treeMin (Node* rootPointer){
    if (rootPointer == 0) {return 0;}
    while (rootPointer->left != 0) {
        rootPointer = rootPointer->left;
    }
    return rootPointer;
}

Node* treeMax (Node* rootPointer){
    if (rootPointer == 0) {return 0;}
    while (rootPointer->right != 0) {
        rootPointer = rootPointer->right;
    }
    return rootPointer;
}


Node* treeFindNext (Node* curNodePointer){
    if (curNodePointer == 0){return 0;}
    if (curNodePointer->right != 0){return treeMin(curNodePointer->right);}

    Node* resultPointer = curNodePointer->parent;
    while ((resultPointer != 0)&&(curNodePointer == resultPointer->right)){
        curNodePointer = resultPointer;
        resultPointer = resultPointer->parent;
    }
    return resultPointer;
}

 Node* treeFindPrev (Node* curNodePointer){
    if (curNodePointer == 0){return 0;}
    if (curNodePointer->left != 0){return treeMax(curNodePointer->left);}

    Node* resultPointer = curNodePointer->parent;
    while ((resultPointer != 0)&&(curNodePointer == resultPointer->left)){
        curNodePointer = resultPointer;
        resultPointer = resultPointer->parent;
    }
    return resultPointer;
}

Node* treeFindElement (Node* rootPointer, long long searchKey) {
    if ((rootPointer == 0)||(rootPointer->key == searchKey)){return rootPointer; }
    if ((rootPointer->key > searchKey) && (rootPointer->left != 0)) {
        return treeFindElement(rootPointer->left, searchKey);
    }
    if ((rootPointer->key < searchKey) && (rootPointer->right != 0)) {
        return treeFindElement(rootPointer->right, searchKey);
    }
    return 0;
}


void InorderTreeWalk(Node* rootPointer){
    if (rootPointer != 0){
        InorderTreeWalk(rootPointer->left);
        cout<< rootPointer->key <<" ";
        InorderTreeWalk(rootPointer->right);
    }
}

void StrightOrderTreeWalk(Node* rootPointer){
    if (rootPointer != 0){
        cout<< rootPointer->key <<" ";
        StrightOrderTreeWalk(rootPointer->left);
        StrightOrderTreeWalk(rootPointer->right);
    }
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("avlset.in", "r", stdin);
    freopen("avlset.out", "w", stdout);


    string curCommand;
    Node* rootPointer = 0;

    while (cin >> curCommand){

       /* cout<<"Before"<<endl;
        cout<<"Array in Order: "; InorderTreeWalk(rootPointer); cout<<endl;
        cout<<"Array as tree: "; StrightOrderTreeWalk(rootPointer); cout<<endl;
        if (rootPointer != 0)
        cout<<"RootPointerKey "<<rootPointer->key<<" RootPointer "<<rootPointer<<endl;
        else cout<<"RootPointer "<<rootPointer<<endl; */



        if (curCommand[0] == 'f') {
            break;
        }
        if (curCommand[0] == 'A') {
            long long key;
            cin>>key;
            rootPointer = addNewNode(key, rootPointer);
            cout<<getBalance(rootPointer)<<endl;
        }
        if (curCommand[0] == 'D') {
            long long searchKey;
            cin>>searchKey;
            Node* curNode = treeFindElement(rootPointer, searchKey);

            if (curNode != 0 && !(rootPointer == curNode && curNode->left == NULL &&curNode->right == NULL)) {
              rootPointer = deleteX(rootPointer, searchKey);
            } else if (curNode != 0 && (rootPointer == curNode && curNode->left == NULL &&curNode->right == NULL)){
                rootPointer = NULL;
            }


            cout<<getBalance(rootPointer)<<endl;
        }

        if (curCommand[0] == 'C') {
            long long searchKey;
            cin>>searchKey;
            Node* curNodePointer = treeFindElement(rootPointer, searchKey);
            if (curNodePointer != 0) cout<<"Y"<<endl;
            if (curNodePointer == 0) cout<<"N"<<endl;

        }




        /*cout<<"After"<<endl;
        cout<<"Array in Order: "; InorderTreeWalk(rootPointer); cout<<endl;
        cout<<"Array as tree: "; StrightOrderTreeWalk(rootPointer); cout<<endl;
        if (rootPointer != 0)
        cout<<"RootPointerKey "<<rootPointer->key<<" RootPointer "<<rootPointer<<endl;
        else cout<<"RootPointer "<<rootPointer<<endl;*/


    }

    return 0;

}
