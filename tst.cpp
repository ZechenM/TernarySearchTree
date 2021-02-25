//TST Implementation

#include "tst.h"

// constructor sets up empty tree
TST::TST()
{
	root = nullptr;
}

// destructor deletes all nodes
TST::~TST()
{
	clear(root);
}

// recursive helper for destructor
void TST::clear(TST::Node *n)
{
	if (n)
	{
		clear(n->left);
		clear(n->middle);
		clear(n->right);
		delete n;
	}
}

//a method for searching a word in the TST
void TST::lookup(string input) const
{
	Node *n = root;
	while (n)
	{
		if (input == n->LeftKey.first)
		{
			cout << input << " found, count = " << n->LeftKey.second << endl;
			return;
		}
		else if (input == n->RightKey.first)
		{
			cout << input << " found, count = " << n->RightKey.second << endl;
			return;
		}
		else if (input < n->LeftKey.first)
		{
			n = n->left;
		}
		else if (input > n->LeftKey.first && input < n->RightKey.first)
		{
			n = n->middle;
		}
		else if (input > n->RightKey.first)
		{
			n = n->right;
		}
	}
	cout << input << " not found" << endl;
}

//insert a new node if the word is not present, set its counter to 1
//otherwise, increment the counter by one
void TST::insert(string input)
{ 
	// handle special case of empty tree first
	if (!root)
	{
		root = new Node;
		root->LeftKey.first = input;
		root->LeftKey.second = 1;
		cout << input << " inserted, new count = " << 1 << endl;
		return;
	}

	// otherwise use recursive helper
	return insert(input, root);
}

//recursive helper for insert
void TST::insert(string input, Node *n)
{
	//increment LeftKey counter by one
	if (input == n->LeftKey.first)
	{
		n->LeftKey.second = n->LeftKey.second + 1;
		cout << input << " inserted, new count = " << n->LeftKey.second << endl;
		return;
	}
	//increment RightKey counter by one
	else if (input == n->RightKey.first)
	{
		n->RightKey.second = n->RightKey.second + 1;
		cout << input << " inserted, new count = " << n->RightKey.second << endl;
		return;
	}
	// if input value is less than the LeftKey
	else if (input < n->LeftKey.first)
	{
		// first check if RightKey is empty or not
		if (n->RightKey.second != 0)
		{
			// RightKey is not empty
			// Check the left subtree
			if (n->left)
			{
				//left subtree is not empty either
				//apply the algorithm recursively
				return insert(input, n->left);
			}
			else
			{
				//left subtree is empty
				n->left = new Node;
				n->left->parent = n;
				n->left->LeftKey.first = input;
				n->left->LeftKey.second = 1;
				cout << input << " inserted, new count = " << 1 << endl;
				return;
			}
		}
		//if RightKey is empty
		else
		{
			//move the current LeftKey to become RightKey
			n->RightKey = n->LeftKey;
			//Assign the new input in LeftKey
			n->LeftKey.first = input;
			n->LeftKey.second = 1;
			//print the output
			cout << input << " inserted, new count = " << 1 << endl;
			return;
		}
	}
	//if input is greater than the LeftKey
	else if (input > n->LeftKey.first)
	{
		//first check if RightKey is empty
		if (n->RightKey.second == 0)
		{
			// RightKey is empty, insert the input in RightKey
			n->RightKey.first = input;
			n->RightKey.second = 1;
			//print the output
			cout << input << " inserted, new count = " << 1 << endl;
			return;
		}
		//Rightkey is not empty
		else
		{
			//if input is less than the RightKey
			if (input < n->RightKey.first)
			{
				//check the middle subtree empty or not
				if (n->middle)
				{
					//middle subtree is not empty
					//call the middle subtree recursively
					return insert(input, n->middle);
				}
				else
				{
					//middle subtree is empty
					n->middle = new Node;
					n->middle->parent = n;
					n->middle->LeftKey.first = input;
					n->middle->LeftKey.second = 1;
					cout << input << " inserted, new count = " << 1 << endl;
					return;
				}
			}
			//otherwise, it must > RightKey
			else
			{
				//if right subtree is not empty
				if (n->right)
				{
					//call the right subtree recursively
					return insert(input, n->right);
				}
				else
				{
					//right subtree is empty
					n->right = new Node;
					n->right->parent = n;
					n->right->LeftKey.first = input;
					n->right->LeftKey.second = 1;
					cout << input << " inserted, new count = " << 1 << endl;
					return;
				}
			}
		}
	}
}

