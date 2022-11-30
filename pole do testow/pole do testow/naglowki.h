//#pragma once

#include<string>
//#include<iostream>

#ifndef NAGLOWKI_H
#define NAGLOWKI_H



/** Funkcja t³umaczy podany jej tekst z alfabetu morsea na ascii
 * @param litera pobierana ze stringa litera podana w kodzie morsea 
 */
void morse_do_ascii(std::string litera);// , int iteracja, int dlugosc_litery);
void morse_do_ascii2(std::string litera);
/** Funkcja t³umaczy podany jej tekst z ascii na alfabet morsea
 * @param litera pobierana ze stringa litera
 */
void  ascii_do_morse(char znak);

#endif
