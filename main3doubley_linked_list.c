#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "doubley.linked_list.h"

//이중 연결리스트 초기화
void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

//이중 연결 리스트의 노드를 인쇄
void print_dlist(DListNode* phead) {
	DListNode* p;
	// p가 최초 위치인 phead에 도달할 때까지 반복
	for (p = phead->rlink; p != phead; p = p->rlink) {
#ifdef USE_STRING
		printf("<-| |%s| |->", p->data);
#endif
#ifdef USE_NUMBER
		printf("<-| |%d| |->", p->data);
#endif
	}
	printf("\n");
}

//새로운 데이터를 노드 before의 오른쪽에 삽입
void dinsert(DListNode* before, element data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
#ifdef USE_STRING
	strcpy(newnode->data, data);	
#endif
#if defined(USE_NUMBER) || defined(USE_STRUCT)
	newnode->data = data;	//새로운 노드에 값 저장
#endif
	newnode->llink = before;		//새로운 노드의 선행 링크를 before의 주소로 할당
	newnode->rlink = before->rlink; //새로운 노드의 후행 링크를 before가 가진 후행링크에서 복사
	before->rlink->llink = newnode; //before의 후행링크에서 보유한선행링크의 주소를 새로운 노드의 주소로 할당
	before->rlink = newnode;		//before의 후행 링크를 새로운 노드의 주소로 할당
}

//removed로 입력된 노드를 삭제
void ddelete(DListNode* head, DListNode* removed) {
	if (removed == head) return; //헤드는 삭제 불가
	//삭제될 노드가 가진 선행 링크의 후행 링크값을 삭제될 노드의 후행 링크값에서 복사
	removed->llink->rlink = removed->rlink;
	//삭제될 노드가 가진 후행 링크의 선행 링크값을 삭제될 노드의 선행 링크값에서 복사
	removed->rlink->llink = removed->llink;
	free(removed);
}

//검색함수(id로 검색)
DListNode*dsearch_id(DListNode* head, int id) {

	DListNode* p = head->rlink; //시작위치
	while (p != head) {
		if (p->data.id == id) {
			return p;
		}
		p = p->rlink;// 다음 노드로 이동
	}
	return NULL;
}
//검색함수(이름으로 검색)
DListNode* dsearch_name(DListNode* head, char*name) {

	DListNode* p = head->rlink; //시작위치
	while (p != head) {
		if (strcmp(p->data.bookname,name) == 0) {
			return p;
		}
		p = p->rlink;// 다음 노드로 이동
	}
	return NULL;

}

//도서 대출함수

void borrow_book(DListNode*head, int id) {
	DListNode* node = dsearch_id(head,id);
	if (node == NULL) printf("책 ID %d를 찾을 수 없습니다.\n", id);
	else if (node->data.is_borrowed)
		printf("책 '%s'(ID:%d)은 이미 대출 중입니다.\n", node->data.bookname, node->data.id);
	else {
		node->data.is_borrowed = 1;
		printf("책 '%s' (ID:%d)을 대출했습니다.\n", node->data.bookname, node->data.id);
	}
}
//도서 반납함수
void return_book(DListNode* head,int id) {
	DListNode* node = dsearch_id(head,id);
	if (node == NULL) 
		printf("책 ID %d를 찾을 수 없습니다.\n", id);
	else if (node->data.is_borrowed)
		printf("책 '%s'(ID:%d)은 이미 대출 중입니다.\n", node->data.bookname, node->data.id);
	else {
		node->data.is_borrowed = 0;
		printf("책 '%s' (ID:%d)을 반납했습니다.\n", node->data.bookname, node->data.id);
	}
}

//도서 목록 출력함수
void display_books(DListNode* head) {
	if (!head) {
		printf("등록된 책이 없습니다.\n");
		return;
	}
	DListNode* p = head->rlink; //이중 연결 리스트 시작 위치
	printf("\n도서 목록\n");
	while (p != head) {				//이중연결 리스트 끝까지 반복
		printf("ID: %d, 제목: %s, 상태: %s\n", p->data.id, p->data.bookname,
			p->data.is_borrowed ? "대출" : "보유");
		p = p->rlink;			//다음 노드로 이동
	}
}



//이중 연결 리스트 테스트
//int main(void) {
//	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
//	init(head);
//	printf("노드 추가\n");
//	for (int i = 0; i < 5; i++) {
//		dinsert(head, i);
//		print_dlist(head);
//	}
//	printf("노드 삭제\n");
//	for (int i = 0; i < 5; i++){
//		print_dlist(head);
//		ddelete(head, head->rlink);
//}
//	free(head);
//	return 0;
//}