#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "sanitize.hpp"

using namespace std;

class TextGen {
private:
    map<string, vector<string>> markov_chain; //map usage is mandatory!
	map<string, vector<string>>::iterator it; //iterator 


public:
	TextGen(const unsigned int seed);
	void readIn(const string & filename);
	bool isEndPunctuation(const char character);
	vector<string> getValues(const string & key);
	string generateSentence();
	map<string, vector<string>> get_markovChain();
};

//TextGen's constructor has been created for you
TextGen::TextGen(const unsigned int seed)
{
	srand(seed);//seeds our random number generator
}


//Create the rest of the functions below...
void TextGen::readIn(const string& filename) {
	ifstream infile(filename); //opens the file and closes once the end of the function
	string word; //a string word to store in the individual words from the files
	string old_word = "^"; //a string word to store in the previous word and have "^" it to indicate the start of a sentence
	while (infile >> word) {
		infile.ignore();
		sanitize(word); //call the sanitize function to remove non-alphabetic characters like dashes, slashes, etc.
		if (isEndPunctuation(word[word.size() - 1])) { //if the current word ends with a punctuation
			string punctuation(1, word[word.size() - 1]); //grabs the punctuation of the word and stores it
			word = word.substr(0, word.size() - 1); //removes the punctuation word
			markov_chain[old_word].push_back(word); //searches for the keyword of old_word and either find and push_back the current word without the punctuation or creates a new entry with the old_word as the key entry and push_back the current word without the punctuation
			markov_chain[word].push_back(punctuation); //searches for the keyword of the current word and either find and push_back the punctuation or creates a new entry with the current word as the key entry and push_back the punctuation
			markov_chain[punctuation].push_back("$"); //searches for the key for the specific punctuation and creates a new entry with the punctuation as the key entry and push_back the question mark to indicate the end of a sentence
			old_word = "^"; //set the old_word as "^" to indicate the start of a new sentence
		}
		else {
			markov_chain[old_word].push_back(word); //searches for the keyword of old_word and either find and push_back the current word or creates a new entry with the old_word as the key entry and push_back the current word
			old_word = word; //set the old_word as the current word
		}
	}
}

bool TextGen::isEndPunctuation(const char character) {
	if (character == '.') //return true if the character is a period, question, exclamation
		return true; 
	else if (character == '?')
		return true; 
	else if (character == '!') 
		return true; 
	else
		return false; //returns false
}

vector<string> TextGen::getValues(const string& key) {
	it = markov_chain.find(key);  // iterates through entire map to find the key
	if (it != markov_chain.end()) {	// if we found they key, print it's value
		return it->second;
	}
	else
		cout << "Key does not exist."; 
}

string TextGen::generateSentence() {
	string sentence; //a string sentence to generate the sentence
	string token; //a string to hold the key that will add to the sentence and used to search in the map
	int size = rand() % markov_chain["^"].size(); //size holds the random generator between 0 to the size of the key vector
	token = markov_chain["^"].at(size); //gets the random word from the key to its value vector using the random generator number

	sentence = token; // sentence has one word now
	while (token != "$") { //a while loop that will stop when the token is "$"
		size = rand() % markov_chain[token].size(); //gets the random word from the key to its value vector using the random generator number
		token = markov_chain[token].at(size); //gets the random word from the key vector using the random generator number
		if (token == "$") {//if the token word is "$"
			string punctuation(1, sentence[sentence.size() - 1]); //grabs the punctuation from the sentence
			sentence = sentence.substr(0, sentence.size() - 2); //removes both the punctuation of sentence and the space at the end
			sentence += punctuation; //adds the punctuation to the sentence without any spacing between it
		}
		else {
			sentence += " " + token; //adds the token word to the sentence string with a space between it
		}
	}

	return sentence; //returns the generated sentence

}


map<string, vector<string>> TextGen::get_markovChain() {
	return markov_chain; 
}
