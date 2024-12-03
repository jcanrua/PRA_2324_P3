#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
		int nelem;
		BSNode<T> *root;

		BSNode<T>* search(BSNode<T>* n, T e) const;
		BSNode<T>* insert(BSNode<T>* n, T e);
		void print_inorder(std::ostream &out, BSNode<T>* n) const;
		BSNode<T>* remove(BSNode<T>* n, T e);
		T max(BSNode<T>* n) const;
		BSNode<T>* remove_max(BSNode<T>* n);
		void delete_cascade(BSNode<T>* n);
    public:
   		BSTree();
		int size() const;
		T search(T e) const;
		T operator[](T e) const;
		void insert(T e);
		friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){	
			bst.print_inorder(out, bst.root); 
			return out;
		}
		void remove(T e);
		~BSTree();
};


template <typename T> 
BSTree<T>::BSTree() : nelem(0), root(nullptr) {}

template <typename T> 
int BSTree<T>::size() const{
 	return nelem;
}

template <typename T> 
T BSTree<T>::search(T e) const{
	return search(root,e)->elem;
}


template <typename T> 
BSNode<T>* BSTree<T>::search(BSNode<T>* n, T e) const{
	if(n == nullptr){
		throw std::runtime_error("No hay nodos en el árbol");
	}
	else if(n->elem < e){
		return search(n->right, e);
	}
	else if(n->elem > e){
		return search(n->left, e);
	}
	else{
		return n;
	}
}

template <typename T>
T BSTree<T>::operator[](T e) const{ 
	return search(e);
}


template <typename T>
void BSTree<T>::insert(T e){
	root = insert(root, e);
}

template <typename T>
BSNode<T>* BSTree<T>::insert(BSNode<T>* n, T e){
	if(n == nullptr){
		n = new BSNode<T>(e);
		nelem++;
	}
	else if(n->elem == e){
		throw std::runtime_error("Elemento duplicado");	
	}
	else if(n->elem > e){
		n->left = insert(n->left, e);
	}
	else if(n->elem < e){
		n->right = insert(n->right, e);
	}
	return n;
}

template <typename T>
void BSTree<T>::print_inorder(std::ostream &out, BSNode<T>* n) const{
	if(n != nullptr){
		print_inorder(out, n->left);
		out << n->elem << " ";
		print_inorder(out, n->right);
	}
}

template <typename T>
void BSTree<T>::remove(T e){
	remove(root, e);
}

template <typename T>
BSNode<T>* BSTree<T>::remove(BSNode<T>* n, T e){
	if(n == nullptr){
		throw std::runtime_error("No hay arbol por aqui");
	}
	else if(n->elem < e){
		n->right = remove(n->right, e);
	}
	else if(n->elem > e){
		n->left = remove(n->left, e);
	}
	else{
		if(n->left != nullptr && n->right != nullptr){
			n->elem = max(n->left);
			n->left = remove_max(n->left);
		}
		else{
			n = (n->left != nullptr) ? n->left : n->right;
			nelem--;
		}
	}
	return n;
}

template<typename T>
T BSTree<T>::max(BSNode<T>* n) const{
	if(n == nullptr){
		throw std::runtime_error("No hay nada por aqui");
	}
	else if(n->right != nullptr){
		return max(n->right);
	}
	else{
		return n->elem;
	}
}


template <typename T>
BSNode<T>* BSTree<T>::remove_max(BSNode<T>* n){
	if(n->right == nullptr){
		return n->left;
	}
	else{
		n->right = remove_max(n->right);
		return n;
	}
}

template <typename T>
BSTree<T>::~BSTree(){
	delete_cascade(root);
}

template <typename T>
void BSTree<T>::delete_cascade(BSNode<T>* n){
	if(n != nullptr){
		delete_cascade(n->left);
		delete_cascade(n->right);
		delete n;
	}
}

#endif
