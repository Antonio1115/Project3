#include <iostream>
#include "SentimentClassifier.h"

int main(int argc, char** argv){
    if (argc != 6) {
        cerr << "Invalid command line arguments" << endl;
        exit(1);
    }
    
    analysisT a;
    a.training(argv[1]);
    a.testing(argv[2]);
    a.validation(argv[3], argv[4], argv[5]);

    return 0;
}