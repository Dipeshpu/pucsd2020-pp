#include<stdio.h>
#include<stdlib.h>      /* for exit()*/ 
#include<ctype.h>     /* for isdigit(char )*/ 
#include<string.h>
#include "include/mul.h"
#include "include/div.h"
#include "include/add.h"
#include "include/sub.h"
#include "validate.h"
#define SIZE 100
char x[20][10];
char operator[4]={'*','/','-','+'};


void solve_expression(int j)
{
	int i,m,flg=0;
	for(i=0;i<4;i++)
	{
		for(m=1;m<j;)
		{
			char temp[20];
			flg=0;
			if(operator[i]==x[m][0] && i==0)
			{
				flg=1;
				int re=multiplication(x[m-1],x[m+1]);
				sprintf(temp,"%d",re);
			}
			else if(operator[i]==x[m][0] && i==1)
			{
				flg=1;
				if(atoi(x[m+1])==0)
				{
					printf("invalid expression..! any no not divided by 0\n");
					exit(1);
				}
				int re=division(x[m-1],x[m+1]);
				sprintf(temp,"%d",re);
			}
			else if(operator[i]==x[m][0] && i==3)
			{
				flg=1;
				int re=addition(x[m-1],x[m+1]);
				sprintf(temp,"%d",re);
			}
			else if(operator[i]==x[m][0] && i==2)
			{
				flg=1;
				int re=substraction(x[m-1],x[m+1]);
				sprintf(temp,"%d",re);
			}

			if(flg==1)
			{
				int kk;
				for(kk=0;kk<strlen(temp);kk++)
				{
					x[m-1][kk]=temp[kk];
				}
				x[m-1][kk]='\0';
				int len_m=m;
				for(kk=m+2;kk<j;kk++)
				{
					int n;
					for(n=0;n<strlen(x[kk]);n++)
					{
						x[len_m][n]=x[kk][n];
					}
					x[len_m][n]='\0';
					len_m++;
				}
			}
			if(flg==1)
				j=j-2;
			else
				m=m+2;

		}
	}

	//for(int i=0;i<j;i++)
	//	printf("%s\n",x[i]);
}


/* this fucntion returns 1 if symbol is opreator else return 0 */

int is_operator(char symbol)
{
	if(symbol == '*')
		return 1;
	else if(symbol == '/')
		return 2;
	else if(symbol == '-')
		return 3;
	else
		return 4;
	
}


void given_exp_stor_in_x_and_validate_exp(char *infix_exp)
{ 
	int i,j,m;
	char item;
	i=0;
	j=0;
	m=0;
	item=infix_exp[i];	/* initialize before loop*/
	if(item=='+')
	{
		i++;
		item=infix_exp[i];
	}
	while(item != '\0')        /* run loop till end of infix expression */
	{
		if((item=='+' || item=='-' || item=='*' || item=='/') && i==0)
		{
			printf("Invalid expression....!\n");
			exit(1);
		}
		if(item==' ')
		{
			i++;
			item=infix_exp[i];
		}
		else if(isdigit(item))
		{
			  int k=0;
       			  char a[6];
			  for(m=0;m<7;m++)
			  {
				  if(item==' ')
				  {
					  i++;
					  item=infix_exp[i];
				  }
				  else if(isdigit(item))
				{
					a[k]=item;
					k++;
				 	i++;
					item=infix_exp[i];
				}
				else
				{
					a[k]='\0';
					for(m=0;m<strlen(a);m++)
					x[j][m]=a[m];

					x[j][m]='\0';
					j++;
					break;
				}
			}
		}
		else
		{
			m=0;
		      	if(is_operator(item) == 1)        /* means symbol is operator */
				x[j][m]='*';
			else if(is_operator(item)==2)
				x[j][m]='/';
			else if(is_operator(item)==3)
				x[j][m]='-';
			else
				x[j][m]='+';

			x[j][m+1]='\0';
			j++;
			i++;
			item=infix_exp[i];
		}
	}
	solve_expression(j);

}

/* main function begins */
int main()
{
	char infix[SIZE];         /* declare infix string and postfix string */
	printf("\nEnter expression : ");
	scanf("%[^\n]s",infix);
	if(validate(infix))
	{
		given_exp_stor_in_x_and_validate_exp(infix);	/* call to convert */
		printf("%s\n",x[0]);
	}
	else
	{
		printf("Invalid Expression.....!\n");
		exit(1);
	}
	return 0;
}
