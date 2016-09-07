#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
	bool process = true; // true for encrypt, false for decrypt
	bool keytype = true; // true for binary, false for hex
	int counter = 0;
	string keyfile = "key.txt";
	string keyline;
	if (argc > 1)
	{
		counter = 1;
		
		string comptemp = string(argv[counter]);
		size_t found = comptemp.find("-k<");
		while (counter < argc)
		{
			if ((comptemp)== "-d")
			{
				process = false;
			}
			if ((comptemp) == "-e")
			{
				process = true;
			}
			if ((comptemp) == "-x")
			{
				keytype = false;
			}
			if ((comptemp) == "-b")
			{
				keytype = true;
			}
			if (found != string::npos)
			{
				//keyfile = comptemp.substr(3,comptemp.size() - 2);
			}	
			counter++;
		}
	}
	
	string keypos = keyfile;
	ifstream key;
	key.open ("key.txt");
	getline(key, keyline);
	//keyline = "0f1e2d3c4b5a6978";
	
	int ui = getchar();
	vector<char> useri;
	vector<char> usero;
	while (ui != EOF) // reads inputstream and fills input string with chosen input
	{
		useri.push_back(ui);
		ui = getchar();
	}
	
	
	if (process) // encryption
	{
		counter = 0;
		while ((unsigned)counter < useri.size())
		{
			int numval = +useri.at(counter);  
			int remain = numval % 16; 
			numval = numval - remain;  
			numval = numval / 16;
			char charval = keyline.at(numval);
			char charrem = keyline.at(remain);
			usero.push_back(charval);
			usero.push_back(charrem);
			usero.push_back(' '); 
			
			
			counter++;
		}
	}

	else //decryption
	{
		counter = 0;
		while ((unsigned)counter < useri.size())
		{
			char charvald = useri.at(counter);
			char charremd = useri.at(counter+1);
			if ((((+charvald < 58) && (+charvald > 47)) || ((+charvald < 103) && (+charvald > 96))) && (((+charremd < 58) && (+charremd > 47)) || ((+charremd < 103) && (+charremd > 96))))
			{
				size_t keysearch = keyline.find(charvald);
				if (keysearch > 9)
				{
					switch (keysearch) 
					{
						case 10: usero.push_back('a'); break;
						case 11: usero.push_back('b'); break;
						case 12: usero.push_back('c'); break;
						case 13: usero.push_back('d'); break;
						case 14: usero.push_back('e'); break;
						case 15: usero.push_back('f'); break;
					}
				}
				else
				{
					char conv = keysearch + '0';
					usero.push_back(conv);
				}
				keysearch = keyline.find(charremd);
				if (keysearch > 9)
				{
					switch (keysearch) 
					{
						case 10: usero.push_back('a'); break;
						case 11: usero.push_back('b'); break;
						case 12: usero.push_back('c'); break;
						case 13: usero.push_back('d'); break;
						case 14: usero.push_back('e'); break;
						case 15: usero.push_back('f'); break;
					}
				}
				else
				{
					char conv = keysearch + '0';
					usero.push_back(conv);
				}
				usero.push_back(' ');
				
			}
			else // if input is not correct key value
			{
				cout << "input is not in hexidecimal format.";
				exit(1);
			}
			counter += 3;
		}
}
	counter = 0;
	while ((unsigned)counter < usero.size())
	{
		putchar(usero.at(counter));
		counter++;
		
	}
} 
