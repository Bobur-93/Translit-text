#include "Header.h"


int main()
{
    //setlocale(LC_ALL, "Russian");
    //setlocale(LC_ALL, "");
    setlocale(LC_CTYPE, ".UTF-8");
    int i;

    wifstream in_file;
    wofstream file_out;

    /*const locale empty_locale = locale::empty();
    typedef codecvt_utf8<wchar_t> converter_type;
    const converter_type* converter = new converter_type;
    const std::locale utf8_locale = std::locale(empty_locale, converter);*/

    in_file.open("in.txt");
    if (!in_file.is_open())
    {
        cout << "Error!";
        return -1;
    }
	
    in_file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    file_out.open("out.txt");
    if (!file_out.is_open())
    {
        cout << "Error!";
        return -1;
    }
    file_out.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    //wifstream word_base;
    //word_base.open("y.txt");
    //word_base.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

    //wstring latin, cyrril;
    //char a = 'a';
    //std::cout << static_cast<int> (a) << std::endl;

    /*while (!word_base.eof())
    {
        word_base >> latin;
        file_out << latin << ' ';
        wcout << latin << endl;
        for (int i = 0; i < latin.size(); i++)
        {
            cout << static_cast<int>(latin[i]) << ' ';
        }
        cout << endl;
        word_base >> cyrril;
        file_out << cyrril << endl;
        wcout << cyrril << endl;
        for (int i = 0; i < cyrril.size(); i++)
        {
            cout << static_cast<int>(cyrril[i]) << ' ';
        }
        cout << endl;

    }*/




    cout << "Enter 0 or 1:\n";
    cin >> i;

    Trans_text test;
    //test.write_text();
    /*for (int i = -128; i < 128; i++)
    {
        cout << static_cast<char>(i) << ' ';
        cout << i << '\n';
    }*/

    wstring text, finish_text;

    while (!in_file.eof())
    {
        getline(in_file, text);
        if (i == 0)
        {
            finish_text = test.lat_to_cyr(text);
        }
        else
        {
            finish_text = test.cyr_to_lat(text);
        }

        file_out << finish_text;
        file_out << endl;
    }


    //string test_text("Versions 1, 2, 3 and 4 return a string object with the resulting sequence. Versions 5 and 6 return out.");
    //string fmt("A");


    /*while (!in_file.eof())
    {
        getline(in_file, text);
        wcout << text << '\n';
        if (!text.empty())
        {
            char* str = new char[text.size() + 1];
            for (int i = 0; i < text.size(); i++)
            {
                str[i] = text[i];
                //cout << str[i];
            }
            str[text.size()] = '\0';
            char* pch = strtok(str, " .,()[]{}!?");
            //cout << pch << '\n';

            while (pch != NULL)
            {
                cout << pch << '\n';
                i = 0;
                while (pch[i]!='\0')
                {
                    word.push_back(pch[i]);
                    i++;
                }
                wcout << word << endl;

                word_cyr = test.latin_word(word);
                if (!word_cyr.empty())
                {
                    wregex replace(word);
                    regex_constants::match_flag_type fonly = regex_constants::format_first_only;
                    text = regex_replace(text, replace, word_cyr, fonly);
                }

                wcout << word_cyr << endl;

                pch = strtok(NULL, " .,()[]{}!?");

                word.clear();
                wcout << word << endl;

                if (pch == NULL)
                {
                    break;
                }
            }

            delete[] str;
            str = NULL;

        }



        //cout << '\n';

        //in_file >> word;
        //cout << word << endl;


        //cout << word << endl;

        *if (i == 0)
        {
            finish_text = test.lat_to_cyr(text);
        }
        else
        {
            finish_text = test.cyr_to_lat(text);
        }

        file_out << finish_text;
        file_out << '\n';


    }*/


    in_file.close();
    file_out.close();

    //regex e("a");

    //cout << test_text << '\n';
    //cout << regex_replace(test_text, e, fmt) << '\n';

    return 0;
}