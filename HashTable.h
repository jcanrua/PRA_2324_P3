#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "/home/jorge/uni/pra/practicas/practica1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {
    private:
		int n;
		int max;
		ListLinked<TableEntry<V>>* table;
		int h(std::string key);
    public:
       	HashTable(int size);
		~HashTable();
		int capacity();
		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
			for (int i = 0; i < th.max; i++) {
        		out << "Bucket " << i << ": ";
        		Node<TableEntry<V>>* current = th.table[i].first;
        		while (current != nullptr) {
            		out << "[" << current->data.key << ": " << current->data.value << "] -> ";
           			current = current->next;
       			}
    	 		out << "nullptr\n";
    		}
    		return out;
		}

		V operator[](std::string key);
		
		//heredados
		void insert(std::string key, V value) override final;
		V search(std::string key) override final;
		V remove(std::string key) override final;
		int entries() override final;
};

template <typename V>
int HashTable<V>::h(std::string key){
	int suma = 0;
	for(int i = 0; i < key.size(); i++){
		suma += int(key.at(i));
	}
	return suma % max;
}

template <typename V>
HashTable<V>::HashTable(int size): n(0), max(size){
	table = new ListLinked<TableEntry<V>>[max];
}

template <typename V>
HashTable<V>::~HashTable(){
	delete[] table;
}

template <typename V>
int HashTable<V>::capacity(){
	return max;
}

template <typename V>
V HashTable<V>::operator[](std::string key){
	return search(key);
}

template <typename V>
void HashTable<V>::insert(std::string key, V value){
	int index = h(key);
	Node<TableEntry<V>>* current = table[index].first;
	while(current != nullptr){
		if(current->data.key == key){
			throw std::runtime_error("La llave ya existe");
		}
		current = current->next;
	}

	TableEntry<V> nueva(key, value);
	table[index].prepend(nueva);
	n++;
}

template <typename V>
V HashTable<V>::search(std::string key){
	int index = h(key);
	Node<TableEntry<V>>* current = table[index].first;
	
	while(current != nullptr){
		if(current->data.key == key){
			return current->data.value;
		}
		current = current->next;
	}
	throw std::runtime_error("La llave no tiene ningun valor asociado");
}

template <typename V>
V HashTable<V>::remove(std::string key){
	int index = h(key);
	Node<TableEntry<V>>* current = table[index].first;
	Node<TableEntry<V>>* prev = nullptr;
	
	while(current != nullptr){
		if(current->data.key == key){
			if(prev != nullptr){
				prev->next == current->next;
			}
			else{
				table[index].first = current->next;
			}
			V dato_eliminado = current->data.value;
			delete current;
			n--;
			return dato_eliminado;
		}
		else{
			prev = current;
			current = current->next;
		}
	}
	throw std::runtime_error("La llave no tiene ningun valor asociado");
}

template <typename V>
int HashTable<V>::entries(){
	return n;
}

#endif
