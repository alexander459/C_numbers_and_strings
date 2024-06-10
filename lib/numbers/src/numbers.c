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
	string num;
	string decimal_part;
	validity valid;
	size_t digits;
};


const char* sign_names_array[] = {"valid", "invalid", "negative", "positive"};
const char* type_names_array[] = {"valid", "invalid", "float", "int"};



static int match_regex(const char *string, const char *pattern) {
	regex_t regex;
	int ret;

	ret = regcomp(&regex, pattern, REG_EXTENDED);
	if(ret){
		exit(1);
	}

	ret = regexec(&regex, string, 0, NULL, 0);
	regfree(&regex);

	return !ret;
}


static sign check_sign(char* num){
	const char *negative_pattern = "^-[0-9]+(\\.[0-9]+)?$";
	const char *positive_pattern = "^[+]?[0-9]+(\\.[0-9]+)?$";
	int both = 0;
	size_t num_len, i;

	sign num_sign;

	num_sign = INVAL_S;
	if(match_regex(num, negative_pattern)){
		num_sign = NEGATIVE;
		both++;
	}
	
	if(match_regex(num, positive_pattern)){
		num_sign = POSITIVE;
		both++;
	}

	assert(both <= 1);

	if(num_sign == VAL_S){
		if(num[0] == '+' || num[0] == '-'){

			num_len = strlen(num);
			for(i=0; i<num_len-1; i++){
				num[i] = num[i+1];
			}
		}
	}
	return num_sign;

}


static type check_type(char* num, string decimal_part){
	const char* integer_pattern = "^[+-]?[0-9]+$";
	const char* float_pattern = "^[+-]?[0-9]+\\.[0-9]+$";
	char* decimal_part_str;

	size_t i;
	int both;
	type num_type;

	both = 0;
	num_type = INVAL_T;
	if(match_regex(num, integer_pattern)){
		num_type = INT;
		both++;
	}
	
	if(match_regex(num, float_pattern)){
		num_type = FLOAT;
		both++;
	}
	
	assert(both <= 1);

	if(num_type == FLOAT){
		for(i=0; num[i]!='.'; i++);
		decimal_part_str = &num[i+1];
		AssignString(decimal_part, decimal_part_str);
		
	}
	return num_type;
}


static validity check_number(string num, type* num_type, sign* num_sign, string decimal_part){
	char* str_num;
	str_num = GetString(num);
	*num_type = check_type(str_num, decimal_part);
	*num_sign = check_sign(str_num);
	
	if(strlen(str_num) == 0) return INVALID_NUMBER;

	if((*num_type == INVAL_T) || (*num_sign == INVAL_S)){
		return INVALID_NUMBER;
	}

	return VALID_NUMBER;
}


validity Number(number* new_num, char* num){
	type num_type;
	sign num_sign;
	string decimal_part;

	*new_num = (number)malloc(sizeof(struct number));
	assert(*new_num != NULL);

	if(num != NULL){
		(*new_num)->num = String(num);		
	}else{
		(*new_num)->num = String("0");
	}

	(*new_num)->decimal_part = String("0");

	(*new_num)->valid = check_number((*new_num)->num, &num_type, &num_sign, decimal_part);
	(*new_num)->num_type = num_type;
	(*new_num)->num_sign = num_sign;
	(*new_num)->decimal_part = decimal_part;
	(*new_num)->digits = SizeString((*new_num)->num);
	return (*new_num)->valid;
}


validity AssignNumber(number n, char* num){
	type num_type;
	sign num_sign;
	string decimal_part;

	assert(n != NULL);
	AssignString(n->num, num);

	n->valid = check_number(n->num, &num_type, &num_sign, decimal_part);
	n->num_type = num_type;
	n->num_sign = num_sign;
	n->digits = SizeString(n->num);
	return n->valid;
}

