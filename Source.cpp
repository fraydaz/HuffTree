#include <iostream>
#include <string>
#include "HuffmanCode.h"
using namespace std;

int main()
{

	string text;
	cout << "Enter some text:\n";
	getline(cin, text);
	HuffmanCode<string>* huffText = new HuffmanCode<string>(text);

	huffText->displayTable();
	huffText->displayHuffmanTable();

	string code = huffText->getEncodedString();
	cout << "Encoded string: " << code << endl << endl;
	cout << "Decoded string: " << huffText->decodeString(code) << endl << endl;

	delete huffText;

	return 0;
}