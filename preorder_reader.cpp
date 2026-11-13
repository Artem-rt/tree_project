#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "tree.h"
#include "tree_func.cpp"

int main ()
{
    int preorder_file = 0;
    FILE* preorder_file1 = 0;

    if ((preorder_file = open (PREORDER_FILE, O_RDONLY)) == 0)
        assert (0 && "problem with preorder_file\n");

    Tree tree = { };

    tree.root_node = parse_preorder_tree (preorder_file);

    if ((preorder_file1 = fopen ("PREORDER_1.txt", "w")) == NULL)
            assert (0 && "sorry, file for preorder can not open :(");
    print_tree_preorder (tree.root_node, preorder_file1);

    dump_tree (&tree);

    delete_tree (tree.root_node);
    close (preorder_file);
}