validity ReadNumber(number n){
	type num_type;
	sign num_sign;
	string decimal_part;

	assert(n != NULL);
	ReadString(n->num);

	n->valid = check_number(n->num, &num_type, &num_sign, decimal_part);
	n->num_type = num_type;
	n->num_sign = num_sign;
	n->digits = SizeString(n->num);
	return n->valid;
}


void DeleteNumber(number num){
	DeleteString(num->num);
	DeleteString(num->decimal_part);
	free(num);
	return;
}

void PrintNumber(number num){
	printf("%s", GetString(num->num));
	return;
}

char* GetNumber(number num){
	assert(num != NULL);
	return GetString(num->num);
}

type GetTypeNumber(number n){
	assert(n != NULL);
	return n->num_type;
}

sign GetSignNumber(number n){
	assert(n != NULL);
	return n->num_sign;
}


static int singleAdd(int n1, int n2, int* carry){
	int res;

	assert(carry != NULL);
	res = (*carry) + n1 + n2;
	(*carry) = (int)res/10;
	res = res%10;
	return res;
}
/*
static singleSub(int n1, int n2){
	return (n1 - n2);
}*/

size_t GetDigits(number n){
	assert(n != NULL);
	return n->digits;
}

static int char_to_int(char c){
	return (c - '0');
}

static char int_to_char(int a){
	return (a + '0');
}


validity AddNumber(number res, number n1, number n2){
	char* n1_str;
	char* n2_str;
	int tmp_res, carry;
	string decimal_part;

	string new_num;
	long int res_len, n1_i, n2_i;
	type num_type;
	sign num_sign;

	n1_str = GetNumber(n1);
	/*printf("n1 is %s\n", n1_str);
*/
	n2_str = GetNumber(n2);
	/*printf("n2 is %s\n", n2_str);
	*/
	
	/*printf("n1 is %s, %s\n", type_names_array[GetTypeNumber(n1)], sign_names_array[GetSignNumber(n1)]);
	printf("n2 is %s, %s\n", type_names_array[GetTypeNumber(n2)], sign_names_array[GetSignNumber(n2)]);
	*/
	if(check_number(n1->num, &num_type, &num_sign, decimal_part) == INVALID_NUMBER){
		return INVALID_NUMBER;
	}

	if(check_number(n2->num, &num_type, &num_sign, decimal_part) == INVALID_NUMBER){
		return INVALID_NUMBER;
	}


	if((GetTypeNumber(n1) == FLOAT) || (GetTypeNumber(n2) == FLOAT)){
		res->num_type = FLOAT;
	}else{
		res->num_type = INT;
	}


	if(GetSignNumber(n1) == GetSignNumber(n2)){
		res->num_sign = GetSignNumber(n1);


		if(GetDigits(n1) > GetDigits(n2)){
			res_len = GetDigits(n1) + 1;
		}else{
			res_len = GetDigits(n2) + 1;
		}

		new_num = String(NULL);
		carry = 0;
		
		n1_i = GetDigits(n1)-1;
		n2_i = GetDigits(n2)-1;
		while(n1_i >= 0 && n2_i >=0){
			tmp_res = singleAdd(char_to_int(n1_str[n1_i]), char_to_int(n2_str[n2_i]), &carry);
			PushFrontString(new_num, int_to_char(tmp_res));
			n1_i--;
			n2_i--;
		}
		
		while(n1_i >= 0){
			tmp_res = singleAdd(char_to_int(n1_str[n1_i]), 0, &carry);
			PushFrontString(new_num, int_to_char(tmp_res));
			n1_i--;
		}

		while(n2_i >= 0){
			tmp_res = singleAdd(char_to_int(n2_str[n2_i]), 0, &carry);
			PushFrontString(new_num, int_to_char(tmp_res));
			n2_i--;
		}

		if(carry != 0){
			PushFrontString(new_num, int_to_char(carry));
		}
		free(res->num);
		res->num = new_num;
	}else{
		/* subtruct */
	}
	return VALID_NUMBER;
}



