/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "schashtable.h"

using hashes::hash;
using std::list;
using std::pair;


template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new list<pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new list<pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new list<pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
  ++elems;
  if(shouldResize()){resizeTable();}
  int index = hash(key, size);
  pair<K,V>temp(key, value);
  table[index].push_front(temp);
    /**
     * @todo Implement this function.
     *
     */

}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    typename list<pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the lab spec about list iterators and the
     * erase() function on std::list!
     */
    //(void) key; // prevent warnings... When you implement this function, remove this line.
    int index = hash(key, size);
    typename list<pair<K,V>>::iterator i = table[index].begin();
    for(;i!=table[index].end();++i){
      if(i->first==key){
        table[index].erase(i);
        break;
      }
    }
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    int index = hash(key, size);
    typename list<pair<K,V>>::iterator i = table[index].begin();
    for(; i!=table[index].end(); ++i){
      if(i->first ==key){
        return i->second;
      }
    }
    /**
     * @todo: Implement this function.
     */

    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hash(key, size);
    pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new list<pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    typename list<pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the spec about list iterators!
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
     typename list<pair<K,V>>::iterator i;
     size_t resized = findPrime(size*2);
     list<pair<K,V>> * temptable = new list <pair<K,V>>[resized];
     for (unsigned x = 0; x<size; x++){
       for (i = table[x].begin();i!=table[x].end();i++ ){
         int index = hash(i->first, resized);
         pair<K,V> temp(i->first, i->second);
         temptable[index].push_front(temp);
       }
     }
     delete[] table;
     table = temptable;
     size = resized;
}
