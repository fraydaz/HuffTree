#pragma once
#include <iostream>
#include <string>
//using std::string;
//using std::ostream;
using namespace std;

template <typename T, typename U>
class HuffmanNode {
private:
	int frequency;
	T value;
	U code;
	HuffmanNode<T, U>* left, *right;
public:
	HuffmanNode<T, U>() :
		value(' '), frequency(0), left(nullptr), right(nullptr) {}
	/*------------------------------------------------------------*/

	HuffmanNode<T, U>(T v, U i) :
		value(v), frequency(i), left(nullptr), right(nullptr) {}
	/*------------------------------------------------------------*/
	// Construct parent node with sum of childrens' frequencies
	HuffmanNode<T, U>(HuffmanNode<T, U>* left, HuffmanNode<T, U>* right)
	{
		this->left = left;
		this->right = right;
		frequency = left->getFrequency() + right->getFrequency();
		value = NULL;
	}
	/*------------------------------------------------------------*/
	HuffmanNode<T, U>(const HuffmanNode<T, U>& rhs)
	{
		//cout << "in copy constructor copying: " << rhs.letter << endl;

		if (rhs.left != NULL) {
			left = new HuffmanNode();
			*left = *(rhs.left);
		}
		if (rhs.right != NULL) {
			right = new HuffmanNode();
			*right = *(rhs.right);
		}
		code = rhs.code;
		value = rhs.value;
		frequency = rhs.frequency;
	}
	/*------------------------------------------------------------*/
	~HuffmanNode<T, U>()
	{
		if (left != nullptr)
			delete left;
		if (right != nullptr)
			delete right;
	}
	/*------------------------------------------------------------*/
	int getFrequency() { return frequency; };
	/*------------------------------------------------------------*/
	T getValue() { return value; };
	/*------------------------------------------------------------*/
	U getCode() { return code; };
	/*------------------------------------------------------------*/
	HuffmanNode<T, U>* getLeft() { return left; };
	/*------------------------------------------------------------*/
	HuffmanNode<T, U>* getRight() { return right; };
	/*------------------------------------------------------------*/

	void setHuffmanCode(string s) { code = s; }
	/*------------------------------------------------------------*/
	friend ostream& operator<<(ostream& os, const HuffmanNode<T, U>& rhs)
	{
		os << "\'" << rhs.value << " " << rhs.frequency << "\' ";
		return os;
	}
	/*------------------------------------------------------------*/
	HuffmanNode<T, U>& operator=(const HuffmanNode<T, U>& rhs)
	{
		//cout << "In assigbnment operator overload." << endl;
		if (!(this == &rhs)) {
			//copy
			code = rhs.code;
			value = rhs.value;
			frequency = rhs.frequency;
			if (!(left == NULL)) delete left;
			if (!(right == NULL)) delete right;

			if (rhs.left != NULL) {
				left = new HuffmanNode();
				*left = *(rhs.left);
				if (rhs.right != NULL) {
					right = new HuffmanNode();
					*right = *(rhs.right);
				}
			}
			else left = right = NULL;
		}
		return *this;
	}
};

