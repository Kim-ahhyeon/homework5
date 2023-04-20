/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4  //MAX_QUEUE_SIZE는 4

typedef char element;               //typedef char형 변수 element 선언
typedef struct {                    //typedef 구조체
	element queue[MAX_QUEUE_SIZE];  //element형 배열 queue 선언, 배열의 크기는 4
	int front, rear;                //int형 변수 front, rear 선언
}QueueType;                         //구조체 변수의 이름은 QueueType


QueueType *createQueue();           //QueueType *createQueue() 정의
int freeQueue(QueueType *cQ);       //int형 함수원형 freeQueue() 정의, 매개변수 QueueType *cQ
int isEmpty(QueueType *cQ);         //int형 isEmpty() 정의, 매개변수 QueueType *cQ
int isFull(QueueType *cQ);          //int형 함수 isFull() 정의, 매개변수 QueueType *cQ
void enQueue(QueueType *cQ, element item);  //void형 함수 enQueue() 정의, 매개변수 QueueType *cQ
void deQueue(QueueType *cQ, element* item);  //void형 함수 deQueue() 정의, 매개변수 QueueType *cQ
void printQ(QueueType *cQ);                  //void형 함수 printQ() 정의, 매개변수 QueueType *cQ
void debugQ(QueueType *cQ);                  //void형 함수 debugQ() 정의, 매개변수 QueueType *cQ
element getElement();                        //element형 함수 getElement()정의


int main(void)
{
	QueueType *cQ = createQueue();  //구조체 QueueType 포인터 변수 *cQ 선언, createQueue() 대입
	element data;   

	char command;  //char형 변수 command 선언

    printf("[----- [Kim ah hyeon] [2022041010] -----]\n");

	do{
		printf("\n-----------------------------------------------------\n");  //----------------------------------------------------- 출력
		printf("                     Circular Q                   \n");       //                     Circular Q                    출력
		printf("------------------------------------------------------\n");   //------------------------------------------------------출력
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");   // Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q 출력
		printf("------------------------------------------------------\n");   //------------------------------------------------------ 출력

		printf("Command = ");  //Command = 출력
		scanf(" %c", &command); //command를 입력받음
 
		switch(command) {  //     //제어식이 command
		case 'i': case 'I':       //command가 i 또는 I이면
			data = getElement();  //data에 getElement() 대입
			enQueue(cQ, data);  //enQueue함수 호출, 
			break;              //break문
		case 'd': case 'D':     //command가 d 또는 D이면
			deQueue(cQ,&data);   //deQueue 함수 호출
			break;              //break문
		case 'p': case 'P':     //command가 p 또는 P이면
			printQ(cQ);         //printQ 함수 호출
			break;              //break문
		case 'b': case 'B':     //command가 b 또는 B이면
			debugQ(cQ);         //debugQ 함수 호출
			break;              //break문
		case 'q': case 'Q':     //command가 q 또는 Q이면
			break;              //break문
		default:                //어떤 case문 과도 일치되지 않을 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //       >>>>>   Concentration!!   <<<<<      출력
			break;                                                      //break문
		}

	}while(command != 'q' && command != 'Q');  //command가 'q'가 아니거나 'Q'가 아니면 조건문 계속 실행


	return 1;  //1을 반환한다.
}

QueueType *createQueue()
{
	QueueType *cQ;  //QueueType의 포인터변수 *cQ 선언
	cQ = (QueueType *)malloc(sizeof(QueueType));  //malloc으로 cQ에 동적할당함, 자료형은 QueType
	cQ->front = 0;  //cq->front에 0 대입
	cQ->rear = 0;   //cq->rear에 0 대입
	return cQ;      //cQ 값 반환
}

int freeQueue(QueueType *cQ)  //freeQueue(QueueType *cQ) 함수
{
    if(cQ == NULL) return 1;   //cQ가 NULL 이라면 1을 반환한다.
    free(cQ);                  //동적 메모리 반납
    return 1;                  //-1 반환
} 

element getElement()
{
	element item;
	printf("Input element = ");  //Input element =  출력
	scanf(" %c", &item);         //item을 입력받는다.
	return item;                 //item을 반환
}


int isEmpty(QueueType *cQ)     //isEmpty(QueueType *cQ) 함수
{
	if (cQ->front == cQ->rear){             //cQ->front가 cQ->rear와 같다면
		printf("Circular Queue is empty!"); //큐가 NULL임으로 Circular Queue is empty!를 출력함.
		return 1;                           //1을 반환한다.
	} 
	else return 0;                          //그렇지 않다면 0을 반환한다.
}

int isFull(QueueType *cQ)                              //isFull(QueueType *cQ) 함수
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {  //cQ->rear+1을 4로 나눈 나머지가 cQ->front와 같다면
		printf(" Circular Queue is full!");            // Circular Queue is full! 를 출력한다.
		return 1;                                      //1을 반환한다.
	}                    
	else return 0;                                     //그렇지 않다면 0을 반환한다.
}

void enQueue(QueueType *cQ, element item)              //enQueue(QueueType *cQ, element item) 함수
{
	if(isFull(cQ)) return;                             //isFull(cQ)가 반환되면 0 반환
	else {                                             //그렇지 않다면
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;    //cQ->rear에 cQ->rear+1을 4로 나눈 나머지 값 대입
		cQ->queue[cQ->rear] = item;                    //cQ->queue[cQ->rear] 에 item 대입
	}
}

void deQueue(QueueType *cQ, element *item)            //deQueue(QueueType *cQ, element *item) 함수
{
	if(isEmpty(cQ)) return;                           //isEmpty(cQ) 값이 반환되면
	else {                                            //그렇지 않다면
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;   //cQ->front에 cQ->front+1을 4로 나눈 나머지 값을 대입함.
		*item = cQ->queue[cQ->front];                 //*item에 cQ->queue[cQ->front] 대입
		return;                                       //0을 반환한다.
	}
}


void printQ(QueueType *cQ)                          //printQ(QueueType *cQ)
{
	int i, first, last;                              //정수형 변수 i, first, last 선언

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;          //first에 cQ->front+1을 4로 나눈 나머지 값을 대입
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;            //last에 cQ->rear + 1을 4로 나눈 나머지 값을 대입

	printf("Circular Queue : [");                    //Circular Queue : [ 출력

	i = first;                                       //i에 first 대입
	while(i != last){                                //i가 last와 같지 않다면
		printf("%3c", cQ->queue[i]);                 //cQ->queue[i] 값 출력
		i = (i+1)%MAX_QUEUE_SIZE;                    //i에는 (i+1)을 4로 나눈 나머지 대입

	}
	printf(" ]\n");                                  // ] 출력
}


void debugQ(QueueType *cQ)                                  //debugQ(QueueType *cQ) 출력
{

	printf("\n---DEBUG\n");                                 //---DEBUG 출력
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)                 //i가 0부터 MAX_QUEUE_SIZE 전까지 증가되며 반복문 실행
	{
		if(i == cQ->front) {                                //i가 cQ->front와 같다면
			printf("  [%d] = front\n", i);                  //[front] 출력
			continue;                                       //다음 반복 즉시 시작
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);           //[i] = cQ->queue[i] 출력

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);  //front = cQ->front값, rear = cQ->rear 값 출력
}
