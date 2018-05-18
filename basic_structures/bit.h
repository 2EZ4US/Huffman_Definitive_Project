
bool Bit_Is_Set(Integer *byte, Integer position) {
    Integer mask = 1 << position;
    return (*byte) & mask;
}

void Bit_Set_Bit(Integer *byte, Integer position) {
    Integer mask = 1 << position;
    (*byte) = (*byte) | mask;
    return;
}