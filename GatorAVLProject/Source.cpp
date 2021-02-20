#include "AVLTree.h"
using namespace std;

int main() {

	string test = "Juan. Linde";
	AVLTree tree;
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

	tree.insert(tree.getRoot(), n4);
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
	tree.insert(tree.getRoot(), n10);
	cout << tree.getNumOfNodes() << endl;
	tree.printInOrder(tree.getRoot());
	cout << endl << "-------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < 2; i++) {
		tree.searchName(tree.getRoot(), "n1400");
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}
	//tree.removeInOrderN(tree.getRoot(), 19);
	//cout << tree.getNumOfNodes() << endl;

	return 0;
}