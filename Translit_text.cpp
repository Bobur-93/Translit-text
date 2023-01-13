#include "Header.h"

Trans_text::Trans_text()
{
    wifstream file_lat, file_cyr;
    wstring buff;

	setlocale(LC_CTYPE, ".UTF-8");
    file_lat.open("Latin letter.txt");
    if (!file_lat.is_open())
    {
        cout << "Error!";
        return;
    }
    file_cyr.open("Cyrrilic letter.txt");
    if (!file_cyr.is_open())
    {
        cout << "Error!";
        return;
    }	
    file_lat.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    file_cyr.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    for (int i = 0; i < 33; i++)
    {
        file_lat >> buff;
        latin_low_let.push_back(buff);
        //buff.clear();
    }
    for (int i = 0; i < 32; i++)
    {
        file_lat >> buff;
        latin_cap_let.push_back(buff);
        //buff.clear();
    }
    for (int i = 0; i < 35; i++)
    {
        file_cyr >> buff;
        cyrillic_low_let.push_back(buff);
        //buff.clear();
    }
    for (int i = 0; i < 35; i++)
    {
        file_cyr >> buff;
        cyrillic_cap_let.push_back(buff);
        //buff.clear();
    }
    
    

    buff.clear();
    file_cyr.close();
    file_lat.close();

    /*wofstream f_out;
    f_out.open("out.txt");
    if (!f_out.is_open())
    {
        cout << "Error!";
        return;
    }
    f_out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    for (int i = 0; i < 31; i++)
    {
        f_out << i << ' ';
    }
    f_out << endl;
    for (int i = 0; i < 31; i++)
    {
        f_out << latin_low_let[i] << ' ';
    }
    f_out << endl;
    for (int i = 0; i < 31; i++)
    {
        f_out << latin_cap_let[i] << ' ';
    }
    f_out << endl;

    for (int i = 0; i < 35; i++)
    {
        f_out << i << ' ';
    }
    f_out << endl;
    for (int i = 0; i < 35; i++)
    {
        f_out << cyrillic_low_let[i] << ' ';
    }
    f_out << endl;
    for (int i = 0; i < 33; i++)
    {
        f_out << cyrillic_cap_let[i] << ' ';
    }
    f_out << endl;

    f_out.close();*/
}

Trans_text::~Trans_text()
{
    //latin_low_let.clear();
    vector <wstring>().swap(latin_low_let);
    vector <wstring>().swap(latin_cap_let);
    vector <wstring>().swap(cyrillic_low_let);
    vector <wstring>().swap(cyrillic_cap_let);

    //delete[] lat_trans;
    //delete[] cyr_trans;
    //delete[] vovel;
}

std::wstring Trans_text::trans_text(std::wstring text, int type)
{
    std::wstring new_text;
    if (type == 0)
    {
        new_text = lat_to_cyr(text);
    }
    else
    {
        new_text = cyr_to_lat(text);
    }

    return new_text;
}

void Trans_text::write_text()
{
	setlocale(LC_CTYPE, ".UTF-8");
    /*for (int i = 0; i < 29; i++)
    {
        cout << latin_low_let[i][0] << ' ';
    }
    cout << '\n';*/
    //char a = 'a';
    //cout << static_cast<int> (a) << endl;
    for (int i = 0; i < 35; i++)
    {
        std::wcout << cyrillic_low_let[i] << ' ';
        //wcout << cyrillic_low_let[i] << '\n';
    }
    std::cout << std::endl;
    /*for (int i = 0; i < 29; i++)
    {
        cout << cyrillic_low_let[i] << ' ';
    }
    cout << '\n';
    for (int i = 0; i < 29; i++)
    {
        cout << latin_low_let[cyr_trans[i]] << ' ';
    }
    cout << '\n';*/
}

