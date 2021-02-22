#pragma once
#include "Node.h"
#include<iostream>
#include<vector>
#include<queue>

class AVLTree {

private:

	Node* root;
	int numOfNodes;

	bool isNameValid(std::string);
	bool isIDUnique(Node*, std::string);
	bool isIDValid(std::string);
	Node* insertHelper(Node*, Node*);
	std::vector<std::string> searchNameHelper(Node*, std::string);
	Node* removeIDHelper(Node*, std::string);
	Node* findInOrderSuccessor(Node*);
	Node* findIDnthNode(Node*, int);
	Node* traverseLeft(Node*);
	Node* removeIDHelperNoPrint(Node*, std::string);
	void removeIDNoPrint(Node*, std::string);
	std::queue<Node*> getChildren(Node*);
	std::queue<Node*> addChildrenToQ(std::queue<Node*>, std::queue<Node*>&);

public:

	AVLTree() { root = nullptr; numOfNodes = 0; }
	Node* getRoot() { return root; }
	int getNumOfNodes() { return numOfNodes; }
	void setRoot(Node* n) { root = n; }

	void insert(Node*, Node*);
	void removeID(Node*, std::string);
	void removeInOrderN(Node*, int);
	void searchID(Node*, std::string);
	void searchName(Node*, std::string);
	void printInOrder(Node*);
	void printPreorder(Node*);
	void printPostorder(Node*);
	void printLevelCount(Node*);

	int getBalanceFactor(Node*);
};

// Insert helper function to avoid recursion in the isIDValid part
// Inserts nodeInsert recursively into the tree. If the function is
// called, the insert values are valid.
Node* AVLTree::insertHelper(Node* nodeStart, Node* nodeInsert) {
	// If tree is empty, create root
	if (root == nullptr) {
		root = nodeInsert;
	}
	// If tree is not empty, recursively find the spot to insert node
	else {
		// Base case for recursion, which means the spot is found
		if (nodeStart == nullptr) {
			// Create node to insert
			return nodeInsert;
		}
		else {
			// If key is less than current node's key, insert to the left recursively
			if (stoi(nodeInsert->getID()) < stoi(nodeStart->getID())) {

				nodeStart->setLeft(insertHelper(nodeStart->getLeft(), nodeInsert));

				int balanceFactor = getBalanceFactor(nodeStart);
				bool balanceFactorInvalid = checkBalanceFactor(balanceFactor);

				if (balanceFactorInvalid) {
					bool isLeftLeftCase = checkLeftLeftCase(nodeStart);
					bool isLeftRightCase = checkLeftRightCase(nodeStart);

					if (isLeftLeftCase) {
						return rotateRight(nodeStart);
					}
					else if (isLeftRightCase) {
						return rotateLeftRight(nodeStart);
					}
				}
			}
			// If key is greater than current node's key, insert to the right recursively
			else {
				nodeStart->setRight(insertHelper(nodeStart->getRight(), nodeInsert));
				int balanceFactor = getBalanceFactor(nodeStart);
				bool balanceFactorInvalid = checkBalanceFactor(balanceFactor);

				if (balanceFactorInvalid) {
					bool isRightRightCase = checkLeftLeftCase(nodeStart);
					bool isRightLeftCase = checkLeftRightCase(nodeStart);

					if (isRightRightCase) {
						return rotateLeft(nodeStart);
					}
					else if (isRightLeftCase) {
						return rotateRightLeft(nodeStart);
					}
				}
			}
		}
	}
}

/*
	Input:		nodeStart  - node from which to insert the new node, usually the root
				nodeInsert - pointer to node to insert into the tree

	Output:		void

	Comments:   The function inserts, using a helper function, a node into the tree in BST order. It also makes sure
				that the tree remains balanced following the AVL tree conventions. The function
				makes sure that the ID and Name in nodeInsert are valid before doing the insertion.
				If the insertion fails, 'unsuccessful' is printed. If it succeeds, 'successful' is
				printed.
*/
void AVLTree::insert(Node* nodeStart, Node* nodeInsert) {

	// Ensures name and ID are valid
	if (isNameValid(nodeInsert->getName()) && isIDValid(nodeInsert->getID())) {

		insertHelper(nodeStart, nodeInsert);
		numOfNodes++;
		std::cout << "successful" << std::endl;

	}
	// If ID or name is not valid
	else std::cout << "unsuccessful" << std::endl;
}

