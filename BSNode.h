#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
   		T elem;
		BSNode<T>* left;
		BSNode<T>* right;
		BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* right=nullptr);
		friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn){
			for(int i = 0; i < bsn.size(); i++){
				out << bsn.elem << ", ";
			}
			return out;
		}
};


template <typename T> 
BSNode<T>::BSNode(T elem, BSNode<T>* left, BSNode<T>*right){
	this->elem = elem;
	this->left = left;
	this->right = right;
}

#endif