//search and return a node by the given input
TST::Node *TST::GetNodeFor(string input, Node *n) const
{
	n = root;
	while (n)
	{
		if (input == n->LeftKey.first || input == n->RightKey.first)
		{
			return n;
		}
		else if (input < n->LeftKey.first)
		{
			n = n->left;
		}
		else if (input > n->LeftKey.first && input < n->RightKey.first)
		{
			n = n->middle;
		}
		else if (input > n->RightKey.first)
		{
			n = n->right;
		}
	}
	return nullptr;
}

//Return the predecessor node for the LeftKey
TST::Node *TST::LeftPredecessorNode(string input) const
{
	Node *p = GetNodeFor(input, root);
	//cannot find the node
	if (p == nullptr)
	{
		return nullptr;
	}
	else
	{ //can find the predecessor
		if (p->left != nullptr)
		{ //go left
			p = p->left;
			//go right...
			while (p->right != nullptr)
			{
				p = p->right;
			}
			return p;
		}
		//no left subtree, cannot go left, no predecesssor
		else
			return nullptr;
	}
}

//return the Predecessor word and count
//shoud be a rightkey
pair<string, int> TST::LeftPredecessor(string input) const
{
	pair<string, int> empty("", 0);
	Node *p = LeftPredecessorNode(input);

	if (p == nullptr)
	{ //either there is no node with the give input
		//or cannot find the predecessor
		return empty;
	}
	else
	{ //if rightkey exists, return the rightkey of the predecessor node
		if (p->RightKey.second != 0)
		{
			return p->RightKey;
		}
		//otherwise, can only return the leftkey
		//rightkey does not exist => leaf node
		else
		{
			return p->LeftKey;
		}
	}
}

//return the successor node for leftkey
TST::Node *TST::LeftSuccessorNode(string input) const
{
	Node *s = GetNodeFor(input, root);
	//cannot find
	if (s == nullptr)
	{
		return nullptr;
	}
	else
	{ //leftkey sucessor should be in middle subtree
		if (s->middle != nullptr)
		{
			s = s->middle;
			while (s->left != nullptr)
			{
				s = s->left;
			}
			return s;
		}
		else
		{ //cannot find successor
			return nullptr;
		}
	}
}

//leftkey successor pair
pair<string, int> TST::LeftSuccessor(string input) const
{
	Node *s = LeftSuccessorNode(input);
	pair<string, int> empty("", 0);
	if (s == nullptr)
	{ //no node OR no successor
		return empty;
	}
	else
	{ //if the node exists, it must have leftkey initialized
		return s->LeftKey;
	}
}

//RightKeyPredecessorNode
TST::Node *TST::RightPredecessorNode(string input) const
{
	Node *p = GetNodeFor(input, root);
	if (p == nullptr)
	{ //cannot find node
		return nullptr;
	}
	else
	{ //predecessor is in middle subtree
		if (p->middle != nullptr)
		{
			p = p->middle;
			while (p->right)
			{ //go right
				p = p->right;
			}
			return p;
		}
		else
		{ //no predecessor
			return nullptr;
		}
	}
}

//RightKeyPredecessorPair
pair<string, int> TST::RightPredecessor(string input) const
{
	Node *p = RightPredecessorNode(input);
	pair<string, int> empty("", 0);
	if (p == nullptr)
	{ //no node OR no predecessor
		return empty;
	}
	else
	{
		//if rightkey exists, return it
		if (p->RightKey.second != 0)
		{
			return p->RightKey;
		}
		else
		{
			//no rightkey => leaf node
			return p->LeftKey;
		}
	}
}

