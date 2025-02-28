#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "doubley.linked_list.h"

//���� ���Ḯ��Ʈ �ʱ�ȭ
void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

//���� ���� ����Ʈ�� ��带 �μ�
void print_dlist(DListNode* phead) {
	DListNode* p;
	// p�� ���� ��ġ�� phead�� ������ ������ �ݺ�
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

//���ο� �����͸� ��� before�� �����ʿ� ����
void dinsert(DListNode* before, element data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
#ifdef USE_STRING
	strcpy(newnode->data, data);	
#endif
#if defined(USE_NUMBER) || defined(USE_STRUCT)
	newnode->data = data;	//���ο� ��忡 �� ����
#endif
	newnode->llink = before;		//���ο� ����� ���� ��ũ�� before�� �ּҷ� �Ҵ�
	newnode->rlink = before->rlink; //���ο� ����� ���� ��ũ�� before�� ���� ���ีũ���� ����
	before->rlink->llink = newnode; //before�� ���ีũ���� �����Ѽ��ีũ�� �ּҸ� ���ο� ����� �ּҷ� �Ҵ�
	before->rlink = newnode;		//before�� ���� ��ũ�� ���ο� ����� �ּҷ� �Ҵ�
}

//removed�� �Էµ� ��带 ����
void ddelete(DListNode* head, DListNode* removed) {
	if (removed == head) return; //���� ���� �Ұ�
	//������ ��尡 ���� ���� ��ũ�� ���� ��ũ���� ������ ����� ���� ��ũ������ ����
	removed->llink->rlink = removed->rlink;
	//������ ��尡 ���� ���� ��ũ�� ���� ��ũ���� ������ ����� ���� ��ũ������ ����
	removed->rlink->llink = removed->llink;
	free(removed);
}

//�˻��Լ�(id�� �˻�)
DListNode*dsearch_id(DListNode* head, int id) {

	DListNode* p = head->rlink; //������ġ
	while (p != head) {
		if (p->data.id == id) {
			return p;
		}
		p = p->rlink;// ���� ���� �̵�
	}
	return NULL;
}
//�˻��Լ�(�̸����� �˻�)
DListNode* dsearch_name(DListNode* head, char*name) {

	DListNode* p = head->rlink; //������ġ
	while (p != head) {
		if (strcmp(p->data.bookname,name) == 0) {
			return p;
		}
		p = p->rlink;// ���� ���� �̵�
	}
	return NULL;

}

//���� �����Լ�

void borrow_book(DListNode*head, int id) {
	DListNode* node = dsearch_id(head,id);
	if (node == NULL) printf("å ID %d�� ã�� �� �����ϴ�.\n", id);
	else if (node->data.is_borrowed)
		printf("å '%s'(ID:%d)�� �̹� ���� ���Դϴ�.\n", node->data.bookname, node->data.id);
	else {
		node->data.is_borrowed = 1;
		printf("å '%s' (ID:%d)�� �����߽��ϴ�.\n", node->data.bookname, node->data.id);
	}
}
//���� �ݳ��Լ�
void return_book(DListNode* head,int id) {
	DListNode* node = dsearch_id(head,id);
	if (node == NULL) 
		printf("å ID %d�� ã�� �� �����ϴ�.\n", id);
	else if (node->data.is_borrowed)
		printf("å '%s'(ID:%d)�� �̹� ���� ���Դϴ�.\n", node->data.bookname, node->data.id);
	else {
		node->data.is_borrowed = 0;
		printf("å '%s' (ID:%d)�� �ݳ��߽��ϴ�.\n", node->data.bookname, node->data.id);
	}
}

//���� ��� ����Լ�
void display_books(DListNode* head) {
	if (!head) {
		printf("��ϵ� å�� �����ϴ�.\n");
		return;
	}
	DListNode* p = head->rlink; //���� ���� ����Ʈ ���� ��ġ
	printf("\n���� ���\n");
	while (p != head) {				//���߿��� ����Ʈ ������ �ݺ�
		printf("ID: %d, ����: %s, ����: %s\n", p->data.id, p->data.bookname,
			p->data.is_borrowed ? "����" : "����");
		p = p->rlink;			//���� ���� �̵�
	}
}



//���� ���� ����Ʈ �׽�Ʈ
//int main(void) {
//	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
//	init(head);
//	printf("��� �߰�\n");
//	for (int i = 0; i < 5; i++) {
//		dinsert(head, i);
//		print_dlist(head);
//	}
//	printf("��� ����\n");
//	for (int i = 0; i < 5; i++){
//		print_dlist(head);
//		ddelete(head, head->rlink);
//}
//	free(head);
//	return 0;
//}