// Tests if passed strings meets the constraints of the name.
// Names must onlu include [a-z, A-Z, spaces]
bool AVLTree::isNameValid(std::string name) {
	char currChar;
	for (int indx = 0; indx < name.length(); indx++) {
		currChar = name[indx];
		// If the current character is not in alphabet, handles the appropiate cases
		if (!isalpha(currChar)) {
			// If it is a digit, returns false
			if (isdigit(currChar)) {
				return true;/*<-----------******************************************************************************************Dont forget to change to false this was just for testing purposes**************************
											   ******************************************************************************************************************************************************************************************
											   *99999999999999999999999999999999999999999999999999999999999999999999999999999999******************************************************************************************************/
			}
			// If it is not a digit, makes sure that it is a space. Otherwise, returns false
			else {
				// If this is true, then character is not a digit, alphabet, or space
				if (ispunct(currChar)) {
					return false;
				}
				// Current character is an invalid whitespace character
				else if (isspace(currChar) && currChar != ' ') {
					return false;
				}
				// Else, it is a space, so it continues to the next
				else continue;
			}
		}
	}
	// If iteration finishes, then name is valid
	return true;
}









//*******************************************************************************************************************************************************************************


/*
	Inputs:	Node - Pointer to the root of the tree

	Comments:	This function does a postorder traversal from the root
				of the tree printing the name associated with each node
				in the process.
*/
void AVLTree::printPostorder(Node* node) {
	static int nodesTraversed = 0;

	if (root == nullptr) {
		std::cout << "Tree is empty" << std::endl;
	}
	//Base case for recursion
	else if (node == nullptr) {
		return;
	}
	else {


		// Visit left
		printPostorder(node->getLeft());
		// Ending hasn't been reached: print comma

		// Visit Right
		printPostorder(node->getRight());
		if (nodesTraversed + 1 != numOfNodes) {
			std::cout << node->getName() << ", ";
			nodesTraversed++;

		}
		// End reached: do not print comma
		else {
			std::cout << node->getName() << std::endl;
			nodesTraversed++;
		}
		// Resets static variable to zero for subsequent function calls
		if (nodesTraversed >= numOfNodes) nodesTraversed = 0;
	}
}

/*
	Input:	Node - Node Pointer to the root

	Comments:     This function traverses the tree in preorder displaying the name of each node
				  in the process
*/
void AVLTree::printPreorder(Node* node) {
	static int nodesTraversed = 0;

	if (root == nullptr) {
		std::cout << "Tree is empty" << std::endl;
	}
	//Base case for recursion
	else if (node == nullptr) {
		return;
	}
	else {

		if (nodesTraversed + 1 != numOfNodes) {
			std::cout << node->getName() << ", ";
			nodesTraversed++;

		}
		// End reached: do not print comma
		else {
			std::cout << node->getName() << std::endl;
			nodesTraversed++;
		}
		// Visit left
		printPreorder(node->getLeft());
		// Ending hasn't been reached: print comma

		// Visit Right
		printPreorder(node->getRight());
		// Resets static variable to zero for subsequent function calls
		if (nodesTraversed >= numOfNodes) nodesTraversed = 0;
	}
}

/*This function calls a helper function that recursively searches the tree for
  the 'name' parameter. If the helper function returns a non-empty vector, then
  this function prints the ID's in the order the helper function found them.*/
