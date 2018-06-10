/*
  Infix to postfix conversion and evaluate postfix expression in C 
  Operands and operator, both must be single character.
  Only '+'  ,  '-'  , '*', '/' and operators are expected. 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#define SIZE 50
typedef struct STACK
{
    int top;
    char st[SIZE];
}STACK;

int abc[26];// Function to show results
void initialize(STACK *);
int isEmpty(STACK);
int isFull(STACK);
char pop(STACK *);
void push(STACK *,char);
void infixToPostfix(char *, STACK *);
int evaluatePostfix(char* , STACK *, char *);
void isNumber();
int precedence(char);// Function to verify whether an operator has higher precedence over other
int isOperator(char);

int main()
{
    char *expression,*c;
    expression=(char *)malloc(100*sizeof(char));
    STACK *stack;
    stack=(STACK *)malloc(sizeof(STACK));
    FILE *fp;
    fp=fopen("input.txt","r");
    initialize(stack);
    do
    {
        c = fgets(expression,255,fp);
        if (c != NULL)
        {
            infixToPostfix(expression,stack);
        }
    } while (c != NULL);

    printf("\n\nRESULTS TABLE\n");
    int i=0;
    while(i<26)
    {
        printf("%c<-%d\t",('a'+i),abc[i]);
        if(i!=0&&i%3==0)
            printf("\n");
        i++;
    }

    return 1;
}
int isOperator(char symbol)
{
	if(symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-')
	{
		return 1;
	}
	else
	{
	return 0;
	}
}
int precedence(char x)
{
    if(x=='(')
        return(0);
    if(x=='+'||x=='-')
        return(1);
    if(x=='*'||x=='/'||x=='%')
        return(2);

    return(3);
}
void infixToPostfix(char *expression,STACK *stack)
{
    int j;
    char *variable,x;
    char postfix[100];

    printf("INTERIM OPERATIONS:\t");
    printf("%s",expression);
    printf("infix to postfix:\n\n");

    variable=strtok (expression," ");
    variable=strtok (NULL," ");
    variable=strtok (NULL," ");
    j=0;
    while(*variable != ';')
    {
        if(*variable=='(')
        {
            push(stack,*variable);
        }
        else if( isdigit(*variable) || isalpha(*variable))
		{
			postfix[j] = *variable;
			j++;
		}
		else if(*variable == ')')
		{
			x = pop(stack);
			while(x != '(')
			{
				postfix[j] = x;
				j++;
				x = pop(stack);
			}
		}
		else if(isOperator(*variable) == 1)        /* means symbol is operator */
		{
			while(isOperator(stack->st[(stack->top)-1]) == 1 && precedence(stack->st[(stack->top)-1])>= precedence(*variable))
			{
			    x = pop(stack);
			    postfix[j] = x;
				j++;

			}
			push(stack,*variable);
		}
        postfix[j]='\0';
        stack->st[stack->top]='\0';
        printf("postfix:%s\t\t\t\tstack:%s\n",postfix,stack->st);

        variable=strtok (NULL," ");
    }

     while(!isEmpty(*stack))
    {
        x=pop(stack);
        postfix[j++]=x;
    }
    postfix[j]='\0';
    stack->st[stack->top]='\0';
    printf("postfix:%s\t\t\t\tstack:%s   (interm result)\n",postfix,stack->st);
    printf("interim result:%c<-%d \n",expression[0],evaluatePostfix(postfix , stack ,expression));
    printf("------------------------------------------------\n");
}
int evaluatePostfix(char *postfix , STACK * stack, char *exp)
{
    printf("\n\nevaluate postfix:\n\n");
    int j,i;

    for (i = 0; postfix[i]; i++)
    {
        if (isalpha(postfix[i]))
            push(stack, abc[postfix[i]-'a']);
        else if (isdigit(postfix[i]))
            push(stack, postfix[i]-'0');
        else
        {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (postfix[i])
            {
             case '+': push(stack, val2 + val1); break;
             case '-': push(stack, val2 - val1); break;
             case '*': push(stack, val2 * val1); break;
             case '/': push(stack, val2/val1);   break;
            }
        }
        stack->st[stack->top]='\0';
        j=0;
        printf("stack: ");
        while(stack->st[j]!='\0')
        {
            printf("%d ",stack->st[j]);
            j++;
        }
        printf("\n");

    }
    abc[exp[0]-'a']=pop(stack);
    return abc[exp[0]-'a'];
}


void initialize(STACK *stack)
{
    stack->top=0;
}
int isEmpty(STACK stack)
{
    if(stack.top==0)
        return 1;
    else
        return 0;
}
int isFull(STACK stack)
{
    if(stack.top==SIZE)
        return 1;
    else
        return 0;
}
void push(STACK *stack, char value)
{
    if(isFull(*stack))
        printf("full\n");
    else
    {
        stack->st[stack->top]=value;
        stack->top++;
    }
}
char pop(STACK *stack)
{
    if(isEmpty(*stack))
        printf("empty\n");
    else
    {
        stack->top--;
        return stack->st[stack->top];
    }
}
