#ifndef TREE_H
#define TREE_H
// -----------------------------------------------------------------------------

#include <stdio.h>

typedef int TYPE_OF_TREE_ELEM;
#define SPECIF_TYPE "%d"

#define DUMP_FILE "tree_dump.txt"

struct Tree_Node
{
    TYPE_OF_TREE_ELEM data;
    Tree_Node* left_child_node;
    Tree_Node* right_child_node;
    Tree_Node* parent_node;
} ;

struct Tree
{
    Tree_Node* root_node;
    long long cnt_nodes;
} ;


void tree_init (struct Tree* new_tree, struct Tree_Node** root_node);
void create_node (struct Tree_Node** new_node, TYPE_OF_TREE_ELEM argument);
void dellite_node (struct Tree_Node** node, struct Tree* tree);
void link_left (struct Tree_Node* sun, struct Tree_Node* parent, struct Tree* tree);
void link_right (struct Tree_Node* child, struct Tree_Node* parent, struct Tree* tree);
void print_tree_preorder (struct Tree_Node* start_node);
void print_tree_inorder (struct Tree_Node* start_node);

void dump_node (struct Tree_Node* node_dump, FILE* dump_file);
void dump_link (struct Tree_Node* parent_node, struct Tree_Node* child_node, FILE* dump_file);
void dump_rang (struct Tree_Node* child_one, struct Tree_Node* child_two, FILE* dump_file);
void dump_tree (struct Tree* tree);
// -----------------------------------------------------------------------------
#endif
