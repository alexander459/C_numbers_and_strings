#include "numbers.h"
#include <stddef.h>
#include "d_strings.h"
#include <stdlib.h>
#include <assert.h>
#include <regex.h>
#include <string.h>

struct number{
	type num_type;
	sign num_sign;

	string whole_num;
	string int_part;
	string decimal_part;
	validity valid;

	size_t int_digits;
	size_t dec_digits;
};


const char* sign_names_array[] = {"valid", "invalid", "negative", "positive"};
const char* type_names_array[] = {"valid", "invalid", "float", "int"};



static int match_regex(const char *string, const char *pattern) {
	regex_t regex;
	int ret;

	ret = regcomp(&regex, pattern, REG_EXTENDED);
	if(ret) exit(1);

	ret = regexec(&regex, string, 0, NULL, 0);
	regfree(&regex);

	return !ret;
}


static void check_sign(number new_num, char* num){
	const char *negative_pattern = "^-[0-9]+(\\.[0-9]+)?$";
	const char *positive_pattern = "^[+]?[0-9]+(\\.[0-9]+)?$";

	if(match_regex(num, negative_pattern))
		new_num->num_sign = NEGATIVE;
	else if(match_regex(num, positive_pattern))
		new_num->num_sign = POSITIVE;
	else
		new_num->num_sign = INVAL_S;

	return;
}


static void check_type(number new_num, char* num){
	const char* integer_pattern = "^[+-]?[0-9]+$";
	const char* float_pattern = "^[+-]?[0-9]+\\.[0-9]+$";
	char* tmp_num;
	string s;

	size_t i;

	s = String(num);
	tmp_num = GetString(s);

	if(match_regex(num, integer_pattern)){
		AssignString(new_num->whole_num, tmp_num);

		new_num->num_type = INT;
		AssignString(new_num->int_part, tmp_num);
		AssignString(new_num->decimal_part, "0");

		RemoveFromString(new_num->int_part, '-');
		RemoveFromString(new_num->int_part, '+');

		new_num->int_digits = SizeString(new_num->int_part);
		new_num->dec_digits = 0;

	}else if(match_regex(num, float_pattern)){
		AssignString(new_num->whole_num, tmp_num);

		new_num->num_type = FLOAT;
		for(i=0; tmp_num[i]!='.'; i++);
		AssignString(new_num->decimal_part, &tmp_num[i+1]);
		tmp_num[i] = '\0';
		AssignString(new_num->int_part, tmp_num);
		tmp_num[i] = '.';

		RemoveFromString(new_num->int_part, '-');
		RemoveFromString(new_num->int_part, '+');

		new_num->int_digits = SizeString(new_num->int_part);
		new_num->dec_digits = SizeString(new_num->decimal_part);
	}else{
		new_num->num_type = INVAL_T;
	}

	DeleteString(s);
	return;
}


static void place_number(number new_num, char* num){
	assert(num != NULL);
	assert(new_num != NULL);

	check_type(new_num, num);
	check_sign(new_num, num);

	if((new_num->num_type == INVAL_T) || (new_num->num_sign == INVAL_S))
		new_num->valid = INVALID_NUMBER;
	else
		new_num->valid = VALID_NUMBER;

	return;
}


validity Number(number* new_num, char* num){

	*new_num = (number)malloc(sizeof(struct number));
	assert(*new_num != NULL);

	(*new_num)->int_part = String(NULL);
	(*new_num)->decimal_part = String(NULL);
	(*new_num)->whole_num = String(NULL);

	if(num == NULL){
		(*new_num)->num_type = INT;
		(*new_num)->num_sign = POSITIVE;
		(*new_num)->valid = VALID_NUMBER;
		(*new_num)->int_digits = 1;
		(*new_num)->dec_digits = 0;

		AssignString((*new_num)->int_part, "0");
		AssignString((*new_num)->decimal_part, "0");
		AssignString((*new_num)->whole_num, "0");
	}else{
		place_number(*new_num, num);
	}
	
	return (*new_num)->valid;
}


validity AssignNumber(number n, char* num){
	assert(n != NULL);
	assert(num != NULL);

	place_number(n, num);
	return n->valid;
}


validity ReadNumber(number n){
	string s;

	assert(n != NULL);
	s = String(NULL);
	ReadString(s);

	place_number(n, GetString(s));
	DeleteString(s);
	return n->valid;
}


void DeleteNumber(number n){
	DeleteString(n->int_part);
	DeleteString(n->decimal_part);
	free(n);
	return;
}

void PrintNumber(number n){
	assert(n != NULL);
	assert(n->whole_num != NULL);

	PrintString(n->whole_num);
	return;
}

void PrintLnNumber(number n){
	assert(n != NULL);
	assert(n->whole_num != NULL);

	PrintLnString(n->whole_num);
	return;
}

string GetNumber(number n){
	assert(n != NULL);
	return n->whole_num;
}

type GetTypeNumber(number n){
	assert(n != NULL);
	return n->num_type;
}

sign GetSignNumber(number n){
	assert(n != NULL);
	return n->num_sign;
}



size_t GetTotalDigits(number n){
	assert(n != NULL);
	return n->int_digits + n->dec_digits;
}


