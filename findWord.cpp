#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <fstream>
#include <sstream>


using namespace std;

int findWordPosition(ifstream&, multimap<string, pair<int,int> >&);
string replaceAll(string&, string, string);
void print(const multimap<string, pair<int,int> > &); 

int main() {
   ifstream inFile("poem.txt");

   multimap<string,pair<int, int> > wordPositions;
   
   int lineNumber = findWordPosition(inFile, wordPositions);

   cout << "This document contains " << lineNumber << " lines of text" << endl << endl;

   print(wordPositions);

   inFile.close();

   return 0;
}

int findWordPosition(ifstream &inFile, multimap<string, pair<int, int> > &wordPositions) {
   int lineNumber = 0, wordPosition = 0;
   string line = "";

   while(!inFile.eof()) {
      lineNumber++;

      // Gets the current line from the file
      getline(inFile, line);
      istringstream iss(line);
      string word = "";

      while(!iss.eof()) {
         // Tracks the position of a given word in a line
         wordPosition++;
         iss >> word;
         
         replaceAll(word, ".", "");   
         replaceAll(word, ",", "");
         replaceAll(word, "?", "");
         replaceAll(word, "!", "");
        
         wordPositions.insert(make_pair(word, make_pair(lineNumber, wordPosition)));
      }
      wordPosition = 0;
   }

   return lineNumber;
}

// Loops through the map and for every word in the map, prints the corresponding position.
void print(const multimap<string, pair<int,int> > &wordPositions) {
   for(auto it1 = wordPositions.cbegin(), it2 = it1; it1 != wordPositions.cend(); it1 = it2) {
      unsigned int occurence = wordPositions.count(it1->first);
      cout << "\"" << it1->first << "\" occurs " << occurence << " times, and is found on: \n";

      for(; it2 != wordPositions.cend() && it2->first == it1->first; it2++) {
         auto [lineNumber, wordPosition] = it2->second;
         cout << "\t line " << lineNumber << ", position " << wordPosition << "\n\n";
      }
   }
}

string replaceAll(string &originalString, string stringToBeReplaced, string replacementString) {
   size_t pos;
   string str = "";

   while( (pos = originalString.find(stringToBeReplaced)) != std::string::npos) {
      originalString.replace(pos, 1, replacementString);
   }
   return originalString;
}
