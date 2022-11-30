

#include "naglowki.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

std::ofstream tlumaczenie("tlumaczenie.txt");



void morse_do_ascii(std::string litera){//, int& iteracja, int dlugosc_litery) { //o dziwo jest szybsze mimo ze zajmuje 6 razy tyle miejsca
    
    
    if(litera[0]=='.'){
        if (litera[1] == '.') {
            if (litera[2] == '.') {
                if (litera[3] == '.') {
                    if (litera[4] == '.') {
                        tlumaczenie << "5";
                        return;
                    }
                    else if (litera[4] == '-') {
                        tlumaczenie << "4";
                        return;
                    }
                    tlumaczenie << "h";
                    return;
                }
                else if (litera[3] == '-') {
                    if (litera[4] == '-') {
                        tlumaczenie << "3";
                        return;
                    }
                    tlumaczenie << "v";
                    return;
                }
                tlumaczenie << "s";
                return;

            }
            else if (litera[2] == '-') {
                if (litera[3] == '.') {
                    tlumaczenie << "f";
                    return;
                }
                else if (litera[3] == '-' && litera[4]=='-') {
                    tlumaczenie << "2";
                    return;
                }
                tlumaczenie << "u";
                return;
            }
            tlumaczenie << "i";
            return;
        }
        else if (litera[1] == '-') {
            if (litera[2] == '.') {
                if (litera[3] == '.') {
                    tlumaczenie << 'l';
                    return;
                }
                tlumaczenie << 'r';
                return;
            }
            else if (litera[2] == '-') {
                if (litera[3] == '.') {
                    tlumaczenie << 'p';
                    return;
                }
                else if (litera[3] == '-') {
                    if (litera[4] == '-') {
                        tlumaczenie << '1';
                        return;
                    }
                    tlumaczenie << 'j';
                    return;
                }
                tlumaczenie << 'w';
                return;
            }
            tlumaczenie << "a";
            return;
        }
        tlumaczenie << "e";
        return;
    }                  
    else if (litera[0] == '-') {
        if (litera[1] == '.') {
            if (litera[2] == '.') {
                if (litera[3] == '.') {
                    if (litera[4] == '.') {
                        tlumaczenie << '6';
                        return;
                    }
                    tlumaczenie << 'b';
                    return;
                }
                else if (litera[3] == '-') {
                    tlumaczenie << 'x';
                    return;
                }
                tlumaczenie << 'd';
                return;
            }
            else if (litera[2] == '-') {
                if (litera[3] == '.') {
                    tlumaczenie << 'c';
                    return;
                }
                else if (litera[3] == '-') {
                    tlumaczenie << 'y';
                    return;
                }
                tlumaczenie << 'k';
                return;
            }
            tlumaczenie << 'n';
            return;
        }
        else if (litera[1] == '-') {
            if (litera[2] == '.') {
                if (litera[3] == '.') {
                    if (litera[4] == '.') {
                        tlumaczenie << '7';
                        return;
                    }
                    tlumaczenie << 'z';
                    return;
                }
                else if (litera[3] == '-') {
                    tlumaczenie << 'q';
                    return;
                }
                tlumaczenie << 'g';
                return;
            }
            else if (litera[2] == '-') {    //3 kreski
                if (litera[3] == '.'&&litera[4]=='.') {     ///---.
                    tlumaczenie << '8';
                    return;
                }
                else if (litera[3] == '-') {    //----
                    if (litera[4] == '.') {
                        tlumaczenie << '9';
                        return;
                    }
                    else if (litera[4] == '-') {
                        tlumaczenie << '0';
                        return;
                    }
                }
                tlumaczenie << 'o';
                return;
            }
            tlumaczenie << 'm';
            return;
        }
        tlumaczenie << 't';
        return;
    }
    //else {tlumaczenie << ' ';}
    
    

}

