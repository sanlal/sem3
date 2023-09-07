#include<bits/stdc++.h>
#include<iostream>
using namespace std;

class node{
    public:
      int data;
      node *left;
      node *right;

      node(int d){
        this->data = d;
        this->left=NULL;
        this->right=NULL;
      }
};

node* buildTree(node *root){
    int data;
    cout<<"Enter data:: ";
    cin>>data;
    root= new node(data);
    if(data==-1){
        return NULL;
    }

    cout<<"Enter Left Child of "<<data<<" : ";
    root->left = buildTree(root->left);

     cout<<"Enter Left Child of "<<data<<" : ";
    root->right = buildTree(root->right);


}

int main(){
    node *root;
    root=NULL;

    root = buildTree(root);
}