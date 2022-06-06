#ifndef __RB_TREE_H__
#define __RB_TREE_H__
#include <iostream>

using namespace std;

enum rb_tree_color 
{
  RB_RED,
  RB_BLACK
};

struct rb_tree_node 
{
  int		key;
  int		color;
  rb_tree_node*	left;
  rb_tree_node*	right;
  rb_tree_node*	p;
};

struct rb_tree_i_info
{
  int i_case_1;
  int i_case_2;
  int i_case_3;
  int i_left_rotate;
  int i_right_rotate;
  int i_duplicate;

  void reset()
    { i_case_1 = i_case_2 = i_case_3 = i_duplicate =
      i_left_rotate = i_right_rotate = 0; }
};


class rb_tree
{ 
  protected:
    rb_tree_node*	T_nil;
    rb_tree_node*	T_root;

  public:
    rb_tree();
    ~rb_tree();
    int input_rbt = 0;
    int black_height_left = 0;
    int leftHeight = 0;
    int rightHeight = 0;
    int i_duplicate = 0;
    int i_case1=0;
    int i_case2=0;
    int i_case3=0;
    int i_leftrotate=0;
    int i_rightrotate=0;
    int array_index_rbt = 0;

    void insert(int*, int);
    void insert(int);

    void counter(){
      cout<<"Case 1: "<<i_case1<<endl;
      cout<<"Case 2: "<<i_case2<<endl;
      cout<<"Case 3: "<<i_case3<<endl;
      cout<<"Left rotate: "<<i_leftrotate<<endl;
      cout<<"Right rotate: "<<i_rightrotate<<endl;
      cout<<"Duplicates="<<i_duplicate<<endl;
    }
    
    void test_black_height()
    {
      black_height_left = black_height(T_root)+1;       //Root node is always black
      cout<<"Black Height: "<<black_height_left<<endl;
      if(black_height_left){
        cout<<"Satisfies Property 5"<<endl;
      }
      else{
        cout<<"Black height check failed!"<<endl;
      }
      //cout<<"Right Black Height"<<black_height_right<<endl;
    }
    int inorder_tree_walk(int* output_array_rbt){
      array_index_rbt = 0;
      inorder_output(T_root, output_array_rbt, 1);
      return input_rbt - i_duplicate;
      }
    void output()
      {
          output(T_root, 1);
      }

  public:
    int black_height(rb_tree_node*);
    void insert(rb_tree_node*);
    void insert_fixup(rb_tree_node*&);

    void remove_all(rb_tree_node*);

    void left_rotate(rb_tree_node*);
    void right_rotate(rb_tree_node*);

    void inorder_output(rb_tree_node*, int*, int);
    void output(rb_tree_node*, int);
};

#endif
