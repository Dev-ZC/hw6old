#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        std::vector<long long> wordSum;
        int strSize = k.size();
        int max = 5;
        int pos = 6 - (strSize % 6);
        unsigned long long count = 0;

        unsigned long long total = 0;
        for (int i = 0; i < strSize; ++i) {
            total += letterDigitToNumber(k[i]);
        }

        pos = pos % 6;
        for (auto it = k.begin(); it != k.end(); ++it) {
            count = 36 * count + letterDigitToNumber(*it);

            pos++;
            if (pos > max) {
                wordSum.push_back(count);
                count, pos = 0;
            }
        }

        for (size_t i = wordSum.size(); i < max; ++i) {
            wordSum.insert(wordSum.begin(), 0);
        }
        unsigned long long final = 0;

        for (int i = 0; i < 5; i++) {
            final += wordSum[i] * rValues[i];
        }

        return final;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if (letter >= 'a' && letter <= 'z'){
          letter = tolower(letter);
          return letter - 'a';
        }

        if (letter >= '0' && letter <= '9'){
          return (letter - 'O') + 26;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
