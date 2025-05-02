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
				const int CHUNK_SIZE = 6;
				const int MAX_CHUNKS = 5;
				std::vector<HASH_INDEX_T> w(MAX_CHUNKS, 0);

				int chunkIndex = MAX_CHUNKS -1;
				for(int i = k.length(); i > 0 && chunkIndex >= 0; i -= CHUNK_SIZE, --chunkIndex)
				{
					HASH_INDEX_T value = 0;
					HASH_INDEX_T power = 1;

					for(int j = i -1; j >= std::max(i - CHUNK_SIZE, 0); --j)
					{
						HASH_INDEX_T charValue = letterDigitToNumber(k[j]);
						value += charValue * power;
						power *= 36;
					}
					w[chunkIndex] = value;
				}

				HASH_INDEX_T hashVal = 0;
				for(int i = 0; i < MAX_CHUNKS; ++i)
				{
					hashVal += rValues[i] * w[i];
				}
				return hashVal;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				if(std::isalpha(letter))
				{
					return std::tolower(letter) - 'a';
				}
				else if(std::isdigit(letter))
				{
					return 26 + (letter - '0');
				}
				return 0;
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
