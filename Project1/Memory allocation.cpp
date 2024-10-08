#define _CRTDBF_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include <cassert>
#include <map>
#include <functional>
using namespace std;

//1.Put the many of data more than momory supposed to use.
//  Every recursive call can put a new stack frame into the stack including parameter, address and variables, 
//  so if a recursive never stop and generate new one again and again, the stack will be filled and can not receive more data.
// 
//use loop to stack overflow;
//class sto {
//	int a;
//public:
//	int loop(int a) {
////(1)
//	while ( a != 0) {
//		cout << a << endl;
//		a = (a + 1) * 2;
//	}
//	return 0;
//}
//};
// 
// //2. dyanamically allocated memory	
// how to avoid? 1.using smart pointer 2.remember to deallocated 
class memoryleak {
	static int leakArray[1000000];
	static void fillarray() {
		for (int i = 0; i < 1000000; ++i) {
			leakArray[i] = i;
		}
	}
};

//3.
class cal_del {
	
public:
	static void full_array() {
		int* array = new int[10];
		for (int i = 0; i < 10; i++ ) {
		array[i] = i;
		cout << array[i] << endl;
		}

	}


};
int* coh() {
	int x = 54;
	int* p = new int(x);
	return p;
 }


class BST
{
	struct node
	{
		int value;
		node* left;
		node* right;
	};
	struct node* root = NULL;
	//Node* CreateNode(int value) 
	//{
	//	Node* newNode = new Node();
	//	newNode->value = value;
	//	newNode->left = newNode -> right = nullptr;
	//	return newNode;

	//}
	void insert_integer(struct node** tree, int value)
	{
		if (*tree == nullptr)
		{
			*tree = new node;
			(*tree)->value = value;
			(*tree)->left = nullptr;
			(*tree)->right = nullptr;

		}
		else if(value < (*tree)->value)
		{
			insert_integer(&(*tree)->left, value);
		}
		else if (value > (*tree)->value)
		{
			insert_integer(&(*tree)->right, value);
		}
	}
	void print_tree(struct node * tree)
	{
		if (tree != NULL)
		{
			print_tree(tree->left);
			cout << tree->value << " ";
			print_tree(tree->right);
		}
	}
	void terminate_tree(struct node* tree)
	{
		if (tree != NULL)
		{
			terminate_tree(tree->left);
			terminate_tree(tree->right);
			delete tree;
		}
	}
	void count_freq(struct node* tree, map<int, int>& freq_mp)
	{
		freq_mp[tree->value]++;
		count_freq(tree->left,freq_mp);
		count_freq(tree->right,freq_mp);
	}
	int most_common_integer(struct node* tree)
	{
		map<int, int> freq_map;
		int freq = 0;
		int number = tree->value;
		for (auto& i : freq_map)
		{
			if (i.second > freq)
			{
				freq = i.second;
				number = i.first;
			}
		}
		return number;

	}
};


int main() {
	//sto st1;
	//st1.loop(6);
	// 
	// //(2)
	//int array[99999999];
	//array[0] = 1;
	//cout << array[0] << endl;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//cal_del::full_array();
	//int* array = new int[10];
	//for (int i = 0; i < 10; i++) {
	//	array[i] = i;
	//	cout << array[i] << endl;
	//}
	//delete[]array;
	int* p = coh();
	cout << *p << endl;
	delete p;

	return 0;

}
