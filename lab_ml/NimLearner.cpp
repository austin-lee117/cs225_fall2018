/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>
#include<vector>
#include<string>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    for(unsigned int i = 0; i<=startingTokens;i++){
    Vertex p1;
    Vertex p2;
    g_.insertVertex("p1-" + to_string(i));
    g_.insertVertex("p2-" + to_string(i));
}
  for(unsigned int i = startingTokens; i>1; i--){
    g_.insertEdge("p1-"+to_string(i), "p2-"+to_string(i-2));
    g_.setEdgeWeight("p1-"+to_string(i), "p2-"+to_string(i-2),0);
    g_.insertEdge("p2-"+to_string(i), "p1-"+to_string(i-2));
    g_.setEdgeWeight("p2-"+to_string(i), "p1-"+to_string(i-2),0);
    }
    for(unsigned int i = startingTokens; i>0; i--){
      g_.insertEdge("p1-"+to_string(i), "p2-"+to_string(i-1));
      g_.setEdgeWeight("p1-"+to_string(i), "p2-"+to_string(i-1),0);
      g_.insertEdge("p2-"+to_string(i), "p1-"+to_string(i-1));
      g_.setEdgeWeight("p2-"+to_string(i), "p1-"+to_string(i-1),0);
      }

  startingVertex_="p1-"+to_string(startingTokens);
  number_token = startingTokens;
}
/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
 string player = "p2-";
 int token = number_token;
 Vertex vx = startingVertex_;

 while(token>0){
   int random = rand()%2+1;
   if(token==1){
     random = 1;
   }
   Vertex next = player+to_string(token-random);
   path.push_back(g_.getEdge(vx,next));
   vx = next;
   if(player == "p1-"){
     player = "p2-";
   }
   else(player = "p1-");

   token = token - random;
    }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 int size = path.size()-1;
 Edge last = path[size];
 Vertex lastvx = last.dest;
 if(lastvx=="p2-0"){
   for(int i = 0; i<=size; i++){
     Edge currvx = path[i];
     if(i%2==0){
       int curr = g_.getEdgeWeight(currvx.source, currvx.dest);
       g_.setEdgeWeight(currvx.source, currvx.dest, curr +1);
     }
     else{
       int curr = g_.getEdgeWeight(currvx.source, currvx.dest);
       g_.setEdgeWeight(currvx.source, currvx.dest, curr-1);
     }
   }
   return;
 }
  else{
    for(int i = 0; i<=size; i++){
      Edge currvx = path[i];
      if(i%2==1){
        int curr = g_.getEdgeWeight(currvx.source, currvx.dest);
        g_.setEdgeWeight(currvx.source, currvx.dest, curr +1);
      }
      else{
        int curr = g_.getEdgeWeight(currvx.source, currvx.dest);
        g_.setEdgeWeight(currvx.source, currvx.dest, curr-1);
      }
    }
  }

}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
