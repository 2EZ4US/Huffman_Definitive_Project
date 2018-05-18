
typedef struct TREE_NODE {
    Generic data;
    struct TREE_NODE *left, *right;
} TREE_NODE;

typedef struct BINARY_TREE {
    struct TREE_NODE *root;
    Integer size;
} BINARY_TREE;

Generic TREE_Create() {
    BINARY_TREE *new_tree = (BINARY_TREE*) malloc(sizeof(BINARY_TREE));
    new_tree->root = NULL;
    new_tree->size = 0;
    return new_tree;
}

Generic TREE_NODE_Create(Generic data) {
    TREE_NODE *new_node = (TREE_NODE*) malloc(sizeof(TREE_NODE));
    new_node->data = data;
    new_node->left = new_node->right = NULL;
    return new_node;
}




