#include <string>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Node {
private:
	std::string name;
	std::string id;
	Node* left;
	Node* right;

public:
	Node(std::string n, std::string i) { name = n; id = i; left = nullptr, right = nullptr; }
	Node(std::string i) { name = "one"; id = i; left = nullptr; right = nullptr; }
	std::string getID() { return id; }
	std::string getName() { return name; }
	Node* getLeft() { return left; }
	Node* getRight() { return right; }
	void setLeft(Node* l) { left = l; }
	void setRight(Node* r) { right = r; }

};

class AVLTree {

private:

	Node* root;
	int numOfNodes;

	bool isNameValid(std::string);
	bool isIDUnique(Node*, std::string);
	bool isIDValid(std::string);
	Node* insertHelper(Node*, Node*);
	int getHeight(Node*);
	int getBalanceFactor(Node*);
	bool isBalancefactorValid(int);
	int checkCase(Node*);
	std::vector<std::string> searchNameHelper(Node*, std::string);
	Node* removeIDHelper(Node*, std::string);
	Node* findInOrderSuccessor(Node*);
	Node* findIDnthNode(Node*, int);
	Node* traverseLeft(Node*);
	Node* removeIDHelperNoPrint(Node*, std::string);
	void removeIDNoPrint(Node*, std::string);
	std::queue<Node*> getChildren(Node*);
	Node* rotateRight(Node*);
	Node* rotateLeft(Node*);
	Node* rotateLeftRight(Node*);
	Node* rotateRightLeft(Node*);
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
};

