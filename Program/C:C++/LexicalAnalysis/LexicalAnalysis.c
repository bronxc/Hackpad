/**
 * Description: This is test to analyse string, and judge type of variable, finally print
 *				Three tuple. example: sum(int, 10)
 * Environment: Linux or Unix. compile by gcc.
 * Author: xx
 * Time: 2017.3.23
 */

#include <stdio.h>
#include <string.h>

#define STR_BUF_SIZE 65535
#define LIST_BUF_SIZE 2048
#define VARIABLE_LENGTH 10
#define VALUE_LENGTH 255

#define TRUE 1
#define FALSE 0

#define INT 1
#define FLOAT 2
#define CHAR 3
#define STRING 4
#define TYPENUM 4

#define ERROR_NONE 0
#define ERROR_NAME_FIRSTLETTER 1
#define ERROR_NAME_INVALIDCH 2
#define ERROR_NAME_KEYWORD 3
#define ERROR_NAME_REPEATDEFINE 4

#define ERROR_VALUE_OVERCHAR 5
#define ERROR_VALUE_LACKQUOTATION 6
#define ERROR_VALUE_POINT 7
#define ERROR_VALUE_INT_ZEROFIRST 8
#define ERROR_VALUE_FLOAT_INVALID 9

/****************************************************************************
Description: This is struct for store content of expression.

****************************************************************************/
struct Node {
	int errorCode;					//Error or not
	int type;						//type
	char name[VARIABLE_LENGTH];		//variable name
	char value[VALUE_LENGTH];		//variable value
};

//this is a list to store keyWords, '#' express end.
const char* keyWords[] = {"const", "int", "float", "char", "string", "#"};

//type string
char intString[] = {"int"};
char floatString[] = {"float"};
char charString[] = {"char"};
char stringString[] = {"string"};

//error string
char errorNameFirstLetterString[] = {"ErrorCode:1. Wrong. The variable name must begin with a letter."};
char errorNameInvalidCH[] = {"ErrorCode:2. Wrong. The variable name only contain numbers, letters and underscores."};
char errorNameKeyword[] = {"ErrorCode:3. Wrong. The variable name conflict with keywords."};
char errorNameRepeatDefine[] = {"ErrorCode:4. Wrong. The variable name already has been defined."};

char errorValueOverChar[] = {"ErrorCode:5. Wrong. The length of value over 1, type \'char\' length is 1."};
char errorValueLackQuotation[] = {"ErrorCode:6. Wrong. The type of value like \'string\' but lack quotation."};
char errorValuePoint[] = {"ErrorCode:7. Wrong. The position of point not allow first and last."};
char errorValueIntZeroFirst[] = {"ErrorCode:8. Wrong. type \'int\' not allow to start with 0."};
char errorValueFloatInvalid[] = {"ErrorCode:9. Wrong. type \'float\' is invalid with part of integer."};


/****************************************************************************
Description: define global variable and function.

****************************************************************************/
char str[STR_BUF_SIZE] = {0};			//store user input string
struct Node nodeList[LIST_BUF_SIZE];	//store every expression

int isBlank(char c);
int isConstString();
int isLetter(char c);
int isCharacter(char c);
int splitStr(int p, int length);
int trim(char* s);
int analyseName(int currentCount);
int analyseValue(int currentCount);
int analyseOtherValue(int currentCount);
int printResult(int length);
int printTotalResult(int length);

