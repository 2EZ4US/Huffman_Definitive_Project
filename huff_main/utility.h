#ifndef UTILITY_AHRT
#define UTILITY_AHRT

FILE* U_Read_From_Stream() {
    char *string = (char*) malloc(MAX_STRING_SIZE * sizeof(char));
    printf("Source file name: ");
    scanf(" %[^\n]s", string);
    FILE *loaded_file = fopen(string, "rb");
    //free(string);
    return loaded_file;
}


void U_Pre_Order_Walk_Debug(TREE_NODE *tree_node) {
    if(tree_node == NULL)
        return;
    if(tree_node->left == NULL && tree_node->right == NULL) {

    }
    printf("%c ", HUFF_DATA_Get_Character(tree_node->data));
    U_Pre_Order_Walk_Debug(tree_node->left);
    U_Pre_Order_Walk_Debug(tree_node->right);
}

void U_HASHING_Pre_Order_Walk(TREE_NODE *tree_node, LIST *list, HASH *cmpressed_repr) {
  
}

void U_PRINTING_Pre_Order_Walk(TREE_NODE *tree_node, FILE *compressed_file) {
    if(tree_node == NULL)
        return;
    if(tree_node->left == NULL && tree_node->right == NULL) {
        if(HUFF_DATA_Get_Character(tree_node->data) == '*' ||
            HUFF_DATA_Get_Character(tree_node->data) == '\\') {
            fputc('\\', compressed_file);
        }
    }
    printf("%c", HUFF_DATA_Get_Character(tree_node->data));
    fputc(HUFF_DATA_Get_Character(tree_node->data), compressed_file);
    U_PRINTING_Pre_Order_Walk(tree_node->left, compressed_file);
    U_PRINTING_Pre_Order_Walk(tree_node->right, compressed_file);
    return;
}

#endif