#include <iostream>
#include <vector>
#include <locale>
#include <codecvt>

using namespace std;

//індекси
int get_index(wchar_t ch){
    if (ch >= L'а' && ch <= L'я') {
        return ch - L'а';
    }
    return -1; 
}

//з індексів в юнікод
wchar_t get_unicode(int index) {
    return static_cast<wchar_t>(index + L'а');
}

//щифрування
void encrypt(const vector<int>& indices, const vector<int>& indices_key, vector<int>& indices_cipher) {
    for (size_t i = 0; i < indices.size(); i++) {
        indices_cipher.push_back((indices[i] + indices_key[i % indices_key.size()]) % 32);
    }
}

//розшифрування
void decrypt(const vector<int>& indices_cipher, const vector<int>& indices_key, vector<int>& indices_new) {
    for (size_t i = 0; i < indices_cipher.size(); i++) {
        indices_new.push_back((indices_cipher[i] - indices_key[i % indices_key.size()]) % 32);
    }
}

string wstring_to_utf8(const wstring& wstr) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

int main(){

    setlocale(LC_ALL, "ru_RU.UTF-8");

    wstring text = L"перстеньнесефродо";
    wstring key = L"назгул";

    vector<int> indices; //індекси відкритого тексту
    vector<int> indices_key; //індекси ключа
    vector<int> indices_cipher; //індекси шифротексту
    vector<int> indices_new; //індекси розшифрованого

    for (wchar_t ch : text) {
        int index = get_index(ch);
        if (index != -1) { // Пропускаємо пробіли та неправильні символи
            indices.push_back(index);
        }
    }

    for (wchar_t ch : key) {
        indices_key.push_back(get_index(ch));
    }

    encrypt(indices, indices_key, indices_cipher);
    decrypt(indices_cipher, indices_key, indices_new);

    wstring encrypted_text;
    for (int index : indices_cipher) {
        encrypted_text += get_unicode(index);
    }

    wstring decrypted_text;
    for (int index : indices_new) {
        decrypted_text += get_unicode(index);
    }

    cout << "Зашифрований текст: " << wstring_to_utf8(encrypted_text) << endl;
    cout << "Розшифрований текст: " << wstring_to_utf8(decrypted_text) << endl;

    return 0;
}