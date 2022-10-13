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
};

void InorderTreeWalk(Node* rootPointer);
Node* treeFindNext (Node* curNodePointer);

void insertX(Node* rootPointer, Node* newNode){
    while (rootPointer != 0){
        if (newNode-> key >= rootPointer-> key){
            if (rootPointer->right != 0){
                rootPointer = rootPointer->right;
            } else {
                newNode->parent = rootPointer;
                rootPointer->right = newNode;
                break;
            }
        } else if (newNode-> key < rootPointer-> key){
            if (rootPointer->left != 0){
                rootPointer = rootPointer->left;
            } else {
                newNode->parent = rootPointer;
                rootPointer->left = newNode;
                break;
            }
        }
    }
}

void deleteX(Node* &rootPointer, Node* nodeToDelete, int &firstNode){
    if ((rootPointer == 0)||(nodeToDelete==0)) return;

    if ((nodeToDelete->parent == 0)&&(nodeToDelete->left == 0)&&(nodeToDelete->right == 0)) {
        firstNode = 1;
        rootPointer = 0;

    } else if ((nodeToDelete->parent == 0)&&(nodeToDelete->left != 0)&&(nodeToDelete->right == 0)) {
        Node* newRoot = nodeToDelete->left;
        nodeToDelete->key = newRoot->key;
        nodeToDelete->left = newRoot->left;
        nodeToDelete->right = newRoot->right;
    }

    else if ((nodeToDelete->parent == 0)&&(nodeToDelete->left == 0)&&(nodeToDelete->right != 0)) {
        Node* newRoot = nodeToDelete->right;
        nodeToDelete->key = newRoot->key;
        nodeToDelete->left = newRoot->left;
        nodeToDelete->right = newRoot->right;
    }

    else if ((nodeToDelete->parent != 0)&&(nodeToDelete->left == 0)&&(nodeToDelete->right == 0)){
        Node* parentPointer = nodeToDelete->parent;
        if ((parentPointer-> left) == nodeToDelete){ parentPointer-> left = 0;}
        if ((parentPointer-> right) == nodeToDelete){ parentPointer-> right = 0;}

    } else if ((nodeToDelete->parent != 0)&&(nodeToDelete->left != 0)&&(nodeToDelete->right == 0)) {
        Node* leftChildPointer = nodeToDelete->left;
        Node* parentPointer = nodeToDelete->parent;
        if ((parentPointer-> left) == nodeToDelete){ parentPointer-> left = leftChildPointer;}
        if ((parentPointer-> right) == nodeToDelete){ parentPointer-> right = leftChildPointer;}
        leftChildPointer->parent = parentPointer;

    } else if ((nodeToDelete->parent != 0)&&(nodeToDelete->left == 0)&&(nodeToDelete->right != 0)) {
        Node* rightChildPointer = nodeToDelete->right;
        Node* parentPointer = nodeToDelete->parent;
        if ((parentPointer-> left) == nodeToDelete){ parentPointer-> left = rightChildPointer;}
        if ((parentPointer-> right) == nodeToDelete){ parentPointer-> right = rightChildPointer;}
        rightChildPointer->parent = parentPointer;

    } else if ((nodeToDelete->left != 0)&&(nodeToDelete->right != 0)){
        Node* newNodeToDelete = treeFindNext(nodeToDelete);
        if (newNodeToDelete == 0){ cout<<"error"<<endl;}
        nodeToDelete->key = newNodeToDelete->key;
        deleteX(rootPointer, newNodeToDelete, firstNode);
    }

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
    if (curNodePointer == 0) {return 0; }
    if (curNodePointer->right != 0) {
        return treeMin(curNodePointer->right);
    }
    Node* tempNodePointer = curNodePointer->parent;
    while (tempNodePointer != 0 && curNodePointer == tempNodePointer->right){
        curNodePointer = tempNodePointer;
        tempNodePointer = tempNodePointer->parent;
    }
    return tempNodePointer;
}

Node* treeFindPrev (Node* curNodePointer){
    if (curNodePointer == 0) {return 0; }
    if (curNodePointer->left != 0) {
        return treeMax(curNodePointer->left);
    }
    Node* tempNodePointer = curNodePointer->parent;
    while (tempNodePointer != 0 && curNodePointer == tempNodePointer->left){
        curNodePointer = tempNodePointer;
        tempNodePointer = tempNodePointer->parent;
    }
    return tempNodePointer;
}

/*Node* treeFindElement (Node* rootPointer, long long searchKey) {
    if (rootPointer->key == searchKey){return rootPointer; }
    if ((rootPointer->key > searchKey) && (rootPointer->left != 0)) {
        return treeFindElement(rootPointer->left, searchKey);
    }
    if ((rootPointer->key < searchKey) && (rootPointer->right != 0)) {
        return treeFindElement(rootPointer->right, searchKey);
    }
    return 0;
}*/

