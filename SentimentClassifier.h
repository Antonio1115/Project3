//
// Created by Xital on 10/31/2024.
//

#ifndef ANALYSIST_H
#define ANALYSIST_H
#include "DSString.h"

#include<map>
#include<vector>
#include<fstream>
#include<string.h> //for strtok()
#include<utility> // to use pairs with the map
#include <iomanip>
using namespace std;

class analysisT {
private:
   
    map<DSString, pair<int, int>> sentCount;
   
    map<DSString, bool> sentValueW;
    
    map<DSString, bool> sentValueS;

    vector<DSString> iDofWrong;

public:
    void training(DSString fileName);
    void testing(DSString fileName);
    void validation(DSString fileName0, DSString fileName1, DSString fileName2);
};



#endif //ANALYSIST_H