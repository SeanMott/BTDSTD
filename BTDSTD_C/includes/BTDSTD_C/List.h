#pragma once

//C API of a dynamic list

#include <BTDSTD_C/Types.h>

#include <stdlib.h>

//defines a dynamic list
typedef struct BTD_List
{
	size_t elementMemSize; //the size of a single element in the array

	size_t objCount; //the number of elements in the list
	size_t totalListSize; //the real length of the list

	//the data
	void** data;
} BTD_List;

//initalize the list and optionally reserve space
inline void BTD_List_Initalize(BTD_List* list, const size_t elementMemSize, const size_t reserveSize)
{
	list->elementMemSize = elementMemSize;
	list->totalListSize = reserveSize;

	//reserve size
	if(list->totalListSize > 0)
		list->data = (void**)realloc(list->data, list->elementMemSize * list->totalListSize);
}

//clears the list
inline void BTD_List_Clear(BTD_List* list, void(*objDestroyFunc)(void*))
{
	//calls a function to properly clean up the object in the list
	if (objDestroyFunc)
	{
		for (uint32 i = 0; i < list->totalListSize; ++i)
		{
			objDestroyFunc(list->data[i]);
			list->data[i] = NULL;
		}
	}
	free(list->data); list->elementMemSize = 0; list->objCount = 0; list->totalListSize = 0;
}

//adds a object in the list
inline void BTD_List_AddObject(BTD_List* list, void* obj)
{
	//if there is still space
	uint32 listIndex = 0;
	if (list->objCount < list->totalListSize)
	{
		listIndex = list->objCount;
	}

	//if there isn't, we reallocate
	else
	{
		list->totalListSize++;
		list->data = (void**)realloc(list->data, list->elementMemSize * list->totalListSize);
		listIndex = list->objCount;
	}

	//adds the object
	list->data[listIndex] = obj;
	list->objCount++;
}

//removes a object from the list

//copies one to list another