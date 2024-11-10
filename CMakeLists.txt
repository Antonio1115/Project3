cmake_minimum_required(VERSION 3.29)
project(Project3_Sentiment_Analysis)

set(CMAKE_CXX_STANDARD 20)

add_executable(test main.cpp
        DSString.cpp
        SentimentClassifier.cpp
        SentimentClassifier.h)