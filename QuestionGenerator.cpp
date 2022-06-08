/*
*****************************************************************************************************************
QUESTION GENERATOR BETA V.1.3
DEVELOPER: Spencer
DATE: 20220606
PURPOSE: Generate questions and compare to answer sheet provided by user. The user can decide the following:
How many questions to go over, random generatiom, linear generation, and starting point for linear generation.
This program is a multi-use with branching logic. The user can effectively use the branching logic to review targetted
questions or use the randomizer to do a more general review session.

INSTRUCTION FOR USE:

1) Make two .txt documents in a folder on your computer, you will need the file path for these. One will be for questions and the other for answers.

2) Input the questions in a questions document and the answers in an answer document (The program reads these line by line so it is important that
the first line of the question document matches the first line of the answer document. I suggest opening both .txt files and putting the answer in
the second file as you are making the questions in the first one side by side

3) Go down to the line 68 and 69 and change the file path.

It is the files formatted likeso:

questions.open(R"()", ios::in);
answers.open(R"()", ios::in);

It reads a Raw string formatted like this R"()" Put the file path inside the parenthesis. You can do this by
going to the properties of the text file and copying it in. You might have to add the name of the file and .txt yourself after you copy the file destination

******************************************************************************************************************
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;



int main() {


	ifstream questions; // Initializing input file variable for questions
	ifstream answers; // Initializing input file variable for answers

	// String variables used for input and formatting input file string
	string data = "";
	string data2 = "";
	string line = "";
	string line2 = "";
	string useranswer = "";

	bool loopcheck = true; // Logic control for entry and exit of while loop. Used for propper data input control

	//Integer variables
	int count1 = 0;
	int count2 = 0;
	int usercount = 0;
	int wrong = 0;
	int userstart = 0;

	float grade = 0.0;
	float correct = 0.0;
	float sum = 0.0;
	
	vector<string> question; //Vector that holds questions from question text document
	vector<string> answer; //Vector that holds answers from answer document
	vector<int> shufflepos;//Vector used to aid in shuffle. This vector is solely used as an index copier of the question vector. 

	questions.open(R"(C:\Users\jspen\OneDrive\Documents\Visual Studio 2017\Flashcards\question.txt)", ios::in); // File input for questions
	answers.open(R"(C:\Users\jspen\OneDrive\Documents\Visual Studio 2017\Flashcards\answer.txt)", ios::in); // File input for answers

	if (questions.is_open() == false) { // File open integrity check
		cerr << "Could not open file!\n";
		return 1;
	}

	while (getline(questions, line)) { // Basic reading loop for an input file. Makes a new vector every line that cycles through.
		question.push_back(line);
		shufflepos.push_back(count1); // Tracking everytime an index for question vector goes up by one. This is important later in program for shuffle.
		count1++;
	}
	while (getline(answers, line2)) { //Reading loop for answers.
		answer.push_back(line2);
		count2++;
	}

	int questionsize = question.size(); //Gathering size of vectors to use in for loop so we know when to end.
	int answersize = answer.size();

	while (loopcheck == true){ // Beginning branch logic for user input to customize question generation experience.
		cout << "How many questions would you like to go over? There are a total of " << count1 << endl;
		cin >> usercount;

		if (usercount <= count1) { // Data validation check
			loopcheck = false;
		}
		else {
			cout << "You enter a data value that did not make sense...try again\n";
		}
	}
	// Shuffle function
	unsigned seed = std::chrono::system_clock::now()
		.time_since_epoch()
		.count();
	shuffle(shufflepos.begin(), shufflepos.end(), std::default_random_engine(seed)); //Third vector tracked index values on question vector. Shuffling this will mix up the indexes called upon later to get a random value.

	loopcheck = true;

	while (loopcheck == true) {
		cout << "Would you like to randomly generate the flash cards or go in order? type 'random' for random and 'order' for in order" << endl; //User can chose to receive random question or targetted questions.

		cin >> useranswer;
		if (useranswer == "random") {


			for (int i = 0; i < usercount; i++) {



				cout << endl << question.at(shufflepos.at(i)) << endl; // Using third vector shuffled index locations as an index for question and answer vectors.
				ws(cin);
				getline(cin, useranswer);

				if (useranswer == answer.at(shufflepos.at(i))) { 
					cout << "You got it correct! \n";
					correct++;
					sum++;
				}
				else {
					cout << "INCORRECT\n The correct answer was : " << answer.at(shufflepos.at(i)); // Gives correct answer if user gives wrong answer.
					wrong++;
					sum++;
				}
			} loopcheck = false;
		}
		else if (useranswer == "order") { //Indicates user wants to go in order from top to bottom of their question document
			cout << "Would you like to set a starting number or start from the very beginning? Type 'begin' to start from the beginning or 'point' to start from at your desired index in the question set\n";
			cin >> useranswer; // User decides to start from the beginning or a set point. Enables user to practice recent questions without shuffling them. 
			if (useranswer == "begin") {
				for (int i = 0; i < usercount; i++) {



					cout << endl << question.at(i) << endl;
					ws(cin);
					getline(cin, useranswer);

					if (useranswer == answer.at(i)) {
						cout << "You got it correct! \n";
						correct++;
						sum++;
					}
					else {
						cout << "INCORRECT\n The correct answer was : " << answer.at(i);
						wrong++;
						sum++;
					}
				} loopcheck = false;

			}
			else if (useranswer == "point") {
				cout << "What question do you wish to begin at? Give a numeric value...\n";
				cin >> userstart;

				for (int i = userstart; i < (userstart + usercount); i++) {



					cout << endl << question.at(i) << endl;
					ws(cin);
					getline(cin, useranswer);

					if (useranswer == answer.at(i)) {
						cout << "You got it correct! \n";
						correct++;
						sum++;
					}
					else {
						cout << "INCORRECT\n The correct answer was : " << answer.at(i);
						wrong++;
						sum++;
					}
				} loopcheck = false;

			}
		}
		else {
			cout << "We did not receive a proper command... please review the options carefully and try again\n";
			loopcheck = true;
		}

	}
	questions.close(); //Document closing
	answers.close();

	grade = (correct / sum) * 100;
	
	cout << "\nQuestion set complete\nYou answered: \n" << correct << " Correct \n" << wrong << " Wrong\n"<<grade<<" % accy\n"; // Incremented values in the loops to give user idea of performance at end.


	return 0;
}