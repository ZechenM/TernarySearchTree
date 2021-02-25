//TST Header File

#ifndef TST_H
#define TST_H

#include <iostream>
#include <string>
#include <utility>
using namespace std;

class TST
{
private:
	struct Node
	{ //Node declaration
		pair<string, int> LeftKey;
		pair<string, int> RightKey;
		Node *left, *middle, *right, *parent;

		// node constructor
		Node()
		{
			LeftKey.first = "";
			RightKey.first = "~";
			LeftKey.second = RightKey.second = 0;
			left = middle = right = parent = nullptr;
		}
	};
	Node *root;													//root node
	void clear(Node *n);										//recursive helper for destructor
	void insert(string input, Node *n);							//recursive helper for insert
	Node *GetNodeFor(string input, Node *n) const;				//return the node for a given input
	void PrintInOrder(Node *n, string start, string end) const; //inorder traversal recursive helper
	Node *LeftPredecessorNode(string input) const;				// returns the Node containing the predecessor of the given value only for LeftKey
	pair<string, int> LeftPredecessor(string input) const;		// returns the predecessor value of the given value or 0 if there is none
	Node *LeftSuccessorNode(string input) const;				// returns the Node containing the successor of the given value
	pair<string, int> LeftSuccessor(string input) const;		// returns the successor value of the given value or 0 if there is none
	Node *RightPredecessorNode(string input) const;				// returns the Node containing the predecessor of the given value only for RightKey
	pair<string, int> RightPredecessor(string input) const;		// returns the predecessor value of the given value or 0 if there is none
	Node *RightSuccessorNode(string input) const;				// returns the Node containing the successor of the given value
	pair<string, int> RightSuccessor(string input) const;		// returns the successor value of the given value or 0 if there is none
	void DeleteNoPrint(string input);							//Delete function helper for Deleting successor/predecessor

public:
	TST();											  //Constructor
	~TST();											  //Destructor
	void lookup(string input) const;				  //a method for searching a word in the TST
	void insert(string input);						  //a function for inserting a new word into the TST
	void Delete(string input);						  //a function for deleting a word from the TST
	void RangeSearch(string start, string end) const; //a function for doing a range search
};

#endif