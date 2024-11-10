#include "SentimentClassifier.h"

#include <set>
//training function
void analysisT::training(DSString fileName) {
    ifstream input (fileName.c_str());

    if (!input.is_open()) {
        cout << "Error opening file" << '\n';
    }


    
    char* buffer = new char[1000];

    input.getline(buffer,1000);

    //parsing the file
    while(!input.eof()) {
        //will get line from each column until 1000 chars or until it reaches a ','
        input.getline(buffer, 1000, ',');

        if (strlen(buffer) == 0) {
            break;
        }

        //getting the postive value from the first char of the file
        bool isPositive = buffer[0] == '4';

        //discarding unneeded columns
        for(int i = 0; i < 4; i++) {
            input.getline(buffer, 1000, ',');
        }

        //reading our text tweet
        input.getline(buffer,1000);

        //our delimiters by using special characters
        char* token = strtok(buffer,"!,@#$%^&*()_+/-|{}[];:\"'?~.<> 1234567890\\");
        //loops through the words until there are no words left
        while(token != nullptr) {
          
            DSString word = token;
            //in case there are two special characters next to each other
            if(word.length() > 2) {
                word.toLower();
                //if word has never been seen before
                if(sentCount.find(word) == sentCount.end()) {
                    if(isPositive) {
                       
                        sentCount[word] = make_pair(1,0);
                    }
                    else {
                        sentCount[word] = make_pair(0,1);
                    }
                }
                //if we have seen the word before
                else {
                  if(isPositive) {
                      //adding the count
                      sentCount[word].first++;
                  }
                  else {
                      sentCount[word].second++;
                  }
                }
            }
            token = strtok(nullptr,"!,@#$%^&*()_+/-|{}[];:\"'?~.<> 1234567890\\");
        }
    }

    //iterating through the map
    for(pair<DSString,pair<int, int>> itr : sentCount) {
        int total = itr.second.first+itr.second.second;
     
        if(total > 6) {
            //probability of a work being positive based on appertiances
            double prob = (double)itr.second.first/total;
            // messing with probability
            if(prob > 0.6) {
                sentValueW[itr.first] = true;
            }
            else if(prob < 0.4) {
                sentValueW[itr.first] = false;
            }
        }
    }
}


//testing function
void analysisT::testing(DSString fileName) {
    ifstream input (fileName.c_str());

    if (!input.is_open()) {
        cout << "Error opening file" << '\n';
    }

    //creating a c-string buffer
    char* buffer = new char[1000];

    //discard header for file by reading in header
    //reading until 1000 char or until \n
    input.getline(buffer,1000);

    //parsing the file
    while(!input.eof()) {
        //will get line from each column until 1000 chars or until it reaches a ','
        input.getline(buffer, 1000, ',');
        if (strlen(buffer) == 0) {
            break;
        }
        //sorting id
        DSString id = buffer;

        //discarding unneeded columns
        for(int i = 0; i < 3; i++) {
            input.getline(buffer, 1000, ',');
        }

        //reading our text tweet
        input.getline(buffer,1000);

        //our delimiters by using special characters
        char* token = strtok(buffer,"!,@#$%^&*()_+/-|{}[];:\"'?~.<> 1234567890\\");

        //
        int netural = 0;

        while(token != nullptr) {
            //calling DDString and making a deep copy
            DSString word = token;
            //in case there are two special characters next to each other
            if(word.length() > 2) {
                word.toLower();
                //if word has been seen before
                if(sentValueW.find(word) != sentValueW.end()) {
                    if(sentValueW[word] == true) {
                        //adds the count if its positive
                        netural++;
                    }
                    else {
                        //subtract the count if its negative
                        netural--;
                    }
                }
            }
            token = strtok(nullptr,"!,@#$%^&*()_+/-|{}[];:\"'?~.<> 1234567890\\");
        }
        //if the sentiment of the word is equal to zero it turns positive
        sentValueS[id] = netural >= 0;
    }

}


//function for validation or accuracy
void analysisT::validation(DSString fileName0, DSString fileName1, DSString fileName2) {
    ifstream input (fileName0.c_str());

    if (!input.is_open()) {
        cout << "Error opening file" << '\n';
    }

    //creating a c-string buffer
    char* buffer = new char[1000];

    //discard header for file by reading in header
    //reading until 1000 char or until \n
    input.getline(buffer,1000);

    //parsing the file
    while(!input.eof()) {
        //will get line from each column until 1000 chars or until it reaches a ','
        input.getline(buffer, 1000, ',');
        if (strlen(buffer) == 0) {
            break;
        }
        bool isPositive = buffer[0] == '4';

        input.getline(buffer, 1000);
        DSString id = buffer;

        if(sentValueS[id] != isPositive) {
            iDofWrong.push_back(id);
        }
    }

    ofstream output0(fileName1.c_str());
    for(pair<DSString, bool> itr : sentValueS) {
        //outputs the correct answers, order as: if positive -> negative and vise versa
        if(itr.second) {
            output0 << "4," << itr.first << "\n";
        }
        else {
            output0 << "0," << itr.first << "\n";
        }
    }
    output0.close();

    ofstream output1(fileName2.c_str());
    //accuracy is 1 - (what we got wrong/what we go right); to get what we go right
    double accuracy = 1 - ((double)(iDofWrong.size())/(sentValueS.size()));

    //setting precision to 3 for decimal
    output1 << setprecision(3) << accuracy << endl;
    for(int i = 0; i < iDofWrong.size(); i++) {
        if(sentValueS[iDofWrong[i]]) {
            output1 << "4,0,";
        } else {
            output1 << "0,4,";
        }
        output1 << iDofWrong[i] << endl;
    }
    output1.close();
}