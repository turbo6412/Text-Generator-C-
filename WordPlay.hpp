#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "sanitize.hpp"

using namespace std;

class WordPlay {
private:

    unordered_map< string, size_t > table; // Mandatory !!

public:

    WordPlay(); // default constructor
    void readIn(const string& filename); // add words from file to hash table
    size_t numberOfWords(); // return the number of unique words
    size_t wordCount(const string& word); // return the number of occurrences of the given word
    size_t wordBucketIdMethod1(const string& word); // return the bucket number where the given word is located
    size_t wordBucketIdMethod2(const string& word); // another way to find the bucket number where the given word is located
    string mostFrequentWord(); // return the most frequent word
    bool lookUpWord(const string& word); // look up given word
    vector<string> suggest(const string& word); // return a list of suggested words

};

// The following function is complete
WordPlay::WordPlay() {
}

// Implement all functions here
void WordPlay::readIn(const string& filename){
  ifstream infile;
  string word;

  infile.open(filename);          // Open file

  if(!infile.is_open()){          // Check if file is properly opened
    return;
  }

  while(infile >> word){
    sanitize(word);
    if(word.length() == 0){       // If word is empty after sanitization, skips
      continue;                   // current word
    }
    table[word]++;                // Add word to table. If word is already in
  }                               // table, value will increase by 1

  infile.close();                 // Close file
}

size_t WordPlay::numberOfWords(){
  return table.size();
}

size_t WordPlay::wordCount(const string& word){
  // Creating iterator called key and moving it to the bucket where the desired
  // word is located
  unordered_map< string, size_t >::const_iterator key = table.find (word);

  return key->second;               // Return the number of times the desired
}                                   // word occurred

size_t WordPlay::wordBucketIdMethod1(const string& word){
  return table.bucket (word);
}

size_t WordPlay::wordBucketIdMethod2(const string& word){
  size_t bucketNum = 0;

  // Loop through all buckets and then iterate through each individual
  // bucket to find the desired word and return the bucket number when found
  for(int i = 0; i < table.bucket_count(); ++i){
    for( auto it = table.begin(i); it != table.end(i); ++it){
      if(word == it->first){
        bucketNum = i;
      }
    }
  }

  return bucketNum;
}

string WordPlay::mostFrequentWord(){
  int highest = 0;
  string bucketWord = " ";

  // Loop through all buckets to find highest number of occurrences
  for(int i = 0; i < table.bucket_count(); ++i){
    for( auto it = table.begin(i); it != table.end(i); ++it){
      if(it->second > highest){     // Compare each # of occurrences with
        highest = it->second;       // recorded highest, if greater, save value
        bucketWord = it->first;     // Then save the word with the current
      }                             // highest # of occurrences
    }
  }

  return bucketWord;
}

bool WordPlay::lookUpWord(const string& word){
  // Create iterator called search and move it to bucket with where desired word
  // is located
  unordered_map< string, size_t >::iterator search = table.find (word);

  if(search == table.end()){    // If iterator reaches end of the table,
    return false;               // return false
  }
  else{                         // If iterator does not reach end of table,
    return true;                // return true
  }

}

vector<string> WordPlay::suggest(const string& word){
  vector<string> suggestion = {""};
  string dictionary = "";
  int count;

  suggestion.clear();
  for(int i = 0; i < table.bucket_count(); ++i){
    for(auto it = table.begin(i); it != table.end(i); ++it){
      if(it->first.length() == word.length()){
        count = 0;
        dictionary = it->first;
        for( int x = 0; x < word.length(); x++){
          if(dictionary[x] != word[x]){
            count++;
          }
        }
        if(count <= 1){
          suggestion.push_back(dictionary);
        }
      }
    }
  }
  return suggestion;
}
