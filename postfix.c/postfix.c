/** 
 * postfix.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20
/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{
      lparen = 0, /* ( 왼쪽 괄호 */
      rparen = 9, /* ) 오른쪽 괄호*/
      times = 7, /* * 곱셈 */
      divide = 6, /* / 나눗셈 */
      plus = 5, /* + 덧셈 */
      minus = 4, /* - 뺄셈 */
      operand = 1 /* 피연산자 */
} precedence;                       //
char infixExp[MAX_EXPRESSION_SIZE];  //char형 배열 infixExp[MAX_EXPRESSION_SIZE] 선언
char postfixExp[MAX_EXPRESSION_SIZE]; //char형 배열 postfixExp[MAX_EXPRESSION_SIZE] 선언
char postfixStack[MAX_STACK_SIZE];    //char형 배열 postfixStack[MAX_STACK_SIZE] 선언
int evalStack[MAX_STACK_SIZE];        //int형 배열 evalStack[MAX_STACK_SIZE] 선언

int postfixStackTop = -1;             //int형 변수 postfixStackTop 선언, -1로 초기화
int evalStackTop = -1;                //int형 변수 evalStackTop 선언, -1로 초기화

int evalResult = 0;                   //int형 변수 evalResult 선언, 0으로 초기화

void postfixPush(char x)              //void형 postfixPush(char x) 정의
char postfixPop()                     //char형 postfixPop() 정의
void evalPush(int x)                  //void형 evalPush(int x) 정의
int evalPop()                         //int형 evalPop() 정의
void getInfix()                       //void형 getInfix() 정의
precedence getToken(char symbol)      //precedence getToken(char symbol) 정의
precedence getPriority(char x)        //precedence getPriority(char x) 정의
void charCat(char* c)                 //void형 charCat(char* c) 정의
void toPostfix()                      //void형 toPostfix() 정의
void debug()                          //void형 debug() 정의
void reset()                          //void형 reset() 정의
void evaluation()                     //void형 evaluation() 정의


int main()
{
      char command;                   //char형 변수 command 선언
      do{

printf("[----- [Kim ah hyeon] [2022041010] -----]\n");


printf("----------------------------------------------------------------\n");   //---------------------------------------------------------------- 출력
printf(" Infix to Postfix, then Evaluation \n");                               // Infix to Postfix, then Evaluation  출력
printf("----------------------------------------------------------------\n");   //---------------------------------------------------------------- 출력
printf(" Infix=i, Postfix=p, Eval=e, Debug=d, Reset=r, Quit=q \n");             // Infix=i, Postfix=p, Eval=e, Debug=d, Reset=r, Quit=q  출력
printf("----------------------------------------------------------------\n");   //---------------------------------------------------------------- 출력
printf("Command = ");                                                           //Command =  출력
scanf(" %c", &command);                                                         //command 값 출력

switch(command) {  //제어식 command
case 'i': case 'I':  //command가 i 또는 I이면
       getInfix();
       break;        //break 문
case 'p': case 'P':  //command가 i 또는 I이면
       toPostfix();
       break;        //break 문
case 'e': case 'E':  //command가 i 또는 I이면
       evaluation();
       break;        //break 문
case 'd': case 'D':  //command가 i 또는 I이면
       debug();
       break;        //break 문
case 'r': case 'R':  //command가 i 또는 I이면
       reset();
       break;        //break 문
case 'q': case 'Q':  //command가 i 또는 I이면
       break;        //break 문
default:             //어떤 case문과도 일치하지 않으면
       printf("\n >>>>> Concentration!! <<<<< \n");   // >>>>> Concentration!! <<<<<  출력
       break;                                         //break 문
}
}while(command != 'q' && command != 'Q'); //command가 'q'도 아니고 'Q'가 아니면 계속 반복
return 1;                                 //1 반환
}

void postfixPush(char x)
{
 postfixStack[++postfixStackTop] = x;  //postfixStack[++postfixStackTop] 에 x를 대입한다.
}


char postfixPop()
{ 
char x;                             //char형 변수 x 선언
 if(postfixStackTop == -1)          //만약 postfixStackTop 이 -1이라면
 return '\0';                       //\0 반환
 else {                             //아닐 경우
 x = postfixStack[postfixStackTop--];  //x에 postfixStack[postfixStackTop--] 대입
 } 
 return x; //x 반환
}


void evalPush(int x)
{
 evalStack[++evalStackTop] = x;   //evalStack[++evalStackTop] 에 x를 대입한다.
}


