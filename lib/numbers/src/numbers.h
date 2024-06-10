#ifndef __NUMBERS_H__
#define __NUMBERS_H__

#include <stddef.h>

typedef struct number* number;
typedef enum{VAL_T, INVAL_T, FLOAT, INT} type;
typedef enum{VAL_S, INVAL_S, NEGATIVE, POSITIVE} sign;
typedef enum{VALID_NUMBER, INVALID_NUMBER} validity;

extern const char* sign_names_array[];
extern const char* type_names_array[];

validity Number(number* new_num, char* num);
void DeleteNumber(number num);

char* GetNumber(number num);

void PrintNumber(number num);
validity AssignNumber(number n, char* num);
validity ReadNumber(number n);
validity AddNumber(number res, number n1, number n2);

type GetTypeNumber(number n);
sign GetSignNumber(number n);

size_t GetDigits(number n);
#endif