void AVLTree::searchName(Node* rt, std::string name) {


	std::vector<std::string> foundNames = searchNameHelper(rt, name);
	// If names were found, print the ID's in preorder traversal order
	if (foundNames.size() > 0) {
		for (int nameIdx = 0; nameIdx < foundNames.size(); nameIdx++) {
			std::cout << foundNames[nameIdx] << std::endl;
		}
	}
	else {
		std::cout << "unsuccessful" << std::endl;
	}

}
/*
	Inputs:       node - ptr to the current node in the preorder recursion
				  name - string with the name to be found in the tree

	output:       foundNames - vector containing the names found in the traversal in preorder

	Comments:     Function searches for names in a tree. If multiple names are found,
				  the names are returned in a vector in the order in which they were
				  found. The function does not check if name is in the tree.

*/
std::vector<std::string> AVLTree::searchNameHelper(Node* node, std::string name) {

	static int traversedNodes = 0;
	static std::vector<std::string> foundNames;
	std::vector<std::string> foundNamesCopy;

	// Base level for recusion.
	if (node == nullptr) {
		return foundNamesCopy;
	}
	// Traverse the tree
	else {
		if (name == node->getName()) {
			foundNames.push_back(node->getID());
		}
		//Search Left
		searchNameHelper(node->getLeft(), name);
		//Search Right
		searchNameHelper(node->getRight(), name);
		traversedNodes++;
		if (traversedNodes == numOfNodes) {
			// Reset static variables for subsequent calls and return a copy of vector with found names
			traversedNodes = 0;
			for (int nameIdx = 0; nameIdx < foundNames.size(); nameIdx++) {
				foundNamesCopy.push_back(foundNames[nameIdx]);
			}
			foundNames.clear();
			return foundNamesCopy;
		}
		else {
			return foundNamesCopy;
		}
	}

}

/*
	Inputs:
			   root - Node* to the root of the tree
			   n    - The nth node to be removed
	Comments:

	The traversal is performed recursively calling a helper function.
	The removal is always started from the root.

*/
void AVLTree::removeInOrderN(Node* root, int n) {

	if (n > numOfNodes - 1) std::cout << "unsuccessful" << std::endl;
	else {
		Node* NodeToBeRemoved = findIDnthNode(root, n);
		std::string id = NodeToBeRemoved->getID();
		removeID(root, id);
	}
}

// Inputs: 
//		         root - Pointer to the root of the tree
//		         n    - The nth node in inorder traversal order
// Outputs: 
//               Node* - pointer to the nth node in inorder traversal
//		            
// Comments:
//               Traverses the tree inorder and returns the id
//			     of the nth node, which is determined by the input.
//             
Node* AVLTree::findIDnthNode(Node* node, int n) {

	static int traversedNodes = 0;
	static std::vector<Node*> NodesUpToIncludingNth;
	Node* ptrToNthNode = nullptr;

	if (node == nullptr) return nullptr;
	else {
		findIDnthNode(node->getLeft(), n);
		// If the nth node is not in the vector or n= 0 and vector is empty, push the current
		if (NodesUpToIncludingNth.size() <= n) NodesUpToIncludingNth.push_back(node);
		findIDnthNode(node->getRight(), n);
		traversedNodes++;
		if (traversedNodes == numOfNodes) {
			// Reset static variables for subsequent calls and return id
			traversedNodes = 0;
			ptrToNthNode = NodesUpToIncludingNth.back();
			NodesUpToIncludingNth.clear();
			return ptrToNthNode;
		}

	}
}

// Prints an inorder version of the tree recursively. 
// The values are separated by commas
void AVLTree::printInOrder(Node* node) {

	static int nodesTraversed = 0;

	if (root == nullptr) {
		std::cout << "Tree is empty" << std::endl;
	}
	//Base case for recursion
	else if (node == nullptr) {
		return;
	}
	else {
		// Visit left
		printInOrder(node->getLeft());
		// Ending hasn't been reached: print comma
		if (nodesTraversed + 1 != numOfNodes) {
			std::cout << node->getName() << ", ";
			nodesTraversed++;

		}
		// End reached: do not print comma
		else {
			std::cout << node->getName() << std::endl;
			nodesTraversed++;
		}
		// Visit Right
		printInOrder(node->getRight());
		// Resets static variable to zero for subsequent function calls
		if (nodesTraversed >= numOfNodes) nodesTraversed = 0;
	}
}

