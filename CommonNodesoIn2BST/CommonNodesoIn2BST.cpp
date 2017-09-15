// CommonNodesoIn2BST.cpp : Defines the entry point for the console application.
/*
Given two Binary Search Trees, find common nodes in them. In other words, find intersection of two BSTs.
*/
//
//ALGO:
//Method - 1 : DO inorder traversal for each tree and find the intersaction of inOrder traversal
//Method - 2: Use iterative inorder traversal stack for both tree

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TNode {
	int data;
	TNode* left;
	TNode* right;
};

TNode* newNode(int val)
{
	TNode* temp = new TNode();
	temp->data = val;
	temp->left = nullptr;
	temp->right = nullptr;
	return temp;
}

vector<int> intersectionArray(vector<int> &A, vector<int> &B)
{
	vector<int> res;
	int nA = A.size();
	int nB = B.size();
	int i, j;
	i = j = 0;

	while (i < nA && j < nB)
	{
		if (A[i] < B[j])
		{
			i++;
		}
		else if (A[i] > B[j])
		{
			j++;
		}
		else //(A[i] == B[j])
		{
			res.push_back(A[i]);
			i++; j++;
		}
	}

	return res;
}

vector<int> InOrderArray(TNode* root)
{
	vector<int> res;
	if (!root) return res;

	stack<TNode*> S;
	TNode* curr = root;
	//S.push(curr);

	while (!S.empty() || curr)
	{
		if (curr)
		{
			//push to the stack
			S.push(curr);
			curr = curr->left;
		}
		else {
			curr = S.top();
			S.pop();
			res.push_back(curr->data);
			curr = curr->right;
		}
	}

	return res;
}

void printCommonNodeIn2BST_Method1(TNode* t1, TNode* t2)
{
	if (!t1 || !t2) return; //no common nodes;
	vector<int> arr1 = InOrderArray(t1);
	vector<int> arr2 = InOrderArray(t2);
	vector<int> commonNodes = intersectionArray(arr1, arr2);
	for (int i = 0; i < commonNodes.size(); i++)
	{
		cout << commonNodes[i] << " ";
	}
	cout << endl;
	
}

void printCommonNodeIn2BST_Method2(TNode* root1, TNode* root2)
{
	if (!root1 || !root2) return;

	stack<TNode*> S1, S2;

	while (1)
	{
		if (root1)
		{
			S1.push(root1);
			root1 = root1->left;
		}
		else if (root2)
		{
			S2.push(root2);
			root2 = root2->left;
		}
		else if (!S1.empty() && !S2.empty())
		{
			//top of stack is always the smallest 
			root1 = S1.top(); 
			root2 = S2.top();
			if (root1->data < root2->data)
			{
				S1.pop();
				root1 = root1->right;
				root2 = nullptr;

			}
			else if (root1->data > root2->data)
			{
				S2.pop();
				root2 = root2->right;
				root1 = nullptr;
			}
			else { //(root1->data == root2->data
				cout << root1->data << " ";
				S1.pop();
				S2.pop();
				root1 = root1->right;
				root2 = root2->right;
			}
		}
		else 
		{
			//
			break;
		}
	}
	cout << endl;
}

int main()
{
	TNode* t1 = newNode(5);
	t1->left = newNode(1);
	t1->right = newNode(10);
	t1->left->left = newNode(0);
	t1->left->right = newNode(4);
	t1->right->left = newNode(7);
	t1->right->left->right = newNode(9);

	TNode* t2 = newNode(10);
	t2->left = newNode(7);
	t2->right = newNode(20);
	t2->left->left = newNode(4);
	t2->left->right = newNode(9);

	printCommonNodeIn2BST_Method1(t1, t2);
	printCommonNodeIn2BST_Method2(t1, t2);

    return 0;
}

