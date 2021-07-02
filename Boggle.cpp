/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
#include "random.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void drawBoard(Grid<char> &table);//draws empty board
void fillBoard(Vector<string> vec,Grid<char> &table);//fills board with characters accordingly
void humanTurn(Grid<char> table,Set<string>& words);//humans turn
bool checkHumanWord(Grid<char> table, string word, string res,Set<double>& tmpPoints);//checks word entered by human
void checkThis(Grid<char>table, int row, int col, string res,string word,int& checker,Set<double> points,Set<double>& tmpPoints);//function to iterate over the graph for human player
void robotTurn(Grid<char> table,Set<string>& words); //computers turn
void checkThisRobot(Grid<char>table, int row, int col, Set<string>& words, string res,Set<double>points); //finds all leftover words for computer.
void playGame(); //main function which combines eveyrything and puts it in a loop.

/* Main program */



int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();
	playGame(); 
	return 0;
}

//plays game, both normal version of boggle (4x4), and extension (5x5)
void playGame(){
	int checker = 0; //checker to see when player wants to end the game
	int r; //variables to determine the size of a boogle (5x5 or 4x4)
	int c;	//variables to determine the size of a boogle (5x5 or 4x4)
	while(true){
		while(true){ //asks player to decide which boogle he wants play
			string question = getLine("Do you want to play big boogle(5x5), instead of normal(4x4)?: ");
			if(question == "yes"){
				r = 5;
				c = 5;
				break;
			} else if(question =="no") {
				r = 4;
				c = 4;
				break;
			} else {
				cout<<"Please enter yes or no!!!"<<endl;
			}
		}
		Set<string> words; //contains all words which have been guessed.
		Grid<char> table(r,c); //grid of appropriate size.
		drawBoard(table); 
		humanTurn(table,words);
		robotTurn(table,words);	
		cout<<"Game is finished!"<<endl;
		while(true){ //after game is over asks player if he wants to play again.
			string question = getLine("Do you want to play again?: ");
			if(question == "yes"){
				break;
			} else if (question == "no"){
				checker++;
				break;	
			} else {
				cout<<"Please enter yes or no!!!"<<endl;
			}
		}
		if(checker > 0){
			cout<<"Ok bye."<<endl;
			break;
		}
	}	
}
Set<string> test;
//iterates over all possible word combination for computers turn.
void checkThisRobot(Grid<char>table, int col, int row, Set<string>& words, string res,Set<double>points){
	Lexicon();
	Lexicon lex("EnglishWords.dat");
	if(res.size()>3){ //only checks words which have length of 4 or more, are contained in a lexicon, is not already gueesed, and the point and word have the same size.
		if(lex.contains(res)){ 
			if(!words.contains(res)){
				if(points.size()==res.size()){
				words.add(res);
				recordWordForPlayer(res, COMPUTER);
				}
			} 
		}  
	}
	if(res.size()!=points.size()){ //if current results size and points size are not the same, it means we used the same num/col more than once, which is not allowed, so we return back.
		return;
	}

	if(res.size()==table.numCols()*table.numRows()){ //if word = col*row, it means its the longest possible combination of a word and its still not found, it means we have to go back.
			return;
	} else {
		cout<<res<<endl; //uncomment this line to see the process of generating words(veraprit ver vipove bagi aq, ramdenjerme amowmebs erti da igives... magito andomebs cota did xans)
		double xCol = col * 1; //double variables to save the location of characters(E.G if char is on 1,1 grid, it saves it as 1.1
		double xRow = row / 10.0; // and so on. 2,2 = 2.2 || 0,1 = 0.1 || 4,0 = 4.0 || 0,0 = 0.
		double point = xCol + xRow;
		points.add(point);
		char ch = table.get(col,row);
		res = res + ch; //this is the word we mutate on every reccursive step, by adding a new character from grid.
		if(!lex.containsPrefix(res)){ //if no word starts from lexicon by our current string, we go back.
			return;
		}
		//recurses over all possible iteration, accoring to the row and col( E.G if position is 0,0 we can only go to the right, down and down+right(diagonally).
		//if its in the middle, we can go on all 8 possible directions and so on.
		if(col>0 && row > 0 && col < table.numCols()-1 && row < table.numRows()-1){
			checkThisRobot(table, col-1,row-1, words,res,points);
			checkThisRobot(table, col-1,row-0, words,res,points);
			checkThisRobot(table, col-0,row-1, words,res,points);
			checkThisRobot(table, col+1,row+1, words,res,points);
			checkThisRobot(table, col+1,row+0, words,res,points);
			checkThisRobot(table, col+0,row+1, words,res,points);
			checkThisRobot(table, col+1,row-1, words,res,points);
			checkThisRobot(table, col-1,row+1, words,res,points);
		}else if(col==0 && row ==0){
			checkThisRobot(table, col+1,row+1, words,res,points);
			checkThisRobot(table, col+1,row+0, words,res,points);
			checkThisRobot(table, col+0,row+1, words,res,points);
		}else if(col==0 && row > 0 && row < table.numRows()-1){
			checkThisRobot(table, col-0,row-1, words,res,points);
			checkThisRobot(table, col+1,row+1, words,res,points);
			checkThisRobot(table, col+1,row+0, words,res,points);
			checkThisRobot(table, col+0,row+1, words,res,points);
			checkThisRobot(table, col+1,row-1, words,res,points);
		}else if(col > 0 && row == 0 && col < table.numCols()-1){
			checkThisRobot(table, col-1,row-0, words,res,points);
			checkThisRobot(table, col+1,row+1, words,res,points);
			checkThisRobot(table, col+1,row+0, words,res,points);
			checkThisRobot(table, col+0,row+1, words,res,points);
			checkThisRobot(table, col-1,row+1, words,res,points);
		}else if(col==table.numCols()-1 && row == table.numRows()-1){
			checkThisRobot(table, col-1,row-1, words,res,points);
			checkThisRobot(table, col-1,row-0, words,res,points);
			checkThisRobot(table, col-0,row-1, words,res,points);

		}else if(col==table.numCols()-1 && row < table.numRows()-1 && row > 0){
			checkThisRobot(table, col-1,row-1, words,res,points);
			checkThisRobot(table, col-1,row-0, words,res,points);
			checkThisRobot(table, col-0,row-1, words,res,points);
			checkThisRobot(table, col+0,row+1, words,res,points);
			checkThisRobot(table, col-1,row+1, words,res,points);

		}else if(col<table.numCols()-1 && row == table.numRows()-1 && col > 0){
			checkThisRobot(table, col-1,row-1, words,res,points);
			checkThisRobot(table, col-1,row-0, words,res,points);
			checkThisRobot(table, col-0,row-1, words,res,points);
			checkThisRobot(table, col+1,row+0, words,res,points);
			checkThisRobot(table, col+1,row-1, words,res,points);		
		}else if(col==0 && row == table.numRows()-1){
			checkThisRobot(table, col+1,row-1, words,res,points);
			checkThisRobot(table, col+1,row-0, words,res,points);
			checkThisRobot(table, col-0,row-1, words,res,points);
		}else if(col==table.numCols()-1 && row == 0){
			checkThisRobot(table, col-1,row+1, words,res,points);
			checkThisRobot(table, col-1,row-0, words,res,points);
			checkThisRobot(table, col-0,row+1, words,res,points);
		}
	}
}
//iterates for robot on grid
void robotTurn(Grid<char> table,Set<string>& words){
	string res ="";
	Set<double> points; //saves points for robots guessed words, helps us to make sure we only use a character once on a grid.
	//E.G if it makes a word by going from positions (1,2 > 1,3 > 1,2) the set of points will have only 1.2 and 1.3, we compare it to string size on every iteration
	//so if size of string is bigger than size of points, it means we did a wrong thing, since its only allowed to use a single point once on grid.
	for(int i = 0; i < table.numCols(); i++){
		for(int j = 0; j < table.numRows(); j++){ //iterates on grid.
			checkThisRobot(table,i,j,words,res,points);				
		}
	}	
}

