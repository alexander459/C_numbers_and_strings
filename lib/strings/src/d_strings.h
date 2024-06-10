#ifndef __STRINGS_H__
#define __STRINGS_H__

#include <stdio.h>
#include <stddef.h>
#define EMPTY_STRING NULL

typedef struct string* string;


/* CONSTRUCTS A NEW STRING
 * PTR s COULD EITHER BE A STRING LITERAL OR NULL.
 * IF s IS LITERAL THEN IT CONVERTS IT TO A STRING.
 * IF s IS NULL THEN IT CREATES AN EMPTY STRING.
 * IF s HAVE BEEN ALREADY CONSTRUCTED THE BEHAVIOUR IS UNPREDICTABLE.
*/
string String(char* s);



/* DESTROYES THE STRING s.
 * IT IS IMPORTANT FOR s TO BE CONSTRUCTED USING THE String FUNCTION.
 * OTHERWISE THE BEHAVIOUR IS UNPREDICTABLE.
*/
void DeleteString(string s);



/* READS A STRING FROM STDIN AND PLACES IT IN s.
 * IT IS IMPORTANT FOR s TO BE CONSTRUCTED USING THE String FUNCTION
*/
void ReadString(string s);



/* PRINTS THE CONTENTS OF THE s IN STDOUT.
 * ITS IMPORTANT FOR s TO BE CONSTRUCTED USING THE String FUNCTION
*/
void PrintString(string s);




/* SAME WITH PRINT BUT IT PRINTS A NEWLINE AT THE END.
*/
void PrintLnString(string s);




/* RETURNS THE s AS A CHAR POINTER
 */
char* GetString(string s);



/* RETURNS THE LENGTH OF THE STRING s.
 * IT IS IMPORTANT FOR s TO BE CONSTRUCTED USING THE String FUNCTION.
*/
size_t SizeString(string s);



/* COPIES THE STRING src TO THE STRING dst.
 * IT IS IMPORTANT FOR BOTH src AND dst TO BE CONSTRUCTED USING THE String FUNCTION.
 *
*/
void Copy(string dst, string src);



/* CONCATENATES THE STRING src TO THE STRING dst.
 * IT IS IMPORTANT FOR BOTH src AND dst TO BE CONSTRUCTED USING THE String FUNCTION.
 *
*/
void Concat(string dst, string src);
void Copy_n(string dst, string src, size_t n);
void Concat_n(string dst, string src, size_t n);



/* IN SUCCESS RETURNS THE INTEGER REPRESENTED FROM THE STRING s.
 * IN FAILURE RETURNS 0.
*/
int Atoi(string s);



/* PERFORMS THE OPERATION s = str.
 * IT IS IMPORTANT FOR s TO BE CONSTRUCTED USING THE String FUNCTION.
 * THE PREVIOUS CONTENT OF s IS OVERWRITTEN BY str.
 * THE SAME OPERATION BETWEEN 2 STRINGS CAN BE PERFORMED USING THE Copy FUNCTION.
*/
void AssignString(string s, char* str);



/* PUSH AND POP, FRONT AND BACK.
 * STRINGS MUST BE CONSTRUCTED BY THE String FUNCTION.
*/
void PushFrontString(string s, char c);
char PopFrontString(string s);
void PushBackString(string s, char c);
char PopBackString(string s);



/* RETURNS THE SIZE ALLOCATED IN MEMORY IN TERMS OF BYTES FOR STRING s.
 * IT IS IMPORTANT FOR s TO BE CONSTRUCTED USING THE String FUNCTION.
 * NOT IMPLEMENTED YES.
*/
size_t GetMemorySizeString(string s);


#endif