/*Prints the level count of the tree. If tree is empty,
  prints 0. */
void AVLTree::printLevelCount(Node* node) {
	int numOfLevels = 0;
	// If root of the tree is null
	if (root == nullptr) std::cout << numOfLevels << std::endl;
	else {
		std::queue<Node*> nodesToTraverse;              // Holds the nodes to be traversed in level order from left to right
		std::queue<Node*> currentNodeChildren;          // Holds the children of the current node being traversed
		std::vector<Node*> nodesInNextLevel;            // Holds the children of the current node being traversed in the queue
		Node* lastNodeInLevel = node;                   // Points to the last node in each level of the tree
		Node* currentNode = node;                       // Holds a pointer to the current node being traversed
		bool currentNodeHasChildren;                    // True if current node has children
		int numOfNodesTraversed = 0;                    // Holds the number of nodes traversed 


		// Pushes the root into the queue, and traverses tree in level order
		nodesToTraverse.push(node);
		numOfLevels++;
		while (!nodesToTraverse.empty()) {

			// Updates current node
			currentNode = nodesToTraverse.front();
			// Gets the children of the current node being traversed
			currentNodeChildren = getChildren(currentNode);
			currentNodeHasChildren = (currentNodeChildren.size() > 0);

			// If current node has children, put them in the queue to be traversed in level order
			if (currentNodeHasChildren) {
				// Puts each child in the queue to be traversed
				while (!currentNodeChildren.empty()) {
					nodesToTraverse.push(currentNodeChildren.front());
					currentNodeChildren.pop();
				}
			}
			// If current node is the last node in level
			if (currentNode == lastNodeInLevel) {
				// Updates the pointer to the next level's last node
				lastNodeInLevel = nodesToTraverse.back();
				// Updates the number of levels except on the last loop
				if (numOfNodesTraversed + 1 < numOfNodes) numOfLevels++;
			}
			// Removes current node from nodes to be traversed
			nodesToTraverse.pop();
			numOfNodesTraversed++;
		}
		std::cout << numOfLevels;
	}
}

/*This function pushes the nodes in the second queue to
  the elements of the first queue. The first queue contains the
  nodes to be visited in a traversal, and the second contains
  the children of a node. Returns a queue with all the nodes
  merged.*/
std::queue<Node*> AVLTree::addChildrenToQ(std::queue<Node*> q1, std::queue<Node*>& q2){
	int q2InitialSize = q2.size();
	for (int i = 0; i < q2InitialSize; i++) {
		q1.push(q2.front());
		q2.pop();
	}
	return q1;
}

/*This function adds the passed node's children to a queue 
  and returns the queue.*/
std::queue<Node*> AVLTree::getChildren(Node* node) {
	std::queue<Node*> q;
	// If node is null return empty queue
	if (node == nullptr) {
		return q;
	}
	else {
		bool nodeHasChildren = (node->getRight() != nullptr || node->getLeft() != nullptr);
		bool nodeHasRightChOnly = (node->getRight() != nullptr && node->getLeft() == nullptr);
		bool nodeHasLeftChOnly = (node->getRight() == nullptr && node->getLeft() != nullptr);

		if (!nodeHasChildren) {
			// Return empty queue
			return q;
		}
		else if (nodeHasRightChOnly) {
			q.push(node->getRight());
			return q;
		}
		else if (nodeHasLeftChOnly) {
			q.push(node->getLeft());
			return q;
		}
		else {
			
			q.push(node->getLeft());
			q.push(node->getRight());
			return q;
		}
	}
	
}

