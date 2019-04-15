

#ifndef BST_H
#define BST_H

#include <cstddef>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stack>


template<typename T>
struct node{
	T value;
	node<T> *parent;
	node<T> *left;
	node<T> *right;
};

// data structure to hold important info about the results of searching for a a value in a tree
template<typename T>
struct search_result{
	bool found;
	char direction;
	node<T> *result_node;
};


template<class T>
class BST{

	public:
		BST();
		BST(const BST &a){root = a.root; length = a.length;}
		BST & operator=(const BST &a){root = a.root; length = a.length; return *this;}
		~BST();
		void insert_val(T val);
		bool delete_val(T val);  // true - deleted
		T get_max();
		T get_min();
		bool exists(T val);
		int get_length();
		void print_tree();
		T get_root();

	public:
        node<T> *search_successor(node<T> *location);
        	T get_successor(T val);
		/**
		 *	Recursively search for the node that contains the maximum value in the BST
		 *	@param location the node pointer to begin the search from
		 *	@return the node pointer that points to the node with the maximum value
		 */
		node<T> *search_max(node<T> *location);

		/**
		 *	Recusively search for the node that contains the minimum value in the BST
		 *	@param location the node pointer to begin the search from
		 *	@return the node pointer that points to the node with the minimum value
		 */
		node<T> *search_min(node<T> *location);

		/**
		 *	Recursively search for a node that contains the desired value
		 *	@param val the value that is being searched for in the BST
		 *	@param location the node pointer to begin the search from
		 *	@return returns a search_result data structure that contains details about the search result
		 */
		search_result<T> search_val(T val, node<T> *location);

		/**
		 *	Traverse the BST. 2 modes:
		 *	@param location the pointer to the node that is being traversed
		 *	@param function the mode
		 *		function == 0 -> traverse in order, print each node value
		 *		function == 1 -> traverse in post order, recursively deleting each node
		 */
		void order(node<T> *location, int function);


		void delete_node(node<T> *location);

		node<T> *root;
		int length;
};


// Constructor
template<class T>
BST<T>::BST(){
	root = NULL;
	length = 0;
}



// Destructor
template<class T>
BST<T>::~BST(){
	if (length > 0)
		order(root, 1);
}

// insert a value
template<class T>
void BST<T>::insert_val(T val){
	search_result<T> result = search_val(val, root);
	if (result.found == true){
		node<T> *ptr = new node<T>;
		ptr->value = val;
		ptr->parent = result.result_node;
		ptr->left = (result.result_node)->left;
		ptr->right = NULL;
		(result.result_node)->left = ptr;
	}
	else{
		if (result.direction == 'R'){
			node<T> *ptr = new node<T>;
			ptr->value = val;
			ptr->parent = result.result_node;
			ptr->left = NULL;
			ptr->right = NULL;
			(result.result_node)->right = ptr;
		}
		else if (result.direction == 'L'){
			node<T> *ptr = new node<T>;
			ptr->value = val;
			ptr->parent = result.result_node;
			ptr->left = NULL;
			ptr->right = NULL;
			(result.result_node)->left = ptr;
		}
		else if (result.direction == 'E'){
			std::cout << "Error" << std::endl;
			length--;
		}
		else{
			node<T> *ptr = new node<T>;
			ptr->value = val;
			ptr->parent = NULL;
			ptr->left = NULL;
			ptr->right = NULL;
			root = ptr;
		}
	}
	length++;
}



// delete a value
template<class T>
bool BST<T>::delete_val(T val){
	search_result<T> result = search_val(val, root);
	node<T> *location = result.result_node;
	if (result.found){
		delete_node(location);
		return true;
	}
	else{
		return false;
	}
}

// delete a node
template<class T>
void BST<T>::delete_node(node<T> *location){
	if (location->left == NULL && location->right == NULL){
		//std::cout << "deleting " << location->value << std::endl;
		if (location->parent != NULL){
			if (location->parent->left == location){
				location->parent->left = NULL;
			}
			else if (location->parent->right == location){
				location->parent->right = NULL;
			}
		}
		delete location;
		length--;
		return;
	}
	// one child on left
	else if (location->left != NULL && location->right == NULL){
		node<T> *left = location->left;
		left->parent = location->parent;
		// is root
		if (location->parent == NULL){
			//std::cout << "deleting root " << location->value << "\tnew root: " << left->value << std::endl;
			root = left;
		}
		else if (location->parent->left == location){
			//std::cout << "deleting " << location->value << std::endl;
			location->parent->left = left;
		}
		else if (location->parent->right == location){
			//std::cout << "deleting " << location->value << std::endl;
			location->parent->right = left;
		}
		delete location;
		length--;
		return;
	}
	// one child on right
	else if (location->left == NULL && location->right != NULL){
		node<T> *right = location->right;
		right->parent = location->parent;
		// is root
		if (location->parent == NULL){
			//std::cout << "deleting root " << location->value << "\tnew root: " << right->value << std::endl;
			root = right;
		}
		else if (location->parent->left == location){
			//std::cout << "deleting " << location->value << std::endl;
			location->parent->left = right;
		}
		else if (location->parent->right == location){
			//std::cout << "deleting " << location->value << std::endl;
			location->parent->right = right;
		}
		delete location;
		length--;
		return;
	}
	// two children
	else{
		node<T> *successor_node = search_successor(location);
		T temp_val = location->value;
		location->value = successor_node->value;
		successor_node->value = temp_val;
		delete_node(successor_node);
		return;
	}
}

