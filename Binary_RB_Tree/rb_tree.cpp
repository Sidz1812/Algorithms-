#include "rb_tree.h"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
    rb_tree::rb_tree()
{ /*<<<*/
/*
 * create T_nil element
 */
  T_nil = new rb_tree_node();
  T_nil->color = RB_BLACK;
  T_nil->p = T_nil;
  T_nil->left = T_nil;
  T_nil->right = T_nil;

/*
 * root of rb tree
 */
  T_root = T_nil;
} /*>>>*/

rb_tree::~rb_tree()
{ /*<<<*/ 
/*
 * delete nil element and all other allocated nodes
 */
  remove_all(T_root);

  delete T_nil;
} /*>>>*/

void rb_tree::insert(int* key_array, int n)
{ 
     input_rbt = n;
  for (int i = 0; i < n; i++)
             insert(key_array[i]);
} 

void rb_tree::insert(int key)
{ /*<<<*/
/*
 * wrapper around insert
 * -> creates black node with key
 * -> inserts node
 */
  rb_tree_node* z;

  z = new rb_tree_node;
  z->color = RB_BLACK;
  z->key = key;

  insert(z);
} /*>>>*/

void rb_tree::insert(rb_tree_node* z)
{ /*<<<*/
/*
 * binary tree type insert 
 * -> search position, insert new node
 * -> fix properties after insert
 */



  rb_tree_node* x;
  rb_tree_node* y;

  y = T_nil;
  x = T_root;


  while (x != T_nil)           //checking duplicates
    {
      y = x;
      if(z->key == x->key)
      {
          i_duplicate++;
          return;
      }
        
      else if (z->key < x->key)
      x = x->left;
        
      else 
      x = x->right;
    }




  z->p = y;
  if (y == T_nil)
    T_root = z;
    
  else
    {
      if (z->key < y->key)
	y->left = z;
      else
	y->right = z;
    }

  z->left = T_nil;
  z->right = T_nil;
  z->color = RB_RED;



  insert_fixup(z);



} /*>>>*/

void rb_tree::insert_fixup(rb_tree_node*& z)

{ /*<<<*/
/*
 * fix RB tree properties, after inserting a node
 * -> see book/slides for details on the cases
 */
  rb_tree_node* y;

  while (z->p->color == RB_RED)
    {
      if (z->p == z->p->p->left)
	{
	  y = z->p->p->right;

	  if (y->color == RB_RED)
	    {
        i_case1++;
	      z->p->color = RB_BLACK;		// Case 1
	      y->color = RB_BLACK;
	      z->p->p->color = RB_RED;
	      z = z->p->p;
	    }
	  else
	    {
	      if (z == z->p->right)
		{
      i_case2++;
		  z = z->p;		            	// Case 2
		  left_rotate(z);
		}
        i_case3++;
	      z->p->color = RB_BLACK;		// Case 3
	      z->p->p->color = RB_RED;
	      right_rotate(z->p->p);
	    }
	}
      else
	{

	  y = z->p->p->left;

	  if (y->color == RB_RED)
	    {
        i_case1++;
	      z->p->color = RB_BLACK;		// Case 1
	      y->color = RB_BLACK;
	      z->p->p->color = RB_RED;
	      z = z->p->p;
	    }
	  else
	    {
	      if (z == z->p->left)
		{
      i_case2++;
		  z = z->p;			            // Case 2
		  right_rotate(z);
		}
        i_case3++;
	      z->p->color = RB_BLACK;		// Case 3
	      z->p->p->color = RB_RED;
	      left_rotate(z->p->p);
	    }
	}
    }

  T_root->color = RB_BLACK;
} /*>>>*/


void rb_tree::left_rotate(rb_tree_node* x)
{ /*<<<*/
/*
 * rotate left -> see book/slides
 */
  rb_tree_node* y;

  y = x->right;			// set y
  x->right = y->left;		
  if (y->left != T_nil)
    y->left->p = x;

  y->p = x->p;			// link x's parent to y
  if (x->p == T_nil)
    T_root = y;
  else
    {
      if (x == x->p->left)
	x->p->left = y;
        
      else
	x->p->right = y;
    }

  y->left = x;			// put x on y's left
  x->p = y;
  i_leftrotate++;
} /*>>>*/

void rb_tree::right_rotate(rb_tree_node* x)
{ /*<<<*/
/*
 * rotate right -> see book/slides
 */
  rb_tree_node* y;

  y = x->left;			// set y
  x->left = y->right;		

  if (y->right != T_nil)
    y->right->p = x;
    y->p = x->p;
    
  if (x->p == T_nil)
    T_root = y;
    
  else
    {
      if (x == x->p->right)
	x->p->right = y;
      else
	x->p->left = y;
    }

  y->right = x;			// put x on y's right
  x->p = y;
  i_rightrotate++;  
} /*>>>*/

void rb_tree::inorder_output(rb_tree_node* x, int* input_array, int level)
{ /*<<<*/
/*
 * in order walk through binary tree
 * -> see book or slides
 */
  if (x != T_nil)

    {

      inorder_output(x->left, input_array, level+1);

      //cout << "(" << x->key << "," << level << "," << ((x->color == RB_RED) ? "R" : "B") << ")" << endl;

      input_array[array_index_rbt] = x->key; 
      array_index_rbt++;
      inorder_output(x->right, input_array, level+1); 

    }
} /*>>>*/






void rb_tree::output(rb_tree_node* x, int r_level)
{ /*<<<*/
    /*
     * some structured output
     */
  list< pair<rb_tree_node*,int> > lNodes;
  pair<rb_tree_node*,int> cNode;
  int cLevel;

  cLevel = r_level;
   lNodes.insert( lNodes.end(), pair<rb_tree_node*,int>(x, r_level));

  while (! lNodes.empty())
    {
      cNode = *( lNodes.begin());

      if (cLevel < cNode.second)
        {
          cout << endl;
          cLevel = cNode.second;
          cout << "(" << cNode.first->key << "," << ((cNode.first->color == RB_RED) ? "R" : "B");
        }

      else if (cNode.first->p == T_nil)
          cout << ",ROOT) ";
        
      else
          cout << ",P:" << cNode.first->p->key << ") ";
        

     if (cNode.first->left != T_nil)
         lNodes.insert( lNodes.end(), pair<rb_tree_node*,int>(cNode.first->left, cNode.second+1));
        
     else
         lNodes.insert( lNodes.end(), pair<rb_tree_node*,int>(cNode.first->right, cNode.second+1));
         lNodes.erase( lNodes.begin());
    }

  cout << endl;
} /*>>>*/






void rb_tree::remove_all(rb_tree_node* x)
{ /*<<<*/
/*
 * recursively remove all tree elements
 */
  if (x != T_nil)


    {
      remove_all(x->left);
      remove_all(x->right);

      delete x;
    }
} /*>>>*/





 int rb_tree::black_height(rb_tree_node* x)
{    
      if(x != T_nil)

     {
        leftHeight = black_height(x->left);
        rightHeight = black_height(x->right);
    

       if (leftHeight == rightHeight)

    {       
         if(x->color == RB_BLACK){       
         leftHeight++;

    }
         return leftHeight;
    }

    else
    {
      cout<<"Property 5 failed"<<endl;
    } 
}
else
{
  return 0;
}
    return 0;
}
