#define _CRTDBF_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
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

struct node { int value; struct node* left; struct node* right; };
struct node* root = NULL;
void insert_integer(struct node** tree, int value) {
	if (*tree == NULL) {
		*tree = new node;
		(*tree)->value = value;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
	}
	else if (value < )
}

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
