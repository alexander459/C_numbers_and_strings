#ifndef __NUMBERS_H__
#define __NUMBERS_H__

#include <stddef.h>
#include "d_strings.h"

typedef struct number* number;
typedef enum{INVAL_T, FLOAT, INT} type;
typedef enum{INVAL_S, NEGATIVE, POSITIVE} sign;
typedef enum{VALID_NUMBER, INVALID_NUMBER} validity;

extern const char* sign_names_array[];
extern const char* type_names_array[];

validity Number(number* new_num, char* num);
void DeleteNumber(number n);

string GetNumber(number n);

void PrintNumber(number n);
void PrintLnNumber(number n);

validity AssignNumber(number n, char* num);
validity ReadNumber(number n);
validity AddNumber(number res, number n1, number n2);
validity SubNumber(number res, number n1, number n2);

type GetTypeNumber(number n);
sign GetSignNumber(number n);

void ChangeSignNumber(number n);

size_t GetTotalDigits(number n);
size_t GetDecimalDigits(number n);
size_t GetIntDigits(number n);
#endif