//checks if word entered by human is findable or not.
void checkThis(Grid<char>table, int col, int row, string res,string word,int& checker,Set<double> points,Set<double>& tmpPoints){
	if(res.size()==word.size()){ //if current string size equals size of the word entered by human.
		if(word==res && points.size()==word.size()){ //if the words are the same, and points size(Exlpained above what points do) equals word size.
			checker++; //increases checker by 1, (by default its 0),
			foreach(double point in points){ //copies points set in tmpPoints(which we use to higlight the word later);
				tmpPoints.add(point);
			}
			return;
		}
	} else {
		if(checker>0){ //if checker is >0, it means we already found the word, no need to continue, thus we return from this void.
			return;
		}
		double xCol = col * 1; //explained above what those do.
		double xRow = row / 10.0;
		double point = xCol + xRow;
		points.add(point);
		char ch = table.get(col,row);
		res = res + ch;
		if(!startsWith(word,res)){ //if our current string is not the prefix of word entered by human, we go back and try another combination.
			return;
		}
		//checks every possible combination accorind to grid col/row, explained above.
		if(col>0 && row > 0 && col < table.numCols()-1 && row < table.numRows()-1){
			checkThis(table, col-1,row-1, res ,word,checker,points, tmpPoints);
			checkThis(table, col-1,row-0, res ,word,checker,points, tmpPoints);
			checkThis(table, col-0,row-1, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row+1, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row+0, res ,word,checker,points, tmpPoints);
			checkThis(table, col+0,row+1, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row-1, res ,word,checker,points, tmpPoints);
			checkThis(table, col-1,row+1, res ,word,checker,points, tmpPoints);
		}
		if(col==0 && row ==0){
			checkThis(table, col+1,row+1, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row+0, res ,word,checker,points, tmpPoints);
			checkThis(table, col+0,row+1, res ,word,checker,points, tmpPoints);
		}
		if(col==0 && row > 0 && row < table.numRows()-1){
			checkThis(table, col-0,row-1, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row+1, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row+0, res ,word,checker,points, tmpPoints);
			checkThis(table, col+0,row+1, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row-1, res ,word,checker,points, tmpPoints);
		}
		if(col > 0 && row == 0 && col < table.numCols()-1){
			checkThis(table, col-1,row-0, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row+1, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row+0, res ,word,checker,points, tmpPoints);
			checkThis(table, col+0,row+1, res ,word,checker,points, tmpPoints);
			checkThis(table, col-1,row+1, res ,word,checker,points, tmpPoints);
		}
		if(col==table.numCols()-1 && row == table.numRows()-1){
			checkThis(table, col-1,row-1, res ,word,checker,points, tmpPoints);
			checkThis(table, col-1,row-0, res ,word,checker,points, tmpPoints);
			checkThis(table, col-0,row-1, res ,word,checker,points, tmpPoints);

		}
		if(col==table.numCols()-1 && row < table.numRows()-1 && row > 0){
			checkThis(table, col-1,row-1, res ,word,checker,points, tmpPoints);
			checkThis(table, col-1,row-0, res ,word,checker,points, tmpPoints);
			checkThis(table, col-0,row-1, res ,word,checker,points, tmpPoints);
			checkThis(table, col+0,row+1, res ,word,checker,points, tmpPoints);
			checkThis(table, col-1,row+1, res ,word,checker,points, tmpPoints);

		}
		if(col<table.numCols()-1 && row == table.numRows()-1 && col > 0){
			checkThis(table, col-1,row-1, res ,word,checker,points, tmpPoints);
			checkThis(table, col-1,row-0, res ,word,checker,points, tmpPoints);
			checkThis(table, col-0,row-1, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row+0, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row-1, res ,word,checker,points, tmpPoints);		
		}
		if(col==0 && row == table.numRows()-1){
			checkThis(table, col+1,row-1, res ,word,checker,points, tmpPoints);
			checkThis(table, col+1,row-0, res ,word,checker,points, tmpPoints);
			checkThis(table, col-0,row-1, res ,word,checker,points, tmpPoints);
		}
		if(col==table.numCols()-1 && row == 0){
			checkThis(table, col-1,row+1, res ,word,checker,points, tmpPoints);
			checkThis(table, col-1,row-0, res ,word,checker,points, tmpPoints);
			checkThis(table, col-0,row+1, res ,word,checker,points, tmpPoints);
		}
	}
}

