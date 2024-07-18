#include "Member.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void MemberMember(Member *member,int mnum,const char *name);
Member *NewMember(int mnum,const char *name)
{
    Member *member = 0;
    member = (Member *)malloc(sizeof(Member));
    MemberMember(member,mnum,name);
    return member;
}
void MemberMember(Member *member,int mnum,const char *name)
{
    member->mnum = mnum;
    memset(member->name,0,sizeof(member->name));
    strncpy(member->name,name,MAX_NAME_LEN);
}
void DeleteMember(Member *member)
{
    free(member);
}
void MemberView(Member *member)
{
    printf("번호:%d 이름:%s\n",member->mnum,member->name);
}
