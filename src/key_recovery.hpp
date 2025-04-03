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
    float language_frequency[32] = {0.11582f, 0.08169f, 0.07453f, 0.06970f, 0.06632f, 0.05676f, 0.05324f, 0.05313f, 
                                    0.04733f, 0.04068f, 0.03384f, 0.03348f, 0.03134f, 0.02768f, 0.02671f, 0.02084f,
                                    0.02073f, 0.02069f, 0.01991f, 0.01823f, 0.01742f, 0.01310f, 0.01068f, 0.01011f, 
                                    0.00917f, 0.00815f, 0.00493f, 0.00473f, 0.00342f, 0.00281f, 0.00267f, 0.00014f};

    int permutation[32] = {2, 19, 9, 17, 10, 1, 23, 20, 3, 22, 12, 7, 11, 4, 0, 13, 
                           8, 6, 5, 14, 31, 21, 29, 18, 24, 28, 32, 15, 16, 30, 27, 25};

    std::deque<uint8_t> ciphertext;

    uint8_t char_to_index(wchar_t wch);

    float index_of_coincidence(float* frequency);
    //float index_of_coincidence(int* frequency, int size);
public:
    wchar_t index_to_char(uint8_t index);
    
    void read_chiphertext(std::string file);
    int index_length_recovery(float threshold);
    //int match_length_recovery(float threshold);
    
    std::vector<int> frequency_key_recovery(int key_size);
    std::vector<int> index_key_recovery(int key_size);
};