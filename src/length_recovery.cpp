#include "key_recovery.hpp"

using namespace std;

float analyzer::index_of_coincidence(float* frequency){
    float index = 0;
    for(int i = 0; i < 32; i++){
        index += frequency[i]*frequency[i];
    }
    return index;
}

int analyzer::length_recovery(float threshold){
    float block_frequency[32] = {}, language_index = index_of_coincidence(language_frequency);
    int char_index, block_size;
    bool flag;

    for(int key = 0; key < ciphertext.size(); key++){
        flag = true;
        for(int shift = 0; shift < key; shift++){
            char_index = shift;
            block_size = 0;
            while(char_index<ciphertext.size()){
                block_frequency[ciphertext[char_index]]++;

                block_size++;
                char_index += key;
            }
            for(int i = 0; i < 32; i++){
                block_frequency[i]/block_size;
            }
            if(abs(language_index-index_of_coincidence(block_frequency))>threshold){
                flag = false;
                break;
            }
        }
        if(flag){
            return key;
        }
    }
}