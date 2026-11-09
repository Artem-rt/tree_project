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

void link_left (struct Tree_Node* child, struct Tree_Node* parent, struct Tree* tree)
{
    assert (child);
    assert (parent);
    assert (tree);

    parent -> left_child_node = child;
    child -> parent_node = parent;
    tree -> cnt_nodes ++ ;
}

void link_right (struct Tree_Node* child, struct Tree_Node* parent, struct Tree* tree)
{
    assert (child);
    assert (parent);
    assert (tree);

    parent -> right_child_node = child;
    child -> parent_node = parent;
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

void dump_node (struct Tree_Node* node_dump, FILE* dump_file)
{
    assert (node_dump);
    assert (dump_file);

    fprintf (dump_file, "node%p [label = \"{parent : %p|data : " SPECIF_TYPE "|{<left>left_child : %p|<right>right_child : %p}}\"];\n",
             node_dump, node_dump -> parent_node, node_dump -> data, node_dump -> left_child_node, node_dump -> right_child_node);

    if (node_dump -> left_child_node)
    {
        dump_node (node_dump -> left_child_node, dump_file);
        dump_link (node_dump, node_dump -> left_child_node, dump_file);
    }
    if (node_dump -> right_child_node)
    {
        dump_node (node_dump -> right_child_node, dump_file);
        dump_link (node_dump, node_dump -> right_child_node, dump_file);
    }
    if (node_dump -> left_child_node && node_dump -> right_child_node)
    {
        dump_rang (node_dump -> left_child_node, node_dump -> right_child_node, dump_file);
    }
}

void dump_link (struct Tree_Node* parent_node, struct Tree_Node* child_node, FILE* dump_file)
{
    assert (parent_node);
    assert (child_node);

    if (parent_node -> left_child_node == child_node)
    {
        fprintf (dump_file, "node%p:left -> node%p;\n", parent_node, child_node);
    } else if (parent_node -> right_child_node == child_node)
    {
        fprintf (dump_file, "node%p:right -> node%p;\n", parent_node, child_node);
    } else
    {
        printf ("parent_node == %p, parent->left == %p, parent->right == %p, child == %p, child->parent == %p\n",
                parent_node, parent_node -> left_child_node, parent_node -> right_child_node, child_node, child_node -> parent_node);
        assert (false);
    }
}

void dump_rang (struct Tree_Node* child_one, struct Tree_Node* child_two, FILE* dump_file)
{
    assert (child_one);
    assert (child_two);

    fprintf (dump_file, "{rank = same; node%p; node%p};\n", child_one, child_two);
}

void dump_tree (struct Tree* tree)
{
    assert (tree);

    FILE* dump_file = NULL;
    static int cnt_call = 0;
    char name_command [512];

    cnt_call ++;
    sprintf (name_command, "dot " DUMP_FILE " -Tpng -o dumps/dump_%d.png", cnt_call);

    if ((dump_file = fopen(DUMP_FILE, "w")) == NULL)
    {
        printf ("sorry, dump_file can not open :(\n");
        assert (false);
    }

    fprintf (dump_file, "digraph DUMP_LIST {\n");
    fprintf (dump_file, "newrank = true;\nnode [shape = Mrecord];\n");
    dump_node (tree -> root_node, dump_file);
    fprintf (dump_file, "}");

    fflush (dump_file); //clear buffer
    system (name_command);
    fclose (dump_file);
}

#endif
