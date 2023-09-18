
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <limits>
#include "Gamer.h"
#include "Manager.h"
#include "ReadWords.h"
using namespace std;

//READ FILE AND IMPORT DATA INTO VECTOR OF VECTORS WITH USER DATA AS ELEMENTS (ARGS: NAME OF THE FILE AND VECTOR TO OUTPUT DATA TO)
vector<vector<string>> readFiles(string filename, vector<vector<string>> dataUsers){
	ifstream f;
		f.open(filename);
		if(!f){
			cout << "File not found";
			exit(1);
		}
		else{
			bool reading = true;
			string n;
		    while (reading){
				if (!f.eof()){
					getline(f,n);
					stringstream ss(n);
					string element;
					vector<string> user;
					while (ss >> element){
					    	user.push_back(element); //CREATE VECTOR WITH PLAYER DATA
					    }

					dataUsers.push_back(user); //ADD VECTOR WITH PLAYER DATA TO VECTOR OF VECTORS
				}
				else{
					reading = false;
					f.close();
				}

		    }
		}
		return dataUsers;
}

//CREATES AND RETURNS A NEW GAMER WITH ARG: REGISTER NUMBER, WHEN THE REG. NO. INTRODUCED DOESNT CORRESPOND TO GAMER OR MANAGER
Gamer newGamer(string regNo){
	string firstName;
	string lastName;
	cout << "This register number does not correspond to an existing gamer or manager" << endl;
	cout << "Enter your details to register as gamer with RegNo: " << regNo << endl;
	cout << "Enter your first name:" << endl;
	cin >> firstName;
	cout << "Enter your last name: " << endl;
	cin >> lastName;
	string fullName = firstName + " " + lastName;
	Gamer g(fullName, stoi(regNo));
	ofstream o;
	o.open("gamers.txt",ios::app);
	o << endl << regNo << " " << firstName << " " << lastName;
	o.close();
	cout << "New gamer was created with name " <<fullName << " and reg No " << regNo << endl;
	return g;
}

