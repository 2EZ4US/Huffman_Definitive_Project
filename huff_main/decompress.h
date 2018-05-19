#ifndef DECOMPRESS_AHRT
#define DECOMPRESS_AHRT

INTEGER Get_Trash_Size(FILE *loaded_file) {
    rewind(loaded_file);
    INTEGER trash_size = fgetc(loaded_file) >> 5;
    return trash_size;
}

INTEGER Get_Huff_Tree_Size(FILE *loaded_file) {
    rewind(loaded_file);
    INTEGER first_byte = fgetc(loaded_file) << 8;
    INTEGER second_byte = fgetc(loaded_file);
    first_byte = first_byte | second_byte;
    INTEGER tree_size = 0;

    for(INTEGER i = 12; i >= 0; i--) {
        if(BIT_Is_Set(&first_byte, i)) {
            BIT_Set_Bit(&tree_size, i);
        }
    }
    return tree_size;
}

TREE_NODE* Build_Huff_Tree(FILE *loaded_file, Byte key, INTEGER *cur_tree_size,
        INTEGER tree_size, bool *allow_decompress) {

    TREE_NODE *new_tree_node = TREE_NODE_Create(key);
    (*cur_tree_size)++;

    if((*cur_tree_size) > tree_size) {
        (*allow_decompress) = false;
        return NULL;
    }

    if(key == '\\') {
        new_tree_node->data = fgetc(loaded_file);
    }
    if(key == '*') {
        new_tree_node->left = Build_Huff_Tree(loaded_file, fgetc(loaded_file), 
            cur_tree_size, tree_size, allow_decompress);
        new_tree_node->right = Build_Huff_Tree(loaded_file, fgetc(loaded_file), 
            cur_tree_size, tree_size, allow_decompress);
    }
    return new_tree_node;
}

BINARY_TREE* Extract_Huff_Tree_From_File(FILE *loaded_file, INTEGER tree_size, 
        bool *allow_decompress) {

    BINARY_TREE *huff_tree = BINARY_TREE_Create();

    huff_tree->root = Build_Huff_Tree(loaded_file, fgetc(loaded_file), &huff_tree->size, 
        tree_size, allow_decompress);

    if(huff_tree->size < tree_size)
        (*allow_decompress) = false;

    return huff_tree;
}

void Decompress(FILE *loaded_file, BINARY_TREE *huff_tree, INTEGER trash_size) {
    FILE *decompressed_file = fopen("decompressed", "wb");
    TREE_NODE *current = huff_tree->root;
    Byte current_byte, check_is_last, stop_point;
    fpos_t stream_position;

    stop_point = 0;
    while(current_byte = fgetc(loaded_file), feof(loaded_file) != 1) {
        for(INTEGER i = 7; i >= stop_point; i--) {
            if(current->left == NULL) {
                fgetpos(loaded_file, &stream_position);

                check_is_last = fgetc(loaded_file);
                if(feof(loaded_file) == 1) {                    
                    stop_point = trash_size;
                }
                fputc(current->data, decompressed_file);
                fsetpos(loaded_file, &stream_position);
                current = huff_tree->root;
            }

            if(BIT_Is_Set(&current_byte, i)) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
    }
    printf("Success!");
    return;
}

void Decompress_File() {
    bool allow_decompress = true;
    

    FILE *loaded_file = U_Read_From_Stream();

    INTEGER trash_size = Get_Trash_Size(loaded_file);
    INTEGER tree_size = Get_Huff_Tree_Size(loaded_file);
    BINARY_TREE *huff_tree = Extract_Huff_Tree_From_File(loaded_file, tree_size, &allow_decompress);

    if(allow_decompress) 
        Decompress(loaded_file, huff_tree, trash_size);
    else printf("Not possible. File Corrupted.");

    return;    
}

#endif
