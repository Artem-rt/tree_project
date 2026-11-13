#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tree_func.cpp"

int main ()
{
    FILE* preorder_file = NULL;
    struct Tree tree_one = { } ;
    struct Tree_Node* root_node = NULL;
    struct Tree_Node* node_rl = NULL;
    struct Tree_Node* node_rr = NULL;
    struct Tree_Node* node_rll = NULL;
    struct Tree_Node* node_rlr = NULL;
    struct Tree_Node* node_rrl = NULL;
    struct Tree_Node* node_rrr = NULL;

    create_node (&root_node, (char*)"cheloveck?");
    tree_init (&tree_one, &root_node);

    // dump_tree (&tree_one);

    create_node (&node_rl, (char*)"LOX?");
    link_left (node_rl, root_node, &tree_one);

    // dump_tree (&tree_one);

    create_node (&node_rr, (char*)"cat?");
    link_right (node_rr, root_node, &tree_one);

    // dump_tree (&tree_one);

    create_node (&node_rll, (char*)"1.5shka");
    link_left (node_rll, node_rl, &tree_one);

    // dump_tree (&tree_one);

    create_node (&node_rlr, (char*)"ded");
    link_right (node_rlr, node_rl, &tree_one);

    // dump_tree (&tree_one);

    create_node (&node_rrl, (char*)"kolia");
    link_left (node_rrl, node_rr, &tree_one);

    // dump_tree (&tree_one);

    create_node (&node_rrr, (char*)"DIA");
    link_right (node_rrr, node_rr, &tree_one);

    // dump_tree (&tree_one);

    if ((preorder_file = fopen (PREORDER_FILE, "w")) == NULL)
            assert (0 && "sorry, file for preorder can not open :(");
    print_tree_preorder (tree_one.root_node, preorder_file);
    printf ("\n");

    print_tree_inorder (tree_one.root_node);
    printf ("\n");

    dellite_node (&node_rlr, &tree_one);
    // dump_tree (&tree_one);
    dellite_node (&node_rll, &tree_one);
    dellite_node (&node_rrr, &tree_one);
    dellite_node (&node_rrl, &tree_one);
    dellite_node (&node_rl, &tree_one);
    dellite_node (&node_rr, &tree_one);
    dellite_node (&root_node, &tree_one);

    fclose (preorder_file);
}