// get the max value
template<class T>
T BST<T>::get_max(){
	node<T> *max_node = search_max(root);
	if (max_node != NULL){
		return max_node->value;
	}
	else{
		return 0;
	}
}

// get the min value
template<class T>
T BST<T>::get_min(){
	node<T> *min_node = search_min(root);
	if (min_node != NULL){
		return min_node->value;
	}
	else{
		std::cout << "Warning: empty BST" << std::endl;
		return 0;
	}
}

// get the max node
template<class T>
node<T>* BST<T>::search_max(node<T> *location){
	if (location->right == NULL){
		if (length == 0){
			return NULL;
		}
		return location;
	}
	else{
		return search_max(location->right);
	}
}

// get the min node
template<class T>
node<T>* BST<T>::search_min(node<T> *location){
	if (location->left == NULL){
		if (length == 0){
			return NULL;
		}
		return location;
	}
	else{
		return search_min(location->left);
	}
}


// check if val exists
template<class T>
bool BST<T>::exists(T val){
	search_result<T> result = search_val(val, root);
	if (result.found){
		return true;
	}
	else{
		return false;
	}
}

// traverse bst
template<class T>
void BST<T>::order(node<T> *location, int function){
	// traverse in order to get the sorted tree
	// left, root, right
	if (function == 0){
		if (location->left != NULL){
			order(location->left, function);
		}
		std::cout << location->value << std::endl;
		if (location->right != NULL){
			order(location->right, function);
		}

	}
	// traverse post order to recursively delete items
	// left, right, root
	else if (function == 1){
		if (location->left != NULL){
			order(location->left, function);
		}
		if (location->right != NULL){
			order(location->right, function);
		}
		length--;
		delete location;
	}
	else{
	}
}

// search for a node
template<class T>
search_result<T> BST<T>::search_val(T val, node<T> *location){
	if (location == NULL){
		search_result<T> result;
		result.found = false;
		result.direction = 'N';
		result.result_node = NULL;
		return result;
	}
	else if (location->value == val){
		search_result<T> result;
		result.found = true;
		result.direction = 'N';
		result.result_node = location;
		return result;
	}
	else if (val > location->value && location->right == NULL){
		search_result<T> result;
		result.found = false;
		result.direction = 'R';
		result.result_node = location;
		return result;
	}
	else if (val > location->value && location->right != NULL){
		return search_val(val, location->right);
	}
	else if (val < location->value && location->left == NULL){
		search_result<T> result;
		result.found = false;
		result.direction = 'L';
		result.result_node = location;
		return result;
	}
	else if (val < location->value && location->left != NULL){
		return search_val(val, location->left);
	}
	else{
		search_result<T> result;
		result.found = false;
		result.direction = 'E';
		result.result_node = NULL;
		return result;
	}
}

// get the number of nodes
template<class T>
int BST<T>::get_length(){
	return length;
}

// print contents in order
template<class T>
void BST<T>::print_tree(){
	std::cout << std::endl << "Elementy drzewa: " << std::endl;
	if (length > 0)
		order(root, 0);
	else{
	}
}

template<class T>
T BST<T>::get_root(){
	if (length > 0){
		return root->value;
	} else{
		return 0;
	}
}

template<class T>
T BST<T>::get_successor(T val){
	search_result<T> location = search_val(val, root);
	if (location.found){
		node<T> *successor_node = search_successor(location.result_node);
		if (successor_node != NULL){
			return successor_node->value;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}

template<class T>
node<T> *BST<T>::search_successor(node<T> * location){
	if (location->right != NULL){
		return search_min(location->right);
	}
	else{
		node<T> *parent = location->parent;
		node<T> *child = location;
		while (parent != NULL && parent->left != child){
			child = parent;
			parent = parent->parent;
		}
		return parent;
	}
}

template<typename T>
class Myset{

public:

    void set_add(T val);
    void set_delete(T val);
    BST<T> bst;
};

template <class T>
void Myset<T>::set_add(T val){
    if(bst.exists(val)==0){
        bst.insert_val(val);
        bst.print_tree();
    }
}
template<class T>
void Myset<T>::set_delete(T val){
    if(bst.exists(val)==1){
        bst.delete_val(val);
        bst.print_tree();
    }
}


template <class T>

class Iterator {

public:
    Iterator() = default;
    Iterator(const std::stack<node<T>> &node_and_predecessors);

    //Iterator(const Iterator&) = default;
    //Iterator& operator=(const Iterator&) = default;
    //Iterator(Iterator&&) = default;
    //Iterator& operator=(Iterator&&) = default;
    Iterator(const node<T>);


    friend class Myset<T>;

private:
    //std::stack< node<T>> node_and_predecessors_;
    node<T> first, current;

public:
    //bool operator==(const Iterator &it) const;
    //bool operator!=(const Iterator &it) const { return !(*this  == it);}
    Iterator& operator++();
    Iterator operator++(int);
    //T& operator*() const;
    //T& operator->() const;
    T begin(const BST<T> &tree);
    T end (const BST<T> &tree  );

    void stack_print();

};

template <class T>
Iterator<T>::Iterator(node<T> root){
    current = root;
    std::cout << current->value << std::endl;
}

template<class T>
T Iterator<T>::begin(const BST<T> &tree){
   first = *tree.root;
        while(first.left != NULL){
                first = first->left;
            }
        return first;
    }


template <class T>
T Iterator<T>::end(const BST<T> &tree){
    node<T> last = tree.root;
    while (last.right != NULL){
        last = last.right;
    }
    return Iterator(last);

}


#endif
