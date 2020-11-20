#include "RBT.h"
using namespace std;

//constructor for class 'Node'
Node::Node(int d)
{
	data=d;
	left=NULL;
	right=NULL;
	parent=NULL;
	//color of newly inserted node is always RED initially
	color=RED;
}

// returns pointer to sibling 
Node* Node::sibling() 
{ 
	// sibling null if no parent 
	if (parent == NULL) 
	{
		return NULL; 
	}

	if (this==parent->left)
	{
		return parent->right; 
	}
	else
	{
		return parent->left; 
	}
}

bool Node::hasRedChild() 
{ 
	return ((left != NULL) && (left->color == RED)) || ((right != NULL) && (right->color == RED)); 
} 
		
//constructor for the RBT class
RBT::RBT()
{
	root=NULL;
}

//recursive function to insert a node into the RBT
//The function is so similar to BST insertion
Node* RBT::insert_node(Node* f_root,Node* node)
{
	if (f_root==NULL)
	{
		return node;
	}
	if ((node->data)<(f_root->data))
	{
		f_root->left=insert_node(f_root->left,node);
		f_root->left->parent=f_root;
	}
	else if ((node->data)>(f_root->data))
	{
		f_root->right=insert_node(f_root->right,node);
		f_root->right->parent=f_root;
	}
	//f_root is unchanged;
	return f_root;
}

//Left rotation i.e.,Rotating the 'node' left(anticlockwise)
void RBT::Lrotation(Node* node)
{
	Node* right_node=node->right;
	node->right=right_node->left;
	//if not the 'node' is leaf node
	if (node->right!=NULL)
	{
		node->right->parent=node;
	}
	right_node->parent=node->parent;
	//if node is the root node
	if (node->parent==NULL)
	{
		root=right_node;
	}
	//if called from case A of violation checking i.e., Lrotation in the left subtree
	else if (node->parent->left==node)
	{
		node->parent->left=right_node;
	}
	//if called from case B of violation checking i.e., Lrotation in the right subtree
	else
	{
		node->parent->right=right_node;
	}
	right_node->left=node;
	node->parent=right_node;	
}

//right rotation i.e.,Rotating the 'node' right(clockwise)
void RBT::Rrotation(Node *node) 
{ 
	Node* left_node=node->left;
	node->left=left_node->right;
	//if not the 'node' is leaf node
	if (node->left!=NULL)
	{
		node->left->parent=node;
	}
	left_node->parent=node->parent;
	//if node is the root node
	if (node->parent==NULL)
	{
		root=left_node;
	}
	//if called from case A of violation checking i.e., Rrotation in the left subtree
	else if (node->parent->left==node)
	{
		node->parent->left=left_node;
	}
	//if called from case B of violation checking i.e., Rrotation in the right subtree
	else
	{
		node->parent->right=left_node;
	}
	left_node->right=node;
	node->parent=left_node;	
} 

//checks for violations of Red Black Tree properties and solve those through recoloring and rotations
void RBT::check_for_violation_insertion(Node* node)
{
	Node* parent_node=NULL;
	Node* grandparent_node=NULL;
	
	//since color of newly inserted node is RED initially, it's parend can't be RED
	while((node!=root) && (node->color!=BLACK) && (node->parent->color==RED))
	{
		parent_node=node->parent;
		grandparent_node=node->parent->parent;
		//case A: if insertion in the left subtree
		if (grandparent_node->left==parent_node)
		{
			Node* uncle_node=grandparent_node->right;
			//case A1: if insertion in the left subtree and color of the uncle is RED -> then recolouring only
			if ((uncle_node!=NULL) && (uncle_node->color==RED))
			{
				uncle_node->color=BLACK;
				parent_node->color=BLACK;
				grandparent_node->color=RED;
				//going up the tree for checking
				node=grandparent_node;
			}
			//case A2: if insertion in the left subtree and color of the uncle is BLACK -> then rotating and recoloring
			else
			{
				//case A2(i): LR rotation needed and recoloring
				if (parent_node->right==node)
				{
					Lrotation(parent_node);
					node=parent_node;
					parent_node=node->parent;
				}
				//case A2(ii): R rotation needed and recoloring
				Rrotation(grandparent_node);
				//recoloring the parent and grandparent of the inserted node
				swap(parent_node->color,grandparent_node->color);
				//going up the tree for checking
				node=parent_node;
			}
		}
		//case B: if insertion in the right subtree
		else
		{
			Node* uncle_node=grandparent_node->left;
			//case B1: if insertion in the right subtree and color of the uncle is RED -> then recolouring only
			if ((uncle_node!=NULL) && (uncle_node->color==RED))
			{
				uncle_node->color=BLACK;
				parent_node->color=BLACK;
				grandparent_node->color=RED;
				//going up the tree for checking
				node=grandparent_node;
			}
			//case B2: if insertion in the right subtree and color of the uncle is BLACK -> then rotating and recoloring
			else
			{
				//case B2(i): RL rotation needed and recoloring
				if (parent_node->left==node)
				{
					Rrotation(parent_node);
					node=parent_node;
					parent_node=node->parent;
				}
				//case B2(ii): L rotation needed and recoloring
				Lrotation(grandparent_node);
				//recoloring the parent and grandparent of the inserted node
				swap(parent_node->color,grandparent_node->color);
				//going up the tree for checking
				node=parent_node;
			}
		}
	}
	root->color=BLACK;
}

