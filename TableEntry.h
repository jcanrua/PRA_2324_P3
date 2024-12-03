#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V> 
class TableEntry {
    public:
   		std::string key;
		V value;
		TableEntry(std::string key, V value);
		TableEntry(std::string key);
		TableEntry();

		friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){
			return te1.key == te2.key;
		}

		friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){
 			return te1.key != te2.key;
		}

		friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te){
			out << te.key << " -> " << te.value;
			return out;
		}
		friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2){
			if(te1.key < te2.key){
				return true;
			}
			else{
				return false;
			}
 		}
		friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2){
			if(te1.key > te2.key){
				return true;
			}
			else{
				return false;
			}

		}
};

template <typename V>
TableEntry<V>::TableEntry(const std::string key, const V value)
	: key(key), value(value) {}

template <typename V>
TableEntry<V>::TableEntry(std::string key)
	: key(key), value(V{}) {}

template <typename V>
TableEntry<V>::TableEntry()
	: key(""), value(V{}) {}

#endif
