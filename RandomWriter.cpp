/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */


#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "vector.h"
#include "map.h"
#include "strlib.h"
#include "tokenscanner.h" 
#include <algorithm> 
#include "random.h"

using namespace std;
string text; //text we read will be stored here 
Map<string,Vector<char>> seeds; //all seeds with its following characters.
Vector<string> allSeeds; //only seeds with duplicates to choose the initial seed.
int order; //markov order 
string curSeed; //current seed
const int MAX_CHAR = 2000; //constant for character limit

void getSeeds(); //gets seeds
void readText(ifstream &input); //reads texts
void getInitialSeed(); //gets the initial seed
bool compareFunction (string a,string b) {return a<b;} //compares strings, using it to sort strings alphabetically, so we can find initial seed easily.
void generateText(); //generates random text
int main() {
    // [TODO: fill with your code]
	ifstream input;
	while (true) {
		cout << "Enter name: ";
		string s = getLine();
		input.open(s.c_str());
		if (!input.fail()) break;
		cout << "Couldn't open file, try again!" << endl;
		input.clear();
	}
	while(true) {
		cout<< "Enter markov order, from 1 to 10: ";
		order = getInteger();
		if(order >=1 && order <=10){
			break;
		}
		cout<< "Please enter intereger form 0 to 10!" << endl;
	}
	readText(input);
	getSeeds();
	getInitialSeed();
	generateText();
	return 0;
}

//reads text line by line and saves in string text.
void readText(ifstream &input){
	TokenScanner scanner;
	scanner.setInput(input);
	while(scanner.hasMoreTokens()){
		text += scanner.nextToken();
	}
	

}

//iterates over text based on markov order, saves each string in map key and following character in value vector.
void getSeeds(){
	for(int i = 0; i<text.length()-order; i++){
		string seed = text.substr(i,order);
		allSeeds.add(seed);
		Vector<char> nextChars;
		char c = text[i+order];
		if(!seeds.containsKey(seed)){
			nextChars.add(c);
			seeds.put(seed,nextChars);
		} else {
			nextChars = seeds[seed];
			nextChars.add(c);
			seeds.put(seed,nextChars);
		}
		
	}
	
}

//gets initial seed, first it sorts the seeds alphabetically, E.G if we have {qwe' ty' zxc' ty' qwe' zxc} after sorting it will be {qwe,qwe,zxc,zxc,ty,ty}.
//saves the string which has the biggest amount of occurances.
void getInitialSeed(){
	sort(allSeeds.begin(),allSeeds.end(),compareFunction);
	int count = 1;
	int tmpCount = 1;
	string tmpCur;
	for(int i = 0; i <allSeeds.size()-1; i++){
		tmpCur = allSeeds[i];
		string nextC = allSeeds[i+1];
		if(tmpCur == nextC){
			tmpCount++;
		} else {
			if(tmpCount>count){
				curSeed = tmpCur;
				count = tmpCount;
			}
			tmpCount = 1;
		}
		
	}
	
}


//simple algorithm to generate new text randomly, chooses next char randomly, erases first letter from current seed, and adds the new random character at the end.
void generateText(){
	string newText = curSeed;
	int tmpSize = curSeed.size();
	for(int i = 0; i < MAX_CHAR - tmpSize ; i++){
		Vector<char> nextChars = seeds[curSeed];
		int rand = randomInteger(0,nextChars.size()-1);
		char c = nextChars.get(rand);
		newText+=c;
		curSeed.erase(0,1);
		curSeed+=c;
	}
	cout<<newText<<endl;
	
}






