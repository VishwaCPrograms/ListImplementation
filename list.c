/* Author: Vishwa Venkateshwaran */
#include "list.h"

static List arrayList[LIST_MAX_NUM_HEADS];

static Node nodeArray[LIST_MAX_NUM_NODES];

static Node* newNode;

static List* newList;

static int initializationDone = 0;

static void initialization() {
	for (int i = 0; i < LIST_MAX_NUM_NODES - 1; i++) {
		nodeArray[i].next = &nodeArray[i + 1];
	}

	for (int j = 0; j < LIST_MAX_NUM_HEADS - 1; j++) {
		arrayList[j].next = &arrayList[j + 1];
	}

	nodeArray[LIST_MAX_NUM_NODES - 1].next = NULL;
	arrayList[LIST_MAX_NUM_HEADS - 1].next = NULL;
	newNode = &nodeArray[0];
	newList = &arrayList[0];
}

static Node* findNewNode() {
	if (newNode) {
		Node* newEmptyNode = newNode;
		newNode = newNode->next;
		newEmptyNode->next = NULL;
		newEmptyNode->previous = NULL;
		newEmptyNode->item = NULL;
		return newEmptyNode;
	} else {
		return NULL;
	}
}

static List* findNewList() {
	if (newList) {
		List* newEmptyList = newList;
		newList = newList->next;
		newEmptyList->count = 0;
		return newEmptyList;
	} else {
		return NULL;
	}
}

static void freeNode(Node* nodeToFree) {
	nodeToFree->previous = NULL;
    nodeToFree->item = NULL;
	if (newNode) {
		nodeToFree->next = newNode->next;
	}
   	newNode = nodeToFree;
}

static void freeList(List* listToFree) {
	listToFree->head = NULL;
	listToFree->tail = NULL;
	listToFree->count = 0;
	if (newList) {
		listToFree->next = newList->next;
	}
	newList = listToFree;
}



List* List_create() {
	if (initializationDone == 0) {
		initialization();
		initializationDone = 1;
	}
	List *newEmptyList = findNewList();
	if (newEmptyList) {
		newEmptyList->stateOfTheCurrentPointer = 100;
        	newEmptyList->count = 0;
        	newEmptyList->head = NULL;
       		newEmptyList->tail = NULL;
		return newEmptyList;
	} else {
		return NULL;
	}
}

int List_count(List* pList) {
	assert(pList != NULL);
	return pList->count;
}

void* List_first(List* pList) {
	assert(pList != NULL);
	if(pList->count != 0) {
		pList->current = pList->head;
		return pList->current->item;
	} 
	pList->current = NULL;
	return NULL;
}

void* List_last(List* pList) {
	assert(pList != NULL);
	if(pList->count != 0) {
		pList->current = pList->tail;
		return pList->current->item;
	}
	pList->current = NULL;
	return NULL;
}	

void* List_next(List* pList) {
	assert(pList != NULL);
	if(pList->count != 0) {
		pList->current = pList->current->next;
		if (pList->current) {
			pList->stateOfTheCurrentPointer = 100;
			return pList->current->item;
		}
		pList->stateOfTheCurrentPointer = LIST_OOB_END;
		return NULL;
	} 
	return NULL;
}

void* List_prev(List* pList) {
	assert(pList != NULL);
	if(pList->count != 0) {
		pList->current = pList->current->previous;
		if (pList->current) {
			pList->stateOfTheCurrentPointer = 100;
			return pList->current->item;
		}
		pList->stateOfTheCurrentPointer = LIST_OOB_START;
		return NULL;
	} 
	return NULL;
}

void* List_curr(List* pList) {
	assert(pList != NULL);
	if (pList->current == NULL) {
		return NULL;
	}
	return pList->current->item;
}

int List_insert_after(List* pList, void* pItem) {
	assert(pList != NULL);
	if (newNode) {
		Node *newEmptyNode = findNewNode();
        	newEmptyNode->item = pItem;
        	if (pList->count == 0) {
            		pList->head = newEmptyNode;
            		pList->tail = newEmptyNode;
		} else if (pList->count == 1) {
			newEmptyNode->next = NULL;
			newEmptyNode->previous = pList->head;
			pList->head->next = newEmptyNode;
			pList->tail = newEmptyNode;
        	} else if (pList->stateOfTheCurrentPointer == LIST_OOB_START) {
            		newEmptyNode->next = pList->head;
            		newEmptyNode->previous = NULL;
            		pList->head->previous = newEmptyNode;
            		pList->head = newEmptyNode;
		} else if (pList->current == pList->tail || pList->stateOfTheCurrentPointer == LIST_OOB_END) {
			newEmptyNode->next = NULL;
	    		newEmptyNode->previous = pList->tail;
	    		pList->tail->next = newEmptyNode;
	    		pList->tail = newEmptyNode;
		} else {
			newEmptyNode->next = pList->current->next;
			pList->current->next->previous = newEmptyNode;
			pList->current->next = newEmptyNode;
			newEmptyNode->previous = pList->current;
		}
		pList->current = newEmptyNode;
		pList->count++;
		return LIST_SUCCESS;
	} else {
		return LIST_FAIL;
	}
}

