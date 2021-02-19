#pragma once
#include <string>

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
	void setLeft(Node * l) { left = l; }
	void setRight(Node* r) { right = r; }
	
};