//RightKeySuccessorNode
TST::Node *TST::RightSuccessorNode(string input) const
{
	Node *s = GetNodeFor(input, root);
	if (!s)
	{
		return nullptr;
	}
	else
	{ //successor is in the right subtree
		if (s->right)
		{
			s = s->right;
			while (s->left)
			{ //go left
				s = s->left;
			}
			return s;
		}
		else
		{ //no successor
			return nullptr;
		}
	}
}

//RightKeySuccessorValue
pair<string, int> TST::RightSuccessor(string input) const
{
	Node *s = RightSuccessorNode(input);
	pair<string, int> empty("", 0);
	if (!s)
	{ //no node OR successor
		return empty;
	}
	else
	{
		return s->LeftKey;
	}
}

//Delete the successor or the predecessor but do not print anything
void TST::DeleteNoPrint(string input)
{
	Node *n = GetNodeFor(input, root);
	//if the node does not exist in the tree
	//print nothing
	if (!n)
	{
		return;
	}
	Node *p = n->parent;
	//if input is the leftkey
	if (n->LeftKey.first == input)
	{
		//successor/predecessor deletion, count does not matter
		//if it is a leaf node
		if (n->left == nullptr && n->middle == nullptr && n->right == nullptr)
		{
			//if it has RightKey, then we cannot delete this node
			if (n->RightKey.second != 0)
			{
				//instead, we should assign RightKey to LeftKey
				n->LeftKey.first = n->RightKey.first;
				n->LeftKey.second = n->RightKey.second;
				//reset RightKey
				n->RightKey.first = "~";
				n->RightKey.second = 0;
				//no print
				return;
			}
			//if no rightkey, delete this node
			else
			{
				//n cannot be the root. This is deletion for successor and predecessor
				//where we have to be able to find successor/predecessor first
				if (p->left == n)
				{
					p->left = nullptr;
				}
				else if (p->middle == n)
				{
					p->middle = nullptr;
				}
				else if (p->right == n)
				{
					p->right = nullptr;
				}

				delete n;
				//no print
				return;
			}
		}
		//if it is not leaf node, no way to delete the node because it has both left and right key
		//to remove left key
		//find its predecessor/successor
		else
		{
			if (n->left)
			{ //stash predecessor
				string tmp1 = LeftPredecessor(input).first;
				int tmp2 = LeftPredecessor(input).second;
				//delete predecessor recursively...
				DeleteNoPrint(tmp1);
				//swap leftkey with its predecessor
				n->LeftKey.first = tmp1;
				n->LeftKey.second = tmp2;
				//no print
				return;
			}
			else if (n->middle)
			{

				//stash successor
				string tmp3 = LeftSuccessor(input).first;
				int tmp4 = LeftSuccessor(input).second;
				//delete successor recursively...
				DeleteNoPrint(tmp3);
				//swap leftkey with its successor
				n->LeftKey.first = tmp3;
				n->LeftKey.second = tmp4;
				//no print
				return;
			}
			else if (n->right)
			{
				//stash n's rightkey successor
				//n->LeftKey.first == input
				string NewInput = n->RightKey.first;
				string tmp5 = RightSuccessor(NewInput).first;
				int tmp6 = RightSuccessor(NewInput).second;
				//delete n's rightkey successor recursively...
				DeleteNoPrint(tmp5);
				//In this case, leftkey doesn't have left/middle subtree
				//its successor is the rightkey
				//assign right to left key
				n->LeftKey.first = n->RightKey.first;
				n->LeftKey.second = n->RightKey.second;
				//swap right with successor
				n->RightKey.first = tmp5;
				n->RightKey.second = tmp6;
				//no print
				return;
			}
		}
	}
	//input is the rightkey
	else
	{
		//successor/predecessor deletion, counter doesn't matter

		//if it is a leaf node
		if (n->left == nullptr && n->middle == nullptr && n->right == nullptr)
		{
			//it must have a leftkey, so reset rightkey
			n->RightKey.first = "~";
			n->RightKey.second = 0;
			//no print
			return;
		}
		//if not a leaf node, find predecessor/successor
		else
		{
			if (n->right)
			{
				//stash successor
				string tmp1_1 = RightSuccessor(input).first;
				int tmp2_2 = RightSuccessor(input).second;
				//delete successor recursively...
				DeleteNoPrint(tmp1_1);
				//swap righttkey with its successor
				n->RightKey.first = tmp1_1;
				n->RightKey.second = tmp2_2;
				//no print
				return;
			}
			else if (n->middle)
			{
				//stash predecessor
				string tmp3_3 = RightPredecessor(input).first;
				int tmp4_4 = RightPredecessor(input).second;
				//delete predecessor recursively
				DeleteNoPrint(tmp3_3);
				//swap rightkey with predecessor
				n->RightKey.first = tmp3_3;
				n->RightKey.second = tmp4_4;
				//no print
				return;
			}
			else if (n->left)
			{
				//stash n's leftkey predecessor
				//n->RightKey.first == input
				string AnoInput = n->LeftKey.first;
				string tmp5_5 = LeftPredecessor(AnoInput).first;
				int tmp6_6 = LeftPredecessor(AnoInput).second;
				//delete n's leftkey predecesoor recursively
				DeleteNoPrint(tmp5_5);
				//rightkey's predecessor is the leftkey
				//assign left to right key
				n->RightKey.first = n->LeftKey.first;
				n->RightKey.second = n->LeftKey.second;
				//swap left with predecessor
				n->LeftKey.first = tmp5_5;
				n->LeftKey.second = tmp6_6;
				//no print
				return;
			}
		}
	}
}

