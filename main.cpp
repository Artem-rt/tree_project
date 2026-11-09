#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tree_func.cpp"

int main ()
{
    struct Tree tree_one = { } ;
    struct Tree_Node* root_node = NULL;
    struct Tree_Node* node_rl = NULL;
    struct Tree_Node* node_rr = NULL;
    struct Tree_Node* node_rll = NULL;
    struct Tree_Node* node_rlr = NULL;


    create_node (&root_node, 10);
    tree_init (&tree_one, &root_node);

    create_node (&node_rl, 20);
    link_left (node_rl, root_node, &tree_one);

    create_node (&node_rr, 30);
    link_right (node_rr, root_node, &tree_one);

    create_node (&node_rll, 40);
    link_left (node_rll, node_rl, &tree_one);

    create_node (&node_rlr, 50);
    link_right (node_rlr, node_rl, &tree_one);

    print_tree_preorder (tree_one.root_node);
    printf ("\n");

    print_tree_inorder (tree_one.root_node);
    printf ("\n");

    dump_tree (&tree_one);

    dellite_node (&node_rlr, &tree_one);
    dellite_node (&node_rll, &tree_one);
    dellite_node (&node_rl, &tree_one);
    dellite_node (&node_rr, &tree_one);
    dellite_node (&root_node, &tree_one);

}
