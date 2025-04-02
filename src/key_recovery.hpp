#pragma once

#include<iostream>
#include<deque>
#include<fstream>
#include<cwchar>
#include<string>
#include<vector>
#include<cmath>

class analyzer{
private:
    float language_frequency[32] = {0.11582, 0.08169, 0.07453, 0.06970, 0.06632, 0.05676, 0.05324, 0.05313, 
                                    0.04733, 0.04068, 0.03384, 0.03348, 0.03134, 0.02768, 0.02671, 0.02084,
                                    0.02073, 0.02069, 0.01991, 0.01823, 0.01742, 0.01310, 0.01068, 0.01011, 
                                    0.00917, 0.00815, 0.00493, 0.00473, 0.00342, 0.00281, 0.00267, 0.00014};

    int permutation[32] = {2, 19, 9, 17, 10, 1, 23, 20, 3, 22, 12, 7, 11, 4, 0, 13, 
                           8, 6, 5, 14, 31, 21, 29, 18, 24, 28, 32, 15, 16, 30, 27, 25};

    std::deque<uint8_t> ciphertext;

    uint8_t char_to_index(wchar_t wch);
    wchar_t index_to_char(uint8_t index);

    float index_of_coincidence(float* frequency);
public:
    void read_chiphertext(std::string file);
    int length_recovery(float threshold);
    
    vector<int> frequency_key_recovery(int key_size);
    vector<int> index_key_recovery(int key_size);
};