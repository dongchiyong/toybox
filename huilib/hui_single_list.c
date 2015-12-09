#include <stdlib.h>
#include <stdio.h>
#include "hui_single_list.h"

HuiSingleList* create_list()
{
	HuiSingleList *ptr = (HuiSingleList *)malloc(sizeof(HuiSingleList));
	if (ptr != NULL){
		ptr->head_ = NULL;
		ptr->tail_ = NULL;
	}

	return ptr;
}

int push_back(HuiSingleList* list_ptr, int data)
{
	HuiSingleListNode *ptr = (HuiSingleListNode *)malloc(sizeof(HuiSingleListNode));
	if (ptr != NULL)
	{
		ptr->next_ = NULL;
		ptr->data_ = data;
	}
	else
	{
		printf("[ERROR] push_back: malloc failed\n");
		return -1;
	}

	if (list_ptr->tail_ == NULL) {
		list_ptr->head_ = list_ptr->tail_ = ptr;
	}
	else {
	       	list_ptr->tail_->next_ = ptr;
	       	list_ptr->tail_ = ptr;
	}

	return 0;
}

void reverse_list(HuiSingleList *list_ptr)
{
	HuiSingleListNode *cur, *pre;

	if (list_ptr->head_ == NULL){
		return;
	}

	pre = list_ptr->head_;
	cur = list_ptr->head_->next_;
	while(cur != NULL){
		pre->next_ = cur->next_;
		cur->next_ = list_ptr->head_;
		list_ptr->head_ = cur;
		if (cur->next_ == NULL){
			list_ptr->tail_ = cur;
		}
		cur = pre->next_;
	}
}

void dump_list(HuiSingleList *list_ptr)
{
	HuiSingleListNode *cur;

	cur = list_ptr->head_;
	while(cur){
		printf("%d\t", cur->data_);
		cur = cur->next_;
	}

	printf("\n");
}

