/*
 * SPArrayList.c
 *
 *      Author: Ariel
 */

#include "SPArrayList.h"

SPArrayList* spArrayListCreate(int maxSize) {
	if (maxSize <= 0) {
		return NULL;
	}
	SPArrayList* returnList = (SPArrayList*) malloc(sizeof(SPArrayList));
	if (returnList == NULL) {
		return NULL;
	}
	returnList->maxSize = maxSize;
	returnList->actualSize = 0;
	returnList->elements = (int*) calloc(maxSize, sizeof(int));
	if (returnList->elements == NULL) {
		return NULL;
	}
	return returnList;
}

SPArrayList* spArrayListCopy(SPArrayList* src) {
	if (src == NULL) {
		return NULL;
	}
	SPArrayList* returnList = spArrayListCreate(src->maxSize);
	if (returnList == NULL) {
		return NULL;
	}
	returnList->actualSize = src->actualSize;
	coptyIntArray(src->elements, returnList->elements, src->maxSize);
	return returnList;
}

void coptyIntArray(int* src, int* dst, int size) {
	int index = 0;
	for (; index < size; index++) {
		dst[index] = src[index];
	}
	return;
}

void spArrayListDestroy(SPArrayList* src) {
	if (src == NULL) {
		return;
	}
	if (src->elements != NULL) {
		free(src->elements);
	}
	free(src);
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src){
	SP_ARRAY_LIST_MESSAGE rc = SP_ARRAY_LIST_SUCCESS;
	if (src == NULL) {
		rc = SP_ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	clearIntArr(src->elements, src->maxSize);
	src->actualSize = 0;
	return rc;
}

void clearIntArr(int* src, int size){
	int index = 0;
	for(; index < size; index++) {
		src[index] = 0;
	}
	return;
}
