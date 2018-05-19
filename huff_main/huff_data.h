#ifndef HUFF_DATA_AHRT
#define HUFF_DATA_AHRT

typedef struct HUFF_DATA {
    Byte  character;
    INTEGER frequency;
} HUFF_DATA;

HUFF_DATA* HUFF_DATA_Create(Byte character, INTEGER frequency) {
    HUFF_DATA* new_huff_data = (HUFF_DATA*) malloc(sizeof(HUFF_DATA));
    new_huff_data->character = character;
    new_huff_data->frequency = frequency;
    return new_huff_data;
}

Byte  HUFF_DATA_Get_Character(HUFF_DATA *huff_data) {
	return huff_data->character;
}

INTEGER HUFF_DATA_Get_Frequency(HUFF_DATA *huff_data) {
	return huff_data->frequency;
}

GENERIC HUFF_DATA_Create_Merged(HUFF_DATA *second, HUFF_DATA *first) {
	HUFF_DATA* new_huff_data = (HUFF_DATA*) malloc(sizeof(HUFF_DATA));
	new_huff_data->character = '*';
	new_huff_data->frequency = second->frequency + first->frequency;
	return new_huff_data;
}

bool HUFF_DATA_Botton_Up_Cmp(TREE_NODE *current, TREE_NODE *parent){
	if(HUFF_DATA_Get_Frequency(current->data) < HUFF_DATA_Get_Frequency(parent->data) || 
		((HUFF_DATA_Get_Frequency(current->data) == HUFF_DATA_Get_Frequency(parent->data) ) 
			&& HUFF_DATA_Get_Character(current->data) == '*')) {
		return true;
	}
	return false;
}

bool HUFF_DATA_Top_Down_Cmp(TREE_NODE *current, TREE_NODE *next){
	if(HUFF_DATA_Get_Frequency(current->data) > HUFF_DATA_Get_Frequency(next->data) || 
		((HUFF_DATA_Get_Frequency(current->data) == HUFF_DATA_Get_Frequency(next->data)) 
			&& (HUFF_DATA_Get_Character(current->data) != '*'
			&& HUFF_DATA_Get_Character(next->data) == '*'))) {
		return true;
	}
	return false;
}

#endif
