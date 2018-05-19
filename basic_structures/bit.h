#ifndef BIT_AHRT
#define BIT_AHRT

typedef struct BIT_MANIP {
    Byte byte, position;
} BIT_MANIP;


BIT_MANIP* BIT_MANIP_Create() {
	BIT_MANIP *byte_to_brush = (BIT_MANIP*) malloc(sizeof(BIT_MANIP));
    byte_to_brush->byte = 0;
    byte_to_brush->position = 7;
}

void BIT_Set_Bit(INTEGER *byte, INTEGER position) {
    INTEGER mask = 1 << position;
    (*byte) = (*byte) | mask;
    return;
}

bool BIT_Is_Set(INTEGER *byte, INTEGER position) {
    INTEGER mask = 1 << position;
    return (*byte) & mask;
}

bool BIT_Error_In_Advance_Position(BIT_MANIP *byte_to_brush) {
    if(byte_to_brush->position == 0) {
        byte_to_brush->position = 7;
        return true;
    } else {
        byte_to_brush->position -= 1;
        return false;
    }
}

#endif
