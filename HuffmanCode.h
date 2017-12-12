#pragma once
#include <string>
#include <map>
#include"HuffmanTree.h"
//using std::string;
//using std::map;
using namespace std;
//template <typename T, typename U> class HuffmanNode;
template <typename T> 
class HuffmanCode {
private:
	string data;
	string encodedData;
	HuffTree<T>* tree;
	map<char, int> frequencyTable;
	map<T, string> huffmanTable;
	/*------------------------------------------------------------*/
	// create frequency table with pairs of characters in string
	// and their frequency
	void buildTable()
	{
		for (size_t i = 0; i < data.length(); i++)
		{
			char c = data.at(i);
			// check if this character already exists in frequencyTable
			if (frequencyTable.find(data.at(i)) == frequencyTable.end())
			{
				// character not in map yet, insert character with frequency 1
				frequencyTable.insert(pair<char, int>(c, 1));
			}
			else
			{
				// already in map, increment frequency
				frequencyTable[c]++;
			}
		}
	}
	/*------------------------------------------------------------*/
	// create huffman tree using frequency table
	void buildTree()
	{
		//fill tree
		for (map<char, int>::iterator it = frequencyTable.begin();
			it != frequencyTable.end(); ++it)
		{
			tree->insert(new HuffmanNode<char, string>(it->first, it->second));
		}
		//pop off two at a time until you get one left
		while (!tree->isEmpty())
		{
			if (tree->getTreeSize() == 1)
				break;
			HuffmanNode<T>* left = tree->removeMin();
			HuffmanNode<T>* right = tree->removeMin();
			tree->insert(new HuffmanNode<T>(left, right));
		}
		//final one is the root of encoding tree
		string code = "";
		getHuffmanEncoding(tree->getRoot(), code);
		encode();
	}
	/*------------------------------------------------------------*/
	template <typename T, typename U>
	void getHuffmanEncoding(HuffmanNode<T, U>* root, string code)
	{
		if (root->getLeft() == NULL)
		{
			root->setHuffmanCode(code);
			huffmanTable.insert(pair<T, string>(root->getValue(), code));
			return;
		}
		else
		{
			getHuffmanEncoding(root->getLeft(), code + "0");
			getHuffmanEncoding(root->getRight(), code + "1");
		}
	}
	/*------------------------------------------------------------*/
	void encode()
	{
		for (size_t i = 0; i < data.length(); i++)
		{
			encodedData.append(huffmanTable[data.at(i)]);
			encodedData.append(" ");
		}
	}
	/*------------------------------------------------------------*/
public:
	HuffmanCode<T>(T input)
	{
		data = input;
		encodedData = "";
		// create tree to be large enough for worst case
		tree = new HuffTree<T>(data.length());
		buildTable();
		buildTree();
	}
	/*------------------------------------------------------------*/
	~HuffmanCode<T>()
	{
		if (tree != nullptr)
			delete tree;
	}
	/*------------------------------------------------------------*/
	T getSourceString() { return data; };
	string getEncodedString() { return encodedData; };
	/*------------------------------------------------------------*/
	void displayTable()
	{
		cout << "Frequency Table:" << endl;
		for (map<char, int>::iterator it = frequencyTable.begin();
			it != frequencyTable.end(); ++it)
		{
			cout << it->first << "\t" << it->second << endl;
		}
	}
	/*------------------------------------------------------------*/
	void displayHuffmanTable()
	{
		cout << "Huffman Table:" << endl;
		for (typename map<T, string>::iterator it = huffmanTable.begin();
			it != huffmanTable.end(); ++it)
		{
			cout << it->first << "\t" << it->second << endl;
		}
	}
	/*------------------------------------------------------------*/
	string decodeString(string src)
	{
		string info = "";
		size_t lastBlock = 0;
		for (size_t i = 0; i < src.length(); i++) {
			if (src.at(i) == ' ') {
				string temp = src.substr(lastBlock, i - lastBlock);
				lastBlock = i + 1;
				for (typename map<T, string>::iterator it = huffmanTable.begin();
					it != huffmanTable.end(); ++it) {
					if (it->second == temp) {
						info += (it->first);
						break;
					}
				}
			}
		}
		return info;
	}
};