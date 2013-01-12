#include "expansor.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

void first_step(str in, macro_t &macro)
{
    macro_i imac;
    string line, name, parameter, data;
    size_t posb,pose;

    ifstream fin(in.c_str());
    if(fin.is_open())
    {
            while(fin.good())
        {
            getline(fin,line);
            posb = line.find(BEGIN);
            if(posb != string::npos) // Se achar MACRO
            {
                // Separa o nome da macro
                name = line;
                name.erase(name.begin() + name.find(":") , name.end());

                // Verifica se tem parametro
                parameter = line;
                parameter.erase(parameter.begin(), (parameter.begin() + parameter.find(BEGIN) + 10) );
                if(!parameter.empty())
                {
                    parameter.erase(parameter.begin(), (parameter.begin() + 1));
                }

                //Pega o código da macro
                data.erase();
                getline(fin, line);
                pose = line.find(END);
                while(pose == string::npos)
                {
                    data += line + '\n';
                    getline(fin, line);
                    pose = line.find(END);
                }

                macro[name] = make_pair(data,parameter);
            }
        }
    }
    fin.close();
}

void second_step(str in, str out, macro_t &macro)
{
    string line, word, data, waux, waux2, param;
    size_t posb, pose;
    map<string, int> macaux;
    map<string, int>::iterator macaux_i;
    macro_i imac;

    ifstream fin(in.c_str());
    ofstream fout(out.c_str());


    for (imac = macro.begin(); imac != macro.end(); imac++)
    {
        macaux[imac->first] = 0;
    }

    if(fin.is_open())
    {
        while(fin.good())
        {
            getline(fin, line);
            posb = line.find(BEGIN);
            if(posb != string::npos)
            {
                pose = line.find(END);
                while (pose == string::npos)
                {
                	getline(fin,line);
                	pose = line.find(END);
                }
            }
            else
            {
                // Separa as Labels
                istringstream iss(line);
                iss >> skipws >> word;
//                cout << word << endl;
                word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end());
                if( (imac = macro.find(word)) != macro.end() )
                {
                    data = imac->second.first;

                    macaux_i = macaux.find(imac->first);
                    macaux_i->second++;
                    istringstream mds(data);
                    while(getline(mds,waux,'\n'))
                    {
                        waux.erase(remove_if(waux.begin(), waux.end(), ::isspace), waux.end());
                        if(waux.find(":") != string::npos)
                        {
                            waux2 = waux.substr(0,waux.find(":"));
                            stringstream nlab;
                            nlab << macaux_i->second;
                            // Trata cada um dos casos possíveis
                            param = waux2 + ":";
                            while(data.find(param) != string::npos)
                            {
                                data.replace( data.find(param), param.length(), waux2 + nlab.str() + ":" );
                            }
                            param = " " + waux2 + " ";
                            while(data.find(param) != string::npos)
                            {
                                data.replace( data.find(param), param.length(), " " + waux2 + nlab.str() + " " );
                            }
                            param = " " + waux2 + "\n";
                            while(data.find(param) != string::npos)
                            {
                                data.replace( data.find(param), param.length(), " " + waux2 + nlab.str() + "\n" );
                            }
                        }
                        imac->second.first = data;
                    }
                    // Trata os parametros
                    if(imac->second.second != "")
                    {
                        getline(iss,waux,' ');
                        data = imac->second.first;
                        param = " " + imac->second.second + " ";
                        while(data.find(param) != string::npos)
                        {
                            data.replace( data.find(param), param.length(), " " + waux  + " " );
                        }
                        param = " " + imac->second.second + "\n";
                        while(data.find(param) != string::npos)
                        {
                            data.replace( data.find(param), param.length(), " " + waux  + "\n" );
                        }
                    }
                    fout << data;
                }
                else
                {
                    fout << line << endl;
                }
            }
        }
    }
    fin.close();
    fout.close();
}


void print_macro(macro_t macro)
{
    macro_i imac;
    for (imac = macro.begin(); imac != macro.end(); imac++)
    {
        cout << "Nome: " << imac->first << endl;
        cout << "Codigo: " << imac->second.first << endl;
        cout << "Paramtero: " << imac->second.second << endl;
    }
}
