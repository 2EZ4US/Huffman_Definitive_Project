
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

TREE* Build_Huff_tree(FILE *loaded_file) {
    bool is_Leaf = 0;
    Byte byte = fgetc(loaded_file);
    if(byte == '\\') {
        byte = fgetc(loaded_file);
        is_Leaf = 1;
    }
    //HUFF_NODE *new_huff_node = HUFF_NODE_Create(byte, 0);
    TREE_NODE *new_tree_node = TREE_Create_Node(new_huff_node);
    if(byte == '*' && !is_Leaf) {
        new_tree_node->left = Build_Huff_Tree(loaded_file);
        new_tree_node->right = Build_Huff_Tree(loaded_file);
    }
    return new_tree_node;
}

TREE* Extract_Huff_Tree_From_File(FILE *loaded_file) {
    TREE *huff_tree = Tree_Create();
    huff_tree->head = Build_Huff_Tree(loaded_file);
    return huff_tree;
}

void Decompress(FILE *loaded_file, TREE *huff_tree, Integer trash_size) {
    FILE *decompressed_file = fopen("decompressed", "wb");
    //NEED END
}

void Decompress_File() {
    FILE *loaded_file = fopen("compressed", "rb");
    Integer trash_size = Get_Trash_Size(loaded_file);
    Integer tree_size = Get_Huff_Tree_Size(loaded_file);
    TREE *huff_tree = Extract_Huff_Tree_From_File(loaded_file);
    //Decompress(loaded_file, huff_tree, trash_size);
}
