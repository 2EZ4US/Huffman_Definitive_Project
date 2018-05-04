

typedef struct LIST_NODE {
    Generic data;
    struct LIST_NODE *prev, *next;
} LIST_NODE;

typedef struct LIST {
    struct LIST_NODE *head, *tail;
    Integer size;
} LIST;

Generic LIST_NODE_Create(Generic data) {
    LIST_NODE *new_list_node = (LIST_NODE*) malloc(sizeof(LIST_NODE));
    new_list_node->data = data;
    new_list_node->prev = new_list_node->next = NULL;
    return new_list_node;
}

Generic LIST_Create() {
    LIST *new_list = (LIST*) malloc(sizeof(LIST));
    new_list->head = new_list->tail = NULL;
    new_list->size = 0;
    return new_list;
}

void LIST_Insert_Tail(LIST *list, Generic data) {
    if(list->head == NULL) {
        list->head = LIST_NODE_Create(data);
        list->tail = list->head;
    } else {
        list->tail->next = LIST_NODE_Create(data);
        list->tail->next->prev = list->tail;
        list->tail = list->tail->next;
    }
    list->size++;
    return;
}

void LIST_Remove_Tail(LIST *list) {
    if(list->head != NULL) {
        LIST_NODE *save_node = list->tail;
        if(list->size == 1) {
            list->head = list->tail = NULL;
        } else {
            list->tail = list->tail->prev;
            list->tail->next = NULL;
        }
        free(save_node);
    }
    list->size--;
    return;
}


