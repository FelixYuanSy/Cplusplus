//#define _CRTDBF_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//#include <iostream>
//#include <cassert>
//#include <map>
//#include <functional>
//using namespace std;
//
////1.Put the many of data more than momory supposed to use.
////  Every recursive call can put a new stack frame into the stack including parameter, address and variables, 
////  so if a recursive never stop and generate new one again and again, the stack will be filled and can not receive more data.
//// 
////use loop to stack overflow;
////class sto {
////	int a;
////public:
////	int loop(int a) {
//////(1)
////	while ( a != 0) {
////		cout << a << endl;
////		a = (a + 1) * 2;
////	}
////	return 0;
////}
////};
//// 
//// //2. dyanamically allocated memory	
//// how to avoid? 1.using smart pointer 2.remember to deallocated 
//class memoryleak {
//	static int leakArray[1000000];
//	static void fillarray() {
//		for (int i = 0; i < 1000000; ++i) {
//			leakArray[i] = i;
//		}
//	}
//};
//
////3.
//class cal_del {
//	
//public:
//	static void full_array() {
//		int* array = new int[10];
//		for (int i = 0; i < 10; i++ ) {
//		array[i] = i;
//		cout << array[i] << endl;
//		}
//
//	}
//
//
//};
//int* coh() {
//	int x = 54;
//	int* p = new int(x);
//	return p;
// }
//
//
//class BST
//{
//	struct node
//	{
//		int value;
//		node* left;
//		node* right;
//	};
//	struct node* root = NULL;
//public:
//	BST() {
//		root = nullptr;  // Initialize root -> nullptr
//	}
//
//	void insert_integer(int value)
//	{
//		insert_integer(&root, value);
//	}
//
//	void print_tree()
//	{
//		print_tree(root);
//	}
//
//	int most_common_integer()
//	{
//		return most_common_integer(root);
//	}
//
//	int largest_integer()
//	{
//		return largest_integer(root);
//	}
//
//	int summ_of_all_integers()
//	{
//		return summ_of_all_integers(root);
//	}
//
//	void terminate_tree()
//	{
//		terminate_tree(root);
//	}
//
//private:
//
//	void insert_integer(struct node** tree, int value)
//	{
//		if (*tree == nullptr)
//		{
//			*tree = new node;
//			(*tree)->value = value;
//			(*tree)->left = nullptr;
//			(*tree)->right = nullptr;
//
//		}
//		else if(value <= (*tree)->value)
//		{
//			insert_integer(&(*tree)->left, value);
//		}
//		else if (value >= (*tree)->value)
//		{
//			insert_integer(&(*tree)->right, value);
//		}
//	}
//	void print_tree(struct node * tree)
//	{
//		if (tree != NULL)
//		{
//			print_tree(tree->left);
//			cout << tree->value << " ";
//			print_tree(tree->right);
//		}
//	}
//	void terminate_tree(struct node* tree)
//	{
//		if (tree != NULL)
//		{
//			terminate_tree(tree->left);
//			terminate_tree(tree->right);
//			delete tree;
//		}
//	}
//	void count_freq(struct node* tree, map<int, int>& freq_mp)
//	{
//		if (tree == nullptr) {
//			return; 
//		}
//		freq_mp[tree->value]++;
//		count_freq(tree->left,freq_mp);
//		count_freq(tree->right,freq_mp);
//	}
//	int most_common_integer(struct node* tree)
//	{
//		map<int, int> freq_map;
//		count_freq(tree, freq_map);
//		int freq = 0;
//		int number = tree->value;
//		for (auto& i : freq_map)
//		{
//			if (i.second > freq)
//			{
//				freq = i.second;
//				number = i.first;
//			}
//		}
//		return number;
//
//	}
//	int largest_integer(struct node* tree)
//	{
//		while (tree->right != nullptr)
//		{
//			tree = tree->right;
//		}
//		return tree->value;
//	}
//	int summ_of_all_integers(struct node* tree)
//	{
//		if (tree == nullptr)
//		{
//			return 0;
//		}
//		return (tree->value) + summ_of_all_integers(tree->left) + summ_of_all_integers(tree->right);
//	}
//};
//
//
//int main() {
//	//sto st1;
//	//st1.loop(6);
//	// 
//	// //(2)
//	//int array[99999999];
//	//array[0] = 1;
//	//cout << array[0] << endl;
//
//	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	////cal_del::full_array();
//	////int* array = new int[10];
//	////for (int i = 0; i < 10; i++) {
//	////	array[i] = i;
//	////	cout << array[i] << endl;
//	////}
//	////delete[]array;
//	//int* p = coh();
//	//cout << *p << endl;
//	//delete p;
//	BST b1;
//	b1.insert_integer(50);
//	b1.insert_integer(10);
//	b1.insert_integer(20);
//	b1.insert_integer(30);
//	b1.insert_integer(5);
//	b1.insert_integer(2);
//	b1.insert_integer(8);
//	b1.insert_integer(30);
//	b1.insert_integer(10);
//	b1.insert_integer(30);
//	b1.insert_integer(8);
//	b1.print_tree();
//	cout << endl;
//	cout<< "largest number " << b1.largest_integer() << endl;
//	cout << "most common number " << b1.most_common_integer() << endl;
//	cout << "sum of all number " << b1.summ_of_all_integers() << endl;
//	b1.terminate_tree();
//
//	return 0;
//
//}
