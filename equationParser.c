#include <stdio.h>      /* printf, scanf */
#include <string.h>		/* strlen, */
#include <stdlib.h>
#include <ctype.h>		/* isdigit */

int oper(int a, char o, int b){
	int c;
	switch(o){
		case '+':
			c = a+b;
			break;
		case '-':
			c = a-b;
			break;
		case '*':
			c = a*b;
			break;
		case '/':
			c = a/b;
			break;
		case '%':
			c = a%b;
			break;
	}
	return c;
}

int main(){
	int limit = 50;
	char equ[limit];

	printf("Hello!\n");


	while(1){
		printf("Please enter the equation (%d) ex. 1+2 :\n", limit);
		fflush(stdout);
		equ[0] = 0; /*memset(equ,0,limit);*/
		scanf("%49[0-9 +.-*/%()]", equ); /*49 related to variable limit*/
		fflush(stdin);
		if (equ[0]==0){
			printf("Thank you!\n");
			break;
		}
		printf("You have entered %s\n", equ);
		fflush(stdout);

		//extract numbers and operators
		int i, state = 1, k = 0, numLimit = 10, x = 0;
		int val1 = 0, val2 = 0, val3 = 0;
		char num1[numLimit], op1, num2[numLimit], op2, num3[numLimit];
		num1[0] = 0; num2[0] = 0; num3[0] = 0;
		for (i=0; i <= strlen(equ); i++){
			printf("state=%d\n",state);
			switch(state){
				case 1://find val1
					if (isdigit(equ[i])){
						num1[k] = equ[i];
						k++;
						num1[k] = 0;
					}
					else {
						if (equ[i] == ' '){
							val1 = atoi(num1);
							k = 0;
							state = 2;
						}
						else if (equ[i] == '+' || equ[i] == '-' || equ[i] == '*' || equ[i] == '/' || equ[i] == '%'){
							val1 = atoi(num1);
							k = 0;
							op1 = equ[i];
							state = 3;
						}
						else if (equ[i] == 0){
							val1 = atoi(num1);
							x = 1;
						}
						else {
							printf("Wrong equation at i = %d. Try again.\n", i);
							x = 2;
						}
					}
					break;

				case 2://find op1
					if (equ[i] == '+' || equ[i] == '-' || equ[i] == '*' || equ[i] == '/' || equ[i] == '%'){
						op1 = equ[i];
						state = 3;//find val2
					}
					else if (equ[i] == ' '){
					}
					else {
						printf("Wrong equation at i = %d. Try again.\n", i);
						x = 2;
					}
					break;

				case 3://find val2
					if (isdigit(equ[i])){
						num2[k] = equ[i];
						k++;
						num2[k] = 0;
					}
					else {
						if (equ[i] == ' '){
							if (k != 0){
								val2 = atoi(num2);
								k = 0;
								//calculate if op1 is * or / or %
								if (op1 == '*' || op1 == '/' || op1 == '%'){
									val1 = oper(val1, op1, val2);
									state = 2; //find op1
								}
								else {
									state = 4; //find op2
								}
							}
							else {
							}
						}
						else if (equ[i] == '+' || equ[i] == '-' || equ[i] == '*' || equ[i] == '/' || equ[i] == '%'){
							if (k != 0){
								val2 = atoi(num2);
								k = 0;
								//calculate if op1 is * or / or %
								if (op1 == '*' || op1 == '/' || op1 == '%'){
									val1 = oper(val1, op1, val2);
									op1 = equ[i];
									state = 3; //find val2
								}
								else {
									op2 = equ[i];
									state = 5; //find val3
								}
							}
							else {
								printf("Wrong equation at i = %d. Try again.\n", i);
								x = 2;
							}
						}
						else if (equ[i] == 0){
							if (k != 0){
								val2 = atoi(num2);
								val1 = oper(val1, op1, val2);
								x = 1;
							}
							else {
								printf("Wrong equation at i = %d. Try again.\n", i);
								x = 2;
							}
						}
					}
					break;

				case 4://find op2
					if (equ[i] == '+' || equ[i] == '-' || equ[i] == '*' || equ[i] == '/' || equ[i] == '%'){
						op2 = equ[i];
						state = 5;//find val3
					}
					else if (equ[i] == ' '){
					}
					else {
						printf("Wrong equation at i = %d. Try again.\n", i);
						x = 2;
					}
					break;

				case 5://find val3
					if (isdigit(equ[i])){
						num3[k] = equ[i];
						k++;
						num3[k] = 0;
					}
					else {
						if (equ[i] == ' '){
							if (k != 0){
								val3 = atoi(num3);
								k = 0;
								//calculate if op2 is * or / or %
								if (op2 == '*' || op2 == '/' || op2 == '%'){
									val2 = oper(val2, op2, val3);
									state = 4; //find op2
								}
								else {
									val1 = oper(val1, op1, val2);
									op1 = op2;
									val2 = val3;
									state = 4; //find op2
								}
							}
							else {
							}
						}
						else if (equ[i] == '+' || equ[i] == '-' || equ[i] == '*' || equ[i] == '/' || equ[i] == '%'){
							if (k != 0){
								val3 = atoi(num3);
								k = 0;
								//calculate if op2 is * or / or %
								if (op2 == '*' || op2 == '/' || op2 == '%'){
									val2 = oper(val2, op2, val3);
									op2 = equ[i];
									state = 5; //find val3
								}
								else {
									val1 = oper(val1, op1, val2);
									op1 = op2;
									val2 = val3;
									op2 = equ[i];
									state = 5; //find val3
								}
							}
							else {
								printf("Wrong equation at i = %d. Try again.\n", i);
								x = 2;
							}
						}
						else if (equ[i] == 0){
							if (k != 0){
								val3 = atoi(num3);
								if (op2 == '*' || op2 == '/' || op2 == '%'){
									val2 = oper(val2, op2, val3);
									val1 = oper(val1, op1, val2);
									x = 1;
								}
								else {
									val1 = oper(val1, op1, val2);
									op1 = op2;
									val2 = val3;
									val1 = oper(val1, op1, val2);
									x = 1;
								}
							}
							else {
								printf("Wrong equation at i = %d. Try again.\n", i);
								x = 2;
							}
						}
					}
					break;
			}//switch
			if (x) break;
		}//for
		if (x != 2){
			printf("ans = %d\n", val1);
		}
		fflush(stdout);
	}
	return 0;
}