wstring Trans_text::lat_to_cyr(std::wstring text)
{
    setlocale(LC_CTYPE, ".UTF-8");
    wstring new_text, word_cyr, word, symbol_lat, symbol_cyr;
    new_text = text;
    int i;

    //split string into words
    if (!new_text.empty())
    {
        char* str = new char[new_text.size() + 1];
        for (int i = 0; i < new_text.size(); i++)
        {
            str[i] = new_text[i];
            //cout << str[i];
        }
        str[new_text.size()] = '\0';
        char* pch = strtok(str, " .,()[]{}!?\\/\"\n\t");
        //cout << pch << '\n';

        while (pch != NULL)
        {
            //cout << pch << '\n';
            i = 0;
            while (pch[i] != '\0')
            {
                word.push_back(pch[i]);
                i++;
            }
            //wcout << word << endl;

            //After splitting the string, check for exceptional words
            word_cyr = latin_word(word);
            if (!word_cyr.empty())
            {
                wregex replace(word_cyr);
                regex_constants::match_flag_type fonly = regex_constants::format_first_only;
                new_text = regex_replace(new_text, replace, word_cyr, fonly);
            }

            //wcout << word_cyr << endl;

            pch = strtok(NULL, " .,()[]{}!?\\/\"\n\t");

            word.clear();
            //wcout << word << endl;

            if (pch == NULL)
            {
                break;
            }
        }

        delete[] str;
        str = NULL;

    }

    //replace endings
    new_text = last_words(new_text);

    //wcout << new_text << '\n';



    for (int i = 0; i < 9; i++)
    {
        //std::wcout << latin_low_let[24 + i] << endl;
        //wcout << cyrillic_low_let[lat_trans[24 + i]] << endl;
        //wcout << cyrillic_cap_let[lat_trans[24 + i]] << endl;

        if (i == 7 || i == 8)
        {
            wregex replace_1(latin_low_let[24 + i]);
            new_text = regex_replace(new_text, replace_1, cyrillic_low_let[lat_trans[24 + i]]);
        }
        else
        {
            wregex replace_1(latin_low_let[24 + i]);
            wregex replace_2(latin_cap_let[24 + i]);
            new_text = regex_replace(new_text, replace_1, cyrillic_low_let[lat_trans[24 + i]]);
            new_text = regex_replace(new_text, replace_2, cyrillic_cap_let[lat_trans[24 + i]]);
        }

    }
    for (int i = 0; i < 24; i++)
    {
        wregex replace_1(latin_low_let[i]);
        wregex replace_2(latin_cap_let[i]);
        new_text = regex_replace(new_text, replace_1, cyrillic_low_let[lat_trans[i]]);
        new_text = regex_replace(new_text, replace_2, cyrillic_cap_let[lat_trans[i]]);
    }    

    //wcout << new_text << endl;

    return new_text;
}

wstring Trans_text::cyr_to_lat(std::wstring text)
{
    wstring new_text, symbol_lat, symbol_5, symbol_5_cap, symbol_23;

    new_text = text;
    //wcout << new_text << '\n';
        
    symbol_5 = latin_low_let[22] + latin_low_let[3];
    symbol_5_cap = latin_cap_let[22] + latin_low_let[3];
    symbol_23 = latin_low_let[18] + latin_low_let[17];
    

    regex_constants::match_flag_type fonly = regex_constants::format_first_only;
    //cout << new_text.size() << endl;
	wstring space, tabulat, new_line;
	space = L" ";
	tabulat = L"\n";
	new_line = L"\t";
    for (int i = 0; i < new_text.size(); i++)
    {
        if (new_text[i] == cyrillic_low_let[5][0] || new_text[i] == cyrillic_low_let[23][0])
        {
            if (i == 0)
            {
                if (new_text[i] == cyrillic_low_let[5][0])
                {
                    wregex replace(cyrillic_low_let[5]);
                    new_text = regex_replace(new_text, replace, symbol_5, fonly);
                }
                else
                {
                    wregex replace(cyrillic_low_let[23]);
                    new_text = regex_replace(new_text, replace, latin_low_let[17], fonly);                    
                }
            }
            else
            {
                if (new_text[i - 1] == space[0] || new_text[i - 1] == tabulat[0] || new_text[i - 1] == new_line[0])
                {
                    if (new_text[i] == cyrillic_low_let[5][0])
                    {
                        wregex replace(cyrillic_low_let[5]);
                        new_text = regex_replace(new_text, replace, symbol_5, fonly);
                    }
                    else
                    {
                        wregex replace(cyrillic_low_let[23]);
                        new_text = regex_replace(new_text, replace, latin_low_let[17], fonly);
                    }
                }
                else
                {
                    int flag = 0;
                    for (int j = 0; j < 10; j++)
                    {
                        if (new_text[i - 1] == cyrillic_low_let[vovel[j]][0])
                        {
                            flag = 1;
                            if (new_text[i] == cyrillic_low_let[5][0])
                            {
                                wregex replace(cyrillic_low_let[5]);
                                new_text = regex_replace(new_text, replace, symbol_5, fonly);
                                break;
                            }
                            else
                            {
                                wregex replace(cyrillic_low_let[23]);
                                new_text = regex_replace(new_text, replace, symbol_23, fonly);
                                break;
                            }
                        }
                    }

                    if (flag == 0)
                    {
                        if (new_text[i] == cyrillic_low_let[5][0])
                        {
                            wregex replace(cyrillic_low_let[5]);
                            new_text = regex_replace(new_text, replace, latin_low_let[3], fonly);
                        }
                        else
                        {
                            wregex replace(cyrillic_low_let[23]);
                            new_text = regex_replace(new_text, replace, latin_low_let[17], fonly);
                        }
                    }
                }
            }
        }
        else
        {
            if (new_text[i] == cyrillic_cap_let[5][0] || new_text[i] == cyrillic_cap_let[23][0])
            {
                if (new_text[i] == cyrillic_cap_let[5][0])
                {
                    wregex replace(cyrillic_cap_let[5]);
                    new_text = regex_replace(new_text, replace, symbol_5_cap, fonly);
                }
                else
                {
                    wregex replace(cyrillic_cap_let[23]);
                    new_text = regex_replace(new_text, replace, latin_cap_let[17], fonly);
                }
            }
        }
    }


    for (int i = 0; i < 34; i++)
    {
        wregex replace_1(cyrillic_low_let[i]);
        wregex replace_2(cyrillic_cap_let[i]);
        new_text = regex_replace(new_text, replace_1, latin_low_let[cyr_trans[i]]);
        new_text = regex_replace(new_text, replace_2, latin_cap_let[cyr_trans[i]]);
    }


    wregex replace(cyrillic_cap_let[34]), replace1(cyrillic_low_let[34]);

    symbol_lat = L"";
    new_text = regex_replace(new_text, replace, symbol_lat);
    new_text = regex_replace(new_text, replace1, symbol_lat);

    return new_text;
}

