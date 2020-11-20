#ifndef RBT_H
#define RBT_H
#include<iostream>

enum Color{RED,BLACK};

class Node
{
	int data;
	//color can be now either be RED(0) or BLACK(1) [ENUMERATION]
	Color color;
	Node* left;
	Node* right;
	Node* parent;
	public:
		//constructor for class 'Node'
		Node(int);
		Node* sibling();	
		bool hasRedChild();
		friend class RBT;
};

//RBT stands for Red Black Tree
class RBT
{
	Node* root;
	protected:
		Node* insert_node(Node*,Node*);
		void Lrotation(Node*);
		void Rrotation(Node*);
		void check_for_violation_insertion(Node*);
		Node* successor(Node*);
		Node* replacement_for(Node*);  //BSTreplace()
		void delete_node(Node*);
		void check_for_violation_deletion(Node*);
		Node* search(int);
		void print(Node*,int);
	public:
		RBT();
		void insert_x(int);
		void delete_x(int);
		void display();
};

#endif