//TAKES WORD,DIFFICULTY LEVEL, CURRENT PLAYER AND TIP FOR WORD AS ARGUMENT TO BE USED IN HANGMAN GAME AND ASSIGN A SCORE TO THE USER.
void guessWord(string word, string difficulty,Gamer g,string tip){

	cout << "Guess the following word: " << endl << endl;
	//create blank word that is updated if letter is guessed
	string blank;
	for(char const &c : word){
		string blankChar;
		if(!isalpha(c)) blankChar = c;
		else{blankChar= "_";}
		blank = blank+blankChar;
	}
	for(int i=0;i<blank.size();i++){
		cout << blank[i] << " ";
	}
	cout << endl << endl;
	vector<char> guesses;
	vector<char> misses;
	bool hangman = false;
	bool playing = true;
	while(playing){
		char letter = ' ';
		//shows tip for the player showing the word to guess as blank except for the charaters already guessed.
		cout << "TIP: ";
		string blankTip;
		for(int i=0;i<blank.size();i++){
			blankTip = blankTip + blank[i] + " ";
		}
		//replaces the word in the tip for the blank word
		string element;
		stringstream ss(tip);
		while(ss >> element){
			if(element == word) element = blankTip;
			cout << element << " ";
		}
		cout << endl;
		cout << "Enter a letter (a-z): " << endl;
		cin >> letter;
		//validate input
		while(cin.fail() || !isalpha(letter)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout << "This is not a valid letter . Enter another one: " << endl;
				cin >> letter;
		}
		bool guessed = false;
		if(guesses.size() !=0){
			for(int i=0;i<guesses.size();i++){
					if(letter == guesses[i]){
						cout << "Letter already guessed." << endl;
						guessed=true;
					}
			}
		}
		if(guessed) continue;
		bool missed = true;
		if(!guessed){
			guesses.push_back(letter);
			for(int i=0;i<word.size();i++){
					if(word[i] == letter){
						blank[i] = word[i];
						missed = false;
					}
				}

		}
		if(missed)misses.push_back(letter);
		for(int i=0;i<blank.size();i++){
				cout << blank[i] << " ";
			}
		cout << endl << endl;
		cout << "Guesses: ";
		for(int i=0;i<guesses.size();i++) cout << guesses[i] << "  ";
		cout << endl << endl;
		cout << "Misses: ";
		for(int i=0;i<misses.size();i++) cout << misses[i] << "  ";
		cout << endl << endl;
		float points = 0.0;
		//assigns points depending on the amount of missed guesses
		if(blank == word){
			if(misses.size()==0){points = 50.0;}
			if(misses.size()==1){points = 20.0;}
			if(misses.size()==2){points = 15.0;}
			if(misses.size()==3){points = 10.0;}
			if(misses.size()==4){points = 5.0;}
			if(misses.size()==5){points = 3.0;}
			cout <<"POINTS: " <<points << " " << difficulty << endl;
			g.addScore(points,difficulty);
			cout << "WORD FOUND!" << endl << endl;
			break;
		}
		//informs the user of the state of the hangman
		if(misses.size()==1){ cout << "Hangman has a head." << endl << endl;}
		if(misses.size()==2){cout << "Hangman has a head and a body." << endl << endl;}
		if(misses.size()==3){cout << "Hangman has a head, a body and an arm." << endl << endl;}
		if(misses.size()==4){cout << "Hangman has a head, a body and two arms." << endl << endl;}
		if(misses.size()==5){cout << "Hangman has a head, a body, two arms and a leg." << endl << endl;}
		if(misses.size()==6){
			cout << "Hangman has is complete." << endl << endl;
			hangman = true;
		}
		if(hangman){
		cout<< "GAME OVER!!!" << endl << endl;
		cout << "The word is " << word << endl;
		break;
		}
	}
}
//GETS LEVEL PARAMETERS FROM LEVEL PARAMETERS FILE AND STORES THEM IN A VECTOR OF VECTORS,
vector<vector<string>> getLevelParameters(){
	ifstream f;
	vector<vector<string>> levelData;
	f.open("levelParameters.txt");
	if(!f){
		cout << "File not found";
		exit(1);
	}

	else{
		string n;
		for(int i=0;i<3;i++){
				getline(f,n);
				stringstream ss(n);
				string element;
				vector<string> level;
				while (ss >> element){
						level.push_back(element);
					}

				levelData.push_back(level);
			}
		}
	f.close();
	return levelData;

}
//TAKES INPUT FOR LEVEL TO PLAY FROM USER  AND GETS THE WORD ACCORDING TO THE LEVEL AND CALLS GUESSWORD.
void playGame(string regNo,Gamer g){
	ReadWords r("mySample.txt");
	int level;
	cout << "Select level of difficulty:  " << endl << "1) easy" << endl << "2) medium" << endl << "3) hard" << endl;
	cin >> level;
	while(cin.fail() || level < 1 || level > 3) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "This is not a valid option . Enter another one: " << endl;
		cin >> level;
	}
	vector<vector<string>> levelData = getLevelParameters();
	string option;
	if(level == 1) option = "easy";
	if(level == 2) option = "medium";
	if(level == 3) option = "hard";
	if(option == levelData[0][0]){ r.getWords(stoi(levelData[0][1]), stoi(levelData[0][2])); string word = r.selectWord();r.getPhraseForWord(word);guessWord(word,"easy",g,r.getPhraseForWord(word));}
	if(option == levelData[1][0]){ r.getWords(stoi(levelData[1][1]), stoi(levelData[1][2]));string word = r.selectWord();r.getPhraseForWord(word);guessWord(word,"medium",g,r.getPhraseForWord(word));}
	if(option == levelData[2][0]){r.getWords(stoi(levelData[2][1]), stoi(levelData[2][2]));string word = r.selectWord();r.getPhraseForWord(word);guessWord(word,"hard",g,r.getPhraseForWord(word));}
}
//SHOWS PLAYER STATISTICS
void statistics(Gamer g){
	cout << "Your statistics:" << endl << endl;
	cout << g;
}
//METHOD TO SORT VECTOR FROM HIGHER TO LOWER BY VALUE
bool sortVector(pair<Gamer,float> &i, pair<Gamer,float> &j)
{ bool b;
if(i.second>j.second) b=true;
   return b;
}
//METHOD TO DISPLAY TOP TEN PLAYERS BY AVERAGE SCORE AND HIGHLIGHT WITH (CURRENT PLAYER) FOR THE CURRENTS PLAYER POSITION
void top_ten(string regNo, vector<Gamer> gamers){
	cout << "TOP 10 PLAYERS RANKED BY AVERAGE SCORE:" << endl << endl;
	vector<pair<Gamer,float>> playerTopScore;
	for(int i=0;i<gamers.size();i++){
		float score = gamers[i].AverageScore();
		int regNo = gamers[i].getRegNo();
		playerTopScore.push_back(make_pair(gamers[i],score));
	}

	sort(playerTopScore.begin(),playerTopScore.end(),sortVector);
	for (int i=1;i<=10;i++) {

		if((playerTopScore[i].first).getRegNo() == stoi(regNo)){
			cout << i << "-" << " (current player) "<<playerTopScore[i].first<< endl; }
		else{
			cout << i << "-" << playerTopScore[i].first<< endl;
		}
	}

}
//SETS ALL SCORES OF PLAYERS TO 0
void resetGame(vector<Gamer> g){
	for(int i=0;i<g.size();i++){
		g[i].updateAccumulativeScore("easy", 0);
		g[i].updateAccumulativeScore("medium", 0);
		g[i].updateAccumulativeScore("hard", 0);
	}
	cout << "The game has been reset. All players have 0 points." << endl << endl;
}
//TAKES INPUT FROM MANAGER TO CHANGE THE LEVEL PARAMETERS
void changeLevel(){
	int minE;
	int minM;
	int minH;
	int maxE;
	int maxM;
	int maxH;
	cout << "Enter MIN parameter for EASY level" << endl;
	cin>>  minE;
	cout << "Enter MAX parameter for EASY level" << endl << endl;
	cin>>  maxE;
	cout << "Enter MIN parameter for MEDIUM level" << endl;
	cin>>  minM;
	cout << "Enter MAX parameter for MEDIUM level" << endl << endl;
	cin>>  maxM;
	cout << "Enter MIN parameter for HARD level" << endl;
	cin>>  minH;
	cout << "Enter MAX parameter for HARD level" << endl << endl;
	cin>>  maxH;
	ofstream o;
	o.open("levelParameters.txt");
	o << "The level parameters are: Easy: " << minE << " " << maxE << endl << " Medium: " << " " << minM << " " << maxM << endl<< " Hard: " << " " << minH << " " << maxH;
}
//TAKES INPUT AND ADD NEW MANAGER
Manager addManager(int size){
	string firstname;
	string lastname;
	cout << "Enter new manager's first name:" << endl;
	cin >> firstname;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout << "Enter new manager's last name:" << endl;
	cin >> lastname;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	string name = firstname+" "+lastname;
	string regNo = "000" + to_string(size);

	Manager m(name, stoi(regNo));
	ofstream o;
	o.open("managers.txt",ios::app);
	o << endl <<regNo << " " << firstname << " " << lastname;
	o.close();
	cout << "The new manager is " << name << " with regNo " << regNo << endl;
	return m;
}