wstring Trans_text::last_words(std::wstring text)
{
    wstring latin, cyrril, error_sign, new_text;
    wifstream file_last_words;
    file_last_words.open("Last_words.txt");
    if (!file_last_words.is_open())
    {
        //cout << "Error!";
        error_sign.push_back('\0');
        return error_sign;
    }	
    file_last_words.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    new_text = text;

    while (!file_last_words.eof())
    {
        file_last_words >> latin;
        file_last_words >> cyrril;

        wregex replace(latin);
        new_text = regex_replace(new_text, replace, cyrril);
    }

    //wcout << text << endl;

    return new_text;
}

wstring Trans_text::latin_word(std::wstring word)
{
    wstring error_sign;

    if (word.empty())
    {
        cout << "Empty word";
        error_sign.push_back('\0');
        return error_sign;
    }

    if (word[0] == 'W' || word[0] == 'w')
    {
        error_sign.push_back('\0');
        return error_sign;
    }
    if (word[0] == 'H' || word[0] == 'h')
    {
        error_sign.push_back('\0');
        return error_sign;
    }

    wstring path;
    std::wifstream word_base;

    //wcout << path << endl;

    for (int i = 0; i < 25; i++)
    {
        if (word[0] == latin_low_let[i][0] || word[0] == latin_cap_let[i][0])
        {
            if (i == 24)
            {
                path = L"ch.txt";
                break;
            }
            path = latin_low_let[i] + L".txt";
            break;
        }
    }

    //wcout << path << endl;

    word_base.open(path.c_str());
    if (!word_base.is_open())
    {
        //cout << "Error";
        error_sign.push_back('\0');
        return error_sign;
    }
    word_base.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    wstring latin, cyrril, buffer_for_latin, buffer_for_cyrril, return_word;
    buffer_for_latin.clear();
    buffer_for_cyrril.clear();
    int return_flag = 0;
    return_word = word;

    while (!word_base.eof())
    {
        word_base >> latin;
        word_base >> cyrril;

        int flag = 0;
        if (word.size() < latin.size())
        {
            continue;
        }
        for (int i = 1; i < latin.size(); i++)
        {
            if (word[i] != latin[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            continue;
        }

        return_flag = 1;
        if (!buffer_for_latin.empty())
        {
            if (buffer_for_latin.size() < latin.size())
            {
                buffer_for_latin = latin;
                buffer_for_cyrril = cyrril;
            }
        }
        else
        {
            buffer_for_latin = latin;
            buffer_for_cyrril = cyrril;
        }

    }

    //system::pin_ptr<wchar_t> letter;
    if (return_flag == 1)
    {
        for (int i = 0; i < 25; i++)
        {
            if (i == 24)
            {
                if (word[0] == latin_cap_let[24][0])
                {
                    buffer_for_cyrril[0] = cyrillic_cap_let[lat_trans[24]][0];
                }
            }
            if (word[0] == latin_cap_let[i][0])
            {
                buffer_for_cyrril[0] = cyrillic_cap_let[lat_trans[i]][0];
            }
        }
    }

    wregex rp(buffer_for_latin);
    regex_constants::match_flag_type fonly = regex_constants::format_first_only;
    return_word = regex_replace(return_word, rp, buffer_for_cyrril, fonly);


    word_base.close();

    return return_word;

}



