//program to replace the root of a binary tree with an internal node. All adjacencies are maintained in the process. The program can replace the
//root of a binary tree only once. Beyond one replacement correctness is not guaranteed.
// Debarka Mukhopadhyay, NIT Warangal, 25-02-17 

#include<iostream>
using namespace std;

class BinaryTree
{
	struct Node
	{
		int data;
		Node *lc,*rc, *nc;
	};
	

	Node *find(Node *r,int key)
	{
		if(r==NULL)
			return NULL;
		if(r->data==key)
			return r;
		if(find(r->lc,key)==NULL)
			return find(r->rc,key);
		else
			return find(r->lc,key);
	}

public:
	Node *root;

	BinaryTree()
	{
		root=NULL;
	}

	void insert(int data)
	{
		Node *newn=new Node;
		newn->data=data;
		newn->lc=newn->rc=newn->nc=NULL;
		if(root==NULL)
		{
			root=newn;
			cout<<"\nEmpty tree inserted data at root";
			return;
		}

		int par;
		char dir;
		Node *tmp;
		cout<<"\nEnter parent data : ";
		cin>>par;
		tmp=find(root,par);
		if(tmp==NULL)
		{
			cout<<"\nParent not found ";
			return ;
		}

		cout<<"\nEnter direction (l/r) : ";
		cin>>dir;

		if(dir=='l' || dir=='L')
		{
			if(tmp->lc!=NULL)
			{
				cout<<"\nLeft side of parent is not empty";
				return;
			}
			tmp->lc=newn;
		}
		else if(dir=='r' || dir=='R')
		{
			if(tmp->rc!=NULL)
			{
				cout<<"\nRight side of parent is not empty";
				return;
			}
			tmp->rc=newn;
		}
	}

	void inorder(Node *r)
	{
		if(r)
		{
			inorder(r->lc);
			cout<<"  "<<r->data;
			inorder(r->rc);
		}
	}

	void preorder(Node *r)
	{
		if(r)
		{
			cout<<" "<<r->data;
			preorder(r->lc);
			preorder(r->rc);
			preorder(r->nc);
		}
	}

	Node *getRoot()
	{
		return root;
	}

	char findDir(int n,Node *r)
	{
		if(find(r->lc,n))
			return 'l';
		else
			return 'r';
	}

	void replaceRoot(int n,Node *r)
	{
		Node *tmp;
		if(r->data==n)
		{
			root=r;
			return;
		}
		char ch=findDir(n,r);
		if(ch=='r')
		{
			tmp=r->rc;
			r->rc=NULL;
			tmp->nc=r;
			root=tmp;
			replaceRoot(n,tmp);
		}
		else if(ch=='l')
		{
			tmp=r->lc;		
			r->lc=NULL;
			tmp->nc=r;	
			root=tmp;		
			replaceRoot(n,tmp);
		}
	}
};


int main()
{
	BinaryTree bt;
	int val;
	for(int i=0;i<6;i++)
	{
		cout<<"\nEnter value : ";
		cin>>val;
		bt.insert(val);
	}
	bt.inorder(bt.getRoot());
	cout<<"\nEnter replacement root : ";
	cin>>val;
	bt.replaceRoot(val,bt.getRoot());
	bt.preorder(bt.getRoot());
	return 0;
}




	