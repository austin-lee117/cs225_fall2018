#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <iostream>
#include <stack>
#include <vector>
#include <map>

using namespace std;
/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;
  map<pair<string, string>, string> history;
  //mark all vertices as unused
  for (auto it = vertexMap.begin(); it!=vertexMap.end(); it++){
    (it->second)[(it->second).key()] = "no";
  }
  //mark all edges as unused
  for (auto it = edgeList.begin(); it!=edgeList.end(); it++){
    string key1 = (*it).get().source().key();
    string key2 = (*it).get().dest().key();
    history.insert(pair<pair<string, string>, string>(pair<string,string>(key1,key2),"no"));
  }
  unordered_map<string, string> predecessor;
  queue<string>que;
  //starting bfS algorithm
  que.push(start);
  V & vx = vertexMap.at(start);
  vx[start] = "yes";
  while(!que.empty()){
    string current = que.front();
    que.pop();
    vector<string> adjacentnodes;
    //checking if edge/nodes exist and are adjacent
    for(auto it = vertexMap.begin(); it!=vertexMap.end(); it++){
      string checking = it->first;
      if(isAdjacent(current, checking)){
        adjacentnodes.push_back(checking);
      }
    }
    //checking all possible edges/nodes
    for(unsigned long i = 0; i<adjacentnodes.size(); i++){
      V& tempvert = vertexMap.at(adjacentnodes[i]);
      pair<string, string> edgecheck = pair<string,string>(current, adjacentnodes[i]);
      //if vertex is not explored
      if(tempvert[adjacentnodes[i]]=="no"){
        history[edgecheck] = "yes";
        tempvert[adjacentnodes[i]] = "yes";
        predecessor.insert(pair<string, string>(adjacentnodes[i],current));
        que.push(adjacentnodes[i]);
      }
      else if(history[edgecheck]=="no") history[edgecheck] = "disregard";
    }
  }
  string endpoint = end;
  //push nodes onto path and reverse order
  while(endpoint!=start){
  path.push_back(endpoint);
  endpoint = predecessor[endpoint];
  }
  path.push_back(endpoint);
  path.reverse();
  return path;
}
