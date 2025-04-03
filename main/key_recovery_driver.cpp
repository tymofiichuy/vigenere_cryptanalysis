#include "key_recovery.hpp"

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 2){
        cerr << "Invalid argument";
    }
    else{
        analyzer anl;
        try{
            anl.read_chiphertext(argv[1]);
        }
        catch(runtime_error err){
            cerr << err.what();
        }

        int len = anl.index_length_recovery(0.005f);
        //cout << len << "\n";

        vector<int> key = anl.frequency_key_recovery(len);
        for(auto iter = key.begin(); iter != key.end(); iter++){
            wcout << anl.index_to_char(*iter);
        }
        cout << "\n";
        key = anl.index_key_recovery(len); 
        for(auto iter = key.begin(); iter != key.end(); iter++){
            wcout << anl.index_to_char(*iter);
        }         
    }
    return 0;
}