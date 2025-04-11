#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>

using namespace std;

// індекси
int get_index(wchar_t ch) {
    // if (ch>=L'а' && ch<=L'я') {
    //     return ch - L'а';
    // }
    if (ch>=0x430 && ch<=0x44F) {
        return ch - 0x430;
    }
    return -1;
}

// з індексів в юнікод
wchar_t get_unicode(int index) {
    return static_cast<wchar_t>(index + 0x430);
}

// шифрування
void encrypt(const vector<int>& indices, const vector<int>& indices_key, wstring& encrypted_text) {
    for (size_t i = 0; i < indices.size(); i++) {
        int encrypted_index=(indices[i]+indices_key[i%indices_key.size()]) %32;
        encrypted_text+=get_unicode(encrypted_index);
    }
}

// розшифрування
void decrypt(const vector<int>& indices_cipher, const vector<int>& indices_key, wstring& decrypted_text) {
    for (size_t i=0; i<indices_cipher.size(); i++) {
        int decrypted_index=(indices_cipher[i]-indices_key[i%indices_key.size()]+32) %32;
        decrypted_text+=get_unicode(decrypted_index);
    }
}

// зчитування UTF-8 файлу в wstring
wstring read_utf8_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return L"";
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return converter.from_bytes(content);
}

// запис wstring у UTF-8 файл
void write_utf8_file(const string& filename, const wstring& content) {
    ofstream file(filename);
    if (!file.is_open()) return;
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    file << converter.to_bytes(content);
}

int main(int argc, char *argv[]) {
    //argv: name, text, key, mode
    if(argc!=4){
        cerr << "Invalid argument";
        return 1;
    }
    else{
        bool mode;
        if(strcmp(argv[3], "--enc") == 0){
            mode = true;
        }
        else if(strcmp(argv[3], "--dec") == 0){
            mode = false;
        }
        else{
            cerr << "Invalid mode";
            return 1;
        }

        wstring text = read_utf8_file(argv[1]);
        wstring key = read_utf8_file(argv[2]);

        if (text.empty() || key.empty()) {
            //cout << "Помилка відкриття або зчитування файлів!" << endl;
            cout << "Error: unable to open/read file" << endl;
            return 1;
        }

        if (!text.empty() && text[0] == 0xFEFF) text.erase(0,1);
        if (!key.empty() && key[0] == 0xFEFF) key.erase(0,1);

        vector<int> indices;
        vector<int> indices_key;
        //vector<int> indices_cipher;

        for (wchar_t ch: text) {
            int index=get_index(ch);
            if (index!=-1) {
                indices.push_back(index);
            }
        }

        for (wchar_t ch: key) {
            int index=get_index(ch);
            if (index!=-1) {
                indices_key.push_back(index);
            }
        }

        if (indices.empty() || indices_key.empty()) {
            //cout << "Помилка: текст або ключ не містять валідних символів!" << endl;
            cout << "Error: there are no valid symbols!" << endl;
            return 1;
        }

        if(mode){
            wstring encrypted_text;
            encrypt(indices, indices_key, encrypted_text);
            write_utf8_file("encrypted_text.txt", encrypted_text);

            // for (wchar_t ch: encrypted_text) {
            //     int index = get_index(ch);
            //     if (index!=-1) {
            //         indices_cipher.push_back(index);
            //     }
            // }            
        }
        else{
            wstring decrypted_text;
            // decrypt(indices_cipher, indices_key, decrypted_text);
            decrypt(indices, indices_key, decrypted_text);
            write_utf8_file("decrypted_text.txt", decrypted_text);            
        }

        //cout << "Файли успішно оброблені: encrypted_text.txt/decrypted_text.txt" << endl;
        cout << "Success: encrypted_text.txt/decrypted_text.txt" << endl;
        return 0;        
    }
}
