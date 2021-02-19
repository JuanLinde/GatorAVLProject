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
	void searchID(Node*, std::string);
	void searchName(Node*, std::string);
	void printInOrder(Node*);
	void removeID(Node*, std::string);
	void removeInOrderN(Node*, int);	
};

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

// Inserts a name and  ID into the tree.
// IDs and names must be valid before being inserted
// If names and id is valid, inserts the name and id
// Following BST order and displays successfull message.
// If names are not valid, displays unsuccessfull message.
// The tree gets balanced automatically if necessary.
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

// Prints an inorder version of the tree recursively. 
// The values are separated by commas
void AVLTree::printInOrder(Node* node) {

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
		// Print Root
		std::cout << node->getName() << " ";
		// Visit Right
		printInOrder(node->getRight());
	}
}

void AVLTree::printLevelCount(Node* node) {
	int numOfLevels = 0
		// If root of the tree is null
		if (root = nullptr) cout << numOfLevels << endl;
		else {
			std::queue<Node*> nodesToTraverse;              // Holds the nodes to be traversed in level order from left to right
			std::queue<Node*> currentNodeChildren;          // Holds the children of the current node being traversed
			std::vector<Node*> nodesInNextLevel;            // Holds the children of the current node being traversed in the queue
			Node* lastLevelInNode = node;                   // Points to the last node in each level of the tree
			Node* currentNode = node;                       // Holds a pointer to the current node being traversed
			bool currentNodeHasChildren;                    // True if current node has children


			// Pushes the root into the queue, and traverses tree in level order
			nodesToTraverse.push(node);
			while (!nodesToTraverse.empty()) {
				// Gets the children of the current node being traversed
				currentNodeChildren = getChildren(currentNode);
				currentNodeHasChildren = (currentNodeChildren > 0);

				// If current node has children, put them in the queue to be traversed in level order
				if (currentNodeHasChildren) {
					// Puts each child in the queue to be traversed
					while (!currentNodeChildren.empty()) {
						nodesToTraverse.push(currentNodeChildren.pop());
					}
					// If current node is the last node in level
					if (currentNode == lastLev)
				}

			}
}

//*******************************************************************************************************************************************************************************

/*Removes the n node from the passed node. If successful
  prints 'successful'. If not, prints unsuccessful.*/
void AVLTree::removeInOrderN(Node* node, int n) {

	// Counts the number of nodes traversed
	static int nodeCounter = -1;

	// Makes sure that there are enough nodes to search
	if (n > numOfNodes) {
		std::cout << "unsuccessful" << std::endl;
		return;
	}
	
	// Recursion Base case: node does not exist in tree
	if (node == nullptr) {
		return;
	}
	// Traverse the tree inorder until the nth node is found
	else {
		//Go left
		removeInOrderN(node->getLeft(), n);
		// Increase Counter
		nodeCounter++;
		// If current node is the nth node, remove it.
		if (n == nodeCounter) {
			removeID(root, node->getID());
			return;
		}
		// Go right
		removeInOrderN(node->getRight(), n);
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
			}
			// If key is greater than current node's key, insert to the right recursively
			else {
				nodeStart->setRight(insertHelper(nodeStart->getRight(), nodeInsert));
			}
		}
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

/*This function searches for the passed name in preorder traversal. It returns
  a vector with the found names.*/
std::vector<std::string> AVLTree::searchNameHelper(Node* node, std::string name) {

	static std::vector<std::string> foundNames;

	// Base level for recusion.
	if (node == nullptr) {
		return foundNames;
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
		return foundNames;
	}
	return foundNames;
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

/*Finds the inorder sucessor of a node in the case where the node has a right subtree only*/
Node* AVLTree::findInOrderSuccessor(Node* node) {
	Node* rightSubtree = node->getRight();
	Node* inOrderSuccessor = traverseLeft(rightSubtree);
	return inOrderSuccessor;
}

/*Same as removeID but does not print any message when successful or unsuccessful*/
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

/*Same as removeIDHelper but does not print any messages when successful or unsuccessful*/
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