//bool which returns true if entered word is possible to form.
bool checkHumanWord(Grid<char> table, string word, string res,Set<double>& tmpPoints){
	Lexicon();
	Lexicon lex("EnglishWords.dat");
	Set<double> points; //same as computer points, saves col/rows as doubles.
	int checker = 0; //we use it in checkThis function, if checker > 0, we found the word.
	 if(!lex.contains(word)){ //if entered word is not contained in lexicon, we automatically return false.
		return false;
	}

	//iterates over grid, if checker goes above 0, we found the word and we return true.
	for(int i = 0; i < table.numCols(); i++){
		for(int j = 0; j < table.numRows(); j++){
			checkThis(table, i,j,res,word,checker,points, tmpPoints);
			if(checker>0){
				return true;
			}		
		}
	}
	return false;
}
void humanTurn(Grid<char> table,Set<string>& words){
	Set<double> tmpPoints; //if word entered by human is findable, we save the path here temporarily, to highlight it after.
	while(true){ //simple loop to make player enter word until it enters empty string(presses just return).
		cout<<"Press enter to finish your guessing."<<endl;
		string word = getLine("Please enter word: ");
		if(word ==""){
			break;
		}
		word = toUpperCase(word);
		if(word.size()>3){ //word size should be at least 4 according to rules.
			string res ="";
			if(checkHumanWord(table,word,res,tmpPoints)){
				if(!words.contains(word)){ //if word is not already guessed, we record it for player and add word to guessed words set.
					words.add(word);
					recordWordForPlayer(word, HUMAN);
				} else {
					cout<<"This word was already guessed, please try another one!"<<endl;
				}
			} else { //if its imposible to form this word, we print it.
				cout<<"You can't make that word!"<<endl;
			}
		} else {
			cout<<"Word should be at least 4 characters long!"<<endl;
		}
		int col;
		int row;
		//we run over our saved points, transfrom them from double to int accoringly, then higlight cubes.
		foreach(double point in tmpPoints){
			int converse = point *10;
			col = converse/10;
			row = converse%10;
			highlightCube(col, row, true);
		}
		pause(500);
		//we pause for a while, then unhiglight it. 
		foreach(double point in tmpPoints){
			int converse = point *10;
			col = converse/10;
			row = converse%10;
			highlightCube(col, row, false);
		}
		tmpPoints.clear(); //clearing tmpPoints for future use.
	}
	cout<<"Ok now robot will guess words you'v missed."<<endl;
}

