//EHArray.c
#include "EHArray.h"
#include <stdlib.h>

void EHArrayEHArray(EHArray *arr,int init_capa,Element init_value);
void EHArrayReserve(EHArray *arr,int capacity);
void EHArrayPushBacks(EHArray *arr,int n,Element value);
void EHArrayTEHArray(EHArray *arr);

EHArray *NewEHArray(int init_capa,Element init_value)
{
    EHArray *arr = (EHArray *)malloc(sizeof(EHArray));
    EHArrayEHArray(arr,init_capa,init_value);
    return arr;
}  

void EHArrayEHArray(EHArray *arr,int init_capa,Element init_value)
{
    arr->base = 0;
    arr->capacity = 0;
    arr->size = 0;
    if(init_capa>0)
    {
        EHArrayReserve(arr,init_capa);
        EHArrayPushBacks(arr,init_capa,init_value);
    }
}
void EHArrayReserve(EHArray *arr,int capacity)
{
    arr->base = (Element *)realloc(arr->base,sizeof(Element)*capacity);
    arr->capacity = capacity;
}
void EHArrayPushBacks(EHArray *arr,int n,Element value)
{
    int i = 0;
    for(i=0;i<n;i++)
    {
        EHArrayPushBack(arr,value);
    }
}
void DeleteEHArray(EHArray *arr)
{
    EHArrayTEHArray(arr);
    free(arr);
}  

void EHArrayTEHArray(EHArray *arr)
{
    if(arr->base)
    {
        free(arr->base);
    }
}
int EHArrayGetCapacity(EHArray *arr)
{
    return arr->capacity;
}
int EHArrayGetSize(EHArray *arr)
{
    return arr->size;
}


void EHArrayPushBack(EHArray *arr,Element data)
{
    if(arr->capacity == arr->size)
    {
        if(arr->capacity)
        {
            EHArrayReserve(arr,arr->capacity*2);
        }
        else
        {
            EHArrayReserve(arr,1);
        }
    }
    arr->base[arr->size] = data;
    arr->size++;
}
Element EHArrayGetAt(EHArray *arr,int index)
{
    if((index>=0)&&(index<arr->size))
    {
        return arr->base[index];
    }
    return 0;
}
void EHArraySetAt(EHArray *arr,int index, Element data)
{
    if((index>=0)&&(index<arr->size))
    {
        arr->base[index] = data;
    }
}
Iterator EHArrayBegin(EHArray *arr)
{
    return arr->base;   
}
Iterator EHArrayEnd(EHArray *arr)
{
    return arr->base + arr->size;
}
void EHArrayErase(EHArray *arr,Iterator it)
{
    Iterator end;
    arr->size--;
    end = arr->base + arr->size;
    for(  ; it != end; it++)
    {
        (*it) = *(it+1);
    }
}
