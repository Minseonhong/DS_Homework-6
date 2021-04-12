/*
* singly linked list.c
*
*  Created on: 2021. 4. 11.
*      Author: 민선홍
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); // 헤드 노드 초기화
int freeList(headNode* h); // 노드 및 연결리스트 해제

int insertFirst(headNode* h, int key); // 리스트 맨 앞 입력 값 삽입
int insertNode(headNode* h, int key); // 리스트 입력 값 삽입
int insertLast(headNode* h, int key); // 리스트 맨뒤 뒤에 입력 값 삽임

int deleteFirst(headNode* h); // 첫번째 노드 삭제
int deleteNode(headNode* h, int key); // 입력 받은 값을 가지고 있는 노드 삭제
int deleteLast(headNode* h); // 마지막 노드 삭제
int invertList(headNode* h); // 가지고 있는 노드를 거꾸로 정렬하여 보여준다

void printList(headNode* h); // 연결리스트 출력

int main()
{
	printf("----- [민선홍] [2018038028] -----");
	char command; // 문자형 변수 command 생성
	int key; // 정수형 변수 key 생성
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch (command) { // command의 입력 받은 값에 따라 switch 문 실행
		case 'z': case 'Z':
			headnode = initialize(headnode); // 헤드노드 초기화 함수 실행
			break;
		case 'p': case 'P':
			printList(headnode); // 연결리스트 출력함수 실행
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key); // key의 값을 요청받음
			insertNode(headnode, key); // 노드의 값을 넣는 함수 실행
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key); // key의 값을 요청받음
			deleteNode(headnode, key); // 입력받은 노드의 값을 가지고 있는 노드 삭제 함수 실행
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key); // key의 값을 요청받음
			insertLast(headnode, key); // 연결리스트 맨 뒤에 값 삽입함수 실행
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 연결리스트 맨 뒤에 있는 노드의 값 삭제하는 함수 실행
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key); // key의 값을 요청받음
			insertFirst(headnode, key); // 연결리스트 맨 처음에 값 삽입함수 실행
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 연결리스트 첫번째 노드의 값 삭제하는 함수 실행
			break;
		case 'r': case 'R':
			invertList(headnode); // 연결리스트 안에 가지고 있는 노드의 값들을 반대로 정렬하여 실행
			break;
		case 'q': case 'Q':
			freeList(headnode); // 노드 및 연결리스트 해제하는 함수 실행
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	* headNode도 해제되어야 함.
	*/
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
* list 처음에 key에 대한 노드하나를 추가
*/
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* new; // 삽입할 신규 노드 newNode 정의
	listNode* x;
	listNode* prev;
	new = (listNode*)malloc(sizeof(listNode)); // new의 데이터 공간을 메모리에 할당받아 주소값 new에 저장
	new->key = key; // new의 데이터 필드에 key 저장
	new->link = NULL;
	if (h->first == NULL) // 만약 연결리스트가 공백인 경우
	{
		new->link = h->first;
		h->first = new; // h가 new를 가리킬 수 있도록 new를 저장하고 종료
		return 0;
	}
	else if (h->first->key >= new->key)
	{
		new->link = h->first;
		h->first = new;
		return 0;
	}
	else
	{
		x = h->first->link;
		prev = h->first;
		while (x != NULL)
		{
			if (x->key > new->key)
			{
				new->link = x;
				prev->link = new;
				return 0;
			}
			prev = x;
			x = x->link;

		}
		prev->link = new;
		new->link = NULL;
	}
	return 0;
}

/**
* list에 key에 대한 노드하나를 추가
*/
int insertLast(headNode* h, int key) {
	listNode* new; // 삽입할 신규 노드 newNode 정의
	listNode* last; // 노드가 존재할 경우 마지막 노드 last로 정의
	new = (listNode*)malloc(sizeof(listNode)); // new의 데이터 공간을 메모리에 할당받아 주소값new에 저장
	new->key = key; // new의 데이터 필드에 key 저장
	new->link = NULL; // 아직 가리키는 메모리 주소값이 없으므로 NULL 저장

	if (h->first == NULL) // 만약 연결리스트가 공백인 경우
	{
		h->first = new; // h가 new를 가리킬 수 있도록 new를 저장하고 종료
		return 0;
	}
	else
	{
		last = h->first; // 공백이 아닌경우, 헤드노드부터 시작해 반복하여 마지막 노드를 find
		while (last->link != NULL) last = last->link;
		last->link = new; // 마지막 노드의 링크 필드에 new의 주소값 저장하여 가리키게 한다.
	}
	return 0;
}