//Delete function
//print nothing if input does not exist
void TST::Delete(string input)
{
	Node *n = GetNodeFor(input, root);
	//if the node does not exist in the tree
	//print nothing
	if (!n)
	{
		return;
	}
	Node *p = n->parent;
	//if input is the leftkey
	if (n->LeftKey.first == input)
	{
		//decrement by 1 if counter > 1
		if (n->LeftKey.second > 1)
		{
			n->LeftKey.second -= 1;
			cout << input << " deleted, new count = " << n->LeftKey.second << endl;
			return;
		}
		//if count = 1
		else
		{
			//if it is a leaf node
			//only leaf nodes might not have a RightKey
			if (n->left == nullptr && n->middle == nullptr && n->right == nullptr)
			{
				//if it has RightKey, then we cannot delete this node
				if (n->RightKey.second != 0)
				{
					//instead, we should assign RightKey to LeftKey
					n->LeftKey.first = n->RightKey.first;
					n->LeftKey.second = n->RightKey.second;
					//reset RightKey
					n->RightKey.first = "~";
					n->RightKey.second = 0;
					//print
					cout << input << " deleted" << endl;
					return;
				}
				//if no rightkey, delete this node
				else
				{
					//if n is the root, it has no parent
					if (n == root)
					{
						root = nullptr;
					}
					//otherwise, it must be left/middle/right child
					else
					{
						if (p->left == n)
						{
							p->left = nullptr;
						}
						else if (p->middle == n)
						{
							p->middle = nullptr;
						}
						else if (p->right == n)
						{
							p->right = nullptr;
						}
					}
					delete n;
					cout << input << " deleted" << endl;
					return;
				}
			}
			//if it is not leaf node, no way to delete the node because it has both left and right key
			//to remove left key
			//find its predecessor/successor
			else
			{
				if (n->left)
				{ //stash predecessor
					string tmp1 = LeftPredecessor(input).first;
					int tmp2 = LeftPredecessor(input).second;
					//delete predecessor
					DeleteNoPrint(tmp1);
					//swap leftkey with its predecessor
					n->LeftKey.first = tmp1;
					n->LeftKey.second = tmp2;
					//print
					cout << input << " deleted" << endl;
					return;
				}
				else if (n->middle)
				{

					//stash successor
					string tmp3 = LeftSuccessor(input).first;
					int tmp4 = LeftSuccessor(input).second;
					//delete successor
					DeleteNoPrint(tmp3);
					//swap leftkey with its successor
					n->LeftKey.first = tmp3;
					n->LeftKey.second = tmp4;
					//print
					cout << input << " deleted" << endl;
					return;
				}
				else if (n->right)
				{
					//stash n's rightkey successor
					//Current Condition: n->LeftKey.first == input
					string NewInput = n->RightKey.first;
					string tmp5 = RightSuccessor(NewInput).first;
					int tmp6 = RightSuccessor(NewInput).second;
					//delete n's rightkey successor
					DeleteNoPrint(tmp5);
					//In this case, leftkey doesn't have left/middle subtree
					//its successor is the rightkey
					//assign right to left key
					n->LeftKey.first = n->RightKey.first;
					n->LeftKey.second = n->RightKey.second;
					//swap right with successor
					n->RightKey.first = tmp5;
					n->RightKey.second = tmp6;
					//print
					cout << input << " deleted" << endl;
					return;
				}
			}
		}
	}
	//input is the rightkey
	else
	{
		//decrement by 1 if counter > 1
		if (n->RightKey.second > 1)
		{
			n->RightKey.second -= 1;
			cout << input << " deleted, new count = " << n->RightKey.second << endl;
			return;
		}
		//if count = 1
		else
		{
			//if it is a leaf node
			if (n->left == nullptr && n->middle == nullptr && n->right == nullptr)
			{
				//it must have a leftkey, so reset rightkey
				n->RightKey.first = "~";
				n->RightKey.second = 0;
				//print
				cout << input << " deleted" << endl;
				return;
			}
			//if not a leaf node
			else
			{
				if (n->right)
				{
					//stash successor
					string tmp1_1 = RightSuccessor(input).first;
					int tmp2_2 = RightSuccessor(input).second;
					//delete successor
					DeleteNoPrint(tmp1_1);
					//swap rightkey with its successor
					n->RightKey.first = tmp1_1;
					n->RightKey.second = tmp2_2;
					//print
					cout << input << " deleted" << endl;
					return;
				}
				else if (n->middle)
				{
					//stash predecessor
					string tmp3_3 = RightPredecessor(input).first;
					int tmp4_4 = RightPredecessor(input).second;
					//delete predecessor
					DeleteNoPrint(tmp3_3);
					//swap rightkey with predecessor
					n->RightKey.first = tmp3_3;
					n->RightKey.second = tmp4_4;
					//print
					cout << input << " deleted" << endl;
					return;
				}
				else if (n->left)
				{
					//stash n's leftkey predecessor
					//Current Condition: n->RightKey.first == input
					string AnoInput = n->LeftKey.first;
					string tmp5_5 = LeftPredecessor(AnoInput).first;
					int tmp6_6 = LeftPredecessor(AnoInput).second;
					//delete n's leftkey predecesoor
					DeleteNoPrint(tmp5_5);
					//rightkey's predecessor is the leftkey
					//assign left to right key
					n->RightKey.first = n->LeftKey.first;
					n->RightKey.second = n->LeftKey.second;
					//swap left with predecessor
					n->LeftKey.first = tmp5_5;
					n->LeftKey.second = tmp6_6;
					//print
					cout << input << " deleted" << endl;
					return;
				}
			}
		}
	}
}

//in order traversal recursive helper
void TST::PrintInOrder(Node *n, string start, string end) const
{
	if (n)
	{
		PrintInOrder(n->left, start, end);
		if (n->LeftKey.first >= start && n->LeftKey.first <= end)
		{
			cout << n->LeftKey.first << endl;
		}
		PrintInOrder(n->middle, start, end);
		if (n->RightKey.first >= start && n->RightKey.first <= end)
		{
			cout << n->RightKey.first << endl;
		}
		PrintInOrder(n->right, start, end);
	}
}

void TST::RangeSearch(string start, string end) const
{
	PrintInOrder(root, start, end);
}
