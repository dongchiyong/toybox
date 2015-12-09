#ifndef HUI_SINGLE_LIST_
#define HUI_SINGLE_LIST_

typedef struct HuiSingleListNode{
	struct HuiSingleListNode *next_;
	int data_;
} HuiSingleListNode;

typedef struct HuiSingleList{
	HuiSingleListNode *head_;
	HuiSingleListNode *tail_;
} HuiSingleList;

void dump_list(HuiSingleList *list_ptr);
void reverse_list(HuiSingleList *list_ptr);
int push_back(HuiSingleList* list_ptr, int data);
HuiSingleList* create_list();

#endif