//creates a node with the integer to be inserted and calls the recursive function for the insertion of that node; 
void RBT::insert_x(int x) 
{ 
	Node* node=new Node(x);
	//calls the recursive insertion function
	root=insert_node(root,node);
	//checks for the violations of the Red Black Tree rules and rectifies those violations
	check_for_violation_insertion(node);
} 

// find node that do not have a left child 
// in the subtree of the given node 
Node* RBT::successor(Node* x) 
{ 
	Node* temp = x; 

	while (temp->right != NULL)
	{ 
		temp = temp->right; 
	}
	return temp; 
} 

// find node that replaces a deleted node in BST 
Node* RBT::replacement_for(Node* x)
{
	//when node have 2 children
	if ((x->left!=NULL) && (x->right!=NULL))
	{
		return successor(x->left);
	}
	
	//when leaf
	if ((x->left==NULL) && (x->right==NULL))
	{
		return NULL;
	}
	
	//when single child
	if (x->left!=NULL)
	{
		return x->left;
	}
	else
	{
		return x->right;
	}
}

void RBT::check_for_violation_deletion(Node* v) 
{ 
	//Case :(double black)
	if (v == root) 
	{
		// Reached root 
		return; 
	}

	Node* sibling = v->sibling();
	Node* parent = v->parent; 
	if (sibling == NULL) 
	{ 
		// No sibiling, double black pushed up    
		check_for_violation_deletion(parent); 
	} 
	else 
	{ 
		if (sibling->color == RED) 
		{ 
			//case A: Sibling red -> recoloring and rotating and checking again 
			parent->color = RED; 
			sibling->color = BLACK; 
			if (sibling==sibling->parent->left) 
			{ 
				//case A1:left sibling red-> left case 
				Rrotation(parent); 
			} 
			else 
			{ 
				//case A2:right sibling red-> right case 
				Lrotation(parent); 
			} 
			check_for_violation_deletion(v); 
		} 
		else 
		{ 
			//case B: Sibling black 
			if (sibling->hasRedChild()) 
			{ 
			//case B1: at least 1 red children 
				if ((sibling->left != NULL) && (sibling->left->color == RED)) 
				{ 
				//case B1(i): left children is red
					if (sibling==sibling->parent->left) 
					{ 
						//left sibling -> left children 
						// left left 
						sibling->left->color = sibling->color; 
						sibling->color = parent->color; 
						Rrotation(parent); 
					} 
					else 
					{ 
						//right sibling -> left children
						// right left 
						sibling->left->color = parent->color; 
						Rrotation(sibling); 
						Lrotation(parent); 
					} 
				} 
				else 
				{ 
				//case B1(ii): right children is red
					if (sibling==sibling->parent->left) 
					{ 
						//left sibling -> right children
						// left right 
						sibling->right->color = parent->color; 
						Lrotation(sibling); 
						Rrotation(parent); 
					} 
					else 
					{ 
						//right sibling -> right children
						// right right 
						sibling->right->color = sibling->color; 
						sibling->color = parent->color; 
						Lrotation(parent); 
					} 
				} 
				parent->color = BLACK; 
			} 
			else 
			{ 
			//case B2 -> 2 black children -> recoloring and/or rotation
				sibling->color = RED; 
				if (parent->color == BLACK) 
				{
					//case B2(i): 2 black children, parent black -> recursively check for the parent
					check_for_violation_deletion(parent); 
				}
				else
				{
					//case B2(ii): 2 black children, parent red -> just recolor parent
					parent->color = BLACK; 
				}
			} 
		} 
	} 
} 

