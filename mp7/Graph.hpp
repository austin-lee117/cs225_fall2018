#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
#include<unordered_map>
using std::unordered_map;
using std::make_pair;
using namespace std;

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  auto i = vertexMap.begin();
  int x = 0;
  for(; x<vertexMap.bucket_count();x++){
    if(*i->second == v) break;
    i++;
  }
  if(x==vertexMap.bucket_count()) return -1;
  else return vertexMap.bucket_size(x);
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  V & vx = *(new V(key));
  vertexMap.insert(pair<string, V&>(key, vx));
  list<edgeListIter> templist = * new list<edgeListIter>;
  adjList.insert(pair<string, list<edgeListIter>>(key, templist));
  return vx;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
//  cout<<"removing vertex "+key<<endl;
  list<edgeListIter> templist = adjList.at(key);

  for(auto it = templist.begin(); it!=templist.end(); it++){
//    cout<<(**it).get()<<endl;
    edgeList.erase(*it);
  }

  adjList.erase(key);
  vertexMap.erase(key);
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  E & edd = *(new E(v1, v2));
  auto tempeli = ref(edd);
  edgeList.push_back(tempeli);
  auto i = edgeList.end();
  i--;
  adjList.at(v1.key()).push_back(i);

  return edd;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2){
  V v1 = vertexMap.at(key1);
  V v2 = vertexMap.at(key2);
  E edd = E(v1, v2);
  list<edgeListIter> templist = adjList.at(key1);
  for(auto it = templist.begin(); it!=templist.end(); it++){
    if((**it).get()==edd){
      templist.erase(it);
    }
  }
  auto i = edgeList.begin();
  for(;i!=edgeList.end();i++){
    if((*i).get()==edd){
      edgeList.erase(i);
      return;
    }
  }
  return;
  }


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it){
  V temp = (*it).get().source();
  list<edgeListIter> templist = adjList.at(temp.key());
  templist.erase(it);
  edgeList.erase(it);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  std::list<std::reference_wrapper<E>> edges;
/*  list<edgeListIter> edgy = adjList.at(key);
  for(typename list<edgeListIter>::iterator i = edgy.begin(); i!=edgy.end();i++){
    cout<<"aye"<<endl;
    edges.push_back((**i));
  }
*/
  auto it = edgeList.begin();
  for(; it != edgeList.end(); it++){
    if((*it).get().source() == key) edges.push_back(*it);
    if((*it).get().dest()==key) edges.push_back(*it);
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  V v1 = vertexMap.at(key1);
  V v2 = vertexMap.at(key2);
  E edd = E(v1, v2);
  auto i = edgeList.begin();
  for(;i!=edgeList.end();i++){
    if((*i).get()==edd){
      return true;
    }
  }

  return false;
}
