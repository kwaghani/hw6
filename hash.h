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
      // Add your code here
      unsigned long long w[5] = {0, 0, 0, 0, 0};  // up to 5 chunks
      int len = k.length();
      int chunkCount = 0;

      for (int i = len; i > 0; i -= 6) {
          unsigned long long chunkValue = 0;
          int start = std::max(0, i - 6);
          int power = 0;

          for (int j = i - 1; j >= start; --j) {
              chunkValue += letterDigitToNumber(k[j]) * pow36(power);
              ++power;
          }

          w[4 - chunkCount] = chunkValue;
          ++chunkCount;
      }

      // Combine using the hash formula
      HASH_INDEX_T h = 0;
      for (int i = 0; i < 5; ++i) {
        std::cout << "w[" << i << "] = " << w[i] << std::endl;
        h += rValues[i] * w[i];
      }
      return h;
    }

    unsigned long long pow36(int power) const
    {
        unsigned long long result = 1;
        for(int i = 0; i < power; ++i) {
            result *= 36;
        }
        return result;
    }


    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = std::tolower(letter);
        if(letter >= 'a' && letter <= 'z') {
            return letter - 'a';
        } else if(letter >= '0' && letter <= '9') {
            return 26 + (letter - '0');
        }
        return 0; // default case for unexpected input
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