// Tests if passed key is already in the tree.
// Uses pre order traversal of the tree
bool AVLTree::isIDUnique(Node* node, std::string id) {

	bool result;
	// This is the base for ending recursion
	// This case also signal when the id is not in the tree yet.
	if (node == nullptr) {
		return true;
	}
	// If id is less than the id of current node, search left
	else if (stoi(id) < stoi(node->getID())) {
		result = isIDUnique(node->getLeft(), id);
		return result;
	}
	// If id is greater than the id of current node, search right
	else if (stoi(id) > stoi(node->getID())) {
		result = isIDUnique(node->getRight(), id);
		return result;
	}
	// If id is equal return false
	else return false;

}

// Test if passed string meets the required constraints for an ID
// ID must be eight digits long and be unique
bool AVLTree::isIDValid(std::string id) {

	// Ensures ID is eight characters long
	int idLength = id.length();
	if (idLength != 8) return false;
	else {
		// Ensures ID is only digits
		for (int idx = 0; idx < idLength; idx++) {
			if (!isdigit(id[idx])) return false;
		}
		// Ensures ID is unique
		if (!isIDUnique(root, id)) return false;

		// If program gets here, ID is valid
		return true;
	}
}


/*This function receives a node and searches recursively for the
  passed id. If ID is not found, displays a message. If it is found,
  displays the name associated with the ID*/
void AVLTree::searchID(Node* rt, std::string id) {
	
	// This is the base for ending recursion
	// This case also signal when the id is not in the tree yet.
	if (rt == nullptr) {
		std::cout << "unsuccessful" << std::endl;
	}
	// If id is less than the id of current node, search left
	else if (stoi(id) < stoi(rt->getID())) {
		searchID(rt->getLeft(), id);

	}
	// If id is greater than the id of current node, search right
	else if (stoi(id) > stoi(rt->getID())) {
		searchID(rt->getRight(), id);
	}
	// If id is equal return false
	else std::cout << rt->getName() << std::endl;
}

/*This function takes a pointer a traverses only the left path of the tree
  starting at the passed pointer until a null node is encountered. It returns
  the last node before the null node was encountered.*/
Node* AVLTree::traverseLeft(Node* node) {

	// Base case recursion: last node before null to the left
	if (node->getLeft() == nullptr) {
		return node;
	}
	else {
		return traverseLeft(node->getLeft());
	}
}

/*Finds the inorder sucessor of a node in the case where the node has a right subtree only
*/
Node* AVLTree::findInOrderSuccessor(Node* node) {
	Node* rightSubtree = node->getRight();
	Node* inOrderSuccessor = traverseLeft(rightSubtree);
	return inOrderSuccessor;
}

/*Same as removeID but does not print any message when successful or unsuccessful
*/
void AVLTree::removeIDNoPrint(Node* node, std::string id) {
	// Takes care of the case where passed node is root of tree and has no children
	if ((node == root) && (node->getRight() == nullptr) && (node->getLeft() == nullptr)) {
		// The root is the node to be removed
		if (stoi(id) == stoi(node->getID())) {
			root = nullptr;
		}
	}
	// Takes care of the cases where the root needs to be removed
	else if (stoi(id) == stoi(node->getID())) {
		// Node has only one child to the left
		if ((node == root) && (node->getRight() == nullptr) && (node->getLeft() != nullptr)) {
			root = node->getLeft();
		}
		// Node has only one child to the right
		else if ((node == root) && (node->getRight() != nullptr) && (node->getLeft() == nullptr)) {
			root = node->getRight();
		}
		// Root has two children and needs to be removed
		else if ((node == root) && (node->getRight() != nullptr) && (node->getLeft() != nullptr)) {
			//if root's right child only has right child or no children, the inorder successor is root's right child
			Node* child = root->getRight();
			bool rootHasGrandchildren = (child->getLeft() != nullptr || child->getRight() != nullptr);
			bool hasGrandChildToRightOnly = (child->getLeft() == nullptr && child->getRight() != nullptr);
			bool rootHasBothGC = (child->getLeft() != nullptr && child->getRight() != nullptr);
			// Root does not have grandchildren or has GC to the right only and needs to be removed
			if ((!rootHasGrandchildren) || hasGrandChildToRightOnly) {
				// Makes sure the left subtree is attached to new root and sets new root
				root->getRight()->setLeft(root->getLeft());
				root = node->getRight();
			}
			// Root has both grandchildren
			else if (rootHasBothGC) {
				Node* inOrderSucc = findInOrderSuccessor(root);
				// Removes the inorder successor and sets its right subtree to the correct node
				removeIDNoPrint(root, inOrderSucc->getID());
				// Saves root's right and left subtree to new root and sets new root
				inOrderSucc->setRight(root->getRight());
				inOrderSucc->setLeft(root->getLeft());
				root = inOrderSucc;
			}
		}
	}
	// The node to be removed is not the root
	else {
		// Calls a helper function to recursively traverse the tree until the needed ID is found
		// or the end of tree is reached.
		removeIDHelperNoPrint(node, id);
	}
}

