#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {
    private:
		BSTree<TableEntry<V>>* tree;
    public:
       BSTreeDict();
	   ~BSTreeDict();
	   friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
		   out << *(bs.tree);
		   return out;
	   }
	   V operator[](std::string key);

	   void insert(std::string key, V value);
	   V search(std::string key);
	   V remove(std::string key);
	   int entries();
};

template <typename V>
BSTreeDict<V>::BSTreeDict(){
	tree = new BSTree<TableEntry<V>>();
}
 
template <typename V>
BSTreeDict<V>::~BSTreeDict(){
	delete tree;
}

template <typename V>
V BSTreeDict<V>::operator[](std::string key){
	return search(key);
}

template <typename V>
V BSTreeDict<V>::remove(std::string key) {
	TableEntry<V> entry(key);
	try{
		V value = tree->search(entry).value;
    	tree->remove(entry);
		return value;	
	}
	catch (const std::runtime_error& e){
		throw std::runtime_error("Clave no encontrada");
	}
}

template <typename V>
void BSTreeDict<V>::insert(std::string key, V value){
	tree->insert(TableEntry<V>(key, value));
}

template <typename V>
V BSTreeDict<V>::search(std::string key) {
    TableEntry<V> entry(key);
    try {
        TableEntry<V> found = tree->search(entry);
        return found.value; 
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("Clave no encontrada");
    }
}


template <typename V>
int BSTreeDict<V>::entries(){
	return tree->size();
}
#endif
