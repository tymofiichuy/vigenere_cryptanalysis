#include "key_recovery.hpp"

using namespace std;

uint8_t analyzer::char_to_index(wchar_t wch){
    if(wch<0x430||wch>0x44F){
        return -1;
    }
    else{
        return static_cast<uint8_t>(wch-0x430);
    }
}

void analyzer::read_chiphertext(string file){
    wifstream str;
    wchar_t wch;
    uint8_t index;

    str.imbue(locale("en_US.UTF-8"));
    str.open(file);
    if(!str){
        throw runtime_error("Unable to open file");
    }

    while(str.read(&wch, 1)){
        index = char_to_index(wch);
        if(index != -1){
            ciphertext.push_back(index);
        }
    }
}