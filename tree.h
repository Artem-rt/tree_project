#ifndef TREE_H
#define TREE_H
// -----------------------------------------------------------------------------

#include <stdio.h>

typedef char* TYPE_OF_TREE_ELEM;
#define SPECIF_TYPE "%s"

#define DUMP_FILE "tree_dump.txt"
#define PREORDER_FILE "PREORDER.txt"
#define MAX_LEN_DATA 256

struct Tree_Node
{
    char data [MAX_LEN_DATA];
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
void print_tree_preorder (struct Tree_Node* start_node, FILE* preorder_file);
void print_tree_inorder (struct Tree_Node* start_node);

void dump_node (struct Tree_Node* node_dump, FILE* dump_file);
void dump_link (struct Tree_Node* parent_node, struct Tree_Node* child_node, FILE* dump_file);
void dump_rang (struct Tree_Node* child_one, struct Tree_Node* child_two, FILE* dump_file);
void dump_tree (struct Tree* tree);
Tree_Node* parse_preorder_tree (int preorder_file);
long long read_preorder_file (int preorder_file, char** buffer);
Tree_Node* parse_node (char** buffer, long long* i_buffer);
void parse_left_son (char** buffer, long long* i_buffer, struct Tree_Node** parent_node);
void parse_right_son (char** buffer, long long* i_buffer, struct Tree_Node** parent_node);
void delete_tree (Tree_Node* root_node);
// -----------------------------------------------------------------------------
#endif
