#ifndef __BS_TREE_H__
#define __BS_TREE_H__
#include <iostream>
using namespace std;

struct bs_tree_node
{
    int key;
    bs_tree_node* left;
    bs_tree_node* right;
    bs_tree_node* p;
};

struct bs_tree_i_info
{
  int i_duplicate;

  void reset()
    { i_duplicate = 0; }
};

class bs_tree
{ 
  protected:
    bs_tree_node*    T_nil;
    bs_tree_node* T_root;
    
  public:
    bs_tree();
    ~bs_tree();
    void insert(bs_tree_node*);
    void remove(bs_tree_node*);
    void output(bs_tree_node*, int);
    void InorderOutput(bs_tree_node*, int*);
    
    int input_bst = 0;
    int duplicate_bst = 0;
    int array_index_bst;

    void insert(int, bs_tree_i_info&);
    int convert(int*, int);
    void insert(int*, int);
    void insert(int);

    void counter()
    {
      cout<<"Duplicates: "<<duplicate_bst<<endl;
    }
    int inorder_tree_walk(int* output_array_bst)
    {
      array_index_bst = 0;
      InorderOutput(T_root, output_array_bst);
      return input_bst-duplicate_bst;
    }
    void output()
    {
      output(T_root, 1);
    }
};

#endif
