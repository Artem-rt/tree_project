#ifndef TREE_FUNC_CPP
#define TREE_FUNC_CPP

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <sys/stat.h>
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

    int len_data = 0;

    if (((*new_node) = (struct Tree_Node*) calloc (1, sizeof (struct Tree_Node))) == NULL)
    {
        printf ("Sorry, can not create new node\n");
        assert (false);
    }

    for (int i = 0; argument [i] != '\0'; i ++)
    {
        (*new_node) -> data [i] = argument [i];
        len_data ++ ;
    }
    (*new_node) -> data [++len_data] = '\0';
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
        if ((*node) -> parent_node->left_child_node == (*node))
            (*node) -> parent_node->left_child_node = NULL;
        else
            (*node) -> parent_node->right_child_node = NULL;
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

void print_tree_preorder (struct Tree_Node* start_node, FILE* preorder_file) //TODO: print file
{
    assert (start_node);
    assert (preorder_file);

    fprintf (preorder_file, "(");
    fprintf (preorder_file, SPECIF_TYPE, start_node -> data);
    if (start_node -> left_child_node) print_tree_preorder (start_node -> left_child_node, preorder_file);
    else fprintf (preorder_file, "(#)");
    if (start_node -> right_child_node) print_tree_preorder (start_node -> right_child_node, preorder_file);
    else fprintf (preorder_file, "(#)");
    fprintf (preorder_file, ")");
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

    if (node_dump -> parent_node == NULL)
        fprintf (dump_file, "node%p [color = \"#480b41\", fillcolor = \"#ff00d953\", style = filled, label = \"{parent : %p|data : " SPECIF_TYPE "|{<left>left_child : %p|<right>right_child : %p}}\"];\n",
             node_dump, node_dump -> parent_node, node_dump -> data, node_dump -> left_child_node, node_dump -> right_child_node);
    else if (node_dump -> left_child_node == NULL && node_dump -> right_child_node == NULL)
        fprintf (dump_file, "node%p [color = \"#20480b\", fillcolor = \"#11712477\", style = filled, label = \"{parent : %p|data : " SPECIF_TYPE "|{<left>left_child : %p|<right>right_child : %p}}\"];\n",
             node_dump, node_dump -> parent_node, node_dump -> data, node_dump -> left_child_node, node_dump -> right_child_node);
    else
        fprintf (dump_file, "node%p [color = \"#1f0b48\", fillcolor = \"#0400ff77\", style = filled, label = \"{parent : %p|data : " SPECIF_TYPE "|{<left>left_child : %p|<right>right_child : %p}}\"];\n",
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
    assert (dump_file);

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
        assert (0 && "something");
    }
}

void dump_rang (struct Tree_Node* child_one, struct Tree_Node* child_two, FILE* dump_file)
{
    assert (child_one);
    assert (child_two);
    assert (dump_file);

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

Tree_Node* parse_preorder_tree (int preorder_file)
{
    assert (preorder_file);

    char* buffer = NULL;
    long long i_buffer = 0;
    Tree_Node* root_node = NULL;

    read_preorder_file (preorder_file, &buffer);

    root_node = parse_node (&buffer, &i_buffer);

    return root_node;
}

long long read_preorder_file (int preorder_file, char** buffer)
{
    assert (preorder_file);
    assert (buffer);

    struct stat file_size = { .st_size = 0 } ;
    long long len_buffer = 0;

    stat (PREORDER_FILE, &file_size);

    if (((*buffer) = (char*)calloc (1, file_size.st_size)) == NULL)
    {
        assert (0 && ("calloc can not find memory for buffer\n"));
    }


    if ((len_buffer = read (preorder_file, (*buffer), file_size.st_size)) == 0)
    {
        printf ("commands array didn't create, sorry...\nfile: %s, func: main.cpp: %d\n", __FILE__, __LINE__);
        assert (false);
    }

    (*buffer) [len_buffer] = '\0' ;

    return len_buffer;
}

Tree_Node* parse_node (char** buffer, long long* i_buffer)
{
    assert (buffer);
    assert (i_buffer);

    // if ((*buffer) [*i_buffer + 1] == '\n')
    //     return NULL;

    if ((*buffer) [*i_buffer] != '(')
        assert (0 && "error call parse_node, buffer [i_buffer] != \'(\'\n");

    struct Tree_Node* new_node = NULL;
    char now_data [MAX_LEN_DATA] = "";
    long long i_now_data = 0;

    (*i_buffer) ++ ;

    while ((*buffer) [*i_buffer] != '(' && (*buffer) [*i_buffer] != ')' && (*buffer) [*i_buffer] != '\n' )
    {
        now_data [i_now_data] = (*buffer) [*i_buffer];
        i_now_data ++ ;
        (*i_buffer) ++ ;
    }
    create_node (&new_node, now_data);

    if ((*buffer) [*i_buffer] == '\n')
        assert (0 && "sintaxis error\n");

    if ((*buffer) [*i_buffer] == ')')
    {
        (*i_buffer) ++;
        return new_node;
    }

    if ((*buffer) [*i_buffer] == '(')
    {
        parse_left_son (buffer, i_buffer, &new_node);
        if ((*buffer) [*i_buffer] == '(')
        {
            parse_right_son (buffer, i_buffer, &new_node);
        }
        if ((*buffer) [*i_buffer] != '(')
            while ((*buffer) [*i_buffer] != '(')
                (*i_buffer) ++ ;
        // if (isdigit ((*buffer) [*i_buffer])) (*i_buffer) --;
        return new_node;
    }

    return NULL;
}

void parse_left_son (char** buffer, long long int* i_buffer, struct Tree_Node** parent_node)
{
    assert (buffer);
    assert (i_buffer);

    if ((*buffer) [*i_buffer] != '(')
        assert (0 && "error call parse_node, buffer [i_buffer] != \'(\'\n");

    (*i_buffer) ++ ;

    if ((*buffer) [*i_buffer] == '#')
    {
        (*parent_node) -> left_child_node = NULL;
        (*i_buffer) += 2;
        return;
    }

    (*i_buffer) -- ;

    struct Tree_Node* new_node = NULL;
    new_node = parse_node (buffer, i_buffer);
    new_node -> parent_node = (*parent_node);
    (*parent_node) -> left_child_node = new_node;
}


void parse_right_son (char** buffer, long long* i_buffer, struct Tree_Node** parent_node)
{
    assert (buffer);
    assert (i_buffer);
    assert (parent_node);
    assert (*parent_node);

    if ((*buffer) [*i_buffer] != '(')
        assert (0 && "error call parse_node, buffer [i_buffer] != \'(\'\n");

    (*i_buffer) ++ ;

    if ((*buffer) [*i_buffer] == '#')
    {
        (*parent_node) -> right_child_node = NULL;
        (*i_buffer) += 1;
        return;
    }

    (*i_buffer) -- ;

    struct Tree_Node* new_node = NULL;
    new_node = parse_node (buffer, i_buffer);
    (*new_node).parent_node = (*parent_node);
    (*parent_node) -> right_child_node = new_node;
}

void delete_tree (Tree_Node* root_node)
{
    if (root_node -> left_child_node)
        delete_tree (root_node -> left_child_node);
    if (root_node -> right_child_node)
        delete_tree (root_node -> right_child_node);

    free (root_node);
    root_node = NULL;
}
#endif
