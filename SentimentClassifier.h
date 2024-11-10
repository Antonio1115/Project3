#ifndef SENTIMENT_CLASSIFIER_H
#define SENTIMENT_CLASSIFIER_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <vector>
#include "DSString.h"

class SentimentClassifier {
private:
    // Map to store the sentiment score for each word (positive/negative)
    std::unordered_map<DSString, int> wordSentimentMap;

    // Set to store stop words (words to be ignored)
    std::set<DSString> stopWords;

public:
    // Default constructor
    SentimentClassifier();

    // Load training data (tweets and sentiment labels)
    void loadTrainingData(const char* filename);

    // Load stop words (words to be ignored in sentiment analysis)
    void loadStopWords(const char* filename);

    // Classify a tweet as positive (1) or negative (0)
    int classifyTweet(const DSString& tweet);

    // Save classification results to file
    void saveResults(const char* filename, const std::vector<std::pair<DSString, int>>& results);

    // Evaluate the classifier's accuracy against a test dataset
    void evaluate(const std::vector<std::pair<DSString, DSString>>& testData,
                  const char* resultsFilename, const char* accuracyFilename);

    // Method to train the sentiment classifier
    void train(const char* trainingDataFile, const char* stopWordsFile);

    // Method to test the classifier
    void test(const char* testDataFile, const char* resultsFile);
};

#endif // SENTIMENT_CLASSIFIER_H
