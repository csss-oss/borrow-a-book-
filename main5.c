//��������ݳ��ý���

#define _CRT_SECURE_NO_WARNINGS

#define USE_STRUCT


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "doubley.linked_list.h"

typedef DListNode Book;
//������ �Է� �Լ� (���� �Է� ����)
int safe_input() {
	int num;
	while (1) {
		if (scanf("%d", &num) == 1) {
			getchar(); //���๮�� ����
			return num;
		}
		else {
			printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���: ");
			while (getchar() != '\n');
		}
	}

}


int main(void) {
	//���� ���� ����Ʈ ��� ����
	Book* head = (Book*)malloc(sizeof(Book));
	init(head); //��� �ʱ�ȭ
	int choice, id;
	char bookname[80];


	while (1) {
		printf("\n���� ���� �ý���\n");
		printf("1. �����߰�\n");
		printf("2. ��������\n");
		printf("3. �����ݳ�\n");
		printf("4. ������Ϻ���\n");
		printf("5. ����\n");
		printf("�޴��� �����ϼ��� :");

		choice = safe_input();

		switch (choice) {
		case 1://�����߰�
			printf("å ID �Է�:");
			id = safe_input();
			printf("å ���� �Է�: ");
			fgets(bookname, sizeof(bookname), stdin);
			bookname[strcspn(bookname, "\n")] = 0; //���๮�ڸ� �α�ȣ�� ��ȯ
			element data;
			strcpy(data.bookname,bookname);
			data.id = id;
			data.is_borrowed = 0;
			dinsert(head, data);
			break;
		case 2://��������
			printf("������ å ID �Է�: ");
			id = safe_input();
			borrow_book(head, id);
			break;
		case 3://���� �ݳ�
			printf("�ݳ��� å ID�Է�: ");
			id = safe_input();
			return_book(head, id);
			break;
		case 4://���� ��Ϻ���
			display_books(head);
			break;
		case 5://����
			printf("���α׷��� �����մϴ�\n");
			return 0;
			break;
		default:
			printf("�߸��� �����Դϴ�. �ٽ� �Է��ϼ���.\n");
			break;
		}
	}
	return 0;
}