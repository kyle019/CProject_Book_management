// EHArray.h
#pragma once
typedef struct _EHArray EHArray;
typedef void *Element; //요소 형식명을 Element로 정의
typedef Element * Iterator;
struct _EHArray
{
    Element *base; //저장소의 위치 정보
    int capacity;     //현재 저장소의 크기
    int size;           //현재 보관한 요소 개수
};

EHArray *NewEHArray(int init_capa,Element init_value); //동적으로 배열 생성
void DeleteEHArray(EHArray *arr); //배열 소멸
int EHArrayGetCapacity(EHArray *arr); //저장소의 크기 가져오기
int EHArrayGetSize(EHArray *arr);       //보관한 요소 개수 가져오기
void EHArrayPushBack(EHArray *arr,Element data); //순차적으로 자료 보관
Element EHArrayGetAt(EHArray *arr,int index); //보관한 요소 가져오기
void EHArraySetAt(EHArray *arr,int index, Element data); //보관한 요소 설정하기
Iterator EHArrayBegin(EHArray *arr); //저장소의 시작 위치
Iterator EHArrayEnd(EHArray *arr); //저장소의 마지막 위치(보관할 위치)
void EHArrayErase(EHArray *arr,Iterator it);//보관한 요소 제거하기
