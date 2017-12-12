#pragma once
#include "HuffmanNode.h"
using namespace std;

template <typename T>
class HuffTree 
{
	private:
		template <typename T, typename U>
		HuffmanNode<T, U>** storage;
		int treeSize;
		int capacity;

		void percUp(int curIndex)
		{
			int parentIndex;
			HuffmanNode<T>* temp;
			if (curIndex != 0) { //are we at the "top"?
				parentIndex = (curIndex - 1) / 2;
				//min tree
				if (storage[parentIndex]->getFrequency() > storage[curIndex]->getFrequency()) {
					temp = storage[parentIndex];
					storage[parentIndex] = storage[curIndex];
					storage[curIndex] = temp;
					percUp(parentIndex);
				}
			}
		}
	/*------------------------------------------------------------*/
	void percDown(int curIndex)
	{
		int children = 0;
		if (children = numChildren(curIndex))
		{ //are we at the "bottom"?
			HuffmanNode<T>* temp;
			int left = 2 * curIndex + 1, right = 2 * curIndex + 2;
			switch (children)
			{ //1 child or 2 children
			case 1:
				//if the child is smaller, perk the current node down
				if (storage[curIndex]->getFrequency() > storage[left]->getFrequency())
				{
					temp = storage[curIndex];
					storage[curIndex] = storage[left];
					storage[left] = temp;
					percDown(left);
				}
				break;
			case 2:
				//2 children, determine which is smaller, perk down that direction
				if ((storage[curIndex]->getFrequency() > storage[left]->getFrequency()) ||
					(storage[curIndex]->getFrequency() > storage[right]->getFrequency()))
				{
					//left child is smaller
					if ((storage[left]->getFrequency() < storage[right]->getFrequency()))
					{
						temp = storage[curIndex];
						storage[curIndex] = storage[left];
						storage[left] = temp;
						percDown(left);
					}
					else
					{ //right child is smaller
						temp = storage[curIndex];
						storage[curIndex] = storage[right];
						storage[right] = temp;
						percDown(right);
					}
				}
				break;
			default:
				//cout << "wtf? this shouldn't happen" << endl;
				break;
			}
		}
		return;
	}
	/*------------------------------------------------------------*/
	int numChildren(int index)
	{
		int children = 0, left = 2 * index + 1, right = 2 * index + 2;
		if (left >= treeSize) return 0;
		if (storage[left] != NULL) children++;
		if (storage[right] != NULL) children++;
		return children;
	}
	/*------------------------------------------------------------*/
public:
	HuffTree<T>(int size)
	{
		capacity = size;
		treeSize = 0;
		storage = new HuffmanNode<T>*[capacity];
		for (int i = 0; i < capacity; i++)
		{
			storage[i] = NULL;
		}
	}
	/*------------------------------------------------------------*/
	~HuffTree<T>()
	{
		if (storage != NULL)
		{
			for (int i = 0; i < capacity; i++)
			{
				if (storage[i] != NULL)
				{
					delete storage[i];
					treeSize--;
				}
			}
			delete[] storage;
			//for debug purposes
			//cout << "tree size is (should be zero): " << treeSize << endl;
		}
	}
	/*------------------------------------------------------------*/
	template <typename T, typename U>
	void insert(HuffmanNode<T, U>* rhs)
	{
		if (treeSize == capacity) {
			cerr << "No more room in this tree!" << endl;
			return;
		}

		//insert at end
		treeSize++;
		storage[treeSize - 1] = rhs;
		percUp(treeSize - 1);
	}
	/*------------------------------------------------------------*/
	template <typename T, typename U>
	HuffmanNode<T, U>* removeMin()
	{
		HuffmanNode<T, U>* value = new HuffmanNode<T>();
		*value = *storage[0];
		//replace min with last filled node slot (treeSize-1)
		//perc down
		HuffmanNode<T, U>* temp = storage[0];
		storage[0] = storage[treeSize - 1];
		storage[treeSize - 1] = temp;
		delete storage[treeSize - 1]; //free
		storage[treeSize - 1] = NULL; //avoid dangling pointers
		treeSize--;
		percDown(0);
		return value;
	}
	/*------------------------------------------------------------*/
	template <typename T, typename U>
	HuffmanNode<T, U> peekMin()
	{
		return *storage[0];
	}
	/*------------------------------------------------------------*/

	bool isEmpty()
	{
		return (treeSize == 0);
	}
	/*------------------------------------------------------------*/
	int getTreeSize() { return treeSize; };
	template <typename T, typename U>
	HuffmanNode<T, U>* getRoot() { return storage[0]; };
};