/****************************************************************************
Description: function main, handle program main process.
parameter: int argc, (unused)
parameter: char* argv, (unused)
return: int

****************************************************************************/
int main(int argc, char* argv[]) {
	int length = 0;
	int p = 0;			//point
	int tupleCount = 0;
	int result = 0;
	int i = 0;

	//input 
	char tempC = 0;
	tempC = getchar();
	while(tempC != ';') {
		str[length] = tempC;
		length = length + 1;
		tempC = getchar();
	}
	str[length] = ';';

	//is 'const' or not
	result = isConstString();
	if(result == FALSE) {
		printf("It is not a constant declaration statement!\nPlease input a string again!\n");
		return 0;
	}

	//set point
	p = 6;

	//call Function splitStr(), to split str by user input
	tupleCount = splitStr(p, length);
	if(tupleCount == 0) {
		printf("Input is Error!\n");
		return 0;
	}

	//start analyse
	for(i = 0; i < tupleCount; i++) {
		//trim()
		trim(nodeList[i].name);
		trim(nodeList[i].value);

		//start analyse
		analyseName(i);
		analyseValue(i);

		//test print
		printf("count: %d, error: %d, name: %s, value: %s, type: %d\n", i, nodeList[i].errorCode, nodeList[i].name, nodeList[i].value, nodeList[i].type);
	}

	//print result
	printResult(tupleCount);

	//finish. print totalResult
	printTotalResult(tupleCount);

	return 0;
}

/****************************************************************************
Description: function isBlank, judge parameter is blank character or not, it can replace by isspace()
parameter: char c, judge character.
return: int(bool)

****************************************************************************/
int isBlank(char c) {			//can replace by function isspace()
	if(c == ' ' || c == '\t' || c == '\n' || c == '\r') {
		return TRUE;
	}
	return FALSE;
}

/****************************************************************************
Description: function isConstString, judge string from input is start with "const".
parameter: null.
return: int(bool)

****************************************************************************/
int isConstString() {
	int i = 0;
	char buf[6] = {0};
	//strlen("const") = 5

	for(i = 0; i < 5; i++) {
		buf[i] = str[i];
	}
	buf[5] = '\0';

	if(isBlank(str[5]) && strcasecmp(buf, "const") == 0) {
		return TRUE;
	}
	return FALSE;
}

