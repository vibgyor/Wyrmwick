#include "include.h"

array* array_new(size_t elemSize, int startingSize, int startingCapacity) {
	if (startingSize > startingCapacity) {
		debug_print("Array size > cap.\r\n");
		sys_abort();
	}
	
	array* arr = (array*) malloc(sizeof(array));
	arr->m_elemSize = elemSize;
	arr->m_len = startingSize;
	arr->m_cap = startingCapacity;
	arr->m_data = calloc(startingCapacity, elemSize);
	return arr;
}

void array_append(array *arr, const void *val) {
	if (arr->m_len == arr->m_cap) {
		int newcap;
		if (arr->m_cap == 0) {
			newcap = 8;
		} else {
			newcap = arr->m_cap * 2;
		}
		
		arr->m_data = realloc(arr->m_data, arr->m_elemSize * newcap);
		if (! arr->m_data) {
			debug_print("Not enough memory to append.\r\n");
			sys_abort();
		}
		memset(((unsigned char*)arr->m_data) + arr->m_cap*arr->m_elemSize, 0, newcap - arr->m_cap);
		arr->m_cap = newcap;
	}
	
	memmove(((unsigned char*)arr->m_data) + arr->m_len*arr->m_elemSize, val, arr->m_elemSize);
	arr->m_len++;
}

void array_get(array *arr, int index, void *val) {
	if (index >= arr->m_len) {
		debug_print("Array index out of bounds.\r\n");
		sys_abort();
	}
	memmove(val, ((unsigned char*) arr->m_data) + index * arr->m_elemSize, arr->m_elemSize);
}

void array_put(array *arr, int index, const void *val) {
	if (index >= arr->m_len) {
		debug_print("Array index out of bounds.\r\n");
		sys_abort();
	}
	memmove(((unsigned char*) arr->m_data) + index * arr->m_elemSize, val, arr->m_elemSize);
}

void* array_ind(array *arr, int index) {
	if (index >= arr->m_len) {
		debug_print("Array index out of bounds.\r\n");
		sys_abort();
	}
	return ((unsigned char*) arr->m_data) + index * arr->m_elemSize;
}

void array_free(array *arr) {
	free(arr->m_data);
	free(arr);
}
