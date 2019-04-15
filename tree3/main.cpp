#include "BST.h"

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <typeinfo>
#include <vector>
template<typename T>
bool set_add(BST<T> *tree, T val){
    if(tree->exists(val) == 0){
        tree->insert_val(val);
        return true;
    }
    else {
        return false;
    }

}

template<typename T>
bool set_delete(BST<T> *tree, T val){
    if (tree->exists(val)== 1){
        tree->delete_val(val);
        return true;
    }
    else return false;
}
int main(){

	srand(time(NULL));
   BST<int> BST2;
	//BST<int> BST;

    std::cout << "hi" << std::endl;
//	for (int i = 0; i < 15; i++){
//	/	int num = rand() % 10;
	//	BST.insert_val(5);
     //   BST.insert_val(4);
     //   BST.insert_val(7);
      //  BST.insert_val(2);
//	}





  //  std::cout << "PIERWSZE DRZEWO" << std::endl;

//	BST.print_tree();

    set_add(&BST2, 6);
   set_add(&BST2, 5);
    set_add(&BST2, 5);
    set_add(&BST2, 5);
    set_add(&BST2, 8);
    set_add(&BST2, 5);
    set_add(&BST2, 3);
      set_add(&BST2, 8);
        set_add(&BST2, 8);
	    std::cout << "DRUGIE DRZEWO"  << std::endl;

       BST2.print_tree();

       BST<int> BSTC = BST2;
        BST<int> BSTO;
        std::cout << "SKOPIOWANE DRZEWO"  << std::endl;
         BSTC.print_tree();

         BSTO = BST2;
         std::cout << "ASSIGMENT"  << std::endl;
         BSTO.print_tree();

         set_delete(&BST2, 8);

          std::cout << "BST 2"  << std::endl;
         BST2.print_tree();
          std::cout << "BSTO 2"  << std::endl;
         BSTO.print_tree();
          std::cout << "BSTC 2"  << std::endl;
         BSTC.print_tree();

         std::cout << std::endl;
         std::vector<int> v(10,4);

         Myset<int> myset;
         myset.set_add(5);
        myset.set_add(5);
        myset.set_add(7);
        myset.set_delete(5);

        BST<int> A;
        A.insert_val(2);
        A.insert_val(5);
        A.print_tree();
        Iterator<int> B;
        B.begin(A);

	return 0;
}
