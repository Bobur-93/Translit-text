#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <codecvt>
#include <locale>
#include <vector>
#include <cstring>
//#include "Translit_text.cpp"

using namespace std;

class Trans_text {
public:
    Trans_text();
    ~Trans_text();

    void write_text();
    wstring trans_text(wstring text, int type);
    wstring lat_to_cyr(wstring text);
    wstring cyr_to_lat(wstring text);
    wstring latin_word(wstring word);
    wstring last_words(wstring text);
private:
    //string latin_low_let[29] = { "a","b","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","x","y","z","ch","sh","yo","yu","ya"};
    //string latin_cap_let[29] = { "A","B","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","X","Y","Z","Ch","Sh","Yo","Yu","Ya"};
    vector <wstring> latin_low_let, latin_cap_let, cyrillic_low_let, cyrillic_cap_let;
    //Буква ц в начале слова и после согласной пишется через s, а после гласной через ts
    //-32 -31 -28 -27 -12 -29 63 -24 -26 -22 -21 -20 -19 -18 -17 63 -16 -15 -14 -13 -30 -11 -23 -25 -9 -8 -72 -2 -1
    //-32 -31 -28 -27 -12 -29 63 -24 -26 -22 -21 -20 -19 -18 -17 63 -16 -15 -14 -13 -30 -11 -23 -25 -9 -8 -72 -2 -1 -32 -31 -13 -27 -30 -29
    //string cyrillic_low_let[35] = { "а","б","в","г","д","е","ё","ж","з","и","й","к","л","м","н","о","п","р","с","т","у","ф","х","ц","ч","ш","э","ю","я","ў","қ","ғ","ҳ", "ъ", "ь"};
    //string cyrillic_cap_let[33] = { "А","Б","В","Г","Д","Е","Ё","Ж","З","И","Й","К","Л","М","Н","О","П","Р","С","Т","У","Ф","Х","Ц","Ч","Ш","Э","Ю","Я","ў","қ","ғ","ҳ" };
    int lat_trans[33] = { 0,1,4,5,21,3,32,9,7,11,12,13,14,15,16,30,17,18,19,20,2,22,10,8,24,25,6,27,28, 29, 31, 33, 33 };
    int cyr_trans[34] = { 0,1,20,5,2,3,26,8,23,7,22,9,10,11,12,13,14,16,17,18,19,4,21,17,24,25,3,27,28, 29, 15, 30, 6, 31 };
    int vovel[10] = { 0,5,6,9,15,20,26,27,28,29 };
};

#endif