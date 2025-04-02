#include "key_recovery.hpp"

using namespace std;

vector<int> analyzer::frequency_key_recovery(int key_size){
    vector<int> key;
    int block_frequency[32] = {}, char_index, block_size, max_val_index = 0, key_symbol;

    for(int shift = 0; shift < key_size; shift++){
        char_index = shift;
        block_size = 0;
        while(char_index<ciphertext.size()){
            block_frequency[ciphertext[char_index]]++;

            block_size++;
            char_index += key_size;
        }

        for(int i = 1; i < 32; i++){
            if(block_frequency[i]>block_frequency[max_val_index]){
                max_val_index = i;
            }
        }

        key_symbol = 14-max_val_index;
        if(key_symbol >= 0){
            key.push_back(key_symbol);
        }
        else{
            key.push_back(32+key_symbol);
        }

        return key;
    }
}