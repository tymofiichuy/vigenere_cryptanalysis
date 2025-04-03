#include "key_recovery.hpp"

using namespace std;

vector<int> analyzer::frequency_key_recovery(int key_size){
    vector<int> key;
    key.reserve(key_size);
    int block_frequency[32] = {}, char_index, max_val_index = 0, key_symbol;

    for(int shift = 0; shift < key_size; shift++){
        char_index = shift;
        for(int i = 0; i < 32; i++){
            block_frequency[i] = 0;
        }
        
        while(char_index<ciphertext.size()){
            block_frequency[ciphertext[char_index]]++;

            char_index += key_size;
        }

        for(int i = 1; i < 32; i++){
            if(block_frequency[i]>block_frequency[max_val_index]){
                max_val_index = i;
            }
        }

        key_symbol = max_val_index-14;
        if(key_symbol >= 0){
            key.push_back(key_symbol);
        }
        else{
            key.push_back(31+key_symbol);
        }
    }
    return key;
}

vector<int> analyzer::index_key_recovery(int key_size){
    vector<int> key;
    key.reserve(key_size);
    int block_frequency[32] = {}, char_index, key_symbol;
    float temp_res, temp_res_prev;

    for(int shift = 0; shift < key_size; shift++){
        char_index = shift;
        for(int i = 0; i < 32; i++){
            block_frequency[i] = 0;
        }
        
        while(char_index<ciphertext.size()){
            block_frequency[ciphertext[char_index]]++;

            char_index += key_size;
        }

        temp_res_prev = 0.0f;
        for(int i = 0; i < 32; i++){
            temp_res = 0.0f;
            for(int j = 0; j < 32; j++){
                temp_res+=block_frequency[(i+j)%32]*language_frequency[permutation[j]];             
            }
            if(temp_res > temp_res_prev){
                key_symbol = i;
                temp_res_prev = temp_res;
            }
        }
        key.push_back(key_symbol);
    }
    return key;
}