/****************************************************************************
Description: function isLetter, judge character is letter or not.
parameter: char c, judge character.
return: int(bool)

****************************************************************************/
int isLetter(char c) {
	if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
		return TRUE;
	}
	return FALSE;
}
/****************************************************************************
Description: function isCharacter, judge character is letter or number or '_'.
parameter: char c, judge character.
return: int(bool)

****************************************************************************/
int isCharacter(char c) {
	if((c >= 65 && c<= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == '_') {
		return TRUE;
	}
	return FALSE;
}

/****************************************************************************
Description: function splitStr, split string from user input, scan from the begin of string, 
			 split by '=', store nodeList[i].name before '=', store nodeList[i].value after '=';
			 then split by ',', i = i + 1.
parameter: int p, current point show position of string.
parameter: int length, length of string.
return: int, length of nodeList.

****************************************************************************/
int splitStr(int p, int length) {
	int nodeCount = 0;
	int mark = FALSE;				// mark '='
	int i = 0;
	int j = 0;

	while(p < length) {
		//before '='
		if(mark == FALSE) {
			if(str[p] == '=') {
				nodeList[nodeCount].name[i] = '\0';
				mark = TRUE;
				p = p + 1;
				continue;
			}
			nodeList[nodeCount].name[i] = str[p];
			i = i + 1;
			p = p + 1;
		}
		//after '='
		else {
			//read '\''
			if(str[p] == '\'') {
				nodeList[nodeCount].value[j] = str[p];
				j = j + 1;
				p = p + 1;
				while(str[p] != '\'') {
					nodeList[nodeCount].value[j] = str[p];
					j = j + 1;
					p = p + 1;
				}
				nodeList[nodeCount].value[j] = str[p];
			}
			//read '\"'
			if(str[p] == '\"') {
				nodeList[nodeCount].value[j] = str[p];
				j = j + 1;
				p = p + 1;
				while(str[p] != '\"') {
					nodeList[nodeCount].value[j] = str[p];
					j = j + 1;
					p = p + 1;
				}
				nodeList[nodeCount].value[j] = str[p];
			}
			//split by ',' or ';'
			if(str[p] == ',' || str[p] == ';') {
				nodeList[nodeCount].value[j] = '\0';
				nodeCount = nodeCount + 1;
				
				//inital variable
				mark = FALSE;
				i = 0;
				j = 0;

				p = p + 1;				//skip str[p] = ','
				continue;
			}

			//normal character
			nodeList[nodeCount].value[j] = str[p];
			j = j + 1;
			p = p + 1;
		}
	}
	
	/*test
	for(int k = 0; k <= nodeCount; k++) {
		printf("Count: %d\n", k);
		printf("name: %s, length=%lu\n", nodeList[k].name, strlen(nodeList[k].name));
		printf("value: %s, length=%lu\n", nodeList[k].value, strlen(nodeList[k].value));
	}
	*/

	return nodeCount + 1;	//return length of nodeList
}

/****************************************************************************
Description: function trim, trim blank character at begin and end of string.
parameter: char* s, string.
return: int

****************************************************************************/
int trim(char* s) {
	char* p = s;
	int gap = 0;

	//ltrim()
	while(isBlank(*p) == TRUE) {
		p = p + 1;
	}
	gap = p - s;
	while(*p != '\0') {
		*(p-gap) = *p;
		p = p + 1;
	}
	*(p-gap) = '\0';

	//rtrim()
	p = p - gap - 1;
	while(isBlank(*p) == TRUE) {
		*p = '\0';
		p = p - 1;
	}

	return 0;
}

/****************************************************************************
Description: function analyseName, analyse variable name. the variable is only start with
			 letter, and only contain letter, number and '_'.
parameter: int currentCount, this is postion in nodeList.
returnL int

****************************************************************************/
int analyseName(int currentCount) {
	char* name = nodeList[currentCount].name;
	char* p = name;
	int i = 0;

	//legal characters
	if(isLetter(*p) == FALSE) {
		nodeList[currentCount].errorCode = ERROR_NAME_FIRSTLETTER;
		return -1;
	}
	p = p + 1;

	while(*p != '\0') {
		if(isCharacter(*p) == FALSE) {
			nodeList[currentCount].errorCode = ERROR_NAME_INVALIDCH;
			return -1;
		}
		p = p + 1;
	}

	//removal keyWords
	while(strcmp(keyWords[i], "#") != 0) {
		if(strcmp(name, keyWords[i]) == 0) {
			nodeList[currentCount].errorCode = ERROR_NAME_KEYWORD;
			return -1;
		}
		i = i + 1;
	}

	//removal same
	i = 0;
	while(i < currentCount) {
		if(strcmp(name, nodeList[i].name) == 0) {
			nodeList[currentCount].errorCode = ERROR_NAME_REPEATDEFINE;
			return -1;
		}
		i = i + 1;
	}

	nodeList[currentCount].errorCode = ERROR_NONE;
	return 0;
}

/****************************************************************************
Description: function analyseValue, analyse variable value. it is int or float or 
			 char or string.
parameter: int currentCount, this is postion in nodeList.
returnL int

****************************************************************************/
int analyseValue(int currentCount) {
	if(nodeList[currentCount].errorCode != ERROR_NONE) {
		return -1;
	}

	char* value = nodeList[currentCount].value;
	char* p = value;
	int length = strlen(value);

	//string
	if(*p == '\"' && *(p + length - 1) == '\"') {
		nodeList[currentCount].type = STRING;
		return 0;
	}

	//character
	if(*p == '\'' && length == 3) {
		nodeList[currentCount].type = CHAR;
		return 0;
	}
	else if(*p == '\'' && length > 3) {
		nodeList[currentCount].errorCode = ERROR_VALUE_OVERCHAR;
		return -1;
	}
	else {
		//other. Haaaaaa, complex, use new function to solve.
		analyseOtherValue(currentCount);
	}

	return 0;
}

/****************************************************************************
Description: function analyseOtherValue, the value is not char and string, go on analyse it is
			 int or float.
parameter: int currentCount, this is postion in nodeList.
returnL int

****************************************************************************/
int analyseOtherValue(int currentCount) {
	char* value = nodeList[currentCount].value;
	char* p = value;
	int point = -1;

	//number first is '+' or '-'.
	if(*p == '+' || *p == '-') {
		p = p + 1;
	}

	//find not number and get position of '.'
	while(*p != '\0') {
		if(*p == '.' && point == -1) {
			point = p - value;
			p = p + 1;
			continue;
		}
		if(*p < 48 || *p > 57) {
			nodeList[currentCount].errorCode = ERROR_VALUE_LACKQUOTATION;
			return -1;
		}
		p = p + 1;
	}

	//error position of '.'
	int length = strlen(value);
	if(point == 0 || point == length) {
		nodeList[currentCount].errorCode = ERROR_VALUE_POINT;
		return -1;
	}

	p = value;
	//int
	if(point == -1) {	
		if(*p == '0') {
			nodeList[currentCount].errorCode = ERROR_VALUE_INT_ZEROFIRST;
			return -1;
		}
		else {
			nodeList[currentCount].type = INT;
			return 0;
		}
	}

	//float
	else {
		if(*p == '0' && *(p + 1) != '.') {
			//example value=00.123, this is invalid.
			nodeList[currentCount].errorCode = ERROR_VALUE_FLOAT_INVALID;
			return -1;
		}
		else {
			nodeList[currentCount].type = FLOAT;
			return 0;
		}
	}
}

/****************************************************************************
Description: function printResult, judge errorCode of item in nodeList, and print result.
parameter: int length, length of nodeList.
returnL int

****************************************************************************/
int printResult(int length) {
	int i = 0;
	char* type = NULL;
	char* errorString = NULL;

	printf("The result: \n");
	for(i = 0; i < length; i++) {
		if(nodeList[i].errorCode == ERROR_NONE) {
			switch(nodeList[i].type) {
				case INT:
					type = intString;
					break;
				case FLOAT:
					type = floatString;
					break;
				case CHAR:
					type = charString;
					break;
				case STRING:
					type = stringString;
					break;
			}
			printf("%s(%s, %s)\n", nodeList[i].name, type, nodeList[i].value);
		}
		//print error informations
		else {
			switch(nodeList[i].errorCode) {
				case ERROR_NAME_FIRSTLETTER:
					errorString = errorNameFirstLetterString;
					break;
				case ERROR_NAME_INVALIDCH:
					errorString = errorNameInvalidCH;
					break;
				case ERROR_NAME_KEYWORD:
					errorString = errorNameKeyword;
					break;
				case ERROR_NAME_REPEATDEFINE:
					errorString = errorNameRepeatDefine;
					break;

				case ERROR_VALUE_OVERCHAR:
					errorString = errorValueOverChar;
					break;
				case ERROR_VALUE_LACKQUOTATION:
					errorString = errorValueLackQuotation;
					break;
				case ERROR_VALUE_POINT:
					errorString = errorValuePoint;
					break;
				case ERROR_VALUE_INT_ZEROFIRST:
					errorString = errorValueIntZeroFirst;
					break;
				case ERROR_VALUE_FLOAT_INVALID:
					errorString = errorValueFloatInvalid;
			}
			printf("%s(%s)\n", nodeList[i].name, errorString);
		}
	}
	
	return 0;
}

/****************************************************************************
Description: function printTotalResult, count number of each type and print.
parameter: int length, length of nodeList.
returnL int

****************************************************************************/
int printTotalResult(int length) {
	int i = 0;
	int totalResult[TYPENUM] = {0};		//int, float, char, string

	for(i = 0; i < length; i++) {
		if(nodeList[i].errorCode == ERROR_NONE) {
			switch(nodeList[i].type) {
				case INT:
					totalResult[0] += 1;
					break;
				case FLOAT:
					totalResult[1] += 1;
					break;
				case CHAR:
					totalResult[2] += 1;
					break;
				case STRING:
					totalResult[3] += 1;
					break;
			}
		}
	}

	printf("int_num: %d, float_num: %d, char_num: %d, string_num: %d\n", totalResult[0], totalResult[1], totalResult[2], totalResult[3]);

	return 0;
}



