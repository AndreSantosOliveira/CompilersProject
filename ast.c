#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

// create a node of a given category with a given lexical symbol
struct node *newnode(enum category category, char *token)
{
    struct node *new = malloc(sizeof(struct node));
    new->category = category;
    new->token = token;
    new->children = malloc(sizeof(struct node_list));
    new->children->node = NULL;
    new->children->next = NULL;
    return new;
}

// append a node to the list of children of the parent node
void addchild(struct node *parent, struct node *child)
{
    struct node_list *new = malloc(sizeof(struct node_list));
    new->node = child;
    new->next = NULL;
    struct node_list *children = parent->children;
    while (children->next != NULL)
        children = children->next;
    children->next = new;
}

void show(struct node *node, int depth)
{
    const char *category_names[] = {
        "Program",
        "Function",
        "Parameters",
        "Parameter",
        "Arguments",
        "Integer",
        "Double",
        "Identifier",
        "Natural",
        "Decimal",
        "Call",
        "If",
        "Add",
        "Sub",
        "Mul",
        "Div"};

    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < depth; i++)
    {
        printf("__");
    }

    // Print the node's category and token (if it exists)
    printf("%s", category_names[node->category]);
    if (node->token != NULL)
    {
        printf("(%s)\n", node->token);
    }
    else
    {
        printf("\n");
    }

    // Recursively traverse and display children
    struct node_list *children = node->children;
    while (children != NULL)
    {
        show(children->node, depth + 1);
        children = children->next;
    }
}

// Free program tree
void free_tree(struct node *root)
{
    if (root == NULL)
    {
        return;
    }

    // Recursively free children
    struct node_list *children = root->children;
    while (children != NULL)
    {
        struct node *child = children->node;
        free_tree(child);
        children = children->next;
    }

    // Free the current node
    free(root->token); // Free any allocated token string
    free(root);
}
