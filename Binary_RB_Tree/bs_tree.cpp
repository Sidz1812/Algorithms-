#include "bs_tree.h"
#include <iostream>
#include <list>

using namespace std;
/*
 * constructor/destructor
 */
bs_tree::bs_tree()
{
  T_root = new bs_tree_node();
  T_root->p = NULL;
  T_root->left = NULL;
  T_root->right = NULL;
}

bs_tree::~bs_tree()
{
/*
 * delete nil element and all other allocated nodes
 */
  remove(T_root);
} /*>>>*/

void bs_tree::insert(int* key_array, int n)
{
  input_bst = n;
  for (int i = 0; i < n; i++)
   { 
    insert(key_array[i]);
   }
    
}

void bs_tree::insert(int key)
{
  bs_tree_node* z;
  z = new bs_tree_node;
  z->key = key;
  insert(z);
} /*>>>*/

void bs_tree::insert(bs_tree_node* z)
{
/*
 * binary tree type insert 
 * -> search position, insert new node
 */


  bs_tree_node* x;
  bs_tree_node* y;

  y = NULL;
  x = T_root;
  while (x != NULL)
    {
      y = x;
      if(z->key == x->key)
      {
          duplicate_bst++;
          return;
      }
        
      else if (z->key < x->key)
      x = x->left;
        
      else 
      x = x->right;
    }

  z->p = y;
  if (y == NULL)
    T_root = z;
    
  else if (z->key < y->key)
	y->left = z;
    
  else
	y->right = z;

  z->left = NULL;
  z->right = NULL;
  } /*>>>*/

void bs_tree::remove(bs_tree_node* x)
{ 
  if (x != NULL)
    {
      remove(x->left);
      remove(x->right);
      delete x;
    }
} /*>>>*/

void bs_tree::InorderOutput(bs_tree_node* x, int* input_array)
{ 
    if (x != NULL) 
    { 
        InorderOutput(x->left, input_array);
        input_array[array_index_bst] = x->key; 
        array_index_bst++;
        InorderOutput(x->right, input_array); 
    } 
}