//deletes the given node
void RBT::delete_node(Node* v)
{
	Node* u=replacement_for(v);
	
	//True when u and v are both black
	bool uvBlack= (((u==NULL) || (u->color==BLACK)) && (v->color==BLACK));
	Node* parent=v->parent;
	
	if (u==NULL)
	{
		//u is NULL therefore v is leaf
		if (v==root)
		{
			//v is root, making root null
			root=NULL;
		}
		else
		{
			if (uvBlack) 
			{ 
				//u and v both black
				//v is leaf, fix double black at v
				check_for_violation_deletion(v);
			}
			else
			{
				//u or v is red -> only recoloring and no rotations
				if (v->sibling()!=NULL)
				{
					//sibling is not null, make it red
					v->sibling()->color=RED;
				}
			}
			//delete v from the tree
			if (v->parent->left==v)
			{
				parent->left=NULL;
			}
			else
			{
				parent->right=NULL;
			}
		}
		delete v;
		return;
	}
		
	else if ((v->left==NULL) || (v->right==NULL))
	{
		//v has 1 child
		if (v==root)
		{
			//v is root, assign the value of u to v, and delete u
			v->data=u->data;
			v->left=v->right=NULL;
			delete u;
		}
		else
		{
			//Detach v from tree and move u up
			if (v->parent->left==v)
			{
				parent->left=u;
			}
			else
			{
				parent->right=u;
			}
			delete v;
			u->parent=parent;
			if (uvBlack)
			{
				//u and v both black, fic double black at u
				check_for_violation_deletion(u);
			}
			else
			{
				//u or v red, color u black-> only recoloring
				u->color=BLACK;
			}
		}
		return;
	}
	// v has 2 children, swap values with successor and recurse 
	swap(u->data, v->data); 
	delete_node(u); 
	
} 

// searches for given value 
// if found returns the node (used for delete) 
// else returns the last node while traversing (used in insert) 
Node* RBT::search(int n) 
{ 
	Node* temp = root; 
	while (temp != NULL) 
	{ 
		if (n < temp->data) 
		{ 
			if (temp->left == NULL) 
			{
				break; 
			}
			else
			{
				temp = temp->left; 
			}
		} 
		else if (n == temp->data) 
		{ 
			break; 
		} 
		else 
		{ 
			if (temp->right == NULL) 
			{
				break; 
			}
			else
			{
				temp = temp->right; 
			}
		} 
	} 
	return temp; 
} 

// utility function that deletes the node with given value 
void RBT::delete_x(int x) 
{ 
	if (root == NULL) 
	{
		// Tree is empty 
		return; 
	}

	Node* node_x = search(x); 

	if (node_x->data != x) 
	{ 
		cout << "No node found to delete with value:" << x << endl; 
		return; 
	} 
	delete_node(node_x); 
} 

//prints the data and the color node by node through recursion , printing in the descending order with '10' spaces between each nodes
void RBT::print(Node* f_root,int space)
{
   	if (f_root==NULL)
   	{
   		return;
	}
	space+=10;
	print(f_root->right,space);
	cout<<endl;
	for (int i=10;i<space;i++)
	{
		cout<<" ";
	}
	cout<<f_root->data<<"(";
	(f_root->color==RED)?cout<<"R)\n":cout<<"B)\n";
	print(f_root->left,space);
}

//displays the tree in the sidewards i.e the root is in the left corner
void RBT::display()
{
		if (root==NULL)
		{
			cout<<"\nTREE EMPTY";
			return;
		}
		print(root,0);
}