//function to draw board, either randomly, or manually by player, depending on what he chooses to do.
void drawBoard(Grid<char> &table){
	Vector<string> vec;
	if(table.numCols()*table.numRows()==25){ //if player wants to play big boggle.
		foreach(string str in BIG_BOGGLE_CUBES){
			vec.add(str);
		}

	}
	if(table.numCols()*table.numRows()==16){ //if player wants to play normal boggle
		foreach(string str in STANDARD_CUBES){
			vec.add(str);
		}
	}
	for(int i = 0; i < vec.size(); i++){
		int r = randomInteger(i,vec.size()-1);
		string tmp = vec[i];
		vec.set(i,vec[r]);
		vec.set(r,tmp);
	}
	drawBoard(table.numCols(),table.numRows()); //different drawBoard function from gboggle interface, draws empty board with sizes accorindgly.
	while(true){//simple loop to ask questions about the board, then configuring it.
		string question = getLine("Do you want to configure cubes by yourself?: ");
		if(question == "no"){
			cout<<"Ok nice! we'll fill it for you."<<endl;
			fillBoard(vec,table);	
			break;
		} else if(question =="yes") {
			cout<<"Ok enter sequence of characters you want to have."<<endl;
			string sequence;
			while(true){
				sequence = getLine("Type here: ");
				if(sequence.length()<vec.size()){
					cout<<"Length of sequence should be at least ";
					cout<<vec.size();
					cout<<" characters long!"<<endl;	
				} else {
					break;
				}
			}
			sequence = toUpperCase(sequence);
			int n = 0;
			//fills board accorind to user input
			for(int i = 0; i < table.numCols(); i++){
				for(int j = 0; j < table.numRows(); j++){
					char ch = sequence[n];
					n++;
					labelCube(i,j,ch);
					table.set(i,j,ch);
				}
			}
			break;

		} else {
			cout<<"Please enter yes or no!!!"<<endl;
		}	
	}
}

//fills board randomly.
void fillBoard(Vector<string> vec,Grid<char>&table){
	int n = 0;
	for(int i = 0; i < table.numCols(); i++){
		for(int j = 0; j < table.numRows(); j++){
			string cube = vec[n];
			n++;
			int rand = randomInteger(0,cube.size()-1);
			char ch = cube[rand];
			labelCube(i,j,ch);
			table.set(i,j,ch);
		}
	}	
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}


