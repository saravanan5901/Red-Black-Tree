//RED BLACK TREE IMPLEMENTATION
//by KARMUGIL S - 19PW24
//and SARAVANAN R - 19PW31

#include <iostream>
#include "RBT.h"
using namespace std;

int main() 
{
	int ch,x;
	RBT tree;
/*	tree.insert_x(7); 
	tree.insert_x(3); 
	tree.insert_x(18); 
	tree.insert_x(10); 
	tree.insert_x(22); 
	tree.insert_x(8); 
	tree.insert_x(11); 
	tree.insert_x(26); 
	tree.insert_x(2); 
	tree.insert_x(6); 
	tree.insert_x(13); 
	
	tree.display();
	cout<<endl<<"Deleting 18, 11, 3, 10, 22"<<endl; 
	
	tree.delete_x(18); 
	tree.delete_x(11); 
	tree.delete_x(3); 
	tree.delete_x(10); 
	tree.delete_x(22); 

	tree.display(); 
*/	do
	{
		cout<<"\n\nEnter your choice (operation on RBT):";
		cout<<"\n\t1 - Insert\
			   \n\t2 - Delete\
			   \n\t3 - Display\
			   \n\t0 - Exit\n";
		cin>>ch;
		switch(ch)
		{
			case 0:return 0;
			case 1:cout<<"\n\nEnter the integer you want to insert_x: ";
				   cin>>x;
				   tree.insert_x(x);
				   break;
			case 2:cout<<"\n\nEnter the integer you want to delete: ";
				   cin>>x;
				   tree.delete_x(x);
				   break;
			case 3:cout<<"\n\n";
				   tree.display();
				   break;
			default:continue;
		}
	}while(ch!=0);
	return 0;
}