void morse_do_ascii2(std::string litera) {
    
    if (litera == ".-") { tlumaczenie << "a";  }
    else if (litera == "-...")  {tlumaczenie << "b"; }
    else if (litera == "-.-.")  {tlumaczenie << "c";  }
    else if (litera == "-..")   {tlumaczenie << "d";  }
    else if (litera == ".")     {tlumaczenie << "e";  }
    else if (litera == "..-.")  {tlumaczenie << "f";  }
    else if (litera == "--.")   {tlumaczenie << "g";  }
    else if (litera == "....")  {tlumaczenie << "h";  }
    else if (litera == "..")    {tlumaczenie << "i";  }
    else if (litera == ".---")  {tlumaczenie << "j";  }
    else if (litera == "-.-")   {tlumaczenie << "k";  }
    else if (litera == ".-..")  {tlumaczenie << "l";  }
    else if (litera == "--")    {tlumaczenie << "m";  }
    else if (litera == "-.")    {tlumaczenie << "n";  }
    else if (litera == "---")   {tlumaczenie << "o";  }
    else if (litera == ".--.")  {tlumaczenie << "p";  }
    else if (litera == "--.-")  {tlumaczenie << "q";  }
    else if (litera == ".-.")   {tlumaczenie << "r";  }
    else if (litera == "...")   {tlumaczenie << "s";  }
    else if (litera == "-")     {tlumaczenie << "t";  }
    else if (litera == "..-")   {tlumaczenie << "u";  }
    else if (litera == "...-")  {tlumaczenie << "v";  }
    else if (litera == ".--")   {tlumaczenie << "w";  }
    else if (litera == "-..-")  {tlumaczenie << "x";  }
    else if (litera == "-.--")  {tlumaczenie << "y";  }
    else if (litera == "--..")  {tlumaczenie << "z";  }
    else if (litera == "-----") {tlumaczenie << "0";  }
    else if (litera == ".----") {tlumaczenie << "1";  }
    else if (litera == "..---") {tlumaczenie << "2";  }
    else if (litera == "...--") {tlumaczenie << "3";  }
    else if (litera == "....-") {tlumaczenie << "4";  }
    else if (litera == ".....") {tlumaczenie << "5";  }
    else if (litera == "-....") {tlumaczenie << "6";  }
    else if (litera == "--...") {tlumaczenie << "7";  }
    else if (litera == "---..") {tlumaczenie << "8";  }
    else if (litera == "----.") {tlumaczenie << "9";  }
    
}

void  ascii_do_morse(char znak) {
    switch(znak){
        case'a':
        case'A':    tlumaczenie << ".- ";       break;
        case'b':
        case'B':    tlumaczenie << "-... ";     break;
        case'c':
        case'C':    tlumaczenie << "-.-. ";     break;
        case 'd':
        case 'D':   tlumaczenie << "-.. ";      break;
        case 'e':
        case 'E':   tlumaczenie << ". ";        break;
        case 'f':
        case 'F':   tlumaczenie << "..-. ";     break;
        case 'g':
        case 'G':   tlumaczenie << "--. ";      break;
        case 'h':
        case 'H':   tlumaczenie << ".... ";     break;
        case 'i':
        case 'I':   tlumaczenie << ".. ";       break;
        case 'j':
        case 'J':   tlumaczenie << ".--- ";     break;
        case 'k':
        case 'K':   tlumaczenie << "-.- ";      break;
        case 'l':
        case 'L':   tlumaczenie << ".-.. ";     break;
        case 'm':
        case 'M':   tlumaczenie << "-- ";       break;
        case 'n':
        case 'N':   tlumaczenie << "-. ";       break;
        case 'o':
        case 'O':   tlumaczenie << "--- ";      break;
        case 'q':
        case 'Q':   tlumaczenie << "--.- ";     break;
        case 'p': 
        case 'P':   tlumaczenie << ".--. ";     break;
        case 'r':
        case 'R':   tlumaczenie << ".-. ";      break;
        case 's':
        case 'S':   tlumaczenie << "... ";      break;
        case 't':
        case 'T':   tlumaczenie << "- ";        break;
        case 'u':
        case 'U':   tlumaczenie << "..- ";      break;
        case 'v':
        case 'V':   tlumaczenie << "...- ";     break;
        case 'w':
        case 'W':   tlumaczenie << ".-- ";      break;
        case 'x':
        case 'X':   tlumaczenie << "-..- ";     break;
        case 'y':
        case 'Y':   tlumaczenie << "-.-- ";     break;
        case 'z':
        case 'Z':   tlumaczenie << "--.. ";     break;
        case '0':   tlumaczenie << "----- ";    break;
        case '1':   tlumaczenie << ".---- ";    break;
        case '2':   tlumaczenie << "..--- ";    break;
        case '3':   tlumaczenie << "...-- ";    break;
        case '4':   tlumaczenie << "....- ";    break;
        case '5':   tlumaczenie << "..... ";    break;
        case '6':   tlumaczenie << "-.... ";    break;
        case '7':   tlumaczenie << "--... ";    break;
        case '8':   tlumaczenie << "---.. ";    break;
        case '9':   tlumaczenie << "----. ";    break;
    }
}

