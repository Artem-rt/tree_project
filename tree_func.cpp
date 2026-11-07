#ifndef TREE_FUNC_CPP
#define TREE_FUNC_CPP

#include <stdio.h>
#include <assert.h>
#include "tree.h"

void tree_init (struct Tree* new_tree, struct Tree_Node** root_node)
{
    assert (new_tree);
    assert (root_node);

    new_tree -> root_node = (*root_node);
    new_tree -> cnt_nodes = 1;
}

void create_node (struct Tree_Node** new_node, TYPE_OF_TREE_ELEM argument)
{
    assert (new_node);

    if (((*new_node) = (struct Tree_Node*) calloc (1, sizeof (struct Tree_Node))) == NULL)
    {
        printf ("Sorry, can not create new node\n");
        assert (false);
    }

    (*new_node) -> data = argument;
    (*new_node) -> left_child_node = (*new_node) -> right_child_node = (*new_node) -> parent_node = NULL;
}

void dellite_node (struct Tree_Node** node, struct Tree* tree)
{
    assert (node);
    assert (tree);

    if ((*node) == tree -> root_node)
    {
        tree -> root_node = NULL;
        tree -> cnt_nodes = 0;
        printf ("WARNING! Your tree was dellite! You must dellite all nodes!!!");
    } else
    {
        tree -> cnt_nodes -- ;
    }

    free ((*node));
    (*node) = NULL;
}

void link_left (struct Tree_Node** child, struct Tree_Node** parent, struct Tree* tree)
{
    assert (child);
    assert (parent);
    assert (tree);

    (*parent) -> left_child_node = (*child);
    (*child) -> parent_node = (*parent);
    tree -> cnt_nodes ++ ;
}

void link_right (struct Tree_Node** child, struct Tree_Node** parent, struct Tree* tree)
{
    assert (child);
    assert (parent);
    assert (tree);

    (*parent) -> right_child_node = (*child);
    (*child) -> parent_node = (*parent);
    tree -> cnt_nodes ++ ;
}

void print_tree_preorder (struct Tree_Node* start_node) //TODO: print file
{
    assert (start_node);

    printf ("( ");
    printf (SPECIF_TYPE, start_node -> data);
    if (start_node -> left_child_node) print_tree_preorder (start_node -> left_child_node);
    else printf ("nil");
    if (start_node -> right_child_node) print_tree_preorder (start_node -> right_child_node);
    else printf ("nil");
    printf (" )");
}

void print_tree_inorder (struct Tree_Node* start_node) //TODO: print file
{
    assert (start_node);

    printf ("( ");
    if (start_node -> left_child_node) print_tree_inorder (start_node -> left_child_node);
    else printf ("nil");
    printf (SPECIF_TYPE, start_node -> data);
    if (start_node -> right_child_node) print_tree_inorder (start_node -> right_child_node);
    else printf ("nil");
    printf (" )");
}

#endif
