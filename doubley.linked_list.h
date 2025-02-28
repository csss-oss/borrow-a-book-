#pragma once
#ifndef __doubly_linked_list_h__
#define __dounly_linked_list_h__

//#define USE_NUMBER
//#define USE_STRING //정수로 사용할 경우 주석처리
#define USE_STRUCT

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef USE_NUMBER
typedef int element;
#endif

#ifdef USE_STRING
typedef char element[80];
#endif

#ifdef USE_STRUCT
typedef struct  {
	char	bookname[80];	//책이름
	int		id;				//책 관리 번호
	int		is_borrowed;	//대여상태(0:보유,1:대여)
} element;
#endif

typedef struct DListNode {
	element data;
	struct DListNode* llink; //선행 노드 링크
	struct DListNode* rlink;  //후행노드 링크
}DListNode;

void init(DListNode* phead);
void print_dlist(DListNode* phead);
void dinsert(DListNode* before, element data);
void ddelete(DListNode* head, DListNode* removed);
DListNode* dsearch_id(DListNode* head, int id);
DListNode* dsearch_name(DListNode* head, char* name);
void borrow_book(DListNode* head, int id);
void return_book(DListNode* head, int id);
void display_books(DListNode* head);

#endif