
Integer Get_Trash_Size(FILE *loaded_file) {
    rewind(loaded_file);
    Integer trash_size = fgetc(loaded_file) >> 5;
    return trash_size;
}

Integer Get_Huff_Tree_Size(FILE *loaded_file) {
    rewind(loaded_file);
    Integer first_byte = fgetc(loaded_file) << 8;
    Integer second_byte = fgetc(loaded_file);
    first_byte = first_byte | second_byte;
    Integer tree_size = 0;

    for(Integer i = 12; i >= 0; i--) {
        if(Bit_Is_Set(&first_byte, i)) {
            Bit_Set_Bit(&tree_size, i);
        }
    }
    return tree_size;
}

TREE_NODE* Build_Huff_Tree(FILE *loaded_file, Byte key) {
    TREE_NODE *new_tree_node = TREE_NODE_Create(key);
    if(key == '\\') {
        new_tree_node = fgetc(loaded_file);
    }
    if(key == '*') {
        new_tree_node->left = Build_Huff_Tree(loaded_file, fgetc(loaded_file));
        new_tree_node->right = Build_Huff_Tree(loaded_file, fgetc(loaded_file));
    }
    return new_tree_node;
}

BINARY_TREE* Extract_Huff_Tree_From_File(FILE *loaded_file) {
    BINARY_TREE *huff_tree = TREE_Create();
    huff_tree->root = Build_Huff_Tree(loaded_file, fgetc(loaded_file));
    return huff_tree;
}

void Decompress(FILE *loaded_file, BINARY_TREE *huff_tree, Integer trash_size) {
    FILE *decompressed_file = fopen("decompressed", "wb");
    //NEED END
}

void Decompress_File() {
    FILE *loaded_file = fopen("compressed", "rb");
    Integer trash_size = Get_Trash_Size(loaded_file);
    Integer tree_size = Get_Huff_Tree_Size(loaded_file);
    BINARY_TREE *huff_tree = Extract_Huff_Tree_From_File(loaded_file);
    //Decompress(loaded_file, huff_tree, trash_size);
}
