#include <stddef.h>
#include "d_strings.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string{
	char* str;
	size_t bytes_alloced;	/*future use*/
	size_t len;
};



static size_t char_ptr_str_len(char* str){
	size_t i;
	assert(str != NULL);
	for(i=0; str[i]!='\0'; i++);
	return i;
}


string String(char* s){
	string new_string;
	size_t len;
	
	new_string = (string)malloc(sizeof(struct string));
	assert(new_string != NULL);
	
	if(s != NULL){
		len = char_ptr_str_len(s);
	}else{
		len = 0;
	}

	new_string->str = (char*)malloc(len + 1);
	assert(new_string->str != NULL);

	if(s != NULL){
		new_string->str = strcpy(new_string->str, s);
	}else{
		new_string->str[0] = '\0';
	}

	new_string->len = len;
	return new_string;
}


void ReadString(string s){
	char c;
	size_t i;

	assert(s != NULL);
	assert(s->str != NULL);

	i = 0;
	c = getchar();
	do{	
		s->str[i] = c;
		i++;
		s->str = (char*)realloc(s->str, i+1);
		assert(s->str != NULL);
		c = getchar();
	}while(c != '\n');

	s->str[i] = '\0';
	s->len = i;
	return;
}


void DeleteString(string s){
	free(s->str);
	free(s);
	return;
}


void PrintString(string s){
	assert(s != NULL);
	assert(s->str != NULL);
	printf("%s", s->str);
	return;
}

void PrintLnString(string s){
	PrintString(s);
	printf("\n");
	return;
}


size_t SizeString(string s){
	assert(s != NULL);
	assert(s->str != NULL);
	return s->len;
}

void Copy(string dst, string src){
	size_t len;

	assert(dst != NULL);
	assert(src != NULL);
	assert(dst->str != NULL);
	assert(src->str != NULL);

	if(strlen(dst->str) > strlen(src->str))
		len = strlen(dst->str);
	else
		len = strlen(src->str);

	dst->str = (char*)realloc((char*)dst->str, len + 1);
	assert(dst->str != NULL);

	dst->str = strcpy(dst->str, src->str);
	dst->len = src->len;
	return;
}


void Copy_n(string dst, string src, size_t n){
	size_t len;

	assert(dst != NULL);
	assert(src != NULL);
	assert(dst->str != NULL);
	assert(src->str != NULL);

	if(strlen(dst->str) > strlen(src->str))
		len = strlen(dst->str);
	else
		len = strlen(src->str);

	dst->str = (char*)realloc((char*)dst->str, len + 1);
	assert(dst->str != NULL);

	dst->str = strncpy(dst->str, src->str, n);
	dst->len = src->len;
	return;
}


void Concat(string dst, string src){
	size_t len;

	assert(dst != NULL);
	assert(src != NULL);
	assert(dst->str != NULL);
	assert(src->str != NULL);

	len = strlen(src->str) + strlen(dst->str);

	dst->str = (char*)realloc((char*)dst->str, len + 1);
	assert(dst->str != NULL);

	dst->str = strcat(dst->str, src->str);
	dst->len += src->len;
	return;
}


void Concat_n(string dst, string src, size_t n){
	size_t len;

	assert(dst != NULL);
	assert(src != NULL);
	assert(dst->str != NULL);
	assert(src->str != NULL);

	len = strlen(src->str) + strlen(dst->str);

	dst->str = (char*)realloc((char*)dst->str, len + 1);
	assert(dst->str != NULL);

	dst->str = strncat(dst->str, src->str, n);
	dst->len += n;
	return;
}


int Atoi(string s){
	assert(s != NULL);
	return atoi(s->str);
}



char* GetString(string s){
	assert(s != NULL);
	return s->str;
}


void AssignString(string s, char* str){
	size_t i, s_len;

	assert(s != NULL);
	assert(s->str != NULL);
	assert(str != NULL);

	s_len = strlen(str);
	s->len = 0;

	for(i=0; i<=s_len; i++){
		s->str = (char*)realloc((char*)s->str, i+1);
		assert(s->str != NULL);
		s->str[i] = str[i];
		s->len++;
	}

	s->len--;				/* LEN DOES NOT INCLUDE '\0' */

	return;
}


void PushFrontString(string s, char c){
	size_t len;
	size_t i;

	assert(s != NULL);
	len = s->len;
	s->str = (char*)realloc((char*)s->str, len+2);
	assert(s->str != NULL);
	s->len++;

	for(i=s->len; i>=1; i--){
		s->str[i] = s->str[i-1];
	}

	s->str[0] = c;

	return;
}

char PopFrontString(string s){
	size_t len, i;
	char c;

	assert(s != NULL);
	assert(s->str != NULL);

	if(s->len == 0)
		return '\0';

	c = s->str[0];

	len = s->len;
	for(i=0; i<len; i++){
		s->str[i] = s->str[i+1];
	}
	s->str = (char*)realloc((char*)s->str, len);
	assert(s->str != NULL);

	s->len--;
	return c;
}

void PushBackString(string s, char c){
	size_t len;

	assert(s != NULL);
	len = s->len;
	s->str = (char*)realloc((char*)s->str, len+2);
	assert(s->str != NULL);

	s->str[len] = c;
	s->str[len+1] = '\0';
	s->len++;

	return;
}


char PopBackString(string s){
	size_t len;
	char c;

	assert(s != NULL);
	assert(s->str != NULL);
	
	if(s->len == 0)
		return '\0';

	len = s->len;
	c = s->str[len-1];
	s->str[len-1] = '\0';

	s->str = (char*)realloc((char*)s->str, len);
	assert(s->str != NULL);

	s->len--;
	return c;
}



size_t GetAllocatedSizeString(string s){
	assert(s != NULL);
	return s->bytes_alloced;
}


int RemoveFromString(string s, char c){
	size_t i;

	assert(s != NULL);
	assert(s->str != NULL);
	assert(c != '\0');
	for(i=0; s->str[i] != c && s->str[i] != '\0'; i++){

	}
	if(s->str[i] == '\0') return 0;
	
	while(s->str[i] != '\0'){
		s->str[i] = s->str[i+1];
		i++;
	}
	
	s->len--;
	s->str = (char*)realloc((char*)s->str, s->len + 1);
	assert(s->str != NULL);
	return 1;
}