Node* treeFindLastInRawElement (Node* rootPointer, long long searchKey) {
    if (rootPointer == 0) {return 0; }
    if ((rootPointer->key > searchKey) && (rootPointer->left != 0)) {
        return treeFindLastInRawElement(rootPointer->left, searchKey);
    }
    if ((rootPointer->key <= searchKey) && (rootPointer->right != 0)) {
        Node* tempPointer = treeFindLastInRawElement(rootPointer->right, searchKey);
        if (tempPointer != 0 ) return tempPointer;
        else if (rootPointer->key == searchKey) return rootPointer;
    }
    if (rootPointer->key == searchKey){return rootPointer;}
    return 0;
}

Node* treeFindFirstInRawElement (Node* rootPointer, long long searchKey) {
    if (rootPointer == 0) {return 0; }
    if ((rootPointer->key >= searchKey) && (rootPointer->left != 0)) {
        Node* tempPointer = treeFindFirstInRawElement(rootPointer->left, searchKey);
        if (tempPointer != 0) return tempPointer;
        else if (rootPointer->key == searchKey) return rootPointer;
    }
    if (rootPointer->key == searchKey){return rootPointer;}//in case rootPointer->left == 0
    if ((rootPointer->key < searchKey) && (rootPointer->right != 0)) {
        return treeFindFirstInRawElement(rootPointer->right, searchKey);
    }
    return 0;
}


void InorderTreeWalk(Node* rootPointer){
    if (rootPointer != 0){
        InorderTreeWalk(rootPointer->left);
        cout<< rootPointer->key<<" ";
        InorderTreeWalk(rootPointer->right);
    }
}

void StrightOrderTreeWalk(Node* rootPointer){
    if (rootPointer != 0){
        cout<< rootPointer->key<<" ";
        StrightOrderTreeWalk(rootPointer->left);
        StrightOrderTreeWalk(rootPointer->right);
    }
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    //freopen("bstsimple.in", "r", stdin);
    //freopen("bstsimple.out", "w", stdout);


    string curCommand;
    int firstNode = 1;

    Node* rootPointer;;

    while (cin >> curCommand){
         
        if (curCommand[0] == 'f') {
            break;
        }
        if (curCommand[0] == 'i') {
            long long key;
            cin>>key;
            Node* newNode = new Node;
            newNode->key = key;
            newNode->parent = 0;
            newNode->left = 0;
            newNode->right = 0;

            if (firstNode == 1){
                rootPointer = newNode;
                firstNode = 0; }
            else {
                insertX (rootPointer, newNode);
            }
            //cout<<rootPointer<<" ";
            //InorderTreeWalk(rootPointer); cout<<endl;
        }
        if (curCommand[0] == 'd') {
            long long searchKey;
            cin>>searchKey;
            Node* curNode = treeFindFirstInRawElement(rootPointer, searchKey);
            if (curNode != 0) {
                deleteX(rootPointer, curNode, firstNode);
            } //else no action

            //cout<<rootPointer<<" "; InorderTreeWalk(rootPointer); cout<<endl;
        }

        if (curCommand[0] == 'e') {
            long long searchKey;
            cin>>searchKey;
            Node* curNodePointer = treeFindFirstInRawElement(rootPointer, searchKey);
            if (curNodePointer != 0) cout<<"true"<<endl;
            if (curNodePointer == 0) cout<<"false"<<endl;

        }

        if (curCommand[0] == 'n') {
            int insertedNewNode = 0;
            long long searchKey;
            cin>>searchKey;
            Node* curNode = treeFindLastInRawElement(rootPointer, searchKey);

            if (curNode == 0){
                insertedNewNode = 1;
                Node* newNode = new Node;
                newNode->key = searchKey;
                newNode->parent = 0;
                newNode->left = 0;
                newNode->right = 0;

                if (firstNode == 1){rootPointer = newNode; firstNode = 0; }
                else {insertX (rootPointer, newNode);}
                curNode = newNode;

            }

            //cout<<rootPointer<<" "; InorderTreeWalk(rootPointer); cout<<endl;

            Node* nextNode = treeFindNext(curNode);

            if (nextNode != 0) { cout << nextNode->key << endl; }
            else {cout<<"none"<<endl;}

            if (insertedNewNode == 1) deleteX(rootPointer, curNode, firstNode);
            //cout<<rootPointer<<" "; InorderTreeWalk(rootPointer); cout<<endl;

        }

        if (curCommand[0] == 'p') {
            int insertedNewNode = 0;
            long long searchKey;
            cin>>searchKey;
            Node* curNode = treeFindFirstInRawElement(rootPointer, searchKey);

            if (curNode == 0){
                insertedNewNode = 1;
                Node* newNode = new Node;
                newNode->key = searchKey;
                newNode->parent = 0;
                newNode->left = 0;
                newNode->right = 0;

                if (firstNode == 1){rootPointer = newNode; firstNode = 0; }
                else {insertX (rootPointer, newNode);}
                curNode = newNode;
            }

            //cout<<rootPointer<<" "; InorderTreeWalk(rootPointer); cout<<endl;

            Node* prevNode = treeFindPrev(curNode);
            if (prevNode != 0)
                cout << prevNode->key << endl;
            else cout<<"none"<<endl;

            if (insertedNewNode == 1) deleteX(rootPointer, curNode, firstNode);

            //cout<<rootPointer<<" "; InorderTreeWalk(rootPointer); cout<<endl;
        }
    }

    return 0;

}