int main() {
	AVLTree tree;

	string numOfInputs;
	string input;
	getline(cin, numOfInputs);
	for (int inputIndx = 0; inputIndx < stoi(numOfInputs); inputIndx++) {
		getline(cin, input);	
		// Look for commands with space, which means the command is not a print command
		size_t isThereSpace = input.find(' ');
		// Command is not a print command
		if (isThereSpace != string::npos) {
			int lenghtInput = input.length();
			size_t firstSpacePos = isThereSpace;
			// Find the command in the input, which is the substring ending at the first space
			string command = input.substr(0, firstSpacePos);
			// Find the arguments to the command, which happens after the first space until the end
			string arguments = input.substr(firstSpacePos + 1);
			if (command == "insert") {
				// Find the position of last quotes to determine the name to insert
				size_t posLastQuotes = arguments.find("\"", 1);
				string name = arguments.substr(1, posLastQuotes - 1);
				string id = arguments.substr(posLastQuotes + 2);
				Node* nodeToInsert = new Node(name, id);
				tree.insert(tree.getRoot(), nodeToInsert);
			}
			else if (command == "search") {
				char firstChar = arguments.at(0);
				// If argument is a number, search number
				if (isdigit(firstChar)) {
					string idToSearch = arguments;
					tree.searchID(tree.getRoot(), idToSearch);
				}
				else {
					string nameToSearch = arguments.substr(1, arguments.length() - 2);
					tree.searchName(tree.getRoot(), nameToSearch);
				}
			}
			else if (command == "remove") {
				string idToRemove = arguments;
				tree.removeID(tree.getRoot(), idToRemove);
			}
			// Nth order removal
			else {
				string nodeToRemove = arguments;
				tree.removeInOrderN(tree.getRoot(), stoi(nodeToRemove));
			}
		}
		// Command has no spaces: it is a print command
		else {
			string printCommand = input.substr(5);
			if (printCommand == "Inorder") {
				tree.printInOrder(tree.getRoot());
			}
			else if (printCommand == "Preorder") {
				tree.printPreorder(tree.getRoot());
			}
			else if (printCommand == "Postorder") {
				tree.printPostorder(tree.getRoot());
			}
			else {
				tree.printLevelCount(tree.getRoot());
			}
		}
	}
	return 0;
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
		else {
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


				if (!isBalancefactorValid(balanceFactor)) {
					// Checks for the type of case for rotation
					int kse = checkCase(nodeStart);
					// kse = 0 -> left left case -> right rotation
					if (kse == 0) {
						if (nodeStart == root) {
							root = rotateRight(nodeStart);
						}
						else return rotateRight(nodeStart);
					}
					// kse = 1 -> left right case -> left right rotation
					else if (kse == 1) {
						if (nodeStart == root) {
							root = rotateLeftRight(nodeStart);
						}
						else return rotateLeftRight(nodeStart);
					}
				}
				else {
					return nodeStart;
				}
			}
			// If key is greater than current node's key, insert to the right recursively
			else {
				nodeStart->setRight(insertHelper(nodeStart->getRight(), nodeInsert));

				int balanceFactor = getBalanceFactor(nodeStart);


				if (!isBalancefactorValid(balanceFactor)) {
					// Checks for the type of case for rotation
					int kse = checkCase(nodeStart);

					// kse = 2 -> right right case -> left rotation
					if (kse == 2) {
						if (nodeStart == root) {
							root = rotateLeft(nodeStart);
						}
						else return rotateLeft(nodeStart);
					}
					// kse = 3 -> right left case -> right left rotation
					else if (kse == 3) {
						if (nodeStart == root) {
							root = rotateRightLeft(nodeStart);
						}
						else return rotateRightLeft(nodeStart);
					}
				}
				else {
					return nodeStart;
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
				return false;
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

/*
	Inputs:	node - pointer from which the rotation starts

	Output: node* - pointer to the new 'root' of rotated subtree

*/
Node* AVLTree::rotateRightLeft(Node* node) {
	if (node->getLeft() == nullptr && node->getRight() == nullptr) {
		return node;
	}
	else {
		node->setRight(rotateRight(node->getRight()));
		Node* newParent = rotateLeft(node);
		return newParent;
	}
}

/*
	Inputs:	node - Pointer from the node where the rotation starts

	Output: node* - Pointer to the new 'root' of the rotated subtree

*/
Node* AVLTree::rotateLeftRight(Node* node) {
	if (node->getLeft() == nullptr && node->getRight() == nullptr) {
		return node;
	}
	else {
		node->setLeft(rotateLeft(node->getLeft()));
		Node* newParent = rotateRight(node);
		return newParent;
	}
}

/*
	Inputs:	node - Node from which the rotation starts

	Output: node* - Node pointer to the new 'root' of the rotated subtree

*/
Node* AVLTree::rotateLeft(Node* node) {
	if (node->getLeft() == nullptr && node->getRight() == nullptr) {
		return node;
	}
	else {
		Node* newParent = node->getRight();
		Node* newParentOldLeft = newParent->getLeft();
		newParent->setLeft(node);
		node->setRight(newParentOldLeft);
		return newParent;
	}
}

/*
	Inputs:	node - pointer from where to start the rotation to the right

	Outputs: Node* - pointer to the new 'root' after rotation

*/
Node* AVLTree::rotateRight(Node* node) {

	// If passed node has no children, return passed node
	if (node->getLeft() == nullptr && node->getRight() == nullptr) {
		return node;
	}
	// If passed node has one children to the left
	else {
		Node* newParent = node->getLeft();
		Node* newParentOldRight = newParent->getRight();
		newParent->setRight(node);
		node->setLeft(newParentOldRight);
		return newParent;
	}
}

/*
	input:	nodeOutOfBalance - Node on which to check the case

	output:	int - 0 -> left left case
				  1 -> left right case
				  2 -> right right case
				  3 -> right left case
*/
int AVLTree::checkCase(Node* nodeOutOfBalance) {
	int balanceFactorPrimaryNode = getBalanceFactor(nodeOutOfBalance);
	int BFPrimaryNodeLeftChild = getBalanceFactor(nodeOutOfBalance->getLeft());
	int BFPrimaryNodeRightChild = getBalanceFactor(nodeOutOfBalance->getRight());

	//Checks left left case
	if (balanceFactorPrimaryNode == 2 && BFPrimaryNodeLeftChild == 1) return 0;
	// Checks left right case
	else if (balanceFactorPrimaryNode == 2 && BFPrimaryNodeLeftChild == -1) return 1;
	// Checks right right case
	else if (balanceFactorPrimaryNode == -2 && BFPrimaryNodeRightChild == -1) return 2;
	// Checks right left case
	else if (balanceFactorPrimaryNode == -2 && BFPrimaryNodeRightChild == 1) return 3;
	// For completeness
	else return -1;

}

/*
	inputs: balanceFactor - The balance factor of the node under consideration

	outputs: bool         - If balance factor < -1 or > 1 returns false

*/
bool AVLTree::isBalancefactorValid(int bf) {
	if (bf < -1 || bf > 1) return false;
	else return true;
}

/*
	Inputs: Node - Pointer to the node whose balance factor is needed

	Output: int - The balance factor of the current node

	Comments:	This function calls the getHeight() function for the left
				and right subtree and gets the balance factor of the node
				based on those heights.

*/
int AVLTree::getBalanceFactor(Node* node) {

	int heightLeftSubtree = 0;
	int heightRightSubtree = 0;
	int balanceFactor = 0;

	if (node == nullptr) return -1;
	// Leaf nodes have balance factor of 0
	if (node->getLeft() == nullptr && node->getRight() == nullptr) {
		return 0;

	}
	else if (node->getRight() == nullptr && node->getLeft() != nullptr) {
		heightRightSubtree = 0;
		heightLeftSubtree = getHeight(node->getLeft());
		balanceFactor = heightLeftSubtree - heightRightSubtree;
		return balanceFactor;
	}
	else if (node->getRight() != nullptr && node->getLeft() == nullptr) {
		heightRightSubtree = getHeight(node->getRight());
		heightLeftSubtree = 0;
		balanceFactor = heightLeftSubtree - heightRightSubtree;
		return balanceFactor;
	}
	else {
		heightRightSubtree = getHeight(node->getRight());
		heightLeftSubtree = getHeight(node->getLeft());
		balanceFactor = heightLeftSubtree - heightRightSubtree;
		return balanceFactor;
	}
}

/*
	Inputs: Node - pointer from which to start calculating height

	Ouput:	int  - The height of the tree from the passed node

	Comments:	This function calculates the height of a tree from the
				passed node. It does so by recursively calling itself.
*/
int AVLTree::getHeight(Node* node) {

	if (node == nullptr) {
		return 0;
	}
	else {
		Node* nodeToLeft = node->getLeft();
		Node* nodeToRight = node->getRight();
		return 1 + std::max(getHeight(nodeToLeft), getHeight(nodeToRight));
	}
}

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
		std::cout << numOfLevels << endl;
	}
}

/*This function pushes the nodes in the second queue to
  the elements of the first queue. The first queue contains the
  nodes to be visited in a traversal, and the second contains
  the children of a node. Returns a queue with all the nodes
  merged.*/
std::queue<Node*> AVLTree::addChildrenToQ(std::queue<Node*> q1, std::queue<Node*>& q2) {
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
