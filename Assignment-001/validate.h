#include<string.h>

int validate(char *infix)
{
	int len=strlen(infix)-1;
	if(infix[0]=='-' || infix[0]=='*' || infix[0]=='/' || infix[len]=='+' || infix[len]=='-' || infix[len]=='*' || infix[len]=='/')
		return 0;
	else 
		return 1;
}
