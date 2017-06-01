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
	src->elements = NULL;
	free(src);
	src = NULL;
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src) {
	SP_ARRAY_LIST_MESSAGE rc = SP_ARRAY_LIST_SUCCESS;
	if (src == NULL) {
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
	if (src == NULL || index < 0 || index > src->actualSize) {
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
	memmove((src->elements + index + 1), (src->elements + index),
			(src->actualSize - index) * sizeof(int));
	src->elements[index] = elem;
	src->actualSize++;
	return rc;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem) {
	return spArrayListAddAt(src, elem, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int elem) {
	if (src == NULL) {
		SP_ARRAY_LIST_MESSAGE rc = SP_ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	return spArrayListAddAt(src, elem, src->actualSize);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index) {
	SP_ARRAY_LIST_MESSAGE rc = SP_ARRAY_LIST_SUCCESS;
	if (src == NULL || index < 0 || index >= src->actualSize) {
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
	memmove((src->elements + index), (src->elements + index + 1),
			(src->actualSize - index) * sizeof(int));
	src->actualSize--;
	return rc;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src) {
	return spArrayListRemoveAt(src, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src) {
	if (src == NULL) {
		SP_ARRAY_LIST_MESSAGE rc = SP_ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	return spArrayListRemoveAt(src, src->actualSize - 1);
}

int spArrayListGetAt(SPArrayList* src, int index) {
	if (src == NULL || index < 0 || index >= src->actualSize) {
		return -1;
	}
	return src->elements[index];
}

int spArrayListGetFirst(SPArrayList* src) {
	return spArrayListGetAt(src, 0);
}

int spArrayListGetLast(SPArrayList* src) {
	if (src == NULL) {
		return -1;
	}
	return spArrayListGetAt(src, src->actualSize);
}

int spArrayListMaxCapacity(SPArrayList* src) {
	if (src == NULL) {
		return -1;
	}
	return src->maxSize;
}

int spArrayListSize(SPArrayList* src) {
	if (src == NULL) {
		return -1;
	}
	return src->actualSize;
}

bool spArrayListIsFull(SPArrayList* src) {
	if (src == NULL || src->actualSize < src->maxSize) {
		return false;
	}
	return true;
}

bool spArrayListIsEmpty(SPArrayList* src) {
	if (src == NULL || src->actualSize > 0) {
		return false;
	}
	return true;
}