size_t GetIntDigits(number n){
	assert(n != NULL);
	return n->int_digits;
}


size_t GetDecimalDigits(number n){
	assert(n != NULL);
	return n->dec_digits;
}


static int char_to_int(char c){
	return (c - '0');
}

static char int_to_char(int a){
	return (a + '0');
}

static int singleAdd(int n1, int n2, int* carry){
	int res;

	assert(carry != NULL);
	res = (*carry) + n1 + n2;
	(*carry) = (int)res/10;
	res = res%10;
	return res;
}

static int singleSub(int n1, int n2, int* carry){

	n2 = n2 + (*carry);
	if(n1 < n2){
		n1 = n1*10;
		*carry = 1;
	}
	return (n1-n2);
}

static void fill_zeros_for_operations(number n1, number n2){
	size_t missing_ints, missing_decs, i;

	if(n1->int_digits > n2->int_digits){
		missing_ints = n1->int_digits - n2->int_digits;
		for(i=0; i<missing_ints; i++){
			PushFrontString(n2->int_part, '0');
		}
	}else{
		missing_ints = n2->int_digits - n1->int_digits;
		for(i=0; i<missing_ints; i++){
			PushFrontString(n1->int_part, '0');
		}
	}

	if(n1->dec_digits > n2->dec_digits){
		missing_decs = n1->dec_digits - n2->dec_digits;
		for(i=0; i<missing_decs; i++){
			PushBackString(n2->decimal_part, '0');
		}
	}else{
		missing_decs = n2->dec_digits - n1->dec_digits;
		for(i=0; i<missing_decs; i++){
			PushBackString(n1->decimal_part, '0');
		}
	}
	return;
}

static void AddPart(string res, string n1, string n2, int* carry){
	long int n1_i, n2_i;
	char* n1_str;
	char* n2_str;
	int tmp_res;

	assert(res != NULL);
	assert(n1 != NULL);
	assert(n2 != NULL);

	n1_str = GetString(n1);
	n2_str = GetString(n2);

	n1_i = SizeString(n1)-1;
	n2_i = SizeString(n2)-1;

	while(n1_i >= 0 && n2_i >=0){
		tmp_res = singleAdd(char_to_int(n1_str[n1_i]), char_to_int(n2_str[n2_i]), carry);
		PushFrontString(res, int_to_char(tmp_res));
		n1_i--;
		n2_i--;
	}
	
	while(n1_i >= 0){
		tmp_res = singleAdd(char_to_int(n1_str[n1_i]), 0, carry);
		PushFrontString(res, int_to_char(tmp_res));
		n1_i--;
	}

	while(n2_i >= 0){
		tmp_res = singleAdd(char_to_int(n2_str[n2_i]), 0, carry);
		PushFrontString(res, int_to_char(tmp_res));
		n2_i--;
	}

	return;
}


validity AddNumber(number res, number n1, number n2){
	int carry;

	if(n1->valid == INVALID_NUMBER || n2->valid == INVALID_NUMBER) return INVALID_NUMBER;

	if((n1->num_type == FLOAT) || (n2->num_type == FLOAT))
		res->num_type = FLOAT;
	else
		res->num_type = INT;


	if(n1->num_sign == n2->num_sign){
		res->num_sign = n1->num_sign;
		AssignString(res->decimal_part, "");
		AssignString(res->int_part, "");
		AssignString(res->whole_num, "");

		carry = 0;
		fill_zeros_for_operations(n1, n2);

		AddPart(res->decimal_part, n1->decimal_part, n2->decimal_part, &carry);
		AddPart(res->int_part, n1->int_part, n2->int_part, &carry);

		if(carry != 0)
			PushFrontString(res->int_part, int_to_char(carry));

		if(res->num_sign == POSITIVE)
			AssignString(res->whole_num, "+");
		else
			AssignString(res->whole_num, "-");

		if(res->num_type == FLOAT){
			Concat(res->whole_num, res->int_part);
			PushBackString(res->whole_num, '.');
			Concat(res->whole_num, res->decimal_part);
			res->int_digits = SizeString(res->int_part);
			res->dec_digits = SizeString(res->decimal_part);
		}else{
			Concat(res->whole_num, res->int_part);
			res->int_digits = SizeString(res->int_part);
			res->dec_digits = 0;
		}

	}else{
		if(n1->num_sign == NEGATIVE) SubNumber(res, n2, n1);
		else SubNumber(res, n1, n2);
	}

	return VALID_NUMBER;
}


validity SubNumber(number res, number n1, number n2){
	int carry;

	if(n1->valid == INVALID_NUMBER || n2->valid == INVALID_NUMBER) return INVALID_NUMBER;

	if((n1->num_type == FLOAT) || (n2->num_type == FLOAT))
		res->num_type = FLOAT;
	else
		res->num_type = INT;


	if(n1->num_sign != n2->num_sign){
		ChangeSignNumber(n2);
		return AddNumber(res, n1, n2);
	}else{

	}
	return VALID_NUMBER;

}

void ChangeSignNumber(number n){
	assert(n != NULL);
	if(n->num_sign == INVAL_S)
		return;
	if(n->num_sign == POSITIVE)
		n->num_sign = NEGATIVE;
	else
		n->num_sign = POSITIVE;
	return;
}