


// Add any #includes for C++ libraries here.
// We have already included iostream as an example.
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>

// This #include adds all the function declarations (a.k.a. prototypes) from the
// reviews.h file, which means the compiler knows about them when it is compiling
// the main function below (e.g. it can verify the parameter types and return types
// of the function declarations match the way those functions are used in main() ).
// However, the #include does not add the actual code for the functions, which is
// in reviews.cpp. This means you need to compile with a g++ command including both
// .cpp source files. For this project, we will being using some features from C++11,
// which requires an additional flag. Compile with this command:
//     g++ --std=c++11 evaluateReviews.cpp reviews.cpp -o evaluateReviews
#include "reviews.h"

using namespace std;

const double SCORE_LIMIT_TRUTHFUL = 3;
const double SCORE_LIMIT_DECEPTIVE = -3;


int main(){
//make in input stream for keywordWeights.txt
ifstream fin("keywordWeights.txt");

//make sure that the file opened correctly and if it didn't end the program
if(!fin.is_open()) {
    cout << "Error: keywordWeights.txt could not be opened." << endl;
    return 1;
}
//make vectors to store the information from keywordWeights
vector<string> words;
vector<double> nums;
//use the previously created function to put information into the vectors
readKeywordWeights(fin,words,nums);

//make a variable to store the highscore
double Hscore = 0;
//make a variable to store the highscore's index
int Highindex = 0;
//make a variable to store the lowscore
double Lscore = 0;
//make a variable to store the lowscore's index
int Lowindex = 0;
//make a variable to count how many reviews there are
int count = 0;
//make a variable for the number of reviews that are truthful
int truth = 0;
//make a variable for the number of reviews that are deceptive
int decept = 0;
//make a variable for the number of reviews that are uncategrized
int uncategorized = 0;
//open the output stream for the report.txt file
ofstream vin("report.txt");
//write the title into report.txt
vin << "review score category \n";


//loop until 100 to ensure that if there are 100 reviews we can get to all of them
for (int i = 0; i < 100; i++) {
    //open an input stream for the each iteration with a new review file each time using the makeReviewFilename function
    ifstream zin(makeReviewFilename(i));
    //check if it opened correctly and if it did not then end the loop
    if(!zin.is_open()) {
        
        break;
    }
    //add 1 to the count
    count++;
    //make a new empty vector
    vector<string> file;
    //read in the data from the input stream to the new vector
    readReview(zin,file);
    //make the variables for score and category
    double score;
    string category;
    //set score equal to the sum of the wordWeights by using the reviewScore function
    score = reviewScore(file,words,nums);

    //check if the current score is greater than the highest score
    if (score > Hscore) {
        //if it is higher, then set the highscore to the current score and the highscore index to the index of the current score
        Hscore = score;
        Highindex = i;
    }
    //check if the current score is lower than the lowest score
    if (score < Lscore) {
        //if it is lower, then set the lowscore to the current score and the lowscore index to the index of the current score
        Lscore = score;
        Lowindex = i;
    }
    
    //if the score is greater than 3
    if (score > 3.0) {
        //set category to truthful and increase truth by 1
        category = "truthful";
        truth++;
    }
    //if the score is less than -3
    else if (score < -3.0) {
        //set category to deceptive and increase decept by 1
        category = "deceptive";
        decept++;
    }
    //else set category to uncategorized and increase uncategorized by 1
    else {
        category = "uncategorized";
        uncategorized++;
    }
    //write the current index, score, and category to report.txt
    vin << i << " " << score << " " << category << " \n";
    
}

//skip a line
vin << "\n";
//print out the following information using the variables storing that information
vin << "Number of reviews: " << count << "\n";
vin << "Number of truthful reviews: " << truth << "\n";
vin << "Number of deceptive reviews: " << decept << "\n";
vin << "Number of uncategorized reviews: " << uncategorized << "\n";
vin << "\n";
vin << "Review with highest score: " << Highindex << "\n";
vin << "Review with lowest score: " << Lowindex << "\n";
    // TODO: implement the main program

}



