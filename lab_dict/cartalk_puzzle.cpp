/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"
#include <tuple>
using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    vector<string> wordbank;
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    while (getline(wordsFile, word)) {
          if(word.length()==5)
            wordbank.push_back(word);
        }
    }
    for(auto& i : wordbank){
      string minusfirst = i.substr(1);
      string minussecond;
      minussecond.append(i.begin(), i.begin()+1);
      minussecond.append(minusfirst.begin()+1, minusfirst.end());
      if(d.homophones(minusfirst, minussecond) && d.homophones(i, minusfirst) && d.homophones(i, minussecond)){
        tuple<string, string, string> yes(i, minusfirst, minussecond);
        //yes.make_tuple(i, minusfirst, minussecond);
        ret.push_back(yes);
      }
      }
    return ret;
}