/*Same as removeIDHelper but does not print any messages when successful or unsuccessful
*/
Node* AVLTree::removeIDHelperNoPrint(Node* node, std::string id) {
	// Base case for recursion: ID not found
	if (node == nullptr) {
		return nullptr;
	}
	else {
		// If ID is equal to current node's ID, remove
		if (stoi(id) == stoi(node->getID())) {
			// If node is a leaf node
			if (node->getLeft() == nullptr && node->getRight() == nullptr) {
				return nullptr;
			}
			// If node not a leaf node and only one child to the left, returns the left child to be 
			// attached to the node's parent
			else if (node->getLeft() != nullptr && node->getRight() == nullptr) {
				return node->getLeft();
			}
			// If node not a leaf node and only one child to the right, returns the right child to be 
			// attached to the node's parent
			else if (node->getLeft() == nullptr && node->getRight() != nullptr) {
				return node->getRight();
			}
			// If node not a leaf and has two children, finds the in order successor and reorders tree
			else {
				Node* inOrderSucc = findInOrderSuccessor(node->getRight());
				// Makes sure that inorder successor's right subtree does not get lost
				removeIDHelperNoPrint(root, inOrderSucc->getID());
				// Creates the new subtree to be attached to current node's parent
				inOrderSucc->setLeft(node->getLeft());
				inOrderSucc->setRight(node->getRight());
				return inOrderSucc;
			}

		}
		// If id is less than current node's ID, search left
		else if (stoi(id) < stoi(node->getID())) {
			// Sets the left subtree recursively calling the removeID function
			node->setLeft(removeIDHelperNoPrint(node->getLeft(), id));
			return node;
		}
		else if (stoi(id) > stoi(node->getID())) {
			// Resets the subtree recursively
			node->setRight(removeIDHelperNoPrint(node->getRight(), id));
			return node;
		}

	}
}


Node* AVLTree::removeIDHelper(Node* node, std::string id) {
	// Base case for recursion: ID not found
	if (node == nullptr) {
		std::cout << "unsuccessful" << std::endl;
		return nullptr;
	}
	else {
		// If ID is equal to current node's ID, remove
		if (stoi(id) == stoi(node->getID())) {
			// If node is a leaf node
			if (node->getLeft() == nullptr && node->getRight() == nullptr) {
				std::cout << "successful" << std::endl;
				numOfNodes--;
				return nullptr;
			}
			// If node not a leaf node and only one child to the left, returns the left child to be 
			// attached to the node's parent
			else if (node->getLeft() != nullptr && node->getRight() == nullptr) {
				std::cout << "successful" << std::endl;
				numOfNodes--;
				return node->getLeft();
			}
			// If node not a leaf node and only one child to the right, returns the right child to be 
			// attached to the node's parent
			else if (node->getLeft() == nullptr && node->getRight() != nullptr) {
				std::cout << "successful" << std::endl;
				numOfNodes--;
				return node->getRight();
			}
			// If node not a leaf and has two children, finds the in order successor and reorders tree
			else {
				Node* inOrderSucc = findInOrderSuccessor(node);
				// Makes sure that inorder successor's right subtree does not get lost
				removeIDHelperNoPrint(root, inOrderSucc->getID());
				// Creates the new subtree to be attached to current node's parent
				inOrderSucc->setLeft(node->getLeft());
				inOrderSucc->setRight(node->getRight());
				std::cout << "successful" << std::endl;
				numOfNodes--;
				return inOrderSucc;
			}
			
		}
		// If id is less than current node's ID, search left
		else if (stoi(id) < stoi(node->getID())) {
			// Sets the left subtree recursively calling the removeID function
			node->setLeft(removeIDHelper(node->getLeft(), id));
			return node;
		}
		else if (stoi(id) > stoi(node->getID())) {
			// Resets the subtree recursively
			node->setRight(removeIDHelper(node->getRight(), id));
			return node;
		}
		
	}
}

