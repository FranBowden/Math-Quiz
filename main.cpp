#include <iostream>
#include <string>
#include <time.h>
using namespace std;

//Declared functions
int displayMenu();
int randomNum(int min, int max);
int displayProblem(int level);
int isCorrect(int total, int score, int attempt, int answer);
int validate();
char decideOperation();
char grading(int score);
void displayFinalResults(int score, char grade);
void logMessage(string msg);

int main() {
    char replay; //declare replay variable
    do{ //do while loop - must run at least once
        int score = 0; //initialising score
        int attempt = 0; //initialising attempt
        int level = displayMenu(); //level stores the return int of displayMenu
        for(int i = 0; i < 10; i++) { //for loop to ask 10 questions
            cout << "Q" << i + 1<< ") "; //couts what question you are on before question is displayed
            int total = displayProblem(level); //displayProblem depending on level and store the returning value in total
            int answer = validate(); //gets user input and validates it
            score = isCorrect(total, score, attempt, answer); //score stores the returning scores the user as gotten
        }
        char grade = grading(score); //stores the grade in a char
        displayFinalResults(score, grade); //display the score after 10 rounds
        logMessage("Press (Y) to play again or enter any other input to quit"); //asks user to play again or quit
        cin >> replay; //gets user input
        replay = toupper(replay); //converts user input to uppercase
    }while(replay == 'Y'); //if user input is equal to Y, repeat the program
    return 0; //end program
}

//Defining Functions
void logMessage(string msg) { //function to store messages that output to the console
    cout << msg << endl;
}

int displayMenu() { //function to display the menu to the user
    logMessage("DIFFICULTY LEVEL\n1. Easy\n2. Moderate\n3. Advanced"); //gets user to enter a difficulty
    int level = validate(); //gets validated user answer stored in level
    while(level > 3) { //while level is over 3
        logMessage("Try again"); //ask user again
        level = validate(); //get validated answer and store in level
    }
    return level;
}

int randomNum(int min, int max) { //function for random number generator
    return rand() % max + min; //creates random number within range of min and max, returns the value
}

char decideOperation() {
    return "+-*"[rand() % 3]; //generate random operation
}

int displayProblem(int level) {
    int n1, n2;
    srand((unsigned) time(NULL));//set random seed
    char op = decideOperation(); //random operation assigned to op
    switch(level) { //switch statement based on what level you chose during the display menu
        case 1: //easy then generate numbers that are 1 digit
            n1 = randomNum(0, 9); //assigned to number 1
            n2 = randomNum(0, 9); //assigned to number 2
            break;
        case 2: //moderate then generate number that are 2 digits
            n1 = randomNum(10, 89);
            n2 = randomNum(10, 89);
            break;
        case 3: //advanced then generate numbers that are 4 digits
            n1 = randomNum(1000, 8999);
            n2 = randomNum(1000, 8999);
            break;
    }
   
    cout << n1 << " " << op << " " << n2 << " = "; //outputs the math question
    
    switch(op) { //switch statement for operation
        case '+': // if char is  +
            return n1 + n2; //add number 1 & number 2 & return total
        case '-':
            return n1 - n2;//subtract number 1 & number 2 & return total
        case '*':
            return n1 * n2; //multiply n1 and n2
        default:
            return 0;
    }
}

int isCorrect(int total, int score, int attempt, int answer) { //checks for correct answer
    if (attempt == 0 && answer == total){ //if your attempt is 0 (first attempt), and equal to the total
        score += 10; //add 10 points
        logMessage("Correct! +10 points"); //outputs 10 points
    }
    while (answer != total && attempt == 0) { //while answer does not equal total and attempt is 0
        logMessage("Incorrect, last try!"); //allow one more chance
        answer = validate(); //ask for user input again
        attempt++; //increase attempt
        if(attempt == 1 && answer == total) { //if attempt is equal to 1 & equal to the total (if user gets it correct during your second attempt)
            score += 5; //gain 5 points
            logMessage("Correct! +5 points"); //couts 5 points
        }else{ //if user gets answer wrong again,
            logMessage("Incorrect! 0 points"); //no points
        }
    }
    return score; //return the score
}

int validate() { //function to validate user input
    int input; //get input
    cin >> input; //get user input
      while(cin.fail() || cin.peek() != '\n') { //if user didnt enter number or did not end with enter button
          cout << "Please enter a valid number" << endl; //asks for input
          cin.clear(); //clear error flag
          cin.ignore(INT_MAX, '\n'); //ignore previous input
          cin >> input; //get user input again
      }
    return input; //return input
}

char grading(int score) { //function to give a grade based on the score achieved
    int scores = score / 10; //divide by 10, rounds score down to 1 - 10 for the case
    char grade; //Creating a grading system
    switch(scores) { //switch statement to grade score
        case 0:
        case 1:
            grade = 'F'; //Gives grade if less than 20
            break; //break
        case 2:
        case 3:
            grade = 'E'; //Gives grade E if less than 40 etc
            break;
        case 4:
            grade = 'D';
            break;
        case 5:
            grade = 'C';
            break;
        case 6:
        case 7:
            grade = 'B';
            break;
        case 8:
        case 9:
        case 10:
            grade = 'A';
            break;
    }
    return grade; //return grade
}

void displayFinalResults(int score, char grade) {
    cout << "You achieved a total score of: " << score << " out of 100\nGRADE: " << grade << endl; //outputs the total score
}