int main() {

	string gamersFile = "gamers.txt";
	string managersFile = "managers.txt";

	//VECTORS OF GAMERS AND MANAGERS INFORMATION IMPORTED FROM FILES
	vector<vector<string>> dataGamers;
	vector<vector<string>> dataManagers;
	dataGamers = readFiles(gamersFile,dataGamers);
	dataManagers = readFiles(managersFile,dataManagers);

	//IMPORTING GAMERS INTO VECTOR OF GAMER OBJECT
	vector<Gamer> gamers;
		for(int i=0;i<dataGamers.size();i++){

			string nameGamer = dataGamers[i][1] + " " +dataGamers[i][2];
			int regNoGamer = stoi(dataGamers[i][0]);
			Gamer g(nameGamer,regNoGamer);
			if (dataGamers[i].size() > 3) g.updateAccumulativeScore("easy",stof(dataGamers[i][3]));
			if (dataGamers[i].size() > 4) g.updateAccumulativeScore("medium",stof(dataGamers[i][4]));
			if (dataGamers[i].size() > 5) g.updateAccumulativeScore("hard",stof(dataGamers[i][5]));
			gamers.push_back(g);

		}

	vector<Manager> managers;
	//ADDING MYSELF AS MANAGER
	Manager me("Sofia Rodriguez",0000);
	managers.push_back(me);

	//IMPORTING MANAGERS INTO VECTOR OF MANAGER OBJECT
		for(int i=0;i<dataManagers.size();i++){
			string nameManager = dataManagers[i][1] + " " + dataManagers[i][2];
				Manager m(nameManager,stoi(dataManagers[i][0]));
				managers.push_back(m);
			}

	//LOOP FOR GAME OPTIONS
	//IDENTIFY TYPE OF USER (GAMER OR MANAGER) BY REG. NO
	bool running = true;
	while (running){
		int regNo;
		cout << "Enter your Registration number to see options or enter '1' to end program" << endl;
		cin >> regNo;
		while(cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "This is not a valid Reg No . Enter another one or enter '1' to end program:" << endl;
			cin >> regNo;
		}
		if(regNo == 1){
			cout << "Program terminated successfully";
			running = false;
			break;
		}


		//CHECKING IF REGNO ENTERED IS EXISTING GAMER OR MANAGER AND SHOW RESPECTIVE OPTIONS
		bool isGamer = false;
		bool isManager = false;

		for(int i = 0; i< managers.size();i++){
			if(regNo == managers[i].getRegNo()){
				isManager = true;

			bool b = true;
					while(b){
					cout << endl;
					cout << "MANAGERS MENU" << endl << endl;
					cout << "1. Reset Game" << endl;
					cout << "2. Change Game Levels" << endl;
					cout << "3. Add Another Manager" << endl;
					cout << "4. Exit Game" << endl << endl;
					cout << "Select option (1,2,3,4 or 5): " << endl << endl;
					int option;
					cin >> option;
					while(cin.fail() || option <1 ||option > 4) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(),'\n');
						cout << "This is not a valid option. Enter another option:" << endl;
						cin >> option;
					}
					string fileName;
					switch(option){
						case 1: resetGame(gamers); break;
						case 2: changeLevel(); break;
						case 3: managers.push_back(addManager(managers.size()));break;
						case 4: b = false;break;
						}
					}
			}
		}

		for(int j=0; j< gamers.size();j++){
			if(regNo == gamers[j].getRegNo()){
				isGamer = true;

				bool b = true;
				while(b){
				cout << endl;
				cout << "PLAYERS MENU" << endl << endl;
				cout << "1. Play Game" << endl;
				cout << "2. Your statistics" << endl;
				cout << "3. Display Top 10" << endl;
				cout << "4. Exit Game" << endl << endl;
				cout << "Select option (1,2,3 or 4): " << endl;
				int option;
				cin >> option;
				while(cin.fail() || option < 1 || option > 5) {
				    cin.clear();
				    cin.ignore(numeric_limits<streamsize>::max(),'\n');
				    cout << "This is not a valid option. Enter another option:" << endl;
				    cin >> option;
				}
				switch(option){
					case 1: playGame(to_string(regNo),gamers[j]);break;
					case 2: statistics(gamers[j]); break;
					case 3: top_ten(to_string(regNo),gamers); break;
					case 4: b = false;break;
				}


				}
			}
		}

		//IF ITS NEITHER MANAGER NOR GAMER, CREATE NEW GAMER AND SHOW OPTIONS
		if(!isGamer & !isManager){
			Gamer ng = newGamer(to_string(regNo));
			gamers.push_back(ng);

		}



	}
	return 0;
	}
