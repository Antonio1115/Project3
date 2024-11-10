#include "SentimentClassifier.h"
#include <sstream>
#include <algorithm>

// Default constructor
SentimentClassifier::SentimentClassifier() {}

// Load training data (tweets and sentiment labels)
void SentimentClassifier::loadTrainingData(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open training file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t commaPos = line.find(",");
        if (commaPos != std::string::npos) {
            // Extract sentiment label (positive or negative) and tweet text
            DSString sentiment(line.substr(0, commaPos).c_str());
            DSString tweet(line.substr(commaPos + 1).c_str());

            // Tokenize the tweet and update sentiment score for each word
            std::vector<DSString> tokens = tweet.tokenize(' '); // Tokenize by spaces
            for (const auto& token : tokens) {
                if (stopWords.find(token) == stopWords.end()) {
                    // If the word is not a stop word, update sentiment map
                    wordSentimentMap[token] += (sentiment == "positive") ? 1 : -1;
                }
            }
        }
    }

    file.close();
}

// Load stop words (words that should be ignored in sentiment analysis)
void SentimentClassifier::loadStopWords(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open stop words file." << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
        stopWords.insert(DSString(word.c_str()));  // Add each word to the stop word set
    }

    file.close();
}

// Classify a tweet as positive (1) or negative (0)
int SentimentClassifier::classifyTweet(const DSString& tweet) {
    std::vector<DSString> tokens = tweet.tokenize(' ');  // Tokenize the tweet by spaces
    int sentimentScore = 0;

    for (const auto& token : tokens) {
        if (stopWords.find(token) == stopWords.end()) {
            // If not a stop word, check if the word exists in the sentiment map
            if (wordSentimentMap.find(token) != wordSentimentMap.end()) {
                sentimentScore += wordSentimentMap[token];  // Add sentiment score of the word
            }
        }
    }

    // Return classification based on sentiment score
    return sentimentScore > 0 ? 1 : 0;  // If score > 0, positive sentiment, else negative
}

// Save classification results to file
void SentimentClassifier::saveResults(const char* filename, const std::vector<std::pair<DSString, int>>& results) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open results file." << std::endl;
        return;
    }

    for (const auto& result : results) {
        file << result.first.c_str() << "," << result.second << std::endl;
    }

    file.close();
}

// Evaluate the classifier's accuracy against a test dataset
void SentimentClassifier::evaluate(const std::vector<std::pair<DSString, DSString>>& testData, const char* resultsFilename, const char* accuracyFilename) {
    std::vector<std::pair<DSString, int>> results;
    int correct = 0;
    int total = testData.size();

    for (const auto& testDatum : testData) {
        int predictedSentiment = classifyTweet(testDatum.first);
        int actualSentiment = (testDatum.second == DSString("positive")) ? 1 : 0;  // Assuming "positive" is the sentiment label

        results.push_back({testDatum.first, predictedSentiment});

        if (predictedSentiment == actualSentiment) {
            correct++;
        }
    }

    saveResults(resultsFilename, results);

    // Calculate and save accuracy
    double accuracy = static_cast<double>(correct) / total * 100.0;
    std::ofstream accuracyFile(accuracyFilename);
    if (accuracyFile.is_open()) {
        accuracyFile << "Accuracy: " << accuracy << "%" << std::endl;
        accuracyFile.close();
    } else {
        std::cerr << "Error: Could not open accuracy file." << std::endl;
    }
}

// Method to train the sentiment classifier
void SentimentClassifier::train(const char* trainingDataFile, const char* stopWordsFile) {
    // Load the training data and stop words
    loadTrainingData(trainingDataFile);
    loadStopWords(stopWordsFile);
}

// Method to test the classifier
void SentimentClassifier::test(const char* testDataFile, const char* resultsFile) {
    std::ifstream file(testDataFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open test file." << std::endl;
        return;
    }

    std::vector<std::pair<DSString, int>> results;
    std::string line;

    while (std::getline(file, line)) {
        size_t commaPos = line.find(",");
        if (commaPos != std::string::npos) {
            DSString tweet(line.substr(0, commaPos).c_str());
            int sentiment = classifyTweet(tweet);
            results.push_back({tweet, sentiment});
        }
    }

    file.close();
    saveResults(resultsFile, results);  // Save the results to the file
}
