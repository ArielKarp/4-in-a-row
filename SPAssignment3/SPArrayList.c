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
	if (NULL == returnList) {
		return NULL;
	}
	returnList->maxSize = maxSize;
	returnList->actualSize = 0;
	returnList->elements = (int*) calloc(maxSize, sizeof(int));
	if (NULL == returnList->elements) {
		return NULL;
	}
	return returnList;
}

SPArrayList* spArrayListCopy(SPArrayList* src) {
	if (NULL == src) {
		return NULL;
	}
	SPArrayList* returnList = spArrayListCreate(src->maxSize);
	if (NULL == returnList) {
		return NULL;
	}
	returnList->actualSize = src->actualSize;
	copyIntArray(src->elements, returnList->elements, src->maxSize);
	return returnList;
}

void copyIntArray(int* src, int* dst, int size) {
	int index = 0;
	for (; index < size; index++) {
		dst[index] = src[index];
	}
	return;
}

bool copyIntArrayFromArrayList(SPArrayList* src, SPArrayList* dst) {
	int index = 0;
	bool rc = true;
	if (NULL == src || NULL == dst || src->maxSize != dst->maxSize) {
		rc = false;
		return rc;
	}
	for (; index < src->maxSize; index++) {
		dst->elements[index] = src->elements[index];
	}
	return rc;
}

void spArrayListDestroy(SPArrayList* src) {
	if (NULL == src) {
		return;
	}
	if (NULL != src->elements) {
		free(src->elements);
	}
	src->elements = NULL;
	free(src);
	src = NULL;
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src) {
	SP_ARRAY_LIST_MESSAGE rc = SP_ARRAY_LIST_SUCCESS;
	if (NULL == src) {
		rc = SP_ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	clearIntArr(src->elements, src->maxSize);
	src->actualSize = 0;
	return rc;
}

void clearIntArr(int* src, int size) {
	int index = 0;
	for (; index < size; index++) {
		src[index] = 0;
	}
	return;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, int elem, int index) {
	SP_ARRAY_LIST_MESSAGE rc = SP_ARRAY_LIST_SUCCESS;
	if (NULL == src || index < 0 || index > src->actualSize) {
		rc = SP_ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	if (src->actualSize == src->maxSize) {
		rc = SP_ARRAY_LIST_FULL;
		return rc;
	}
	if (index == src->actualSize) {
		src->elements[index] = elem;
		src->actualSize++;
		return rc;
	}
//	memmove((src->elements + index + 1), (src->elements + index),
//			(src->actualSize - index) * sizeof(int));
	int i = src->actualSize;
	for(; i > index; i--){
		src->elements[i] = src->elements[i-1];
	}
	src->elements[index] = elem;
	src->actualSize++;
	return rc;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem) {
	return spArrayListAddAt(src, elem, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int elem) {
	if (NULL == src) {
		SP_ARRAY_LIST_MESSAGE rc = SP_ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	return spArrayListAddAt(src, elem, src->actualSize);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index) {
	SP_ARRAY_LIST_MESSAGE rc = SP_ARRAY_LIST_SUCCESS;
	if (NULL == src || index < 0 || index >= src->actualSize) {
		rc = SP_ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	if (src->actualSize == 0) {
		rc = SP_ARRAY_LIST_EMPTY;
		return rc;
	}
	if (index == src->actualSize) {
		src->elements[index] = 0;
		src->actualSize--;
		return rc;
	}
//	memmove((src->elements + index), (src->elements + index + 1),
//			(src->actualSize - index) * sizeof(int));
	int i = index;
	for (; i < (src->actualSize - 1); i++) {
		src->elements[i] = src->elements[i+1];
	}
	src->elements[src->actualSize - 1] = 0;
	src->actualSize--;
	return rc;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src) {
	return spArrayListRemoveAt(src, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src) {
	if (NULL == src) {
		SP_ARRAY_LIST_MESSAGE rc = SP_ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	return spArrayListRemoveAt(src, src->actualSize - 1);
}

int spArrayListGetAt(SPArrayList* src, int index) {
	if (NULL == src || index < 0 || index >= src->actualSize) {
		return -1;
	}
	return src->elements[index];
}

int spArrayListGetFirst(SPArrayList* src) {
	return spArrayListGetAt(src, 0);
}

int spArrayListGetLast(SPArrayList* src) {
	if (NULL == src) {
		return -1;
	}
	return spArrayListGetAt(src, src->actualSize - 1);
}

int spArrayListMaxCapacity(SPArrayList* src) {
	if (NULL == src) {
		return -1;
	}
	return src->maxSize;
}

int spArrayListSize(SPArrayList* src) {
	if (NULL == src) {
		return -1;
	}
	return src->actualSize;
}

bool spArrayListIsFull(SPArrayList* src) {
	if (NULL == src || src->actualSize < src->maxSize) {
		return false;
	}
	return true;
}

bool spArrayListIsEmpty(SPArrayList* src) {
	if (NULL == src || src->actualSize > 0) {
		return false;
	}
	return true;
}

