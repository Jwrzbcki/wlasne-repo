
#include <iostream>


int main()
{
	std::string sznur;
	std::cout << "jakie liczby odwracasz\n";
	std::cin >> sznur;
	char przechowalnia;
	
	if ((sznur.length() % 2) == 0)
	{
		for (int i = 1; i <= (sznur.length() / 2); i++)
		{
			int liczba = i - 1;
			przechowalnia = sznur[liczba];
			sznur[liczba] = sznur[(sznur.length() - i)];
			sznur[(sznur.length() - i)] = przechowalnia;
		}

	}
	else
	{
		for (int i = 1; i <= ((sznur.length()-1) / 2); i++)
		{
			int liczba = i - 1;
			przechowalnia = sznur[liczba];
			sznur[liczba] = sznur[(sznur.length() - i)];
			sznur[(sznur.length() - i)] = przechowalnia;
		}
	}
	std::cout <<"\n"<< sznur << " :zsacarwdo ybzcil eikaj \n";
	


}