/*This function removes the node containing the passed ID from the tree.
  If deletion is successful, prints 'successful'. If it isn't, prints
  'unsuccessful'. If the node to be deleted has two children, inorder successor takes its place.*/
void AVLTree::removeID(Node* node, std::string id) {

	// Takes care of the case where passed node is root of tree and has no children
	if ((node == root) && (node->getRight() == nullptr) && (node->getLeft() == nullptr)) {
		// The root is the node to be removed
		if (stoi(id) == stoi(node->getID())) {
			root = nullptr;
			std::cout << "successful" << std::endl;
			numOfNodes--;
		}
		else{
			std::cout << "unsuccessful" << std::endl;
		}
	}
	// Takes care of the cases where the root needs to be removed
	else if (stoi(id) == stoi(node->getID())) {
		// Node has only one child to the left
		if ((node == root) && (node->getRight() == nullptr) && (node->getLeft() != nullptr)) {
			root = node->getLeft();
			std::cout << "successful" << std::endl;
			numOfNodes--;
		}
		// Node has only one child to the right
		else if ((node == root) && (node->getRight() != nullptr) && (node->getLeft() == nullptr)) {
			root = node->getRight();
			std::cout << "successful" << std::endl;	
			numOfNodes--;
		}
		// Root has two children and needs to be removed
		else if ((node == root) && (node->getRight() != nullptr) && (node->getLeft() != nullptr)) {
			//if root's right child only has right child or no children, the inorder successor is root's right child
			Node* child = root->getRight();
			bool rootHasGrandchildren = (child->getLeft() != nullptr || child->getRight() != nullptr);
			bool hasGrandChildToRightOnly = (child->getLeft() == nullptr && child->getRight() != nullptr);
			bool rootHasBothGC = (child->getLeft() != nullptr && child->getRight() != nullptr);
			// Root does not have grandchildren or has GC to the right only and needs to be removed
			if ((!rootHasGrandchildren) || hasGrandChildToRightOnly) {
				// Makes sure the left subtree is attached to new root and sets new root
				root->getRight()->setLeft(root->getLeft());
				root = node->getRight();
				std::cout << "successful" << std::endl;
				numOfNodes--;
			}
			// Root has both grandchildren
			else if (rootHasBothGC) {
				Node* inOrderSucc = findInOrderSuccessor(root);
				// Removes the inorder successor and sets its right subtree to the correct node
				removeIDNoPrint(root, inOrderSucc->getID());
				// Saves root's right and left subtree to new root and sets new root
				inOrderSucc->setRight(root->getRight());
				inOrderSucc->setLeft(root->getLeft());
				root = inOrderSucc;
				std::cout << "successful" << std::endl;
				numOfNodes--;
			}
		}
	}
	// The node to be removed is not the root
	else {
		// Calls a helper function to recursively traverse the tree until the needed ID is found
		// or the end of tree is reached.
		removeIDHelper(node, id);
	}
}