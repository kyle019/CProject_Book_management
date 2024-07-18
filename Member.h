#pragma once
typedef struct _Member Member;
#define MAX_NAME_LEN 20
struct _Member
{
    int mnum;
    char name[MAX_NAME_LEN+1];
};


Member *NewMember(int mnum,const char *name);   //배열생성 함수
void DeleteMember(Member *member);              //맴버삭제 함수
int MemberGetNum(Member *member);               //맴버숫자 출력함수
const char *MemberGetName(Member *member);      //맴버이름 출력함수
void MemberView(Member *member);                //모든뱀버 출력함수