int evalPop()
{ 
 if(evalStackTop == -1)          //만약 evalStackTop 이 -1이라면
 return -1;                      //-1 반환
 else                            //아닐 경우
 return evalStack[evalStackTop--];  //evalStack[evalStackTop--] 반환
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */


void getInfix()
{
 printf("Type the expression >>> ");  //Type the expression >>>  출력
 scanf("%s",infixExp);                //infixExp를 입력받는다.
}


precedence getToken(char symbol)
{
switch(symbol) {         //제어식이 symbol
case '(' : return lparen; //symbol이 '('이면 lparen 반환
case ')' : return rparen; //symbol이 ')'이면 lparen 반환
case '+' : return plus; //symbol이 '+'이면 lparen 반환
case '-' : return minus; //symbol이 '-'이면 lparen 반환
case '/' : return divide; //symbol이 '/'이면 lparen 반환
case '*' : return times; //symbol이 '*'이면 lparen 반환
default : return operand; //어떤 case문도 아니면 operand 반환
}
}


precedence getPriority(char x)
{
return getToken(x);     //getToken(x) 반환
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */

void charCat(char* c)
{  
if (postfixExp == '\0')    //postfixExp 이 '\0'이라면
strncpy(postfixExp, c, 1);  //po
else                        //아닐 경우
strncat(postfixExp, c, 1);
}


/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
/* infixExp의 문자 하나씩을 읽기위한 포인터 */
    char *exp = infixExp;
    char x; /* 문자하나를 임시로 저장하기 위한 변수 */
/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
    while(*exp != '\0')
    {
         if(getPriority(*exp) == operand)    //getPriority(*exp) 이 operand와 같다면
         {
           x = *exp;  //x에 *exp 값 대입
         charCat(&x); //charCat(&x) 함수 호출
         }
     else if(getPriority(*exp) == lparen) {  //getPriority(*exp) == lparen이면
       postfixPush(*exp);                    //postfixPush(*exp) 호출
      }
     else if(getPriority(*exp) == rparen)    //getPriority(*exp) == rparen이면
    {
       while((x = postfixPop()) != '(') {    //(x = postfixPop()) != '('이면
              charCat(&x);                   //charCat(&x 호출
       } 
    }
     else
     {
        while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))   //getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)이면
        {
             x = postfixPop();   //x = postfixPop() 대입
             charCat(&x);        //charCat(&x) 호출
        }
        postfixPush(*exp);       //postfixPush(*exp) 호출
    }
    exp++;                       //exp 증가
   }

 while(postfixStackTop != -1)    //postfixStackTop != -1이면
 {
 x = postfixPop();   //x 에 postfixPop() 대입
 charCat(&x);        //charCat(&x) 함수 호출
 }
}


void debug()
{
printf("\n---DEBUG\n");             //---DEBUG 출력
printf("infixExp = %s\n", infixExp); //infixExp =  출력
printf("postExp = %s\n", postfixExp);  //postExp =  출력
printf("eval result = %d\n", evalResult);  //eval result =  출력
printf("postfixStack : ");                  //postfixStack : " 출력
for(int i = 0; i < MAX_STACK_SIZE; i++)     //i 0으로 초기화,  MAX_STACK_SIZE 전까지 증가하며 반복문 실행
printf("%c ", postfixStack[i]);             //postfixStack[i] 값 출력
printf("\n");                               //줄바꿈
}


void reset()
{
infixExp[0] = '\0';                    //infixExp[0] 를 '\0'으로 초기화
postfixExp[0] = '\0';                  //postfixExp[0] 를 '\0'으로 초기화
for(int i = 0; i < MAX_STACK_SIZE; i++)     //i 0으로 초기화,  MAX_STACK_SIZE 전까지 증가하며 반복문 실행
postfixStack[i] = '\0';                     //postfixStack[i] 를 '\0'으로 초기화
 
postfixStackTop = -1;                       //postfixStackTop 를 -1으로 초기화
evalStackTop = -1;                          //evalStackTop 를 -1으로 초기화
evalResult = 0;                             //evalResult 를 0으로 초기화
}



void evaluation()
{
      int opr1, opr2, i;                       //int형 변수 opr1, opr2, i 선언
      
      int length = strlen(postfixExp);         //int형 변수 length 선언, strlen(postfixExp)으로 초기화
      char symbol;                             //char형 변수 symbol 선언
      evalStackTop = -1;                       //evalStackTop -1로 초기화

      for(i = 0; i < length; i++)
      {
          symbol = postfixExp[i];
          if(getToken(symbol) == operand) {
                evalPush(symbol - '0');
          }
          else {
               opr2 = evalPop();
               opr1 = evalPop();
               switch(getToken(symbol)) {                //제어식이 getToken(symbol)
               case plus: evalPush(opr1 + opr2); break;  //제어식이 plus일 경우, evalPush(opr1 + opr2) 호출, break
               case minus: evalPush(opr1 - opr2); break; //제어식이 minus일 경우, evalPush(opr1 - opr2) 호출, break
               case times: evalPush(opr1 * opr2); break; //제어식이 times일 경우, evalPush(opr1 * opr2) 호출, break
               case divide: evalPush(opr1 / opr2); break; //제어식이 devide일 경우, evalPush(opr1 / opr2) 호출, break
               default: break;                            //어떤 조건문과도 일치하지 않으면, break
               }
          }
      }
       evalResult = evalPop();                           //evalResult에 evalPop() 대입
 }