/**
* list의 첫번째 노드 삭제
*/
int deleteFirst(headNode* h) {
	listNode* del;

	if (h->first == NULL) return 0; // 만약 빈 리스트일 경우 종료
	if (h->first->link == NULL) // 리스트의 노드가 한 개일 경우,
	{
		free(h->first); // 노드의 메모리 해제
		h->first = NULL; // 노드의 link 필드에 NULL 할당
		return 0;
	}
	else
	{
		del = h->first;
		h->first = del->link;
		free(del);
	}
	return 0;
}


/**
* list에서 key에 대한 노드 삭제
*/
int deleteNode(headNode* h, int key) {
	listNode* del = h->first;
	listNode* prev = NULL;
	if (h->first == NULL) return 0; // 만약 빈 리스트일 경우 종료
	if (h->first->link == NULL) // 리스트의 노드가 한 개일 경우,
	{
		printf("1");
		if (key == del->key)
		{
			printf("2");
			free(del); // 노드의 메모리 해제
			h->first = NULL; // 노드의 link 필드에 NULL 할당
			return 0;
		}
	}
	else // 노드의 값이 2개 이상이면,
	{
		prev = h->first; // 전노드는 헤드가 가리키는 처음 노드의 값
		del = prev->link; // 지우려는 노드는 처음 노드가 가리키는 link
		if (prev->key == key) {//첫번째 노드가 삭제하려는 값이라면?
			h->first = prev->link;
			free(prev);
			return 0;
		}
		while (del != NULL) // 지우려는 노드의 NULL값 갈 때 까지,
		{
			if (del->key == key) // del이 key의 값이 가리 킬 때, key의 값과 같으면
			{
				prev->link = del->link; // prev 노드는 del이 가리키는 link
				free(del); // del 값 노드의 메모리 해제
				return 0;
			}
			prev = del;
			del = del->link;
		}
	}
	return 0;

}

/**
* list의 마지막 노드 삭제
*/
int deleteLast(headNode* h) {

	listNode* prev; // 삭제할 노드의 선행 노드를 가리키는 변수
	listNode* del; // 삭제할 노드를 가리킬 변수
	if (h->first == NULL) return 0; // 만약 빈 리스트일 경우 종료
	if (h->first->link == NULL) // 리스트의 노드가 한 개일 경우,
	{
		free(h->first); // 노드의 메모리 해제
		h->first = NULL; // 노드의 link 필드에 NULL 할당
		return 0;
	}
	else
	{
		prev = h->first; // 2개 이상인 경우, 삭제할 노드의 선행노드를 첫번 째 노드로 지정
		del = h->first->link; // 삭제할 노드를 두 번째 노드로 지정
		while (del->link != NULL) // while문을 이용하여, 링크필드가 NULL이 아닐 때 까지 뒤로 한칸 씩 이동
		{
			prev = del;
			del = del->link;
		}
		free(del); // 마지막 노드를 찾으면 메모리 해제
		prev->link = NULL; // 선행 노드의 링크 필드에 NULL 할당
	}
	return 0;
}


/**
* 리스트의 링크를 역순으로 재 배치
*/
int invertList(headNode* h) {

	listNode* p, *q, *r; // 순회 포인터로 p q r 사용
	p = h->first; // p는 현재 가리키는 노드
	q = NULL; // q에 NULL값을 넣어주면서 이전 노드
	while (p != NULL) // p가 NULL값을 가리킬 때 까지,
	{
		r = q; // r은 q, q는 p를 차례로 따라간다
		q = p;
		p = p->link; // p를 미리 옮겨 놓는다
		q->link = r; // q의 link 방향을 바꾼다
	}
	h->first = q; // q는 역순으로 되어있는 리스트의 헤드 포인터다
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
