//#include "AVLTree.h"
#include "Node.h"
#include <iostream>
using namespace std;

int getHeight(Node* node) {

	if (node == nullptr) {
		return 0;
	}
	else {
		Node* nodeToLeft = node->getLeft();
		Node* nodeToRight = node->getRight();
		return 1 + max(getHeight(nodeToLeft), getHeight(nodeToRight));
	}
}

int getBalanceFactor(Node* node) {

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

int checkCase(Node* nodeOutOfBalance) {
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

Node* rotateRight(Node* node) {

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
void printInOrder(Node* node, int numOfNodes) {

	static int nodesTraversed = 0;
	//Base case for recursion
	if (node == nullptr) {
		return;
	}
	else {
		// Visit left
		printInOrder(node->getLeft(), numOfNodes);
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
		printInOrder(node->getRight(), numOfNodes);
		// Resets static variable to zero for subsequent function calls
		if (nodesTraversed >= numOfNodes) nodesTraversed = 0;
	}
}



int main() {

	string test = "Juan. Linde";
	//AVLTree tree;
	Node* n4 = new Node("n4","00000500");
	Node* n1 = new Node("n1", "00000250");
	Node* n0 = new Node("n0", "00000010");
	Node* n3 = new Node("n3", "00000300");
	Node* n7 = new Node("n7","00000750");
	Node* n5 = new Node("n5","00000600");
	Node* n12 = new Node("n12", "00001000");
	Node* n11 = new Node("n11", "00000900");
	Node* n17 = new Node("n17", "00002000");
	Node* n13 = new Node("n13", "00001500");
	Node* n18 = new Node("n18", "00002500");
	Node* n6 = new Node("n6", "00000620");
	Node* n2 = new Node("n2", "00000275");
	Node* n15 = new Node("n15", "00001700");
	Node* n14 = new Node("n14", "00001600");
	Node* n16 = new Node("n16", "00001750");
	Node* n9 = new Node("n9", "00000800");
	Node* n8 = new Node("n8", "00000775");
	Node* n10 = new Node("n10", "00000850");
	
	n4->setLeft(n1);
	n1->setLeft(n3);
	printInOrder(n4, 3);
	rotateRight(n4);
	printInOrder(n1, 3);
	
	cout << endl << "-------------------------------------------------------------------------------------------------" << endl;
	/*tree.insert(tree.getRoot(), n4);
	tree.insert(tree.getRoot(), n1);
	tree.insert(tree.getRoot(), n0);
	tree.insert(tree.getRoot(), n3);
	tree.insert(tree.getRoot(), n7);
	tree.insert(tree.getRoot(), n5);
	tree.insert(tree.getRoot(), n12);
	tree.insert(tree.getRoot(), n11);
	tree.insert(tree.getRoot(), n17);
	tree.insert(tree.getRoot(), n13);
	tree.insert(tree.getRoot(), n18);
	tree.insert(tree.getRoot(), n6);
	tree.insert(tree.getRoot(), n2);
	tree.insert(tree.getRoot(), n15);
	tree.insert(tree.getRoot(), n14);
	tree.insert(tree.getRoot(), n16);
	tree.insert(tree.getRoot(), n9);
	tree.insert(tree.getRoot(), n8);
	tree.insert(tree.getRoot(), n10);*/

	/*cout << tree.getNumOfNodes() << endl;
	tree.printInOrder(tree.getRoot());
	tree.printInOrder(tree.getRoot());
	cout << endl << "-------------------------------------------------------------------------------------------------" << endl;
	tree.printPreorder(tree.getRoot());
	tree.printPreorder(tree.getRoot());
	cout << endl << "-------------------------------------------------------------------------------------------------" << endl;
	tree.printPostorder(tree.getRoot());
	tree.printPostorder(tree.getRoot());*/
	return 0;
}