int List_insert_before(List* pList, void* pItem) {
	assert(pList != NULL);
	if (newNode) {
		Node *newEmptyNode = findNewNode();
        	newEmptyNode->item = pItem;
		if (pList->count == 0) {
            		pList->head = newEmptyNode;
           		pList->tail = newEmptyNode;
        	} else if (pList->count == 1) {
                        newEmptyNode->next = pList->head;
                        newEmptyNode->previous = NULL;
                        pList->head->previous = newEmptyNode;
                        pList->head = newEmptyNode;
                } else if (pList->stateOfTheCurrentPointer == LIST_OOB_END) {
            		newEmptyNode->next = NULL;
            		newEmptyNode->previous = pList->tail;
            		pList->tail->next = newEmptyNode;
            		pList->tail = newEmptyNode;
        	} else if (pList->current == pList->head || pList->stateOfTheCurrentPointer == LIST_OOB_START) {
            		newEmptyNode->next = pList->head;
            		newEmptyNode->previous = NULL;
            		pList->head->previous = newEmptyNode;
            		pList->head = newEmptyNode;
        	} else {
            		newEmptyNode->next = pList->current;
            		pList->current->previous->next = newEmptyNode;
            		newEmptyNode->previous = pList->current->previous;
            		pList->current->previous = newEmptyNode;
        	}
		pList->current = newEmptyNode;
		pList->count++;
		return LIST_SUCCESS;
	}
	return LIST_FAIL;
}

int List_append(List* pList, void* pItem) {
	assert(pList != NULL);
	if (newNode) {
        	Node *newEmptyNode = findNewNode();
        	newEmptyNode->item = pItem;
        	if (pList->count == 0) {
            		pList->head = newEmptyNode;
           		pList->tail = newEmptyNode;
       	 	} else {
            		newEmptyNode->next = NULL;
            		newEmptyNode->previous = pList->tail;
	    		pList->tail->next = newEmptyNode;
			pList->tail = newEmptyNode;
		}
		pList->current = newEmptyNode;
		pList->count++;
		return LIST_SUCCESS;
	}
	return LIST_FAIL;
}

int List_prepend(List* pList, void* pItem) {
	assert(pList != NULL);
	if (newNode) {
        	Node *newEmptyNode = findNewNode();
        	newEmptyNode->item = pItem;
        	if (pList->count == 0) {
            		pList->head = newEmptyNode;
           		pList->tail = newEmptyNode;
       	 	} else {
            		newEmptyNode->next = pList->head;
            		newEmptyNode->previous = NULL;
	    		pList->head->previous = newEmptyNode;
			pList->head = newEmptyNode;
		}
		pList->current = newEmptyNode;
		pList->count++;
		return LIST_SUCCESS;
	}
	return LIST_FAIL;
}

void* List_remove(List* pList) {
	assert(pList != NULL);
	if (pList->count > 0 && pList->current)  {
        	Node* itemToRemove = pList->current;
        	if (pList->count == 1) {
            		freeNode(pList->current);
            		freeList(pList);
        	} else if (pList->current == pList->head) {
            		pList->head = pList->head->next;
            		pList->head->previous = NULL;
            		pList->current = pList->head;
            		pList->count--;
       	 	} else if (pList->current == pList->tail) {
            		List_trim(pList);
        	} else {
            		pList->current = pList->current->next;
           		itemToRemove->previous->next = pList->current;
            		pList->current->previous = itemToRemove->previous;
            		pList->count--;
        	}
        	freeNode(itemToRemove);
        	return itemToRemove->item;
	} else {
		return NULL;
	}
}

void* List_trim(List* pList) {
	assert(pList != NULL);
	if (pList->count > 0 && pList->current)  {
         	Node* itemToRemove = pList->tail;
         	pList->tail = pList->tail->previous;
         	pList->tail->next = NULL;
        	pList->current = pList->tail;
         	pList->count--;
         	freeNode(itemToRemove);
         	return itemToRemove->item;
     	} 
       	return NULL;
}

void List_concat(List* pList1, List* pList2) {
	assert(pList1 != NULL);
	assert(pList2 != NULL);
	if (pList2->count > 0) {
		if (pList1->count > 0) {
			pList1->tail->next = pList2->head;
			pList2->head->previous = pList1->tail;
		
		} else {
			pList1->head = pList2->head;
			
		}
		pList1->tail = pList2->tail;
		pList1->count += pList2->count;
		freeList(pList2);
	}
}

void List_free(List* pList, FREE_FN pItemFreeFn) {
	assert(pList != NULL);
	if (pList->count > 0) {
		pList->current = pList->head;
		Node* currentNodeToFree = pList->current;
		while (pList->count != 0) {
			pList->current = pList->current->next;
			(*pItemFreeFn)(currentNodeToFree->item);
			freeNode(currentNodeToFree);
			currentNodeToFree = pList->current;
			pList->count--;
		}
	}
	freeList(pList);
}

void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg) {
	assert(pList != NULL);
	if (pList->count != 0 && pComparisonArg) {
		if ((*pComparator)(pList->current->item, pComparisonArg)) {
			return pList->current->item;
		}
		while (pList->current != pList->tail) {
			pList->current = pList->current->next;
			if ((*pComparator)(pList->current->item, pComparisonArg)) {
				return pList->current->item;
			}
		}
		pList->current = pList->current->next;
		return NULL;
	}
	return NULL;
}

