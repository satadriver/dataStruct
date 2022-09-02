#pragma once

#include <iostream>



#pragma pack(1)
typedef struct  _DLLIST
{
	_DLLIST* prev;
	_DLLIST* next;
}DLLIST,*LPDLLIST;
#pragma pack()





int insertListElem();

int deleteListElem();