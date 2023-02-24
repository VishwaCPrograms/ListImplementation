/* Author:  Vishwa Venkateshwaran
 *
 * Notes:
 * Size of nodes array at time of testing: 10
 * Size of lists array at time of testing: 3
 *
 * */

#include "list.h"


void freeItem(void* pItem) {
	return;
}

bool compare(void* pItem, void* pComparisonArg) {
	return (pItem == pComparisonArg) ? 1 : 0;
}


int main(int argc, char *argv[]) {

	List* L1 = List_create();
	List* L2 = List_create();
	List* L3 = List_create();
	
	int num1 = 10;
	int num2 = 20;
	int num3 = 30;
	int num4 = 40;
	int num5 = 50;
	int num6 = 60;
	int num7 = 70;
	int num8 = 80;
	int num9 = 90;
	int num10 = 100;

	printf("Size of nodes array at time of testing: 10\n");
	printf("Size of lists array at time of testing: 3\n");

	printf("------------------------------------------------------\n");
	
	List* L4 = List_create();
	if (L4) {
		printf("A new 4th list has been created.\n");
	} else {
		printf("Sorry, we're out of space! We cannot create a 4th list.\n");
	}

	printf("------------------------------------------------------\n");
	
	printf("L1: \n");
	if(List_append(L1, &num1) == 0) {
		printf("Element at the top: %d\n", *(int*)List_first(L1));
		printf("Element at the bottom: %d\n", *(int*)List_last(L1));
	}

	List_insert_after(L1, &num2);

	List_prepend(L1, &num3);

	List_first(L1);
	
	List_next(L1);

	printf("After moving to the first element and then 1 element over, current element in the list: %d\n", *(int*)List_curr(L1));

	int numThatShouldBe0 = List_insert_after(L1, &num4);
	if(numThatShouldBe0 == 0) {
		printf("4th element in the list has been added.\n");
	} else {
		printf("Sorry, we're all out of space!\n");
	}

	List_first(L1);

	List_prev(L1);

	List_insert_before(L1, &num5);
	
	printf("First element in L1: %d\n", *(int*)List_first(L1));
	void* ptr1 = List_next(L1);
	while(ptr1) {
		printf("Next element: %d\n", *(int*)ptr1);
		ptr1 = List_next(L1);
	}
	
	printf("List 1 size: %d\n", List_count(L1));
	
	printf("------------------------------------------------------\n");

	printf("L2: \n");

	if(List_prepend(L2, &num6) == 0) {
		printf("Element at the top: %d\n", *(int*)List_first(L2));
		printf("Element at the bottom: %d\n", *(int*)List_last(L2));
	}

	List_insert_before(L2, &num7);
	
	List_next(L2);
	List_next(L2);
	List_insert_after(L2, &num8);

	printf("First element in L2: %d\n", *(int*)List_first(L2));
	void* ptr2 = List_next(L2);
	while(ptr2) {
		printf("Next element: %d\n", *(int*)ptr2);
		ptr2 = List_next(L2);
	}

	printf("List 2 size: %d\n", List_count(L2));
	
	printf("------------------------------------------------------\n");

	printf("L3: \n");

	if(!List_first(L3)) {
		printf("Sorry, list is empty\n");
	}
	
	if(!List_last(L3)) {
		printf("Sorry, list is empty\n");
	}
	
	if(!List_prev(L3)) {
		printf("Sorry, list is empty\n");
	}
	
	if(!List_next(L3)) {
		printf("Sorry, list is empty\n");
	}
	
	
	if(List_insert_before(L3, &num9) == 0) {
		printf("Element at the top: %d\n", *(int*)List_first(L3));
		printf("Element at the bottom: %d\n", *(int*)List_last(L3));
	}

	
	if(List_insert_before(L3, &num10) == 0) {
		printf("Element at the top: %d\n", *(int*)List_first(L3));
		printf("Element at the bottom: %d\n", *(int*)List_last(L3));
	}

	int dontMessUp = 13;
	if(List_insert_before(L3, &dontMessUp) == 0) {
		printf("Element at the top: %d\n", *(int*)List_first(L3));
		printf("Element at the bottom: %d\n", *(int*)List_last(L3));
	} else {
		printf("Sorry, no more nodes left!\n");
	}

	printf("First element in L3: %d\n", *(int*)List_first(L3));
	void* ptr3 = List_next(L3);
	while(ptr3) {
		printf("Next element: %d\n", *(int*)ptr3);
		ptr3 = List_next(L3);
	}
	
	printf("List 3 size: %d\n", List_count(L3));

	printf("------------------------------------------------------\n");

	printf("L1 + L3: \n");

	List_concat(L1, L3);

	printf("First element in L1+L3: %d\n", *(int*)List_first(L1));
	void* ptr4 = List_next(L1);
	while(ptr4) {
		printf("Next element: %d\n", *(int*)ptr4);
		ptr4 = List_next(L1);
	}
	
	printf("List 1+3 size: %d\n", List_count(L1));

	printf("L1 + L3 + L2: \n");
	
	List_concat(L1, L2);

	printf("First element in L0: %d\n", *(int*)List_first(L1));
	void* ptr5 = List_next(L1);
	while(ptr5) {
		printf("Next element: %d\n", *(int*)ptr5);
		ptr5 = List_next(L1);
	}
	printf("List 0 size: %d\n", List_count(L1));
	
	printf("------------------------------------------------------\n");
	
	printf("Removing nodes and reusage: \n");	

	List_first(L1);

	List_next(L1);
	List_next(L1);
	List_next(L1);
	List_next(L1);
	List_next(L1);
	
	printf("Current element in L0: %d\n", *(int*)List_curr(L1));

	List_remove(L1);	

	printf("After calling remove on current element.\n");
	printf("New current element: %d\n", *(int*)List_curr(L1));
	printf("First element in L0: %d\n", *(int*)List_first(L1));
	void* ptr = List_next(L1);
	while(ptr) {
		printf("Next element: %d\n", *(int*)ptr);
		ptr = List_next(L1);
	}
	printf("List 0 size: %d\n", List_count(L1));

	int numToAdd = 1000;

	List_prepend(L1, &numToAdd);

	printf("First element in L0: %d\n", *(int*)List_first(L1));
	printf("List 0 size after adding 1000: %d\n", List_count(L1));

	List_trim(L1);
	
	printf("New last element after calling trim: %d\n", *(int*)List_last(L1));
	printf("List 0 size after trim: %d\n", List_count(L1));

	printf("------------------------------------------------------\n");

	printf("List search and freeing it: \n");
	
	void* answerPtr = (List_search(L1, compare, &num7));
	if(answerPtr) {
		printf("List search result: %d\n", *(int*)answerPtr);
	}

	List_free(L1, freeItem);

	printf("%d\n", List_count(L1));

	return 0;
}
